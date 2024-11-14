//#pragma comment(lib, "D3dx9.lib")
//struct vertex
//{
//	FLOAT x, y, z, rhw;
//	DWORD color;
//};

namespace H
{
	namespace Draw
	{
		//static LPDIRECT3DVERTEXBUFFER9  g_pVB = NULL;
		//static LPDIRECT3DINDEXBUFFER9   g_pIB = NULL;
		//enum text_alignment { lefted, centered, righted };
		//ID3DXFont *pFont;
		//IDirect3DDevice9* pDevice;
		class Vertexs
		{
		public:
			float	x = 0.f;
			float	y = 0.f;
			float	z = 0.f;
		};
		void DrawLine(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawLine(x1, y1, x2, y2);
			surface()->DrawSetColor(255, 255, 255, 255);
		}
		void DrawLine(Vector2D pos1, Vector2D pos2, Color color = Color(255, 255, 255, 255))
		{
			DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, color);
		}
		//void D_DrawLine(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, Color color = Color(255,255,255,255), bool antialias = false, int width = 1)
		//{
		//	ID3DXLine *m_Line;
		//
		//	D3DXCreateLine(pDevice, &m_Line);
		//	D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
		//	m_Line->SetWidth(width);
		//	if (antialias) m_Line->SetAntialias(1);
		//	m_Line->Begin();
		//	m_Line->Draw(line, 2, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));
		//	m_Line->End();
		//	m_Line->Release();
		//}
		//void D_DrawLinev(Vector2D pos1, Vector2D pos2, Color color, bool antialias = false, int width = 1)
		//{
		//	D_DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, color, antialias, width);
		//}
		void DrawOutlineRect(int x, int y, int w, int h, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawOutlinedRect(x, y, x + w, y + h);
			surface()->DrawSetColor(255, 255, 255, 255);
		}
		//void BoxFilled(float x, float y, float w, float h, DWORD color)
		//{
		//	vertex V[4];
		//
		//	V[0].color = V[1].color = V[2].color = V[3].color = color;
		//
		//	V[0].z = V[1].z = V[2].z = V[3].z = 0;
		//	V[0].rhw = V[1].rhw = V[2].rhw = V[3].rhw = 0;
		//
		//	V[0].x = x;
		//	V[0].y = y;
		//	V[1].x = x + w;
		//	V[1].y = y;
		//	V[2].x = x + w;
		//	V[2].y = y + h;
		//	V[3].x = x;
		//	V[3].y = y + h;
		//
		//	unsigned short indexes[] = { 0, 1, 3, 1, 2, 3 };
		//
		//	pDevice->CreateVertexBuffer(4 * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
		//	pDevice->CreateIndexBuffer(2 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);
		//
		//	VOID* pVertices;
		//	g_pVB->Lock(0, sizeof(V), (void**)&pVertices, 0);
		//	memcpy(pVertices, V, sizeof(V));
		//	g_pVB->Unlock();
		//
		//	VOID* pIndex;
		//	g_pIB->Lock(0, sizeof(indexes), (void**)&pIndex, 0);
		//	memcpy(pIndex, indexes, sizeof(indexes));
		//	g_pIB->Unlock();
		//
		//	pDevice->SetTexture(0, NULL);
		//	pDevice->SetPixelShader(NULL);
		//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//
		//	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
		//	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		//	pDevice->SetIndices(g_pIB);
		//
		//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		//
		//	g_pVB->Release();
		//	g_pIB->Release();
		//}
		//void Box(int x, int y, int w, int h, Color color, IDirect3DDevice9* pDevice)
		//{
		//	BoxFilled(x, y, w, 1, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));             // Top
		//	BoxFilled(x, y + h - 1, w, 1, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));         // Bottom
		//	BoxFilled(x, y + 1, 1, h - 2 * 1, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));       // Left
		//	BoxFilled(x + w - 1, y + 1, 1, h - 2 * 1, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));   // Right
		//}
		//void D_DrawOutlineRect(int x, int y, int w, int h, Color color)
		//{
		//	Box(x + 1, y + 1, w - 2 * 1, h - 1, color, pDevice);
		//	Box(x, y, w, h, color, pDevice);
		//	Box(x - 1, y - 1, w + 2 * 1, h + 1, color, pDevice);
		//}
		void DrawCircle(int x, int y, int radius,int segments, Color color = Color(255, 255, 255, 255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawOutlinedCircle(x, y, radius, segments);
			surface()->DrawSetColor(Color(255, 255, 255, 255));
		}
		//void D_DrawCircle(int x, int y, int r, int num, Color color)
		//{
		//	std::vector<vertex> circle(num + 2);
		//	float angle = 0*D3DX_PI / 180;
		//	float pi;
		//
		//	pi = D3DX_PI;        // Full circle
		//
		//
		//	for (int i = 0; i < num + 2; i++)
		//	{
		//		circle[i].x = (float)(x - r*cos(i*(2 * pi / num)));
		//		circle[i].y = (float)(y - r*sin(i*(2 * pi / num)));
		//		circle[i].z = 0;
		//		circle[i].rhw = 1;
		//		circle[i].color = D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a());
		//	}
		//
		//	// Rotate matrix
		//	int _res = num + 2;
		//	for (int i = 0; i < _res; i++)
		//	{
		//		circle[i].x = x + cos(angle)*(circle[i].x - x) - sin(angle)*(circle[i].y - y);
		//		circle[i].y = y + sin(angle)*(circle[i].x - x) + cos(angle)*(circle[i].y - y);
		//	}
		//
		//	pDevice->CreateVertexBuffer((num + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
		//
		//	VOID* pVertices;
		//	g_pVB->Lock(0, (num + 2) * sizeof(vertex), (void**)&pVertices, 0);
		//	memcpy(pVertices, &circle[0], (num + 2) * sizeof(vertex));
		//	g_pVB->Unlock();
		//
		//
		//	pDevice->SetTexture(0, NULL);
		//	pDevice->SetPixelShader(NULL);
		//	//if (smoothing)
		//	//{
		//	//	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		//	//	pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
		//	//}
		//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//
		//	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
		//	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		//
		//	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, num);
		//	if (g_pVB != NULL) g_pVB->Release();
		//}
		void DrawRect(int x = 0, int y = 0, int w = 100, int h = 100, Color color = Color(255,255,255,255))
		{
			surface()->DrawSetColor(color);
			surface()->DrawFilledRect(x, y, x + w, y + h);
			surface()->DrawSetColor(255, 255, 255, 255);
		}
		//void D_Drawtext(const char* text = "Sample Text", int font = 1, int x = 0, int y = 0, Color color = Color(255, 255, 255, 255), int orientation = 0, bool bordered = false, Color bcolor = Color(0, 0, 0, 255))
		//{
		//	RECT rect;
		//
		//	switch (orientation)
		//	{
		//	case lefted:
		//		if (bordered)
		//		{
		//			SetRect(&rect, x - 1, y, x - 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));
		//			SetRect(&rect, x + 1, y, x + 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y - 1, x, y - 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y + 1, x, y + 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//		}
		//		SetRect(&rect, x, y, x, y);
		//		pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));
		//		break;
		//	case centered:
		//		if (bordered)
		//		{
		//			SetRect(&rect, x - 1, y, x - 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x + 1, y, x + 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y - 1, x, y - 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y + 1, x, y + 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//		}
		//		SetRect(&rect, x, y, x, y);
		//		pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));
		//		break;
		//	case righted:
		//		if (bordered)
		//		{
		//			SetRect(&rect, x - 1, y, x - 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x + 1, y, x + 1, y);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y - 1, x, y - 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//			SetRect(&rect, x, y + 1, x, y + 1);
		//			pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_RGBA(bcolor.r(), bcolor.g(), bcolor.b(), bcolor.a()));
		//		}
		//		SetRect(&rect, x, y, x, y);
		//		pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, D3DCOLOR_RGBA(color.r(), color.g(), color.b(), color.a()));
		//		break;
		//	}
		//}
		//void AddFont(LPCWSTR Caption, float size, bool bold, bool italic)
		//{
		//	D3DXCreateFont(pDevice, size, 0, (bold) ? FW_BOLD : FW_NORMAL, 1, (italic) ? 1 : 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, Caption, &pFont);
		//}
		//bool Font()
		//{
		//	if (pFont) return false;
		//	return true;
		//}
		//void FontReset()
		//{
		//	pFont->OnLostDevice();
		//	pFont->OnResetDevice();
		//}
		//
		//void OnLostDevice()
		//{
		//	pFont->OnLostDevice();
		//}
		void Drawtext(const char* text = "Sample Text", int font = 1, int x = 0, int y = 0, Color color = Color(255,255,255,255))
		{
			//const size_t cSize = strlen(text) + 1;
			//wchar_t* wc = new wchar_t[cSize];
			va_list va_alist;
			char buf[1024];
			va_start(va_alist, text);
			_vsnprintf(buf, sizeof(buf), text, va_alist);
			va_end(va_alist);
			wchar_t wbuf[1024];
			MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
			//mbstowcs(wc, text, cSize);
			surface()->DrawSetTextFont(1);
			surface()->DrawSetTextColor(Color(0, 0, 0, 255));
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextColor(255, 255, 255, 255);
			surface()->DrawSetTextFont(font);
			surface()->DrawSetTextColor(color);
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextColor(255,255,255,255);
			//delete[] wc;
		}
		void DrawtextBig(const char* text = "Sample Text", int font = 2, int x = 0, int y = 0, Color color = Color(255, 255, 255, 255))
		{
			//const size_t cSize = strlen(text) + 1;
			//wchar_t* wc = new wchar_t[cSize];
			va_list va_alist;
			char buf[1024];
			va_start(va_alist, text);
			_vsnprintf(buf, sizeof(buf), text, va_alist);
			va_end(va_alist);
			wchar_t wbuf[1024];
			MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
			//mbstowcs(wc, text, cSize);
			surface()->DrawSetTextFont(3);
			surface()->DrawSetTextColor(Color(0, 0, 0, 255));
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextColor(255, 255, 255, 255);
			surface()->DrawSetTextFont(font);
			surface()->DrawSetTextColor(color);
			surface()->DrawSetTextPos(x, y);
			surface()->DrawPrintText(wbuf, wcslen(wbuf));
			surface()->DrawSetTextColor(255, 255, 255, 255);
			//delete[] wc;
		}
	};
	Vector savedPos = Vector();

	Vector FreeCam(CViewSetup& view)
	{
		Vector    vPos = savedPos;
		QAngle    vView = view.angles;

		FLOAT    fCos = cosf(vView.x);
		FLOAT    fSin = sinf(vView.x);


		Vector fwd, rt, up;
		AngleVectors(vView, &fwd, &rt, &up);

		float speed = HackVars::Visuals::FreeCamSpeed;

		if (GetAsyncKeyState(VK_SHIFT))
			speed *= 2;

		if (GetAsyncKeyState(VK_CONTROL))
			speed /= 4;

		if (GetAsyncKeyState(VK_SPACE))
			vPos.z += 1.0f * speed;

		if (GetAsyncKeyState(VK_LMENU))
			vPos.z -= 1.0f * speed;

		if (GetAsyncKeyState('W'))
			vPos += fwd * speed;

		if (GetAsyncKeyState('S'))
			vPos -= fwd * speed;

		if (GetAsyncKeyState('A'))
			vPos -= rt * speed;

		if (GetAsyncKeyState('D'))
			vPos += rt * speed;

		return vPos;
	}
};
