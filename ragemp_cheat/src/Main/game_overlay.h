bool proverka_unloada = false;

using namespace std;
class Renderer : public Singleton<Renderer>
{
private:
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pDeviceContext = NULL;

public:
	bool bInitialized = false;

	void Render(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags);
};

class Fonts : public Singleton<Fonts>
{
public:
	ImFont* fITCAvant18 = nullptr;
};
using namespace std;

class Nemo : public Singleton<Nemo>
{
public:
	HMODULE hModule = nullptr;
	HWND hWindow = nullptr;
	WNDPROC wWndproc = nullptr;

	Vector2 vScreen = Vector2(1920, 1080);
	string sProcessName = "RAGE Multiplayer";

	void Run(HMODULE hModule);
	void Shutdown();
};
class Wndproc : public Singleton<Wndproc>
{
public:
	LRESULT call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l);
};
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Wndproc::call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l)
{
	if (message_u == WM_KEYUP)
	{
		//if (param_w == VK_DELETE)
		if (param_w == amphetamine::amphetamine_settings->key_menu_global)
		{
			global::show = !global::show;
		}

		//if (param_w == VK_NUMPAD9) Config::Instance().self.noclip = !Config::Instance().self.noclip;

		/* VEHICLE STEALER, need to be ported into hack module */
		if (param_w == VK_NUMPAD1) {
			//if (Config::Instance().vehicle.stealer) Config::Instance().vehicle.want_steal = !Config::Instance().vehicle.want_steal;
		}
	}

	if (ImGui::GetIO().MouseDrawCursor)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, message_u, param_w, param_l))
			return true;

		return 1l;
	}

	return CallWindowProc(Nemo::Instance().wWndproc, hwnd, message_u, param_w, param_l);
}
LRESULT call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l) {
	return Wndproc::Instance().call_wndproc(hwnd, message_u, param_w, param_l);
}


namespace hooks
{
	class virtual_table_hook
	{
	public:
		explicit virtual_table_hook() noexcept { }

		explicit virtual_table_hook(std::string name, void* obj, std::size_t num_funcs) :
			m_object(static_cast<void***>(obj)),
			m_num_funcs(num_funcs + 1),
			m_name(name),
			m_original_table(*m_object),
			m_new_table(std::make_unique<void* []>(m_num_funcs))
		{
			std::copy_n(m_original_table - 1, m_num_funcs, m_new_table.get());
		}

		void operator=(virtual_table_hook vmt)
		{
			m_name = vmt.m_name;
			m_object = vmt.m_object;
			m_num_funcs = vmt.m_num_funcs;
			m_original_table = vmt.m_original_table;
			m_new_table = vmt.m_new_table;
		}

		~virtual_table_hook() noexcept
		{
			if (m_hooked)
				disable();

			m_new_table.reset();
		}

		void enable()
		{
			*m_object = m_new_table.get() + 1;
			m_hooked = true;

			//	Log::Debug(_xor_("[+] Hooks >>"), m_name, _xor_("enabled."));
		}

		void disable()
		{
			if (m_hooked)
			{
				m_hooked = false;
				*m_object = m_original_table;
			}
		}

		void attach(std::size_t index, void* func)
		{
			m_new_table[index + 1] = func;
		}

		void detach(std::size_t index)
		{
			m_new_table[index + 1] = m_original_table[index];
		}

		template<typename type>
		type fetch(type func, int index)
		{
			return static_cast<type>(m_original_table[index]);
		}

	private:
		bool						m_succeed_create = false;
		bool						m_hooked = false;
		std::string					m_name;

		void*** m_object;
		std::size_t					m_num_funcs;

		void** m_original_table;
		std::shared_ptr<void* []>	m_new_table;
	};
}
using namespace std;
class Hooks : public Singleton<Hooks>
{
private:
	void Thread();
	void Native();
public:
	std::unique_ptr<hooks::virtual_table_hook> vthDirectHook;
	//Memory::script_thread_tick_t original_native_thread = nullptr;


