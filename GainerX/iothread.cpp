#include "stdafx.h"
#include "protocol.h"

HANDLE init_comm(BSTR devicename)
{
    HANDLE h = CreateFileW(devicename, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    if (h == INVALID_HANDLE_VALUE)
    {
        ATLTRACE(_T("Can't Open the port: %d\n"), GetLastError());
        return h;
    }
    DCB dcb = { sizeof(DCB) };
    GetCommState(h, &dcb);
    dcb.BaudRate = CBR_38400;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    SetCommState(h, &dcb);
    return h;
}

void init_io(OVERLAPPED& roverlapped, OVERLAPPED& soverlapped)
{
    soverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    roverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

bool message_dispatch(std::queue<char*>& queue)
{
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        switch (msg.message)
        {
        case WM_QUIT:
        case WM_COM_CLOSE:
            return true;
        case WM_COM_IO:
            queue.push(reinterpret_cast<char*>(msg.lParam));
            break;
        default:
            DispatchMessage(&msg);
            break;
        }
    }
    return false;
}

void abort_io(HANDLE h, std::queue<char*>& queue, Context& context)
{
    DWORD dwRead;
    Sleep(1000);
    PurgeComm(h, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    ClearCommError(h, &dwRead, NULL);
    while (queue.size() > 0)
    {
        char* p = queue.front();
        queue.pop();
        delete[] p;
    }
    queue.push(strcpy(new char[3], "Q*"));
    context.notify_reboot();
    context.next_state(IDLE);
}

#if 0
unsigned __stdcall start_iothread(void* param)
{
    std::queue<char*> queue;
    queue.push(strcpy(new char[3], "Q*"));
    message_dispatch(queue);

    HANDLE h = init_comm(reinterpret_cast<ThreadParam*>(param)->devicename);
    OVERLAPPED roverlapped = { 0 }, soverlapped = { 0 };
    init_io(roverlapped, soverlapped);
    HANDLE events[] = { roverlapped.hEvent, soverlapped.hEvent };
    int event_count(0);
    Context context(*reinterpret_cast<ThreadParam*>(param));

    for (bool request_read = true;;)
    {
        DWORD dw, len;
        char buff[16];
        if (request_read)
        {
            for (;;)
            {
                if (ReadFile(h, buff, 1, &len, &roverlapped))
                {
#ifdef _DEBUG_TRACE
                    ATLTRACE(_T("-%c (%d)\n"), buff[0], len);
#endif
                    if (len == 1 && !context.push(buff[0])) {
                        abort_io(h, queue, context);
                    }
                    continue;
                }
                else
                {
                    DWORD error = GetLastError();
                    if (error != ERROR_IO_PENDING)
                    {
                        context.notify(ERROR_OCCURED, error);
                        goto exit_thread;
                    }
                    break;
                }
            }
            request_read = false;
            event_count++;
        }

        if (message_dispatch(queue)) break;

        if (context.is_idle() && event_count <= 1 && queue.size() > 0)
        {
            dw = WriteFile(h, queue.front(), strlen(queue.front()), NULL, &soverlapped);
            if (!dw)
            {
                DWORD error = GetLastError();
                if (error != ERROR_IO_PENDING)
                {
                    context.notify(ERROR_OCCURED, error);
                    goto exit_thread;
                }
                event_count++;
            }
            else
            {
#ifdef _DEBUG_TRACE
                ATLTRACE("%s\n", queue.front());
#endif
                delete[] queue.front();
                queue.pop();
            }
            context.next_state(WAIT_RESP);
        }

        dw = MsgWaitForMultipleObjects(event_count, events, FALSE, 3000, QS_ALLEVENTS);
        if (dw == WAIT_TIMEOUT) 
        {
            if (!context.is_idle())
            {
                context.next_state(IDLE);
            }
            continue;
        }
        else if (dw == WAIT_OBJECT_0)
        {
            event_count--;
            if (GetOverlappedResult(h, &roverlapped, &len, FALSE))
            {
                if (len == 1)
                {
#ifdef _DEBUG_TRACE
                    ATLTRACE(_T("=%c\n"), buff[0]);
#endif
                    if (!context.push(buff[0]))
                    {
                        abort_io(h, queue, context);
                    }
                }
                request_read = true;
            }
        }
        else if (event_count > 1 && dw == WAIT_OBJECT_0 + 1)
        {
            event_count--;
            GetOverlappedResult(h, &soverlapped, &len, FALSE);
#ifdef _DEBUG_TRACE
            ATLTRACE("%s\n", queue.front());
#endif
            delete[] queue.front();
            queue.pop();
        }
    }
exit_thread:
    CancelIo(h);
    CloseHandle(h);
    for (int i = 0; i < COUNT_OF(events); i++) CloseHandle(events[i]);
    return 0;
}
#endif

unsigned __stdcall start_iothread(void* param)
{
    std::queue<char*> queue;
    queue.push(strcpy(new char[3], "Q*"));
    message_dispatch(queue);

    HANDLE h = init_comm(reinterpret_cast<ThreadParam*>(param)->devicename);
    OVERLAPPED roverlapped = { 0 }, soverlapped = { 0 };
    COMSTAT cs;
    init_io(roverlapped, soverlapped);
    HANDLE events[] = { roverlapped.hEvent, soverlapped.hEvent };
    int event_count(0);
    Context context(*reinterpret_cast<ThreadParam*>(param));
    SetCommMask(h, EV_RXCHAR);

    for (bool request_read = true;;)
    {
        DWORD dw, len, dwEvent;
        char buff[64];
        if (request_read)
        {
            if (WaitCommEvent(h, &dwEvent, &roverlapped)) goto data_read;
            DWORD error = GetLastError();
            if (error != ERROR_IO_PENDING)
            {
                context.notify(ERROR_OCCURED, error);
                goto exit_thread;
            }
            request_read = false;
            event_count++;
        }

        if (message_dispatch(queue)) break;

        if (context.is_idle() && event_count <= 1 && queue.size() > 0)
        {
            dw = WriteFile(h, queue.front(), strlen(queue.front()), NULL, &soverlapped);
            if (!dw)
            {
                DWORD error = GetLastError();
                if (error != ERROR_IO_PENDING)
                {
                    context.notify(ERROR_OCCURED, error);
                    goto exit_thread;
                }
                event_count++;
            }
            else
            {
#ifdef _DEBUG_TRACE
                ATLTRACE("%s\n", queue.front());
#endif
                delete[] queue.front();
                queue.pop();
            }
            context.next_state(WAIT_RESP);
        }

        dw = MsgWaitForMultipleObjects(event_count, events, FALSE, 3000, QS_ALLEVENTS);
        if (dw == WAIT_TIMEOUT) 
        {
            if (!context.is_idle())
            {
                context.next_state(IDLE);
            }
            continue;
        }
        else if (dw == WAIT_OBJECT_0)
        {
            request_read = true;
            event_count--;
            if (!GetOverlappedResult(h, &roverlapped, &len, FALSE))
            {
                context.notify(ERROR_OCCURED, GetLastError());
                goto exit_thread;
            }

    data_read:
            ClearCommError(h, &dw, &cs);
            if ((dwEvent & EV_RXCHAR) && cs.cbInQue)
            {
                if (cs.cbInQue > sizeof(buff)) // buffer overflow ?
                {
                    abort_io(h, queue, context);
                }
                if (!ReadFile(h, buff, cs.cbInQue, &len, &roverlapped))
                {
                    DWORD error = GetLastError();
                    if (error != ERROR_IO_PENDING)
                    {
                        context.notify(ERROR_OCCURED, error);
                        goto exit_thread;
                    }
                    GetOverlappedResult(h, &roverlapped, &len, TRUE); // some condition (but not happened)
                }
#ifdef _DEBUG_TRACE
                buff[len] = 0;
                ATLTRACE(_T("read: %s\n"), buff);
#endif
                for (size_t i = 0; i < len; i++)
                {
                    if (!context.push(buff[i]))
                    {
                        abort_io(h, queue, context);
                    }
                }
            }
        }
        else if (event_count > 1 && dw == WAIT_OBJECT_0 + 1)
        {
            event_count--;
            GetOverlappedResult(h, &soverlapped, &len, FALSE);
#ifdef _DEBUG_TRACE
            ATLTRACE("%s\n", queue.front());
#endif
            delete[] queue.front();
            queue.pop();
        }
    }
exit_thread:
    CancelIo(h);
    CloseHandle(h);
    for (int i = 0; i < COUNT_OF(events); i++) CloseHandle(events[i]);
    return 0;
}
