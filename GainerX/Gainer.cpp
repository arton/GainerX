
#include "stdafx.h"
#include "Gainer.h"

// CGainer
#define CHECK_PORT(Port)     if (Port < 0 || Port > 8) return Error(IDS_E_PARAM)

LRESULT CGainer::ResponseHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = true;
    switch (wParam)
    {
    case ERROR_OCCURED:
        FinalRelease();
        Fire_Error(lParam);
        break;
    case BUTTON_PRESSED:
        Fire_ButtonPressed();
        break;
    case BUTTON_RELEASED:
        Fire_ButtonReleased();
        break;
    }
    return TRUE;
}

LRESULT CGainer::RebootHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = true;
    Fire_Rebooted();
    return TRUE;
}

LRESULT CGainer::ResponseTextHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = true;
    if (lParam)
    {
        BSTR bstr = reinterpret_cast<BSTR>(lParam);
        SAFEARRAY* p = convert(bstr);
        if (p)
        {
            if (*bstr == L'i')
                this->Fire_AnalogInputs(p);
            else if (*bstr == L'r')
                this->Fire_DigitalInputs(p);
            SafeArrayDestroy(p);
        }
        SysFreeString(bstr);
    }
    return TRUE;
}

const UINT MAX_WAIT = 5000;

HRESULT CGainer::wait_response(BSTR* p)
{
    MSG msg;
    UINT_PTR timer = ::SetTimer(m_hWndCD, 0, MAX_WAIT, NULL);
    HRESULT hr = E_FAIL;
    for (bool exit_loop = false; !exit_loop;)
    {
        int ret = GetMessage(&msg, m_hWndCD, 0, 0);  // m_hWndCD may be null
        if (!ret) break;
        if (ret < 0) 
        {
            hr = Error(IDS_E_BADWINDOW);
            break;
        }
        switch (msg.message)
        {
        case WM_TIMER:
            hr = Error(IDS_E_TIMEOUT);
            goto exit_loop;
        case WM_COM_READRESULT:
            if (msg.lParam)
            {
                *p = reinterpret_cast<BSTR>(msg.lParam);
                hr = S_OK;
            }
            else
            {
                *p = NULL;
            }
            goto exit_loop;
        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
exit_loop:
    ::KillTimer(m_hWndCD, timer);

    return hr;
}

inline int xconv(OLECHAR c)
{
    if (c >= L'0' && c <= L'9')
        return c - L'0';
    else if (c >= L'A' && c <= L'F')
        return c - L'A' + 10;
    return 0;
}

SAFEARRAY* CGainer::convert(BSTR bstr)
{
    if (!SysStringLen(bstr) || !wcschr(L"IiRr", *bstr)) {
        return NULL;
    }
    bool digital = *bstr == 'R' || *bstr == 'r';
    int len = (digital) ? (SysStringLen(bstr) - 1) : (SysStringLen(bstr) - 1) / 2;
    SAFEARRAYBOUND rgsabound[1];
    rgsabound[0].cElements = len;
    rgsabound[0].lLbound = 0L;
#ifdef USE_VARIANT
    SAFEARRAY* pNewAry = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
#else
    SAFEARRAY* pNewAry = SafeArrayCreate(VT_UI1, 1, rgsabound);
#endif
    SafeArrayLock(pNewAry);
#ifdef USE_VARIANT
    VARIANT* ps = (VARIANT*)pNewAry->pvData;
#else
    LPBYTE ps = (LPBYTE)pNewAry->pvData;
#endif
    for (int i = 0; i < len; i++, ps++)
    {
#ifdef USE_VARIANT
        VariantInit(ps);
        if (digital)
        {
            ps->vt = VT_UI1;
            ps->bVal = (byte)xconv(*(bstr + i + 1));
        }
        else
        {
            ps->vt = VT_UI1;
            ps->bVal = (byte)((xconv(*(bstr + i * 2 + 1)) << 4) | xconv(*(bstr + i * 2 + 2)));
        }
#else
        if (digital)
        {
            *ps = (byte)xconv(*(bstr + i + 1));
        }
        else
        {
            *ps = (byte)((xconv(*(bstr + i * 2 + 1)) << 4) | xconv(*(bstr + i * 2 + 2)));
        }
#endif
    }
    SafeArrayUnlock(pNewAry);
    return pNewAry;
}

HRESULT STDMETHODCALLTYPE CGainer::Open( 
            /* [in] */ BSTR device)
{
    if (SysStringLen(device) == 0 || SysStringLen(device) > 5 || wcsncmp(L"COM", device, 3)) return Error(IDS_E_BADNAME);
        
    if (!m_iothread)
    {
        if (!m_hWndCD)
        {
            HWND hparent = NULL;
            RECT rc = { 0, 0, 0, 0, };
            if (m_spInPlaceSite)
            {
                m_spInPlaceSite->GetWindow(&hparent);
            }
            CreateControlWindow(hparent, rc);
#if defined(ACTIVEX_CONTROL_ONLY)
            if (!m_hWndCD)
            {
                return Error(IDS_E_BADWINDOW);
            }
#endif
        }
        ThreadParam* t = new ThreadParam(device, m_hWndCD);
        m_iothread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, start_iothread, t, 0, reinterpret_cast<unsigned*>(&m_iothread_id)));
    }
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::Close( void)
{
    if (m_iothread)
    {
        notify_message(m_iothread_id, WM_COM_CLOSE);
        FinalRelease();
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CGainer::Wait( 
            /* [in] */ long Timeout)
{
    MSG msg;
    for (;;)
    {
        UINT_PTR timer = ::SetTimer(NULL, 0, Timeout, NULL);
        int ret = GetMessage(&msg, m_hWndCD, 0, 0);  // m_hWndCD may be null
        ::KillTimer(m_hWndCD, timer);
        if (!ret) break;
        if (ret < 0) return Error(IDS_E_BADWINDOW);
        switch (msg.message)
        {
        case WM_TIMER:
            return S_OK;
        case WM_COM_READRESULT:
        case WM_COM_REBOOT:
        case WM_COM_RESPONSE:
            if (!m_hWndCD)
            {
                BOOL bHandled;
                switch (msg.message)
                {
                case WM_COM_READRESULT:
                    ResponseTextHandler(msg.message, msg.wParam, msg.lParam, bHandled);
                    break;
                case WM_COM_REBOOT:
                    RebootHandler(msg.message, msg.wParam, msg.lParam, bHandled);
                    break;
                default:
                    ResponseHandler(msg.message, msg.wParam, msg.lParam, bHandled);
                    break;   
                }
                continue;
            }
            // fall through
        default:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::put_Configuration( 
            /* [in] */ GainerConfiguration mode)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (mode < INIT_MODE || mode > CAPACITIVE_SENSING_MODE) return Error(IDS_E_PARAM);
    char smode[32];
    sprintf(smode, "KONFIGURATION_%d*", mode);
    notify_message(m_iothread_id, WM_COM_IO, smode);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::Reboot( void)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    notify_message(m_iothread_id, WM_COM_IO, "Q*");
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::put_Verbose( 
            /* [in] */ VARIANT_BOOL Enabled)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    char vmode[16];
    sprintf(vmode, "V%d*", (Enabled) ? 1 : 0);
    notify_message(m_iothread_id, WM_COM_IO, vmode);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::ReadVersion( 
            /* [retval][out] */ BSTR *pResult)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (!pResult) return E_POINTER;
    notify_message(m_iothread_id, WM_COM_IO, "?*");
    return wait_response(pResult);
}
        
HRESULT STDMETHODCALLTYPE CGainer::put_LED( 
            /* [in] */ VARIANT_BOOL On)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    char cled[16];
    sprintf(cled, "%c*", (On) ? 'h' : 'l');
    notify_message(m_iothread_id, WM_COM_IO, cled);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::SetPGA( 
            /* [in] */ long Gain,
            /* [in] */ long reference)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);

    return E_NOTIMPL;
}
        
HRESULT STDMETHODCALLTYPE CGainer::WriteAllDigitalOutputs( 
            /* [in] */ SAFEARRAY **NewValue)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (!NewValue || !*NewValue) return E_POINTER;
    SAFEARRAY* p = *NewValue;
    SafeArrayLock(p);
    LPBYTE pdata = reinterpret_cast<LPBYTE>(p->pvData);
    char* dst = reinterpret_cast<char*>(_alloca(p->rgsabound[0].cElements + 8));
    char* msg = dst;
    *dst++ = 'D';
    for (size_t i = p->rgsabound[0].lLbound; i < p->rgsabound[0].cElements; i++)
    {
        dst += sprintf(dst, "%d", *(pdata + i - p->rgsabound[0].lLbound));
    }
    *dst++ = '*';
    *dst = '\0';
    SafeArrayUnlock(p);
    notify_message(m_iothread_id, WM_COM_IO, msg);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::ReadAllDigitalInputs( 
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY * *ppResult)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);

    bool continuous = convert_default(ContinuousMode);
    notify_message(m_iothread_id, WM_COM_IO, (continuous) ? "r*" : "R*");
    if (continuous)
        return S_OK;
    BSTR bstr;
    HRESULT hr = wait_response(&bstr);
    if (hr == S_OK)
    {
        *ppResult = convert(bstr);
        SysFreeString(bstr);
    }
    return hr;
}
        
HRESULT STDMETHODCALLTYPE CGainer::WriteDigitalOutput( 
            /* [in] */ long Port,
            /* [in] */ VARIANT_BOOL High)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    CHECK_PORT(Port);
    char msg[8];
    sprintf(msg, "%c%d*", (High) ? 'H' : 'L', Port);
    notify_message(m_iothread_id, WM_COM_IO, msg);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::put_Sensitivity( 
            /* [in] */ long NewValue)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);

    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::WriteAllAnalogOutputs( 
            /* [in] */ SAFEARRAY **NewValue)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (!NewValue || !*NewValue) return E_POINTER;
    SAFEARRAY* p = *NewValue;
    SafeArrayLock(p);
    LPBYTE pdata = reinterpret_cast<LPBYTE>(p->pvData);
    char* dst = reinterpret_cast<char*>(_alloca(2 * p->rgsabound[0].cElements + 8));
    char* msg = dst;
    *dst++ = 'A';
    for (size_t i = p->rgsabound[0].lLbound; i < p->rgsabound[0].cElements; i++)
    {
        dst += sprintf(dst, "%02X", *(pdata + i - p->rgsabound[0].lLbound));
    }
    *dst++ = '*';
    *dst = '\0';
    SafeArrayUnlock(p);
    notify_message(m_iothread_id, WM_COM_IO, msg);

    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::WriteAnalogOuput( 
            /* [in] */ long Port,
            /* [in] */ long Value)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    CHECK_PORT(Port);
    char msg[8];
    sprintf(msg, "a%d%02X*", Port, Value);
    notify_message(m_iothread_id, WM_COM_IO, msg);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::WriteAnalogOuputByRow( 
            /* [in] */ long Row,
            /* [in] */ SAFEARRAY **Value)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);

    return E_NOTIMPL;
}
        
