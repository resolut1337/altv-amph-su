
#pragma once
#include <Windows.h>
#include <vector>
#include <dxgi.h>
#include <d3d11.h>
#include <emmintrin.h>
#include "../ragemp_cheat/src/ImGui/imgui.h"
#include "../ragemp_cheat/src/ImGui/imgui_impl_dx11.h"
#include "../ragemp_cheat/src/ImGui/imgui_impl_win32.h"

#include "../ragemp_cheat/src/ImGui/imgui_internal.h"
#include "../ragemp_cheat/src/ImGui/imgui_freetype.h"
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")


#include <D3dx9math.h>
#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <emmintrin.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <thread>
#include <comdef.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "D:/sourca/amthsave7/AMTH/cpr.lib")
#pragma comment(lib, "D:/sourca/amthsave7/AMTH/zlib.lib")
#pragma comment(lib, "D:/sourca/amthsave7/AMTH/libcurl.lib")
#include "Urlmon.h"
#pragma comment(lib, "Urlmon.lib")
#define STB_IMAGE_IMPLEMENTATION
#include "../ragemp_cheat/src/Vector.hpp"
#include "../ragemp_cheat/src/xorstr.hpp"

#pragma once
#include <cmath>

#include <xmmintrin.h>
#include <iostream>
#pragma warning(disable: 4996)


#include "src/Main/vectors.hpp"
#include "src/Main/vars.h"

HWND hWnd;

#pragma warning(disable : 4996)
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#ifdef _WIN64
#define PTRMAXVAL ((DWORD64)0x000F000000000000)
#else
#define PTRMAXVAL ((DWORD64)0xFFF00000)
#endif
#include "src/encryptfynk.hpp"

namespace Helper
{
	bool ValidPTR(DWORD64 ptr)
	{
		if (ptr >= 0x10000 && ptr < PTRMAXVAL)
			return true;

		return false;
	}

	DWORD64 FindPattern(const char* szModule, const char* szSignature)
	{
		MODULEINFO modInfo;
		GetModuleInformation(SAFE_CALL(GetCurrentProcess)(), SAFE_CALL(GetModuleHandleA)(szModule), &modInfo, sizeof(MODULEINFO));
		DWORD64 startAddress = (DWORD64)SAFE_CALL(GetModuleHandleA)(szModule);
		DWORD64 endAddress = (startAddress + (DWORD64)modInfo.SizeOfImage);
		const char* pat = szSignature;
		DWORD64 firstMatch = 0;
		for (DWORD64 pCur = startAddress; pCur < endAddress; pCur++)
		{
			if (!*pat) return firstMatch;
			if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch) firstMatch = pCur;
				if (!pat[2]) return firstMatch;
				if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) pat += 3;
				else pat += 2;
			}
			else {
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;
	}
	SIZE_T GetPointerAddress(SIZE_T Address, UINT Offset)
	{
		if (Address == 0)
			return 0;

		if (sizeof(SIZE_T) == 8)
			return Address + (INT)((*(INT*)(Address + Offset) + Offset) + sizeof(INT));

		return (SIZE_T) * (DWORD*)(Address + Offset);
	}

}


namespace global_nat_platf {
	int version_platform = 0; //1 altv || 2 ragemp
}

namespace image
{
	ID3D11ShaderResourceView* roll = nullptr;

	ID3D11ShaderResourceView* rusifikacia = nullptr;
	ID3D11ShaderResourceView* rusifikacia_ru = nullptr;
	ID3D11ShaderResourceView* discord_logo = nullptr;
	ID3D11ShaderResourceView* telegram_logo = nullptr;
	ID3D11ShaderResourceView* vk_logo = nullptr;
	ID3D11ShaderResourceView* site_logo = nullptr;
}
namespace font
{
	ImFont* poppins_medium = nullptr;
	ImFont* poppins_medium_low = nullptr;
	ImFont* tab_icon = nullptr;
	ImFont* chicons = nullptr;
	ImFont* tahoma_bold = nullptr;
	ImFont* tahoma_bold2 = nullptr;
}
//ImFont* m_pFont2 = font::poppins_medium;

#include <ShlObj_core.h>
//#include "src/stb_image.h"
#include <Windows.h>
#include <winternl.h>
#include <utility>
#include <optional>
#include <string>
using namespace std;
template<typename T>
class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

public:
	static T& Instance()
	{
		static T inst{};
		return inst;
	}
};
class Vehicle_r : public Singleton<Vehicle_r>
{
public:
	void Tick();
};
#include <functional>
float get_distance_between_coords_3d(Vector3 from, Vector3 to)
{
	return (float)sqrt(pow(double(from.x - to.x), 2.0) + pow(double(from.y - to.y), 2.0) + pow(double(from.z - to.z), 2.0));
}

#include <Psapi.h>
#include <sstream>
#include <optional>
#include <array>

namespace sy
{
	class handle {
	public:
		handle() = default;
		explicit handle(uintptr_t address) : m_Address(address) {}

		template <typename T>
		T as() const {
			return reinterpret_cast<T>(m_Address);
		}

		handle add(uintptr_t offset) const {
			if (m_Address != 0)
			{
				return handle(m_Address + offset);
			}

			return *this;
		}

		handle sub(uintptr_t offset) const {
			if (m_Address != 0)
			{
				return handle(m_Address - offset);
			}

			return *this;
		}

		handle rip() const {
			if (m_Address != 0)
			{
				auto offset = *as<int32_t*>();
				return add(offset + sizeof(int32_t));
			}

			return *this;
		}

		uintptr_t get_address()
		{
			return m_Address;
		}

	private:
		uintptr_t m_Address = 0;
	};


	class _module {
	public:
		_module(const char* module) : m_Module(module)
		{
			m_ModuleHandle = GetModuleHandleA(m_Module);
		}

		handle get_export(const char* func)
		{
			return handle((std::uintptr_t)GetProcAddress(m_ModuleHandle, func));
		}

		HMODULE get_handle()
		{
			return m_ModuleHandle;
		}

	private:
		const char* m_Module;
		HMODULE m_ModuleHandle;
	};

	class pattern {
	public:
		explicit pattern(_module module);
		~pattern() noexcept;

		pattern& scanNow(std::string sigName, std::string  IDASig);
		pattern& scanAllNow(std::string sigName, std::string  IDASig);

		handle getResult();
		std::vector<handle> getAllResults();
	private:
		_module m_Module;
		size_t m_ModuleSize;
		HMODULE m_ModuleHandle;
		handle m_Result;
		std::vector<handle> m_AllResults;
	};

	class offset {
	public:
		explicit offset(uint64_t offset, _module module = "GTA5.exe");
		~offset() noexcept;

		handle& getResult();
		uintptr_t& getAddress();
	private:
		uint64_t m_Offset;
		_module m_Module;
		handle m_Result;
		HMODULE m_ModuleHandle;
		uintptr_t m_Address;
	};
}
 //#include <utility>
namespace sy
{
	std::vector<std::optional<uint8_t>> parseIDASignature(const char* sig) {
		std::vector<std::optional<uint8_t>> bytes;
		std::stringstream ss(sig);

		while (!ss.eof()) {
			std::string byte_str;
			ss >> byte_str;

			if (byte_str == "?" || byte_str == "??") {
				bytes.push_back(std::nullopt);
				continue;
			}

			if (byte_str.length() != 2) {
				throw std::runtime_error("Invalid byte in IDA signature: " + byte_str);
			}

			char* end;
			long value = strtol(byte_str.c_str(), &end, 16);

			if (*end != '\0') {
				throw std::runtime_error("Invalid byte in IDA signature: " + byte_str);
			}

			bytes.push_back(static_cast<uint8_t>(value));
		}

		return bytes;
	}


