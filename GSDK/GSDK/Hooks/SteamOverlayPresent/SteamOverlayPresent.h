decltype(Hook::SteamOverlayPresent) Hook::SteamOverlayPresent = nullptr;

HRESULT STDMETHODCALLTYPE Hook::SteamOverlayPresent_hook(IDirect3DDevice9* thisptr, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region)
{

	if (engine()->IsInGame())
	{
		if (HackVars::Visuals::Enabled)
		{
			BaseEntity* LocalPlayer = (BaseEntity*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			if (LocalPlayer)
			{
				
			}
		}
	}

	return Hook::SteamOverlayPresent(thisptr, src, dest, wnd_override, dirty_region);
}