#define NETMSG_TYPE_BITS	5	// must be 2^NETMSG_TYPE_BITS > SVC_LASTMSG
#include "include.h"


HANDLE myThread = NULL;

HANDLE console;
HMODULE module = NULL;
//HANDLE myThread;
std::string autorun = "";

int run = 1;
int freeconsole = 0;
int count = 0;
int cur = 1;



int cLoadbufferx(GarrysMod::Lua::lua_State* state, const char *buff, size_t sz, const char *name, void *mode)
{
	loadbufferstate = state;
	//char buf[512];
	//sprint(buf, "Catched Loadbuffer [%s]:\n", name);
	//printf(buff);
	//printf("\n");
	//char buffer[21] = "C:/Appel/lastrun.lua";
	//RunFile(buffer);

	if (!allow)
		return pLoadBufferx(state, buff, sz, name, mode);
	//if (std::string(name).find("includes/extensions/net.lua") != std::string::npos) 
	//{
	//	if (fileExists("C:/Appel/net.lua"))
	//	{
	//		//printf(buff);
	//		printInfo("Replaced includes/extensions/net.lua \n");
	//		std::string newbuff = openFile("C:/Appel/net.lua");
	//		//printf(newbuff.c_str());
	//		return pLoadBufferx(state, newbuff.c_str(), sz, name, mode);
	//	}
	//}
	if (engine()->IsConnected())
	{
		std::string bug = std::string(buff);
		if (bug.find("net.Receive(") != std::string::npos && (std::string(name).find("includes/extensions/net.lua") == std::string::npos))
		{
			std::istringstream f(bug);
			std::string line;

			while (std::getline(f, line, '\n')) {
				if (line.find("net.Receive(") != std::string::npos && (line.find("=") == std::string::npos))
				{
					if (HackVars::Script::Log_Net)
					{
						printInfo(std::string(std::string(line) + " \n").c_str());
					}
					stringtable[cur] = line;
					stringtablel[cur] = std::string(name);
					cur++;
				}
			}

		}
	}
	if (HackVars::Script::Steal_Lua)
	{
		if (engine()->IsConnected())
		{
			if (HackVars::Script::Steal_Lua_Log)
				printInfo(std::string("Loading " + std::string(name) + " \n").c_str());

			std::string ip = engine()->GetNetChannelInfo()->GetAddress();
			std::replace(ip.begin(), ip.end(), ':', '_');
			std::string result = "C:/Appel/filestealer/" + ip + "/" + name;
			if (HackVars::Script::Steal_Lua_Log)
				printInfo(std::string("Stealing " + std::string(name) + " \n").c_str());

			stealLua(result.c_str(), std::string(buff));
		}
	}
	if (HackVars::Script::Catch_Lua)
	{
		if (strcmp(name, "@LuaCmd") != 0 && strcmp(name, "@Startup") != 0) {
			printInfo("Lua Detected: " + std::string(name) + " \n");
			printColorS(COLOR_CYAN, buff);
			printf("\n");

			//printInfo("Lua Detected: " + std::string(name) + " and " + std::string(mode) + " \n");
			//printColorS(COLOR_CYAN, buff);
			//printf("\n");
			//printf("0x%X\n", state);
			//getSomeState();
			//printf("0x%X\n", qrex);
		}
	}
	if (strcmp(name, "@LuaCmd") == 0)
	{
		if (!HackVars::Script::Block_SendLua)
		{
			printInfo("SendLua Detected \n");
		}
		else {
			printWarningS("SendLua Blocked \n");
			printColorS(COLOR_PURPLE, buff);
			printf("\n");
			return 0;
		}
		printColorS(COLOR_PURPLE, buff);
		printf("\n");
	}
	if (strcmp(name, "@Startup") == 0)
	{
		if (HackVars::Script::Steal_Lua)
		{
			printInfo("Started Lua stealing.\n");
		}
		if (autorun != "") {
			printInfo("Launching Before Autorun script.\n");
			std::string buf(autorun);
			buf.append(buff);
			return pLoadBufferx(state, buf.c_str(), buf.size(), name, mode);
		}

	}
	return pLoadBufferx(state, buff, sz, name, mode);
}

