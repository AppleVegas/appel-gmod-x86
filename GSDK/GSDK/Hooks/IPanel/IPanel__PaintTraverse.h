typedef void(__thiscall* PaintTraverseFn)(void*, vgui::VPanel*, bool, bool);
PaintTraverseFn orgPaintTraverse = nullptr;

void __fastcall hkPaintTraverse(void* ecx, void* edx, vgui::VPanel* vguiPanel, bool forceRepaint, bool allowForce)
{
	orgPaintTraverse(ecx, vguiPanel, forceRepaint, allowForce);

	if (!allow)
		return;

	if (!engine()->IsInGame() || (strcmp(Interfaces::IPanel()->GetName(vguiPanel), "HudGMOD")))
		return;

	static int cnt = 0;
	if (HackVars::Visuals::HEFreeCam && ImGui::IsKeyDown(HackVars::Visuals::HFreeCam) && !Menu::opened)
	{
		cnt++;
	}
	else
		cnt = 0;

	if (cnt == 1) { HackVars::Visuals::FreeCam = !HackVars::Visuals::FreeCam; }

	if (HackVars::Script::Fspam && !Menu::opened)
	{
		if (GetAsyncKeyState(70))
		{
			engine()->ClientCmd_Unrestricted("impulse 100");
		}
	}


	//if (HackVars::Script::ChatClear)
	//{
	//	HackVars::Script::ChatClear = false;
	//
	//	//char cmd[256];
	//	//sprintf(cmd, "say huy");
	//	INetChannel *ch = (INetChannel*)engine()->GetNetChannelInfo();
	//
	//	ch->StringCommand("say huesosina");
	//}
}
