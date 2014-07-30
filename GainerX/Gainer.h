// Gainer.h : ActiveX Control Class
#pragma once
#include "resource.h"
#include <atlctl.h>
#include "GainerX_i.h"
#include "_IGainerEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "WinCE version must construct with STA mode"
#endif

#include "interthread.h"

// CGainer
class ATL_NO_VTABLE CGainer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CGainer, IGainer>,
	public IPersistStreamInitImpl<CGainer>,
	public IOleControlImpl<CGainer>,
	public IOleObjectImpl<CGainer>,
	public IOleInPlaceActiveObjectImpl<CGainer>,
	public IViewObjectExImpl<CGainer>,
	public IOleInPlaceObjectWindowlessImpl<CGainer>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGainer>,
	public CProxy_IGainerEvents<CGainer>,
	public IPersistStorageImpl<CGainer>,
	public ISpecifyPropertyPagesImpl<CGainer>,
	public IPersistPropertyBagImpl<CGainer>,
	public IQuickActivateImpl<CGainer>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CGainer>,
#endif
	public IProvideClassInfo2Impl<&CLSID_Gainer, &__uuidof(_IGainerEvents), &LIBID_GainerXLib>,
#ifdef _WIN32_WCE
	public IObjectSafetyImpl<CGainer, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<CGainer, &CLSID_Gainer>,
	public CComCompositeControl<CGainer>
{
public:


    CGainer()
    {
        m_bWindowOnly = TRUE;
        m_bVisible = FALSE;
        m_iothread = NULL;
        m_iothread_id = 0;
		CalcExtent(m_sizeExtent);
    }

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_GAINER)


