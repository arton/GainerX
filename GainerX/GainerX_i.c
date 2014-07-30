

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_GainerXLib,0xF3A76D0B,0xAB61,0x491C,0x96,0x1F,0x26,0x7D,0x38,0xA2,0x02,0x50);


MIDL_DEFINE_GUID(IID, IID_IGainer,0x6831B355,0xEDA7,0x46F8,0xAD,0x85,0x14,0xF9,0x68,0xFE,0x9F,0xF1);


MIDL_DEFINE_GUID(IID, DIID__IGainerEvents,0xF9FE5F60,0x5467,0x4F95,0xAA,0x58,0x4B,0x11,0x2C,0x02,0x4A,0x49);


MIDL_DEFINE_GUID(CLSID, CLSID_Gainer,0xFB4167A2,0x2958,0x4AAA,0x86,0x1D,0x78,0xE6,0x73,0x08,0x99,0x73);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



