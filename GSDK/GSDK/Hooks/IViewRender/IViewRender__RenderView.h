typedef void(__thiscall* RenderViewFn)(void*, CViewSetup&,int,int);
RenderViewFn orgRenderView = nullptr;




void __fastcall hookRenderView(IViewRender* ViewRender, void* edx, CViewSetup& view,int nClearFlags, int whatToDraw)
{
	//static BYTE* IsRecordingMovie = *(BYTE**)(Util::Pattern::FindPattern("engine.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? D9 45 18"/*CL_StartMovie*/) + 0x3E);
	//if (engine()->IsTakingScreenshot() || *IsRecordingMovie) // steam screenshot & startmovie checks
	//	return orgRenderView(ViewRender, view, nClearFlags, whatToDraw);
	if (!allow)
		return orgRenderView(ViewRender, view, nClearFlags, whatToDraw);
	if (!HackVars::Visuals::Enabled)
	{
		return orgRenderView(ViewRender, view, nClearFlags, whatToDraw);
	}
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	if (HackVars::Visuals::FreeCam)
	{
		if (H::savedPos == Vector())
		{
			ViewAngles = LocalPlayer->GetRenderAngles();
			H::savedPos = LocalPlayer->EyePosition();
		}
		if (!Input()->m_fCameraInThirdPerson)
			Input()->m_fCameraInThirdPerson = true;
		if (HackVars::Visuals::FreeCam && H::savedPos != Vector()) {
			H::savedPos = H::FreeCam(view);
		}
		else {
			H::savedPos = view.origin;
		}

		view.origin = H::savedPos;
		return orgRenderView(ViewRender, view, nClearFlags, whatToDraw);

	}
	else
	{
		if (H::savedPos != Vector())
		{
			H::savedPos = Vector();
			Input()->m_fCameraInThirdPerson = false;
		}
			
	}
	
	

	//C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	if (!HackVars::Visuals::RenderView::Enabled && !HackVars::Aimbot::Norecoil)
	{
		return orgRenderView(ViewRender, view, nClearFlags, whatToDraw);
	}
	view.angles = ViewAngle;
	if (HackVars::Visuals::RenderView::ThirdPerson && LocalPlayer && HackVars::Visuals::RenderView::Enabled)
	{
		Input()->m_fCameraInThirdPerson = true;
		float radx = DEG2RAD(view.angles.x); float rady = DEG2RAD(view.angles.y);
		Vector fwdzinvert = Vector(cos(radx) * cos(rady), cos(radx) * sin(rady), sin(radx) * -1);

		trace_t trace;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = LocalPlayer;
		ray.Init(view.origin, view.origin - (fwdzinvert * HackVars::Visuals::RenderView::ThirdPersonDistance), Vector(-7, -7, -7), Vector(7, 7, 7));
		EngineTrace()->TraceRay(ray, MASK_SOLID, &filter, &trace);

		view.origin = trace.endpos;
	}
	else
		Input()->m_fCameraInThirdPerson = false;
	if (HackVars::Visuals::RenderView::EnableFOV && HackVars::Visuals::RenderView::Enabled)
	{
		view.fov = HackVars::Visuals::RenderView::FOV;
		HackVars::FOV = view.fov;
	}
	if (HackVars::Visuals::RenderView::EnableViewFOV && HackVars::Visuals::RenderView::Enabled)
	{
		view.fovViewmodel = HackVars::Visuals::RenderView::ViewModelFOV;
	}
	
	if(HackVars::CurCmd) {
		QAngle eye = H::Util::Math::FixAngles(HackVars::CurCmd->viewangles);
		LocalPlayer->EyeAngles() = eye; LocalPlayer->LocalEyeAngles() = eye;
		LocalPlayer->GetAnimState()->m_DebugAnimData.m_flAimPitch = eye.x;
		LocalPlayer->GetAnimState()->m_DebugAnimData.m_flAimYaw = eye.y;
		LocalPlayer->GetAnimState()->m_flEyePitch = eye.x;
		LocalPlayer->GetAnimState()->m_flEyeYaw = eye.y;
		LocalPlayer->GetAnimState()->Update(eye.y, eye.x);
		LocalPlayer->GetAnimState()->m_angRender.y = LocalPlayer->GetAnimState()->m_flCurrentFeetYaw;
	}
	return orgRenderView(ViewRender,view,nClearFlags,whatToDraw);
}
