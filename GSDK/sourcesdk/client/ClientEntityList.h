class IClientNetworkable;
class BaseEntity;
class CBaseHandle;
class IClientEntity;
class ClientEntityList
{
public:
	virtual ~ClientEntityList();
	virtual IClientNetworkable*	GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle* hEnt) = 0;
	virtual IClientEntity*		GetClientEntity(int entnum) = 0;
	virtual IClientEntity*		GetClientEntityFromHandle(CBaseHandle* hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void) = 0;
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};
/*
virtual void				OnAddEntity(void*, CBaseHandle) = 0;
virtual void				OnRemoveEntity(void*, CBaseHandle) = 0;
virtual ~ClientEntityList();
virtual IClientNetworkable*	GetClientNetworkable(int entnum) = 0;
virtual IClientEntity*		GetClientEntity(int entnum) = 0;
virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
virtual void*				GetClientUnknownFromHandle(uintptr_t hEnt) = 0;
virtual IClientNetworkable* GetClientNetworkableFromHandle(uintptr_t hEnt) = 0;
virtual IClientEntity*		GetClientEntityFromHandle(uintptr_t hEnt) = 0;
virtual int					GetHighestEntityIndex(void) = 0;
virtual void				SetMaxEntities(int maxents) = 0;
virtual int					GetMaxEntities() = 0;
*/