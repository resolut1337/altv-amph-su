#include <memory>
#include <D3D11.h>
#include <d3d9.h>
#include <D2D1.h>
#include <unordered_map>
#include <dwrite_1.h>
#include <string_view>//#include <../stb_image.h>
#pragma comment( lib, "dxgi" )
#pragma comment( lib, "d2d1" )
#pragma comment( lib, "dcomp" )
#pragma comment( lib, "dwrite" )
static char custmomfontname[128] = "Arial";
#define RET_CHK(x) if ( x != S_OK ) return
ID3D11ShaderResourceView * logo = NULL;
//.ID3D11ShaderResourceView* IconAvatar = NULL;
const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);
	return wc;
}
namespace Render_D2 {
	ID2D1Factory* Interface;
	ID2D1RenderTarget* Canvas;
	IDWriteFactory1* TextEngine;
	IDWriteTextFormat* TextFormat;
	IDWriteTextFormat* BigText;
	ID2D1SolidColorBrush* SolidColor;
	bool initialized = false;

	UINT wcslen(const wchar_t* Str) {
		const wchar_t* TempStr = Str;
		for (; *TempStr; ++TempStr);
		return (UINT)(TempStr - Str);
	}
	bool InitRender(IDXGISwapChain* SwapChain) {
		if (!initialized) {
			initialized = true;
			D2D1_FACTORY_OPTIONS CreateOpt = { D2D1_DEBUG_LEVEL_NONE };
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(TextEngine), (IUnknown**)&TextEngine);
			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &CreateOpt, (void**)&Interface);
			TextEngine->CreateTextFormat((L"Cunia"), NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 9.f, L"", &TextFormat);
			if (!Interface || !TextEngine || !TextFormat) return false;
		}
		ID3D11Device* d3d_device;
		if (SwapChain->GetDevice(IID_PPV_ARGS(&d3d_device))) return false;
		WORD flagsOffset = *(WORD*)((*(DWORD64**)d3d_device)[38] + 2); //x64
		int& flags = *(INT*)((DWORD64)d3d_device + flagsOffset);
		d3d_device->Release();
		IDXGISurface* d3d_bbuf;
		if (SwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d_bbuf)))
			return false;
		D2D1_RENDER_TARGET_PROPERTIES d2d_prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		flags |= 0x20; HRESULT canvas_state = Interface->CreateDxgiSurfaceRenderTarget(d3d_bbuf, d2d_prop, &Canvas); flags &= ~0x20; d3d_bbuf->Release(); if (canvas_state) return false;
		if (!SolidColor) Canvas->CreateSolidColorBrush({}, &SolidColor); return true;
	}
	bool NewFrame(IDXGISwapChain* SwapChain) {
		if (!Canvas && !InitRender(SwapChain))
			return false;
		Canvas->BeginDraw();
		return true;
	}
	ImVec2 CanvasSize() {
		D2D1_SIZE_F Size = Canvas->GetSize();
		return ImVec2{ Size.width, Size.height };
	}
	void ResetCanvas() {
		if (Canvas) {
			Canvas->Release();
			Canvas = nullptr;
		}
	}
	void EndFrame() {
		HRESULT state = Canvas->EndDraw();
		if (state == D2DERR_RECREATE_TARGET)
			ResetCanvas();
	}
	class Color3
	{
	public:
		float r, g, b, a;

		Color3() {
			r = g = b = a = 0;
		}

		Color3(float r, float g, float b, float a = 255) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}


		Color3 operator+(const Color3& input) const {
			return Color3{ r + input.r, g + input.g, b + input.b,a + input.a };
		}

		Color3 operator-(const Color3& input) const {
			return Color3{ r - input.r, g - input.g, b - input.b,a - input.a };
		}

		Color3 operator/(float input) const {
			return Color3{ r / input, g / input, b / input,a / input };
		}

		Color3 operator*(float input) const {
			return Color3{ r * input, g * input, b * input,a * input };
		}

		Color3& operator-=(const Color3& v) {
			r -= v.r;
			g -= v.g;
			b -= v.b;
			a -= v.a;

			return *this;
		}

		Color3& operator+=(const Color3& v) {
			r += v.r;
			g += v.g;
			b += v.b;
			a += v.a;

			return *this;
		}

		Color3& operator/=(float input) {
			r /= input;
			g /= input;
			b /= input;
			a /= input;

			return *this;
		}

		Color3& operator*=(float input) {
			r *= input;
			g *= input;
			b *= input;
			a *= input;

			return *this;
		}

		bool operator==(const Color3& input) const {
			return r == input.r && g == input.g && b == input.b && a == input.a;
		}
	};
	void lineqwas(const ImVec2 start, const ImVec2 end, const D2D1::ColorF& Clr, bool outl = false, float thickness = 1.f) {
		if (outl) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ start.x, start.y }, { end.x, end.y }, SolidColor, thickness * 2);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ start.x, start.y }, { end.x, end.y }, SolidColor, thickness);
	}
	void LineLua(const ImVec2& Start, const ImVec2& End, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
		Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}
	void horizontal_line(ImVec2 pos, float size, const D2D1::ColorF& Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ pos.x, pos.y }, { size, 1 }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ pos.x, pos.y }, { size, 1 }, SolidColor, Thick);
	}
	void vertical_line(ImVec2 pos, float size, const D2D1::ColorF& Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ pos.x, pos.y }, { 1, size }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ pos.x, pos.y }, { 1, size }, SolidColor, Thick);
	}
	void LineTESDTXBOX(const ImVec2& pos, const ImVec2& size, const D2D1::ColorF& Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ pos.x, pos.y }, { size.y }, SolidColor, Thick * 1.75);
			Canvas->DrawLine({ pos.x + size.x }, { pos.y, size.y }, SolidColor, Thick * 1.75);
			Canvas->DrawLine({ pos.x, pos.y }, { size.x }, SolidColor, Thick * 1.75);
			Canvas->DrawLine({ pos.x, pos.y }, { size.y, size.x }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ pos.x, pos.y }, { size.y }, SolidColor, Thick);
		Canvas->DrawLine({ pos.x + size.x }, { pos.y, size.y }, SolidColor, Thick);
		Canvas->DrawLine({ pos.x, pos.y }, { size.x }, SolidColor, Thick);
		Canvas->DrawLine({ pos.x, pos.y }, { size.y, size.x }, SolidColor, Thick);
	}
	void Line(const ImVec2& Start, const ImVec2& End, const D2D1::ColorF& Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(Clr);
		Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}

	void LineLuacolor(const ImVec2& Start, const ImVec2& End, const ImColor Clr, float Thick = 1.5f, bool outline = false) {
		if (outline) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick * 1.75);
		}
		SolidColor->SetColor(D2D1::ColorF(Clr));
		Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}

	void Circle(const ImVec2& Start, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) {
		SolidColor->SetColor(Clr);
		Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);
	}
	void CircleOut(const ImVec2& Start, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) {

		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick * 1.75);

		SolidColor->SetColor(Clr);
		Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);

	}
	void CircleLuaColor(const ImVec2& Start, const ImColor Clr, float Rad, float Thick = 1.5f) {
		SolidColor->SetColor(D2D1::ColorF(Clr));
		Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);
	}
	void FillCircle(const ImVec2& Start, const D2D1::ColorF& Clr, float Rad) {
		SolidColor->SetColor(Clr);
		Canvas->FillEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor);
	}
	void FillCircleColorLua(const ImVec2& Start, const ImColor Clr, float Rad) {
		SolidColor->SetColor(D2D1::ColorF(Clr));
		Canvas->FillEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor);
	}
	void Rectangle(const ImVec2& Start, const ImVec2& Sz, const D2D1::ColorF& Clr, float Thick = 1.5f) {
		SolidColor->SetColor(Clr);

		Canvas->DrawRectangle({ Start.x, Start.y,  Sz.x,  Sz.y }, SolidColor, Thick);

		//Canvas->DrawRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor, Thick);
	}
	void RectangleLuaColor(const ImVec2& Start, const ImVec2& Sz, const ImColor Clr, float Thick = 1.5f) {
		SolidColor->SetColor(D2D1::ColorF(Clr));
		Canvas->DrawRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor, Thick);
	}
	void AddRectFilledMultiColor(float x, float y, float w, float h, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left)
	{
		ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), col_upr_left, col_upr_right, col_bot_right, col_bot_left);
	}
	void FillRectangle(const ImVec2& Start, const ImVec2& Sz, const D2D1::ColorF& Clr) {
		SolidColor->SetColor(Clr);


		Canvas->FillRectangle({ Start.x, Start.y, Sz.x, Sz.y }, SolidColor);
		//Canvas->FillRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor);
	}
	void FillRectangleLuaColor(const ImVec2& Start, const ImVec2& Sz, const ImColor Clr) {
		SolidColor->SetColor(D2D1::ColorF(Clr));
		Canvas->FillRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor);
	}
	void OutlineRect(const ImVec2& pos, const ImVec2& size, const D2D1::ColorF& color, const D2D1::ColorF& oColor, float thickness) {
		SolidColor->SetColor(color);
		Canvas->FillRectangle({ pos.x, pos.y, pos.x + size.x, pos.y + size.y }, SolidColor);
		SolidColor->SetColor(oColor);
		Canvas->DrawRectangle({ pos.x, pos.y, pos.x + size.x, pos.y + size.y }, SolidColor, thickness);
	}
	ImVec2 Stringq(const ImVec2& pos, const wchar_t* text, const D2D1::ColorF& color, bool outline, bool center = false) {
		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
			DWRITE_TEXT_METRICS TextInfo;
			TextLayout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			if (outline) {
				const auto x = pos.x - TextSize.x;
				const auto y = pos.y - TextSize.y;
				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}
			SolidColor->SetColor(color);
			Canvas->DrawTextLayout({ pos.x - TextSize.x, pos.y - TextSize.y }, TextLayout, SolidColor);
			TextLayout->Release();
			return TextSize;
		}
		IDWriteTextLayout* TextLayout;
		TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;
			Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
		}
		SolidColor->SetColor(color);
		//Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x, pos.y, FLT_MAX, FLT_MAX }, SolidColor);
		TextLayout->Release();
		return { 0,0 };
	}
	void RoundedRectangle(const ImVec2& Start, const ImVec2& Sz, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) {
		SolidColor->SetColor(Clr);
		Canvas->DrawRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, Rad, Rad }, SolidColor, Thick);
	}
	void FillRoundedRectangle(const ImVec2& Start, const ImVec2& Sz, const D2D1::ColorF& Clr, float Rad) {
		SolidColor->SetColor(Clr);
		Canvas->FillRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y}, Rad, Rad }, SolidColor);
	}

	void RectangleFillPoint(const ImVec2 middle, float sz, float szy, const D2D1::ColorF clr) {
		SolidColor->SetColor(clr);
		Canvas->FillRectangle({ middle.x - (sz / 2), middle.y - (szy / 2), middle.x + sz, middle.y + szy }, SolidColor);
	}
	void RectanglePointFov(const ImVec2 middle, float sz, float szy, const D2D1::ColorF clr, float thicness = 1.f) {
		//SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		//Canvas->DrawRectangle({ middle.x - (sz / 2), middle.y - (szy / 2), middle.x + sz, middle.y + szy }, SolidColor, thicness * 1.75);

		SolidColor->SetColor(clr);
		Canvas->DrawRectangle({ middle.x - (sz / 2), middle.y - (szy / 2), middle.x + sz, middle.y + szy }, SolidColor, thicness);

	}
	void RectanglePoint(const ImVec2 middle, float sz, float szy, const D2D1::ColorF clr) {
		SolidColor->SetColor(clr);
		Canvas->DrawRectangle({ middle.x - (sz / 2), middle.y - (szy / 2), middle.x + sz, middle.y + szy }, SolidColor, 0.8f);
	}
	void Triangle(const ImVec2 top, const D2D1::ColorF clr, float sz) {
		Line(top, top + ImVec2(sz, sz), clr);
		Line(top, top - ImVec2(sz, -sz), clr);
		Line(top + ImVec2(sz, sz), top - ImVec2(sz, -sz), clr);
	}

	ImVec2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
		float nigga = flAngle;
		nigga += 45.f;

		float flYaw = (nigga) * (3.14159265358979323846 / 180.0);

		float viewcosyawzzzzzzz = cos(flYaw);
		float viewsinyawzzzzzzz = sin(flYaw);

		float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
		float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

		int posonscreenX = x + int(x2 / range * (LineLength));
		int posonscreenY = y + int(y2 / range * (LineLength));

		return ImVec2(posonscreenX, posonscreenY);
	}
	void CosTanSinLine(float flAngle, float range, int x, int y, int LineLength, const D2D1::ColorF& Clr, bool oof = false, bool outline = false) {
		float nigga = flAngle;
		nigga += 45.f;

		float flYaw = (nigga) * (3.14159265358979323846 / 180.0);

		float viewcosyawzzzzzzz = cos(flYaw);
		float viewsinyawzzzzzzz = sin(flYaw);

		float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
		float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

		int posonscreenX = x + int(x2 / range * (LineLength));
		int posonscreenY = y + int(y2 / range * (LineLength));

		if (!oof) {
			Line(ImVec2(x, y), ImVec2(posonscreenX, posonscreenY), Clr);
		}
		else {
			Line(CosTanSinLineH(flAngle, range, x, y, LineLength / 1.3), ImVec2(posonscreenX, posonscreenY), Clr, 1.5f);
			if (outline) {
				Line(CosTanSinLineH(flAngle, range, x, y, LineLength / 1.3), ImVec2(posonscreenX, posonscreenY), Clr, 1.5f, true);
			}
		}
		if (outline) {
			//FillCircle(ImVec2(posonscreenX, posonscreenY), D2D1::ColorF::Black, 5.35f);
		}
		//FillCircle(ImVec2(posonscreenX, posonscreenY), Clr, 4);//P.S this is the small dot at the end of each line!!!!!!!!!XD
	}
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height) {
		// Load from disk into a raw RGBA buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = image_width;
		desc.Height = image_height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = image_data;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}
	template <typename ...Args>
	void Textplussize(const ImVec2 pos, const D2D1::ColorF clr, bool center, bool outline, float sizez, const std::wstring_view text, Args&&... args) {
		const auto size = static_cast<std::size_t>(std::swprintf(nullptr, 0, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		std::swprintf(buffer.get(), size, text.data(), std::forward<Args>(args)...);

		const auto str = std::wstring(buffer.get(), buffer.get() + size - 1);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, TextFormat, global::ScreenWidth, global::ScreenHeight, &dwrite_layout));

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};
		dwrite_layout->SetFontFamilyName(GetWC(custmomfontname), range);

		dwrite_layout->SetFontSize(sizez, range);

		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			DWRITE_TEXT_METRICS TextInfo;
			dwrite_layout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			const auto x = pos.x - TextSize.x;
			const auto y = pos.y - TextSize.y;
			if (outline) {

				Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
			}

			SolidColor->SetColor(clr);

			Canvas->DrawTextLayout(D2D1::Point2F(x, y), dwrite_layout, SolidColor);
			dwrite_layout->Release();
			return;
		}


		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;

			Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
		}

		SolidColor->SetColor(clr);
		Canvas->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), dwrite_layout, SolidColor);
		dwrite_layout->Release();
	}
	template <typename ...Args>
	void Text(const ImVec2 pos, const D2D1::ColorF clr, bool center, bool outline, const std::wstring_view text, Args&&... args) {
		const auto size = static_cast<std::size_t>(std::swprintf(nullptr, 0, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		std::swprintf(buffer.get(), size, text.data(), std::forward<Args>(args)...);

		const auto str = std::wstring(buffer.get(), buffer.get() + size - 1);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, TextFormat, global::ScreenWidth, global::ScreenHeight, &dwrite_layout));

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};
		dwrite_layout->SetFontFamilyName(GetWC(custmomfontname), range);


		dwrite_layout->SetFontSize(amphetamine::amphetamine_settings->textsize, range);        //////////////////////////////////////////////////////////////////////////////////////////

		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			DWRITE_TEXT_METRICS TextInfo;
			dwrite_layout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			const auto x = pos.x - TextSize.x;
			const auto y = pos.y - TextSize.y;
			if (outline) {

				Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
			}

			SolidColor->SetColor(clr);

			Canvas->DrawTextLayout(D2D1::Point2F(x, y), dwrite_layout, SolidColor);
			dwrite_layout->Release();
			return;
		}


		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;

			Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
		}

		SolidColor->SetColor(clr);
		Canvas->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), dwrite_layout, SolidColor);
		dwrite_layout->Release();
	}
	template <typename ...Args>
	void TextHPSMALLSIZE(const ImVec2 pos, const D2D1::ColorF clr, bool center, bool outline, const std::wstring_view text, Args&&... args) {
		const auto size = static_cast<std::size_t>(std::swprintf(nullptr, 0, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		std::swprintf(buffer.get(), size, text.data(), std::forward<Args>(args)...);

		const auto str = std::wstring(buffer.get(), buffer.get() + size - 1);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, TextFormat, global::ScreenWidth, global::ScreenHeight, &dwrite_layout));

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};

		dwrite_layout->SetFontSize(7.f, range);

		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			DWRITE_TEXT_METRICS TextInfo;
			dwrite_layout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			const auto x = pos.x - TextSize.x;
			const auto y = pos.y - TextSize.y;
			if (outline) {

				Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
			}

			SolidColor->SetColor(clr);

			Canvas->DrawTextLayout(D2D1::Point2F(x, y), dwrite_layout, SolidColor);
			dwrite_layout->Release();
			return;
		}


		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;

			Canvas->DrawTextLayout(D2D1::Point2F(x - 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1.75, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1.75), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1.75), dwrite_layout, SolidColor);
		}

		SolidColor->SetColor(clr);
		Canvas->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), dwrite_layout, SolidColor);
		dwrite_layout->Release();
	}
	template <typename ...Args>
	void TextLuagui(const ImVec2 pos, const ImColor clr, bool center, bool outline, float textsize, const std::wstring_view text, Args&&... args) {
		const auto size = static_cast<std::size_t>(std::swprintf(nullptr, 0, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		std::swprintf(buffer.get(), size, text.data(), std::forward<Args>(args)...);

		const auto str = std::wstring(buffer.get(), buffer.get() + size - 1);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, TextFormat, global::ScreenWidth, global::ScreenHeight, &dwrite_layout));

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};


		dwrite_layout->SetFontFamilyName(L"C:\\Windows\\Fonts\\tahomabd.ttf", range);


		dwrite_layout->SetFontSize(textsize, range);

		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			DWRITE_TEXT_METRICS TextInfo;
			dwrite_layout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			const auto x = pos.x - TextSize.x;
			const auto y = pos.y - TextSize.y;
			if (outline) {

				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), dwrite_layout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), dwrite_layout, SolidColor);
			}

			SolidColor->SetColor(D2D1::ColorF(clr));

			Canvas->DrawTextLayout(D2D1::Point2F(x, y), dwrite_layout, SolidColor);
			dwrite_layout->Release();
			return;
		}


		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;

			Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), dwrite_layout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), dwrite_layout, SolidColor);
		}

		SolidColor->SetColor(D2D1::ColorF(clr));
		Canvas->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), dwrite_layout, SolidColor);
		dwrite_layout->Release();
	}
	ImVec2 StringLUA(const ImVec2& pos, const wchar_t* text, const D2D1::ColorF& color, bool outline, bool center = false) {
		if (center) {
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
			DWRITE_TEXT_METRICS TextInfo;
			TextLayout->GetMetrics(&TextInfo);
			ImVec2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			if (outline) {
				const auto x = pos.x - TextSize.x;
				const auto y = pos.y - TextSize.y;
				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}
			SolidColor->SetColor(color);
			Canvas->DrawTextLayout({ pos.x - TextSize.x, pos.y - TextSize.y }, TextLayout, SolidColor);
			TextLayout->Release();
			return TextSize;
		}
		IDWriteTextLayout* TextLayout;
		TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		if (outline) {
			const auto x = pos.x;
			const auto y = pos.y;
			Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
		}
		SolidColor->SetColor(color);
		TextLayout->Release();
		return { 0,0 };
	}
}
