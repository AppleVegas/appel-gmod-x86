#ifndef GARRYSMOD_LUA_LUABASE_H
#define GARRYSMOD_LUA_LUABASE_H

#define LUA_MULTRET -1
#include <stddef.h>
#include <Windows.h>




namespace GarrysMod
{
	namespace Lua
	{
		struct lua_State;

		typedef int(*CFunc) (lua_State *L);
		typedef int(*_luaL_loadbufferx)(lua_State* state, const char *buff, size_t sz, const char* name, void* mode);
		typedef int(*_luaL_loadbuffer)(lua_State *state, const char *buff, size_t sz, const char* name);

		//
		// Access to raw Lua function calls
		//
		class ILuaObject;
		class ILuaInterface
		{
		public:
			virtual int                Top(void) = 0;                                                                            //0000
			virtual void            Push(int iStackPos) = 0;                                                                    //0004
			virtual void            Pop(int iAmt = 1) = 0;                                                                    //0008
			virtual void            GetTable(int iStackPos) = 0;                                                                //000C
			virtual void            GetField(int iStackPos, const char* strName) = 0;                                            //0010
			virtual void            SetField(int iStackPos, const char* strName) = 0;                                            //0014
			virtual void            CreateTable() = 0;                                                                            //0018
			virtual void            SetTable(int i) = 0;                                                                        //001C
			virtual void            SetMetaTable(int i) = 0;                                                                    //0020
			virtual bool            GetMetaTable(int i) = 0;                                                                    //0024
			virtual void            Call(int iArgs, int iResults) = 0;
			virtual int                PCall(int iArgs, int iResults, int iErrorFunc) = 0;
			virtual int                Equal(int iA, int iB) = 0;
			virtual int                RawEqual(int iA, int iB) = 0;
			virtual void            Insert(int iStackPos) = 0;
			virtual void            Remove(int iStackPos) = 0;
			virtual int                Next(int iStackPos) = 0;
			virtual void*            NewUserdata(unsigned int iSize) = 0;
			virtual void            ThrowError(const char* strError) = 0;
			virtual void            CheckType(int iStackPos, int iType) = 0;
			virtual void            ArgError(int iArgNum, const char* strMessage) = 0;
			virtual void*           RawGet(int iStackPos) = 0;
			virtual void            RawSet(int iStackPos) = 0;
			virtual const char*        GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
			virtual double            GetNumber(int iStackPos = -1) = 0;
			virtual bool            GetBool(int iStackPos = -1) = 0;
			virtual CFunc   GetCFunction(int iStackPos = -1) = 0;
			virtual void*            GetUserdata(int iStackPos = -1) = 0;
			virtual void            PushNil() = 0;
			virtual void            PushString(const char* val, unsigned int iLen = 0) = 0;
			virtual void            PushNumber(double val) = 0;
			virtual void            PushBool(bool val) = 0;
			virtual void            PushCFunction(CFunc val) = 0;
			virtual void            PushCClosure(CFunc val, int iVars) = 0;
			virtual void            PushUserdata(void*) = 0;
			virtual int                ReferenceCreate() = 0;
			virtual void            ReferenceFree(int i) = 0;
			virtual void            ReferencePush(int i) = 0;
			virtual void            PushSpecial(int iType) = 0;
			virtual bool            IsType(int iStackPos, int iType) = 0;
			virtual int                GetType(int iStackPos) = 0;
			virtual const char*        GetTypeName(int iType) = 0;
			virtual void            CreateMetaTableType(const char* strName, int iType) = 0;
			virtual const char*        CheckString(int iStackPos = -1) = 0;
			virtual double            CheckNumber(int iStackPos = -1) = 0;
			virtual size_t            ObjLen(int index) = 0;

