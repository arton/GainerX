// dllmain.h : 

class CGainerXModule : public CAtlDllModuleT< CGainerXModule >
{
public :
	DECLARE_LIBID(LIBID_GainerXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GAINERX, "{9C08F949-B94C-4D11-ABA1-664C95EA4DF6}")
};

extern class CGainerXModule _AtlModule;