	pattern::pattern(_module module) :
		m_Module(module), m_Result(0)
	{
		m_ModuleHandle = m_Module.get_handle();

		if (m_ModuleHandle == nullptr) {
			throw std::runtime_error("Could not find module!");
		}

		MODULEINFO mi = { 0 };

		if (!GetModuleInformation(GetCurrentProcess(), m_ModuleHandle, &mi, sizeof(mi))) {
			throw std::runtime_error("Could not get module information!");
		}
		m_ModuleSize = mi.SizeOfImage;
	}

	pattern::~pattern() {}

	pattern& pattern::scanAllNow(std::string sigName, std::string  IDASig)
	{
		auto signature = parseIDASignature(IDASig.c_str());

		std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(m_ModuleHandle);

		std::size_t sig_size = signature.size();
		std::uintptr_t end_address = base_address + m_ModuleSize - sig_size;

		std::array<int, 256> bad_char;
		for (int i = 0; i < 256; ++i) {
			bad_char[i] = sig_size;
		}
		for (int i = 0; i < sig_size - 1; ++i) {
			if (signature[i].has_value()) {
				bad_char[signature[i].value()] = sig_size - i - 1;
			}
			else {
				for (int j = 0; j < 256; ++j) {
					bad_char[j] = min(bad_char[j], sig_size - i - 1);
				}
			}
		}

		std::uintptr_t i = base_address + sig_size - 1;
		while (i < end_address) {
			int j = sig_size - 1;
			while (j >= 0) {
				if (signature[j].has_value() && signature[j].value() != *reinterpret_cast<uint8_t*>(i - sig_size + j + 1))
					break;
				--j;
			}
			if (j < 0) {
				m_Result = handle(i - sig_size + 1);
				//..g_Logger->logNow("Found pattern: " + sigName, logClass::GENERAL);
				m_AllResults.push_back(m_Result);
			}
			i += max(bad_char[*reinterpret_cast<uint8_t*>(i)], static_cast<int>(sig_size - j - 1));
		}

		//if (!m_AllResults.empty())
			//..g_Logger->logNow("Failed to find pattern: " + sigName, logClass::ALERT);

		return *this;
	}


	pattern& pattern::scanNow(std::string sigName, std::string  IDASig)
	{
		auto signature = parseIDASignature(IDASig.c_str());

		std::uintptr_t base_address = reinterpret_cast<std::uintptr_t>(m_ModuleHandle);

		std::size_t sig_size = signature.size();
		std::uintptr_t end_address = base_address + m_ModuleSize - sig_size;

		std::array<int, 256> bad_char;
		for (int i = 0; i < 256; ++i) {
			bad_char[i] = sig_size;
		}
		for (int i = 0; i < sig_size - 1; ++i) {
			if (signature[i].has_value()) {
				bad_char[signature[i].value()] = sig_size - i - 1;
			}
			else {
				for (int j = 0; j < 256; ++j) {
					bad_char[j] = min(bad_char[j], sig_size - i - 1);
				}
			}
		}

		std::uintptr_t i = base_address + sig_size - 1;
		while (i < end_address) {
			int j = sig_size - 1;
			while (j >= 0) {
				if (signature[j].has_value() && signature[j].value() != *reinterpret_cast<uint8_t*>(i - sig_size + j + 1))
					break;
				--j;
			}
			if (j < 0) {
				m_Result = handle(i - sig_size + 1);
				//g_Logger->logNow("Found pattern: " + sigName, logClass::GENERAL);
				return *this;
			}
			i += max(bad_char[*reinterpret_cast<uint8_t*>(i)], static_cast<int>(sig_size - j - 1));
		}

	//	g_Logger->logNow("Failed to find pattern: " + sigName, logClass::ALERT);
		m_Result = handle(0);

		return *this;
	}

	handle pattern::getResult()
	{
		return m_Result;
	}

	std::vector<handle> pattern::getAllResults()
	{
		return m_AllResults;
	}


	offset::offset(uint64_t offset, _module module) :
		m_Offset(offset), m_Module(module)
	{
		m_ModuleHandle = m_Module.get_handle();
	}

	offset::~offset() {}

	handle& offset::getResult()
	{
		auto addr = (uintptr_t)m_ModuleHandle + m_Offset;
		m_Result = handle(addr);

		return m_Result;
	}

	uintptr_t& offset::getAddress()
	{
		auto addr = (uintptr_t)m_ModuleHandle + m_Offset;
		return addr;
	}
}
namespace Memory {
	using pointer_handler_t = int32_t(*)(intptr_t pointer);
	pointer_handler_t pointer_to_handle = nullptr;
}


#include "src/NativeInvoker.hpp" //

enum class thread_state_t : std::uint32_t
{
	idle,
	running,
	killed,
	unk_3,
	unk_4,
};


class thread_context_t
{
public:
	std::uint32_t m_thread_id;
	std::uint32_t m_script_hash; // + 4 (program id)
	thread_state_t m_state; // + 8
	std::uint32_t m_instruction_pointer; // 0x0C
	std::uint32_t m_frame_pointer;       // 0x10
	std::uint32_t m_stack_pointer;       // 0x14
	float m_timer_a;                     // 0x18
	float m_timer_b;                     // 0x1C
	float m_timer_c;                     // 0x20
	char m_padding1[0x2C];               // 0x24
	std::uint32_t m_stack_size;          // 0x50
	char m_padding2[0x54];               // 0x54
};

class game_thread
{
public:
	virtual ~game_thread() = default;
	//virtual thread_state_t reset(std::uint32_t script_hash, void* args, std::uint32_t arg_count) = 0;
	//virtual thread_state_t run() = 0;
	//virtual thread_state_t tick() = 0;
	virtual void kill() = 0;

	inline static game_thread*& get() {
		//return *(game_thread**)(*reinterpret_cast<uintptr_t*>(__readgsqword(0x58)) + 0x830);
		return *(game_thread**)(*reinterpret_cast<uintptr_t*>(__readgsqword(0x58)) + 0x830);//new
	}
public:
	thread_context_t m_context; // 0x08
	void* m_stack;              // 0xB0
	char m_padding[0x10];       // 0xB8
	const char* m_exit_message; // 0xC8
	char m_name[0x40];          // 0xD0
	void* m_handler;   // 0x110
	char m_padding2[0x28];      // 0x118
	std::uint8_t m_flag1;       // 0x140
	std::uint8_t m_flag2;       // 0x141
	char m_padding3[0x16];      // 0x142
};

using script_thread_tick_t = uintptr_t(*)(game_thread* thread, int ops_to_execute);
//get_bone_position_t ptr_gta_get_bone_position = nullptr;
script_thread_tick_t gta_script_thread_tick = nullptr;
script_thread_tick_t original_native_thread = nullptr;

namespace fiberq
{
	using script_func_t = void(*)();

	class fiber_task
	{
	public:
		explicit fiber_task(HMODULE hmod, script_func_t func) :
			m_hmodule(hmod),
			m_function(func)
		{ }

		~fiber_task() noexcept
		{
			if (m_script_fiber)
			{
				DeleteFiber(m_script_fiber);
			}
		}

		HMODULE get_hmodule()
		{
			return m_hmodule;
		}

		script_func_t get_function()
		{
			return m_function;
		}

		void on_tick()
		{
			if (GetTickCount64() < m_wake_at)
				return;

			if (!m_main_fiber)
			{
				m_main_fiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);
			}

