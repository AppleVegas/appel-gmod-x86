typedef bool(__thiscall* CCreateMoveFn)(void*, int, float, bool);
CCreateMoveFn orgCCreateMove = nullptr;


bool __fastcall hookCCreateMove(CHLClient* ClientMode, void* edx, int sequence_number, float input_sample_frametime, bool active)
{
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
	orgCCreateMove(ClientMode, sequence_number, input_sample_frametime, active);

	CUserCmd *cmd = Input()->GetUserCmd(sequence_number);
	CVerifiedUserCmd *Verifiedcmd = &Input()->m_pVerifiedCommands[sequence_number % 90];
	//std::cout << pCommand << std::endl;
	if (!cmd)
		return false;
	ViewAngle = cmd->viewangles;
	if (cmd->command_number == 0 || !engine()->IsInGame() || !LocalPlayer || !LocalPlayer->IsAlive()) {
		orgCCreateMove(ClientMode, sequence_number, input_sample_frametime, active);
		return false;
	}
	bool ForcedPacket = false;

	if (engine()->GetNetChannel()->m_nChokedPackets >= 14)
		ForcedPacket = true;

	HackVars::CurCmd = cmd;

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);

	//printf("here");
	if (!ForcedPacket)
	{
		cmd->viewangles.x = 90;
		cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
		H::Util::CorrectMovement(cmd, ViewAngle);
	}
	//std::cout << sequence_number << std::endl;
	if (ForcedPacket)
		sendpacket = true;

	if (sendpacket) {
		HackVars::LastSentInfo::Position = LocalPlayer->GetRenderOrigin();
		HackVars::LastSentInfo::viewangles = cmd->viewangles;
	}
	//
	//*(Vector*)(pCommand + 0x40) = Vector(999, 999, 999); // normalized directional vectow
	//*(int8_t*)(pCommand + 0x3f) = true; // tell game we r in context menu =)
	Verifiedcmd->m_cmd = *cmd;
	Verifiedcmd->m_crc = cmd->GetChecksum();
	return true;
};
