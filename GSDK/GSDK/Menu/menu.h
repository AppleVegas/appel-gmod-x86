#include "included.h"
#define TABWIDTH 65
#define TABWHEIGHT 30
TextEditor editor;

namespace Menu
{
	bool initialised = false;
	bool linitialised = false;
	bool opened = false;
	bool openede = false;
	bool openeda = false;
	bool openedp = false;
	bool openedh = false;
	bool savede = false;
	bool loade = false;
	bool InsertDown = false;
	int tab = 1;
	int n_open = 0;
	int n1 = false;
	int n2 = false;
	int n3 = false;
	void DrawMenu()
	{
		ImGui::GetIO().MouseDrawCursor = 0;

		if (!opened)
			return;
		SetCursor(NULL);
		if (ImGui::Begin("Appel", &opened, ImVec2(350, 500), 0.8f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::GetIO().MouseDrawCursor = 1;
			
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Aimbot", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 1;
				ImGui::SameLine();
				if (ImGui::Button("HvH", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 2;
				ImGui::SameLine();
				if (ImGui::Button("Visuals", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 3;
				ImGui::SameLine();
				if (ImGui::Button("Players", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 5;
				ImGui::SameLine();
				if (ImGui::Button("Script", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 4;
				ImGui::SameLine();
				if (ImGui::Button("Settings", ImVec2(TABWIDTH, TABWHEIGHT))) tab = 6;
			}
			ImGui::EndGroup();
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
				if (tab == 1)
				{
					if (ImGui::CollapsingHeader("Aimbot", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						ImGui::Checkbox("Enable Aimbot", &HackVars::Aimbot::Enabled);
						ImGui::Spacing();

						ImGui::SliderInt("Aimbot FOV", &HackVars::Aimbot::FOV, 0, 360);
						ImGui::Checkbox("FOV Circle", &HackVars::Visuals::Aimbot::FOVCircle);
						ImGui::SameLine();
						ImGui::Checkbox("Draw Target", &HackVars::Visuals::Aimbot::DrawTarget);
						//ImGui::SameLine();
						//ImGui::Checkbox("Enemy Only", &HackVars::Aimbot::EnemyOnly);
						ImGui::Checkbox("Aim On Shoot", &HackVars::Aimbot::AimOnShoot);
						if (!HackVars::Aimbot::AimOnShoot) {
							ImGui::Checkbox("Aimbot HotKey", &HackVars::Aimbot::HEAimbot);
							if (HackVars::Aimbot::HEAimbot)
								ImGui::Hotkey(" Aimbot HotKey", &HackVars::Aimbot::HAimbot, ImVec2(103, 18));
							ImGui::Checkbox("Aim Always", &HackVars::Aimbot::Always);
							ImGui::Checkbox("Autoshoot", &HackVars::Aimbot::Autoshoot);
						}
						else {
							HackVars::Aimbot::Always = false;
						}
						ImGui::Checkbox("Silent Aim", &HackVars::Aimbot::Silent);
						ImGui::SameLine();
						ImGui::Checkbox("No recoil", &HackVars::Aimbot::Norecoil);
						ImGui::SameLine();
						ImGui::Checkbox("No spread", &HackVars::Aimbot::Nospread);
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Checkbox("Unlimited Distance", &HackVars::Aimbot::UnlimDist);
						if (!HackVars::Aimbot::UnlimDist)
						{
							ImGui::Spacing();
							ImGui::SliderFloat(" > Max Dist", &HackVars::Aimbot::MaxDist, 0.0f, 4000.f, ("%.1f"));
							ImGui::Spacing();
						}
					}
				}
				else if (tab == 2)
				{
					if (ImGui::CollapsingHeader("HvH", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						ImGui::Checkbox("Enable AntiAim", &HackVars::HvH::AntiaimEnabled);
						const char* AntiAimS[]
						{
							"Linear",
							"Random",
							"Spinning",
							"Freak Out"
						};

						ImGui::Text("Anti-Aim Style");
						ImGui::Combo("##antiaimstyle", &HackVars::HvH::Antiaimstyle, AntiAimS, ARRAYSIZE(AntiAimS));
						if (HackVars::HvH::Antiaimstyle == 2)
						{
							ImGui::Spacing();
							ImGui::SliderFloat("Spin Speed", &HackVars::HvH::AntiaimSpinSpeed, 1.0f, 100.f, ("%.f"));
						}
						ImGui::Spacing();
					}
				}
				else if (tab == 3)
				{
					if (ImGui::CollapsingHeader("Visuals", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						ImGui::Checkbox("Enable ", &HackVars::Visuals::Enabled);
						ImGui::Spacing();
						ImGui::Checkbox("HitMarker ", &HackVars::Visuals::Hitmarker);
						ImGui::Spacing();
						ImGui::Checkbox("Fullbright ", &HackVars::Visuals::Fullbright);
						//ImGui::Spacing();
						//ImGui::Checkbox("Minecraftify ", &HackVars::Visuals::Minecraftify);
						ImGui::Spacing();
						ImGui::Checkbox("Rainbow map ", &HackVars::Visuals::Rainbowmap);
						ImGui::Spacing();
						//ImGui::Checkbox("Gray map ", &HackVars::Visuals::Graymap);
						//ImGui::Spacing();
						ImGui::Checkbox("FreeCam", &HackVars::Visuals::FreeCam);
						ImGui::SameLine();
						ImGui::Checkbox("Freecam HotKey", &HackVars::Visuals::HEFreeCam);
						if (HackVars::Visuals::HEFreeCam)
							ImGui::Hotkey(" FreeCam HotKey", &HackVars::Visuals::HFreeCam, ImVec2(103,18));
						if (HackVars::Visuals::FreeCam)
							ImGui::SliderInt("FreeCam Speed", &HackVars::Visuals::FreeCamSpeed, 10, 100);
						ImGui::Spacing();
						if (ImGui::CollapsingHeader("Eyes"))
						{
							ImGui::Spacing();
							ImGui::Checkbox("Nightmode", &HackVars::Visuals::Nightmode);
							ImGui::Spacing();
							ImGui::Checkbox("Wireframe Hands", &HackVars::Visuals::HandsEnabled);
							ImGui::ColorEdit4("Color", HackVars::Visuals::WireframeHandsColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							ImGui::Spacing();
							ImGui::Checkbox("Enable Camera Mods", &HackVars::Visuals::RenderView::Enabled);
							if (HackVars::Visuals::RenderView::Enabled)
							{
								ImGui::Spacing();
								ImGui::Checkbox("ThirdPerson (F6)", &HackVars::Visuals::RenderView::ThirdPerson);
								ImGui::SliderInt("Distance", &HackVars::Visuals::RenderView::ThirdPersonDistance, 0, 500);
								ImGui::Spacing();
								ImGui::Checkbox("Enable FOV", &HackVars::Visuals::RenderView::EnableFOV);
								ImGui::SliderInt("FOV", &HackVars::Visuals::RenderView::FOV, 0, 180);
								ImGui::Checkbox("Enable View FOV", &HackVars::Visuals::RenderView::EnableViewFOV);
								ImGui::SliderInt("Viewmodel FOV", &HackVars::Visuals::RenderView::ViewModelFOV, 0, 180);
							}
						}
						if (ImGui::CollapsingHeader("Player"))
						{
							ImGui::Spacing();
							ImGui::Checkbox("Enable Player ESP", &HackVars::Visuals::ESP::PlayerESP);
							ImGui::Spacing(); ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
							ImGui::Checkbox("Draw Box ##p", &HackVars::Visuals::ESP::PlayerBox);
							ImGui::SameLine();
							ImGui::Checkbox("Draw Name ##p", &HackVars::Visuals::ESP::PlayerDrawname);
							ImGui::SameLine();
							ImGui::Checkbox("Draw HP ##p", &HackVars::Visuals::ESP::PlayerDrawHealth);
							ImGui::Checkbox("Draw Distance ##p", &HackVars::Visuals::ESP::PlayerDrawDist);

							const char* BoxStyles[]
							{
								"Normal",
								"Corner"
							};

							ImGui::Text("Box Style");
							ImGui::Combo("##boxstylepl", &HackVars::Visuals::ESP::PlayerBoxStyle, BoxStyles, ARRAYSIZE(BoxStyles));
							ImGui::Checkbox("Health Bar", &HackVars::Visuals::ESP::PlayerDrawHealthBar);
							ImGui::Checkbox("Unlimited Distance ##p", &HackVars::Visuals::ESP::pUnlimDist);
							if (!HackVars::Visuals::ESP::pUnlimDist)
							{
								ImGui::Spacing();
								ImGui::SliderFloat(" > Max Dist ##pl", &HackVars::Visuals::ESP::pMaxDist, 0.0f, 4000.f, ("%.1f"));
								ImGui::Spacing();
							}
							ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
							ImGui::Checkbox("Chams", &HackVars::Visuals::ESP::PlayerChamsEnabled);
							//ImGui::Checkbox("XQZ", &HackVars::Visuals::ESP::PlayerXQZ);
							const char* ChamStyles[]
							{
								"Normal",
								"Flat",
								//"Wireframe",
								"Game"
							};

							ImGui::Text("Chams Style");
							ImGui::Combo("##chamsstylepl", &HackVars::Visuals::ESP::PlayerChamsStyle, ChamStyles, ARRAYSIZE(ChamStyles));
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();
						}

						if (ImGui::CollapsingHeader("Entities"))
						{
							ImGui::Spacing();
							ImGui::Checkbox("Enable Entity ESP", &HackVars::Visuals::ESP::LuaESP);
							ImGui::Spacing(); ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
							ImGui::Checkbox("Lua Entities ##l", &HackVars::Visuals::ESP::lua);
							ImGui::SameLine();
							ImGui::Checkbox("NPCs ##l", &HackVars::Visuals::ESP::npc);
							ImGui::Spacing();
							ImGui::Checkbox("Draw Box ##l", &HackVars::Visuals::ESP::LuaBox);
							ImGui::SameLine();
							ImGui::Checkbox("Draw Name ##l", &HackVars::Visuals::ESP::LuaDrawName);
							ImGui::SameLine();
							ImGui::Checkbox("Draw HP ##l", &HackVars::Visuals::ESP::LuaDrawHealth);
							const char* BoxStyles2[]
							{
								"Normal",
								"Corner"
							};

							ImGui::Text("Box Style");
							ImGui::Combo("##boxstylelua", &HackVars::Visuals::ESP::LuaBoxStyle, BoxStyles2, ARRAYSIZE(BoxStyles2));
							ImGui::Checkbox("Unlimited Distance ##lua", &HackVars::Visuals::ESP::lUnlimDist);
							if (!HackVars::Visuals::ESP::lUnlimDist)
							{
								ImGui::Spacing();
								ImGui::SliderFloat(" > Max Dist ##lua", &HackVars::Visuals::ESP::lMaxDist, 0.0f, 4000.f, ("%.1f"));
								ImGui::Spacing();
							}
							ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
							ImGui::Checkbox("Chams ##lua", &HackVars::Visuals::ESP::LuaChamsEnabled);
							//ImGui::SameLine();
							//ImGui::Checkbox("XQZ ", &HackVars::Visuals::ESP::LuaXQZ);
							const char* ChamStyles2[]
							{
								"Normal",
								"Flat",
								//"Wireframe",
								"Game"
							};

							ImGui::Text("Chams Style");
							ImGui::Combo("##chamsstylelua", &HackVars::Visuals::ESP::LuaChamsStyle, ChamStyles2, ARRAYSIZE(ChamStyles2));
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();
						}
						if (ImGui::CollapsingHeader("Weapons"))
						{
							ImGui::Spacing();
							ImGui::Checkbox("Enable Chams", &HackVars::Visuals::ESP::WeaponESP);
							ImGui::Spacing();
							//ImGui::SameLine();
							ImGui::Checkbox("Chams ##wep", &HackVars::Visuals::ESP::WeaponChamsEnabled);
							//ImGui::SameLine();
							//ImGui::Checkbox("XQZ  ", &HackVars::Visuals::ESP::WeaponXQZ);
							const char* ChamStyles3[]
							{
								"Normal",
								"Flat",
								"Game"
							};

							ImGui::Text("Chams Style");
							ImGui::Combo("##chamsstylewep", &HackVars::Visuals::ESP::WeaponChamsStyle, ChamStyles3, ARRAYSIZE(ChamStyles3));
							ImGui::Checkbox("Unlimited Distance ##wep", &HackVars::Visuals::ESP::wUnlimDist);
							if (!HackVars::Visuals::ESP::wUnlimDist)
							{
								ImGui::Spacing();
								ImGui::SliderFloat(" > Max Dist ##wep", &HackVars::Visuals::ESP::wMaxDist, 0.0f, 4000.f, ("%.1f"));
								ImGui::Spacing();
							}
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

						}
					}
				}
				else if (tab == 4)
				{
					if (ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						if (ImGui::Button("Lua Editor"))
						{
							openede = true;
						}
						ImGui::Spacing();
						ImGui::Checkbox("Catch Lua", &HackVars::Script::Catch_Lua);
						ImGui::Spacing();
						ImGui::Checkbox("Log net.Receive", &HackVars::Script::Log_Net);
						//if (HackVars::Script::Log_Net)
						//{
						//	if (!n2)
						//	{
						//		std::string sett = openFile("garrysmod/cl").c_str();
						//		sett[1] = '1';
						//		createFile("garrysmod/cl", sett);
						//		n2 = true;
						//	}
						//}
						//else
						//{
						//	if (n2)
						//	{
						//		std::string sett = openFile("garrysmod/cl").c_str();
						//		sett[1] = '0';
						//		createFile("garrysmod/cl", sett);
						//		n2 = false;
						//	}
						//}
						ImGui::Spacing();
						ImGui::Checkbox("Steal Lua", &HackVars::Script::Steal_Lua);
						if (HackVars::Script::Steal_Lua)
						{
							ImGui::SameLine();
							ImGui::Checkbox("Logging", &HackVars::Script::Steal_Lua_Log);
						}
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("Protection:");
						ImGui::Checkbox("Block SendLua", &HackVars::Script::Block_SendLua);
						ImGui::Spacing();
						ImGui::Checkbox("Block net.Receive", &HackVars::Script::Block_Net);
						//ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("Buffs:");
						ImGui::Checkbox("AutoHeal", &HackVars::Script::AutoHeal);
						if (HackVars::Script::AutoHeal)
						{
							ImGui::SliderInt(" > Minumum Health ##pl", &HackVars::Script::AutoHealMin, 1, 99);
							ImGui::SliderInt(" > Tick Count ##pl", &HackVars::Script::AutoHealTick, 0, 50);
						}
						ImGui::Spacing();
						ImGui::Checkbox("Physgun Tricks", &HackVars::Script::PropBoost);
						if (HackVars::Script::PropBoost)
							ImGui::Hotkey(" Trick HotKey", &HackVars::Script::HPropBoost, ImVec2(103, 18));
						const char* tricksm[]
						{
							"Prop Boost",
							"Prop Boost 2",
							"Prop Walk"
						};
						ImGui::Combo("##trickmodes", &HackVars::Script::MPropBoost, tricksm, ARRAYSIZE(tricksm));
						ImGui::SameLine();
						ImGui::Text("Trick Mode");
						//ImGui::Checkbox("AutoArmor", &HackVars::Script::AutoArmor);
						//if (HackVars::Script::AutoArmor)
						//	ImGui::SliderInt(" > Minumum Armor ##pl", &HackVars::Script::AutoArmorMin, 1, 99);
						//ImGui::Spacing();
						//ImGui::Separator();
						//ImGui::Spacing();
						//ImGui::Text("Name Changer:");
						//ImGui::InputText("##NameField", HackVars::Script::Name, 32);
						//ImGui::Spacing();
						//if (ImGui::Button("Change Name"))
						//{
						//	HackVars::Script::ChatClear = true;
						//}
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("Spammers:");
						ImGui::Spacing();
						ImGui::Checkbox("Use", &HackVars::Script::Uspam);
						ImGui::SameLine();
						ImGui::Checkbox("Flashlight", &HackVars::Script::Fspam);
						ImGui::SameLine();
						ImGui::Checkbox("Attack1", &HackVars::Script::A1Spam);
						ImGui::SameLine();
						ImGui::Checkbox("Attack2", &HackVars::Script::A2Spam);
						ImGui::SameLine();
						ImGui::Checkbox("Rope", &HackVars::Script::RopeSpam);
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Checkbox("Bunnyhop", &HackVars::Script::Bunnyhop);
						ImGui::Spacing();
						ImGui::Checkbox("Followbot (Key B)", &HackVars::Script::FollowBot::Enabled);
						ImGui::Spacing();
						if (HackVars::Script::FollowBot::Enabled)
						{
							ImGui::SliderFloat(" > Max Dist", &HackVars::Script::FollowBot::MaxDist, 0.0f, 1000.f, ("%.1f"));
							ImGui::SliderFloat(" > Min Dist", &HackVars::Script::FollowBot::MinDist, 0.0f, 1000.f, ("%.1f"));
						}
					}
					//if (ImGui::CollapsingHeader("Developer", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
					//{
					//ImGui::InputText("Test", &HackVars::Developer::Text, 2);
					//}
				}
				else if (tab == 5)
				{
					if (ImGui::CollapsingHeader("Players", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						static int currentPlayer = -1;

						C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

						if (!engine()->IsInGame())
							currentPlayer = -1;

						ImGui::ListBoxHeader("", ImVec2(310, 200));
						ImGui::Columns(3);

						ImGui::Text("ID");
						ImGui::NextColumn();

						ImGui::Text("Nickname");
						ImGui::NextColumn();

						ImGui::Text("Weapon");
						ImGui::NextColumn();

						if (engine()->IsInGame())
						{
							for (int i = 1; i <= globals()->maxClients; i++)
							{
								C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);

								if (!player || player == LocalPlayer || !player->IsPlayer())
									continue;
								player_info_t player_info;
								if (engine()->GetPlayerInfo(player->entIndex(), &player_info))
								{
									//std::cout << CCPlayerResource()->GetArmor(i) << std::endl;
									if (ImGui::Selectable(std::to_string(i).c_str(), i == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
										currentPlayer = i;
									ImGui::NextColumn();
								
									ImGui::Text(player_info.name);
									ImGui::NextColumn();
								
									//CBaseCombatWeapon* ActiveWeapon = player->GetActiveWeapon();
									//if (ActiveWeapon)
									//{
										char const* name = "disabled_feature";//ActiveWeapon->GetName();
										if (name)
											ImGui::Text(name);
										else
											ImGui::Text("none");
									//}
									//else
									//	ImGui::Text("none");
									ImGui::NextColumn();
								}


							}
						}
						ImGui::ListBoxFooter();
						ImGui::SameLine();
						if (ImGui::BeginChild("inside", ImVec2(-1, 200)))
						{
							if (currentPlayer != -1)
							{
								ImGui::Checkbox("Aimbot Ignore", &HackVars::Aimbot::aimbotnotarget[currentPlayer]);
								ImGui::Checkbox("ESP HighLight", &HackVars::Visuals::ESP::esphighlight[currentPlayer]);
								ImGui::Checkbox("ESP Ignore", &HackVars::Visuals::ESP::espnotarget[currentPlayer]);
							}
							else
							{
								ImGui::Text("No Player Selected");
							}
						}
						ImGui::EndChild();
						ImGui::Spacing();
					}
				}
				else if (tab == 6)
				{
					if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
					{
						ImGui::Spacing();
						if (ImGui::Button("Test"))
						{
							C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
							//CBaseCombatWeapon* Weapon = LocalPlayer->GetActiveWeapon();
							int armor = *(int*)((uintptr_t)LocalPlayer + offsets::DT_PlayerResource::m_iArmor);
							//CBaseHandle* hActiveWeapon = (CBaseHandle*)((uintptr_t)LocalPlayer + offsets::DT_BaseCombatCharacter::m_hActiveWeapon);
							std::cout << armor << "\n";
						}
						ImGui::Checkbox("Safe Mode", &HackVars::Other::SafeMode);
						ImGui::Spacing();
						if (ImGui::Button("Save Settings"))
						{
							SaveSettings();
						}
						ImGui::Spacing();
						if (ImGui::Button("Load Settings"))
						{
							LoadSettings();
						}
						ImGui::Spacing();
						if (ImGui::Button("Reset Settings"))
						{
							ResetSettings();
						}
						ImGui::Spacing();
						ImGui::Spacing();
						if (ImGui::CollapsingHeader("Player ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
						{
							ImGui::ColorEdit4("Box Color ##p", HackVars::Visuals::ESP::fPBoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							ImGui::ColorEdit4("Highlight Color", HackVars::Visuals::ESP::fPHBoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::ColorEdit4("Chams ##p", HackVars::Visuals::ESP::fVPlayerChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							//ImGui::ColorEdit4("Chams XQZ", HackVars::Visuals::ESP::fNVPlayerChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						}
						if (ImGui::CollapsingHeader("Lua Entity ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
						{
							ImGui::ColorEdit4("Box Color ##l", HackVars::Visuals::ESP::fLBoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::ColorEdit4("Chams ##l", HackVars::Visuals::ESP::fVLuaChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							//ImGui::ColorEdit4("Chams XQZ ", HackVars::Visuals::ESP::fNVLuaChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						}
						if (ImGui::CollapsingHeader("Weapons ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
						{
							ImGui::ColorEdit4("Chams ##w", HackVars::Visuals::ESP::fVWeapChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
							//ImGui::ColorEdit4("Chams XQZ  ", HackVars::Visuals::ESP::fNVWeapChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						}
						ImGui::Spacing();
					}
				}
			//fix the colors up lol.
			HackVars::Visuals::ESP::PBoxColor = Color(HackVars::Visuals::ESP::fPBoxColor);
			HackVars::Visuals::ESP::LBoxColor = Color(HackVars::Visuals::ESP::fLBoxColor);
		}
		ImGui::End();
	}
	void DrawAimbotExclude()
	{
		if (!opened)
			return;

		if (!openeda)
			return;

		if (ImGui::Begin("Hahaha", nullptr, ImVec2(500, 100), 0.8f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::Button("OK"))
			{
				openeda = false;
			}
			ImGui::Spacing();
		}
		ImGui::End();
	}
	//void DrawESPExclude()
	//{
	//	if (!opened)
	//		return;
	//
	//	if (!openedp)
	//		return;
	//}
	void DrawTextEditor()
	{
		if (!opened)
			return;

		if (!openede)
			return;

		if (!linitialised) {

			auto lang = TextEditor::LanguageDefinition::Lua();

			editor.SetLanguageDefinition(lang);
			if (dirExists("C:/Appel"))
			{
				if (fileExists("C:/Appel/appel_1.lua"))
					editor.SetText(openFile("C:/Appel/appel_1.lua"));
			}
			linitialised = true;
		}

		auto cpos = editor.GetCursorPosition();
		if (ImGui::Begin("Lua Editor", nullptr, ImVec2(500, 500), 0.8f, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse)) {
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{
					if (ImGui::MenuItem("Clear"))
					{
						editor.SetText("");
					}
					if (ImGui::MenuItem("Quit", "Alt-F4"))
					{
						openede = false;
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Save"))
				{
					if (ImGui::MenuItem("Save as"))
					{
						savede = true;
					}
					ImGui::Spacing();
					if (ImGui::MenuItem("Save in slot 1"))
					{
						auto textToSave = editor.GetText();
						if (createDir("C:/Appel"))
							createFile("C:/Appel/appel_1.lua", textToSave);
					}
					if (ImGui::MenuItem("Save in slot 2"))
					{
						auto textToSave = editor.GetText();
						if (createDir("C:/Appel"))
							createFile("C:/Appel/appel_2.lua", textToSave);
					}
					if (ImGui::MenuItem("Save in slot 3"))
					{
						auto textToSave = editor.GetText();
						if (createDir("C:/Appel"))
							createFile("C:/Appel/appel_3.lua", textToSave);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Load"))
				{
					if (ImGui::MenuItem("Load"))
					{
						loade = true;
					}
					ImGui::Spacing();
					if (ImGui::MenuItem("Load slot 1"))
					{
						if (dirExists("C:/Appel"))
						{
							if (fileExists("C:/Appel/appel_1.lua"))
								editor.SetText(openFile("C:/Appel/appel_1.lua"));
						}
					}
					if (ImGui::MenuItem("Load slot 2"))
					{
						if (dirExists("C:/Appel"))
						{
							if (fileExists("C:/Appel/appel_2.lua"))
								editor.SetText(openFile("C:/Appel/appel_2.lua"));
						}
					}
					if (ImGui::MenuItem("Load slot 3"))
					{
						if (dirExists("C:/Appel"))
						{
							if (fileExists("C:/Appel/appel_3.lua"))
								editor.SetText(openFile("C:/Appel/appel_3.lua"));
						}
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					bool ro = editor.IsReadOnly();
					if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
						editor.SetReadOnly(ro);
					ImGui::Separator();

					if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
						editor.Undo();
					if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
						editor.Redo();

					ImGui::Separator();

					if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
						editor.Copy();
					if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
						editor.Cut();
					if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
						editor.Delete();
					if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
						editor.Paste();

					ImGui::Separator();

					if (ImGui::MenuItem("Select all", nullptr, nullptr))
						editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

					ImGui::EndMenu();
				}

				//if (ImGui::BeginMenu("View"))
				//{
				//	if (ImGui::MenuItem("Dark palette"))
				//		editor.SetPalette(TextEditor::GetDarkPalette());
				//	if (ImGui::MenuItem("Light palette"))
				//		editor.SetPalette(TextEditor::GetLightPalette());
				//	if (ImGui::MenuItem("Retro blue palette"))
				//		editor.SetPalette(TextEditor::GetRetroBluePalette());
				//	ImGui::EndMenu();
				//}
				ImGui::EndMenuBar();
			}
			if (ImGui::Button("Run"))
			{
				const char* code = editor.GetText().c_str();
				
				HackVars::luascript = code;
				HackVars::runlua = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Run Menu"))
			{
				const char* code = editor.GetText().c_str();

				AppelLua::RunLua(code, true);
			}
			ImGui::SameLine();
			if (ImGui::Button("Run Before Autorun"))
			{
				auto textToSave = editor.GetText();
				RunBeforeAutorun(textToSave);
			}
			ImGui::SameLine();
			if (ImGui::Button("Clear Before Autorun script"))
			{
				ClearBeforeAutorunScript();
			}
			ImGui::SameLine();
			ImGui::Text("%6d lines  | %s", editor.GetTotalLines(), editor.CanUndo() ? "Edited" : " ");
			ImGui::Spacing();
			editor.Render("Lua Editor");
		}
		if (savede)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Save As", 0, "C:/Appel/", "appel"))
			{
				if (ImGuiFileDialog::Instance()->IsOk == true)
				{
					auto textToSave = editor.GetText();
					if (createDir("C:/Appel"))
						createFile(std::string(ImGuiFileDialog::Instance()->GetFilepathName() + ".lua").c_str(), textToSave);
				}
				else
				{
				}
				savede = false;
			}
		}
		if (loade)
		{
			if (ImGuiFileDialog::Instance()->FileDialog("Load", 0, "C:/Appel/", "appel"))
			{
				if (ImGuiFileDialog::Instance()->IsOk == true)
				{
					editor.SetText(openFile(ImGuiFileDialog::Instance()->GetFilepathName().c_str()));
				
				}
				else
				{
				}
				loade = false;
			}
		}
		ImGui::End();
	}
	void OpenMenuThing()
	{
		if (InsertDown)
		{
			n_open++;
			if (n_open == 1)
			{
				opened = !opened;
			}
		}
		else
			n_open = 0;
	}
};