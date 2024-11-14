//#include "../Game Events/hitmarker.h"

namespace H
{
	namespace ESP
	{

		bool IsBlackListedModel(const char* model) {
			if (strcmp(model, "gmod_hands") == 0 || strcmp(model, "gmod_camera") == 0)
				return true;

			return false;
		}
		void DrawBoundingBox(BaseEntity* Ent, BaseEntity* LocalPlayer, bool highlight = false, bool me = false)
		{
				Vector Pos = Ent->GetRenderOrigin();
				auto& frame = *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<uintptr_t>(Ent) + 0x308);

				Vector min = Pos + Ent->CollisionMins();
				Vector max = Pos + Ent->CollisionMaxs();

				Vector points[] = { Vector(min.x, min.y, min.z),
					Vector(min.x, max.y, min.z),
					Vector(max.x, max.y, min.z),
					Vector(max.x, min.y, min.z),
					Vector(max.x, max.y, max.z),
					Vector(min.x, max.y, max.z),
					Vector(min.x, min.y, max.z),
					Vector(max.x, min.y, max.z) };

				Vector vTransformed[8];

				Vector2D blb;
				Vector2D brb;
				Vector2D frb;
				Vector2D flb;

				Vector2D frt;
				Vector2D brt;
				Vector2D blt;
				Vector2D flt;

				int iY = 0;

				//if (!Util::Math::WorldToScreen(points[0], blb) || !Util::Math::WorldToScreen(points[1], brb) || !Util::Math::WorldToScreen(points[2], frb) || !Util::Math::WorldToScreen(points[3], flb) ||
				//	!Util::Math::WorldToScreen(points[4], frt) || !Util::Math::WorldToScreen(points[5], brt) || !Util::Math::WorldToScreen(points[6], blt) || !Util::Math::WorldToScreen(points[7], flt))
				//return;

				if (!Util::Math::WorldToScreen(points[3], flb) || !Util::Math::WorldToScreen(points[5], brt)
					|| !Util::Math::WorldToScreen(points[0], blb) || !Util::Math::WorldToScreen(points[4], frt)
					|| !Util::Math::WorldToScreen(points[2], frb) || !Util::Math::WorldToScreen(points[1], brb)
					|| !Util::Math::WorldToScreen(points[6], blt) || !Util::Math::WorldToScreen(points[7], flt))
					return;

				Vector2D arr[] = { blb,brb,frb,flb,frt,brt,blt,flt };
				float left = flb.x;
				float top = flb.y;
				float right = flb.x;
				float bottom = flb.y;

				for (int i = 1; i < 8; i++)
				{
					if (left > arr[i].x)
						left = arr[i].x;
					if (top < arr[i].y)
						top = arr[i].y;
					if (right < arr[i].x)
						right = arr[i].x;
					if (bottom > arr[i].y)
						bottom = arr[i].y;
				}

				float x = left;
				float y = bottom;
				float w = right - left;
				float h = top - bottom;

				x += ((right - left) / 8); //pseudo fix for those THICC boxes
				w -= ((right - left) / 8) * 2;



				if (Ent->IsPlayer() && Ent->IsAlive())
				{
					if (HackVars::Visuals::ESP::PlayerBox)
					{
						if (HackVars::Visuals::ESP::PlayerBoxStyle == 0)
						{
							H::Draw::DrawOutlineRect(x, y, w, h, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
						}
						else if (HackVars::Visuals::ESP::PlayerBoxStyle == 1)
						{
							int VertLine;
							int HorzLine;
							VertLine = (((float)w) * (0.2f));
							HorzLine = (((float)h) * (0.2f));

							H::Draw::DrawOutlineRect(x, y - 1, VertLine, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - VertLine, y - 1, VertLine, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - VertLine, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));

							H::Draw::DrawOutlineRect(x - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));

							H::Draw::DrawOutlineRect(x, y, VertLine, 1, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + w - VertLine, y, VertLine, 1, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x, y + h, VertLine, 1, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + w - VertLine, y + h, VertLine, 1, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);

							H::Draw::DrawOutlineRect(x, y, 1, HorzLine, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x, y + h - HorzLine, 1, HorzLine, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + w, y, 1, HorzLine, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + w, y + h - HorzLine, 1, HorzLine, highlight ? HackVars::Visuals::ESP::fPHBoxColor : HackVars::Visuals::ESP::fPBoxColor);
						}
					}

