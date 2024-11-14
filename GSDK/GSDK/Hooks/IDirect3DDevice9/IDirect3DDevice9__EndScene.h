typedef HRESULT(__stdcall* EndSceneFn)(IDirect3DDevice9*);
EndSceneFn orgEndScene = nullptr;
extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC orgproc = nullptr;

typedef BOOL(WINAPI* hk_SetCursorPos)(int, int);
hk_SetCursorPos orgSetCursorPos = NULL;

bool openedfully = false;
bool closedfully = false;

BOOL WINAPI hookSetCursorPos(int X, int Y)
{
	if (Menu::opened && !Menu::InsertDown)
		return FALSE;

	return orgSetCursorPos(X, Y);
}

LRESULT __stdcall proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (msg == WM_KEYDOWN)
		if (wParam == VK_INSERT){Menu::InsertDown = true;}
		
	if (msg == WM_KEYUP)
		if (wParam == VK_INSERT) { Menu::InsertDown = false; }

	ImGui_ImplDX9_WndProcHandler(hwnd, msg, wParam, lParam);

	return CallWindowProcA(orgproc, hwnd, msg, wParam, lParam);
}


HRESULT __stdcall hookEndScene(IDirect3DDevice9* device)
{
	if (!allow)
	{
		if (Menu::opened)
		{
			InputSystem()->EnableInput(true);
			surface()->SetCursorAlwaysVisible(false);
		}
		return orgEndScene(device);
	}
	if (!Menu::initialised)
	{
		auto gmod = FindWindowW(L"Valve001", nullptr);

		orgproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(gmod, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc)));
		
		ImFontConfig font_config;
		font_config.OversampleH = 1; //or 2 is the same
		font_config.OversampleV = 1;
		font_config.PixelSnapH = true;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x044F, // Cyrillic
			0,
		};
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);
		font1->DisplayOffset.y -= 1;
		ImGui_ImplDX9_Init(gmod, device);
		ImGuiStyle& style = ImGui::GetStyle();

		Menu::initialised = true;
	}
	else
	{
		if (Menu::opened)
		{
			InputSystem()->EnableInput(false);
			if (!openedfully)
			{
				surface()->SetCursorAlwaysVisible(true);
				openedfully = true;
				closedfully = false;
			}
		}
		else
		{
			
			if (!closedfully)
			{
				if (engine()->IsInGame())
				{
					int centerW, centerH;
					engine()->GetScreenSize(centerW, centerH);
					orgSetCursorPos(centerW / 2, centerH / 2);
				}
				surface()->SetCursorAlwaysVisible(false);
				closedfully = true;
				openedfully = false;
			}
			InputSystem()->EnableInput(true);
		}

		if (HackVars::Visuals::FreeCam && HackVars::Visuals::Enabled)
			InputSystem()->EnableInput(false);

		ImGui_ImplDX9_NewFrame();
		Menu::OpenMenuThing();
		Menu::DrawMenu();
		Menu::DrawAimbotExclude();
		//Menu::DrawESPExclude();
		Menu::DrawTextEditor();

		ImGui::Render();
	}
	//static bool initFonts;
	//if (!initFonts)
	//{
	//	H::Draw::pDevice = device;
	//	H::Draw::AddFont(L"Tahoma", 15, false, false);
	//	initFonts = true;
	//}
	//if (H::Draw::Font()) H::Draw::OnLostDevice();
	return orgEndScene(device);
}