bool unload(void* dll)
{
	InputSystem()->EnableInput(true);
	surface()->SetCursorAlwaysVisible(false);
	SetWindowLongPtrW(FindWindowW(L"Valve001", nullptr), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(orgproc));
	delete Interfaces::_I::HitMarkerEvent;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)pLoadBufferx, cLoadbufferx);
	DetourTransactionCommit();
	Hook::UnHookFunctions();

	ImGui_ImplDX9_Shutdown();
	if (TerminateThread(myThread, 0))
	{
		FreeConsole();
		FreeLibraryAndExitThread(HMODULE(dll), 0);
		return true;
	}
} 

void RunBeforeAutorun(const std::string& buff)
{
		autorun = buff + "\n";
}

void ClearBeforeAutorunScript()
{
	autorun = "";
}
void SetupOffsets()
{
	CNetworkedVariableManager* NVMGR = new CNetworkedVariableManager();
	// DT_BasePlayer
	offsets::DT_BasePlayer::m_iFOV						= NVMGR->GetOffset("DT_BasePlayer","m_iFOV");
	offsets::DT_BasePlayer::m_iFOVStart					= NVMGR->GetOffset("DT_BasePlayer", "m_iFOVStart");
	offsets::DT_BasePlayer::m_flFOVTime					= NVMGR->GetOffset("DT_BasePlayer", "m_flFOVTime");
	offsets::DT_BasePlayer::m_iDefaultFOV				= NVMGR->GetOffset("DT_BasePlayer", "m_iDefaultFOV");
	offsets::DT_BasePlayer::m_hZoomOwner				= NVMGR->GetOffset("DT_BasePlayer", "m_hZoomOwner");
	offsets::DT_BasePlayer::m_hVehicle					= NVMGR->GetOffset("DT_BasePlayer", "m_hVehicle");
	offsets::DT_BasePlayer::m_hUseEntity				= NVMGR->GetOffset("DT_BasePlayer", "m_hUseEntity");
	offsets::DT_BasePlayer::m_iHealth					= NVMGR->GetOffset("DT_BasePlayer", "m_iHealth");
	offsets::DT_BasePlayer::m_lifeState					= NVMGR->GetOffset("DT_BasePlayer", "m_lifeState");
	offsets::DT_BasePlayer::m_iBonusProgress			= NVMGR->GetOffset("DT_BasePlayer", "m_iBonusProgress");
	offsets::DT_BasePlayer::m_iBonusChallenge			= NVMGR->GetOffset("DT_BasePlayer", "m_iBonusChallenge");
	offsets::DT_BasePlayer::m_flMaxspeed				= NVMGR->GetOffset("DT_BasePlayer", "m_flMaxspeed");
	offsets::DT_BasePlayer::m_fFlags					= NVMGR->GetOffset("DT_BasePlayer", "m_fFlags");
	offsets::DT_BasePlayer::m_iObserverMode				= NVMGR->GetOffset("DT_BasePlayer", "m_iObserverMode");
	offsets::DT_BasePlayer::m_hObserverTarget			= NVMGR->GetOffset("DT_BasePlayer", "m_hObserverTarget");
	offsets::DT_BasePlayer::m_szLastPlaceName			= NVMGR->GetOffset("DT_BasePlayer", "m_szLastPlaceName");
	offsets::DT_BasePlayer::m_bUseWeaponsInVehicle		= NVMGR->GetOffset("DT_BasePlayer", "m_bUseWeaponsInVehicle");
	//offsets::DT_BasePlayer::m_ArmorValue				= NVMGR->GetOffset("DT_BasePlayer", "m_ArmorValue");
	offsets::DT_PlayerResource::m_iArmor = NVMGR->GetOffset("DT_BasePlayer", "m_iArmor");
	//printf(std::to_string(offsets::DT_PlayerResource::m_iArmor).c_str());
	// DT_BaseEntity
	offsets::DT_BaseEntity::m_flSimulationTime			= NVMGR->GetOffset("DT_BaseEntity", "m_flSimulationTime");
	//offsets::DT_BaseEntity::m_ArmorValue				= NVMGR->GetOffset("DT_BaseEntity", "m_flSuitPower");
	offsets::DT_BaseEntity::m_ubInterpolationFrame		= NVMGR->GetOffset("DT_BaseEntity", "m_ubInterpolationFrame");
	offsets::DT_BaseEntity::m_vecOrigin					= NVMGR->GetOffset("DT_BaseEntity", "m_vecOrigin");
	offsets::DT_BaseEntity::m_angRotation				= NVMGR->GetOffset("DT_BaseEntity", "m_angRotation");
	offsets::DT_BaseEntity::m_nModelIndex				= NVMGR->GetOffset("DT_BaseEntity", "m_nModelIndex");
	offsets::DT_BaseEntity::m_fEffects					= NVMGR->GetOffset("DT_BaseEntity", "m_fEffects");
	offsets::DT_BaseEntity::m_nRenderMode				= NVMGR->GetOffset("DT_BaseEntity", "m_nRenderMode");
	offsets::DT_BaseEntity::m_nRenderFX					= NVMGR->GetOffset("DT_BaseEntity", "m_nRenderFX");
	offsets::DT_BaseEntity::m_clrRender					= NVMGR->GetOffset("DT_BaseEntity", "m_clrRender");
	offsets::DT_BaseEntity::m_iTeamNum					= NVMGR->GetOffset("DT_BaseEntity", "m_iTeamNum");
	offsets::DT_BaseEntity::m_CollisionGroup			= NVMGR->GetOffset("DT_BaseEntity", "m_CollisionGroup");
	offsets::DT_BaseEntity::m_flElasticity				= NVMGR->GetOffset("DT_BaseEntity", "m_flElasticity");
	offsets::DT_BaseEntity::m_flShadowCastDistance		= NVMGR->GetOffset("DT_BaseEntity", "m_flShadowCastDistance");
	offsets::DT_BaseEntity::m_hOwnerEntity				= NVMGR->GetOffset("DT_BaseEntity", "m_hOwnerEntity");
	offsets::DT_BaseEntity::m_hEffectEntity				= NVMGR->GetOffset("DT_BaseEntity", "m_hEffectEntity");
	offsets::DT_BaseEntity::moveparent					= NVMGR->GetOffset("DT_BaseEntity", "moveparent");
	offsets::DT_BaseEntity::m_iParentAttachment			= NVMGR->GetOffset("DT_BaseEntity", "m_iParentAttachment");
	offsets::DT_BaseEntity::m_Collision					= NVMGR->GetOffset("DT_BaseEntity", "m_Collision");
	offsets::DT_BaseEntity::m_iTextureFrameIndex		= NVMGR->GetOffset("DT_BaseEntity", "m_iTextureFrameIndex");
	offsets::DT_BaseEntity::m_bSimulatedEveryTick		= NVMGR->GetOffset("DT_BaseEntity", "m_bSimulatedEveryTick");
	offsets::DT_BaseEntity::m_bAnimatedEveryTick		= NVMGR->GetOffset("DT_BaseEntity", "m_bAnimatedEveryTick");
	offsets::DT_BaseEntity::m_bAlternateSorting			= NVMGR->GetOffset("DT_BaseEntity", "m_bAlternateSorting");
	offsets::DT_BaseEntity::m_takedamage				= NVMGR->GetOffset("DT_BaseEntity", "m_takedamage");
	offsets::DT_BaseEntity::m_RealClassName				= NVMGR->GetOffset("DT_BaseEntity", "m_RealClassName");
	offsets::DT_BaseEntity::m_OverrideMaterial			= NVMGR->GetOffset("DT_BaseEntity", "m_OverrideMaterial");
	offsets::DT_BaseEntity::m_iHealth					= NVMGR->GetOffset("DT_BaseEntity", "m_iHealth");
	offsets::DT_BaseEntity::m_iMaxHealth				= NVMGR->GetOffset("DT_BaseEntity", "m_iMaxHealth");
	offsets::DT_BaseEntity::m_spawnflags				= NVMGR->GetOffset("DT_BaseEntity", "m_spawnflags");
	offsets::DT_BaseEntity::m_iGModFlags				= NVMGR->GetOffset("DT_BaseEntity", "m_iGModFlags");
	offsets::DT_BaseEntity::m_bOnFire					= NVMGR->GetOffset("DT_BaseEntity", "m_bOnFire");
	offsets::DT_BaseEntity::m_CreationTime				= NVMGR->GetOffset("DT_BaseEntity", "m_CreationTime");
	offsets::DT_BaseEntity::m_vecVelocity0				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[0]");
	offsets::DT_BaseEntity::m_vecVelocity1				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[1]");
	offsets::DT_BaseEntity::m_vecVelocity2				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[2]");
	offsets::DT_BaseEntity::m_GMOD_DataTable			= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_DataTable");
	offsets::DT_BaseEntity::m_GMOD_bool					= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_bool");
	offsets::DT_BaseEntity::m_GMOD_float				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_float");
	offsets::DT_BaseEntity::m_GMOD_int					= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_int");
	offsets::DT_BaseEntity::m_GMOD_Vector				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_Vector");
	offsets::DT_BaseEntity::m_GMOD_QAngle				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_QAngle");
	offsets::DT_BaseEntity::m_GMOD_EHANDLE				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_EHANDLE");
	offsets::DT_BaseEntity::m_GMOD_String0				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String0");
	offsets::DT_BaseEntity::m_GMOD_String1				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String1");
	offsets::DT_BaseEntity::m_GMOD_String2				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String2");
	offsets::DT_BaseEntity::m_GMOD_String3				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String3");


	//DT_BaseCombatCharacter
	offsets::DT_BaseCombatCharacter::m_hActiveWeapon	= NVMGR->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsets::DT_BaseCombatCharacter::m_hMyWeapons		= NVMGR->GetOffset("DT_BaseCombatCharacter", "m_hMyWeapons");
	//std::cout << offsets::DT_BaseCombatCharacter::m_hActiveWeapon;

	//DT_BaseAnimating
	offsets::DT_BaseAnimating::m_nSequence = NVMGR->GetOffset("DT_BaseAnimating", "m_nSequence");
	offsets::DT_BaseAnimating::m_nForceBone = NVMGR->GetOffset("DT_BaseAnimating", "m_nForceBone");
	offsets::DT_BaseAnimating::m_vecForce = NVMGR->GetOffset("DT_BaseAnimating", "m_vecForce");
	offsets::DT_BaseAnimating::m_nSkin = NVMGR->GetOffset("DT_BaseAnimating", "m_nSkin");
	offsets::DT_BaseAnimating::m_nBody = NVMGR->GetOffset("DT_BaseAnimating", "m_nBody");
	offsets::DT_BaseAnimating::m_nHitboxSet = NVMGR->GetOffset("DT_BaseAnimating", "m_nHitboxSet");
	offsets::DT_BaseAnimating::m_flModelScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flModelScale");
	offsets::DT_BaseAnimating::m_flModelWidthScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flModelWidthScale");
	offsets::DT_BaseAnimating::m_flPoseParameter = NVMGR->GetOffset("DT_BaseAnimating", "m_flPoseParameter");
	offsets::DT_BaseAnimating::m_flPlaybackRate = NVMGR->GetOffset("DT_BaseAnimating", "m_flPlaybackRate");
	offsets::DT_BaseAnimating::m_flEncodedController = NVMGR->GetOffset("DT_BaseAnimating", "m_flEncodedController");
	offsets::DT_BaseAnimating::m_bClientSideAnimation = NVMGR->GetOffset("DT_BaseAnimating", "m_bClientSideAnimation");
	offsets::DT_BaseAnimating::m_bClientSideFrameReset = NVMGR->GetOffset("DT_BaseAnimating", "m_bClientSideFrameReset");
	offsets::DT_BaseAnimating::m_nNewSequenceParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nNewSequenceParity");
	offsets::DT_BaseAnimating::m_nResetEventsParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nResetEventsParity");
	offsets::DT_BaseAnimating::m_nMuzzleFlashParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nMuzzleFlashParity");
	offsets::DT_BaseAnimating::m_hLightingOrigin = NVMGR->GetOffset("DT_BaseAnimating", "m_hLightingOrigin");
	offsets::DT_BaseAnimating::m_hLightingOriginRelative = NVMGR->GetOffset("DT_BaseAnimating", "m_hLightingOriginRelative");
	offsets::DT_BaseAnimating::m_fadeMinDist = NVMGR->GetOffset("DT_BaseAnimating", "m_fadeMinDist");
	offsets::DT_BaseAnimating::m_flFadeScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flFadeScale");
	offsets::DT_BaseAnimating::m_pBoneManipulator = NVMGR->GetOffset("DT_BaseAnimating", "m_pBoneManipulator");
	offsets::DT_BaseAnimating::m_pFlexManipulator = NVMGR->GetOffset("DT_BaseAnimating", "m_pFlexManipulator");
	offsets::DT_BaseAnimating::m_OverrideViewTarget = NVMGR->GetOffset("DT_BaseAnimating", "m_OverrideViewTarget");

	//DT_GMOD_Player
	offsets::DT_GMOD_Player::m_iGModPlayerFlags = NVMGR->GetOffset("DT_GMOD_Player", "m_iGModPlayerFlags");
	offsets::DT_GMOD_Player::m_HoveredWidget = NVMGR->GetOffset("DT_GMOD_Player", "m_HoveredWidget");
	offsets::DT_GMOD_Player::m_PressedWidget = NVMGR->GetOffset("DT_GMOD_Player", "m_PressedWidget");
	offsets::DT_GMOD_Player::m_Driving = NVMGR->GetOffset("DT_GMOD_Player", "m_Driving");
	offsets::DT_GMOD_Player::m_DrivingMode = NVMGR->GetOffset("DT_GMOD_Player", "m_DrivingMode");
	offsets::DT_GMOD_Player::m_PlayerClass = NVMGR->GetOffset("DT_GMOD_Player", "m_PlayerClass");
	offsets::DT_GMOD_Player::m_bCanZoom = NVMGR->GetOffset("DT_GMOD_Player", "m_bCanZoom");
	offsets::DT_GMOD_Player::m_bCanWalk = NVMGR->GetOffset("DT_GMOD_Player", "m_bCanWalk");
	offsets::DT_GMOD_Player::m_bIsTyping = NVMGR->GetOffset("DT_GMOD_Player", "m_bIsTyping");
	offsets::DT_GMOD_Player::m_StepSize = NVMGR->GetOffset("DT_GMOD_Player", "m_StepSize");
	offsets::DT_GMOD_Player::m_JumpPower = NVMGR->GetOffset("DT_GMOD_Player", "m_JumpPower");
	offsets::DT_GMOD_Player::m_ViewOffset = NVMGR->GetOffset("DT_GMOD_Player", "m_ViewOffset");
	offsets::DT_GMOD_Player::m_ViewOffsetDucked = NVMGR->GetOffset("DT_GMOD_Player", "m_ViewOffsetDucked");
	offsets::DT_GMOD_Player::m_fGestureEndTime = NVMGR->GetOffset("DT_GMOD_Player", "m_fGestureEndTime");
	offsets::DT_GMOD_Player::m_PlayerColor = NVMGR->GetOffset("DT_GMOD_Player", "m_PlayerColor");
	offsets::DT_GMOD_Player::m_WeaponColor = NVMGR->GetOffset("DT_GMOD_Player", "m_WeaponColor");
	offsets::DT_GMOD_Player::m_Hands = NVMGR->GetOffset("DT_GMOD_Player", "m_Hands");
	offsets::DT_GMOD_Player::m_nWaterLevel = NVMGR->GetOffset("DT_GMOD_Player", "m_nWaterLevel");

	// DT_HL2MP_Player
	offsets::DT_HL2MP_Player::m_hRagdoll = NVMGR->GetOffset("DT_HL2MP_Player", "m_hRagdoll");
	offsets::DT_HL2MP_Player::m_iSpawnInterpCounter = NVMGR->GetOffset("DT_HL2MP_Player", "m_iSpawnInterpCounter");
	offsets::DT_HL2MP_Player::m_iPlayerSoundType = NVMGR->GetOffset("DT_HL2MP_Player", "m_iPlayerSoundType");
	offsets::DT_HL2MP_Player::m_fIsWalking = NVMGR->GetOffset("DT_HL2MP_Player", "m_fIsWalking");
} 

