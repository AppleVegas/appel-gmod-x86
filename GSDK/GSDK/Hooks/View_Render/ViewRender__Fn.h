typedef void(__thiscall* ViewRenderFn)(void*, void*, vrect_t*);
ViewRenderFn orgView_Render = nullptr;




void __fastcall hookView_Render(CHLClient* client, void* edx, vrect_t* rect) // index 26 
{
	orgView_Render(client, edx, rect);

	if (!allow)
		return;

	if (!engine()->IsInGame())
		return;

	if (HackVars::runlua)
	{
		AppelLua::RunLua(HackVars::luascript);
		HackVars::runlua = false;
	}

	static BYTE* IsRecordingMovie = *(BYTE**)(Util::Pattern::FindPattern("engine.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? D9 45 18"/*CL_StartMovie*/) + 0x3E);
	if (engine()->IsTakingScreenshot() || *IsRecordingMovie) // steam screenshot & startmovie checks
		return;

	if (!HackVars::Visuals::Enabled)
		return;
	DrawChams();
	DrawESP();

}
