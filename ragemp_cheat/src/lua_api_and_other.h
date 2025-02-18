#include "../src/lua/lua/singleton.h"
#pragma once

#include <cstdint>
#include <windows.h>
#include <cmath>

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#define crypt_str(s) s
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
std::vector <std::string> scripts;
std::vector <std::string> hitsounds;
std::string editing_script;
bool loaded_script = false;
bool loaded_hitsounds = false;
int selected_script = 0;

//#include "../ResourceManager.h"

//#include "../other2.h"

auto loaded_editing_script = false;
int rotation_start_index;
void ImRotateStart()
{
	rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
}
ImVec2 ImRotationCenter()
{
	ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

	const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

	return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2); // or use _ClipRectStack?
}
void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
{
	float s = sin(rad), c = cos(rad);
	center = ImRotate(center, s, c) - center;

	auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
	for (int i = rotation_start_index; i < buf.Size; i++)
		buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
}



int imguieditscriptlua = 0;





enum menu_item_type
{
	NEXT_LINE,
	CHECK_BOX,
	COMBO_BOX,
	SLIDER_INT,
	SLIDER_FLOAT,
	COLOR_PICKER,
	HOTKEY
};
class menu_item
{
public:
	bool check_box_value = false;
	int hotkey_value = 0;

	std::vector <std::string> combo_box_labels;
	int combo_box_value = 0;

	int slider_int_min = 0;
	int slider_int_max = 0;
	int slider_int_value = 0;

	float slider_float_min = 0.0f;
	float slider_float_max = 0.0f;
	float slider_float_value = 0.0f;

	ColorLua color_picker_value = ColorLua::White;
	menu_item_type type = NEXT_LINE;

	menu_item()
	{
		type = NEXT_LINE;
	}

	menu_item(const menu_item& item)
	{
		hotkey_value = item.hotkey_value;

		check_box_value = item.check_box_value;

		combo_box_labels = item.combo_box_labels;
		combo_box_value = item.combo_box_value;

		slider_int_min = item.slider_int_min;
		slider_int_max = item.slider_int_max;
		slider_int_value = item.slider_int_value;

		slider_float_min = item.slider_float_min;
		slider_float_max = item.slider_float_max;
		slider_float_value = item.slider_float_value;

		color_picker_value = item.color_picker_value;
		type = item.type;
	}

	menu_item& operator=(const menu_item& item)
	{
		hotkey_value = item.hotkey_value;

		check_box_value = item.check_box_value;

		combo_box_labels = item.combo_box_labels;
		combo_box_value = item.combo_box_value;

		slider_int_min = item.slider_int_min;
		slider_int_max = item.slider_int_max;
		slider_int_value = item.slider_int_value;

		slider_float_min = item.slider_float_min;
		slider_float_max = item.slider_float_max;
		slider_float_value = item.slider_float_value;

		color_picker_value = item.color_picker_value;
		type = item.type;

		return *this;
	}

	menu_item(bool value)
	{
		check_box_value = value;
		type = CHECK_BOX;
	}
	menu_item(int value)
	{
		hotkey_value = value;
		type = HOTKEY;
	}
	menu_item(std::vector <std::string> labels, int value) //-V818
	{
		combo_box_labels = labels; //-V820
		combo_box_value = value;

		type = COMBO_BOX;
	}

	menu_item(int min, int max, int value)
	{
		slider_int_min = min;
		slider_int_max = max;
		slider_int_value = value;

		type = SLIDER_INT;
	}

	menu_item(float min, float max, float value)
	{
		slider_float_min = min;
		slider_float_max = max;
		slider_float_value = value;

		type = SLIDER_FLOAT;
	}

	menu_item(ColorLua value) //-V818
	{
		color_picker_value = value;
		type = COLOR_PICKER;
	}
};
menu_item chlen;
#include "../src/lua/lua/Clua.h"


void lua_panic(sol::optional <std::string> message)
{
	if (!message)
		return;

	auto log = crypt_str("Lua error: ") + message.value_or("unknown");
	//	eventlogs::get().add(log, false);
}

std::string get_current_script(sol::this_state s)
{
	sol::state_view lua_state(s);
	sol::table rs = lua_state["debug"]["getinfo"](2, ("S"));
	std::string source = rs["source"];
	std::string filename = std::filesystem::path(source.substr(1)).filename().string();

	return filename;
}
int get_current_script_id(sol::this_state s)
{
	return c_lua::get().get_script_id(get_current_script(s));
}

namespace ns_client
{
	void add_callback(sol::this_state s, std::string eventname, sol::protected_function func)
	{
		if (eventname != crypt_str("on_paint") && eventname != crypt_str("on_ragemp_thread_tick"))
		{
			MessageBoxA(NULL, ("Error CallBack"), ("Lua"), MB_ICONERROR);
			return;
		}


		if (c_lua::get().loaded.at(get_current_script_id(s)))//new
			c_lua::get().hooks.registerHook(eventname, get_current_script_id(s), func);
	}

	void load_script(std::string name)
	{
		c_lua::get().refresh_scripts();
		c_lua::get().load_script(c_lua::get().get_script_id(name));
	}

	void unload_script(std::string name)
	{
		c_lua::get().refresh_scripts();
		c_lua::get().unload_script(c_lua::get().get_script_id(name));
	}

	void log(LPCSTR text)
	{
		(MessageBoxA)(NULL, text, ("Lua"), MB_ICONINFORMATION);
	}
}

std::vector <std::pair <std::string, menu_item>>::iterator find_item(std::vector <std::pair <std::string, menu_item>>& items, const std::string& name)
{
	for (auto it = items.begin(); it != items.end(); ++it)
		if (it->first == name)
			return it;

	return items.end();
}

menu_item find_item(std::vector <std::vector <std::pair <std::string, menu_item>>>& scripts, const std::string& name)
{
	for (auto& script : scripts)
	{
		for (auto& item : script)
		{
			std::string item_name;

			auto first_point = false;
			auto second_point = false;

			for (auto& c : item.first)
			{
				if (c == '.')
				{
					if (first_point)
					{
						second_point = true;
						continue;
					}
					else
					{
						first_point = true;
						continue;
					}
				}

				if (!second_point)
					continue;

				item_name.push_back(c);
			}

			if (item_name == name)
				return item.second;
		}
	}

	return menu_item();
}
//
//void register_event(sol::this_state s, std::string event_name, sol::protected_function function)
//{
//	if (std::find(g_ctx.globals.events.begin(), g_ctx.globals.events.end(), event_name) == g_ctx.globals.events.end())
//	{
//		m_eventmanager()->AddListener(&hooks::hooked_events, event_name.c_str(), false);
//		g_ctx.globals.events.emplace_back(event_name);
//	}
//
//	c_lua::get().events[get_current_script_id(s)][event_name] = function;
//}








namespace ns_menu
{
	bool get_visible()
	{
		return global::show;
	}

	void set_visible(bool visible)
	{
		global::show = visible;
	}

	auto next_line_counter = 0;

	void next_line(sol::this_state s)
	{
		c_lua::get().items.at(get_current_script_id(s)).emplace_back(std::make_pair(crypt_str("next_line_") + std::to_string(next_line_counter), menu_item()));
		++next_line_counter;
	}

	void add_check_box(sol::this_state s, const std::string& name)
	{
		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(false)));
	}
	void add_hotkey(sol::this_state s, const std::string& name)
	{
		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(0)));
	}
	void add_color_picker(sol::this_state s, const std::string& name)
	{
		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(ColorLua::White)));
	}
	void add_combo_box(sol::this_state s, std::string name, std::vector <std::string> labels) //-V813
	{
		if (labels.empty())
			return;

		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(labels, 0)));
	}

	void add_slider_int(sol::this_state s, const std::string& name, int min, int max)
	{
		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(min, max, min)));
	}
	std::unordered_map <int, bool> keys;
	std::unordered_map <std::string, bool> first_update;
	std::unordered_map <std::string, menu_item> stored_values;
	std::unordered_map <std::string, void*> config_items;

	bool get_key_bind_state_lua(int key_bind_id)
	{
		if (key_bind_id < 0 || key_bind_id > 22)
			return false;

		switch (key_bind_id)
		{


			//////////////////////////////////////////////////////////

		case 13:
			return GetAsyncKeyState(VK_SHIFT);
		case 14:
			return GetAsyncKeyState(0x43);
		case 15:
			return GetAsyncKeyState(0x46);
		case 16:
			return GetAsyncKeyState(VK_TAB);

		default:
			return keys[key_bind_id];
		}
	}
	bool get_key_bind_state(int key_bind)
	{
		return get_key_bind_state_lua(key_bind);
	}
	bool get_key_bind_state_lua_opt(int key_bind_id)
	{
		return GetAsyncKeyState(key_bind_id);
	}
	bool get_key_bind_state_opt(int key_bind)
	{
		return get_key_bind_state_lua_opt(key_bind);
	}
	void add_slider_float(sol::this_state s, const std::string& name, float min, float max)
	{
		auto script = get_current_script(s);
		auto script_id = c_lua::get().get_script_id(script);

		auto& items = c_lua::get().items.at(script_id);
		auto full_name = script + '.' + name;

		if (find_item(items, full_name) != items.end())
			return;

		items.emplace_back(std::make_pair(full_name, menu_item(min, max, min)));
	}



	bool find_config_item(std::string name, std::string type)
	{
		if (config_items.find(name) == config_items.end())
		{
			auto found = false;

			for (auto item : cfg_manager->items)
			{
				if (item->name == name)
				{
					if (item->type != type)
					{
						return false;
					}

					found = true;
					config_items[name] = item->pointer;
					break;
				}
			}

			if (!found)
			{
				return false;
			}
		}

		return true;
	}

	bool get_bool(std::string name)
	{
		if (first_update.find(name) == first_update.end())
			first_update[name] = false;

		if (!global::show && first_update[name])
		{
			if (stored_values.find(name) != stored_values.end())
				return stored_values[name].check_box_value;
			else if (config_items.find(name) != config_items.end())
				return *(bool*)config_items[name];
			else
				return false;
		}

		auto it = find_item(c_lua::get().items, name);

		if (it.type == NEXT_LINE)
		{
			if (find_config_item(name, crypt_str("bool")))
				return *(bool*)config_items[name];
			return false;
		}

		first_update[name] = true;
		stored_values[name] = it;

		return it.check_box_value;
	}
	int get_int(std::string name)
	{
		if (first_update.find(name) == first_update.end())
			first_update[name] = false;

		if (!global::show && first_update[name])
		{
			if (stored_values.find(name) != stored_values.end())
				return stored_values[name].type == COMBO_BOX ? stored_values[name].combo_box_value : stored_values[name].slider_int_value;
			else if (config_items.find(name) != config_items.end())
				return *(int*)config_items[name]; //-V206
			else
				return 0;
		}

		auto it = find_item(c_lua::get().items, name);

		if (it.type == NEXT_LINE)
		{
			if (find_config_item(name, crypt_str("int")))
				return *(int*)config_items[name]; //-V206
			return 0;
		}

		first_update[name] = true;
		stored_values[name] = it;

		return it.type == COMBO_BOX ? it.combo_box_value : it.slider_int_value;
	}


	//int get_int_hotkey(std::string name)
	//{
	//	if (first_update.find(name) == first_update.end())
	//		first_update[name] = false;

	//	if (!show && first_update[name])
	//	{
	//		if (stored_values.find(name) != stored_values.end())
	//			return stored_values[name].hotkey_value;
	//		else if (config_items.find(name) != config_items.end())
	//			return *(int*)config_items[name]; //-V206
	//		else
	//			return 0;
	//	}

	//	auto& it = find_item(c_lua::get().items, name);

	//	if (it.type == NEXT_LINE)
	//	{
	//		if (find_config_item(name, crypt_str("int")))
	//			return *(int*)config_items[name]; //-V206
	//		return 0;
	//	}

	//	first_update[name] = true;
	//	stored_values[name] = it;

	//	return it.hotkey_value ;
	//}


	float get_float(std::string name)
	{
		if (first_update.find(name) == first_update.end())
			first_update[name] = false;

		if (!global::show && first_update[name])
		{
			if (stored_values.find(name) != stored_values.end())
				return stored_values[name].slider_float_value;
			else if (config_items.find(name) != config_items.end())
				return *(float*)config_items[name];
			else
				return 0.0f;
		}

		auto it = find_item(c_lua::get().items, name);

		if (it.type == NEXT_LINE)
		{
			if (find_config_item(name, crypt_str("float")))
				return *(float*)config_items[name];
			return 0.0f;
		}

		first_update[name] = true;
		stored_values[name] = it;

		return it.slider_float_value;
	}

	void set_bool(std::string name, bool value)
	{
		if (!find_config_item(name, crypt_str("bool")))
			return;

		*(bool*)config_items[name] = value;
	}

	void set_int(std::string name, int value)
	{
		if (!find_config_item(name, crypt_str("int")))
			return;

		*(int*)config_items[name] = value; //-V206
	}

	void set_float(std::string name, float value)
	{
		if (!find_config_item(name, crypt_str("float")))
			return;

		*(float*)config_items[name] = value;
	}

	void set_color(std::string name, ColorLua value)
	{
		if (!find_config_item(name, crypt_str("Color")))
			return;

		*(ColorLua*)config_items[name] = value;
	}
	ColorLua get_color(std::string name)
	{
		if (first_update.find(name) == first_update.end())
			first_update[name] = false;

		if (!global::show && first_update[name])
		{
			if (stored_values.find(name) != stored_values.end())
				return stored_values[name].color_picker_value;
			else if (config_items.find(name) != config_items.end())
				return *(ColorLua*)config_items[name];
			else
				return ColorLua::White;
		}

		auto it = find_item(c_lua::get().items, name);

		if (it.type == NEXT_LINE)
		{
			if (find_config_item(name, crypt_str("Color")))
				return *(ColorLua*)config_items[name];
			return ColorLua::White;
		}

		first_update[name] = true;
		stored_values[name] = it;

		return it.color_picker_value;
	}
}



sol::state lua(sol::c_call <decltype(&lua_panic), &lua_panic>);
#include "texteditor.h"
TextEditor editor;
std::string fileToEdit = "234234.txt";
auto lang = TextEditor::LanguageDefinition::Lua();

// set your own known preprocessor symbols...
static const char* ppnames[] = { "NULL", "PM_REMOVE",
	"ZeroMemory", "DXGI_SWAP_EFFECT_DISCARD", "D3D_FEATURE_LEVEL", "D3D_DRIVER_TYPE_HARDWARE", "WINAPI","D3D11_SDK_VERSION", "assert" };
