typedef bool(__thiscall* CreateMoveFn)(void*, float, CUserCmd*);
CreateMoveFn orgCreateMove = nullptr;

inline void AngleNormalize(QAngle& v)
{
	for (auto i = 0; i < 3; i++)
	{
		if (v[i] < -180.0f) v[i] += 360.0f;
		if (v[i] >  180.0f) v[i] -= 360.0f;
	}
}
inline bool IsKeyDown(DWORD key)
{
	if (GetAsyncKeyState(key))
		return true;

	return false;
}
int counter = 1;
int counters = 1;
bool st = false;
bool __fastcall hookCreateMove(ClientMode* ClientMode, void* edx, float flInputSampleTime, CUserCmd* cmd)
{
	
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
	if (HackVars::Visuals::FreeCam && HackVars::Visuals::Enabled)
	{
		cmd->viewangles = ViewAngles;
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		return false;
	}
	else
	{
		if (ViewAngles != QAngle(0, 0, 0))
		{
			cmd->viewangles = ViewAngles;
			orgCreateMove(ClientMode, flInputSampleTime, cmd);
			ViewAngles = QAngle(0, 0, 0);
			return true;
		}
	}
	if (HackVars::Other::SafeMode) {
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		return false;
	}
	if (!cmd)
		return orgCreateMove(ClientMode, flInputSampleTime, cmd);

	
	//C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
	ViewAngle = cmd->viewangles;
	if (cmd->command_number == 0 || !engine()->IsInGame() || !LocalPlayer || !LocalPlayer->IsAlive()) {
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		return false;
	}
	bool ForcedPacket = false;

	if (engine()->GetNetChannel()->m_nChokedPackets >= 14)
		ForcedPacket = true;

	HackVars::CurCmd = cmd;
	
	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);
	//std::cout << CCPlayerResource()->GetArmor(LocalPlayer->entIndex()) << std::endl;
	//uintptr_t hActiveWeapon = *(uintptr_t*)((uintptr_t)LocalPlayer + offsets::DT_BaseCombatCharacter::m_hActiveWeapon);

	//CBaseCombatWeapon* weapon = LocalPlayer->GetActiveWeapon();//(CBaseCombatWeapon*)(cliententitylist()->GetClientEntityFromHandle(hActiveWeapon));
	QAngle viewpunchangle = LocalPlayer->m_vecViewPunch();
	
	//Fix vtables for LocalPlayer or Weapon
	bool HoldingTool = false;//H::Util::IsHoldingTool();
	bool HoldingExplosiveWeapon = false;//H::Util::IsExplosive();
	bool HoldingWeaponWithNospread = false;//H::Util::IsNospreadWeapon();
	
	//std::cout << LocalPlayer->GetMoveType() << std::endl;
	if (HackVars::Script::PropBoost)
	{
		if (GetAsyncKeyState(HackVars::Script::HPropBoost))
		{
			vec_t lastangles = cmd->viewangles.y;
			vec_t lastanglesx = cmd->viewangles.x;
			if (HackVars::Script::MPropBoost == 0)
			{
				cmd->viewangles.y = (lastangles - 180);
			}
			else if (HackVars::Script::MPropBoost == 1)
			{
				cmd->viewangles.x = (lastanglesx * -1);
				cmd->viewangles.y = (lastangles - 180);
			}
			else if (HackVars::Script::MPropBoost == 2)
			{
				cmd->viewangles.x = 90;
				//cmd->viewangles.y = (lastangles - 180);
			}
			cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
			H::Util::CorrectMovement(cmd, ViewAngle);
		}
	}
	
	if (HackVars::Script::AutoHeal)
	{
		if (!st)
		{
			if (HackVars::Script::AutoHealTick <= counter)
			{
				if ((LocalPlayer->GetHealth() <= HackVars::Script::AutoHealMin) && (LocalPlayer->IsAlive() && LocalPlayer->GetFlags().IsFlagSet(FL_ONGROUND)))
				{
					st = true;
					cmd->viewangles.x = 90;
					orgCreateMove(ClientMode, flInputSampleTime, cmd);
					counter = 0;
					return false;
				}
			}
			counter++;
		}
		if (st)
		{
			if (counters > 6)
			{
				counters = 0;
				st = false;
			}
			if (counters == 3)
				engine()->ClientCmd_Unrestricted("gm_spawnsent item_healthkit");
			cmd->viewangles.x = 90;
			counters++;
			orgCreateMove(ClientMode, flInputSampleTime, cmd);
			return false;
		}
	}
	
	//int Armor = *(unsigned int*)(LocalPlayer + 0xB248);
	//std::cout << Armor;
	//if (HackVars::Script::AutoArmor)
	//{
	//	if (Armor <= HackVars::Script::AutoArmorMin)
	//	{
	//		cmd->viewangles.x = 90;
	//		orgCreateMove(ClientMode, flInputSampleTime, cmd);
	//		engine()->ClientCmd_Unrestricted("gm_spawnsent item_battery");
	//		return false;
	//	}
	//}

	if (HackVars::Script::Bunnyhop)
		H::Bhop(cmd);

	if ((HackVars::Script::A1Spam || HackVars::Script::A2Spam || HackVars::Script::Uspam) && !HackVars::Script::RopeSpam)
	{
		H::Spam(cmd);
	}

	if (HackVars::Script::FollowBot::Enabled)
		H::RunFollowbot(cmd);

	PredictionSystem.StartPrediction(cmd);
	
	//Fix GetActiveWeapon
	QAngle SpreadAngle = QAngle(0, 0, 0); //H::SpreadAngle(cmd);
	
	bool bCanShoot = true; //weapon->m_flNextPrimaryAttack() <= LocalPlayer->m_nTickBase() * globals()->interval_per_tick;
	
	C_GMOD_Player* Target = nullptr;
	//Target->CreateMove();
	QAngle TargetAngle = QAngle(0, 0, 0);
	bool Aim = false;
	bool preaim = false;
	
	if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread && !preaim)
	{
		if (bCanShoot && cmd->buttons.IsFlagSet(IN_ATTACK) && !HoldingTool)
			cmd->viewangles += SpreadAngle;
	}
	
	if (!HackVars::Aimbot::Always)
	{
		if (((HackVars::Aimbot::AimOnShoot && cmd->buttons.IsFlagSet(IN_ATTACK)) || (HackVars::Aimbot::HEAimbot && IsKeyDown(HackVars::Aimbot::HAimbot) && !Menu::opened)) && (HackVars::Aimbot::Enabled && !HoldingTool && !HoldingExplosiveWeapon && !ForcedPacket)) {
			if (H::ClosestTargetToCrosshair(cmd, Target, TargetAngle)) {
				preaim = true;
				if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread)
				{
					if (bCanShoot)
						cmd->viewangles = TargetAngle + SpreadAngle;
				}
				else {
					cmd->viewangles = TargetAngle;
				}

				if (HackVars::Aimbot::Autoshoot && !HackVars::Aimbot::AimOnShoot)
					cmd->buttons.SetFlag(IN_ATTACK);

				H::Util::CorrectMovement(cmd, ViewAngle);
				Aim = true;
				cmd->tick_count = TIME_TO_TICKS(Target->m_flSimulationTime());
				// ^ that will not hit anyone fake lagging in hvh fyi.
			}
		}
	}
	else
	{
		if (HackVars::Aimbot::Enabled && !HoldingTool && !HoldingExplosiveWeapon && !ForcedPacket) {
			if (H::ClosestTargetToCrosshair(cmd, Target, TargetAngle)) {
				preaim = true;
				if (!HoldingWeaponWithNospread && HackVars::Aimbot::Nospread)
				{
					if (bCanShoot)
						cmd->viewangles = TargetAngle + SpreadAngle;
				}
				else
					cmd->viewangles = TargetAngle;
				if (HackVars::Aimbot::Autoshoot)
					cmd->buttons.SetFlag(IN_ATTACK);

				H::Util::CorrectMovement(cmd, ViewAngle);

				Aim = true;
				cmd->tick_count = TIME_TO_TICKS(Target->m_flSimulationTime());
				// ^ that will not hit anyone fake lagging in hvh fyi.
			}
		}
	}
	HackVars::Aimbot::AimbotTarget = Target;


	static float prev_yaw;
	static int prev_yawx;
	if (HackVars::HvH::AntiaimEnabled && !HackVars::Script::RopeSpam)
	{
		if (!Aim && !cmd->buttons.IsFlagSet(IN_ATTACK))
		{
			if (HackVars::HvH::Antiaimstyle == 0)
			{
				cmd->viewangles.x = 90;
				static float cur_yaw = 0;
				if (cur_yaw == 0) { cur_yaw = 180; }
				else if (cur_yaw == 180) { cur_yaw = 0; }
				cur_yaw = H::Util::Math::AngleNormalize(cur_yaw);
				cmd->viewangles.y = cur_yaw;
				cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
				H::Util::CorrectMovement(cmd, ViewAngle);
				orgCreateMove(ClientMode, flInputSampleTime, cmd);
			}
			else if (HackVars::HvH::Antiaimstyle == 1)
			{
				cmd->viewangles.x = 90;
				static float cur_yaw;
				QAngle Randy = RandomAngle(-180, 180);
				cmd->viewangles.y = H::Util::Math::AngleNormalize(Randy.y);
				cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
				H::Util::CorrectMovement(cmd, ViewAngle);
				orgCreateMove(ClientMode, flInputSampleTime, cmd);
			}
			else if (HackVars::HvH::Antiaimstyle == 2)
			{
				cmd->viewangles.x = 90;
				static float cur_yaw;
				cur_yaw += HackVars::HvH::AntiaimSpinSpeed;
				cur_yaw = H::Util::Math::AngleNormalize(cur_yaw);
				cmd->viewangles.y += cur_yaw;
				cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
				H::Util::CorrectMovement(cmd, ViewAngle);
			}
			else if (HackVars::HvH::Antiaimstyle == 3)
			{
				static float cur_yawx;

				if (prev_yawx < 2)
				{
					QAngle Randx = RandomAngle(10, 90);
					cur_yawx = H::Util::Math::AngleNormalize(Randx.x);
					prev_yawx++;
				}
				else
				{
					//srand(time(NULL));
					cur_yawx = -45;
					prev_yawx = 0;
				}
				cmd->viewangles.x = cur_yawx;
				static float cur_yaw;
				QAngle Randy = RandomAngle(-180, 180);
				cmd->viewangles.y = H::Util::Math::AngleNormalize(Randy.y);
				cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
				H::Util::CorrectMovement(cmd, ViewAngle);
				orgCreateMove(ClientMode, flInputSampleTime, cmd);
			}
		}
		else 
		{
			cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
			PredictionSystem.EndPrediction(cmd);
			orgCreateMove(ClientMode, flInputSampleTime, cmd);
		}
	}
	else if (HackVars::Script::RopeSpam)
	{
		static float cur_yawx;

		if (prev_yawx < 2)
		{
			QAngle Randx = RandomAngle(10, 90);
			cur_yawx = H::Util::Math::AngleNormalize(Randx.x);
			prev_yawx++;
		}
		else
		{
			//srand(time(NULL));
			cur_yawx = -45;
			prev_yawx = 0;
		}
		cmd->viewangles.x = cur_yawx;
		static float cur_yaw;
		QAngle Randy = RandomAngle(-180, 180);
		cmd->viewangles.y = H::Util::Math::AngleNormalize(Randy.y);
		cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
		H::Util::CorrectMovement(cmd, ViewAngle);
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		H::Spam2(cmd);
	}
	else
	{
		cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
		PredictionSystem.EndPrediction(cmd);
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
	}
	//*(Vector*)(cmd + 0x40) = Vector(ViewAngle.x, ViewAngle.y, ViewAngle.z); // normalized directional vectow
	//*(int8_t*)(cmd + 0x3f) = true; // tell game we r in context menu =)
	//bool h = *(bool*)(cmd + 0x3f);
	//std::cout << h << std::endl;
	if (ForcedPacket)
		sendpacket = true;

	if (sendpacket) {
		HackVars::LastSentInfo::Position = LocalPlayer->GetRenderOrigin();
		HackVars::LastSentInfo::viewangles = cmd->viewangles;
	}

	if(Aim)
		return !HackVars::Aimbot::Silent;
	return false;
};

typedef bool(__thiscall* ShouldDrawFogFn)(ClientMode*);
ShouldDrawFogFn orgShouldDrawFog = nullptr;
bool __fastcall hookShouldDrawFog(ClientMode *clientmode) {
	//printf("hey");
	orgShouldDrawFog(clientmode);
	return false;
}