			if (m_script_fiber)
			{
				current_fiber_script = this;
				SwitchToFiber(m_script_fiber);
				current_fiber_script = nullptr;
			}
			else
			{
				m_script_fiber = CreateFiber(0, [](PVOID param)
					{
						auto this_script = static_cast<fiber_task*>(param);
						while (true)
						{
							this_script->m_function();
						}
					}, this);
			}
		}
		void wait(std::uint32_t time)
		{
			m_wake_at = GetTickCount64() + time;
			SwitchToFiber(m_main_fiber);
		}

		inline static fiber_task* get_current_script()
		{
			return current_fiber_script;
		}
	private:
		HMODULE m_hmodule{};
		script_func_t m_function{};

		std::uint32_t m_wake_at{};
		void* m_script_fiber{};
		void* m_main_fiber{};

		inline static fiber_task* current_fiber_script{};
	};
}
std::unique_ptr<fiberq::fiber_task> game_fiber;
void call_thread(game_thread* this_ptr, int ops_to_execute) {
	if ((
		/*Ragemp*/(this_ptr->m_context.m_script_hash == 0x26FB4AB9 || this_ptr->m_context.m_script_hash == 1104607124 || this_ptr->m_context.m_script_hash == 3381724246) ||
		/*AltV*/(this_ptr->m_context.m_script_hash == 2003913879 || this_ptr->m_context.m_script_hash == 3522812357/* || this_ptr->m_context.m_script_hash == 20 || this_ptr->m_context.m_script_hash == 21*/)
		)) {
		auto& thread = game_thread::get();
		auto orig_thread = thread;
		thread = this_ptr;
		game_fiber->on_tick();
		thread = orig_thread;
	}
}
uintptr_t hooked_native_thread(game_thread* this_ptr, int ops_to_execute) {
	call_thread(this_ptr, ops_to_execute);
	return original_native_thread(this_ptr, ops_to_execute);
}

DWORD64 FrameCount = 0x0;
static uint64_t GetFrameCount() {
	uint64_t        cur = *(uint64_t*)(FrameCount);
	return cur;
}

class CViewPort {
public:
	char _0x0000[0x24C];
	float fViewMatrix[0x10];
	//D3DXMATRIX fViewMatrix;
};//Size=0x028C
#pragma pack(pop)
static CViewPort* m_viewPort;

#include "../ragemp_cheat/src/Main/pattern_scanning.h"


using namespace rage::native;

struct Player_ss {
	c_ped* m_ped;
	bool is_admin;
	bool is_visible;
	bool is_vehicle;

	//std::uint32_t model_hash; //0x0018 
	//std::uint32_t handle; //0x0110 
	//struct _ { // 0x0168
	//	c_ped* m_ped;
	//} *m_ped_link;
	//std::string name; //0x0188 
	//std::uint8_t alpha; //0x01D6 
public:
	std::uintptr_t** get_js_object() {
		return reinterpret_cast<std::uintptr_t**>(std::uintptr_t(this) + 0x70);
	}
};

namespace Pool
{
	struct Players
	{
		hk_Ped* ped;
		ImVec4 position;
		ImVec2 Head;
		ImVec2 Left_Foot;
		ImVec2 Right_Foot;
		ImVec2 Pelvis;
		ImVec2 Neck;
    	ImVec2 Clavicle_Left;
		ImVec2 Clavicle_Right;
		ImVec2 Uperarm_left;
		ImVec2 Uperarm_right;
		ImVec2 Elbow_l;
		ImVec2 Elbow_r;
		ImVec2 R_FormArm;
		ImVec2 L_FormArm;
		ImVec2 SKEL_R_Hand;
		ImVec2 SKEL_L_Hand;
		ImVec2 SKEL_L_Thigh;
		ImVec2 SKEL_L_Calf;
		ImVec2 SKEL_R_Thigh;
		ImVec2 SKEL_R_Calf;

		ImVec4 PedModelInfo_GetMin;
		ImVec4 PedModelInfo_GetMax;
		//Vector3 mins = Peds->PedModelInfo()->GetMin();
						//Vector3 maxs = Peds->PedModelInfo()->GetMax();

		float health;
		float maxhealth;
		float armor;
		float distance;
		std::string weapon_and_dist = "None";
		std::string weapon_for_arrow = "None";

		bool visible = false;
		bool is_ped_a_player = false;
		bool is_ped_is_any_vehicle = false;
		bool is_admin = false;
		int index;

		//float head_pos_x;
		//float head_pos_y;

		//float Left_Foot_pos_x;
		//float Left_Foot_pos_y;

		//float Right_Foot_pos_x;
		//float Right_Foot_pos_y;

		//float max_health;
		//float health;
		//float armor;
		//uint64_t Weapon_hash;

		//int index_count ;
		//float height_ground ;
	};
	Players new_list[512];
}
namespace Aimbot
{
	DWORD64 TICKS = GetTickCount64();
	int AimbotTick = 16;
	
	float screen_distance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}

	float get_distance(Vector3 to, Vector3 from) {
		return (sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
	}
	int aimneck;
}

#include "../ragemp_cheat/src/imgui_settings.h"
#include "src/Main/otherImgui.hpp"
#include "src/auth.h"
class CXenForo
{
public:
	struct Endpoints_t
	{
		CAuth Auth;
	} Endpoint;
};

CXenForo g_XenForo;
namespace Global
{
	static struct
	{
		std::string server = (std::string)xorstr_("amph.su");
		std::string forum_dir = (std::string)xorstr_("/");
		std::string secret_key = (std::string)xorstr_("afsdgasd5437f5i7hsirf345rweg");
	} server;

	static struct
	{
		std::string version = (std::string)xorstr_("1");
		std::string client_key = (std::string)xorstr_("sgfdhsdfgerwtwertwretwe");
		std::string cheat = (std::string)xorstr_("amphetamine");
		std::string username;
		std::string password;
		std::string stop;
	} client;
};
std::string new_object_name;

std::string new_config_name;
std::vector <std::string> filesobjectlist;
std::vector <std::string> files;
int selected_config;
int selected_objectlist;
class C_ConfigManager
{
public:
	class C_ConfigItem
	{
	public:
		std::string name;
		void* pointer;
		std::string type;

		C_ConfigItem(std::string name, void* pointer, std::string type)  //-V818
		{
			this->name = name; //-V820
			this->pointer = pointer;
			this->type = type; //-V820
		}
	};

	void add_item(void* pointer, const char* name, const std::string& type);
	void setup_item(int*, int, const std::string&);
	void setup_item(bool*, bool, const std::string&);
	void setup_item(float*, float, const std::string&);
	//void setup_item(key_bind*, key_bind, const std::string&);
	//void setup_item(Color*, Color, const std::string&);
	void setup_item(std::vector< int >*, int, const std::string&);
	void setup_item(std::vector< std::string >*, const std::string&);
	void setup_item(std::string*, const std::string&, const std::string&);

	std::vector <C_ConfigItem*> items;

	C_ConfigManager()
	{

	};
	void hitsoundfiles();
	void remove(const std::string config);
	std::vector<std::string> files;
	std::vector <std::string> fileshitsound;
	void config_files();
};
extern C_ConfigManager* cfg_manager;
C_ConfigManager* cfg_manager = new C_ConfigManager();
#include "src/Config.h"




