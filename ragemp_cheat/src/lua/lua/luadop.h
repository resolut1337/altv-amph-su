#pragma once

#include <cstdint>
#include <windows.h>
#include <cmath>

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


class ColorLua //-V690
{
public:
	ColorLua();
	ColorLua(int _r, int _g, int _b);
	ColorLua(int _r, int _g, int _b, int _a);
	ColorLua(float _r, float _g, float _b) : ColorLua(_r, _g, _b, 1.0f) {}
	ColorLua(float _r, float _g, float _b, float _a)
		: ColorLua(
			static_cast<int>(_r * 255.0f),
			static_cast<int>(_g * 255.0f),
			static_cast<int>(_b * 255.0f),
			static_cast<int>(_a * 255.0f))
	{
	}
	explicit ColorLua(float* rgb) : ColorLua(rgb[0], rgb[1], rgb[2], 1.0f) {}
	explicit ColorLua(unsigned long argb)
	{
		_CColor[2] = (unsigned char)((argb & 0x000000FF) >> (0 * 8));
		_CColor[1] = (unsigned char)((argb & 0x0000FF00) >> (1 * 8));
		_CColor[0] = (unsigned char)((argb & 0x00FF0000) >> (2 * 8));
		_CColor[3] = (unsigned char)((argb & 0xFF000000) >> (3 * 8));
	}

	static ColorLua FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f; //-V550
		float f = h - (int)h; //-V2003
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return ColorLua(
				(unsigned char)(brightness * 255), //-V2004
				(unsigned char)(t * 255), //-V2004
				(unsigned char)(p * 255) //-V2004
			);
		}
		else if (h < 2)
		{
			return ColorLua(
				(unsigned char)(q * 255), //-V2004
				(unsigned char)(brightness * 255), //-V2004
				(unsigned char)(p * 255) //-V2004
			);
		}
		else if (h < 3)
		{
			return ColorLua(
				(unsigned char)(p * 255), //-V2004
				(unsigned char)(brightness * 255), //-V2004
				(unsigned char)(t * 255) //-V2004
			);
		}
		else if (h < 4)
		{
			return ColorLua(
				(unsigned char)(p * 255), //-V2004
				(unsigned char)(q * 255), //-V2004
				(unsigned char)(brightness * 255) //-V2004
			);
		}
		else if (h < 5)
		{
			return ColorLua(
				(unsigned char)(t * 255), //-V2004
				(unsigned char)(p * 255), //-V2004
				(unsigned char)(brightness * 255) //-V2004
			);
		}
		else
		{
			return ColorLua(
				(unsigned char)(brightness * 255), //-V2004
				(unsigned char)(p * 255), //-V2004
				(unsigned char)(q * 255) //-V2004
			);
		}
	}

	static ColorLua FromHSV(float h, float s, float v)
	{
		if (s == 0.0f) //-V550
		{
			// gray
			return ColorLua(v, v, v);
		}

		h = fmodf(h, 1.0f) / (60.0f / 360.0f);
		int   i = (int)h; //-V2003
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0: return ColorLua(v * 255, t * 255, p * 255); break;
		case 1: return ColorLua(q * 255, v * 255, p * 255); break;
		case 2: return ColorLua(p * 255, v * 255, t * 255); break;
		case 3: return ColorLua(p * 255, q * 255, v * 255); break;
		case 4: return ColorLua(t * 255, p * 255, v * 255); break;
		case 5: default: return ColorLua(v * 255, p * 255, q * 255); break;
		}
	}

	void    SetRawColor(int color32);
	int     GetRawColor() const;
	void    SetColorq(int _r, int _g, int _b, int _a = 0);
	void    SetColorq(float _r, float _g, float _b, float _a = 0);
	void	SetColorq(float* color) //-V2009
	{
		if (!color)
			return;

		_CColor[0] = (unsigned char)(color[0] * 255.f); //-V2004
		_CColor[1] = (unsigned char)(color[1] * 255.f); //-V2004
		_CColor[2] = (unsigned char)(color[2] * 255.f); //-V2004
		_CColor[3] = (unsigned char)(color[3] * 255.f); //-V2004
	}
	void    GetColor(int& _r, int& _g, int& _b, int& _a) const;
	inline int get_red() const
	{
		return _CColor[0];
	}
	inline int get_green() const
	{
		return _CColor[1];
	}
	inline int get_blue() const
	{
		return _CColor[2];
	}
	inline int get_alpha() const
	{
		return _CColor[3];
	}
	void set(int _r, int _g, int _b, int _a = 255)
	{
		_CColor[0] = (unsigned char)_r;
		_CColor[1] = (unsigned char)_g;
		_CColor[2] = (unsigned char)_b;
		_CColor[3] = (unsigned char)_a;
	}
	inline void set_red(int value) {
		_CColor[0] = value;
	}
	inline void set_green(int value) {
		_CColor[1] = value;
	}
	inline void set_blue(int value) {
		_CColor[2] = value;
	}
	inline void set_alpha(int value) {
		_CColor[3] = value;
	}
	int r() const { return _CColor[0]; }
	int g() const { return _CColor[1]; }
	int b() const { return _CColor[2]; }
	int a() const { return _CColor[3]; }

	void SetAlpha(int alpha) { _CColor[3] = alpha; }

	unsigned char& operator[](int index)
	{
		return _CColor[index];
	}
	const unsigned char& operator[](int index) const
	{
		return _CColor[index];
	}

	bool operator==(const ColorLua& rhs) const;
	bool operator!=(const ColorLua& rhs) const;
	ColorLua& operator=(const ColorLua& rhs);

	static ColorLua Black;
	static ColorLua White;
	static ColorLua Red;
	static ColorLua Green;
	static ColorLua Blue;
	static ColorLua Yellow;
	static ColorLua Pink;
	static ColorLua LightBlue;

	unsigned char _CColor[4];
};
ColorLua ColorLua::Black(0, 0, 0);
ColorLua ColorLua::White(255, 255, 255);
ColorLua ColorLua::Red(255, 0, 0);
ColorLua ColorLua::Green(0, 255, 0);
ColorLua ColorLua::Blue(0, 0, 255);
ColorLua ColorLua::Yellow(255, 255, 0);
ColorLua ColorLua::Pink(255, 0, 255);
ColorLua ColorLua::LightBlue(0, 255, 255);