			// New
			virtual void            AddThreadedCall(void* tc) = 0;
			virtual bool            Init(void* pCallBack, bool bLoadJit) = 0;
			virtual void            Shutdown(void) = 0;
			virtual void*            Cycle(void) = 0;
			virtual lua_State*        GetLuaState() = 0;
			virtual ILuaObject*        Global() = 0;
			virtual ILuaObject*        GetObject(int index) = 0;
			virtual void            _nullstub1(int) = 0;
			virtual void            _nullstub2(int) = 0;
			virtual void            PushLuaObject(ILuaObject *obj) = 0;
			virtual void            PushLuaFunction(CFunc func) = 0;
			virtual void            LuaError(const char *err, int index) = 0;
			virtual void            TypeError(const char *name, int index) = 0;
			virtual void            CallInternal(int args, int rets) = 0;
			virtual void            CallInternalNoReturns(int args) = 0;
			virtual bool            CallInternalGetBool(int args) = 0;
			virtual const char*        CallInternalGetString(int args) = 0;
			virtual bool            CallInternalGet(int args, ILuaObject *obj) = 0;
			virtual void            _nullstub3(ILuaObject *, void *) = 0;
			virtual void            NewGlobalTable(const char *name) = 0;
			virtual ILuaObject*        NewTemporaryObject() = 0;
			virtual bool            isUserData(int index) = 0;
			virtual ILuaObject*        GetMetaTableObject(const char *name, int type) = 0;
			virtual ILuaObject*        GetMetaTableObject(int index) = 0;
			virtual ILuaObject*        GetReturn(int index) = 0;
			virtual bool            IsServer() = 0;
			virtual bool            IsClient() = 0;
			virtual bool            IsDedicatedServer() = 0;
			virtual void            DestroyObject(ILuaObject *obj) = 0;
			virtual ILuaObject*        CreateObject() = 0;
			virtual void            SetMember(ILuaObject *table, ILuaObject *key, ILuaObject *value) = 0;
			virtual void            GetNewTable() = 0;
			virtual void            SetMember(ILuaObject *table, float key) = 0;
			virtual void            SetMember(ILuaObject *table, float key, ILuaObject *value) = 0;
			virtual void            SetMember(ILuaObject *table, const char *key) = 0;
			virtual void            SetMember(ILuaObject *table, const char *key, ILuaObject *value) = 0;
			virtual void            SetIsServer(bool isServer) = 0;
			virtual void            PushLong(long num) = 0;
			virtual int                GetFlags(int index) = 0;
			virtual bool            FindOnObjectsMetaTable(int objIndex, int keyIndex) = 0;
			virtual bool            FindObjectOnTable(int tableIndex, int keyIndex) = 0;
			virtual void            SetMemberFast(ILuaObject *table, int keyIndex, int valueIndex) = 0;
			virtual bool            RunString(const char *filename, const char *path, const char *stringToRun, bool run, bool showErrors) = 0;
			virtual bool            IsEqual(ILuaObject *objA, ILuaObject *objB) = 0;
			virtual void            Error(const char *err) = 0;
			virtual const char*        GetStringOrError(int index) = 0;
			virtual bool            RunLuaModule(const char *name) = 0;
			virtual bool            FindAndRunScript(const char *filename, bool run, bool showErrors, const char *) = 0;
			virtual void            SetPathID(const char *pathID) = 0;
			virtual const char*        GetPathID() = 0;
			virtual void            ErrorNoHalt(const char *fmt, ...) = 0;
			virtual void            Msg(const char *fmt, ...) = 0;
			virtual void            PushPath(const char *path) = 0;
			virtual void            PopPath() = 0;
			virtual const char*        GetPath() = 0;
			virtual int                GetColor(int index) = 0;
			virtual void            PushColor(int r, int g, int b, int a) = 0;
			virtual int                GetStack(int level, void *dbg) = 0;
			virtual int                GetInfo(const char *what, void *dbg) = 0;
			virtual const char*        GetLocal(void *dbg, int n) = 0;
			virtual const char*        GetUpvalue(int funcIndex, int n) = 0;
			virtual void*           RunStringEx(const char *filename, const char *path, const char *stringToRun, bool run, bool showErrors, bool) = 0;
			virtual void            _nullstub4(const char *, int) = 0;
			virtual size_t            GetDataString(int index, const char **str) = 0;
			virtual void            ErrorFromLua(const char *fmt, ...) = 0;
			virtual void            GetCurrentLocation() = 0;
			virtual void            MsgColour(const Color &col, const char *fmt, ...) = 0;
			virtual void            SetState(lua_State* state) = 0;
			virtual void            _nullstub5(void) = 0;
			virtual void            GetCurrentFile(std::string &outStr) = 0;
			virtual void            CompileString(void *dumper, const std::string &stringToCompile) = 0;
			virtual void            ThreadLock() = 0;
			virtual void            ThreadUnlock() = 0;
			virtual bool            CallFunctionProtected(int, int, bool) = 0;
			virtual void            Require(const char *name) = 0;
			virtual const char*        GetActualTypeName(int type) = 0;
			virtual void            SetupInfiniteLoopProtection(void);
		};
		class ILuaBase
		{
		public:
			virtual int			Top(void) = 0;
			virtual void		Push(int iStackPos) = 0;
			virtual void		Pop(int iAmt = 1) = 0;
			virtual void		GetTable(int iStackPos) = 0;
			virtual void		GetField(int iStackPos, const char* strName) = 0;
			virtual void		SetField(int iStackPos, const char* strName) = 0;
			virtual void		CreateTable() = 0;
			virtual void		SetTable(int i) = 0;
			virtual void		SetMetaTable(int i) = 0;
			virtual bool		GetMetaTable(int i) = 0;
			virtual void		Call(int iArgs, int iResults) = 0;
			virtual int			PCall(int iArgs, int iResults, int iErrorFunc) = 0;
			virtual int			Equal(int iA, int iB) = 0;
			virtual int			RawEqual(int iA, int iB) = 0;
			virtual void		Insert(int iStackPos) = 0;
			virtual void		Remove(int iStackPos) = 0;
			virtual int			Next(int iStackPos) = 0;
			virtual void*		NewUserdata(unsigned int iSize) = 0;
			virtual void		ThrowError(const char* strError) = 0;
			virtual void		CheckType(int iStackPos, int iType) = 0;
			virtual void		ArgError(int iArgNum, const char* strMessage) = 0;
			virtual void		RawGet(int iStackPos) = 0;
			virtual void		RawSet(int iStackPos) = 0;