void add_config()
{
	auto empty = true;
	for (auto current : new_config_name)
	{
		if (current != ' ')
		{
			empty = false;
			break;
		}
	}
	if (empty)
		new_config_name = ("config");
	amphetamine::amphetamine_settings->upload_cfg(new_config_name + "&create_cfg_new");
	std::string remnot = "Created Config: " + new_config_name;
	cfg_manager->config_files();
	selected_config = cfg_manager->files.size() - 1;
	files = cfg_manager->files;
}
void load_config()
{
	if (cfg_manager->files.empty())
		return;
	amphetamine::amphetamine_settings->load_cloud_cfg(cfg_manager->files.at(selected_config));
	std::string remnot = "Loaded Config: " + cfg_manager->files.at(selected_config);

	cfg_manager->config_files();
}
void save_config()
{
	if (cfg_manager->files.empty())
		return;
	amphetamine::amphetamine_settings->upload_cfg(cfg_manager->files.at(selected_config));
	std::string remnot = "Saved Config: " + cfg_manager->files.at(selected_config);
	cfg_manager->config_files();
}

void remove_config()
{
	if (cfg_manager->files.empty())
		return;
	cfg_manager->remove(cfg_manager->files.at(selected_config));
	cfg_manager->config_files();
	files = cfg_manager->files;
	if (selected_config >= files.size())
		selected_config = files.size() - 1;
}


__forceinline BOOL EnablePriv(LPCSTR lpszPriv)
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}
typedef VOID(_stdcall* RtlSetProcessIsCritical) (IN BOOLEAN NewValue, OUT PBOOLEAN OldValue, IN BOOLEAN IsWinlogon);
__forceinline BOOL MakeCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA(xorstr_("ntdll.dll"));
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, (xorstr_("RtlSetProcessIsCritical")));
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}
__forceinline void clown()
{
	MakeCritical();
	raise(11);
}

DWORD weaponsLlist[] = {
	0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, //Throwables
	0x34A67B97, 0xFBAB5776, 0x060EC506, //Miscellaneous
	0xB1CA77B1, 0xA284510B, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, //Heavy Weapons
	0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, //Sniper Rifles
	0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, //Light Machine Guns
	0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, //Assault Rifles
	0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, //Submachine Guns
	0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, //Pistols
	0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, //Mele
	0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D
};
static int weapon_current = 0;
std::vector <std::string> weapon_list=
{ "Dagger", "Bat", "Knife", "Machete", "Pistol", "Pistol MK2", "Combat Pistol", "AP Pistol", "Stungun", "Pistol 50", "SNS PISTOL", "SNS Pistol MK2", "Heavy Pistol", "Vintage Pisol", "Flare Gun", "Marksman Pistol", "Revolver", "Revolver MK2", "Double Action", "Micro Smg", "Smg", "Smg MK2", "Assault Smg", "Combat PDW", "Machine Pistol", "Mini Smg", "Pump Shotgun", "Pump Shotgun MK2", "Sawnoff Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "DB Shotgun", "Auto Shotgun", "Assault Rifle", "Assault Rifle MK2", "Carbine Rifle", "Carbine Rifle MK2", "Advanced Rifle", "Special Carbine", "Special Carbine MK2", "Bullpup Rifle", "Bullpup Rifle MK2", "Compact Rifle", "Machine Gun", "Combat MG", "Combat MG MK2", "GUSENBERG", "Sniper Rifle", "Heavy Sniper", "Heavy Sniper MK2", "Marksman Rifle", "Marksman Rifle MK2", "RPG", "Grenade Launcher", "MiniGun", "FireWork", "RailGun", "Homing Launcher", "Compact Launcher", "Grenade", "BZGAS", "Smoke Grenade", "Flare", "Molotov", "Sticky BOMB", "Prox Mine", "SnowBall", "Pipe Bomb", "Ball", "Petrol Can", "Fire Extinguisher", "Parachute" };

static int v_subtabs = 0;
static int v_misc_subtabs = 0;
static int selectedVeh_index = 1;
static int selected_index = 1;
bool welcome_succes = true;

float test111 = 100.f;
float test222 = 100.f;
float test333 = 100.f;
float test444 = 100.f;


BOOL IsValid(PVOID64 ptr)
{
	return (BOOL)(ptr != NULL);
}

D3DCOLOR FLOAT4TOD3DCOLOR(ImColor Col)
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
#include "src/Main/render.h"

//#include "../../../stb_image.h"
//#include "../../../stb_sprintf.h"
//#include "src/CRT.h"
#include "../ragemp_cheat/src/Main/Visuals.hpp"

#include "src/lua_api_and_other.h"
#include "src/safe_ptr.hpp"
struct _Mutex {
	std::unique_ptr<sf::contention_free_shared_mutex<>> NativeHelper;
}; std::unique_ptr<_Mutex> Mutex;



#include "src/Main/Misc.hpp"
#include "src/Menu.h"





bool inited = false;
#include <ShlObj_core.h>

#include "src/inject_sound.hpp"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


#include <wininet.h>
#pragma comment(lib, "WinINet.lib")
std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
std::string DownloadString(std::string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


namespace Globals
{
	static struct
	{
		std::string server = xorstr_("amph.su");
		std::string forum_dir = xorstr_("/");
		std::string secret_key = xorstr_("1234567890");
	} server_side;

	static struct
	{
		std::string version = xorstr_("1.3");
		std::string client_key = xorstr_("0987654321");
		std::string cheat = xorstr_("amphetamine");
	} client_side;
};

#include "../ragemp_cheat/minhook/minhook.h"
#include <src/md5.h>





D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
namespace uLoader
{
	string CheckVersion() {
		std::string tempory_cipher_key;
		std::string tempory_iv_key;
		std::vector<std::string> vector_tempory_key;
		auto unprotect_request = DownloadString((string)xorstr_("https://") + Global::server.server + (string)xorstr_("/client/session.php"));
		for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 64)
			tempory_cipher_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
		for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 32)
			tempory_iv_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
		std::string protect_request = aes::encrypt(unprotect_request, tempory_cipher_key, tempory_iv_key);
		std::string protect_key = aes::encrypt(Globals::client_side.client_key, tempory_cipher_key, tempory_iv_key);
		std::string protect_version = aes::encrypt(Globals::client_side.version, tempory_cipher_key, tempory_iv_key);
		unprotect_request = aes::encrypt(unprotect_request.c_str(), xorstr_("r09y7LrY1C4yqONI641qMQe7GA5mQvdf"), xorstr_("H1ggF9foFGLerr8q")); // static keys
		//auto accepted_request = DownloadString((string)xorstr_("https://amph.su/client/versions_check.php?a=") + unprotect_request + (string)xorstr_("&b=") + protect_request + (string)xorstr_("&c=") + protect_key + (string)xorstr_("&d=") + protect_version);
		auto accepted_request = DownloadString((string)xorstr_("https://amph.su/client/versions_check.php?a=") + unprotect_request + (string)xorstr_("&b=") + protect_request + (string)xorstr_("&c=") + protect_key + (string)xorstr_("&d=") + protect_version + (string)xorstr_("&prod=") + "altv");

		return aes::decrypt(aes::decrypt(accepted_request, tempory_cipher_key, tempory_iv_key), tempory_cipher_key, tempory_iv_key);
	}
	bool check_version()
	{
		std::string server_version = CheckVersion();
		if (server_version == Globals::client_side.version) {
			return true;
		}
		else {
			return false;
		}
	}

	__forceinline void strip_string(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), [](int c) {return !(c > 32 && c < 127); }), str.end());
	}
	__forceinline std::string get_hwidqwe()
	{

		std::string result = xorstr_("");

		HANDLE hDevice = CreateFileA(xorstr_("\\\\.\\PhysicalDrive0"), (DWORD)nullptr, FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)nullptr, OPEN_EXISTING, (DWORD)nullptr, (HANDLE)nullptr);

		if (hDevice == INVALID_HANDLE_VALUE) return result;

		STORAGE_PROPERTY_QUERY storagePropertyQuery;
		ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
		storagePropertyQuery.PropertyId = StorageDeviceProperty;
		storagePropertyQuery.QueryType = PropertyStandardQuery;

		STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
		DWORD dwBytesReturned = 0;

		DeviceIoControl
		(
			hDevice,
			IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery,
			sizeof(STORAGE_PROPERTY_QUERY),
			&storageDescriptorHeader,
			sizeof(STORAGE_DESCRIPTOR_HEADER),
			&dwBytesReturned,
			nullptr
		);

		const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
		BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
		ZeroMemory(pOutBuffer, dwOutBufferSize);

		DeviceIoControl
		(
			hDevice,
			IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery,
			sizeof(STORAGE_PROPERTY_QUERY),
			pOutBuffer,
			dwOutBufferSize,
			&dwBytesReturned,
			nullptr
		);

		STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;

		if (pDeviceDescriptor->SerialNumberOffset)
		{
			result += std::string((char*)(pOutBuffer + pDeviceDescriptor->SerialNumberOffset));
		}

		if (pDeviceDescriptor->ProductRevisionOffset)
		{
			result += std::string((char*)(pOutBuffer + pDeviceDescriptor->ProductRevisionOffset));
		}

		if (pDeviceDescriptor->ProductIdOffset)
		{
			result += std::string((char*)(pOutBuffer + pDeviceDescriptor->ProductIdOffset));
		}

		uint32_t regs[4];
		__cpuid((int*)regs, 0);

		std::string vendor;

		vendor += std::string((char*)&regs[1], 4);
		vendor += std::string((char*)&regs[3], 4);
		vendor += std::string((char*)&regs[2], 4);

		result += std::string(vendor);

		strip_string(result);

		delete[] pOutBuffer;
		CloseHandle(hDevice);

		result = md5::create_from_string(result);

		return result;
	}

	string Login() {
		std::string tempory_cipher_key;
		std::string tempory_iv_key;
		std::vector<std::string> vector_tempory_key;
		auto unprotect_request = DownloadString((string)xorstr_("https://") + Global::server.server + (string)xorstr_("/client/session.php"));
		for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 64)
			tempory_cipher_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
		for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 32)
			tempory_iv_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
		std::string protect_request = aes::encrypt(unprotect_request, tempory_cipher_key, tempory_iv_key);
		std::string protect_username = aes::encrypt(Global::client.username, tempory_cipher_key, tempory_iv_key);
		std::string protect_password = aes::encrypt(Global::client.password, tempory_cipher_key, tempory_iv_key);
		std::string protect_hwid = aes::encrypt(get_hwidqwe(), tempory_cipher_key, tempory_iv_key);
		unprotect_request = aes::encrypt(unprotect_request, (string)xorstr_("r09y7LrY1C4yqONI641qMQe7GA5mQvdf"), (string)xorstr_("H1ggF9foFGLerr8q")); // static keys
		char request[9999];
		(sprintf)(request, xorstr_("https://amph.su/client/loaderxen.php?a=%s&b=%s&username=%s&password=%s&hwid=%s&cheat_prod_message=%s"), unprotect_request.c_str(), protect_request.c_str(), protect_username.c_str(), protect_password.c_str(), protect_hwid.c_str(), "cheat");
		std::string accepted_request = DownloadString(request);
		return aes::decrypt(aes::decrypt(accepted_request, tempory_cipher_key, tempory_iv_key), tempory_cipher_key, tempory_iv_key);
	}
	bool check_one_log = false;
	int checkUser() {
		std::string output;
		if (!check_one_log) {
			output = Login();
			check_one_log = true;
		}
		if (output == xorstr_("username:fail")) {
			return 4;
		}
		else if (output == xorstr_("PASSWORD:fail")) {
			return 5;
		}
		else if (output == xorstr_("hwid:fail")) {
			return 2;
		}
		else if (output == xorstr_("ban:fail")) {
			return 6;
		}
		else if (output == xorstr_("success role")) {
			return 1;
		}
		else if (output == xorstr_("role:fail")) {
			return 3;
		}
	}

}


