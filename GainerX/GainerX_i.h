

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Sat Mar 28 04:35:59 2009
 */
/* Compiler settings for .\GainerX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __GainerX_i_h__
#define __GainerX_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGainer_FWD_DEFINED__
#define __IGainer_FWD_DEFINED__
typedef interface IGainer IGainer;
#endif 	/* __IGainer_FWD_DEFINED__ */


#ifndef ___IGainerEvents_FWD_DEFINED__
#define ___IGainerEvents_FWD_DEFINED__
typedef interface _IGainerEvents _IGainerEvents;
#endif 	/* ___IGainerEvents_FWD_DEFINED__ */


#ifndef __Gainer_FWD_DEFINED__
#define __Gainer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Gainer Gainer;
#else
typedef struct Gainer Gainer;
#endif /* __cplusplus */

#endif 	/* __Gainer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GainerX_0000_0000 */
/* [local] */ 


enum GainerCtlDispids
    {	DISPID_VISIBLE	= 10,
	DISPID_OPEN	= 20,
	DISPID_CLOSE	= ( DISPID_OPEN + 1 ) ,
	DISPID_WAIT	= ( DISPID_CLOSE + 1 ) ,
	DISPID_CONFIGURATION	= ( DISPID_WAIT + 1 ) ,
	DISPID_SET_ALLDIGITALOUTPUTS	= ( DISPID_CONFIGURATION + 1 ) ,
	DISPID_SET_SPECIDIFEDDIGITALOUTPUT	= ( DISPID_SET_ALLDIGITALOUTPUTS + 1 ) ,
	DISPID_GET_ALLDIGITALINPUTS	= ( DISPID_SET_SPECIDIFEDDIGITALOUTPUT + 1 ) ,
	DISPID_EXIT_CONTINOUS_MODE	= ( DISPID_GET_ALLDIGITALINPUTS + 1 ) ,
	DISPID_SET_SENSITIVITY	= ( DISPID_EXIT_CONTINOUS_MODE + 1 ) ,
	DISPID_SET_ALLANALOGOUTPUTS	= ( DISPID_SET_SENSITIVITY + 1 ) ,
	DISPID_SET_SPECIFIEDANALOGOUTPUT	= ( DISPID_SET_ALLANALOGOUTPUTS + 1 ) ,
	DISPID_SET_SPECIFIEDANALOGOUTPUT_BY_ROW	= ( DISPID_SET_SPECIFIEDANALOGOUTPUT + 1 ) ,
	DISPID_GET_ALLANALOGINPUTS	= ( DISPID_SET_SPECIFIEDANALOGOUTPUT_BY_ROW + 1 ) ,
	DISPID_GET_SPECIFIEDANALOGINPUT	= ( DISPID_GET_ALLANALOGINPUTS + 1 ) ,
	DISPID_SET_AIN_SAMPLINGMODE	= ( DISPID_GET_SPECIFIEDANALOGINPUT + 1 ) ,
	DISPID_LED	= ( DISPID_SET_AIN_SAMPLINGMODE + 1 ) ,
	DISPID_PGA	= ( DISPID_LED + 1 ) ,
	DISPID_REBOOT	= ( DISPID_PGA + 1 ) ,
	DISPID_VERBOSE	= ( DISPID_REBOOT + 1 ) ,
	DISPID_VERSION	= ( DISPID_VERBOSE + 1 ) 
    } ;


extern RPC_IF_HANDLE __MIDL_itf_GainerX_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GainerX_0000_0000_v0_0_s_ifspec;


#ifndef __GainerXLib_LIBRARY_DEFINED__
#define __GainerXLib_LIBRARY_DEFINED__

/* library GainerXLib */
/* [helpstring][version][uuid] */ 

typedef /* [helpstring] */ 
enum _ConfigMode
    {	INIT_MODE	= 0,
	DEFAULT_MODE	= 1,
	MODE_2	= 2,
	MODE_3	= 3,
	MODE_4	= 4,
	DIN_MODE	= 5,
	DOUT_MODE	= 6,
	MATRIX_LED_MODE	= 7,
	CAPACITIVE_SENSING_MODE	= 8
    } 	GainerConfiguration;


