#if !defined(_GAINERX_INTERTHREAD_H)
#define _GAINERX_INTERTHREAD_H

extern unsigned __stdcall start_iothread(void*);

enum InterfaceMessage {
    WM_COM_RESPONSE = WM_APP,	// wParam: command, lParam: NULL
    WM_COM_READRESULT,		// wParam: NULL, lParam: BSTR
    WM_COM_REBOOT,              // wParam: NULL, lParam: NULL
    WM_COM_CLOSE,		// wParam: NULL, lParam: NULL
    WM_COM_IO,			// wParam: NULL, lParam: ReqString
};

enum EventType {
    ERROR_OCCURED,
    BUTTON_PRESSED,
    BUTTON_RELEASED,
};

#pragma warning(disable: 4996)
inline void notify_message(DWORD id, DWORD wm, char* msg = NULL)
{
    char* pm(NULL);
    if (msg)
    {
        size_t len = strlen(msg);
        pm = strcpy(new char[len + 1], msg);
    }
    PostThreadMessage(id, wm, 0, reinterpret_cast<LPARAM>(pm));
}

struct ThreadParam
{
    ThreadParam(BSTR name, HWND wnd = NULL) 
    {
        _ASSERT(SysStringLen(name) < COUNT_OF(devicename));

        wcscpy_s(devicename, name);
        hWnd = wnd;
        threadId = GetCurrentThreadId();
    }

    wchar_t devicename[8];
    HWND hWnd;
    DWORD threadId;
};


#endif