void OnUnload(HMODULE hModule)
{
	while (true)
	{
		if (!engine()->IsConnected())
		{
			cur = 1;
		}
		if (run == 0)
		{
			run = 2;
			if (unload(hModule))
				ExitThread(0);
		}

		Sleep(1000);
	}
}
 
void Main(HMODULE hModule)
{
	CreateConsole(std::string("Appel v" + version).c_str());
	printColor(COLOR_PURPLE, R"EOF(
  ___                   _ 
 / _ \                 | |
/ /_\ \_ __  _ __   ___| |
|  _  | '_ \| '_ \ / _ \ |
| | | | |_) | |_) |  __/ |
\_| |_/ .__/| .__/ \___|_|    x86
      | |   | |           
      |_|   |_|           
)EOF");
	printf("\n\n\n");


	// setup interfaces.
	Interfaces::_SetupInterfaces();
	Interfaces::_I::MatRenderContext = Interfaces::_I::materialsystem->GetRenderContext();
	//Interfaces::_printInterfaceAddresses();

	//setup offsets
	SetupOffsets();

	// setup some default hack variables  
	HackVars::Fonts::DefaultFont = surface()->ISCreateFont();
	surface()->SetFontGlyphSet(HackVars::Fonts::DefaultFont, "Tahoma", 15, 500, NULL, NULL, FONTFLAG_ANTIALIAS);
	surface()->SetFontGlyphSet(1, "Tahoma", 15, 500, 3, NULL, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
	surface()->SetFontGlyphSet(2, "Tahoma", 25, 600, NULL, NULL, FONTFLAG_ANTIALIAS);
	surface()->SetFontGlyphSet(3, "Tahoma", 25, 600, 3, NULL, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
	HackVars::convars::FOV = CVar()->FindVar("fov_desired");
	HackVars::Visuals::RenderView::FOV = HackVars::convars::FOV->GetInt() + 20;
	HackVars::Visuals::RenderView::ViewModelFOV = HackVars::convars::FOV->GetInt() + 30;


	// hook stuff
	Hook::SetupHooks();
	Hook::HookFunctions();

	Interfaces::_I::HitMarkerEvent = new Event_HitMarker();
	GarrysMod::Lua::_luaL_loadbuffer luaL_loadbuffer = (GarrysMod::Lua::_luaL_loadbuffer)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "luaL_loadbuffer");
	pLoadBuffer = luaL_loadbuffer;
	GarrysMod::Lua::_luaL_loadbufferx luaL_loadbufferx = (GarrysMod::Lua::_luaL_loadbufferx)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "luaL_loadbufferx");
	if (luaL_loadbufferx)
	{
		pLoadBufferx = luaL_loadbufferx;
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pLoadBufferx, cLoadbufferx);
		DetourTransactionCommit();
	}
	//skeleton for hooking functions
	//orgServerToClient = *(ServerToClient)((*(uintptr_t**)_I::engine)[0] + 0x08B5E0);
	//DetourTransactionBegin();
	//DetourUpdateThread(GetCurrentThread());
	//DetourAttach(&(PVOID&)orgServerToClient, hookServerToClient);
	//DetourTransactionCommit();
	luaL_loadfile = (_luaL_loadfile)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "luaL_loadfile");
	if (!luaL_loadfile) {
		printErrorS("Failed to find luaL_loadfile.\n");
		return;
	}

	luaL_loadstring = (_luaL_loadstring)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "luaL_loadstring");
	if (!luaL_loadstring) {
		printErrorS("Failed to find luaL_loadstring.\n");
		return;
	}

	lua_tolstring = (_lua_tolstring)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "lua_tolstring");
	if (!lua_tolstring) {
		printErrorS("Failed to find lua_tolstring.\n");
		return;
	}

	luaL_gettop = (_luaL_gettop)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "lua_gettop");
	if (!luaL_gettop) {
		printErrorS("Failed to find luaL_gettop.\n");
		return;
	}

	luaL_settop = (_luaL_settop)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "lua_settop");
	if (!luaL_settop) {
		printErrorS("Failed to find luaL_settop.\n");
		return;
	}

	luaL_pcall = (_luaL_pcall)GetProcAddress(GetModuleHandle(L"lua_shared.dll"), "lua_pcall");
	if (!luaL_pcall) {
		printErrorS("Failed to find lua_pcall.\n");
		return;
	}
	
	LoadSettings();
	printInfo("Appel successfully loaded! \n");

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnUnload, hModule, 0, nullptr);
	while (run == 1) {

		// Get input from the user.
		char usrInput[2048] = { 0 };
		fgets(usrInput, 2047, stdin);

		// Seperate and validate the user input.
		char *cmd = strtok(usrInput, " ");
		if (strcmp(cmd, "run") == 0) {
			char *scrLua = strtok(NULL, "\0");
			scrLua[strlen(scrLua) - 1] = '\0';

			// Execute the Lua script provided.
			AppelLua::RunLua(scrLua);
			continue;
		}
		else
		if (strcmp(cmd, "run\n") == 0) {
			printErrorS("Please, provide script.\n");
			continue;
		}
		if (strcmp(cmd, "runmenu") == 0) {
			char *scrLua = strtok(NULL, "\0");
			scrLua[strlen(scrLua) - 1] = '\0';

			// Execute the Lua script provided.
			AppelLua::RunFile(scrLua, true);
			continue;
		}
		else
			if (strcmp(cmd, "runmenu\n") == 0) {
				printErrorS("Please, provide script.\n");
				continue;
			}
		else
		if (strcmp(cmd, "runfile") == 0) {
			char *scrDir = strtok(NULL, "\0");
			scrDir[strlen(scrDir) - 1] = '\0';

			// Execute the Lua script provided.
			AppelLua::RunFile(scrDir);
			continue;
		}
		else
		if (strcmp(cmd, "runfile\n") == 0) {
			printErrorS("Please, provide script.\n");
			continue;
		}
		if (strcmp(cmd, "runfilemenu") == 0) {
			char *scrDir = strtok(NULL, "\0");
			scrDir[strlen(scrDir) - 1] = '\0';

			// Execute the Lua script provided.
			AppelLua::RunFile(scrDir, true);
			continue;
		}
		else
			if (strcmp(cmd, "runfilemenu\n") == 0) {
				printErrorS("Please, provide script.\n");
				continue;
			}
		else
		if (strcmp(cmd, "help\n") == 0) {
			printColorS(COLOR_BLUE, "Command list: \n");
			printColorS(COLOR_CYAN, "help - show command list. \n");
			printColorS(COLOR_CYAN, "run - run one line lua script. \n");
			printColorS(COLOR_CYAN, "runmenu - run one line lua script in menu state. \n");
			printColorS(COLOR_CYAN, "runfile - run lua file. \n");
			printColorS(COLOR_CYAN, "runfilemenu - run lua file in menu state. \n");
			printColorS(COLOR_CYAN, "cl - get client lua state. \n");
			printColorS(COLOR_CYAN, "exit - uninject Appel. \n");
			continue;
		}
		if (strcmp(cmd, "exit\n") == 0) {
			if (run == 1) {
				printInfo("Uninjected.\n");
				run = 0;
			}
			return;
		}
		if (strcmp(cmd, "cl\n") == 0) {
			AppelLua::getClientState();
			continue;
		}
		if (strcmp(cmd, "test\n") == 0) {
			GarrysMod::Lua::ILuaBase* qrex = _I::LuaShared->GetLuaInterface(GarrysMod::Lua::Client);
			GarrysMod::Lua::lua_State* pGLuaState = qrex->L;
			print("0x%X\n", pGLuaState);
			print("0x%X\n", loadbufferstate);
			continue;
		}
		else {
			printErrorS("Unknown command! \n");
			continue;
		}
	}
	return;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		module = hModule;
		myThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr);
	//	Main();
		break;
	case DLL_PROCESS_DETACH:
		run = 0;
		break;
	}
	return TRUE;
}