HRESULT STDMETHODCALLTYPE CGainer::ReadAllAnalogInputs( 
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY **ppResult)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);

    bool continuous = convert_default(ContinuousMode);
    notify_message(m_iothread_id, WM_COM_IO, (continuous) ? "i*" : "I*");
    if (continuous)
        return S_OK;
    BSTR bstr;
    HRESULT hr = wait_response(&bstr);
    if (hr == S_OK)
    {
        *ppResult = convert(bstr);
        SysFreeString(bstr);
    }
    return hr;
}
        
HRESULT STDMETHODCALLTYPE CGainer::ReadAnalogInput( 
            /* [in] */ long Port,
            /* [retval][out] */ long *pResult)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    CHECK_PORT(Port);
    char msg[8];
    printf(msg, "S%d*", Port);
    notify_message(m_iothread_id, WM_COM_IO, msg);
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::ExitContinousMode( void)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    notify_message(m_iothread_id, WM_COM_IO, "E*");
    return S_OK;
}
        
HRESULT STDMETHODCALLTYPE CGainer::put_AinSamplingMode( 
            /* [in] */ long NewMode)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (NewMode < 0 || NewMode > 1) return Error(IDS_E_PARAM);

    char smode[16];
    sprintf(smode, "M%d*", NewMode);
    notify_message(m_iothread_id, WM_COM_IO, smode);
    return S_OK;
}

bool CGainer::convert_default(VARIANT &v)
{
    if (v.vt == (VT_BYREF | VT_VARIANT)) return convert_default(*v.pvarVal);
    if (v.vt == VT_BOOL && v.boolVal) return true;
    return v.vt == (VT_BOOL | VT_BYREF) && *v.pboolVal;
}
