
decltype(Hook::SteamOverlayReset) Hook::SteamOverlayReset = nullptr;

HRESULT STDMETHODCALLTYPE Hook::SteamOverlayReset_hook(IDirect3DDevice9* thisptr, D3DPRESENT_PARAMETERS* params)
{
	return Hook::SteamOverlayReset(thisptr, params);
}