	void Render();
	void Initialize();
};

IDXGISwapChain* ptr_gta_swapchain = nullptr;

enum game_state_t
{
	playing,
	intro,
	unk,
	license,
	main_menu,
	load_online
};
game_state_t* ptr_gta_game_state = 0;
void Nemo::Shutdown()
{
	//MH_DisableHook(MH_ALL_HOOKS);
	//MH_Uninitialize();

	//Hooks::Instance().vthDirectHook->detach(8);
	//Hooks::Instance().vthDirectHook->disable();

	SetWindowLongPtrW(this->hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(this->wWndproc));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


static int tabb = 0;
bool init_vehicle_egineon = false;

void Renderer::Render(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags) {
	if (!global::Panic) {

	}
	else {
		if (!proverka_unloada) {
			clearwinr();
			regedit_clear();
			amphetamine::amphetamine_settings->No_Recoil = false;
			amphetamine::amphetamine_settings->No_Spread = false;

			proverka_unloada = true;
		}
		Nemo::Instance().Shutdown();
	}
	if (!global::Panicnoclear) {

	}
	else {
		if (!proverka_unloada) {
			amphetamine::amphetamine_settings->No_Recoil = false;
			amphetamine::amphetamine_settings->No_Spread = false;

			proverka_unloada = true;
		}
		Nemo::Instance().Shutdown();
	}


	if (!bInitialized) {
		this_swapchain_pointer->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pDeviceContext);

		ImGui::CreateContext();


		DXGI_SWAP_CHAIN_DESC sd;
		this_swapchain_pointer->GetDesc(&sd);
		Nemo::Instance().hWindow = sd.OutputWindow;

		ImGuiStyle* s = &ImGui::GetStyle();
		init_styles(*s);
		s->WindowPadding = ImVec2(0, 0), s->WindowBorderSize = 0;
		s->ItemSpacing = ImVec2(20, 20);
		s->ScrollbarSize = 8.f;

		//static TCHAR path[MAX_PATH];
		//std::string savedCreditsPath;
		//SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path);
		//savedCreditsPath = std::string(path) + ("\\AMTH.CSGO\\avatar.png");
		//IconAvatarInit(savedCreditsPath);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImFontConfig cfg;
		cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
		static const ImWchar ranges[] = {
	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	0x2000, 0x206F, // General Punctuation
	0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
	0x31F0, 0x31FF, // Katakana Phonetic Extensions
	0xFF00, 0xFFEF, // Half-width characters
	0x4e00, 0x9FAF, // CJK Ideograms
	0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
	0x2DE0, 0x2DFF, // Cyrillic Extended-A
	0xA640, 0xA69F, // Cyrillic Extended-B
	0,
		};

		font::poppins_medium = io.Fonts->AddFontFromMemoryTTF(poppins_medium, sizeof(poppins_medium), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		font::poppins_medium_low = io.Fonts->AddFontFromMemoryTTF(poppins_medium, sizeof(poppins_medium), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		font::tab_icon = io.Fonts->AddFontFromMemoryTTF(tabs_icons, sizeof(tabs_icons), 24.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		font::tahoma_bold = io.Fonts->AddFontFromMemoryTTF(tahoma_bold, sizeof(tahoma_bold), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		font::tahoma_bold2 = io.Fonts->AddFontFromMemoryTTF(tahoma_bold, sizeof(tahoma_bold), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		font::chicons = io.Fonts->AddFontFromMemoryTTF(chicon, sizeof(chicon), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

		if (image::roll == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, iconmain, sizeof(iconmain), &info, pump, &image::roll, 0);
		if (image::rusifikacia == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, engbyte, sizeof(engbyte), &info, pump, &image::rusifikacia, 0);
		if (image::rusifikacia_ru == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, rubyte, sizeof(rubyte), &info, pump, &image::rusifikacia_ru, 0);
		if (image::discord_logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, discordlogoo, sizeof(discordlogoo), &info, pump, &image::discord_logo, 0);
		if (image::telegram_logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, telegramlogo, sizeof(telegramlogo), &info, pump, &image::telegram_logo, 0);
		if (image::vk_logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, vklogoo, sizeof(vklogoo), &info, pump, &image::vk_logo, 0);
		if (image::site_logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(pDevice, sitelogoo, sizeof(sitelogoo), &info, pump, &image::site_logo, 0);
		fontbigg = io.Fonts->AddFontFromFileTTF(("C:/windows/fonts/tahoma.ttf"), 44.f, &cfg, ranges);

		ImGui_ImplWin32_Init(Nemo::Instance().hWindow);
		ImGui_ImplDX11_Init(pDevice, pDeviceContext);
		Nemo::Instance().wWndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(Nemo::Instance().hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(call_wndproc)));


		static TCHAR pathqw[MAX_PATH];
		std::string savedCreditsPathqw;
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, pathqw);
		savedCreditsPathqw = std::string(pathqw) + xorstr_("\\AMTH.CSGO\\font.bin");
		std::ifstream fin(savedCreditsPathqw);
		fin >> custmomfontname;
		std::ifstream file;
		file.open(savedCreditsPathqw);

		bInitialized = true;
	}

	static uintptr_t pixel_refresh_clock = 0;
	if (GetTickCount64() - pixel_refresh_clock > 4000)
	{
		RECT rect;
		GetClientRect(Nemo::Instance().hWindow, &rect);
		int client_width = (rect.right - rect.left);
		int client_height = (rect.bottom - rect.top);

		Nemo::Instance().vScreen = { static_cast<float>(client_width), static_cast<float>(client_height) };
		global::ScreenHeight = client_height;
		global::ScreenWidth = client_width;

		pixel_refresh_clock = GetTickCount64();
	}
	tab_size = ImLerp(tab_size, tab_opening ? 160.f : 0.f, ImGui::GetIO().DeltaTime * 12.f);
	arrow_roll = ImLerp(arrow_roll, tab_opening && (tab_size >= 159) ? 1.f : -1.f, ImGui::GetIO().DeltaTime * 12.f);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();



	Render_D2::NewFrame(this_swapchain_pointer);


	if (loaded_script)
		for (auto current : c_lua::get().hooks.getHooks("on_paint"))
			current.func();

	/////

	//numberplatesfindvehicle();
	//testmegafunk();
	Visuals::draw_object_esp();
	Visuals::VehicleESP();
	click_warp_vehicle();
	Entity_Tick();
	Visuals::localplayer_esp();
	players_tick();
	weapons_tick();
	Vehicle_r::Instance().Tick();
	MiscFunk::MiscF();
	//debugcamera();

	pre_draw();
	Render_D2::EndFrame();
	if (welcome_succes) {
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0, 0, 0, 0.0 });
		ImGui::Begin(xorstr_("##welcome"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove);
		{
			notification::position = ImGui::GetWindowPos();
			notification::draw = ImGui::GetForegroundDrawList();
			if (welcome_succes == true) {
				bool notifydone = false;
				notification::start(xorstr_("Welcome to AMPH.su"), Global::client.username.c_str(), &notifydone);
				if (notifydone)
				{
					welcome_succes = false;
				}
			}
		}
		ImGui::End();
		ImGui::PopStyleColor();
	}

	if (tabb == 1) {
		Stealth_menu();
	}

	if (global::show) {
		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
	}
	else {
		ImGui::GetIO().MouseDrawCursor = false;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


HRESULT call_renderer_hook(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags)
{
	Renderer::Instance().Render(this_swapchain_pointer, sync_interval, flags);
	return Hooks::Instance().vthDirectHook->fetch(call_renderer_hook, 8)(this_swapchain_pointer, sync_interval, flags);
}
void Hooks::Render() {
	this->vthDirectHook = std::make_unique<hooks::virtual_table_hook>(("Swapchain"), ptr_gta_swapchain, 0x12);
	this->vthDirectHook->attach(8, call_renderer_hook);
	this->vthDirectHook->enable();
}