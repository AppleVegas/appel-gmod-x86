QAngle ViewAngle = QAngle(0, 0, 0);
QAngle ViewAngles = QAngle(0, 0, 0);
namespace HackVars
{
	CUserCmd* CurCmd = nullptr;
	const char* playerlist[512];
	const char* luascript;
	bool runlua;
	float FOV = 90.0f;
	namespace Fonts
	{
		int DefaultFont = 0;
	};
	namespace convars
	{
		ConVar* FOV = nullptr;
	}
	namespace LastSentInfo
	{
		QAngle viewangles = QAngle(0, 0, 0);
		Vector Position = Vector(0, 0, 0);
	};
	namespace Aimbot
	{
		BaseEntity* AimbotTarget = nullptr;
		Vector AimbotPos = Vector(0, 0, 0);
		bool Enabled = false;
		bool Silent = false;
		bool pSilent = false;
		bool Always = false;
		bool Autoshoot = false;
		bool HEAimbot = false;
		int HAimbot = NULL;
		bool Nospread = false;
		bool Norecoil = false;
		bool EnemyOnly = false;
		bool AimOnShoot = true;
		bool NoTarget = false;
		bool aimbotnotarget[512];
		bool UnlimDist = true;
		float MaxDist = 1000;
		int Hotkey = 18;
		int FOV = 30;
	};
	namespace HvH
	{
		bool AntiaimEnabled = false;
		float AntiaimSpinSpeed = 10;
		int Antiaimstyle = 0;
	};
	namespace Script
	{
		bool Catch_Lua = false;
		bool Block_SendLua = false;
		bool Block_Net = false;
		bool Log_Net = false;
		bool Steal_Lua = false;
		bool Steal_Lua_Log = false;
		bool PropBoost = false;
		int HPropBoost = 66;
		int MPropBoost = 0;
		bool AutoHeal = false;
		int AutoHealMin = 50;
		int AutoHealTick = 10;
		bool AutoArmor = false;
		int AutoArmorMin = 50;
		bool Bunnyhop = false;
		char Name[32] = "Name";
		bool ChatClear = false;
		bool Uspam = false;
		bool Fspam = false;
		bool A1Spam = false;
		bool A2Spam = false;
		bool RopeSpam = false;
		namespace FollowBot {
			bool Enabled =false;
			int Key = 66;
			float MaxDist = 175.f;
			float MinDist = 35.f;
		}
	};
	namespace Visuals
	{
		bool Enabled = true;
		bool HandsEnabled = false;
		bool Hitmarker = false;
		bool Nightmode = false;
		bool Fullbright = false;
		bool Rainbowmap = false;
		bool Minecraftify = false;
		bool Graymap = false;
		bool Nofog = false;
		bool FreeCam = false;
		bool HEFreeCam = false;
		int HFreeCam = NULL;
		int FreeCamSpeed = 10;
		float WireframeHandsColor[4] = { 0, 0.82f, 0, 0 };
		namespace Aimbot
		{
			bool FOVCircle = false;
			bool DrawTarget = true;
		};
		namespace RenderView
		{
			bool Enabled = false;
			bool ThirdPerson = false;
			int ThirdPersonDistance = 100;
			bool EnableFOV = false;
			int FOV = 0;
			bool EnableViewFOV = false;
			int ViewModelFOV = 0;
		};
		namespace ESP
		{
			//player 
			bool PlayerESP = false;
			bool lua = true;
			bool npc = false;
			bool PlayerBox = true;
			int PlayerBoxStyle = 1;
			bool PlayerDrawname = true;
			bool PlayerDrawHealth = true;
			bool PlayerDrawDist = true;
			bool PlayerDrawHealthBar = false;
			float fPBoxColor[4] = { 1, 1, 1, 1 };
			float fPHBoxColor[4] = { 1, 0, 0, 1 };
			Color PBoxColor = Color(255, 255, 255, 255);
			bool pUnlimDist = true;
			float pMaxDist = 1000;
			bool espnotarget[512];
			bool esphighlight[512];
			bool PlayerChamsEnabled = true;
			bool PlayerXQZ = true;
			bool PlayerCFlat = true;
			int PlayerChamsStyle;
			float fNVPlayerChamsColor[4] = { 0, 0.82f, 0, 0 };
			float fVPlayerChamsColor[4] = { 0, 0, 1, 0 };

			// lua esp
			bool LuaESP = false;

			bool LuaBox = true;
			bool LuaDrawName = true;
			bool LuaDrawHealth = true;
			int LuaBoxStyle = 1;
			float fLBoxColor[4] = { 1, 1, 1, 1 };
			Color LBoxColor = Color(255, 255, 255, 255);
			bool lUnlimDist = true;
			float lMaxDist = 1000;
			bool LuaChamsEnabled = true;
			bool LuaXQZ = true;
			bool LuaCFlat = true;
			int LuaChamsStyle = 0;
			float fNVLuaChamsColor[4] = { 0, 0, 1, 0 };
			float fVLuaChamsColor[4] = { 0, 1, 0, 0 };

			// weapon esp
			bool WeaponESP = false;
			bool wUnlimDist = true;
			float wMaxDist = 1000;
			bool WeaponChamsEnabled = true;
			bool WeaponXQZ = true;
			bool WeaponCFlat = true;
			int WeaponChamsStyle = 1;
			float fNVWeapChamsColor[4] = { 1, 0, 0, 0 };
			float fVWeapChamsColor[4] = { 1, 1, 0, 0 };
		};

	};
	namespace Developer
	{
		char Text = 'Ï';
	};
	namespace Other
	{
		bool SafeMode = false;
	};
};