EXTERN_C const IID LIBID_GainerXLib;

#ifndef __IGainer_INTERFACE_DEFINED__
#define __IGainer_INTERFACE_DEFINED__

/* interface IGainer */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6831B355-EDA7-46F8-AD85-14F968FE9FF1")
    IGainer : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Valid( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Valid( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR device) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Wait( 
            /* [in] */ long Timeout) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Configuration( 
            /* [in] */ GainerConfiguration mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reboot( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Verbose( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadVersion( 
            /* [retval][out] */ BSTR *pResult) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LED( 
            /* [in] */ VARIANT_BOOL On) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPGA( 
            /* [in] */ long Gain,
            /* [in] */ long reference) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteAllDigitalOutputs( 
            /* [in] */ SAFEARRAY * *NewValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAllDigitalInputs( 
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY * *ppResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteDigitalOutput( 
            /* [in] */ long Port,
            /* [in] */ VARIANT_BOOL High) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Sensitivity( 
            /* [in] */ long NewValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteAllAnalogOutputs( 
            /* [in] */ SAFEARRAY * *NewValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteAnalogOuput( 
            /* [in] */ long Port,
            /* [in] */ long Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteAnalogOuputByRow( 
            /* [in] */ long Row,
            /* [in] */ SAFEARRAY * *Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAllAnalogInputs( 
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY * *ppResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAnalogInput( 
            /* [in] */ long Port,
            /* [retval][out] */ long *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExitContinousMode( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AinSamplingMode( 
            /* [in] */ long NewMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGainer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGainer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGainer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGainer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGainer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGainer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IGainer * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IGainer * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Valid )( 
            IGainer * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Valid )( 
            IGainer * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IGainer * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IGainer * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IGainer * This,
            /* [in] */ BSTR device);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IGainer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Wait )( 
            IGainer * This,
            /* [in] */ long Timeout);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Configuration )( 
            IGainer * This,
            /* [in] */ GainerConfiguration mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reboot )( 
            IGainer * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Verbose )( 
            IGainer * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadVersion )( 
            IGainer * This,
            /* [retval][out] */ BSTR *pResult);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LED )( 
            IGainer * This,
            /* [in] */ VARIANT_BOOL On);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPGA )( 
            IGainer * This,
            /* [in] */ long Gain,
            /* [in] */ long reference);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteAllDigitalOutputs )( 
            IGainer * This,
            /* [in] */ SAFEARRAY * *NewValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAllDigitalInputs )( 
            IGainer * This,
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY * *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteDigitalOutput )( 
            IGainer * This,
            /* [in] */ long Port,
            /* [in] */ VARIANT_BOOL High);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sensitivity )( 
            IGainer * This,
            /* [in] */ long NewValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteAllAnalogOutputs )( 
            IGainer * This,
            /* [in] */ SAFEARRAY * *NewValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteAnalogOuput )( 
            IGainer * This,
            /* [in] */ long Port,
            /* [in] */ long Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteAnalogOuputByRow )( 
            IGainer * This,
            /* [in] */ long Row,
            /* [in] */ SAFEARRAY * *Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAllAnalogInputs )( 
            IGainer * This,
            /* [optional][in] */ VARIANT ContinuousMode,
            /* [retval][out] */ SAFEARRAY * *ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAnalogInput )( 
            IGainer * This,
            /* [in] */ long Port,
            /* [retval][out] */ long *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExitContinousMode )( 
            IGainer * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AinSamplingMode )( 
            IGainer * This,
            /* [in] */ long NewMode);
        
        END_INTERFACE
    } IGainerVtbl;

    interface IGainer
    {
        CONST_VTBL struct IGainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGainer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGainer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGainer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGainer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGainer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGainer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGainer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGainer_put_Enabled(This,vbool)	\
    ( (This)->lpVtbl -> put_Enabled(This,vbool) ) 

#define IGainer_get_Enabled(This,pbool)	\
    ( (This)->lpVtbl -> get_Enabled(This,pbool) ) 

#define IGainer_put_Valid(This,vbool)	\
    ( (This)->lpVtbl -> put_Valid(This,vbool) ) 

#define IGainer_get_Valid(This,pbool)	\
    ( (This)->lpVtbl -> get_Valid(This,pbool) ) 

#define IGainer_put_Visible(This,vbool)	\
    ( (This)->lpVtbl -> put_Visible(This,vbool) ) 

#define IGainer_get_Visible(This,pbool)	\
    ( (This)->lpVtbl -> get_Visible(This,pbool) ) 

#define IGainer_Open(This,device)	\
    ( (This)->lpVtbl -> Open(This,device) ) 

#define IGainer_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IGainer_Wait(This,Timeout)	\
    ( (This)->lpVtbl -> Wait(This,Timeout) ) 

#define IGainer_put_Configuration(This,mode)	\
    ( (This)->lpVtbl -> put_Configuration(This,mode) ) 

#define IGainer_Reboot(This)	\
    ( (This)->lpVtbl -> Reboot(This) ) 

#define IGainer_put_Verbose(This,Enabled)	\
    ( (This)->lpVtbl -> put_Verbose(This,Enabled) ) 

#define IGainer_ReadVersion(This,pResult)	\
    ( (This)->lpVtbl -> ReadVersion(This,pResult) ) 

#define IGainer_put_LED(This,On)	\
    ( (This)->lpVtbl -> put_LED(This,On) ) 

#define IGainer_SetPGA(This,Gain,reference)	\
    ( (This)->lpVtbl -> SetPGA(This,Gain,reference) ) 

#define IGainer_WriteAllDigitalOutputs(This,NewValue)	\
    ( (This)->lpVtbl -> WriteAllDigitalOutputs(This,NewValue) ) 

#define IGainer_ReadAllDigitalInputs(This,ContinuousMode,ppResult)	\
    ( (This)->lpVtbl -> ReadAllDigitalInputs(This,ContinuousMode,ppResult) ) 

#define IGainer_WriteDigitalOutput(This,Port,High)	\
    ( (This)->lpVtbl -> WriteDigitalOutput(This,Port,High) ) 

#define IGainer_put_Sensitivity(This,NewValue)	\
    ( (This)->lpVtbl -> put_Sensitivity(This,NewValue) ) 

#define IGainer_WriteAllAnalogOutputs(This,NewValue)	\
    ( (This)->lpVtbl -> WriteAllAnalogOutputs(This,NewValue) ) 

#define IGainer_WriteAnalogOuput(This,Port,Value)	\
    ( (This)->lpVtbl -> WriteAnalogOuput(This,Port,Value) ) 

#define IGainer_WriteAnalogOuputByRow(This,Row,Value)	\
    ( (This)->lpVtbl -> WriteAnalogOuputByRow(This,Row,Value) ) 

#define IGainer_ReadAllAnalogInputs(This,ContinuousMode,ppResult)	\
    ( (This)->lpVtbl -> ReadAllAnalogInputs(This,ContinuousMode,ppResult) ) 

#define IGainer_ReadAnalogInput(This,Port,pResult)	\
    ( (This)->lpVtbl -> ReadAnalogInput(This,Port,pResult) ) 

#define IGainer_ExitContinousMode(This)	\
    ( (This)->lpVtbl -> ExitContinousMode(This) ) 

#define IGainer_put_AinSamplingMode(This,NewMode)	\
    ( (This)->lpVtbl -> put_AinSamplingMode(This,NewMode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGainer_INTERFACE_DEFINED__ */


#ifndef ___IGainerEvents_DISPINTERFACE_DEFINED__
#define ___IGainerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGainerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGainerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F9FE5F60-5467-4F95-AA58-4B112C024A49")
    _IGainerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGainerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IGainerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IGainerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IGainerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IGainerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IGainerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IGainerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IGainerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IGainerEventsVtbl;

    interface _IGainerEvents
    {
        CONST_VTBL struct _IGainerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGainerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IGainerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IGainerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IGainerEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IGainerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IGainerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IGainerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGainerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Gainer;

#ifdef __cplusplus

class DECLSPEC_UUID("FB4167A2-2958-4AAA-861D-78E673089973")
Gainer;
#endif
#endif /* __GainerXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