BEGIN_COM_MAP(CGainer)
	COM_INTERFACE_ENTRY(IGainer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
#ifdef _WIN32_WCE
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CGainer)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY_TYPE("Enabled", DISPID_ENABLED, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("Valid", DISPID_VALID, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("Visible", DISPID_VISIBLE, CLSID_NULL, VT_BOOL)
	// PROP_ENTRY_TYPE("property name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CGainer)
	CONNECTION_POINT_ENTRY(__uuidof(_IGainerEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CGainer)
    MESSAGE_HANDLER(WM_COM_RESPONSE, ResponseHandler)
    MESSAGE_HANDLER(WM_COM_READRESULT, ResponseTextHandler)
    MESSAGE_HANDLER(WM_COM_REBOOT, RebootHandler)
    CHAIN_MSG_MAP(CComCompositeControl<CGainer>)
END_MSG_MAP()
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
    LRESULT ResponseHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT ResponseTextHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT RebootHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

BEGIN_SINK_MAP(CGainer)
	// check event handler having __stdcall directive.
END_SINK_MAP()

    STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
    {
        if (dispid == DISPID_AMBIENT_BACKCOLOR)
        {
            SetBackgroundColorFromAmbient();
            FireViewChange();
        }
        return IOleControlImpl<CGainer>::OnAmbientPropertyChange(dispid);
    }
// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
    {
        static const IID* arr[] =
        {
            &IID_IGainer,
        };

        for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
        {
            if (InlineIsEqualGUID(*arr[i], riid))
                return S_OK;
        }
        return S_FALSE;
    }

// IPersistPropertyBag
    HRESULT IPersistPropertyBag_Load(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog, const ATL::ATL_PROPMAP_ENTRY* pMap)
    {
        ATLTRACE(_T("PersistPropertyBag_Load\n"));
        HRESULT hr = IPersistPropertyBagImpl<CGainer>::IPersistPropertyBag_Load(pPropBag, pErrorLog, pMap);
        return hr;
    }

// IViewObjectEx
    DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IGainer
    BOOL m_bEnabled;
    void OnEnabledChanged()
    {
        ATLTRACE(_T("OnEnabledChanged\n"));
    }
    BOOL m_bValid;
    void OnValidChanged()
    {
        ATLTRACE(_T("OnValidChanged\n"));
    }
    BOOL m_bVisible;
    void OnVisibleChanged()
    {
        ATLTRACE(_T("OnVisibleChanged\n"));
    }

    enum { IDD = IDD_GAINER };

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
        if (m_iothread)
        {
            DWORD exitcode;
            if (GetExitCodeThread(m_iothread, &exitcode) && exitcode == STILL_ACTIVE)
            {
                PostThreadMessage(m_iothread_id, WM_QUIT, 0, 0);
            }
            m_iothread_id = 0;
            CloseHandle(m_iothread);
            m_iothread = 0;
        }
    }

    HRESULT STDMETHODCALLTYPE put_Visible( 
        /* [in] */ VARIANT_BOOL vbool)
    {
        m_bVisible = (vbool == VARIANT_FALSE) ? false : true;
        return S_OK;
    }
    
    HRESULT STDMETHODCALLTYPE get_Visible( 
        /* [retval][out] */ VARIANT_BOOL *pbool)
    {
        *pbool = (m_bVisible) ? VARIANT_TRUE : VARIANT_FALSE;
        return S_OK;
    }
    
    HRESULT STDMETHODCALLTYPE Open( 
        /* [in] */ BSTR device);
    
    HRESULT STDMETHODCALLTYPE Close( void);

    HRESULT STDMETHODCALLTYPE Wait( 
        /* [in] */ long Timeout);
    
    HRESULT STDMETHODCALLTYPE put_Configuration( 
        /* [in] */ GainerConfiguration mode);
    
    HRESULT STDMETHODCALLTYPE Reboot( void);
    
    HRESULT STDMETHODCALLTYPE put_Verbose( 
        /* [in] */ VARIANT_BOOL Enabled);
    
    HRESULT STDMETHODCALLTYPE ReadVersion( 
        /* [retval][out] */ BSTR *pResult);
    
    HRESULT STDMETHODCALLTYPE put_LED( 
        /* [in] */ VARIANT_BOOL On);
    
    HRESULT STDMETHODCALLTYPE SetPGA( 
        /* [in] */ long Gain,
        /* [in] */ long reference);
    
    HRESULT STDMETHODCALLTYPE WriteAllDigitalOutputs( 
        /* [in] */ SAFEARRAY **NewValue);
    
    HRESULT STDMETHODCALLTYPE ReadAllDigitalInputs( 
        /* [optional][in] */ VARIANT ContinuousMode,
        /* [retval][out] */ SAFEARRAY **ppResult);
    
    HRESULT STDMETHODCALLTYPE WriteDigitalOutput( 
        /* [in] */ long Port,
        /* [in] */ VARIANT_BOOL High);
    
    HRESULT STDMETHODCALLTYPE put_Sensitivity( 
        /* [in] */ long NewValue);
    
    HRESULT STDMETHODCALLTYPE WriteAllAnalogOutputs( 
        /* [in] */ SAFEARRAY **NewValue);
    
    HRESULT STDMETHODCALLTYPE WriteAnalogOuput( 
        /* [in] */ long Port,
        /* [in] */ long Value);
    
    HRESULT STDMETHODCALLTYPE WriteAnalogOuputByRow( 
        /* [in] */ long Row,
        /* [in] */ SAFEARRAY **Value);
    
    HRESULT STDMETHODCALLTYPE ReadAllAnalogInputs( 
        /* [optional][in] */ VARIANT ContinuousMode,
        /* [retval][out] */ SAFEARRAY **ppResult);
    
    HRESULT STDMETHODCALLTYPE ReadAnalogInput( 
        /* [in] */ long Port,
        /* [retval][out] */ long *pResult);
    
    HRESULT STDMETHODCALLTYPE ExitContinousMode( void);
    
    HRESULT STDMETHODCALLTYPE put_AinSamplingMode( 
        /* [in] */ long NewMode);

    HANDLE m_iothread;
    DWORD m_iothread_id;

private:
    bool convert_default(VARIANT& v);
    HRESULT wait_response(BSTR*);
    SAFEARRAY* convert(BSTR);
};

OBJECT_ENTRY_AUTO(__uuidof(Gainer), CGainer)
