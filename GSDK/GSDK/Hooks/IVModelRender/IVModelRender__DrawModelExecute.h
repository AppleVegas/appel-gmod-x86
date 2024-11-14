typedef void(__thiscall* DrawModelExecuteFn)(IVModelRender*, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
DrawModelExecuteFn orgDrawModelExecute = nullptr;

void __fastcall hookDrawModelExecute(IVModelRender* modelrender, void* edx, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	//static BYTE* IsRecordingMovie = *(BYTE**)(Util::Pattern::FindPattern("engine.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? D9 45 18"/*CL_StartMovie*/) + 0x3E);
	//if (engine()->IsTakingScreenshot() || *IsRecordingMovie) // steam screenshot & startmovie checks
	//	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
	if (!allow)
		return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
	if (!HackVars::Visuals::Enabled)
		return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
	if (pInfo.entity_index)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		BaseEntity* Ent = (BaseEntity*)cliententitylist()->GetClientEntity(pInfo.entity_index);
		const char* ModelName = ModelInfo()->GetModelName((model_t*)pInfo.pModel);
		//
		//if (!Ent || Ent->IsWorld())
		//	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//
		//float colormod[3];
		//colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//
		IMaterial* WireFrameh = MaterialSystem()->FindMaterial("models/wireframe", TEXTURE_GROUP_MODEL);
		WireFrameh->AddRef();
		//
		//if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::PlayerESP && Ent != LocalPlayer && Ent->IsPlayer() && Ent->IsAlive())
		//{
		//	if (!HackVars::Visuals::ESP::pUnlimDist && (LocalPlayer->m_vecOrigin().DistTo(Ent->m_vecOrigin()) > (float)HackVars::Visuals::ESP::pMaxDist))
		//			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	if (HackVars::Visuals::ESP::PlayerXQZ)
		//	{
		//		if (HackVars::Visuals::ESP::PlayerChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::PlayerChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		colormod[0] = HackVars::Visuals::ESP::fNVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVPlayerChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::PlayerChamsStyle == 0 || HackVars::Visuals::ESP::PlayerChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::PlayerChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	}
		//	if (HackVars::Visuals::ESP::PlayerChamsEnabled)
		//	{
		//		if (HackVars::Visuals::ESP::PlayerChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::PlayerChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//		colormod[0] = HackVars::Visuals::ESP::fVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVPlayerChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::PlayerChamsStyle == 0 || HackVars::Visuals::ESP::PlayerChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::PlayerChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	}
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//	colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//	renderview()->SetColorModulation(colormod);
		//	ModelRender()->ForcedMaterialOverride(nullptr);
		//	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//}
		//else if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::LuaESP && Ent->UsesLua() && !Ent->IsPlayer() && !Ent->IsWeapon() && !Ent->IsHands())
		//{
		//	if (!HackVars::Visuals::ESP::lUnlimDist && (LocalPlayer->m_vecOrigin().DistTo(Ent->m_vecOrigin()) > (float)HackVars::Visuals::ESP::lMaxDist))
		//			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	if (HackVars::Visuals::ESP::LuaXQZ)
		//	{
		//		if (HackVars::Visuals::ESP::LuaChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::LuaChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		colormod[0] = HackVars::Visuals::ESP::fNVLuaChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVLuaChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVLuaChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::LuaChamsStyle == 0 || HackVars::Visuals::ESP::LuaChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::LuaChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	}
		//	if (HackVars::Visuals::ESP::LuaChamsEnabled)
		//	{
		//		if (HackVars::Visuals::ESP::LuaChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::LuaChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//		colormod[0] = HackVars::Visuals::ESP::fVLuaChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVLuaChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVLuaChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::LuaChamsStyle == 0 || HackVars::Visuals::ESP::LuaChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::LuaChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//		renderview()->SetColorModulation(colormod);
		//		ModelRender()->ForcedMaterialOverride(nullptr);
		//		return;
		//	}
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//	colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//	renderview()->SetColorModulation(colormod);
		//	ModelRender()->ForcedMaterialOverride(nullptr);
		//
		//	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//}
		//else if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::WeaponESP && Ent->IsWeapon() && !Ent->IsHands())
		//{
		//	if (!HackVars::Visuals::ESP::wUnlimDist && (LocalPlayer->m_vecOrigin().DistTo(Ent->m_vecOrigin()) > (float)HackVars::Visuals::ESP::wMaxDist))
		//			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	if (HackVars::Visuals::ESP::WeaponXQZ)
		//	{
		//		if (HackVars::Visuals::ESP::WeaponChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::WeaponChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
		//		colormod[0] = HackVars::Visuals::ESP::fNVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVWeapChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::WeaponChamsStyle == 0 || HackVars::Visuals::ESP::WeaponChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//	}
		//	if (HackVars::Visuals::ESP::WeaponChamsEnabled)
		//	{
		//		if (HackVars::Visuals::ESP::WeaponChamsStyle == 0)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		else if (HackVars::Visuals::ESP::WeaponChamsStyle == 1)
		//			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//		colormod[0] = HackVars::Visuals::ESP::fVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVWeapChamsColor[2];
		//		renderview()->SetColorModulation(colormod);
		//		if (HackVars::Visuals::ESP::WeaponChamsStyle == 0 || HackVars::Visuals::ESP::WeaponChamsStyle == 1)
		//			ModelRender()->ForcedMaterialOverride(DebugWhite);
		//		else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
		//			ModelRender()->ForcedMaterialOverride(WireFrame);
		//		orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//		colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//		renderview()->SetColorModulation(colormod);
		//		ModelRender()->ForcedMaterialOverride(nullptr);
		//		return;
		//	}
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		//	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		//	colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
		//	renderview()->SetColorModulation(colormod);
		//	ModelRender()->ForcedMaterialOverride(nullptr);
		//	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		//}
		if (HackVars::Visuals::HandsEnabled && Ent->IsHands()) {
			float colormod[3];
			colormod[0] = HackVars::Visuals::WireframeHandsColor[0]; colormod[1] = HackVars::Visuals::WireframeHandsColor[1]; colormod[2] = HackVars::Visuals::WireframeHandsColor[2];
			ModelRender()->ForcedMaterialOverride(WireFrameh);
			renderview()->SetColorModulation(colormod);
			orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			ModelRender()->ForcedMaterialOverride(nullptr);
			colormod[0] = 1; colormod[1] = 1; colormod[2] = 1;
			renderview()->SetColorModulation(colormod);
			return;
		}
		if (HackVars::Visuals::Nightmode)
		{
			if (strstr(ModelName, "models/props"))
			{
				renderview()->SetBlend(0.5f);
			}
		}


	}
	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
}

typedef bool(__thiscall* OverrideConfigFn)(IMaterialSystem*, const MaterialSystem_Config_t*, bool);
OverrideConfigFn orgOverrideConfig = nullptr;

bool __fastcall hookOverrideConfig(IMaterialSystem* ms, void *edx, MaterialSystem_Config_t *config, bool bForceUpdate)
{
	if (HackVars::Visuals::Fullbright)
		config->m_nFullbright = true;
	if (HackVars::Visuals::Minecraftify)
		config->m_bShowLowResImage = true;
	if (HackVars::Visuals::Rainbowmap)
		config->m_nShowMipLevels = true;
	if (HackVars::Visuals::Graymap)
		config->m_bDrawGray = true;

	return orgOverrideConfig(ms, config, bForceUpdate);
}