			virtual const char*		GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
			virtual double			GetNumber(int iStackPos = -1) = 0;
			virtual bool			GetBool(int iStackPos = -1) = 0;
			virtual CFunc*	GetCFunction(int iStackPos = -1) = 0;
			virtual void*			GetUserdata(int iStackPos = -1) = 0;

			virtual void		PushNil() = 0;
			virtual void		PushString(const char* val, unsigned int iLen = 0) = 0;
			virtual void		PushNumber(double val) = 0;
			virtual void		PushBool(bool val) = 0;
			virtual void		PushCFunction(CFunc* val) = 0;
			virtual void		PushCClosure(CFunc* val, int iVars) = 0;
			virtual void		PushUserdata(void*) = 0;

			//
			// If you create a reference - don't forget to free it!
			//
			virtual int			ReferenceCreate() = 0;
			virtual void		ReferenceFree(int i) = 0;
			virtual void		ReferencePush(int i) = 0;

			//
			// Push a special value onto the top of the stack ( see below )
			//
			virtual void		PushSpecial(int iType) = 0;

			//
			// For type enums see Types.h 
			//
			virtual bool			IsType(int iStackPos, int iType) = 0;
			virtual int				GetType(int iStackPos) = 0;
			virtual const char*		GetTypeName(int iType) = 0;

			//
			// Creates a new meta table of string and type and leaves it on the stack.
			// Will return the old meta table of this name if it already exists.
			//
			virtual void			CreateMetaTableType(const char* strName, int iType) = 0;

			//
			// Like Get* but throws errors and returns if they're not of the expected type
			//
			virtual const char*		CheckString(int iStackPos = -1) = 0;
			virtual double	CheckNumber(int iStackPos = -1) = 0;