					if (HackVars::Visuals::ESP::PlayerDrawname)
					{
						if (!me) {
							player_info_t player_info;
							if (engine()->GetPlayerInfo(Ent->entIndex(), &player_info))
							{
								H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, x + w + 2, y + iY, highlight ? HackVars::Visuals::ESP::fPHBoxColor : Color(255,255,255,255)); //, get_team_color(Ent->GetTeamNumber())
								iY += 15;
							}
						}
						else
						{
							H::Draw::Drawtext("Me", HackVars::Fonts::DefaultFont, x + w + 2, y + iY); //, get_team_color(Ent->GetTeamNumber())
							iY += 15;
						}
					}

					float health = Ent->GetHealth();

					int Red = 255 - (health*2.55);
					int Green = health*2.55;

					if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::PlayerDrawHealth && !me)
					{
						H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, x + w + 2, y + iY, Color(Red, Green, 0, 255));
						iY += 15;
					}
					if (HackVars::Visuals::ESP::PlayerDrawDist && !me)
					{
						H::Draw::Drawtext(std::to_string((int)LocalPlayer->m_vecOrigin().DistTo(Ent->m_vecOrigin())).c_str(), HackVars::Fonts::DefaultFont, x + w + 2, y + iY, highlight ? HackVars::Visuals::ESP::fPHBoxColor : Color(255, 255, 255, 255));
						iY += 15;
					}
					if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::PlayerDrawHealthBar)
					{
						float hh = (h);
						float offset = (hh / 4.f) + 5;
						float w = hh / 64.f;
						UINT hp = hh - (UINT)((hh * health) / 100); // Percentage

						H::Draw::DrawOutlineRect(x, y, w, h, Color(0, 0, 0, 0));
						H::Draw::DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 0));
						H::Draw::Drawtext("", HackVars::Fonts::DefaultFont, x + w + 2, y + iY, Color(Red, Green, 0, 255));
						iY += 15;

						H::Draw::DrawOutlineRect((x - 6) - 1, y - 1, 3, hh + 2, Color(0, 0, 0, 255));
						H::Draw::DrawLine((x - 6), y + hp, (x - 6), y + hh, Color(Red, Green, 0, 255));
					}
				}
				else if (((Ent->UsesLua() && HackVars::Visuals::ESP::lua && !H::ESP::IsBlackListedModel(Ent->GetLuaScriptName())) || (Ent->IsNPC() && HackVars::Visuals::ESP::npc)) && !me)
				{
					if (HackVars::Visuals::ESP::LuaBox)
					{
						if (HackVars::Visuals::ESP::LuaBoxStyle == 0)
						{
							H::Draw::DrawOutlineRect(x, y, w, h, HackVars::Visuals::ESP::fPBoxColor);
							H::Draw::DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, HackVars::Visuals::ESP::fPBoxColor);
						}
						else if (HackVars::Visuals::ESP::LuaBoxStyle == 1)
						{
							int VertLine1;
							int HorzLine1;
							VertLine1 = (((float)w) * (0.2f));
							HorzLine1 = (((float)h) * (0.2f));

							H::Draw::DrawOutlineRect(x, y - 1, VertLine1, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - VertLine1, y - 1, VertLine1, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x, y + h - 1, VertLine1, 1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - VertLine1, y + h - 1, VertLine1, 1, Color(10, 10, 10, 150));

							H::Draw::DrawOutlineRect(x - 1, y, 1, HorzLine1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x - 1, y + h - HorzLine1, 1, HorzLine1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - 1, y, 1, HorzLine1, Color(10, 10, 10, 150));
							H::Draw::DrawOutlineRect(x + w - 1, y + h - HorzLine1, 1, HorzLine1, Color(10, 10, 10, 150));

							H::Draw::DrawOutlineRect(x, y, VertLine1, 1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x + w - VertLine1, y, VertLine1, 1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x, y + h, VertLine1, 1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x + w - VertLine1, y + h, VertLine1, 1, HackVars::Visuals::ESP::fLBoxColor);

							H::Draw::DrawOutlineRect(x, y, 1, HorzLine1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x, y + h - HorzLine1, 1, HorzLine1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x + w, y, 1, HorzLine1, HackVars::Visuals::ESP::fLBoxColor);
							H::Draw::DrawOutlineRect(x + w, y + h - HorzLine1, 1, HorzLine1, HackVars::Visuals::ESP::fLBoxColor);
						}
					}
					if (HackVars::Visuals::ESP::LuaDrawName)
					{
						if (Ent->UsesLua())
							H::Draw::Drawtext(Ent->GetLuaScriptName(), HackVars::Fonts::DefaultFont, left, top + 2);
						else if (Ent->IsNPC())
							H::Draw::Drawtext("NPC", HackVars::Fonts::DefaultFont, left, top + 2);
					}

					if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::LuaDrawHealth)
						H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, left, top + 17, Color(255, 0, 0, 255));

				}
		}
		void FovCircle(float fov)
		{
			// wont be accurate around the edges when the aimbot fov is high, not like that matters.
			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);
			if (fov > 180)
				fov = 180;
			H::Draw::DrawCircle(scrw / 2, scrh / 2, tan(DEG2RAD(fov) / 2) / tan(DEG2RAD(HackVars::FOV) / 2) * scrw, 100, Color(255, 255, 255, 255));
		}
		void DrawAimbotTargetLine()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);

			Vector2D Screen;

			if (!Util::Math::WorldToScreen(HackVars::Aimbot::AimbotPos, Screen))
				return;

			H::Draw::DrawLine(scrw / 2, scrh, Screen.x, Screen.y, Color(0, 255, 0, 255));
		}
		void DrawAimbotTarget()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			player_info_t player_info;
			if (engine()->GetPlayerInfo(HackVars::Aimbot::AimbotTarget->entIndex(), &player_info))
			{
				H::Draw::Drawtext("Target: ", HackVars::Fonts::DefaultFont, 0, 0);
				H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, 45, 0);
			}
			DrawAimbotTargetLine();
		}
		void DrawFreeCam()
		{
			//int scrw, scrh; engine()->GetScreenSize(scrw, scrh);
			C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			if (!LocalPlayer || !engine()->IsConnected() || !engine()->IsInGame() || !HackVars::Visuals::Enabled || !HackVars::Visuals::ESP::PlayerESP)
				return;
			//H::Draw::DrawtextBig("FreeCam", 2, 0, 0, Color(255,0,0,255));
			DrawBoundingBox(LocalPlayer,LocalPlayer, false, true);
		}
		void NightMode()
		{
			C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			static std::string old_Skyname = "";
			static bool OldNightmode;
			static int OldSky;
			if (!LocalPlayer || !engine()->IsConnected() || !engine()->IsInGame())
			{
				old_Skyname = "";
				OldNightmode = false;
				OldSky = 0;
				return;
			}
			static ConVar*r_DrawSpecificStaticProp;
			if (OldNightmode != HackVars::Visuals::Nightmode)
			{
				if (!r_DrawSpecificStaticProp)
					r_DrawSpecificStaticProp = CVar()->FindVar("r_DrawSpecificStaticProp");
				r_DrawSpecificStaticProp->SetValue(0);
				for (MaterialHandle_t i = MaterialSystem()->FirstMaterial(); i != MaterialSystem()->InvalidMaterial(); i = MaterialSystem()->NextMaterial(i))
				{
					IMaterial* pMaterial = MaterialSystem()->GetMaterial(i);
					if (!pMaterial)
						continue;
					if (strstr(pMaterial->GetTextureGroupName(), "World") || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
					{
						if (HackVars::Visuals::Nightmode)
							if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
								pMaterial->ColorModulate(0.3f, 0.3f, 0.3f);
							else
								pMaterial->ColorModulate(0.2f, 0.2f, 0.2f);
						else
							pMaterial->ColorModulate(1.0f, 1.0f, 1.0f);
					}
				}
				OldNightmode = HackVars::Visuals::Nightmode;
			}
		}
	};

};
void DrawChams()
{
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
	//BaseEntity* Ent = (BaseEntity*)cliententitylist()->GetClientEntity(pInfo.entity_index);
	//const char* ModelName = ModelInfo()->GetModelName((model_t*)pInfo.pModel);
	const CViewSetup &view = *ViewRender()->GetPlayerViewSetup();

	float colormod[3];
	colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;

	IMaterial* DebugWhite = MaterialSystem()->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
	DebugWhite->AddRef();

	IMaterial* WireFrame = MaterialSystem()->FindMaterial("models/wireframe", TEXTURE_GROUP_MODEL);
	WireFrame->AddRef();

	Render()->Push3DView(view, 0, nullptr, ViewRender()->GetFrustum());
	if (HackVars::Visuals::ESP::PlayerESP && HackVars::Visuals::ESP::PlayerChamsEnabled)
	{
		for (int i = 1; i <= globals()->maxClients; i++) {
			C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);

			if (!player || !player->IsPlayer() || !player->IsAlive() || player == LocalPlayer || HackVars::Visuals::ESP::espnotarget[i])
				continue;
			if (HackVars::Visuals::ESP::pUnlimDist || (LocalPlayer->m_vecOrigin().DistTo(player->m_vecOrigin()) <= (float)HackVars::Visuals::ESP::pMaxDist))
			{
				if (HackVars::Visuals::ESP::PlayerChamsEnabled)
				{
					if (HackVars::Visuals::ESP::PlayerChamsStyle == 0)
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
					else if (HackVars::Visuals::ESP::PlayerChamsStyle == 1)
					{
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
					}
					WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					if (HackVars::Visuals::ESP::PlayerChamsStyle == 0 || HackVars::Visuals::ESP::PlayerChamsStyle == 1)
						ModelRender()->ForcedMaterialOverride(DebugWhite);
					//else if (HackVars::Visuals::ESP::PlayerChamsStyle == 2)
					//	ModelRender()->ForcedMaterialOverride(WireFrame);
					if (HackVars::Visuals::ESP::esphighlight[i])
					{
						colormod[0] = HackVars::Visuals::ESP::fPHBoxColor[0]; colormod[1] = HackVars::Visuals::ESP::fPHBoxColor[1]; colormod[2] = HackVars::Visuals::ESP::fPHBoxColor[2];
					}
					else
					{
						colormod[0] = HackVars::Visuals::ESP::fVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVPlayerChamsColor[2];
					}
					renderview()->SetColorModulation(colormod);
					player->GetClientRenderable()->DrawModel(STUDIO_RENDER);
					ModelRender()->ForcedMaterialOverride(nullptr);
				}
			}
		}
	}
	if ((HackVars::Visuals::ESP::LuaESP && HackVars::Visuals::ESP::LuaChamsEnabled) || (HackVars::Visuals::ESP::WeaponESP && HackVars::Visuals::ESP::WeaponChamsEnabled)) {
		for (int i = globals()->maxClients; i <= cliententitylist()->GetHighestEntityIndex(); i++)
		{
			BaseEntity* ent = (BaseEntity*)cliententitylist()->GetClientEntity(i);
			if (!ent || ent->IsDormant() || ent->IsWorld() || H::ESP::IsBlackListedModel(ent->GetLuaScriptName()))
				continue;
			if ((((ent->UsesLua() && HackVars::Visuals::ESP::lua) || (ent->IsNPC() && HackVars::Visuals::ESP::npc)) && !ent->hasowner() && (HackVars::Visuals::ESP::LuaChamsEnabled && HackVars::Visuals::ESP::LuaESP)))
			{
				if (HackVars::Visuals::ESP::lUnlimDist || (LocalPlayer->m_vecOrigin().DistTo(ent->m_vecOrigin()) <= (float)HackVars::Visuals::ESP::lMaxDist))
				{
					if (HackVars::Visuals::ESP::LuaChamsStyle == 0)
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
					else if (HackVars::Visuals::ESP::LuaChamsStyle == 1)
					{
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
					}
					else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
					{
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					}
					WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					if (HackVars::Visuals::ESP::LuaChamsStyle == 0 || HackVars::Visuals::ESP::LuaChamsStyle == 1)
						ModelRender()->ForcedMaterialOverride(DebugWhite);
					//else if (HackVars::Visuals::ESP::LuaChamsStyle == 2)
					//	ModelRender()->ForcedMaterialOverride(WireFrame);
					colormod[0] = HackVars::Visuals::ESP::fVLuaChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVLuaChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVLuaChamsColor[2];
					renderview()->SetColorModulation(colormod);
					ent->GetClientRenderable()->DrawModel(STUDIO_RENDER);
					ModelRender()->ForcedMaterialOverride(nullptr);
				}
			}
			if ((!ent->UsesLua() && ent->IsWeapon() && (HackVars::Visuals::ESP::WeaponChamsEnabled && HackVars::Visuals::ESP::WeaponESP)))
			{
				if (HackVars::Visuals::ESP::wUnlimDist || (LocalPlayer->m_vecOrigin().DistTo(ent->m_vecOrigin()) <= (float)HackVars::Visuals::ESP::wMaxDist))
				{
					if (HackVars::Visuals::ESP::WeaponChamsStyle == 0)
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
					else if (HackVars::Visuals::ESP::WeaponChamsStyle == 1)
					{
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
					}
					else if (HackVars::Visuals::ESP::WeaponChamsStyle == 2)
					{
						DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					}
					DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					WireFrame->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					if (HackVars::Visuals::ESP::WeaponChamsStyle == 0 || HackVars::Visuals::ESP::WeaponChamsStyle == 1)
						ModelRender()->ForcedMaterialOverride(DebugWhite);
					colormod[0] = HackVars::Visuals::ESP::fVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVWeapChamsColor[2];
					renderview()->SetColorModulation(colormod);
					ent->GetClientRenderable()->DrawModel(STUDIO_RENDER);
					ModelRender()->ForcedMaterialOverride(nullptr);
				}
			}
		}
	}
	Render()->PopView(ViewRender()->GetFrustum());
}
void DrawESP()
{
	surface()->StartDrawing();
	BaseEntity* LocalPlayer = (BaseEntity*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	if (!LocalPlayer)
		return;

	if (HackVars::Visuals::Aimbot::FOVCircle && HackVars::Aimbot::Enabled)
		H::ESP::FovCircle(HackVars::Aimbot::FOV);

	if (HackVars::Visuals::Hitmarker)
		Interfaces::_I::HitMarkerEvent->Paint();

	if (HackVars::Visuals::Aimbot::DrawTarget)

		H::ESP::DrawAimbotTarget();
	if (HackVars::Visuals::FreeCam)
		H::ESP::DrawFreeCam();
	if (HackVars::Visuals::ESP::LuaESP) {
		for (int i = globals()->maxClients; i <= cliententitylist()->GetHighestEntityIndex(); i++)
		{
			BaseEntity* ent = (BaseEntity*)cliententitylist()->GetClientEntity(i);
			if (!ent || ent->IsDormant() || ent->IsWorld())
				continue;

			if ((((ent->UsesLua() && HackVars::Visuals::ESP::lua) || (ent->IsNPC() && HackVars::Visuals::ESP::npc)) && !ent->hasowner() && (HackVars::Visuals::ESP::LuaBox || HackVars::Visuals::ESP::LuaDrawHealth || HackVars::Visuals::ESP::LuaDrawName)))
				if (HackVars::Visuals::ESP::lUnlimDist || (LocalPlayer->m_vecOrigin().DistTo(ent->m_vecOrigin()) <= (float)HackVars::Visuals::ESP::lMaxDist))
				{
					H::ESP::DrawBoundingBox(ent, LocalPlayer);
				}
		}
	}
	if (HackVars::Visuals::ESP::PlayerESP) {
		for (int i = 1; i <= globals()->maxClients; i++)
		{
			C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);
			if (!player || !player->IsPlayer() || player->IsDormant())
				continue;

			if (player == LocalPlayer || !player->IsAlive() || HackVars::Visuals::ESP::espnotarget[i])
				continue;

			if (player->ShouldDraw()) {
				if (HackVars::Visuals::ESP::PlayerBox || HackVars::Visuals::ESP::PlayerDrawHealth || HackVars::Visuals::ESP::PlayerDrawHealth)
					if (HackVars::Visuals::ESP::pUnlimDist || (LocalPlayer->m_vecOrigin().DistTo(player->m_vecOrigin()) <= (float)HackVars::Visuals::ESP::pMaxDist))
					{
						if (HackVars::Visuals::ESP::esphighlight[i])
							H::ESP::DrawBoundingBox(player, LocalPlayer, true);
						else
							H::ESP::DrawBoundingBox(player, LocalPlayer);
					}
			}
		}
	}
	surface()->FinishDrawing();
}