namespace mem {
	template<typename T>
	T read(DWORD64 addr) {
		return *((T*)addr);
	}

	template<typename T>
	void write(DWORD64 addr, T value) {
		*((T*)addr) = value;
	}
	template<typename T>
	DWORD64 protect(DWORD64 addr, DWORD protection) {
		DWORD oldProtection;
		VirtualProtect((LPVOID)addr, sizeof(T), protection, &oldProtection);

		return oldProtection;
	}

	DWORD64 hookFunction(DWORD64 hookAt, DWORD64 newFunc, unsigned int size) {
		DWORD64 newOffset = newFunc - hookAt - 5;   // -5 since the jump is relative
													// to the next instruction
		auto oldProtection = mem::protect<DWORD[3]>(hookAt + 1, PAGE_EXECUTE_READWRITE);

		mem::write<BYTE>(hookAt, 0xE9);          // Opcode of the jmp instruction
		mem::write<DWORD>(hookAt + 1, newOffset);

		for (unsigned int i = 5; i < size; i++) // nop extra bytes to avoid
												// corrupting the overwritten opcode
			mem::write<BYTE>(hookAt + i, 0x90);

		mem::protect<DWORD[3]>(hookAt + 1, oldProtection);

		return hookAt + 5;
	}
}


#include <TlHelp32.h>
DWORD GetPIDbyName(LPTSTR szProcessName)
{
	HANDLE hSnapShot;
	PROCESSENTRY32 pe = { sizeof(pe) };
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return 0;
	if (!Process32First(hSnapShot, &pe))
		return 0;
	do
		if (!lstrcmpi(pe.szExeFile, szProcessName))
		{
			CloseHandle(hSnapShot);
			return pe.th32ProcessID;
		}
	while (Process32Next(hSnapShot, &pe));
	CloseHandle(hSnapShot);
	return 0;
}
struct handle_data
{
	unsigned long process_id;
	HWND window_handle;
};
BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}
HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.window_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.window_handle;
}

HWND windowHWND;
WNDPROC m_og_wndproc;

HMODULE GetCurrentModule()
{
	HMODULE hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GetCurrentModule,
		&hModule);

	return hModule;
}

typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* D3D11ResizeBuffersHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef void(__stdcall* D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
typedef void(__stdcall* D3D11DrawHook) (ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation);
typedef void(__stdcall* D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall* D3D11DrawIndexedInstancedHook) (ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall* D3D11CreateQueryHook) (ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);


D3D11PresentHook phookD3D11Present = NULL;
D3D11ResizeBuffersHook phookD3D11ResizeBuffers = NULL;
D3D11PSSetShaderResourcesHook phookD3D11PSSetShaderResources = NULL;
D3D11DrawHook phookD3D11Draw = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11DrawIndexedInstancedHook phookD3D11DrawIndexedInstanced = NULL;
D3D11CreateQueryHook phookD3D11CreateQuery = NULL;


ID3D11DeviceContext* pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;


//viewport
UINT vps = 1;
D3D11_VIEWPORT viewport;
float ScreenCenterX;
float ScreenCenterY;

ID3D11RenderTargetView* RenderTargetView = NULL;
HRESULT hr;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (global::show && (!global::Panic || !global::Panicnoclear))
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return 1l;
	}
	return CallWindowProcW(m_og_wndproc, hWnd, msg, wParam, lParam);
}
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

HANDLE mainFiber;
std::uint32_t wakeAt{};




#include"../ragemp_cheat/src/Main/Native_functions.h"


