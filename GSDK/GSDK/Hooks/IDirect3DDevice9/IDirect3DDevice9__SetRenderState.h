typedef HRESULT(WINAPI* SetRenderStateFn)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
SetRenderStateFn orgSetRenderState = nullptr;

HRESULT WINAPI hookSetRenderState(LPDIRECT3DDEVICE9 device, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	//if (!allow)
	//{
	//	return orgSetRenderState(device, State, Value);//
	//}
	//if (fullbright)
	//{
	//printf("here");
	//device->SetRenderState(D3DRS_LIGHTING, false);
	//device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255));
	//orgSetRenderState(device, D3DRS_ZENABLE, true);
	//orgSetRenderState(device, D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255)); // use all colors to glow up the lighting ingame
	//}
	//printf(std::to_string(Value).c_str());
	//printf("\n");
	//if (State == D3DRS_LIGHTING)
	//	device->SetRenderState(D3DRS_LIGHTING, false);
	//if (nofog) // if nofog on
	//{ // then
	//	pDevice->SetRenderState(D3DRS_FOGENABLE, false); // Disable the Fog
	//} // end of then
	//if (xray)
	//{
	//	if (m_Stride == Modelrecognition) //you can define the stride like this to        
	//	{
	//		m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//	}
	//}
	return orgSetRenderState(device, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
