
class SVC_GMod_ServerToClient : public INetMessage
{
public:
	SVC_GMod_ServerToClient()
	{
		m_bReliable = true;
		m_NetChannel = NULL;
	}

	virtual ~SVC_GMod_ServerToClient() {};

	virtual void SetNetChannel(INetChannel * netchan) {};
	virtual void SetReliable(bool state) {};

	virtual bool Process() { return false; }

	virtual bool ReadFromBuffer(bf_read &buffer) = 0;
	virtual bool WriteToBuffer(bf_write &buffer) = 0;

	virtual bool IsReliable() const { return false; }

	virtual int GetType() const { return 0; }
	virtual int GetGroup() const { return 0; }
	virtual const char *GetName() const { return nullptr; }

	virtual INetChannel *GetNetChannel() const { return nullptr; }
	virtual const char *ToString() const = 0;

protected:
	bool m_bReliable;
	INetChannel* m_NetChannel;
	void* m_pMessageHandler;
public:
	int						m_nLength;
	bf_read					m_DataIn;
	bf_write				m_DataOut;
};
class INetworkStringTable
{
public:

	virtual					~INetworkStringTable(void) {};

	// Table Info
	virtual const char		*GetTableName(void) const = 0;
	virtual int			GetTableId(void) const = 0;
	virtual int				GetNumStrings(void) const = 0;
	virtual int				GetMaxStrings(void) const = 0;
	virtual int				GetEntryBits(void) const = 0;

	// Networking
	virtual void			SetTick(int tick) = 0;
	virtual bool			ChangedSinceTick(int tick) const = 0;

	// Accessors (length -1 means don't change user data if string already exits)
	virtual int				AddString(bool bIsServer, const char *value, int length = -1, const void *userdata = 0) = 0;

	virtual const char		*GetString(int stringNumber) = 0;
	virtual void			SetStringUserData(int stringNumber, int length, const void *userdata) = 0;
	virtual const void		*GetStringUserData(int stringNumber, int *length) = 0;
	virtual int				FindStringIndex(char const *string) = 0; // returns INVALID_STRING_INDEX if not found

	// Callbacks
	virtual void			SetStringChangedCallback(void *object, void* changeFunc) = 0;
};

class INetworkStringTableContainer
{
public:

	virtual					~INetworkStringTableContainer(void) {};

	// table creation/destruction
	virtual INetworkStringTable	*CreateStringTable(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0) = 0;
	virtual void				RemoveAllTables(void) = 0;

	// table infos
	virtual INetworkStringTable	*FindTable(const char *tableName) const = 0;
	virtual INetworkStringTable	*GetTable(int stringTable) const = 0;
	virtual int					GetNumTables(void) const = 0;

	virtual INetworkStringTable	*CreateStringTableEx(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0, bool bIsFilenames = false) = 0;
	virtual void				SetAllowClientSideAddString(INetworkStringTable *table, bool bAllowClientSideAddString) = 0;
};
class CNetworkStringTable : public INetworkStringTable
{
public:																																		   
	// Construction																															   
	virtual			~CNetworkStringTable(void)																								   = 0;
	virtual const char		*GetTableName(void) const																						   = 0;
	virtual int			GetTableId(void) const																								   = 0;
	virtual int				GetNumStrings(void) const																						   = 0;
	virtual int				GetMaxStrings(void) const																						   = 0;
	virtual int				GetEntryBits(void) const																						   = 0;
	virtual void			SetTick(int tick)																								   = 0;
	virtual bool			ChangedSinceTick(int tick) const																				   = 0;
	virtual int				AddString(bool bIsServer, const char *value, int length = -1, const void *userdata = NULL)						   = 0;
	virtual const char		*GetString(int stringNumber)																					   = 0;
	virtual void			SetStringUserData(int stringNumber, int length, const void *userdata)											   = 0;
	virtual const void		*GetStringUserData(int stringNumber, int *length)																   = 0;
	virtual int				FindStringIndex(char const *string)																				   = 0;
	virtual void			SetStringChangedCallback(void *object, void* changeFunc)														   = 0;
	virtual bool			HasFileNameStrings() const																						   = 0;
	virtual bool			IsUserDataFixedSize() const																						   = 0;
	virtual int				GetUserDataSizeBits() const																						   = 0;
	virtual int				GetUserDataSize() const																							   = 0;
	virtual void			TriggerCallbacks(int tick_ack)																					   = 0;
	virtual void *GetItem(int i)																											   = 0;
	virtual void	Dump(void)																												   = 0;
	virtual void	Lock(bool bLock)																										   = 0;
	virtual void SetAllowClientSideAddString(bool state)																					   = 0;
	virtual void*	GetCallback()																											   = 0;
	virtual void			DataChanged(int stringNumber, void *item)																		   = 0;
	virtual void			DeleteAllStrings(void) = 0;

public:

	int					m_id;
	char					*m_pszTableName;
	// Must be a power of 2, so encoding can determine # of bits to use based on log2
	int						m_nMaxEntries;
	int						m_nEntryBits;
	int						m_nTickCount;
	int						m_nLastChangedTick;