namespace Player_init {
	void Tick()
	{
		hk_Ped* LocalPlayer;
		hk_ReplayInterface* ReplayInterface;
		hk_PedInterface* PedInterface;
		__try
		{
			LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
			ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
			PedInterface = ReplayInterface->PedInterface();
		}
		__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}

		for (int i = 0; i < 512; i++)
		{
			Pool::new_list[i].ped = NULL;
			Pool::new_list[i].position.x = 0.0f;

			if (i < PedInterface->PedMaximum())
			{
				__try
				{
					hk_Ped* Peds_ = PedInterface->PedList()->Ped(i);
					if (Helper::ValidPTR((DWORD64)Peds_))
					{
						Pool::new_list[i].ped = Peds_;
						Pool::new_list[i].is_ped_a_player = ped::is_ped_a_player(Memory::pointer_to_handle((DWORD64)Peds_));
						Pool::new_list[i].position = ImVec4(Peds_->GetCoordinate().x, Peds_->GetCoordinate().y, Peds_->GetCoordinate().z, 0.f);

						Pool::new_list[i].Head = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x796E);
						Pool::new_list[i].Left_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x3779);
						Pool::new_list[i].Right_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xCC4D);
						if (amphetamine::amphetamine_settings->Skeleton) {
							Pool::new_list[i].Pelvis = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x2e28);
							Pool::new_list[i].Neck = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x9995);
							Pool::new_list[i].Clavicle_Left = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xFCD9);
							Pool::new_list[i].Clavicle_Right = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x29D2);
							Pool::new_list[i].Uperarm_left = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xB1C5);
							Pool::new_list[i].Uperarm_right = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x9D4D);
							Pool::new_list[i].Elbow_l = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x58B7);
							Pool::new_list[i].Elbow_r = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xBB0);
							Pool::new_list[i].R_FormArm = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x6E5C);
							Pool::new_list[i].L_FormArm = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xEEEB);
							Pool::new_list[i].SKEL_R_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xDEAD);
							Pool::new_list[i].SKEL_L_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x49D9);
							Pool::new_list[i].SKEL_L_Thigh = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xE39F);
							Pool::new_list[i].SKEL_L_Calf = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xF9BB);
							Pool::new_list[i].SKEL_R_Thigh = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0xCA72);
							Pool::new_list[i].SKEL_R_Calf = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds_), 0x9000);
						}
						if (amphetamine::amphetamine_settings->StaticESP) {
							Pool::new_list[i].PedModelInfo_GetMin = ImVec4(Peds_->PedModelInfo()->GetMin().x, Peds_->PedModelInfo()->GetMin().y, Peds_->PedModelInfo()->GetMin().z, 0.f);
							Pool::new_list[i].PedModelInfo_GetMax = ImVec4(Peds_->PedModelInfo()->GetMax().x, Peds_->PedModelInfo()->GetMax().y, Peds_->PedModelInfo()->GetMax().z, 0.f);
						}
						Pool::new_list[i].health = Peds_->GetHealth();
						Pool::new_list[i].maxhealth = Peds_->GetMaxHealth();
						Pool::new_list[i].armor = Peds_->GetArmor();
						Pool::new_list[i].visible = IsVisibleAimBot(Memory::LocalPlayer, (DWORD64)Peds_);
						Pool::new_list[i].is_ped_is_any_vehicle = PED::IS_PED_IN_ANY_VEHICLE(Memory::pointer_to_handle((DWORD64)Peds_), true);
						auto Distance = Aimbot::get_distance(LocalPlayer->GetCoordinate(), Peds_->GetCoordinate());
						std::string str_weapon_dist = "";
						if (amphetamine::amphetamine_settings->Weapon)
						{
							hk_WeaponManager* PedsWeaponManager = Peds_->WeaponManager();
							if (PedsWeaponManager) {
								hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
								if (PedsWeaponInfo) {
									uint64_t Hash = PedsWeaponInfo->GetHash();
									str_weapon_dist.append(get_weapon_name(Hash));
								}
							}
						}
						if (amphetamine::amphetamine_settings->oofindicators_players_weapon) {
							Pool::new_list[i].weapon_for_arrow = str_weapon_dist;
						}
						if (amphetamine::amphetamine_settings->DistanceESP) {
							std::string strr = " [" + std::to_string((int)round(Distance)) + "m]";
							if (!amphetamine::amphetamine_settings->Weapon)
								strr = "[" + std::to_string((int)round(Distance)) + "m]";
							str_weapon_dist.append(strr);
						}
						Pool::new_list[i].weapon_and_dist = str_weapon_dist;

	

						Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
					
						/*if (Aimbot::get_distance(localpos, Peds_->GetCoordinate()) > amphetamine::amphetamine_settings->Distance)
							continue;*/


						if (Aimbot::get_distance(localpos, Peds_->GetCoordinate()) > amphetamine::amphetamine_settings->max_distance_aim)
							continue;
						if (!amphetamine::amphetamine_settings->Draw_botsaim)
						{
							if (!ped::is_ped_a_player(Memory::pointer_to_handle((DWORD64)Peds_))) {
								continue;
							}
						}

						if (Peds_->GetHealth() <= 0) continue;

						if (amphetamine::amphetamine_settings->VisibleCheck) {
							if (!IsVisibleAimBot(Memory::LocalPlayer, (DWORD64)Peds_)) {
								continue;
							}
						}
						ImVec2 Ped_Location = Memory::WorldToScreen(Peds_->GetCoordinate());
						ImVec2 LocalPlayer_Location = Memory::WorldToScreen(LocalPlayer->GetCoordinate());
						if ((DWORD64)Peds_ == Memory::LocalPlayer) {
							continue;
						}


					
							


						AimBot(Peds_, LocalPlayer_Location, Ped_Location, Distance);

					}
				}
				__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
			}
		}
	}
}


void entytesandaimbot() {
	__try { Player_init::Tick(); }
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
}

bool freecam_active = false;
void call_native_functions() {
	if (global::Panic || global::Panicnoclear) {
	}
	else {
		rage::native_queue->on_native_tick(); // для вызова нативов не из script_thread


		FlyingCarLoop();

		//gravitygun(amphetamine::amphetamine_settings->gravitygun);
		//esp_rage();
		entytesandaimbot();

		vehicle_no_collisioon();
		no_collision_object();
		//entytesandaimbot();

		auto_pilot();
		//debugcamera();
		//freecam_era::on_tick();
		
		
		//freecam_era::on_tick();

		if (amphetamine::amphetamine_settings->clickwarp) {
			//clickwarp_player();
		}


		clickflipvehicle(amphetamine::amphetamine_settings->clickflipvehicle);

	
		vehicle_auto_fix(amphetamine::amphetamine_settings->Fix_On_damage);
		//vehicle_collision(Config::vehicle_collision);
		slideRun();
		thermalvision(amphetamine::amphetamine_settings->thermalvision);
		nightvision(amphetamine::amphetamine_settings->nightmode);
		//numberplatesfindvehicle();
		superbrakes(amphetamine::amphetamine_settings->superbrakes);
		autoflip(amphetamine::amphetamine_settings->autoflipvehicle);
		driftmode(amphetamine::amphetamine_settings->driftmode);
		vehinvisible(amphetamine::amphetamine_settings->vehicleinvisible);
		//rapidfire(amphetamine::amphetamine_settings->rapidfire);
		//collision(Config::collision);
		alwaysragdoll(amphetamine::amphetamine_settings->AlwaysRagdoll);
		if (amphetamine::amphetamine_settings->RainBowweapon) {
			RAINBOWguner();
		}
		nofall(amphetamine::amphetamine_settings->nofall);
		ghostmode(amphetamine::amphetamine_settings->ghostmode);
		explosive_ammo();
	//	superpunch();
		NoClipme();
		enginealwayson();
		if (loaded_script)
			for (auto current : c_lua::get().hooks.getHooks("on_ragemp_thread_tick"))
				current.func();
		
	}
	return;
}


