#define lua_popa(L,n)  luaL_settop(L, -(n)-1)
class CLuaShared
{
public:
	virtual ~CLuaShared() = 0;
	virtual int Init(char*, char*, void*, void*) = 0;
	virtual int Shutdown(void) = 0;
	virtual int DumpStats(void) = 0;
	virtual GarrysMod::Lua::ILuaBase* CreateLuaInterface(int, bool) = 0;
	virtual int CloseLuaInterface(GarrysMod::Lua::ILuaBase*) = 0;
	virtual GarrysMod::Lua::ILuaBase* GetLuaInterface(int) = 0;
	virtual int LoadFile(std::string, std::string, std::string, bool) = 0;
	virtual int GetCache(std::string) = 0;
	virtual int MountLua(const char*) = 0;
	virtual int MountLuaAdd(const char*, const char*) = 0;
	virtual int UnMountLua(const char*) = 0;
	virtual void SetFileContents() = 0; // does legit nothing
	virtual int SetLuaFindHook(void*/*LuaClientDatatableHook**/) = 0;
	virtual int FindScripts() = 0;
	virtual void* GetStackTraces() = 0;
};
namespace AppelLua
{
	GarrysMod::Lua::ILuaBase* getClientState()
	{
		GarrysMod::Lua::ILuaBase* qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);
		if (qrex == NULL) {
			printErrorS("Client State not initialized \n");
			return NULL;
		}

		return qrex;
	}

	GarrysMod::Lua::ILuaBase* getMenuState()
	{
		GarrysMod::Lua::ILuaBase* qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Menu);
		if (qrex == NULL) {
			printErrorS("Menu State not initialized \n");
			return NULL;
		}

		return qrex;
	}

	void RunFile(const char* file, bool menu = false)
	{
		if (!allow)
			return;
		GarrysMod::Lua::ILuaBase* qrex;

		if (!menu)
			qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);
		else
			qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Menu);

		//DWORD qrex2 = (DWORD)qrex;
		if (!qrex) {
			printError("Failed to get Client Interface. Couldn't run lua script.\n");
			return;
		}

		GarrysMod::Lua::lua_State* pGLuaState = qrex->L;

		if (!pGLuaState) {
			printError("Failed to get lua_State. Couldn't run lua script.\n");
			return;
		}

		if (!luaL_gettop(pGLuaState))
		{
			if (!luaL_loadfile(pGLuaState, file))
			{
				if (!luaL_pcall(pGLuaState, 0, 0, 0))
				{
					return;
				}
			}
		}

		printError("Couldn't run lua script.\n");
	}
	void RunLua(const char* code, bool menu = false)
	{
		if (!allow)
			return;
		GarrysMod::Lua::ILuaBase* qrex;

		if (!menu)
			qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);
		else
			qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Menu);


		//DWORD qrex2 = (DWORD)qrex;
		if (!code) {
			printError("Code is NULL??. Couldn't run lua script.\n");
			return;
		}

		if (!qrex) {
			printError("Failed to get Client Interface. Couldn't run lua script.\n");
			return;
		}

		GarrysMod::Lua::lua_State* pGLuaState = qrex->L;

		if (!pGLuaState) {
			printError("Failed to get lua_State. Couldn't run lua script.\n");
			return;
		}
		int error = pLoadBufferx(pGLuaState, code, strlen(code), "what", 0);

		if (error)
		{
			const char * error = lua_tolstring(pGLuaState, -1, 0);
			char tmperror[5024];
			strcpy(tmperror, error);

			lua_popa(pGLuaState, 1);

			printError(tmperror);
			printf("\n");
			return;
		}
		if (luaL_pcall(pGLuaState, 0, LUA_MULTRET, 0))
		{
			lua_popa(pGLuaState, 1);
			printError("Couldn't run lua script.\n");
			return;
		}
		//!*(DWORD*)(qrex2 + 0x2C) && 
		//if (!luaL_loadstring(pGLuaState, code))
		//{
		//	if (!luaL_pcall(pGLuaState, 0, 0, 0))
		//	{
		//		return;
		//	}
		//}
		//qrex->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		//qrex->GetField(-1, "CompileString");
		//qrex->PushString(code);
		//qrex->PushString("");
		//qrex->PushBool(true);
		//qrex->Call(3, 1);
		//qrex->Push(2);
		//qrex->Call(0, 0);
		//qrex->Pop(2);

		//printError("Couldn't run lua script.\n");
	}
	void RunFileS(const std::string& buff)
	{
		GarrysMod::Lua::ILuaBase* qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);

		if (!qrex) {
			printError("Failed to get Client Interface. Couldn't run lua script.\n");
			return;
		}

		//pLoadBuffer(qrex + 0x4, buff.c_str(), buff.length(), "appel.lua");
	}
	Color get_team_color(int team)
	{
		auto glua = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);

		if (!glua)
			return {};

		glua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		glua->GetField(-1, "team");
		glua->GetField(-1, "GetColor");
		glua->PushNumber(team);
		glua->Call(1, 1);

		glua->PushString("r");
		glua->GetTable(-2);
		auto r = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("g");
		glua->GetTable(-2);
		auto g = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("b");
		glua->GetTable(-2);
		auto b = glua->GetNumber(-1);
		glua->Pop(4);

		return Color(r, g, b, 255);
	}
}