			virtual void ObjLen(int) = 0;
			virtual void GetAngle(int) = 0;
			virtual void GetVector(int) = 0;
			virtual void PushAngle(Vector const&) = 0;
			virtual void PushVector(Vector const&) = 0;
			virtual void SetState(lua_State *) = 0;
			virtual void CreateMetaTable(char const*) = 0;
			virtual void PushMetaTable(int) = 0;
			virtual void PushUserType(void *, int) = 0;
			virtual void SetUserType(int, void *) = 0;
			virtual void Init(void *, bool) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Cycle(void) = 0;
			virtual void Global(void) = 0;
			virtual void* GetObject(int) = 0;
			virtual void PushLuaObject(void *) = 0;
			virtual void PushLuaFunction(CFunc) = 0;
			virtual void LuaError(char const*, int) = 0;
			virtual void TypeError(char const*, int) = 0;
			virtual void CallInternal(int, int) = 0;
			virtual void CallInternalNoReturns(int) = 0;
			virtual void CallInternalGetBool(int) = 0;
			virtual void CallInternalGetString(int) = 0;
			virtual void CallInternalGet(int, void *) = 0;
			virtual void NewGlobalTable(char const*) = 0;
			virtual void NewTemporaryObject(void) = 0;
			virtual void isUserData(int) = 0;
			virtual void GetMetaTableObject(char const*, int) = 0;
			virtual void GetMetaTableObject(int) = 0;
			virtual void GetReturn(int) = 0;
			virtual void IsServer(void) = 0;
			virtual void IsClient(void) = 0;
			virtual void IsDedicatedServer(void) = 0;
			virtual void DestroyObject(void *) = 0;
			virtual void CreateObject(void) = 0;
			virtual void SetMember(void *, void *, void *) = 0;
			virtual void GetNewTable(void) = 0;
			virtual void SetMember(void *, float) = 0;
			virtual void SetMember(void *, float, void *) = 0;
			virtual void SetMember(void *, char const*) = 0;
			virtual void SetMember(void *, char const*, void *) = 0;
			virtual void SetIsServer(bool) = 0;
			virtual void PushLong(long) = 0;
			virtual void GetFlags(int) = 0;
			virtual void FindOnObjectsMetaTable(int, int) = 0;
			virtual void FindObjectOnTable(int, int) = 0;
			virtual void SetMemberFast(void *, int, int) = 0;
			virtual void RunString(char const* filename, char const* path, char const* stringtoun, bool run = true, bool showerrors = true) = 0;
			virtual void IsEqual(void *, void *) = 0;
			virtual void Error(char const*) = 0;
			virtual void GetStringOrError(int) = 0;
			virtual void RunLuaModule(char const*) = 0;
			virtual void FindAndRunScript(const char* path, bool run = true, bool showerrors = true, const char* type = "!CLIENT") = 0;
			virtual void SetPathID(char const*) = 0;
			virtual void GetPathID(void) = 0;
			virtual void ErrorNoHalt(char const*, ...) = 0;
			virtual void Msg(char const*, ...) = 0;
			virtual void PushPath(char const*) = 0;
			virtual void PopPath(void) = 0;
			virtual void GetPath(void) = 0;
			virtual void GetColor(int) = 0;
			virtual void PushColor(Color) = 0;
			virtual int GetStack(int, void *) = 0;
			virtual void GetInfo(char const*, void *) = 0;
			virtual void GetLocal(void *, int) = 0;
			virtual void GetUpvalue(int, int) = 0;
			virtual void RunStringEx(void*, char const* filename, char const* path, char const* torun, bool run, bool showerrors, bool idk, bool idk2) = 0;
			virtual void GetDataString(int, void **) = 0;
			virtual void ErrorFromLua(char const*, ...) = 0;
			virtual void GetCurrentLocation(void) = 0;
			virtual void MsgColour(Color const&, char const*, ...) = 0;
			virtual void GetCurrentFile(std::string &) = 0;
			virtual void CompileString(int &, std::string const&) = 0;
			virtual void CallFunctionProtected(int, int, bool) = 0;
			virtual void Require(char const*) = 0;
			virtual void GetActualTypeName(int) = 0;
			virtual void PreCreateTable(int, int) = 0;
			virtual void PushPooledString(int) = 0;
			virtual void GetPooledString(int) = 0;
			virtual void AddThreadedCall(void *) = 0;

			lua_State* L;
		};

		struct lua_State
		{
			unsigned char				_ignore_this_common_lua_header_[69];
			ILuaBase*	luabase;
		};

		enum
		{
			SPECIAL_GLOB,		// Global table
			SPECIAL_ENV,		// Environment table
			SPECIAL_REG,		// Registry table
		};
		enum
		{
			Client,
			Server,
			Menu
		};
	}
}

GarrysMod::Lua::_luaL_loadbufferx pLoadBufferx;
GarrysMod::Lua::_luaL_loadbuffer pLoadBuffer;

GarrysMod::Lua::lua_State* loadbufferstate;
typedef int(__cdecl *_luaL_loadfile)(GarrysMod::Lua::lua_State *state, const char *filename);
_luaL_loadfile luaL_loadfile = NULL;

typedef int(__cdecl *_luaL_gettop)(GarrysMod::Lua::lua_State *state);
_luaL_gettop luaL_gettop = NULL;

typedef int(__cdecl *_luaL_settop)(GarrysMod::Lua::lua_State *state, int top);
_luaL_settop luaL_settop = NULL;

typedef int(__cdecl *_luaL_loadstring)(GarrysMod::Lua::lua_State *state, const char *str);
_luaL_loadstring luaL_loadstring = NULL;

typedef const char*(__cdecl *_lua_tolstring)(GarrysMod::Lua::lua_State *state, int i1, int i2);
_lua_tolstring lua_tolstring = NULL;

typedef int(__cdecl *_luaL_pcall)(GarrysMod::Lua::lua_State *state, int nargs, int nresults, int errfunc);
_luaL_pcall luaL_pcall = NULL;

#endif 