#include "../ragemp_cheat/src/clear_unload.h"


string alt_v_socialclub;
void pre_draw() {
	if (amphetamine::amphetamine_settings->DrawFov) {
		auto draw_list = ImGui::GetBackgroundDrawList();

		Render_D2::Circle(ImVec2{ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 }, D2D1::ColorF::Black, amphetamine::amphetamine_settings->Aimbot_Fov * 10, 2.4f);
		Render_D2::Circle(ImVec2{ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 }, FLOAT4TOD3rwerLOR(amphetamine::amphetamine_settings->Fov_Color), amphetamine::amphetamine_settings->Aimbot_Fov * 10, 0.8f);


		/*if (_cfg.Visuals.DrawSilentFov == 2) {
			const unsigned int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			const unsigned int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			Renderer::RectanglePointFov(Vector2{ screenWidth / 2 - (_cfg.AimBot.Fov * 1.15f) / 2 / 2, screenHeight / 2 - (_cfg.AimBot.Fov * 1.15f) / 2 / 2 }, _cfg.AimBot.Fov * 1.15f, _cfg.AimBot.Fov * 1.15f, D2D1::ColorF::Black, 3.f);
			Renderer::RectanglePointFov(Vector2{ screenWidth / 2 - (_cfg.AimBot.Fov * 1.15f) / 2 / 2, screenHeight / 2 - (_cfg.AimBot.Fov * 1.15f) / 2 / 2 }, _cfg.AimBot.Fov * 1.15f, _cfg.AimBot.Fov * 1.15f, otherEsp::FLOAT4TOD3DCOLORqqwfdsf(_cfg.ColorVis.fovpsilenttoptop), 0.8f);
		}*/


		//draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), amphetamine::amphetamine_settings->Aimbot_Fov * 10, ImColor(0, 0, 0, 255), 35, 2.4f);
		//draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), amphetamine::amphetamine_settings->Aimbot_Fov * 10, ImColor(amphetamine::amphetamine_settings->Fov_Color), 35, 0.8f);
	}
	if (amphetamine::amphetamine_settings->Crosshair) {
		static float faken_rot = 0.0f;
		static int gamerjuice = 0;
		float a = (ImGui::GetIO().DisplaySize.y / 2) / 60.0f;
		float gamma = atan(a / a);
		if ((int)faken_rot > 89) { faken_rot = (float)0; }
		faken_rot++;

		if (gamerjuice > 30)
		{
			gamerjuice = 0;

		}
		else
			gamerjuice++;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		static int cases = 0;
		switch (cases)
		{
		case 0: { r -= 0.020f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.020f; b -= 0.020f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.020f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.020f; g -= 0.020f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		for (int i = 0; i < 4; i++)
		{
			std::vector <int> p;
			p.push_back(a * sin(GRD_TO_BOG(faken_rot + (i * 90))));									//p[0]		p0_A.x
			p.push_back(a * cos(GRD_TO_BOG(faken_rot + (i * 90))));									//p[1]		p0_A.y
			p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(faken_rot + (i * 90) + BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
			p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(faken_rot + (i * 90) + BOG_TO_GRD(gamma))));	//p[3]		p0_B.y
			//ImGui::GetBackgroundDrawList()->AddLine({ (ImGui::GetIO().DisplaySize.x / 2), (ImGui::GetIO().DisplaySize.y / 2) }, { (ImGui::GetIO().DisplaySize.x / 2) + p[0], (ImGui::GetIO().DisplaySize.y / 2) - p[1] }, ImColor(r, g, b, 255.f), 2.f);
			Render_D2::Line({ (ImGui::GetIO().DisplaySize.x / 2), (ImGui::GetIO().DisplaySize.y / 2) }, { (ImGui::GetIO().DisplaySize.x / 2) + p[0], (ImGui::GetIO().DisplaySize.y / 2) - p[1] }, FLOAT4TOD3rwerLOR(ImColor(r, g, b, 255.f)), 2.f, true);
		}
	}

	
}

#include "src/bytes.h"

#include "../ragemp_cheat/src/Main/game_overlay.h"



void on_native_thread() {

	static uint64_t    last = 0;
	uint64_t        cur = *(uint64_t*)(FrameCount);
	if (last != cur) {
		last = cur;	
		call_native_functions();
	}
	game_fiber->wait(0);
}

void call_fiber() {
	game_fiber = std::make_unique<fiberq::fiber_task>(nullptr, on_native_thread);
}



#include "../ragemp_cheat/src/Main/altv_executor.h"


#include "../ragemp_cheat/src/Main/ragemp_thread.h"


#include"../ragemp_cheat/src/Main/dxgi_overlay.h"



DWORD __stdcall InitializeHook()
{

	/*Memoryqe::module_t gta5_module = Memoryqe::module_t(nullptr);
	ptr_gta_swapchain = *Memoryqe::as_relative<IDXGISwapChain**>(Memoryqe::find_pattern(gta5_module, ("Swapchain"), "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8"));*/


	Memory::initGame();
	c_lua::get().initialize();

	if (!inited) {
		PlaySoundA((LPCTSTR)Inject_sound, NULL, SND_MEMORY | SND_ASYNC);
		inited = true;
	}

	//Hooks::Instance().Render();




	//if (global_nat_platf::version_platform == 2) {
	//	auto ptr = std::make_unique<gta::pointers>();
	//	if (!ptr) {
	//		Beep(1000, 100);
	//	}
	//	auto ptrq = std::make_unique<gta::hooking>();
	//	if (!ptrq) {
	//		Beep(1000, 100);
	//	}
	//}
	//else {
	
	//}



	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle("dxgi.dll");
	} while (!hDXGIDLL);

	IDXGISwapChain* pSwapChain;
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = MultisampleCount;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	UINT createFlags = 0;
	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBox(hWnd, "Failed to create directX device and swapchain!", "Error", MB_ICONERROR);
		return NULL;
	}
	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];
	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];
	phookD3D11Present = (D3D11PresentHook)(DWORD_PTR*)pSwapChainVtable[8];
	phookD3D11ResizeBuffers = (D3D11ResizeBuffersHook)(DWORD_PTR*)pSwapChainVtable[13];
	phookD3D11PSSetShaderResources = (D3D11PSSetShaderResourcesHook)(DWORD_PTR*)pContextVTable[8];
	phookD3D11Draw = (D3D11DrawHook)(DWORD_PTR*)pContextVTable[13];
	phookD3D11DrawIndexed = (D3D11DrawIndexedHook)(DWORD_PTR*)pContextVTable[12];
	phookD3D11DrawIndexedInstanced = (D3D11DrawIndexedInstancedHook)(DWORD_PTR*)pContextVTable[20];
	//phookD3D11CreateQuery = (D3D11CreateQueryHook)(DWORD_PTR*)pDeviceVTable[24];


	call_fiber();
	if (MH_Initialize() != MH_OK) return 0;
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) return 1;
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) return 1;

	MH_CreateHook(gta_script_thread_tick, hooked_native_thread, reinterpret_cast<void**>(&original_native_thread));
	if (gta_script_thread_tick) {
		if (MH_EnableHook(gta_script_thread_tick) == MH_OK) {
			cout << "succes hook thread tick" << endl;
		}
	}

	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	while (true)
	{
		Sleep(10000);
	}

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();










	//if (!global::Panic) {
	//	while (!global::Panic)
	//	{
	//		superjump(amphetamine::amphetamine_settings->SuperJump);
	//		if (amphetamine::amphetamine_settings->customtime) {
	//			network::network_override_clock_time(amphetamine::amphetamine_settings->customtimesize, 0, 0);
	//		}
	//		Sleep(20);
	//	}
	//}
	//while (true) { Sleep(700); }



	return NULL;
}


