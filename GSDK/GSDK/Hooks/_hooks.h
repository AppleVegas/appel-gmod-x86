#include "detours.h"
#include "detver.h"

namespace Hook
{
	std::uintptr_t present_addr;
	std::uintptr_t reset_addr;
	VMTHook* IPanel = nullptr;
	VMTHook* IClientMode = nullptr;
	VMTHook* CHLClient = nullptr;
	VMTHook* EngineClient = nullptr;
	VMTHook* D3DDevice = nullptr;
	VMTHook* MaterialSystem = nullptr;
	VMTHook* MatRenderContext = nullptr;
	VMTHook* ViewRender = nullptr;
	VMTHook* RenderView = nullptr; 
	VMTHook* ModelRender = nullptr;
	VMTHook* Inputf = nullptr;
	VMTHook* BaseClientState = nullptr;
	VMTHook* ClientState = nullptr;
	void SetupHooks()
	{
		IPanel = new VMTHook(Interfaces::IPanel());
		IClientMode = new VMTHook(Interfaces::clientmode());
		CHLClient = new VMTHook(client());
		EngineClient = new VMTHook(engine());
		D3DDevice = new VMTHook(Interfaces::D3DDevice());
		MatRenderContext = new VMTHook(Interfaces::MatRenderContext());
		MaterialSystem = new VMTHook(Interfaces::MaterialSystem());
		ViewRender = new VMTHook(Interfaces::ViewRender());
		Inputf = new VMTHook(Interfaces::Input());
		RenderView = new VMTHook(Interfaces::renderview());
		BaseClientState = new VMTHook(Interfaces::BaseClientState());
		ClientState = new VMTHook(reinterpret_cast<DWORD**>((DWORD)Interfaces::BaseClientState() + 0x8));
		ModelRender = new VMTHook(Interfaces::ModelRender());
	}
	void HookFunctions()
	{
		//std::uintptr_t present_addr = Util::Pattern::FindPattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB 74 1E") + 2;
		//std::uintptr_t reset_addr = Util::Pattern::FindPattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 2;
		//
		//Hook::SteamOverlayPresent = **reinterpret_cast<decltype(&Hook::SteamOverlayPresent)*>(present_addr);
		//Hook::SteamOverlayReset = **reinterpret_cast<decltype(&Hook::SteamOverlayReset)*>(reset_addr);
		//
		//**reinterpret_cast<void***>(present_addr) = reinterpret_cast<void*>(&Hook::SteamOverlayPresent_hook);
		//**reinterpret_cast<void***>(reset_addr) = reinterpret_cast<void*>(&Hook::SteamOverlayReset_hook);

		//// IPanel
		orgPaintTraverse = (PaintTraverseFn)IPanel->hookFunction(41, hkPaintTraverse);
		//
		////orgReadPixels = (CMatRenderContext)MatRenderContext->hookFunction(99, hReadPixels);
		//// IClientMode
		orgCreateMove = (CreateMoveFn)IClientMode->hookFunction(21, hookCreateMove); 
		//orgShouldDrawFog = (ShouldDrawFogFn)IClientMode->hookFunction(8, hookShouldDrawFog);
		///orgCCreateMove = (CCreateMoveFn)CHLClient->hookFunction(21, hookCCreateMove);
		//
		//orgOverrideView = (OverrideViewFn)IClientMode->hookFunction(16, hookOverrideView); --
		orgOverrideConfig = (OverrideConfigFn)MaterialSystem->hookFunction(16, hookOverrideConfig);
		//// CHLClient
		orgFrameStageNotify = (FrameStageNotifyFn)CHLClient->hookFunction(35, hookFrameStageNotify);
		//
		//
		////ViewRenderFn
		orgView_Render = (ViewRenderFn)CHLClient->hookFunction(26, hookView_Render); //prob
		//
		//Net Hooking
		orgServerToClient = (ServerToClient)ClientState->hookFunction(30, hookServerToClient); 
		//// ViewRender
		orgRenderView = (RenderViewFn)ViewRender->hookFunction(6, hookRenderView);
		//
		//// Renderview
		orgSceneEnd = (SceneEndFn)RenderView->hookFunction(9, hookSceneEnd);
		//
		//// IVModelRender
		orgDrawModelExecute = (DrawModelExecuteFn)ModelRender->hookFunction(20, hookDrawModelExecute);

		// D3DDevice
		orgReset = (ResetFn)D3DDevice->hookFunction(16, hookReset);
		orgEndScene = (EndSceneFn)D3DDevice->hookFunction(42, hookEndScene);
		//orgSetRenderState = (SetRenderStateFn)D3DDevice->hookFunction(81, hookSetRenderState);

		orgSetCursorPos = SetCursorPos;
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)orgSetCursorPos, hookSetCursorPos);
		DetourTransactionCommit();
	}
	void UnHookFunctions()
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)orgSetCursorPos, hookSetCursorPos);
		DetourTransactionCommit();

		//**reinterpret_cast<void***>(present_addr) = reinterpret_cast<void*>(&Hook::SteamOverlayPresent);
		//**reinterpret_cast<void***>(reset_addr) = reinterpret_cast<void*>(&Hook::SteamOverlayReset);
		// IPanel
		IPanel->unhookFunction(41);
		//MatRenderContext->unhookFunction(11);

		// IClientMode
		IClientMode->unhookFunction(21);
		//IClientMode->unhookFunction(15);
		IClientMode->unhookFunction(8);
		//net
		ClientState->unhookFunction(30);
		MaterialSystem->unhookFunction(16);
		// CHLClient
		CHLClient->unhookFunction(35);
		CHLClient->unhookFunction(26);
		///CHLClient->unhookFunction(21);
		// ViewRender
		
		ViewRender->unhookFunction(6);

		// Renderview
		RenderView->unhookFunction(9);

		// IVModelRender
		ModelRender->unhookFunction(20);

		// D3DDevice
		D3DDevice->unhookFunction(16);
		D3DDevice->unhookFunction(42);
		//D3DDevice->unhookFunction(81);
	}
};