ColorLua::ColorLua()
{
	SetColorq(255, 255, 255, 255);
}

ColorLua::ColorLua(int _r, int _g, int _b)
{
	SetColorq(_r, _g, _b, 255);
}

ColorLua::ColorLua(int _r, int _g, int _b, int _a)
{
	SetColorq(_r, _g, _b, _a);
}

void ColorLua::SetRawColor(int color32)
{
	*((int*)this) = color32; //-V1032
}

int ColorLua::GetRawColor() const
{
	return *((int*)this); //-V1032
}

__inline void ColorLua::SetColorq(int _r, int _g, int _b, int _a)
{
	_CColor[0] = (unsigned char)_r;
	_CColor[1] = (unsigned char)_g;
	_CColor[2] = (unsigned char)_b;
	_CColor[3] = (unsigned char)_a;
}

__inline void ColorLua::SetColorq(float _r, float _g, float _b, float _a)
{
	_CColor[0] = static_cast<unsigned char>(_r * 255.0f); //-V2004
	_CColor[1] = static_cast<unsigned char>(_g * 255.0f); //-V2004
	_CColor[2] = static_cast<unsigned char>(_b * 255.0f); //-V2004
	_CColor[3] = static_cast<unsigned char>(_a * 255.0f); //-V2004
}

void ColorLua::GetColor(int& _r, int& _g, int& _b, int& _a) const
{
	_r = _CColor[0];
	_g = _CColor[1];
	_b = _CColor[2];
	_a = _CColor[3];
}

bool ColorLua::operator== (const ColorLua& rhs) const
{
	return (*((int*)this) == *((int*)&rhs)); //-V1032
}

bool ColorLua::operator!= (const ColorLua& rhs) const
{
	return !(operator==(rhs));
}

ColorLua& ColorLua::operator=(const ColorLua& rhs)
{
	SetRawColor(rhs.GetRawColor());
	return *this;
}