std::vector <std::string> rememberlogin;

__forceinline void Activate() {

	auto accepted_request = DownloadString((string)xorstr_("https://amph.su/client/auto_login.php?hwid=") + uLoader::get_hwidqwe().c_str());
	if (!accepted_request.empty()) {
		rememberlogin.clear();
		std::istringstream iss(accepted_request);
		std::string item;
		while (iss >> item) {
			rememberlogin.push_back(item);
		}
		Global::client.username = rememberlogin[0];
		Global::client.password = rememberlogin[1];

	}
	if (!g_XenForo.Endpoint.Auth.setup(xorstr_("https://amph.su/index.php/api/auth"), xorstr_("ON2q0uoTkrSj8JYV7eRnx8Gy_29auPqN")))
	{
		exit(-1);
	}

	if (!g_XenForo.Endpoint.Auth.request(Global::client.username, Global::client.password))
	{
		exit(-1);
	}

	if (g_XenForo.Endpoint.Auth.example())
	{
		//Successfully authenticated user
		if (uLoader::checkUser() == 1) {	
			tabb = 1;
			InitializeHook();	
		}
		if (uLoader::checkUser() == 2) {
			exit(-1);
		}
		if (uLoader::checkUser() == 3) {
			exit(-1);
		}
	}
}




static bool OverlayHooked = false;
void startthreadauth() {

	
	//uintptr_t module_ragemp = (uintptr_t)SAFE_CALL(GetModuleHandleA)("multiplayer.dll");

	//if (module_ragemp != 0) {
	//	global_nat_platf::version_platform = 2;
	//}
	//else {
	//	global_nat_platf::version_platform = 1;
	//}


	global_nat_platf::version_platform = 1;

	if (!uLoader::check_version()) {
		exit(-1);
	}
	else {
		Activate();
	}
}


namespace Mega_AntiCrack_1000iq
{
	int getProcID(const std::string& p_name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 structprocsnapshot = { 0 };

		structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

		if (snapshot == INVALID_HANDLE_VALUE)return 0;
		if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;

		while (Process32Next(snapshot, &structprocsnapshot))
		{
			if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
			{
				CloseHandle(snapshot);
				return structprocsnapshot.th32ProcessID;
			}
		}
		CloseHandle(snapshot);
		return 0;

	}
	bool isProcRunning(std::string process) {
		if (getProcID(process) == 0) {
			return false;
		}
		else
		{
			return true;
		}
	}
	void ProcessHacker_check() {
		if (isProcRunning(xorstr_("ProcessHacker.exe"))) {
			raise(11);
		}
	}
	void Tick() {
		if (isProcRunning(xorstr_("ida64.exe"))
			|| isProcRunning(xorstr_("dotPeek64.exe"))
			|| isProcRunning(xorstr_("ida32.exe"))
			|| isProcRunning(xorstr_("ida.exe"))
			|| isProcRunning(xorstr_("reclass.net.exe"))
			|| isProcRunning(xorstr_("reclass.exe"))
			|| isProcRunning(xorstr_("heyrays.exe"))
			|| isProcRunning(xorstr_("lighthouse.exe"))
			|| isProcRunning(xorstr_("cheatengine-x86_64.exe"))
			|| isProcRunning(xorstr_("classinformer.exe"))
			|| isProcRunning(xorstr_("ida-x86emu.exe"))
			|| isProcRunning(xorstr_("cffexplorer.exe"))
			|| isProcRunning(xorstr_("winhex.exe"))
			|| isProcRunning(xorstr_("hiew.exe"))
			|| isProcRunning(xorstr_("fiddler.exe"))
			|| isProcRunning(xorstr_("httpdebugger.exe"))
			|| isProcRunning(xorstr_("httpdebuggerpro.exe"))
			|| isProcRunning(xorstr_("scylla.exe"))
			|| isProcRunning(xorstr_("Cheat Engine.exe")))
		{
			clown();
			raise(11);
		}
	}
}
string GlobalBanHwid(string nadolibanit) {
	std::string tempory_cipher_key;
	std::string tempory_iv_key;
	std::vector<std::string> vector_tempory_key;
	auto unprotect_request = DownloadString((string)xorstr_("https://") + Global::server.server + (string)xorstr_("/client/session.php"));
	for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 64)
		tempory_cipher_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
	for (std::size_t pos = 0; pos < unprotect_request.size(); pos += 32)
		tempory_iv_key = vector_tempory_key.emplace_back(unprotect_request.data() + pos, unprotect_request.data() + min(pos + 32, unprotect_request.size()));
	std::string protect_request = aes::encrypt(unprotect_request, tempory_cipher_key, tempory_iv_key);
	std::string protect_hwid = aes::encrypt(uLoader::get_hwidqwe(), tempory_cipher_key, tempory_iv_key);
	unprotect_request = aes::encrypt(unprotect_request, (string)xorstr_("r09y7LrY1C4yqONI641qMQe7GA5mQvdf"), (string)xorstr_("H1ggF9foFGLerr8q")); // static keys
	auto accepted_request = DownloadString((string)xorstr_("https://amph.su/client/globalbanhwids.php?a=") + unprotect_request + (string)xorstr_("&b=") + protect_request + (string)xorstr_("&hwid=") + protect_hwid + (string)xorstr_("&nadolibanit=") + nadolibanit);
	return aes::decrypt(aes::decrypt(accepted_request, tempory_cipher_key, tempory_iv_key), tempory_cipher_key, tempory_iv_key);
}
int globalbanshwid(string nadolibanit) { //"0" бан не выдается, "1" бан выдается
	std::string nadolibanitt = nadolibanit;
	std::string output = GlobalBanHwid(nadolibanitt);

	if (output == xorstr_("estbanhwida")) {
		return 1;
	}
	else if (output == xorstr_("bananet")) {
		return 2;
	}
}
__forceinline void BanThread()
{
	while (true)
	{
		Mega_AntiCrack_1000iq::Tick();
		Mega_AntiCrack_1000iq::ProcessHacker_check();
		if (tabb == 1) {

			if (uLoader::checkUser() == 3) { //Subscription ERROR
				raise(11);
			}
			if (uLoader::checkUser() == 4) { //Invalid username
				raise(11);
			}
			if (uLoader::checkUser() == 5) { //Invalid password
				raise(11);
			}
			if (uLoader::checkUser() == 6) { //banned acc forum
				clown();
				raise(11);
			}
			if (globalbanshwid(xorstr_("0")) == 1) //banned hwid
			{
				clown();
				raise(11);
			}
		}
		Sleep(500000);
	}
}

#include "src/Main/secure.h"


extern "C" __declspec(dllexport) 
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		SAFE_CALL(_beginthreadex)(0, 0, (_beginthreadex_proc_type)startthreadauth, 0, 0, 0);
		SAFE_CALL(_beginthreadex)(0, 0, (_beginthreadex_proc_type)BanThread, 0, 0, 0);
		tools::unlink_module_peb(hModule);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {

	}
	return TRUE;
}

extern "C" __declspec(dllexport) int gfdgKJdf(int code, WPARAM wParam, LPARAM lParam) {
  return CallNextHookEx(NULL, code, wParam, lParam);
}