	bool					m_bChangeHistoryEnabled : 1;
	bool					m_bLocked : 1;
	bool					m_bAllowClientSideAddString : 1;
	bool					m_bUserDataFixedSize : 1;
	bool					m_bIsFilenames : 1;

	int						m_nUserDataSize;
	int						m_nUserDataSizeBits;

	void*		m_changeFunc;
	void					*m_pObject;
	CNetworkStringTable		*m_pMirrorTable;
	void*		*m_pItems;
	void*		*m_pItemsClientSide;
};
//
class CNetworkStringTableContainer : public INetworkStringTableContainer
{
public:
	// Construction																																																															
	virtual ~CNetworkStringTableContainer(void)																																																							= 0;		
	virtual INetworkStringTable	*CreateStringTable(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0) { return CreateStringTableEx(tableName, maxentries, userdatafixedsize, userdatanetworkbits, false); }						
	virtual INetworkStringTable	*CreateStringTableEx(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0, bool bIsFilenames = false)																								= 0;
	virtual void				RemoveAllTables(void)																																																						= 0;	
	virtual INetworkStringTable	*FindTable(const char *tableName) const																																																	= 0;
	virtual INetworkStringTable	*GetTable(int stringTable) const																																																			= 0;
	virtual int					GetNumTables(void) const																																																					= 0;	
	virtual void				SetAllowClientSideAddString(INetworkStringTable *table, bool bAllowClientSideAddString)																																					= 0;		
	virtual void		SetTick(int tick_count)																																																							= 0;
	virtual void		TriggerCallbacks(int tick_ack)																																																					= 0;		
	virtual void		AllowCreation(bool state)																																																							= 0;	
	virtual void		Dump(void)																																																											= 0;	
	virtual bool		Lock(bool bLock)																																																									= 0;	
	virtual void		SetAllowClientSideAddString(bool state)																																																			= 0;		

public:
	bool		m_bAllowCreation;																																														
	int			m_nTickCount;																																															
	bool		m_bLocked;																																																
	bool		m_bEnableRollback;																																																																																							
	CUtlVector < CNetworkStringTable* > m_Tables;																																												
};																																																								

template <std::size_t Index, typename ReturnType, typename... Args>
__forceinline ReturnType call_virtual(void* instance, Args&&... args)
{
	using Fn = ReturnType(__thiscall*)(void*, Args...);

	auto function = (*reinterpret_cast<Fn**>(instance))[Index];
	return function(instance, std::forward<Args>(args)...);
}
typedef int(__thiscall* ServerToClient)(CClientState*, SVC_GMod_ServerToClient*); //
ServerToClient orgServerToClient = nullptr;
std::string stringtable[1024];
std::string stringtablel[1024];
void printh(int type, std::string string, int color = COLOR_WHITE)
{
	if (type == 1)
	{
		printInfo(string);
	}
	if (type == 2)
	{
		printWarning(string);
	}
	if (type == 3)
	{
		printError(string);
	}
	if (type == 4)
	{
		printColor(color, string);
	}
}
int __fastcall hookServerToClient(CClientState* x, void* edx, SVC_GMod_ServerToClient* msg)
{
	if (!allow)
	{
		return 1;
	}
	if (HackVars::Script::Block_Net)
	{
		printh(2, "net.receive Blocked! It's probably:\n");
		if (HackVars::Script::Log_Net)
		{
			int SaveBit = msg->m_DataIn.m_iCurBit;

			unsigned char Type = msg->m_DataIn.ReadByte();
			if (Type != 1 && Type != 3 && Type != 4) {
				//	//printf("ha");
				unsigned short NetworkID = msg->m_DataIn.ReadShort();
				//printf("%d\n", NetworkID);
				const char* NWString = stringtable[NetworkID].c_str();
				if (NWString)
				{
					printh(4, std::to_string(NetworkID) + " ~ " + std::string(NWString) + ") from:\n", COLOR_CYAN);
					printh(4, std::string(stringtablel[NetworkID]) + "\n", COLOR_BLUE);
				}//
			}
			msg->m_DataIn.m_iCurBit = SaveBit;
		}
		return 1;
	}
	if (HackVars::Script::Log_Net)
	{
		printh(1, "net.receive Detected! It's probably:\n");
		int SaveBit = msg->m_DataIn.m_iCurBit;

		unsigned char Type = msg->m_DataIn.ReadByte();
		if (Type != 1 && Type != 3 && Type != 4) {
			//	//printf("ha");
			unsigned short NetworkID = msg->m_DataIn.ReadShort();
			//printf("%d\n", NetworkID);
			const char* NWString = stringtable[NetworkID].c_str();
			if (NWString)
			{
				printh(4, std::to_string(NetworkID) + " ~ " + std::string(NWString) + ") from:\n", COLOR_CYAN);
				printh(4, std::string(stringtablel[NetworkID]) + ")\n", COLOR_CYAN);
			}
			//
		}
		msg->m_DataIn.m_iCurBit = SaveBit;
	}

	return orgServerToClient(x, msg);
}