// ... and their corresponding values
static const char* ppvalues[] = {
	"#define NULL ((void*)0)",
	"#define PM_REMOVE (0x0001)",
	"Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
	"enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
	"enum D3D_FEATURE_LEVEL",
	"enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
	"#define WINAPI __stdcall",
	"#define D3D11_SDK_VERSION (7)",
	" #define assert(expression) (void)(                                                  \n"
	"    (!!(expression)) ||                                                              \n"
	"    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
	" )"
};
// set your own identifiers
static const char* identifiers[] = {
	"HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
	"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
	"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
	"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };
static const char* idecls[] =
{
	"typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
	"typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
	"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
	"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
	"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };




//static const char* fileToEdit = "TextEditor.txt";

void c_lua::load_script(int id)
{
	if (id == -1)
		return;

	if (loaded.at(id)) //-V106
		return;

	auto path = get_script_path(id);

	if (path == crypt_str(""))
		return;

	fileToEdit = path;



	auto error_load = false;
	loaded.at(id) = true;
	std::string remnot = "Loaded Script: " + scripts.at(id);
	//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, remnot.c_str(), "amphetamine.su" });

	lua.script_file(path,
		[&error_load](lua_State*, sol::protected_function_result result)
		{
			if (!result.valid())
			{
				sol::error error = result;
				error_load = true;
			}

			return result;
		}
	);

	if (error_load | loaded.at(id) == false)
	{
		loaded.at(id) = false;
		return;
	}


	//-V106
	loaded_script = true;
}
namespace beps {
	void beeplua()
	{
		Beep(100, 100);
	}
}
//void __fastcall Circle2(float point, float point1, float radius, float Color1, float Color2, float Color3, float trich)
//{
//	Renderer::CircleLuaColor(Vector2{ point, point1 }, ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3)), radius, trich);
//}
//
//void __fastcall LineLuaImGUI(float pos, float pos1, float size, float size1, float Color1, float Color2, float Color3, float thickness)
//{
//	Renderer::LineLuacolor(Vector2{ pos, pos1 }, Vector2{ size, size1 }, ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3)), thickness, true);
//}


//namespace ns_engine
//{
//	int get_screen_width()
//	{
//		float xs = global::ScreenWidth / 2;
//		//screen_center.x;
//		return xs;
//	}
//
//	int get_screen_height()
//	{
//		float ys = global::ScreenHeight / 2;
//
//		return ys;
//	}
//}


ImFont* arial_big;
//
//
//void textluahui(float posx, float posy, std::string text, bool outline, float fontSize, float Color1, float Color2, float Color3, float alpha, bool center = false)
//{
//	std::wstring string_to_convert;
//	using convert_type = std::codecvt_utf8<wchar_t>;
//	std::wstring_convert<convert_type, wchar_t> converter;
//	std::string converted_str = converter.to_bytes(string_to_convert);
//	std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(text);
//	//std::wstring widestr = std::wstring(text.begin(), text.end());
//	Renderer::TextLuagui(Vector2(posx, posy), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)), center, outline, fontSize, str);
//}
//void __fastcall TextLua(float pos, float pos1, std::string strText, bool outline, float fontSize, int Color1, int Color2, int Color3, int alpha)
//{
//	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
//	ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Always);
//	ImGui::Begin(("    qwadsf"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_None | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
//	{
//		ImGuiContext& g = *GImGui;
//		const char* text_end = strText.c_str() + strlen(strText.c_str());
//		const char* text_display_end = ImGui::FindRenderedTextEnd(strText.c_str(), text_end);
//		if (fontSize == 0.f) fontSize = g.Font->FontSize;
//		if (outline) {
//			ImGui::GetWindowDrawList()->AddText(arial_big, fontSize, ImVec2(pos, pos1) - ImVec2(1, 0), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
//			ImGui::GetWindowDrawList()->AddText(arial_big, fontSize, ImVec2(pos, pos1) - ImVec2(0, 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
//			ImGui::GetWindowDrawList()->AddText(arial_big, fontSize, ImVec2(pos, pos1) + ImVec2(1, 0), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
//			ImGui::GetWindowDrawList()->AddText(arial_big, fontSize, ImVec2(pos, pos1) + ImVec2(0, 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
//		}
//		ImGui::GetWindowDrawList()->AddText(arial_big, fontSize, ImVec2(pos, pos1), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)), strText.c_str(), NULL, 0.0f, NULL);
//	}
//	ImGui::End();
//}
//void __fastcall DrawFilledRect(float x, float y, float w, float h, float Color1, float Color2, float Color3, float alpha)
//{
//	Renderer::FillRectangleLuaColor(Vector2(x, y), Vector2(w, h), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)));
//}
//void __fastcall DrawRect(float x, float y, float w, float h, float Color1, float Color2, float Color3, float alpha)
//{
//	Renderer::RectangleLuaColor(Vector2(x, y), Vector2(w, h), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)));
//}


//
//void icongeneration(std::string pathpng)
//{
//	int LogoWidth = 16;
//	int LogoHeight = 16;
//	bool ImageLoaded = Renderer::LoadTextureFromFile(pathpng.c_str(), &logo, &LogoWidth, &LogoHeight);
//	IM_ASSERT(ImageLoaded);
//}

//void __fastcall filledcircle(float point, float point1, float radius, float Color1, float Color2, float Color3, float alpha)
//{
//	Renderer::FillCircleColorLua(Vector2{ point, point1 }, ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)), radius);
//}

//void __fastcall Triangle(float x, float y, float w, float h, float b, float g, float Color1, float Color2, float Color3, float alpha, float thickness)
//{
//	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
//	ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Always);
//	ImGui::Begin(("    qwsdfa"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_None | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
//	{
//		ImGui::GetWindowDrawList()->AddTriangle(ImVec2(x, y), ImVec2(w, h), ImVec2(b, g), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)), thickness);
//	}
//	ImGui::End();
//
//	//Renderer::Triangle();
//}
//
//void iconrender(float pos1, float pos2, float pos3, float pos4)
//{
//	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
//	ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Always);
//	ImGui::Begin("testluaicon", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
//	{
//		ImDrawList* draw = ImGui::GetWindowDrawList();
//
//
//		draw->AddImage(((void*)logo), ImVec2(pos1, pos2), ImVec2(pos3, pos4));
//
//
//	}
//	ImGui::End();
//
//
//}



bool allow_http = true;

void downloadlua(std::string urldown, std::string puthfile)
{
	URLDownloadToFileA(nullptr, urldown.c_str(), puthfile.c_str(), 0, nullptr);
}


//extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
//extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
//	PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
//void BlueScreen() {
//	BOOLEAN bl;
//	ULONG Response;
//	RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
//	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
//}
bool mocha = false;









int c_lua::get_script_id(const std::string& name)
{
	for (auto i = 0; i < scripts.size(); i++)
		if (scripts.at(i) == name) //-V106
			return i;

	return -1;
}

int c_lua::get_script_id_by_path(const std::string& path)
{
	for (auto i = 0; i < pathes.size(); i++)
		if (pathes.at(i).string() == path) //-V106
			return i;

	return -1;
}

void c_lua::refresh_scripts()
{
	auto oldLoaded = loaded;
	auto oldScripts = scripts;

	loaded.clear();
	pathes.clear();
	scripts.clear();

	std::string folder;
	static TCHAR path[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
	{
		folder = std::string(path) + crypt_str("\\AMTH.CSGO\\Lua\\");
		CreateDirectory(folder.c_str(), NULL);

		auto i = 0;

		for (auto& entry : std::filesystem::directory_iterator(folder))
		{
			if (entry.path().extension() == crypt_str(".lua") || entry.path().extension() == crypt_str(".luac"))
			{
				auto path = entry.path();
				auto filename = path.filename().string();

				auto didPut = false;

				for (auto i = 0; i < oldScripts.size(); i++)
				{
					if (filename == oldScripts.at(i)) //-V106
					{
						loaded.emplace_back(oldLoaded.at(i)); //-V106
						didPut = true;
					}
				}

				if (!didPut)
					loaded.emplace_back(false);

				pathes.emplace_back(path);
				scripts.emplace_back(filename);

				items.emplace_back(std::vector <std::pair <std::string, menu_item>>());
				++i;
			}
		}
	}
}

void c_lua::unload_script(int id)
{
	if (id == -1)
		return;

	if (!loaded.at(id)) //-V106
		return;

	items.at(id).clear(); //-V106

	if (c_lua::get().events.find(id) != c_lua::get().events.end()) //-V807
		c_lua::get().events.at(id).clear();


	std::string remnot = "UnLoaded Script: " + scripts.at(id);
//	ImGui::InsertNotification({ ImGuiToastType_Success, 4000, remnot.c_str(), "amphetamine.su" });

	hooks.unregisterHooks(id);
	loaded.at(id) = false; //-V106
	loaded_script = false;
}

void c_lua::reload_all_scripts()
{
	for (auto current : scripts)
	{
		if (!loaded.at(get_script_id(current))) //-V106
			continue;

		unload_script(get_script_id(current));
		load_script(get_script_id(current));
	}
}

void c_lua::unload_all_scripts()
{
	for (auto s : scripts)
		unload_script(get_script_id(s));
}

std::string c_lua::get_script_path(const std::string& name)
{
	return get_script_path(get_script_id(name));
}

std::string c_lua::get_script_path(int id)
{
	if (id == -1)
		return crypt_str("");

	return pathes.at(id).string(); //-V106
}

void TextGradiented(const char* text, ImU32 leftcolor, ImU32 rightcolor, float smooth = 175) {
	using namespace ImGui;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	const ImVec2 pos = window->DC.CursorPos;
	ImDrawList* draw_list = window->DrawList;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(text);
	const ImVec2 size = CalcTextSize(text);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return;


	const ImU32 col_white = IM_COL32(255, 255, 255, 255);
	float centeredvertex = ImMax((int)smooth, 35);
	float vertex_out = centeredvertex * 0.50f;
	float text_inner = vertex_out - centeredvertex;
	const int vert_start_idx = draw_list->VtxBuffer.Size;
	draw_list->AddText(pos, col_white, text);
	const int vert_end_idx = draw_list->VtxBuffer.Size;
	for (int n = 0; n < 1; n++)
	{
		const ImU32 col_hues[2] = { leftcolor, rightcolor };
		ImVec2 textcenter(pos.x + (size.x / 2), pos.y + (size.y / 2));

		const float a0 = (n) / 6.0f * 2.0f * IM_PI - (0.5f / vertex_out);
		const float a1 = (n + 1.0f) / 6.0f * 2.0f * IM_PI + (0.5f / vertex_out);


		ImVec2 gradient_p0(textcenter.x + ImCos(a0) * text_inner, textcenter.y + ImSin(a0) * text_inner);
		ImVec2 gradient_p1(textcenter.x + ImCos(a1) * text_inner, textcenter.y + ImSin(a1) * text_inner);
		ShadeVertsLinearColorGradientKeepAlpha(draw_list, vert_start_idx, vert_end_idx, gradient_p0, gradient_p1, col_hues[n], col_hues[n + 1]);
	}
}
void __fastcall TextLua(float pos, float pos1, std::string strText, bool outline, float fontSize, int Color1, int Color2, int Color3, int alpha)
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), ImGuiCond_Always);
	ImGui::Begin(("    qwadsf"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_None | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
	{
		ImGuiContext& g = *GImGui;
		const char* text_end = strText.c_str() + strlen(strText.c_str());
		const char* text_display_end = ImGui::FindRenderedTextEnd(strText.c_str(), text_end);
		if (fontSize == 0.f) fontSize = g.Font->FontSize;
		if (outline) {
			ImGui::GetWindowDrawList()->AddText(font::poppins_medium_low, fontSize, ImVec2(pos, pos1) - ImVec2(1, 0), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
			ImGui::GetWindowDrawList()->AddText(font::poppins_medium_low, fontSize, ImVec2(pos, pos1) - ImVec2(0, 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
			ImGui::GetWindowDrawList()->AddText(font::poppins_medium_low, fontSize, ImVec2(pos, pos1) + ImVec2(1, 0), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
			ImGui::GetWindowDrawList()->AddText(font::poppins_medium_low, fontSize, ImVec2(pos, pos1) + ImVec2(0, 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0)), strText.c_str(), NULL, 0.0f, NULL);
		}
		ImGui::GetWindowDrawList()->AddText(font::poppins_medium_low, fontSize, ImVec2(pos, pos1), ImGui::ColorConvertFloat4ToU32(ImColor(Color1, Color2, Color3, alpha)), strText.c_str(), NULL, 0.0f, NULL);
	}
	ImGui::End();
}
void c_lua::initialize()
{
	lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::debug, sol::lib::package);
	lua[crypt_str("collectgarbage")] = sol::nil;
	lua[crypt_str("dofilsse")] = sol::nil;
	lua[crypt_str("load")] = sol::nil;
	lua[crypt_str("loadfile")] = sol::nil;
	lua[crypt_str("pcall")] = sol::nil;
	lua[crypt_str("print")] = sol::nil;
	lua[crypt_str("xpcall")] = sol::nil;
	lua[crypt_str("getmetatable")] = sol::nil;
	lua[crypt_str("setmetatable")] = sol::nil;
	lua[crypt_str("__nil_callback")] = []() {};


	auto render = lua.create_table();
	render[crypt_str("text")] = TextLua;
	//render[crypt_str("Circle")] = Circle2;
	//render[crypt_str("line")] = LineLuaImGUI;
	//render[crypt_str("filledrect")] = DrawFilledRect;
	//render[crypt_str("rect")] = DrawRect;
	//render[crypt_str("fillcircle")] = filledcircle;
	//render[crypt_str("triangle")] = Triangle;
	//	render[crypt_str("imageputh")] = icongeneration;
	//	render[crypt_str("image")] = iconrender;


	auto engine = lua.create_table();
	engine[crypt_str("screenwidth")] = global::ScreenWidth;
	engine[crypt_str("screenheight")] = global::ScreenHeight;


	auto client = lua.create_table();
	client[crypt_str("beep")] = Beep;
	client[crypt_str("addcallback")] = ns_client::add_callback;
	client[crypt_str("GetAsyncKeyState")] = ns_menu::get_key_bind_state_opt;

	client[crypt_str("load_script")] = ns_client::load_script;
	client[crypt_str("unload_script")] = ns_client::unload_script;
	client[crypt_str("messagebox")] = ns_client::log;
	client[crypt_str("urldownload")] = downloadlua;





	lua.new_usertype <Vector3>(crypt_str("Vector3"), sol::constructors <Vector3(), Vector3(float, float, float)>(),
		(std::string)crypt_str("x"), &Vector3::x,
		(std::string)crypt_str("y"), &Vector3::y,
		(std::string)crypt_str("z"), &Vector3::z
		);
	lua.new_usertype <Vector2>(crypt_str("Vector2"), sol::constructors <Vector2(), Vector2(float, float)>(),
		(std::string)crypt_str("x"), &Vector2::x,
		(std::string)crypt_str("y"), &Vector2::y
		);

	auto menu = lua.create_table();
	menu[crypt_str("checkbox")] = ns_menu::add_check_box;
	menu[crypt_str("slider_int")] = ns_menu::add_slider_int;
	menu[crypt_str("slider_float")] = ns_menu::add_slider_float;
	menu[crypt_str("hotkey")] = ns_menu::add_hotkey;
	menu[crypt_str("key_bind_state")] = ns_menu::get_key_bind_state;
	menu[crypt_str("key_hotkeys")] = chlen.hotkey_value;
	menu[crypt_str("key_manipulator")] = 2;
	menu[crypt_str("key_shift")] = 13;
	menu[crypt_str("key_c")] = 14;
	menu[crypt_str("key_f")] = 15;
	menu[crypt_str("key_tab")] = 16;
	menu[crypt_str("get_bool")] = ns_menu::get_bool;
	menu[crypt_str("get_int")] = ns_menu::get_int;
	//menu[crypt_str("get_int_hotkey")] = ns_menu::get_int_hotkey;

	menu[crypt_str("get_float")] = ns_menu::get_float;
	menu[crypt_str("set_bool")] = ns_menu::set_bool;
	menu[crypt_str("set_int")] = ns_menu::set_int;
	menu[crypt_str("set_color")] = ns_menu::set_color;
	menu[crypt_str("get_color")] = ns_menu::get_color;
	menu[crypt_str("color_picker")] = ns_menu::add_color_picker;

	auto N_PLAYER = lua.create_table();
	N_PLAYER[crypt_str("GET_PLAYER_PED")] = PLAYER::GET_PLAYER_PED;
	N_PLAYER[crypt_str("GET_PLAYER_PED_SCRIPT_INDEX")] = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX;
	N_PLAYER[crypt_str("SET_PLAYER_MODEL")] = PLAYER::SET_PLAYER_MODEL;
	N_PLAYER[crypt_str("CHANGE_PLAYER_PED")] = PLAYER::CHANGE_PLAYER_PED;
	N_PLAYER[crypt_str("GET_PLAYER_RGB_COLOUR")] = PLAYER::GET_PLAYER_RGB_COLOUR;
	N_PLAYER[crypt_str("GET_NUMBER_OF_PLAYERS")] = PLAYER::GET_NUMBER_OF_PLAYERS;
	N_PLAYER[crypt_str("GET_PLAYER_TEAM")] = PLAYER::GET_PLAYER_TEAM;
	N_PLAYER[crypt_str("SET_PLAYER_TEAM")] = PLAYER::SET_PLAYER_TEAM;
	N_PLAYER[crypt_str("GET_PLAYER_NAME")] = PLAYER::GET_PLAYER_NAME;
	N_PLAYER[crypt_str("ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP")] = PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP;
	N_PLAYER[crypt_str("ARE_PLAYER_STARS_GREYED_OUT")] = PLAYER::ARE_PLAYER_STARS_GREYED_OUT;
	N_PLAYER[crypt_str("IS_PLAYER_PLAYING")] = PLAYER::IS_PLAYER_PLAYING;
	N_PLAYER[crypt_str("SET_EVERYONE_IGNORE_PLAYER")] = PLAYER::SET_EVERYONE_IGNORE_PLAYER;
	N_PLAYER[crypt_str("SET_ALL_RANDOM_PEDS_FLEE")] = PLAYER::SET_ALL_RANDOM_PEDS_FLEE;
	N_PLAYER[crypt_str("SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME")] = PLAYER::SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME;
	N_PLAYER[crypt_str("SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS")] = PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS;
	N_PLAYER[crypt_str("START_FIRING_AMNESTY")] = PLAYER::START_FIRING_AMNESTY;
	N_PLAYER[crypt_str("_SWITCH_CRIME_TYPE")] = PLAYER::_SWITCH_CRIME_TYPE;
	N_PLAYER[crypt_str("IS_PLAYER_READY_FOR_CUTSCENE")] = PLAYER::IS_PLAYER_READY_FOR_CUTSCENE;
	N_PLAYER[crypt_str("IS_PLAYER_TARGETTING_ENTITY")] = PLAYER::IS_PLAYER_TARGETTING_ENTITY;
	N_PLAYER[crypt_str("GET_PLAYER_TARGET_ENTITY")] = PLAYER::GET_PLAYER_TARGET_ENTITY;
	N_PLAYER[crypt_str("IS_PLAYER_FREE_AIMING")] = PLAYER::IS_PLAYER_FREE_AIMING;
	N_PLAYER[crypt_str("IS_PLAYER_FREE_AIMING_AT_ENTITY")] = PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY;
	N_PLAYER[crypt_str("GET_ENTITY_PLAYER_IS_FREE_AIMING_AT")] = PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT;
	N_PLAYER[crypt_str("SET_PLAYER_LOCKON_RANGE_OVERRIDE")] = PLAYER::SET_PLAYER_LOCKON_RANGE_OVERRIDE;
	N_PLAYER[crypt_str("SET_PLAYER_CAN_DO_DRIVE_BY")] = PLAYER::SET_PLAYER_CAN_DO_DRIVE_BY;
	N_PLAYER[crypt_str("SET_PLAYER_CAN_BE_HASSLED_BY_GANGS")] = PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS;
	N_PLAYER[crypt_str("SET_PLAYER_CAN_USE_COVER")] = PLAYER::SET_PLAYER_CAN_USE_COVER;
	N_PLAYER[crypt_str("IS_PLAYER_TARGETTING_ANYTHING")] = PLAYER::IS_PLAYER_TARGETTING_ANYTHING;
	N_PLAYER[crypt_str("SET_PLAYER_SPRINT")] = PLAYER::SET_PLAYER_SPRINT;
	N_PLAYER[crypt_str("RESET_PLAYER_STAMINA")] = PLAYER::RESET_PLAYER_STAMINA;
	N_PLAYER[crypt_str("RESTORE_PLAYER_STAMINA")] = PLAYER::RESTORE_PLAYER_STAMINA;
	N_PLAYER[crypt_str("GET_PLAYER_SPRINT_STAMINA_REMAINING")] = PLAYER::GET_PLAYER_SPRINT_STAMINA_REMAINING;
	N_PLAYER[crypt_str("GET_PLAYER_SPRINT_TIME_REMAINING")] = PLAYER::GET_PLAYER_SPRINT_TIME_REMAINING;
	N_PLAYER[crypt_str("GET_PLAYER_UNDERWATER_TIME_REMAINING")] = PLAYER::GET_PLAYER_UNDERWATER_TIME_REMAINING;
	N_PLAYER[crypt_str("GET_PLAYER_GROUP")] = PLAYER::GET_PLAYER_GROUP;
	N_PLAYER[crypt_str("GET_PLAYER_MAX_ARMOUR")] = PLAYER::GET_PLAYER_MAX_ARMOUR;
	N_PLAYER[crypt_str("IS_PLAYER_CONTROL_ON")] = PLAYER::IS_PLAYER_CONTROL_ON;
	N_PLAYER[crypt_str("_IS_PLAYER_CAM_CONTROL_DISABLED")] = PLAYER::_IS_PLAYER_CAM_CONTROL_DISABLED;
	N_PLAYER[crypt_str("IS_PLAYER_CLIMBING")] = PLAYER::IS_PLAYER_CLIMBING;
	N_PLAYER[crypt_str("IS_PLAYER_BEING_ARRESTED")] = PLAYER::IS_PLAYER_BEING_ARRESTED;
	N_PLAYER[crypt_str("GET_PLAYERS_LAST_VEHICLE")] = PLAYER::GET_PLAYERS_LAST_VEHICLE;
	N_PLAYER[crypt_str("GET_PLAYER_INDEX")] = PLAYER::GET_PLAYER_INDEX;
	N_PLAYER[crypt_str("INT_TO_PLAYERINDEX")] = PLAYER::INT_TO_PLAYERINDEX;
	N_PLAYER[crypt_str("INT_TO_PARTICIPANTINDEX")] = PLAYER::INT_TO_PARTICIPANTINDEX;
	N_PLAYER[crypt_str("GET_TIME_SINCE_PLAYER_HIT_VEHICLE")] = PLAYER::GET_TIME_SINCE_PLAYER_HIT_VEHICLE;
	N_PLAYER[crypt_str("GET_TIME_SINCE_PLAYER_HIT_PED")] = PLAYER::GET_TIME_SINCE_PLAYER_HIT_PED;
	N_PLAYER[crypt_str("GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT")] = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT;
	N_PLAYER[crypt_str("GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC")] = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC;
	N_PLAYER[crypt_str("IS_PLAYER_FREE_FOR_AMBIENT_TASK")] = PLAYER::IS_PLAYER_FREE_FOR_AMBIENT_TASK;
	N_PLAYER[crypt_str("PLAYER_ID")] = PLAYER::PLAYER_ID;
	N_PLAYER[crypt_str("PLAYER_PED_ID")] = PLAYER::PLAYER_PED_ID;
	N_PLAYER[crypt_str("NETWORK_PLAYER_ID_TO_INT")] = PLAYER::NETWORK_PLAYER_ID_TO_INT;
	N_PLAYER[crypt_str("SET_PLAYER_INVINCIBLE")] = PLAYER::SET_PLAYER_INVINCIBLE;
	N_PLAYER[crypt_str("GET_PLAYER_INVINCIBLE")] = PLAYER::GET_PLAYER_INVINCIBLE;
	N_PLAYER[crypt_str("REMOVE_PLAYER_HELMET")] = PLAYER::REMOVE_PLAYER_HELMET;
	N_PLAYER[crypt_str("GIVE_PLAYER_RAGDOLL_CONTROL")] = PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL;
	N_PLAYER[crypt_str("SET_PLAYER_LOCKON")] = PLAYER::SET_PLAYER_LOCKON;
	N_PLAYER[crypt_str("SET_PLAYER_TARGETING_MODE")] = PLAYER::SET_PLAYER_TARGETING_MODE;
	N_PLAYER[crypt_str("CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED")] = PLAYER::CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED;
	N_PLAYER[crypt_str("HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED")] = PLAYER::HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED;
	N_PLAYER[crypt_str("HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED")] = PLAYER::HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED;
	N_PLAYER[crypt_str("SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE")] = PLAYER::SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE;
	N_PLAYER[crypt_str("SET_SWIM_MULTIPLIER_FOR_PLAYER")] = PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER;
	N_PLAYER[crypt_str("SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER")] = PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER;
	N_PLAYER[crypt_str("GET_TIME_SINCE_LAST_DEATH")] = PLAYER::GET_TIME_SINCE_LAST_DEATH;
	N_PLAYER[crypt_str("SET_PLAYER_FORCED_AIM")] = PLAYER::SET_PLAYER_FORCED_AIM;
	N_PLAYER[crypt_str("SET_PLAYER_FORCED_ZOOM")] = PLAYER::SET_PLAYER_FORCED_ZOOM;
	N_PLAYER[crypt_str("SET_PLAYER_FORCE_SKIP_AIM_INTRO")] = PLAYER::SET_PLAYER_FORCE_SKIP_AIM_INTRO;
	N_PLAYER[crypt_str("DISABLE_PLAYER_FIRING")] = PLAYER::DISABLE_PLAYER_FIRING;
	N_PLAYER[crypt_str("SET_DISABLE_AMBIENT_MELEE_MOVE")] = PLAYER::SET_DISABLE_AMBIENT_MELEE_MOVE;
	N_PLAYER[crypt_str("SET_PLAYER_MAX_ARMOUR")] = PLAYER::SET_PLAYER_MAX_ARMOUR;
	N_PLAYER[crypt_str("START_PLAYER_TELEPORT")] = PLAYER::START_PLAYER_TELEPORT;
	N_PLAYER[crypt_str("_HAS_PLAYER_TELEPORT_FINISHED")] = PLAYER::_HAS_PLAYER_TELEPORT_FINISHED;
	N_PLAYER[crypt_str("STOP_PLAYER_TELEPORT")] = PLAYER::STOP_PLAYER_TELEPORT;
	N_PLAYER[crypt_str("IS_PLAYER_TELEPORT_ACTIVE")] = PLAYER::IS_PLAYER_TELEPORT_ACTIVE;
	N_PLAYER[crypt_str("SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER")] = PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER;
	N_PLAYER[crypt_str("SET_PLAYER_WEAPON_DAMAGE_MODIFIER")] = PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_WEAPON_DEFENSE_MODIFIER")] = PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER")] = PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER")] = PLAYER::SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_VEHICLE_DAMAGE_MODIFIER")] = PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_VEHICLE_DEFENSE_MODIFIER")] = PLAYER::SET_PLAYER_VEHICLE_DEFENSE_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_PARACHUTE_TINT_INDEX")] = PLAYER::SET_PLAYER_PARACHUTE_TINT_INDEX;
	N_PLAYER[crypt_str("CAN_PED_HEAR_PLAYER")] = PLAYER::CAN_PED_HEAR_PLAYER;
	N_PLAYER[crypt_str("SIMULATE_PLAYER_INPUT_GAIT")] = PLAYER::SIMULATE_PLAYER_INPUT_GAIT;
	N_PLAYER[crypt_str("RESET_PLAYER_INPUT_GAIT")] = PLAYER::RESET_PLAYER_INPUT_GAIT;
	N_PLAYER[crypt_str("SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE")] = PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE;
	N_PLAYER[crypt_str("SET_PLAYER_STEALTH_PERCEPTION_MODIFIER")] = PLAYER::SET_PLAYER_STEALTH_PERCEPTION_MODIFIER;
	N_PLAYER[crypt_str("SET_PLAYER_SIMULATE_AIMING")] = PLAYER::SET_PLAYER_SIMULATE_AIMING;
	N_PLAYER[crypt_str("SET_PLAYER_CLOTH_PIN_FRAMES")] = PLAYER::SET_PLAYER_CLOTH_PIN_FRAMES;
	N_PLAYER[crypt_str("SET_PLAYER_CLOTH_PACKAGE_INDEX")] = PLAYER::SET_PLAYER_CLOTH_PACKAGE_INDEX;
	N_PLAYER[crypt_str("DISABLE_PLAYER_VEHICLE_REWARDS")] = PLAYER::DISABLE_PLAYER_VEHICLE_REWARDS;
	auto N_ENTITY = lua.create_table();
	N_ENTITY[crypt_str("DOES_ENTITY_EXIST")] = ENTITY::DOES_ENTITY_EXIST;
	N_ENTITY[crypt_str("DOES_ENTITY_BELONG_TO_THIS_SCRIPT")] = ENTITY::DOES_ENTITY_BELONG_TO_THIS_SCRIPT;
	N_ENTITY[crypt_str("DOES_ENTITY_HAVE_DRAWABLE")] = ENTITY::DOES_ENTITY_HAVE_DRAWABLE;
	N_ENTITY[crypt_str("DOES_ENTITY_HAVE_PHYSICS")] = ENTITY::DOES_ENTITY_HAVE_PHYSICS;
	N_ENTITY[crypt_str("HAS_ENTITY_ANIM_FINISHED")] = ENTITY::HAS_ENTITY_ANIM_FINISHED;
	N_ENTITY[crypt_str("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT")] = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT;
	N_ENTITY[crypt_str("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED")] = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED;
	N_ENTITY[crypt_str("HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE")] = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE;
	N_ENTITY[crypt_str("HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY")] = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY;
	N_ENTITY[crypt_str("HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT")] = ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT;
	N_ENTITY[crypt_str("HAS_ENTITY_COLLIDED_WITH_ANYTHING")] = ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING;
	N_ENTITY[crypt_str("GET_LAST_MATERIAL_HIT_BY_ENTITY")] = ENTITY::GET_LAST_MATERIAL_HIT_BY_ENTITY;
	N_ENTITY[crypt_str("GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY")] = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY;
	N_ENTITY[crypt_str("FORCE_ENTITY_AI_AND_ANIMATION_UPDATE")] = ENTITY::FORCE_ENTITY_AI_AND_ANIMATION_UPDATE;
	N_ENTITY[crypt_str("GET_ENTITY_ANIM_CURRENT_TIME")] = ENTITY::GET_ENTITY_ANIM_CURRENT_TIME;
	N_ENTITY[crypt_str("GET_ENTITY_ANIM_TOTAL_TIME")] = ENTITY::GET_ENTITY_ANIM_TOTAL_TIME;
	N_ENTITY[crypt_str("_GET_ANIM_DURATION")] = ENTITY::_GET_ANIM_DURATION;
	N_ENTITY[crypt_str("GET_ENTITY_ATTACHED_TO")] = ENTITY::GET_ENTITY_ATTACHED_TO;
	N_ENTITY[crypt_str("GET_ENTITY_COORDS")] = ENTITY::GET_ENTITY_COORDS;
	N_ENTITY[crypt_str("GET_ENTITY_FORWARD_VECTOR")] = ENTITY::GET_ENTITY_FORWARD_VECTOR;
	N_ENTITY[crypt_str("GET_ENTITY_FORWARD_X")] = ENTITY::GET_ENTITY_FORWARD_X;
	N_ENTITY[crypt_str("GET_ENTITY_FORWARD_Y")] = ENTITY::GET_ENTITY_FORWARD_Y;
	N_ENTITY[crypt_str("GET_ENTITY_HEADING")] = ENTITY::GET_ENTITY_HEADING;
	N_ENTITY[crypt_str("_GET_ENTITY_PHYSICS_HEADING")] = ENTITY::_GET_ENTITY_PHYSICS_HEADING;
	N_ENTITY[crypt_str("GET_ENTITY_HEALTH")] = ENTITY::GET_ENTITY_HEALTH;
	N_ENTITY[crypt_str("GET_ENTITY_MAX_HEALTH")] = ENTITY::GET_ENTITY_MAX_HEALTH;
	N_ENTITY[crypt_str("SET_ENTITY_MAX_HEALTH")] = ENTITY::SET_ENTITY_MAX_HEALTH;
	N_ENTITY[crypt_str("GET_ENTITY_HEIGHT")] = ENTITY::GET_ENTITY_HEIGHT;
	N_ENTITY[crypt_str("GET_ENTITY_HEIGHT_ABOVE_GROUND")] = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND;
	N_ENTITY[crypt_str("GET_ENTITY_MATRIX")] = ENTITY::GET_ENTITY_MATRIX;
	N_ENTITY[crypt_str("GET_ENTITY_MODEL")] = ENTITY::GET_ENTITY_MODEL;
	N_ENTITY[crypt_str("GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS")] = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS;
	N_ENTITY[crypt_str("GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS")] = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS;
	N_ENTITY[crypt_str("GET_ENTITY_PITCH")] = ENTITY::GET_ENTITY_PITCH;
	N_ENTITY[crypt_str("GET_ENTITY_QUATERNION")] = ENTITY::GET_ENTITY_QUATERNION;
	N_ENTITY[crypt_str("GET_ENTITY_ROLL")] = ENTITY::GET_ENTITY_ROLL;
	N_ENTITY[crypt_str("GET_ENTITY_ROTATION")] = ENTITY::GET_ENTITY_ROTATION;
	N_ENTITY[crypt_str("GET_ENTITY_ROTATION_VELOCITY")] = ENTITY::GET_ENTITY_ROTATION_VELOCITY;
	N_ENTITY[crypt_str("GET_ENTITY_SCRIPT")] = ENTITY::GET_ENTITY_SCRIPT;
	N_ENTITY[crypt_str("GET_ENTITY_SPEED")] = ENTITY::GET_ENTITY_SPEED;
	N_ENTITY[crypt_str("GET_ENTITY_SPEED_VECTOR")] = ENTITY::GET_ENTITY_SPEED_VECTOR;
	N_ENTITY[crypt_str("GET_ENTITY_UPRIGHT_VALUE")] = ENTITY::GET_ENTITY_UPRIGHT_VALUE;
	N_ENTITY[crypt_str("GET_ENTITY_VELOCITY")] = ENTITY::GET_ENTITY_VELOCITY;
	N_ENTITY[crypt_str("GET_OBJECT_INDEX_FROM_ENTITY_INDEX")] = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX;
	N_ENTITY[crypt_str("GET_PED_INDEX_FROM_ENTITY_INDEX")] = ENTITY::GET_PED_INDEX_FROM_ENTITY_INDEX;
	N_ENTITY[crypt_str("GET_VEHICLE_INDEX_FROM_ENTITY_INDEX")] = ENTITY::GET_VEHICLE_INDEX_FROM_ENTITY_INDEX;
	N_ENTITY[crypt_str("GET_WORLD_POSITION_OF_ENTITY_BONE")] = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE;
	N_ENTITY[crypt_str("GET_NEAREST_PLAYER_TO_ENTITY")] = ENTITY::GET_NEAREST_PLAYER_TO_ENTITY;
	N_ENTITY[crypt_str("GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM")] = ENTITY::GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM;
	N_ENTITY[crypt_str("GET_ENTITY_TYPE")] = ENTITY::GET_ENTITY_TYPE;
	N_ENTITY[crypt_str("_GET_ENTITY_POPULATION_TYPE")] = ENTITY::_GET_ENTITY_POPULATION_TYPE;
	N_ENTITY[crypt_str("IS_AN_ENTITY")] = ENTITY::IS_AN_ENTITY;
	N_ENTITY[crypt_str("IS_ENTITY_A_PED")] = ENTITY::IS_ENTITY_A_PED;
	N_ENTITY[crypt_str("IS_ENTITY_A_MISSION_ENTITY")] = ENTITY::IS_ENTITY_A_MISSION_ENTITY;
	N_ENTITY[crypt_str("IS_ENTITY_A_VEHICLE")] = ENTITY::IS_ENTITY_A_VEHICLE;
	N_ENTITY[crypt_str("IS_ENTITY_AN_OBJECT")] = ENTITY::IS_ENTITY_AN_OBJECT;
	N_ENTITY[crypt_str("IS_ENTITY_AT_COORD")] = ENTITY::IS_ENTITY_AT_COORD;
	N_ENTITY[crypt_str("IS_ENTITY_AT_ENTITY")] = ENTITY::IS_ENTITY_AT_ENTITY;
	N_ENTITY[crypt_str("IS_ENTITY_ATTACHED")] = ENTITY::IS_ENTITY_ATTACHED;
	N_ENTITY[crypt_str("IS_ENTITY_ATTACHED_TO_ANY_OBJECT")] = ENTITY::IS_ENTITY_ATTACHED_TO_ANY_OBJECT;
	N_ENTITY[crypt_str("IS_ENTITY_ATTACHED_TO_ANY_PED")] = ENTITY::IS_ENTITY_ATTACHED_TO_ANY_PED;
	N_ENTITY[crypt_str("IS_ENTITY_ATTACHED_TO_ANY_VEHICLE")] = ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE;
	N_ENTITY[crypt_str("IS_ENTITY_ATTACHED_TO_ENTITY")] = ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY;
	N_ENTITY[crypt_str("IS_ENTITY_DEAD")] = ENTITY::IS_ENTITY_DEAD;
	N_ENTITY[crypt_str("IS_ENTITY_IN_AIR")] = ENTITY::IS_ENTITY_IN_AIR;
	N_ENTITY[crypt_str("IS_ENTITY_IN_AREA")] = ENTITY::IS_ENTITY_IN_AREA;
	N_ENTITY[crypt_str("IS_ENTITY_IN_ZONE")] = ENTITY::IS_ENTITY_IN_ZONE;
	N_ENTITY[crypt_str("IS_ENTITY_IN_WATER")] = ENTITY::IS_ENTITY_IN_WATER;
	N_ENTITY[crypt_str("IS_ENTITY_ON_SCREEN")] = ENTITY::IS_ENTITY_ON_SCREEN;
	N_ENTITY[crypt_str("IS_ENTITY_PLAYING_ANIM")] = ENTITY::IS_ENTITY_PLAYING_ANIM;
	N_ENTITY[crypt_str("IS_ENTITY_STATIC")] = ENTITY::IS_ENTITY_STATIC;
	N_ENTITY[crypt_str("IS_ENTITY_VISIBLE")] = ENTITY::IS_ENTITY_VISIBLE;
	N_ENTITY[crypt_str("IS_ENTITY_VISIBLE_TO_SCRIPT")] = ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT;
	N_ENTITY[crypt_str("IS_ENTITY_OCCLUDED")] = ENTITY::IS_ENTITY_OCCLUDED;
	N_ENTITY[crypt_str("WOULD_ENTITY_BE_OCCLUDED")] = ENTITY::WOULD_ENTITY_BE_OCCLUDED;
	N_ENTITY[crypt_str("IS_ENTITY_WAITING_FOR_WORLD_COLLISION")] = ENTITY::IS_ENTITY_WAITING_FOR_WORLD_COLLISION;
	N_ENTITY[crypt_str("DELETE_ENTITY")] = ENTITY::DELETE_ENTITY;
	N_ENTITY[crypt_str("DETACH_ENTITY")] = ENTITY::DETACH_ENTITY;
	N_ENTITY[crypt_str("FREEZE_ENTITY_POSITION")] = ENTITY::FREEZE_ENTITY_POSITION;
	N_ENTITY[crypt_str("_SET_ENTITY_SOMETHING")] = ENTITY::_SET_ENTITY_SOMETHING;
	N_ENTITY[crypt_str("PLAY_ENTITY_ANIM")] = ENTITY::PLAY_ENTITY_ANIM;
	N_ENTITY[crypt_str("STOP_ENTITY_ANIM")] = ENTITY::STOP_ENTITY_ANIM;
	N_ENTITY[crypt_str("SET_ENTITY_ANIM_CURRENT_TIME")] = ENTITY::SET_ENTITY_ANIM_CURRENT_TIME;
	N_ENTITY[crypt_str("SET_ENTITY_ANIM_SPEED")] = ENTITY::SET_ENTITY_ANIM_SPEED;
	N_ENTITY[crypt_str("SET_ENTITY_COLLISION")] = ENTITY::SET_ENTITY_COLLISION;
	N_ENTITY[crypt_str("_GET_ENTITY_COLLISON_DISABLED")] = ENTITY::_GET_ENTITY_COLLISON_DISABLED;
	N_ENTITY[crypt_str("_SET_ENTITY_COLLISION_2")] = ENTITY::_SET_ENTITY_COLLISION_2;
	N_ENTITY[crypt_str("_SET_ENTITY_COORDS_2")] = ENTITY::_SET_ENTITY_COORDS_2;
	N_ENTITY[crypt_str("SET_ENTITY_COORDS")] = ENTITY::SET_ENTITY_COORDS;
	N_ENTITY[crypt_str("SET_ENTITY_COORDS_NO_OFFSET")] = ENTITY::SET_ENTITY_COORDS_NO_OFFSET;
	N_ENTITY[crypt_str("SET_ENTITY_DYNAMIC")] = ENTITY::SET_ENTITY_DYNAMIC;
	N_ENTITY[crypt_str("SET_ENTITY_HEADING")] = ENTITY::SET_ENTITY_HEADING;
	N_ENTITY[crypt_str("SET_ENTITY_HEALTH")] = ENTITY::SET_ENTITY_HEALTH;
	N_ENTITY[crypt_str("SET_ENTITY_INVINCIBLE")] = ENTITY::SET_ENTITY_INVINCIBLE;
	N_ENTITY[crypt_str("SET_ENTITY_IS_TARGET_PRIORITY")] = ENTITY::SET_ENTITY_IS_TARGET_PRIORITY;
	N_ENTITY[crypt_str("SET_ENTITY_LIGHTS")] = ENTITY::SET_ENTITY_LIGHTS;
	N_ENTITY[crypt_str("SET_ENTITY_MAX_SPEED")] = ENTITY::SET_ENTITY_MAX_SPEED;
	N_ENTITY[crypt_str("SET_ENTITY_ONLY_DAMAGED_BY_PLAYER")] = ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER;
	N_ENTITY[crypt_str("SET_ENTITY_QUATERNION")] = ENTITY::SET_ENTITY_QUATERNION;
	N_ENTITY[crypt_str("SET_ENTITY_RECORDS_COLLISIONS")] = ENTITY::SET_ENTITY_RECORDS_COLLISIONS;
	N_ENTITY[crypt_str("SET_ENTITY_ROTATION")] = ENTITY::SET_ENTITY_ROTATION;
	N_ENTITY[crypt_str("SET_ENTITY_VISIBLE")] = ENTITY::SET_ENTITY_VISIBLE;
	N_ENTITY[crypt_str("SET_ENTITY_VELOCITY")] = ENTITY::SET_ENTITY_VELOCITY;
	N_ENTITY[crypt_str("SET_ENTITY_HAS_GRAVITY")] = ENTITY::SET_ENTITY_HAS_GRAVITY;
	N_ENTITY[crypt_str("SET_ENTITY_LOD_DIST")] = ENTITY::SET_ENTITY_LOD_DIST;
	N_ENTITY[crypt_str("SET_ENTITY_ALPHA")] = ENTITY::SET_ENTITY_ALPHA;
	N_ENTITY[crypt_str("GET_ENTITY_ALPHA")] = ENTITY::GET_ENTITY_ALPHA;
	N_ENTITY[crypt_str("SET_ENTITY_NO_COLLISION_ENTITY")] = ENTITY::SET_ENTITY_NO_COLLISION_ENTITY;


	auto N_PED = lua.create_table();
	N_PED[crypt_str("CREATE_PED")] = PED::CREATE_PED;
	N_PED[crypt_str("DELETE_PED")] = PED::DELETE_PED;
	N_PED[crypt_str("CLONE_PED")] = PED::CLONE_PED;
	N_PED[crypt_str("CLONE_PED_TO_TARGET")] = PED::CLONE_PED_TO_TARGET;
	N_PED[crypt_str("IS_PED_IN_VEHICLE")] = PED::IS_PED_IN_VEHICLE;
	N_PED[crypt_str("IS_PED_IN_MODEL")] = PED::IS_PED_IN_MODEL;
	N_PED[crypt_str("IS_PED_IN_ANY_VEHICLE")] = PED::IS_PED_IN_ANY_VEHICLE;
	N_PED[crypt_str("IS_COP_PED_IN_AREA_3D")] = PED::IS_COP_PED_IN_AREA_3D;
	N_PED[crypt_str("IS_PED_INJURED")] = PED::IS_PED_INJURED;
	N_PED[crypt_str("IS_PED_HURT")] = PED::IS_PED_HURT;
	N_PED[crypt_str("IS_PED_FATALLY_INJURED")] = PED::IS_PED_FATALLY_INJURED;
	N_PED[crypt_str("IS_PED_DEAD_OR_DYING")] = PED::IS_PED_DEAD_OR_DYING;
	N_PED[crypt_str("IS_CONVERSATION_PED_DEAD")] = PED::IS_CONVERSATION_PED_DEAD;
	N_PED[crypt_str("IS_PED_AIMING_FROM_COVER")] = PED::IS_PED_AIMING_FROM_COVER;
	N_PED[crypt_str("IS_PED_RELOADING")] = PED::IS_PED_RELOADING;
	N_PED[crypt_str("IS_PED_A_PLAYER")] = PED::IS_PED_A_PLAYER;
	N_PED[crypt_str("CREATE_PED_INSIDE_VEHICLE")] = PED::CREATE_PED_INSIDE_VEHICLE;
	N_PED[crypt_str("SET_PED_DESIRED_HEADING")] = PED::SET_PED_DESIRED_HEADING;
	N_PED[crypt_str("_FREEZE_PED_CAMERA_ROTATION")] = PED::_FREEZE_PED_CAMERA_ROTATION;
	N_PED[crypt_str("IS_PED_FACING_PED")] = PED::IS_PED_FACING_PED;
	N_PED[crypt_str("IS_PED_IN_MELEE_COMBAT")] = PED::IS_PED_IN_MELEE_COMBAT;
	N_PED[crypt_str("IS_PED_STOPPED")] = PED::IS_PED_STOPPED;
	N_PED[crypt_str("IS_PED_SHOOTING_IN_AREA")] = PED::IS_PED_SHOOTING_IN_AREA;
	N_PED[crypt_str("IS_ANY_PED_SHOOTING_IN_AREA")] = PED::IS_ANY_PED_SHOOTING_IN_AREA;
	N_PED[crypt_str("IS_PED_SHOOTING")] = PED::IS_PED_SHOOTING;
	N_PED[crypt_str("SET_PED_ACCURACY")] = PED::SET_PED_ACCURACY;
	N_PED[crypt_str("GET_PED_ACCURACY")] = PED::GET_PED_ACCURACY;
	N_PED[crypt_str("IS_PED_MODEL")] = PED::IS_PED_MODEL;
	N_PED[crypt_str("EXPLODE_PED_HEAD")] = PED::EXPLODE_PED_HEAD;
	N_PED[crypt_str("REMOVE_PED_ELEGANTLY")] = PED::REMOVE_PED_ELEGANTLY;
	N_PED[crypt_str("ADD_ARMOUR_TO_PED")] = PED::ADD_ARMOUR_TO_PED;
	N_PED[crypt_str("SET_PED_ARMOUR")] = PED::SET_PED_ARMOUR;
	N_PED[crypt_str("SET_PED_INTO_VEHICLE")] = PED::SET_PED_INTO_VEHICLE;
	N_PED[crypt_str("SET_PED_ALLOW_VEHICLES_OVERRIDE")] = PED::SET_PED_ALLOW_VEHICLES_OVERRIDE;
	N_PED[crypt_str("CAN_CREATE_RANDOM_PED")] = PED::CAN_CREATE_RANDOM_PED;
	N_PED[crypt_str("CREATE_RANDOM_PED")] = PED::CREATE_RANDOM_PED;
	N_PED[crypt_str("CREATE_RANDOM_PED_AS_DRIVER")] = PED::CREATE_RANDOM_PED_AS_DRIVER;
	N_PED[crypt_str("CAN_CREATE_RANDOM_DRIVER")] = PED::CAN_CREATE_RANDOM_DRIVER;
	N_PED[crypt_str("CAN_CREATE_RANDOM_BIKE_RIDER")] = PED::CAN_CREATE_RANDOM_BIKE_RIDER;
	N_PED[crypt_str("SET_PED_MOVE_ANIMS_BLEND_OUT")] = PED::SET_PED_MOVE_ANIMS_BLEND_OUT;
	N_PED[crypt_str("SET_PED_CAN_BE_DRAGGED_OUT")] = PED::SET_PED_CAN_BE_DRAGGED_OUT;
	N_PED[crypt_str("IS_PED_MALE")] = PED::IS_PED_MALE;
	N_PED[crypt_str("IS_PED_HUMAN")] = PED::IS_PED_HUMAN;
	N_PED[crypt_str("GET_VEHICLE_PED_IS_IN")] = PED::GET_VEHICLE_PED_IS_IN;
	N_PED[crypt_str("RESET_PED_LAST_VEHICLE")] = PED::RESET_PED_LAST_VEHICLE;
	N_PED[crypt_str("SET_PED_DENSITY_MULTIPLIER_THIS_FRAME")] = PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME;
	N_PED[crypt_str("SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME")] = PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME;
	N_PED[crypt_str("SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME")] = PED::SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME;
	N_PED[crypt_str("SET_PED_NON_CREATION_AREA")] = PED::SET_PED_NON_CREATION_AREA;
	N_PED[crypt_str("CLEAR_PED_NON_CREATION_AREA")] = PED::CLEAR_PED_NON_CREATION_AREA;
	N_PED[crypt_str("IS_PED_ON_MOUNT")] = PED::IS_PED_ON_MOUNT;
	N_PED[crypt_str("GET_MOUNT")] = PED::GET_MOUNT;
	N_PED[crypt_str("IS_PED_ON_VEHICLE")] = PED::IS_PED_ON_VEHICLE;
	N_PED[crypt_str("IS_PED_ON_SPECIFIC_VEHICLE")] = PED::IS_PED_ON_SPECIFIC_VEHICLE;
	N_PED[crypt_str("SET_PED_MONEY")] = PED::SET_PED_MONEY;
	N_PED[crypt_str("GET_PED_MONEY")] = PED::GET_PED_MONEY;
	N_PED[crypt_str("SET_PED_SUFFERS_CRITICAL_HITS")] = PED::SET_PED_SUFFERS_CRITICAL_HITS;
	N_PED[crypt_str("IS_PED_SITTING_IN_VEHICLE")] = PED::IS_PED_SITTING_IN_VEHICLE;
	N_PED[crypt_str("IS_PED_SITTING_IN_ANY_VEHICLE")] = PED::IS_PED_SITTING_IN_ANY_VEHICLE;
	N_PED[crypt_str("IS_PED_ON_FOOT")] = PED::IS_PED_ON_FOOT;
	N_PED[crypt_str("IS_PED_ON_ANY_BIKE")] = PED::IS_PED_ON_ANY_BIKE;
	N_PED[crypt_str("IS_PED_PLANTING_BOMB")] = PED::IS_PED_PLANTING_BOMB;
	N_PED[crypt_str("IS_PED_IN_ANY_BOAT")] = PED::IS_PED_IN_ANY_BOAT;
	N_PED[crypt_str("IS_PED_IN_ANY_HELI")] = PED::IS_PED_IN_ANY_HELI;
	N_PED[crypt_str("IS_PED_IN_ANY_PLANE")] = PED::IS_PED_IN_ANY_PLANE;
	N_PED[crypt_str("IS_PED_IN_FLYING_VEHICLE")] = PED::IS_PED_IN_FLYING_VEHICLE;
	N_PED[crypt_str("GET_PED_ARMOUR")] = PED::GET_PED_ARMOUR;
	N_PED[crypt_str("SET_PED_STAY_IN_VEHICLE_WHEN_JACKED")] = PED::SET_PED_STAY_IN_VEHICLE_WHEN_JACKED;
	N_PED[crypt_str("SET_PED_CAN_BE_SHOT_IN_VEHICLE")] = PED::SET_PED_CAN_BE_SHOT_IN_VEHICLE;
	N_PED[crypt_str("GET_PED_LAST_DAMAGE_BONE")] = PED::GET_PED_LAST_DAMAGE_BONE;
	N_PED[crypt_str("SET_AI_WEAPON_DAMAGE_MODIFIER")] = PED::SET_AI_WEAPON_DAMAGE_MODIFIER;
	N_PED[crypt_str("RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER")] = PED::RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER;
	N_PED[crypt_str("IS_PED_IN_PARACHUTE_FREE_FALL")] = PED::IS_PED_IN_PARACHUTE_FREE_FALL;
	N_PED[crypt_str("IS_PED_FALLING")] = PED::IS_PED_FALLING;
	N_PED[crypt_str("IS_PED_JUMPING")] = PED::IS_PED_JUMPING;
	N_PED[crypt_str("IS_PED_CLIMBING")] = PED::IS_PED_CLIMBING;
	N_PED[crypt_str("IS_PED_VAULTING")] = PED::IS_PED_VAULTING;
	N_PED[crypt_str("IS_PED_DIVING")] = PED::IS_PED_DIVING;
	N_PED[crypt_str("IS_PED_JUMPING_OUT_OF_VEHICLE")] = PED::IS_PED_JUMPING_OUT_OF_VEHICLE;
	N_PED[crypt_str("SET_PED_DUCKING")] = PED::SET_PED_DUCKING;
	N_PED[crypt_str("IS_PED_DUCKING")] = PED::IS_PED_DUCKING;
	N_PED[crypt_str("IS_PED_IN_ANY_TAXI")] = PED::IS_PED_IN_ANY_TAXI;
	N_PED[crypt_str("SET_PED_HEARING_RANGE")] = PED::SET_PED_SHOOT_RATE;
	N_PED[crypt_str("SET_COMBAT_FLOAT")] = PED::SET_COMBAT_FLOAT;
	N_PED[crypt_str("GET_COMBAT_FLOAT")] = PED::GET_COMBAT_FLOAT;
	N_PED[crypt_str("GET_GROUP_SIZE")] = PED::GET_GROUP_SIZE;
	N_PED[crypt_str("GET_PED_GROUP_INDEX")] = PED::GET_PED_GROUP_INDEX;
	N_PED[crypt_str("IS_PED_IN_GROUP")] = PED::IS_PED_IN_GROUP;
	N_PED[crypt_str("GET_VEHICLE_PED_IS_USING")] = PED::GET_VEHICLE_PED_IS_USING;
	N_PED[crypt_str("SET_PED_GRAVITY")] = PED::SET_PED_GRAVITY;
	N_PED[crypt_str("APPLY_DAMAGE_TO_PED")] = PED::APPLY_DAMAGE_TO_PED;
	N_PED[crypt_str("SET_PED_ALLOWED_TO_DUCK")] = PED::SET_PED_ALLOWED_TO_DUCK;
	N_PED[crypt_str("GET_PED_TYPE")] = PED::GET_PED_TYPE;
	N_PED[crypt_str("SET_PED_MAX_HEALTH")] = PED::SET_PED_MAX_HEALTH;
	N_PED[crypt_str("GET_PED_MAX_HEALTH")] = PED::GET_PED_MAX_HEALTH;
	N_PED[crypt_str("SET_PED_MAX_TIME_IN_WATER")] = PED::SET_PED_MAX_TIME_IN_WATER;
	N_PED[crypt_str("SET_PED_MAX_TIME_UNDERWATER")] = PED::SET_PED_MAX_TIME_UNDERWATER;
	N_PED[crypt_str("SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE")] = PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE;
	N_PED[crypt_str("SET_PED_KEEP_TASK")] = PED::SET_PED_KEEP_TASK;
	N_PED[crypt_str("IS_PED_SWIMMING")] = PED::IS_PED_SWIMMING;
	N_PED[crypt_str("SET_PED_COORDS_KEEP_VEHICLE")] = PED::SET_PED_COORDS_KEEP_VEHICLE;
	N_PED[crypt_str("SET_PED_DIES_IN_VEHICLE")] = PED::SET_PED_DIES_IN_VEHICLE;
	N_PED[crypt_str("SET_PED_AS_ENEMY")] = PED::SET_PED_AS_ENEMY;
	N_PED[crypt_str("IS_PED_IN_ANY_TRAIN")] = PED::IS_PED_IN_ANY_TRAIN;
	N_PED[crypt_str("IS_PED_GETTING_INTO_A_VEHICLE")] = PED::IS_PED_GETTING_INTO_A_VEHICLE;
	N_PED[crypt_str("IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE")] = PED::IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE;
	N_PED[crypt_str("SET_ENABLE_HANDCUFFS")] = PED::SET_ENABLE_HANDCUFFS;
	N_PED[crypt_str("SET_ENABLE_BOUND_ANKLES")] = PED::SET_ENABLE_BOUND_ANKLES;
	N_PED[crypt_str("SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE")] = PED::SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE;
	N_PED[crypt_str("SET_PED_MOVEMENT_CLIPSET")] = PED::SET_PED_MOVEMENT_CLIPSET;
	N_PED[crypt_str("SET_PED_IN_VEHICLE_CONTEXT")] = PED::SET_PED_IN_VEHICLE_CONTEXT;
	N_PED[crypt_str("SET_PED_ALTERNATE_MOVEMENT_ANIM")] = PED::SET_PED_ALTERNATE_MOVEMENT_ANIM;
	N_PED[crypt_str("GET_ANIM_INITIAL_OFFSET_POSITION")] = PED::GET_ANIM_INITIAL_OFFSET_POSITION;
	N_PED[crypt_str("GET_PED_PROP_INDEX")] = PED::GET_PED_PROP_INDEX;
	N_PED[crypt_str("SET_PED_PROP_INDEX")] = PED::SET_PED_PROP_INDEX;
	N_PED[crypt_str("KNOCK_OFF_PED_PROP")] = PED::KNOCK_OFF_PED_PROP;
	N_PED[crypt_str("GET_RANDOM_PED_AT_COORD")] = PED::GET_RANDOM_PED_AT_COORD;
	N_PED[crypt_str("GET_CLOSEST_PED")] = PED::GET_CLOSEST_PED;
	N_PED[crypt_str("CAN_PED_RAGDOLL")] = PED::CAN_PED_RAGDOLL;
	N_PED[crypt_str("SET_PED_TO_RAGDOLL")] = PED::SET_PED_TO_RAGDOLL;
	N_PED[crypt_str("SET_PED_TO_RAGDOLL_WITH_FALL")] = PED::SET_PED_TO_RAGDOLL_WITH_FALL;
	N_PED[crypt_str("SET_PED_RAGDOLL_ON_COLLISION")] = PED::SET_PED_RAGDOLL_ON_COLLISION;
	N_PED[crypt_str("IS_PED_RAGDOLL")] = PED::IS_PED_RAGDOLL;
	N_PED[crypt_str("IS_PED_RUNNING_RAGDOLL_TASK")] = PED::IS_PED_RUNNING_RAGDOLL_TASK;
	N_PED[crypt_str("RESET_PED_RAGDOLL_TIMER")] = PED::RESET_PED_RAGDOLL_TIMER;
	N_PED[crypt_str("SET_PED_CAN_RAGDOLL")] = PED::SET_PED_CAN_RAGDOLL;
	N_PED[crypt_str("RESET_PED_VISIBLE_DAMAGE")] = PED::RESET_PED_VISIBLE_DAMAGE;
	N_PED[crypt_str("CLEAR_PED_WETNESS")] = PED::CLEAR_PED_WETNESS;
	N_PED[crypt_str("SET_PED_WETNESS_HEIGHT")] = PED::SET_PED_WETNESS_HEIGHT;
	N_PED[crypt_str("SET_PED_WETNESS_ENABLED_THIS_FRAME")] = PED::SET_PED_WETNESS_ENABLED_THIS_FRAME;
	N_PED[crypt_str("SET_PED_SWEAT")] = PED::SET_PED_SWEAT;
	N_PED[crypt_str("_SET_PED_DECORATION")] = PED::_SET_PED_DECORATION;
	N_PED[crypt_str("GET_PED_BONE_COORDS")] = PED::GET_PED_BONE_COORDS;
	N_PED[crypt_str("PLAY_FACIAL_ANIM")] = PED::PLAY_FACIAL_ANIM;
	N_PED[crypt_str("SET_PED_SHOOTS_AT_COORD")] = PED::SET_PED_SHOOTS_AT_COORD;
	N_PED[crypt_str("GIVE_PED_HELMET")] = PED::GIVE_PED_HELMET;
	N_PED[crypt_str("REMOVE_PED_HELMET")] = PED::REMOVE_PED_HELMET;
	N_PED[crypt_str("SET_PED_MOTION_BLUR")] = PED::SET_PED_MOTION_BLUR;
	N_PED[crypt_str("SET_PED_CAN_SWITCH_WEAPON")] = PED::SET_PED_CAN_SWITCH_WEAPON;
	N_PED[crypt_str("SET_PED_COMBAT_MOVEMENT")] = PED::SET_PED_COMBAT_MOVEMENT;
	N_PED[crypt_str("GET_PED_COMBAT_MOVEMENT")] = PED::GET_PED_COMBAT_MOVEMENT;
	N_PED[crypt_str("IS_PED_PERFORMING_STEALTH_KILL")] = PED::IS_PED_PERFORMING_STEALTH_KILL;
	N_PED[crypt_str("SET_PED_CAPSULE")] = PED::SET_PED_CAPSULE;
	N_PED[crypt_str("SET_PED_LOD_MULTIPLIER")] = PED::SET_PED_LOD_MULTIPLIER;

	auto N_VEHICLE = lua.create_table();
	N_VEHICLE[crypt_str("CREATE_VEHICLE")] = VEHICLE::CREATE_VEHICLE;
	N_VEHICLE[crypt_str("DELETE_VEHICLE")] = VEHICLE::DELETE_VEHICLE;
	N_VEHICLE[crypt_str("SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON")] = VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON;
	N_VEHICLE[crypt_str("IS_VEHICLE_MODEL")] = VEHICLE::IS_VEHICLE_MODEL;
	N_VEHICLE[crypt_str("DOES_SCRIPT_VEHICLE_GENERATOR_EXIST")] = VEHICLE::DOES_SCRIPT_VEHICLE_GENERATOR_EXIST;
	N_VEHICLE[crypt_str("REMOVE_VEHICLE_UPSIDEDOWN_CHECK")] = VEHICLE::REMOVE_VEHICLE_UPSIDEDOWN_CHECK;
	N_VEHICLE[crypt_str("IS_VEHICLE_STOPPED")] = VEHICLE::IS_VEHICLE_STOPPED;
	N_VEHICLE[crypt_str("GET_VEHICLE_NUMBER_OF_PASSENGERS")] = VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS;
	N_VEHICLE[crypt_str("GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS")] = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS;
	N_VEHICLE[crypt_str("GET_VEHICLE_MODEL_NUMBER_OF_SEATS")] = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS;
	N_VEHICLE[crypt_str("SET_VEHICLE_OUT_OF_CONTROL")] = VEHICLE::SET_VEHICLE_OUT_OF_CONTROL;
	N_VEHICLE[crypt_str("SET_VEHICLE_TIMED_EXPLOSION")] = VEHICLE::SET_VEHICLE_TIMED_EXPLOSION;
	N_VEHICLE[crypt_str("SET_VEHICLE_COLOURS")] = VEHICLE::SET_VEHICLE_COLOURS;
	N_VEHICLE[crypt_str("SET_VEHICLE_FULLBEAM")] = VEHICLE::SET_VEHICLE_FULLBEAM;
	N_VEHICLE[crypt_str("STEER_UNLOCK_BIAS")] = VEHICLE::STEER_UNLOCK_BIAS;
	N_VEHICLE[crypt_str("_JITTER_VEHICLE")] = VEHICLE::_JITTER_VEHICLE;
	N_VEHICLE[crypt_str("SET_VEHICLE_FORWARD_SPEED")] = VEHICLE::SET_VEHICLE_FORWARD_SPEED;
	N_VEHICLE[crypt_str("_SET_VEHICLE_HALT")] = VEHICLE::_SET_VEHICLE_HALT;
	N_VEHICLE[crypt_str("SET_VEHICLE_TYRE_BURST")] = VEHICLE::SET_VEHICLE_TYRE_BURST;
	N_VEHICLE[crypt_str("SET_VEHICLE_DOORS_SHUT")] = VEHICLE::SET_VEHICLE_DOORS_SHUT;
	N_VEHICLE[crypt_str("SET_VEHICLE_TYRES_CAN_BURST")] = VEHICLE::SET_VEHICLE_TYRES_CAN_BURST;
	N_VEHICLE[crypt_str("GET_VEHICLE_TYRES_CAN_BURST")] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST;
	N_VEHICLE[crypt_str("SET_VEHICLE_WHEELS_CAN_BREAK")] = VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK;
	N_VEHICLE[crypt_str("SET_VEHICLE_DOOR_OPEN")] = VEHICLE::SET_VEHICLE_DOOR_OPEN;
	N_VEHICLE[crypt_str("REMOVE_VEHICLE_WINDOW")] = VEHICLE::REMOVE_VEHICLE_WINDOW;
	N_VEHICLE[crypt_str("SET_VEHICLE_LIGHTS")] = VEHICLE::SET_VEHICLE_LIGHTS;
	N_VEHICLE[crypt_str("SET_VEHICLE_ALARM")] = VEHICLE::SET_VEHICLE_ALARM;
	N_VEHICLE[crypt_str("SET_VEHICLE_TYRE_FIXED")] = VEHICLE::SET_VEHICLE_TYRE_FIXED;
	N_VEHICLE[crypt_str("SET_VEHICLE_NUMBER_PLATE_TEXT")] = VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT;
	N_VEHICLE[crypt_str("GET_VEHICLE_NUMBER_PLATE_TEXT")] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT;
	N_VEHICLE[crypt_str("GET_NUMBER_OF_VEHICLE_NUMBER_PLATES")] = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES;
	N_VEHICLE[crypt_str("SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX")] = VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX;
	N_VEHICLE[crypt_str("GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX")] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX;
	N_VEHICLE[crypt_str("SET_RANDOM_TRAINS")] = VEHICLE::SET_RANDOM_TRAINS;
	N_VEHICLE[crypt_str("GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME")] = VEHICLE::GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME;
	N_VEHICLE[crypt_str("GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME")] = VEHICLE::GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME;
	N_VEHICLE[crypt_str("DELETE_MISSION_TRAIN")] = VEHICLE::DELETE_MISSION_TRAIN;
	N_VEHICLE[crypt_str("SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED")] = VEHICLE::SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED;
	N_VEHICLE[crypt_str("SET_MISSION_TRAIN_COORDS")] = VEHICLE::SET_MISSION_TRAIN_COORDS;
	N_VEHICLE[crypt_str("IS_THIS_MODEL_A_BOAT")] = VEHICLE::IS_THIS_MODEL_A_BOAT;
	N_VEHICLE[crypt_str("SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED")] = VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED;
	N_VEHICLE[crypt_str("SET_VEHICLE_ENGINE_ON")] = VEHICLE::SET_VEHICLE_ENGINE_ON;
	N_VEHICLE[crypt_str("SET_VEHICLE_UNDRIVEABLE")] = VEHICLE::SET_VEHICLE_UNDRIVEABLE;
	N_VEHICLE[crypt_str("SET_VEHICLE_PROVIDES_COVER")] = VEHICLE::SET_VEHICLE_PROVIDES_COVER;
	N_VEHICLE[crypt_str("_GET_PED_USING_VEHICLE_DOOR")] = VEHICLE::_GET_PED_USING_VEHICLE_DOOR;
	N_VEHICLE[crypt_str("SET_VEHICLE_DOOR_SHUT")] = VEHICLE::SET_VEHICLE_DOOR_SHUT;
	N_VEHICLE[crypt_str("IS_BIG_VEHICLE")] = VEHICLE::IS_BIG_VEHICLE;
	N_VEHICLE[crypt_str("GET_NUMBER_OF_VEHICLE_COLOURS")] = VEHICLE::GET_NUMBER_OF_VEHICLE_COLOURS;
	N_VEHICLE[crypt_str("SET_VEHICLE_COLOUR_COMBINATION")] = VEHICLE::SET_VEHICLE_COLOUR_COMBINATION;
	N_VEHICLE[crypt_str("GET_RANDOM_VEHICLE_MODEL_IN_MEMORY")] = VEHICLE::GET_RANDOM_VEHICLE_MODEL_IN_MEMORY;
	N_VEHICLE[crypt_str("GET_VEHICLE_DOOR_LOCK_STATUS")] = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS;
	N_VEHICLE[crypt_str("SET_VEHICLE_FIXED")] = VEHICLE::SET_VEHICLE_FIXED;
	N_VEHICLE[crypt_str("SET_VEHICLE_DEFORMATION_FIXED")] = VEHICLE::SET_VEHICLE_DEFORMATION_FIXED;
	N_VEHICLE[crypt_str("START_VEHICLE_HORN")] = VEHICLE::START_VEHICLE_HORN;
	N_VEHICLE[crypt_str("_SET_VEHICLE_SILENT")] = VEHICLE::_SET_VEHICLE_SILENT;
	N_VEHICLE[crypt_str("GET_DISPLAY_NAME_FROM_VEHICLE_MODEL")] = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL;
	N_VEHICLE[crypt_str("GET_VEHICLE_DEFORMATION_AT_POS")] = VEHICLE::GET_VEHICLE_DEFORMATION_AT_POS;
	N_VEHICLE[crypt_str("_GET_VEHICLE_MAX_SPEED")] = VEHICLE::_GET_VEHICLE_MAX_SPEED;
	N_VEHICLE[crypt_str("SET_VEHICLE_MOD")] = VEHICLE::SET_VEHICLE_MOD;
	N_VEHICLE[crypt_str("_SET_VEHICLE_ENGINE_POWER_MULTIPLIER")] = VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER;
	N_VEHICLE[crypt_str("_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER")] = VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER;
	N_VEHICLE[crypt_str("SET_VEHICLE_SHOOT_AT_TARGET")] = VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET;
	N_VEHICLE[crypt_str("_GET_VEHICLE_OWNER")] = VEHICLE::_GET_VEHICLE_OWNER;
	N_VEHICLE[crypt_str("IS_VEHICLE_VISIBLE")] = VEHICLE::IS_VEHICLE_VISIBLE;
	N_VEHICLE[crypt_str("SET_VEHICLE_GRAVITY")] = VEHICLE::SET_VEHICLE_GRAVITY;
	N_VEHICLE[crypt_str("DISABLE_VEHICLE_WEAPON")] = VEHICLE::DISABLE_VEHICLE_WEAPON;
	N_VEHICLE[crypt_str("_SET_VEHICLE_JET_ENGINE_ON")] = VEHICLE::_SET_VEHICLE_JET_ENGINE_ON;
	N_VEHICLE[crypt_str("_SET_VEHICLE_NEON_LIGHTS_COLOUR")] = VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR;
	N_VEHICLE[crypt_str("_SET_VEHICLE_NEON_LIGHT_ENABLED")] = VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED;
	N_VEHICLE[crypt_str("GET_VEHICLE_BODY_HEALTH")] = VEHICLE::GET_VEHICLE_BODY_HEALTH;
	N_VEHICLE[crypt_str("SET_VEHICLE_BODY_HEALTH")] = VEHICLE::SET_VEHICLE_BODY_HEALTH;
	N_VEHICLE[crypt_str("_SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER")] = VEHICLE::_SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER;
	N_VEHICLE[crypt_str("_SET_VEHICLE_ROCKET_BOOST_ACTIVE")] = VEHICLE::_SET_VEHICLE_ROCKET_BOOST_ACTIVE;
	N_VEHICLE[crypt_str("_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME")] = VEHICLE::_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME;
	N_VEHICLE[crypt_str("_HAS_VEHICLE_JUMPING_ABILITY")] = VEHICLE::_HAS_VEHICLE_JUMPING_ABILITY;
	N_VEHICLE[crypt_str("_IS_THIS_MODEL_AN_AMPHIBIOUS_CAR")] = VEHICLE::_IS_THIS_MODEL_AN_AMPHIBIOUS_CAR;
	N_VEHICLE[crypt_str("_IS_MODEL_A_PED")] = VEHICLE::_IS_MODEL_A_PED;
	N_VEHICLE[crypt_str("_GET_PED_AMMO_TYPE_FROM_WEAPON_2")] = VEHICLE::_GET_PED_AMMO_TYPE_FROM_WEAPON_2;
	N_VEHICLE[crypt_str("_GET_ALL_VEHICLES")] = VEHICLE::_GET_ALL_VEHICLES;
	N_VEHICLE[crypt_str("_SET_AIRCRAFT_BOMB_COUNT")] = VEHICLE::_SET_AIRCRAFT_BOMB_COUNT;

	auto N_OBJECT = lua.create_table();
	N_OBJECT[crypt_str("CREATE_OBJECT")] = OBJECT::CREATE_OBJECT;
	N_OBJECT[crypt_str("CREATE_OBJECT_NO_OFFSET")] = OBJECT::CREATE_OBJECT_NO_OFFSET;
	N_OBJECT[crypt_str("DELETE_OBJECT")] = OBJECT::DELETE_OBJECT;
	N_OBJECT[crypt_str("PLACE_OBJECT_ON_GROUND_PROPERLY")] = OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY;
	N_OBJECT[crypt_str("SLIDE_OBJECT")] = OBJECT::SLIDE_OBJECT;
	N_OBJECT[crypt_str("IS_OBJECT_VISIBLE")] = OBJECT::IS_OBJECT_VISIBLE;
	N_OBJECT[crypt_str("CREATE_PICKUP")] = OBJECT::CREATE_PICKUP;
	N_OBJECT[crypt_str("CREATE_PICKUP_ROTATE")] = OBJECT::CREATE_PICKUP_ROTATE;
	N_OBJECT[crypt_str("CREATE_AMBIENT_PICKUP")] = OBJECT::CREATE_AMBIENT_PICKUP;
	N_OBJECT[crypt_str("ATTACH_PORTABLE_PICKUP_TO_PED")] = OBJECT::ATTACH_PORTABLE_PICKUP_TO_PED;
	N_OBJECT[crypt_str("GET_SAFE_PICKUP_COORDS")] = OBJECT::GET_SAFE_PICKUP_COORDS;
	N_OBJECT[crypt_str("GET_PICKUP_COORDS")] = OBJECT::GET_PICKUP_COORDS;
	N_OBJECT[crypt_str("REMOVE_ALL_PICKUPS_OF_TYPE")] = OBJECT::REMOVE_ALL_PICKUPS_OF_TYPE;
	N_OBJECT[crypt_str("HAS_PICKUP_BEEN_COLLECTED")] = OBJECT::HAS_PICKUP_BEEN_COLLECTED;
	N_OBJECT[crypt_str("CREATE_MONEY_PICKUPS")] = OBJECT::CREATE_MONEY_PICKUPS;
	N_OBJECT[crypt_str("SET_TEAM_PICKUP_OBJECT")] = OBJECT::SET_TEAM_PICKUP_OBJECT;
	N_OBJECT[crypt_str("_GET_WEAPON_HASH_FROM_PICKUP")] = OBJECT::_GET_WEAPON_HASH_FROM_PICKUP;
	N_OBJECT[crypt_str("_SET_OBJECT_TEXTURE_VARIANT")] = OBJECT::_SET_OBJECT_TEXTURE_VARIANT;

	auto N_CAM = lua.create_table();
	N_CAM[crypt_str("CREATE_OBJECT")] = CAM::RENDER_SCRIPT_CAMS;
	N_CAM[crypt_str("_RENDER_FIRST_PERSON_CAM")] = CAM::_RENDER_FIRST_PERSON_CAM;
	N_CAM[crypt_str("CREATE_CAM")] = CAM::CREATE_CAM;
	N_CAM[crypt_str("CREATE_CAM_WITH_PARAMS")] = CAM::CREATE_CAM_WITH_PARAMS;
	N_CAM[crypt_str("CREATE_CAMERA")] = CAM::CREATE_CAMERA;
	N_CAM[crypt_str("CREATE_CAMERA_WITH_PARAMS")] = CAM::CREATE_CAMERA_WITH_PARAMS;
	N_CAM[crypt_str("DESTROY_CAM")] = CAM::DESTROY_CAM;
	N_CAM[crypt_str("DESTROY_ALL_CAMS")] = CAM::DESTROY_ALL_CAMS;
	N_CAM[crypt_str("DOES_CAM_EXIST")] = CAM::DOES_CAM_EXIST;
	N_CAM[crypt_str("SET_CAM_ACTIVE")] = CAM::SET_CAM_ACTIVE;
	N_CAM[crypt_str("IS_CAM_ACTIVE")] = CAM::IS_CAM_ACTIVE;
	N_CAM[crypt_str("IS_CAM_RENDERING")] = CAM::IS_CAM_RENDERING;
	N_CAM[crypt_str("GET_RENDERING_CAM")] = CAM::GET_RENDERING_CAM;
	N_CAM[crypt_str("GET_CAM_COORD")] = CAM::GET_CAM_COORD;
	N_CAM[crypt_str("GET_CAM_ROT")] = CAM::GET_CAM_ROT;
	N_CAM[crypt_str("GET_CAM_FOV")] = CAM::GET_CAM_FOV;
	N_CAM[crypt_str("GET_CAM_NEAR_CLIP")] = CAM::GET_CAM_NEAR_CLIP;
	N_CAM[crypt_str("GET_CAM_FAR_CLIP")] = CAM::GET_CAM_FAR_CLIP;
	N_CAM[crypt_str("GET_CAM_FAR_DOF")] = CAM::GET_CAM_FAR_DOF;
	N_CAM[crypt_str("SET_CAM_PARAMS")] = CAM::SET_CAM_PARAMS;
	N_CAM[crypt_str("SET_CAM_COORD")] = CAM::SET_CAM_COORD;
	N_CAM[crypt_str("SET_CAM_ROT")] = CAM::SET_CAM_ROT;
	N_CAM[crypt_str("SET_CAM_FOV")] = CAM::SET_CAM_FOV;
	N_CAM[crypt_str("SET_CAM_NEAR_CLIP")] = CAM::SET_CAM_NEAR_CLIP;
	N_CAM[crypt_str("SET_CAM_FAR_CLIP")] = CAM::SET_CAM_FAR_CLIP;
	N_CAM[crypt_str("GET_GAMEPLAY_CAM_COORD")] = CAM::GET_GAMEPLAY_CAM_COORD;
	N_CAM[crypt_str("GET_GAMEPLAY_CAM_ROT")] = CAM::GET_GAMEPLAY_CAM_ROT;
	N_CAM[crypt_str("GET_GAMEPLAY_CAM_FOV")] = CAM::GET_GAMEPLAY_CAM_FOV;
	N_CAM[crypt_str("CUSTOM_MENU_COORDINATES")] = CAM::CUSTOM_MENU_COORDINATES;
	N_CAM[crypt_str("IS_AIM_CAM_ACTIVE")] = CAM::IS_AIM_CAM_ACTIVE;
	N_CAM[crypt_str("_GET_GAMEPLAY_CAM_ZOOM")] = CAM::_GET_GAMEPLAY_CAM_ZOOM;

	auto N_WEAPON = lua.create_table();
	N_WEAPON[crypt_str("ENABLE_LASER_SIGHT_RENDERING")] = WEAPON::ENABLE_LASER_SIGHT_RENDERING;
	N_WEAPON[crypt_str("GET_WEAPON_COMPONENT_TYPE_MODEL")] = WEAPON::GET_WEAPON_COMPONENT_TYPE_MODEL;
	N_WEAPON[crypt_str("GET_WEAPONTYPE_MODEL")] = WEAPON::GET_WEAPONTYPE_MODEL;
	N_WEAPON[crypt_str("SET_CURRENT_PED_WEAPON")] = WEAPON::SET_CURRENT_PED_WEAPON;
	N_WEAPON[crypt_str("GET_CURRENT_PED_WEAPON_ENTITY_INDEX")] = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX;
	N_WEAPON[crypt_str("GET_BEST_PED_WEAPON")] = WEAPON::GET_BEST_PED_WEAPON;
	N_WEAPON[crypt_str("IS_PED_ARMED")] = WEAPON::IS_PED_ARMED;
	N_WEAPON[crypt_str("IS_WEAPON_VALID")] = WEAPON::IS_WEAPON_VALID;
	N_WEAPON[crypt_str("HAS_PED_GOT_WEAPON")] = WEAPON::HAS_PED_GOT_WEAPON;
	N_WEAPON[crypt_str("GET_AMMO_IN_PED_WEAPON")] = WEAPON::GET_AMMO_IN_PED_WEAPON;
	N_WEAPON[crypt_str("ADD_AMMO_TO_PED")] = WEAPON::ADD_AMMO_TO_PED;
	N_WEAPON[crypt_str("SET_PED_AMMO")] = WEAPON::SET_PED_AMMO;
	N_WEAPON[crypt_str("SET_PED_INFINITE_AMMO")] = WEAPON::SET_PED_INFINITE_AMMO;
	N_WEAPON[crypt_str("GIVE_WEAPON_TO_PED")] = WEAPON::GIVE_WEAPON_TO_PED;
	N_WEAPON[crypt_str("GIVE_DELAYED_WEAPON_TO_PED")] = WEAPON::GIVE_DELAYED_WEAPON_TO_PED;
	N_WEAPON[crypt_str("REMOVE_WEAPON_FROM_PED")] = WEAPON::REMOVE_WEAPON_FROM_PED;
	N_WEAPON[crypt_str("HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE")] = WEAPON::HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE;
	N_WEAPON[crypt_str("SET_PED_CURRENT_WEAPON_VISIBLE")] = WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE;
	N_WEAPON[crypt_str("HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON")] = WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON;
	N_WEAPON[crypt_str("SET_PED_DROPS_WEAPON")] = WEAPON::SET_PED_DROPS_WEAPON;
	N_WEAPON[crypt_str("SET_PED_DROPS_INVENTORY_WEAPON")] = WEAPON::SET_PED_DROPS_INVENTORY_WEAPON;
	N_WEAPON[crypt_str("GET_MAX_AMMO_IN_CLIP")] = WEAPON::GET_MAX_AMMO_IN_CLIP;
	N_WEAPON[crypt_str("GET_AMMO_IN_CLIP")] = WEAPON::GET_AMMO_IN_CLIP;
	N_WEAPON[crypt_str("SET_AMMO_IN_CLIP")] = WEAPON::SET_AMMO_IN_CLIP;
	N_WEAPON[crypt_str("GET_MAX_AMMO")] = WEAPON::GET_MAX_AMMO;
	N_WEAPON[crypt_str("SET_PED_AMMO_BY_TYPE")] = WEAPON::SET_PED_AMMO_BY_TYPE;
	N_WEAPON[crypt_str("SET_PED_AMMO_TO_DROP")] = WEAPON::SET_PED_AMMO_TO_DROP;
	N_WEAPON[crypt_str("GET_PED_AMMO_TYPE_FROM_WEAPON")] = WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON;
	N_WEAPON[crypt_str("GET_SELECTED_PED_WEAPON")] = WEAPON::GET_SELECTED_PED_WEAPON;
	N_WEAPON[crypt_str("SET_FLASH_LIGHT_FADE_DISTANCE")] = WEAPON::SET_FLASH_LIGHT_FADE_DISTANCE;
	N_WEAPON[crypt_str("IS_PED_WEAPON_COMPONENT_ACTIVE")] = WEAPON::IS_PED_WEAPON_COMPONENT_ACTIVE;
	N_WEAPON[crypt_str("_PED_SKIP_NEXT_RELOADING")] = WEAPON::_PED_SKIP_NEXT_RELOADING;


	auto N_GAMEPLAY = lua.create_table();
	N_GAMEPLAY[crypt_str("GET_ALLOCATED_STACK_SIZE")] = GAMEPLAY::GET_ALLOCATED_STACK_SIZE;
	N_GAMEPLAY[crypt_str("_GET_FREE_STACK_SLOTS_COUNT")] = GAMEPLAY::_GET_FREE_STACK_SLOTS_COUNT;
	N_GAMEPLAY[crypt_str("SET_RANDOM_SEED")] = GAMEPLAY::SET_RANDOM_SEED;
	N_GAMEPLAY[crypt_str("SET_TIME_SCALE")] = GAMEPLAY::SET_TIME_SCALE;
	N_GAMEPLAY[crypt_str("SET_MISSION_FLAG")] = GAMEPLAY::SET_MISSION_FLAG;
	N_GAMEPLAY[crypt_str("GET_MISSION_FLAG")] = GAMEPLAY::GET_MISSION_FLAG;
	N_GAMEPLAY[crypt_str("SET_RANDOM_EVENT_FLAG")] = GAMEPLAY::SET_RANDOM_EVENT_FLAG;
	N_GAMEPLAY[crypt_str("GET_RANDOM_EVENT_FLAG")] = GAMEPLAY::GET_RANDOM_EVENT_FLAG;
	N_GAMEPLAY[crypt_str("_GET_GLOBAL_CHAR_BUFFER")] = GAMEPLAY::_GET_GLOBAL_CHAR_BUFFER;
	N_GAMEPLAY[crypt_str("GET_PREV_WEATHER_TYPE_HASH_NAME")] = GAMEPLAY::GET_PREV_WEATHER_TYPE_HASH_NAME;
	N_GAMEPLAY[crypt_str("GET_NEXT_WEATHER_TYPE_HASH_NAME")] = GAMEPLAY::GET_NEXT_WEATHER_TYPE_HASH_NAME;
	N_GAMEPLAY[crypt_str("IS_PREV_WEATHER_TYPE")] = GAMEPLAY::IS_PREV_WEATHER_TYPE;
	N_GAMEPLAY[crypt_str("IS_NEXT_WEATHER_TYPE")] = GAMEPLAY::IS_NEXT_WEATHER_TYPE;
	N_GAMEPLAY[crypt_str("SET_WEATHER_TYPE_PERSIST")] = GAMEPLAY::SET_WEATHER_TYPE_PERSIST;
	N_GAMEPLAY[crypt_str("SET_WEATHER_TYPE_NOW_PERSIST")] = GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST;
	N_GAMEPLAY[crypt_str("SET_WEATHER_TYPE_NOW")] = GAMEPLAY::SET_WEATHER_TYPE_NOW;
	N_GAMEPLAY[crypt_str("_SET_WEATHER_TYPE_OVER_TIME")] = GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME;
	N_GAMEPLAY[crypt_str("SET_RANDOM_WEATHER_TYPE")] = GAMEPLAY::SET_RANDOM_WEATHER_TYPE;
	N_GAMEPLAY[crypt_str("CLEAR_WEATHER_TYPE_PERSIST")] = GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST;
	N_GAMEPLAY[crypt_str("_GET_WEATHER_TYPE_TRANSITION")] = GAMEPLAY::_GET_WEATHER_TYPE_TRANSITION;
	N_GAMEPLAY[crypt_str("_SET_WEATHER_TYPE_TRANSITION")] = GAMEPLAY::_SET_WEATHER_TYPE_TRANSITION;
	N_GAMEPLAY[crypt_str("SET_OVERRIDE_WEATHER")] = GAMEPLAY::SET_OVERRIDE_WEATHER;
	N_GAMEPLAY[crypt_str("CLEAR_OVERRIDE_WEATHER")] = GAMEPLAY::CLEAR_OVERRIDE_WEATHER;
	N_GAMEPLAY[crypt_str("SET_WIND")] = GAMEPLAY::SET_WIND;
	N_GAMEPLAY[crypt_str("SET_WIND_SPEED")] = GAMEPLAY::SET_WIND_SPEED;
	N_GAMEPLAY[crypt_str("GET_WIND_SPEED")] = GAMEPLAY::GET_WIND_SPEED;
	N_GAMEPLAY[crypt_str("SET_WIND_DIRECTION")] = GAMEPLAY::SET_WIND_DIRECTION;
	N_GAMEPLAY[crypt_str("GET_WIND_DIRECTION")] = GAMEPLAY::GET_WIND_DIRECTION;
	N_GAMEPLAY[crypt_str("_SET_RAIN_FX_INTENSITY")] = GAMEPLAY::_SET_RAIN_FX_INTENSITY;
	N_GAMEPLAY[crypt_str("GET_RAIN_LEVEL")] = GAMEPLAY::GET_RAIN_LEVEL;
	N_GAMEPLAY[crypt_str("GET_SNOW_LEVEL")] = GAMEPLAY::GET_SNOW_LEVEL;
	N_GAMEPLAY[crypt_str("_CREATE_LIGHTNING_THUNDER")] = GAMEPLAY::_CREATE_LIGHTNING_THUNDER;
	N_GAMEPLAY[crypt_str("_SET_CLOUD_HAT_TRANSITION")] = GAMEPLAY::_SET_CLOUD_HAT_TRANSITION;
	N_GAMEPLAY[crypt_str("_CLEAR_CLOUD_HAT")] = GAMEPLAY::_CLEAR_CLOUD_HAT;
	N_GAMEPLAY[crypt_str("_SET_CLOUD_HAT_OPACITY")] = GAMEPLAY::_SET_CLOUD_HAT_OPACITY;
	N_GAMEPLAY[crypt_str("GET_GAME_TIMER")] = GAMEPLAY::GET_GAME_TIMER;
	N_GAMEPLAY[crypt_str("GET_FRAME_TIME")] = GAMEPLAY::GET_FRAME_TIME;
	N_GAMEPLAY[crypt_str("_GET_BENCHMARK_TIME")] = GAMEPLAY::_GET_BENCHMARK_TIME;
	N_GAMEPLAY[crypt_str("GET_FRAME_COUNT")] = GAMEPLAY::GET_FRAME_COUNT;
	N_GAMEPLAY[crypt_str("GET_RANDOM_FLOAT_IN_RANGE")] = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE;
	N_GAMEPLAY[crypt_str("GET_GROUND_Z_FOR_3D_COORD")] = GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD;
	N_GAMEPLAY[crypt_str("_GET_GROUND_Z_COORD_WITH_OFFSETS")] = GAMEPLAY::_GET_GROUND_Z_COORD_WITH_OFFSETS;
	N_GAMEPLAY[crypt_str("ASIN")] = GAMEPLAY::ASIN;
	N_GAMEPLAY[crypt_str("ACOS")] = GAMEPLAY::ACOS;
	N_GAMEPLAY[crypt_str("TAN")] = GAMEPLAY::TAN;
	N_GAMEPLAY[crypt_str("ATAN")] = GAMEPLAY::ATAN;
	N_GAMEPLAY[crypt_str("ATAN2")] = GAMEPLAY::ATAN2;
	N_GAMEPLAY[crypt_str("GET_DISTANCE_BETWEEN_COORDS")] = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS;
	N_GAMEPLAY[crypt_str("GET_ANGLE_BETWEEN_2D_VECTORS")] = GAMEPLAY::GET_ANGLE_BETWEEN_2D_VECTORS;
	N_GAMEPLAY[crypt_str("GET_HEADING_FROM_VECTOR_2D")] = GAMEPLAY::GET_HEADING_FROM_VECTOR_2D;
	N_GAMEPLAY[crypt_str("SET_BIT")] = GAMEPLAY::SET_BIT;
	N_GAMEPLAY[crypt_str("CLEAR_BIT")] = GAMEPLAY::CLEAR_BIT;
	N_GAMEPLAY[crypt_str("GET_HASH_KEY")] = GAMEPLAY::GET_HASH_KEY;
	N_GAMEPLAY[crypt_str("IS_AREA_OCCUPIED")] = GAMEPLAY::IS_AREA_OCCUPIED;
	N_GAMEPLAY[crypt_str("IS_POSITION_OCCUPIED")] = GAMEPLAY::IS_POSITION_OCCUPIED;
	N_GAMEPLAY[crypt_str("IS_POINT_OBSCURED_BY_A_MISSION_ENTITY")] = GAMEPLAY::IS_POINT_OBSCURED_BY_A_MISSION_ENTITY;
	N_GAMEPLAY[crypt_str("CLEAR_AREA")] = GAMEPLAY::CLEAR_AREA;
	N_GAMEPLAY[crypt_str("_CLEAR_AREA_OF_EVERYTHING")] = GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING;
	N_GAMEPLAY[crypt_str("CLEAR_AREA_OF_VEHICLES")] = GAMEPLAY::CLEAR_AREA_OF_VEHICLES;
	N_GAMEPLAY[crypt_str("CLEAR_ANGLED_AREA_OF_VEHICLES")] = GAMEPLAY::CLEAR_ANGLED_AREA_OF_VEHICLES;
	N_GAMEPLAY[crypt_str("CLEAR_AREA_OF_OBJECTS")] = GAMEPLAY::CLEAR_AREA_OF_OBJECTS;
	N_GAMEPLAY[crypt_str("CLEAR_AREA_OF_PEDS")] = GAMEPLAY::CLEAR_AREA_OF_PEDS;
	N_GAMEPLAY[crypt_str("CLEAR_AREA_OF_COPS")] = GAMEPLAY::CLEAR_AREA_OF_COPS;
	N_GAMEPLAY[crypt_str("CLEAR_AREA_OF_PROJECTILES")] = GAMEPLAY::CLEAR_AREA_OF_PROJECTILES;
	N_GAMEPLAY[crypt_str("SET_SAVE_MENU_ACTIVE")] = GAMEPLAY::SET_SAVE_MENU_ACTIVE;
	N_GAMEPLAY[crypt_str("SET_CREDITS_ACTIVE")] = GAMEPLAY::SET_CREDITS_ACTIVE;
	N_GAMEPLAY[crypt_str("TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME")] = GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME;
	N_GAMEPLAY[crypt_str("NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME")] = GAMEPLAY::NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME;
	N_GAMEPLAY[crypt_str("ADD_HOSPITAL_RESTART")] = GAMEPLAY::ADD_HOSPITAL_RESTART;
	N_GAMEPLAY[crypt_str("DISABLE_HOSPITAL_RESTART")] = GAMEPLAY::DISABLE_HOSPITAL_RESTART;
	N_GAMEPLAY[crypt_str("ADD_POLICE_RESTART")] = GAMEPLAY::ADD_POLICE_RESTART;
	N_GAMEPLAY[crypt_str("DISABLE_POLICE_RESTART")] = GAMEPLAY::DISABLE_POLICE_RESTART;
	N_GAMEPLAY[crypt_str("_SET_CUSTOM_RESPAWN_POSITION")] = GAMEPLAY::_SET_CUSTOM_RESPAWN_POSITION;
	N_GAMEPLAY[crypt_str("_SET_NEXT_RESPAWN_TO_CUSTOM")] = GAMEPLAY::_SET_NEXT_RESPAWN_TO_CUSTOM;
	N_GAMEPLAY[crypt_str("_DISABLE_AUTOMATIC_RESPAWN")] = GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN;
	N_GAMEPLAY[crypt_str("IGNORE_NEXT_RESTART")] = GAMEPLAY::IGNORE_NEXT_RESTART;
	N_GAMEPLAY[crypt_str("SET_FADE_OUT_AFTER_DEATH")] = GAMEPLAY::SET_FADE_OUT_AFTER_DEATH;
	N_GAMEPLAY[crypt_str("SET_FADE_OUT_AFTER_ARREST")] = GAMEPLAY::SET_FADE_OUT_AFTER_ARREST;
	N_GAMEPLAY[crypt_str("IS_MEMORY_CARD_IN_USE")] = GAMEPLAY::IS_MEMORY_CARD_IN_USE;
	N_GAMEPLAY[crypt_str("SHOOT_SINGLE_BULLET_BETWEEN_COORDS")] = GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS;
	N_GAMEPLAY[crypt_str("_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_PRESET_PARAMS")] = GAMEPLAY::_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_PRESET_PARAMS;
	N_GAMEPLAY[crypt_str("_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_WITH_EXTRA_PARAMS")] = GAMEPLAY::_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_WITH_EXTRA_PARAMS;
	N_GAMEPLAY[crypt_str("GET_MODEL_DIMENSIONS")] = GAMEPLAY::GET_MODEL_DIMENSIONS;
	N_GAMEPLAY[crypt_str("SET_FAKE_WANTED_LEVEL")] = GAMEPLAY::SET_FAKE_WANTED_LEVEL;
	N_GAMEPLAY[crypt_str("GET_FAKE_WANTED_LEVEL")] = GAMEPLAY::GET_FAKE_WANTED_LEVEL;
	N_GAMEPLAY[crypt_str("IS_BIT_SET")] = GAMEPLAY::IS_BIT_SET;
	N_GAMEPLAY[crypt_str("IS_SNIPER_BULLET_IN_AREA")] = GAMEPLAY::IS_SNIPER_BULLET_IN_AREA;
	N_GAMEPLAY[crypt_str("IS_PROJECTILE_IN_AREA")] = GAMEPLAY::IS_PROJECTILE_IN_AREA;
	N_GAMEPLAY[crypt_str("IS_PROJECTILE_TYPE_IN_AREA")] = GAMEPLAY::IS_PROJECTILE_TYPE_IN_AREA;
	N_GAMEPLAY[crypt_str("IS_PROJECTILE_TYPE_IN_ANGLED_AREA")] = GAMEPLAY::IS_PROJECTILE_TYPE_IN_ANGLED_AREA;
	N_GAMEPLAY[crypt_str("IS_BULLET_IN_ANGLED_AREA")] = GAMEPLAY::IS_BULLET_IN_ANGLED_AREA;
	N_GAMEPLAY[crypt_str("IS_BULLET_IN_AREA")] = GAMEPLAY::IS_BULLET_IN_AREA;
	N_GAMEPLAY[crypt_str("IS_BULLET_IN_BOX")] = GAMEPLAY::IS_BULLET_IN_BOX;
	N_GAMEPLAY[crypt_str("HAS_BULLET_IMPACTED_IN_BOX")] = GAMEPLAY::HAS_BULLET_IMPACTED_IN_BOX;
	N_GAMEPLAY[crypt_str("HAS_BULLET_IMPACTED_IN_AREA")] = GAMEPLAY::HAS_BULLET_IMPACTED_IN_AREA;
	N_GAMEPLAY[crypt_str("IS_ORBIS_VERSION")] = GAMEPLAY::IS_ORBIS_VERSION;
	N_GAMEPLAY[crypt_str("CANCEL_STUNT_JUMP")] = GAMEPLAY::CANCEL_STUNT_JUMP;
	N_GAMEPLAY[crypt_str("SET_GAME_PAUSED")] = GAMEPLAY::SET_GAME_PAUSED;
	N_GAMEPLAY[crypt_str("_USE_FREEMODE_MAP_BEHAVIOR")] = GAMEPLAY::_USE_FREEMODE_MAP_BEHAVIOR;
	N_GAMEPLAY[crypt_str("IS_FRONTEND_FADING")] = GAMEPLAY::IS_FRONTEND_FADING;
	N_GAMEPLAY[crypt_str("GET_INDEX_OF_CURRENT_LEVEL")] = GAMEPLAY::GET_INDEX_OF_CURRENT_LEVEL;
	N_GAMEPLAY[crypt_str("SET_GRAVITY_LEVEL")] = GAMEPLAY::SET_GRAVITY_LEVEL;
	N_GAMEPLAY[crypt_str("_DISPLAY_ONSCREEN_KEYBOARD_2")] = GAMEPLAY::_DISPLAY_ONSCREEN_KEYBOARD_2;
	N_GAMEPLAY[crypt_str("DISPLAY_ONSCREEN_KEYBOARD")] = GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD;
	N_GAMEPLAY[crypt_str("GET_ONSCREEN_KEYBOARD_RESULT")] = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT;
	N_GAMEPLAY[crypt_str("SET_EXPLOSIVE_AMMO_THIS_FRAME")] = GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME;
	N_GAMEPLAY[crypt_str("SET_FIRE_AMMO_THIS_FRAME")] = GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME;
	N_GAMEPLAY[crypt_str("SET_EXPLOSIVE_MELEE_THIS_FRAME")] = GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME;
	N_GAMEPLAY[crypt_str("SET_SUPER_JUMP_THIS_FRAME")] = GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME;
	N_GAMEPLAY[crypt_str("_REMOVE_STEALTH_KILL")] = GAMEPLAY::_REMOVE_STEALTH_KILL;



	lua[crypt_str("N_PLAYER")] = N_PLAYER;
	lua[crypt_str("N_ENTITY")] = N_ENTITY;
	lua[crypt_str("N_PED")] = N_PED;
	lua[crypt_str("N_VEHICLE")] = N_VEHICLE;
	lua[crypt_str("N_OBJECT")] = N_OBJECT;
	lua[crypt_str("N_CAM")] = N_CAM;
	lua[crypt_str("N_WEAPON")] = N_WEAPON;
	lua[crypt_str("N_GAMEPLAY")] = N_GAMEPLAY;


	lua[crypt_str("menu")] = menu;
	lua[crypt_str("render")] = render;
	lua[crypt_str("cl")] = client;
	lua[crypt_str("screen")] = engine;


	refresh_scripts();
}
