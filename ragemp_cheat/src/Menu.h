
bool fsdjgnsifjdgjsdfjgjksdfgkj = false;
void teleport_entity_to_coords(Entity e, Vector3 pos)
{
	Vector3 tmp = pos;
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, tmp.x, tmp.y, tmp.z, 0, 0, 0);
}

void teleport_to_coords(Vector3 coords)
{
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_ID(),0))
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	teleport_entity_to_coords(e, coords);
}








static bool Dcheckbox = false;
static bool Headcheckbox = false;
static bool Healthcheckbox = false;
static bool Namecheckbox = false;
static bool Distancecheckbox = false;
static bool weaponcheckbox = false;
static bool Filterteams = false;
static bool Filterteams_map = false;
static bool Bonecheckbox = false;
static float boxtk = 1.f;
static float hptk = 1.f;
static float hdtk = 1.f;
static float bonetk = 1.f;
static bool Flogs[6] = { false, false, false, false,false };
const char* Flogss[6] = { "Head", "Health Bar", "Player Name", "Distance","Weapon" };


DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;
float tab_size = 0.f;
float arrow_roll = 0.f;
bool tab_opening = true;

static bool languages = true;

void Particles()
{
	ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

	static ImVec2 partile_pos[100];
	static ImVec2 partile_target_pos[100];
	static float partile_speed[100];
	static float partile_radius[100];


	for (int i = 1; i < 50; i++)
	{
		if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
		{
			partile_pos[i].x = rand() % (int)screen_size.x + 1;
			partile_pos[i].y = 15.f;
			partile_speed[i] = 1 + rand() % 25;
			partile_radius[i] = rand() % 4;

			partile_target_pos[i].x = rand() % (int)screen_size.x;
			partile_target_pos[i].y = screen_size.y * 2;
		}

		partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

		if (partile_pos[i].y > screen_size.y)
		{
			partile_pos[i].x = 0;
			partile_pos[i].y = 0;
		}

		ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 255.f / 2));
	}

}
enum sub_heads {
	general, accuracy, exploits, _general, advanced
};
struct subtab_element {

	float element_opacity, rect_opacity, text_opacity;
	ImVec4 image, background;
};

bool subtab(const char* name, bool boolean)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(name);
	const ImVec2 label_size = ImGui::CalcTextSize(name);
	ImVec2 pos = window->DC.CursorPos;

	const ImRect rect(pos, ImVec2(pos.x + 85, pos.y + 32));
	ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 3), style.FramePadding.y);
	if (!ImGui::ItemAdd(rect, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

	static std::map <ImGuiID, subtab_element> anim;
	auto it_anim = anim.find(id);
	if (it_anim == anim.end()) {
		anim.insert({ id, { 0.0f, 0.0f, 0.0f } });
		it_anim = anim.find(id);
	}

	it_anim->second.element_opacity = ImLerp(it_anim->second.element_opacity, (boolean ? 0.04f : 0.0f), 0.09f * (1.0f - ImGui::GetIO().DeltaTime));
	it_anim->second.rect_opacity = ImLerp(it_anim->second.rect_opacity, (boolean ? 1.0f : 0.0f), 0.20f * (1.0f - ImGui::GetIO().DeltaTime));
	it_anim->second.text_opacity = ImLerp(it_anim->second.text_opacity, (boolean ? 1.0f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
	it_anim->second.image = ImLerp(it_anim->second.image, boolean || hovered ? ImVec4(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.5f) : c::text::text, g.IO.DeltaTime * 12.f);
	it_anim->second.background = ImLerp(it_anim->second.background, boolean || hovered ? c::child::outline_background : hovered ? c::child::outline_background : c::child::outline_background, g.IO.DeltaTime * 12.f);


	//  window->DrawList->AddShadowRect(rect.Min, rect.Max, GetColorU32(it_anim->second.image), 70, ImVec2(0, 0), 35, 70);

	if (boolean) {
		ImGui::GetWindowDrawList()->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32(it_anim->second.background), c::button::rounding);
		ImGui::GetWindowDrawList()->AddRect(rect.Min, rect.Max, ImGui::GetColorU32(it_anim->second.image), c::button::rounding);

		ImGui::GetWindowDrawList()->AddShadowRect(rect.Min, rect.Max, ImGui::GetColorU32(it_anim->second.image), 70, ImVec2(0, 0), 35, 70);

	}
	ImGui::GetWindowDrawList()->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32(c::checkbox::background), c::button::rounding);
	ImGui::GetWindowDrawList()->AddRect(rect.Min, rect.Max, ImGui::GetColorU32(c::checkbox::outline_background), c::button::rounding);




	window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity), 3.0f);
	window->DrawList->AddText(ImVec2(rect.Min.x + 15, (rect.Min.y + rect.Max.y) / 2 - label_size.y / 2), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity), name);

	window->DrawList->AddRectFilled(ImVec2(rect.Max.x + 5, rect.Min.y + 9), ImVec2(rect.Max.x + 8, rect.Max.y - 9), ImGui::GetColorU32(it_anim->second.image), 10.0f, ImDrawFlags_RoundCornersLeft);









	return pressed;
}
void init_styles(ImGuiStyle& style)
{
	style.Colors[ImGuiCol_Border] = ImVec4(c::text::text.x, c::text::text.y, c::text::text.z, c::text::text.w / 2);
	style.Colors[ImGuiCol_FrameBg] = ImColor(43, 63, 90, 1);

	style.Colors[ImGuiCol_Text] = ImVec4(c::text::text_hov.x, c::text::text_hov.y, c::text::text_hov.z, c::text::text_hov.w / 2);
}
static int select_tab_misc = 0;
static int select_tab_visuals = 0;
void Stealth_menu() {
	IMGUI_API bool			ListBoxConfigArray(const char* label, int* currIndex, std::vector<std::string>&values, int height = 9, bool custom_selectable = true);



	static sub_heads subtab_{ general };

	ImGuiStyle* s = &ImGui::GetStyle();


	//if (amphetamine::amphetamine_settings->show) {
	if (global::show) {
		ImGui::SetNextWindowSize(ImVec2(c::bg::size) + ImVec2(tab_size, 0));
		//ImGui::Begin("IMGUI MENU", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
		bool luawindow = false;
		ImGui::Begin(xorstr_("decor amph"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
		{
			static int tabs = 0;
			const ImVec2& pos = ImGui::GetWindowPos();
			const auto& p = ImGui::GetWindowPos();
			const ImVec2 spacing = ImGui::GetStyle().ItemSpacing;

			ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(c::bg::size) + ImVec2(tab_size, 0), ImGui::GetColorU32(ImVec4(c::bg::background)), c::bg::rounding);
			ImGui::GetBackgroundDrawList()->AddRect(pos, pos + ImVec2(c::bg::size) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::bg::outline_background), c::bg::rounding);

			//ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(pos, pos + ImVec2(c::bg::size) + ImVec2(tab_size, 0), ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f)); //dark


			ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(c::accent_text_color));

			ImGui::PushFont(font::tahoma_bold2); ImGui::RenderTextClipped(pos + ImVec2(60, 0) + spacing, pos + spacing + ImVec2(60, 70) + ImVec2(tab_size + (spacing.x / 2) - 30, 0), xorstr_("AMPH"), NULL, NULL, ImVec2(0.5f, 0.5f), NULL); ImGui::PopFont();

			if (ïîëó÷åíèåäàòûïîäïèñêè != xorstr_("")) {
				ImGui::RenderTextClipped(pos + ImVec2(60 + spacing.x, c::bg::size.y - 60 * 2), pos + spacing + ImVec2(60, c::bg::size.y) + ImVec2(tab_size, 0), ïîëó÷åíèåäàòûïîäïèñêè.c_str(), NULL, NULL, ImVec2(0.0f, 0.43f), NULL);
			}
			else {
				clown();
				exit(-1);
			}
			if (Global::client.username != xorstr_("")) {
				ImGui::RenderTextClipped(pos + ImVec2(60 + spacing.x, c::bg::size.y - 60 * 2), pos + spacing + ImVec2(60, c::bg::size.y) + ImVec2(tab_size, 0), Global::client.username.c_str(), NULL, NULL, ImVec2(0.0f, 0.57f), NULL);
			}
			else {
				clown();
				exit(-1);
			}


			//  ImGui::PushFont(font::tahoma_bold2); ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(250, 255, 255,255)); ImGui::RenderTextClipped(pos + ImVec2(0, 0) + spacing, pos + spacing + ImVec2(60, 40) + ImVec2(tab_size + (spacing.x / 2) + 199, 0), "Hello, Fe1ZeP", NULL, NULL, ImVec2(1.f, 0.5f), NULL); ImGui::PopFont(); ImGui::PopStyleColor();

			ImGui::GetBackgroundDrawList()->AddImage((void*)IconAvatar, pos + ImVec2(10, 10), pos + ImVec2(10, 10), ImVec2(100, 100), ImVec2(100, 100), ImColor(255, 255, 255, 255));
			ImGuiContext& g = *GImGui;
			ImGuiWindow* parent_window = g.CurrentWindow;
			//if (tabs == 2) {
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::BeginChild("", "  ", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60));

			//	const char* items[6]{ xorstr_("Player"), xorstr_("LocalPlayer"), xorstr_("Bots"), xorstr_("Admin"), xorstr_("Object/Other"), xorstr_("Radar") };
			//	ImGui::Combo(xorstr_("Section"), &select_tab_visuals, items, IM_ARRAYSIZE(items), 3);
			//	ImGui::EndChild();
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);

			//}
			//else if (tabs == 3) {
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::BeginChild("", "  ", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60));
			//	const char* items[4]{ xorstr_("LocalPlayer"), xorstr_("Vehicle"), xorstr_("Exploit"), xorstr_("Vehicle/Player List") };
			//	ImGui::Combo(xorstr_("Section"), &select_tab_misc, items, IM_ARRAYSIZE(items), 3);
			//	ImGui::EndChild();
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);

			//}
			//else {
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::BeginChild("", "  ", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60));
			//	ImGui::Text(xorstr_("Global Section"));
			//	ImGui::EndChild();
			//	ImGui::SetCursorPos(ImVec2(60 + tab_size, -20) + (s->ItemSpacing * 2));
			//	ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);

			//}
			{
				//ImGui::SetCursorPos(ImVec2(385 + tab_size, -20) + (s->ItemSpacing * 2));
				//ImGuiContext& g = *GImGui;
				//ImGuiWindow* parent_window = g.CurrentWindow;
				//ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImGui::GetColorU32(c::child::background), c::child::rounding);
				//ImGui::GetWindowDrawList()->AddRect(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);

				//ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 60), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);

				//ImGui::SetCursorPos(ImVec2(415 + tab_size, -5) + (s->ItemSpacing * 2));
				//if (ImGui::CustomButton(2, languages ? image::rusifikacia_ru : image::rusifikacia, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(255, 255, 255, 255.f))))
				//	languages = !languages;
				//ImGui::SameLine();
				//if (ImGui::CustomButton(3, image::discord_logo, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(255, 255, 255, 255.f))))
				//	system(xorstr_("start https://discord.gg/6gcHpxKRHT"));
				//ImGui::SameLine();
				//if (ImGui::CustomButton(4, image::telegram_logo, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(255, 255, 255, 255.f))))
				//	system(xorstr_("start https://t.me/amphetamine_su"));
				//ImGui::SameLine();
				//if (ImGui::CustomButton(5, image::vk_logo, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(255, 255, 255, 255.f))))
				//	system(xorstr_("start https://vk.com/amph_su"));
				//ImGui::SameLine();
				//if (ImGui::CustomButton(5, image::site_logo, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(255, 255, 255, 255.f))))
				//	system(xorstr_("start https://amph.su"));
			}
			ImGui::PopStyleColor(1);
			const char* nametab_array1[5] = { "E", "A", "D", "C", "B" };
			const char* nametab_array[5] = { xorstr_("AimBot"), xorstr_("Weapon"), xorstr_("Visuals"), ("Misc"), xorstr_("Settings") };
			const char* nametab_hint_array[5] = { xorstr_("Aim, Damager, Trigger"), xorstr_("Recoil, Spread, RapidFire"), xorstr_("Player, Local, Admin"), xorstr_("Player, LocalPlayer"), xorstr_("Save, Load, Editor") };
			const char* nametab_arraynamee[5] = { "0", "1", "0", "0", "0" };
		/*	ImGui::SetCursorPos(ImVec2(spacing.x + (60 - 22) / 2, 60 + (spacing.y * 2) + 22));
			
			ImGui::BeginGroup();
			{
				for (int i = 0; i < sizeof(nametab_array1) / sizeof(nametab_array1[0]); i++)
				{
					if (ImGui::Tab(i == tabs, nametab_array1[i], nametab_array[i], nametab_hint_array[i], ImVec2(35 + tab_size, 35), nametab_arraynamee[i]))
					{
						tabs = i;
					}
				}
			}
			ImGui::EndGroup();*/
			ImGui::SetCursorPos(ImVec2(spacing.x + 40 / 2, 60 + (spacing.y * 2) + 10));
			ImGui::BeginGroup();
			{
				// e_elements::begin_child("Tabs", ImVec2(35 + tab_size + 50, 340));
				{
					for (int i = 0; i < sizeof(nametab_array1) / sizeof(nametab_array1[0]); i++)
					{
						if (ImGui::Tab(i == tabs, nametab_array1[i], nametab_array[i], nametab_hint_array[i], ImVec2(tab_opening == true ? tab_size - 80 : tab_size /* - 80*/, 50), nametab_arraynamee[i]))
						{
							tabs = i;
						}
					}
				}
				// e_elements::end_child();
			}
			ImGui::EndGroup();


			if (tabs == 0) {

				tab_opening = false;

				/*ImGui::SetCursorPos(ImVec2(spacing.x + 195 / 2, 60 + (spacing.y * 2)));
				ImGui::BeginGroup(); {
					ImGui::BeginChild("AimBot", ImVec2((c::bg::size.x - 550) / 2, 165));
					if (subtab("Vector", subtab_ == general)) { subtab_ = general; }
					if (subtab("Silent", subtab_ == accuracy)) { subtab_ = accuracy; }
					if (subtab("TriggerBot", subtab_ == exploits)) { subtab_ = exploits; }
					ImGui::EndChild();

				} ImGui::EndGroup();*/
			}
			if (tabs == 1) {

				tab_opening = false;

				
			}
			if (tabs == 2) {
				tab_opening = true;
				//const char* items[6]{ xorstr_("Player"), xorstr_("LocalPlayer"), xorstr_("Bots"), xorstr_("Admin"), xorstr_("Object/Other"), xorstr_("Radar") };
				ImGui::SetCursorPos(ImVec2(spacing.x + 195 / 2, 60 + (spacing.y * 2)));
				ImGui::BeginGroup(); {
					ImGui::BeginChild("Visuals", ImVec2((c::bg::size.x - 550) / 2, 300));
					if (subtab("Player", select_tab_visuals == 0)) { select_tab_visuals = 0; }
					if (subtab("Local", select_tab_visuals == 1)) { select_tab_visuals = 1; }
				    if (subtab("Bots", select_tab_visuals == 2)) { select_tab_visuals = 2; }
					if (subtab("Admin", select_tab_visuals == 3)) { select_tab_visuals = 3; }
					if (subtab("Other", select_tab_visuals == 4)) { select_tab_visuals = 4; }
					if (subtab("Radar", select_tab_visuals == 5)) { select_tab_visuals = 5; }
					ImGui::EndChild();

				} ImGui::EndGroup();
			}
			if (tabs == 3) {
				tab_opening = true;
				//const char* items[4]{ xorstr_("LocalPlayer"), xorstr_("Vehicle"), xorstr_("Exploit"), xorstr_("Vehicle/Player List") };
				ImGui::SetCursorPos(ImVec2(spacing.x + 195 / 2, 60 + (spacing.y * 2)));
				ImGui::BeginGroup(); {
					ImGui::BeginChild("Misc", ImVec2((c::bg::size.x - 550) / 2, 210));
					if (subtab("Local", select_tab_misc == 0)) { select_tab_misc = 0; }
					if (subtab("Vehicle", select_tab_misc == 1)) { select_tab_misc = 1; }
					if (subtab("Exploit", select_tab_misc == 2)) { select_tab_misc = 2; }
					if (subtab("Lists", select_tab_misc == 3)) { select_tab_misc = 3; }
					ImGui::EndChild();

				} ImGui::EndGroup();
			}
			if (tabs == 4) {
				tab_opening = false;
			}

			//ImGui::SetCursorPos(ImVec2(4, 9) + spacing);

			//ImRotateStart();
			//if (ImGui::CustomButton(1, image::roll, ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 255.f)))) tab_opening = !tab_opening;
			//ImRotateEnd(1.57f * arrow_roll);


			////ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, -20 + spacing.y) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - 60 - spacing.y * 3) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::background), c::child::rounding);
			////ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, -20 + spacing.y) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - 60 - spacing.y * 3) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);

			////ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::background), c::child::rounding);
			////ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);

			////ImGui::GetWindowDrawList()->AddImage((void*)IconAvatar, pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing + ImVec2(12, 12), pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) - ImVec2(12, 12), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));


			////ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 10.f, ImGui::GetColorU32(c::child::background), 100.f);
			////ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 6.f, ImColor(0, 255, 0, 255), 100.f);



			//ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::background), c::child::rounding);
			//ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);
			//ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);



			//ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, 0) + spacing, pos + spacing + ImVec2(0, 70) + ImVec2(tab_size + 60, 0), ImGui::GetColorU32(c::child::background), c::child::rounding);
			//ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, 0) + spacing, pos + spacing + ImVec2(0, 70) + ImVec2(tab_size + 60, 0), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);


			//ImGui::GetWindowDrawList()->AddImage(IconAvatar, pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing + ImVec2(12, 12), pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) - ImVec2(12, 12), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));

			//ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 10.f, ImGui::GetColorU32(c::child::background), 100.f);
			//ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 6.f, ImColor(0, 255, 0, 255), 100.f);
			//ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(pos + ImVec2(0, 0) + spacing, pos + spacing + ImVec2(0, 70) + ImVec2(tab_size + 60, 0), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);


			ImGui::SetCursorPos(ImVec2(4, 9) + spacing);

			// ImRotateStart();
			if (ImGui::CustomButton(1, image::roll, ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImVec4(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 255.f)))) /*tab_opening = !tab_opening*/;
			// ImRotateEnd(1.57f * arrow_roll);


			ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::background), c::child::rounding);
			ImGui::GetBackgroundDrawList()->AddRect(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImGui::GetColorU32(c::child::outline_background), c::child::rounding);
			//  ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing, pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) + ImVec2(tab_size, 0), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);




			ImGui::GetWindowDrawList()->AddImage(IconAvatar, pos + ImVec2(0, c::bg::size.y - 60 - spacing.y * 2) + spacing + ImVec2(12, 12), pos + spacing + ImVec2(60, c::bg::size.y - spacing.y * 2) - ImVec2(12, 12), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));

			ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 10.f, ImGui::GetColorU32(c::child::background), 100.f);
			ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(63, c::bg::size.y - (spacing.y * 2) + 3), 6.f, ImColor(0, 255, 0, 255), 100.f);
			//  ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(pos + ImVec2(0, 0) + spacing, pos + spacing + ImVec2(0, 70) + ImVec2(tab_size + 60, 0), ImColor(c::child::background), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.f), ImColor(c::menu_sett::menu_color_swither.Value.x, c::menu_sett::menu_color_swither.Value.y, c::menu_sett::menu_color_swither.Value.z, 0.055f), 4.0f, ImDrawCornerFlags_TopLeft);

			if (popit) {
				Particles();
			}


			static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

			tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);
			tab_add = ImClamp(tab_add + (std::round(350.f) * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);

			if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs;

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * s->Alpha);
			if (tabs == 0)
			{
				if (subtab_ == general) {

					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));

					//ImGui::BeginChild( "      ", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
					ImGui::BeginChild(xorstr_("Vector Aim"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 230));
					{
						ImGui::Checkbox(xorstr_("Vector Aim"), &amphetamine::amphetamine_settings->Aimbot_Toggle);
						ImGui::Keybind(xorstr_("Aim Key"), &amphetamine::amphetamine_settings->HotKeyAim, true);
						ImGui::SliderInt(xorstr_("Smooth"), &amphetamine::amphetamine_settings->AimbotSmooth, 1, 30);

						const char* aimmodee[2] = { "Defoult", "Humanizer" };
						ImGui::Combo(xorstr_("Mode"), &amphetamine::amphetamine_settings->aimmode, aimmodee, 2);


						/*ImGui::Checkbox("slaper", &amphetamine::amphetamine_settings->slaper);
						ImGui::Keybind("slaper key", &amphetamine::amphetamine_settings->slaper_key, true);
					*/

					}
					ImGui::EndChild();


					ImGui::BeginChild(xorstr_("Silent Aim"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 160));
					{
						ImGui::Checkbox(xorstr_("Silent Aim"), &amphetamine::amphetamine_settings->Silent_Aim);


						ImGui::Checkbox(xorstr_("On key"), &amphetamine::amphetamine_settings->Silent_Aimhotkey);
						if (amphetamine::amphetamine_settings->Silent_Aimhotkey) {
							ImGui::Keybind(xorstr_("Silent Key"), &amphetamine::amphetamine_settings->silenthotkeyaim, true);
						}
					}
					ImGui::EndChild();

					ImGui::BeginChild(xorstr_("TriggerBot"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 160));
					{
						ImGui::Checkbox(xorstr_("Trigger Bot"), &amphetamine::amphetamine_settings->TriggerBot);
						ImGui::Keybind(xorstr_("Trigger Key"), &amphetamine::amphetamine_settings->trigetbotHotkey, true);
					}
					ImGui::EndChild();

					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					ImGui::BeginChild(xorstr_("Damager"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 160));
					{
						ImGui::Checkbox(xorstr_("Damager"), &amphetamine::amphetamine_settings->damager);
						ImGui::Keybind(xorstr_("Damager Key"), &amphetamine::amphetamine_settings->damager_key, true);
						ImGui::SliderInt(xorstr_("ShootRate"), &amphetamine::amphetamine_settings->shootRate, 1, 2000);
					}
					ImGui::EndChild();


					ImGui::BeginChild("Other", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590 - 180));
					{

						


						const char* AimbotBones[7] = { "Head", "Body", "Leg left", "Leg right", "Arm right", "Arm left", "Nearest" };
						ImGui::Combo(xorstr_("Bone"), &amphetamine::amphetamine_settings->Aimbot_Bone, AimbotBones, 7);
						ImGui::Checkbox(xorstr_("VisibleCheck"), &amphetamine::amphetamine_settings->VisibleCheck);
						ImGui::Checkbox(xorstr_("Bots Target"), &amphetamine::amphetamine_settings->Draw_botsaim);
						ImGui::SliderInt(xorstr_("Max Distance"), &amphetamine::amphetamine_settings->max_distance_aim, 10, 400);

						ImGui::SliderInt(xorstr_("Fov size"), &amphetamine::amphetamine_settings->Aimbot_Fov, 1, 1200 / 10);
						//ImGui::CheckPicker(xorstr_("Draw fov"), xorstr_("fov Color##2"), &amphetamine::amphetamine_settings->DrawFov, (float*)&amphetamine::amphetamine_settings->Fov_Color);

						ImGui::Checkbox(xorstr_("Draw fov"), &amphetamine::amphetamine_settings->DrawFov);
						ImGui::ColorEdit4(xorstr_("Fov Color"), (float*)&amphetamine::amphetamine_settings->Fov_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

						//ImGui::SliderFloat("2D box thick", &boxtk, 1.f, 5.f, "%.1f");
						///ImGui::SliderFloat("Head Size", &hdtk, 1.f, 10.f, "%.1f");
						///ImGui::SliderFloat("Health Size", &hptk, 1.f, 5.f, "%.1f");
						//ImGui::SliderFloat("Bone thick", &bonetk, 1.f, 5.f, "%.1f");

					}
					ImGui::EndChild();
					ImGui::EndGroup();
					// ImGui::SetCursorPos(ImVec2(260,540));
				}
			}
			if (tabs == 1)
			{
				ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
				//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
				ImGui::BeginGroup();
				{

					ImGui::BeginChild(xorstr_("Settings Weapon"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
					{
						ImGui::Checkbox(xorstr_("No Spread"), &amphetamine::amphetamine_settings->No_Spread);
						ImGui::Checkbox(xorstr_("No Recoil"), &amphetamine::amphetamine_settings->No_Recoil);
						//ImGui::Checkbox(xorstr_("Explosive Ammo"), &amphetamine::amphetamine_settings->ExplosiveAmmo);
						ImGui::Checkbox(xorstr_("No Reload"), &amphetamine::amphetamine_settings->NoReload);
						ImGui::Checkbox(xorstr_("Infinite Ammo"), &amphetamine::amphetamine_settings->InfiniteAmmo);
						ImGui::Checkbox(xorstr_("RainBow Weapon"), &amphetamine::amphetamine_settings->RainBowweapon);
						ImGui::Checkbox(xorstr_("Fire Ammo"), &amphetamine::amphetamine_settings->fire_ammo);
					//	ImGui::Checkbox(xorstr_("Rapid Fire"), &amphetamine::amphetamine_settings->rapidfire);
					}
					ImGui::EndChild();

				}
				ImGui::EndGroup();
				ImGui::SameLine();

				ImGui::BeginGroup();
				{

					ImGui::BeginChild(xorstr_("Others"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
					{
						ImGui::Checkbox(xorstr_("Explosive Melee"), &amphetamine::amphetamine_settings->explosive_melee);



					}
					ImGui::EndChild();
				}
				ImGui::EndGroup();





			}

			if (tabs == 2)
			{

				switch (select_tab_visuals) {
				case 0:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("Player"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							ImGui::Checkbox(xorstr_("Enable ESP"), &amphetamine::amphetamine_settings->enable);

							const char* boxtypes[3] = { "None", "Default", "Corner" };
							ImGui::Combo(xorstr_("Box ESP"), &amphetamine::amphetamine_settings->Npc_Box_Esp_Type, boxtypes, 3);
							ImGui::SliderFloat(xorstr_("Box Size"), &amphetamine::amphetamine_settings->BoxSize, 0.5, 3, "%.1f");
							ImGui::Checkbox(xorstr_("Fill Box"), &amphetamine::amphetamine_settings->Filled);
							ImGui::ColorEdit4(xorstr_("Box Color"), (float*)&amphetamine::amphetamine_settings->Box_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::Checkbox(xorstr_("Rainbow Box"), &amphetamine::amphetamine_settings->rainbowbox);

							ImGui::Checkbox(xorstr_("Skeleton ESP"), &amphetamine::amphetamine_settings->Skeleton);
							ImGui::ColorEdit4((xorstr_("Visible Skel")), (float*)&amphetamine::amphetamine_settings->SkelColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4((xorstr_("InVisible Skel")), (float*)&amphetamine::amphetamine_settings->invisibleSkelColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);


							const char* Skeletonstyle[2] = { "Simple", "Detailled" };

							ImGui::Combo(xorstr_("Skeleton"), &amphetamine::amphetamine_settings->Skeleton_idx, Skeletonstyle, 2);
							
							ImGui::Checkbox(xorstr_("Arrow Indicators"), &amphetamine::amphetamine_settings->oofindicators_players);
							ImGui::Checkbox(xorstr_("Weapon for arrow"), &amphetamine::amphetamine_settings->oofindicators_players_weapon);



							const char* HealthBartypes[5] = { "Up", "Down", "Left", "Right", "None" };
							ImGui::Combo(xorstr_("HealthBar"), &amphetamine::amphetamine_settings->HealthBar_idx, HealthBartypes, 5);
							ImGui::Checkbox(xorstr_("ArmorBar"), &amphetamine::amphetamine_settings->ArmorBar);

	
							ImGui::Checkbox(xorstr_("SnapLines"), &amphetamine::amphetamine_settings->Snapline);
							ImGui::ColorEdit4(xorstr_("SnapLines Color"), (float*)&amphetamine::amphetamine_settings->SnapLines_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);



							//ImGui::Checkbox(xorstr_("Static ESP"), &amphetamine::amphetamine_settings->StaticESP);
							ImGui::Checkbox(xorstr_("Player Name"), &amphetamine::amphetamine_settings->PlayerName);
							ImGui::ColorEdit4(xorstr_("Visible name"), (float*)&amphetamine::amphetamine_settings->Name_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4(xorstr_("InVisible name"), (float*)&amphetamine::amphetamine_settings->Name_Color_invisible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::Checkbox(xorstr_("Weapon Name"), &amphetamine::amphetamine_settings->Weapon);
							ImGui::Checkbox(xorstr_("Distance ESP"), &amphetamine::amphetamine_settings->DistanceESP);
							ImGui::ColorEdit4(xorstr_("Visible Distance"), (float*)&amphetamine::amphetamine_settings->Dist_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4(xorstr_("InVisible Distance"), (float*)&amphetamine::amphetamine_settings->invisibleDist_Color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

							//slider_int((("Font size")), &Settings::Visuals::fontsize, 4, 17, NULL);

							ImGui::SliderInt(xorstr_("Distance"), &amphetamine::amphetamine_settings->Distance, 1, 500);

							ImGui::Checkbox(xorstr_("Draw Flag In Car"), &amphetamine::amphetamine_settings->is_ped_is_any_vehicle);

							ImGui::Checkbox((xorstr_("Draw ESP DeadPlayer")), &amphetamine::amphetamine_settings->Draw_Dead);

							ImGui::Checkbox((xorstr_("Draw ESP NPC")), &amphetamine::amphetamine_settings->Draw_botvisuals);





						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild("", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 420));
						{
							ImVec2 pos = ImGui::GetWindowPos();
							ImDrawList* draw = ImGui::GetWindowDrawList();

							if (true)
							{
								ImGui::SetCursorPos(ImVec2(42, 15));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								draw->AddRectFilled(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 0.0f);
								draw->AddShadowRect(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 14.0f, ImVec2(0, 0), 0, 0);
							}
							if (amphetamine::amphetamine_settings->PlayerName)
							{
								ImGui::SetCursorPos(ImVec2(112, 0));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								draw->AddText(ImVec2(pos1.x, pos1.y), ImColor(255, 255, 255, 255), xorstr_("PLAYER NAME"));
							}
							if (amphetamine::amphetamine_settings->Skeleton)
							{
								ImGui::SetCursorPos(ImVec2(26, 74));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								ImVec2 child_size = ImGui::GetWindowSize();
								ImDrawList* draw_list = ImGui::GetWindowDrawList();
								//²±×Ó
								ImVec2 neck(122 + pos1.x, pos1.y);
								//×óÊÖ±Û
								ImVec2 epaule_droite(70 + pos1.x, 40 + pos1.y);
								ImVec2 coude_droite(45 + pos1.x, 100 + pos1.y);
								//ÓÒÊÖ±Û
								ImVec2 epaule_gauche(170 + pos1.x, 20 + pos1.y);
								ImVec2 coude_gauche(210 + pos1.x, 100 + pos1.y);
								//ÉíÌåÏß
								ImVec2 bassin(121 + pos1.x, 110 + pos1.y);
								//×óÍÈ
								ImVec2 anche_droite(80 + pos1.x, 207 + pos1.y);
								ImVec2 genoux_droite(80 + pos1.x, 258 + pos1.y);
								//ÓÒÍÈ
								ImVec2 anche_gauche(175 + pos1.x, 210 + pos1.y);
								ImVec2 genoux_gauche(175 + pos1.x, 261 + pos1.y);
								//»æÖÆÍ·²¿ÏßÖÁÉíÌåÏß
								draw_list->AddLine(neck, bassin, ImColor(255, 255, 255, 255), bonetk);
								//»æÖÆ×óÊÖ±Û
								draw_list->AddLine(neck, epaule_droite, ImColor(255, 255, 255, 255), bonetk);
								draw_list->AddLine(epaule_droite, coude_droite, ImColor(255, 255, 255, 255), bonetk);
								//»æÖÆÓÒÊÖ±Û
								draw_list->AddLine(neck, epaule_gauche, ImColor(255, 255, 255, 255), bonetk);
								draw_list->AddLine(epaule_gauche, coude_gauche, ImColor(255, 255, 255, 255), bonetk);
								//»æÖÆ×óÍÈ
								draw_list->AddLine(bassin, anche_droite, ImColor(255, 255, 255, 255), bonetk);
								draw_list->AddLine(anche_droite, genoux_droite, ImColor(255, 255, 255, 255), bonetk);
								//»æÖÆÓÒÍÈ
								draw_list->AddLine(bassin, anche_gauche, ImColor(255, 255, 255, 255), bonetk);
								draw_list->AddLine(anche_gauche, genoux_gauche, ImColor(255, 255, 255, 255), bonetk);
							}

						}
						ImGui::EndChild();
						ImGui::BeginChild(xorstr_("Settings"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 150));
						{
							ImGui::InputText("Font", custmomfontname, sizeof(custmomfontname));
							ImGui::Text("If the font is installed in the game, restart!");
							if (ImGui::Button(("Save Font"), ImVec2(100, 20))) {
								static TCHAR pathqwq[MAX_PATH];
								std::string savedCreditsPathqwq;
								SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, pathqwq);
								savedCreditsPathqwq = std::string(pathqwq) + ("\\AMTH.CSGO\\font.bin");
								std::ofstream out;
								out.open(savedCreditsPathqwq);
								out << custmomfontname;
								out.close();
								//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Font Saved!", "amphetamine.su" });
							}
							ImGui::SliderFloat(("TextSize"), &amphetamine::amphetamine_settings->textsize, 7.f, 14.f, "%00.00f");
							ImGui::Checkbox((xorstr_("Crosshair")), &amphetamine::amphetamine_settings->Crosshair);
							//	ImGui::SliderFloat("2D box thick", &boxtk, 1.f, 5.f, "%.1f");
							//	ImGui::SliderFloat("Head Size", &hdtk, 1.f, 10.f, "%.1f");
							//	ImGui::SliderFloat("Health Size", &hptk, 1.f, 5.f, "%.1f");
							//	ImGui::SliderFloat("Bone thick", &bonetk, 1.f, 5.f, "%.1f");
						}
						ImGui::EndChild();
						//ImGui::SetCursorPos(ImVec2(60 + tab_size, 440) + (s->ItemSpacing * 2));
						//ImGui::BeginChild("Others", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 130));
						//{
						//	ImGui::InputText("Font", custmomfontname, sizeof(custmomfontname));
						//	ImGui::Text("If the font is installed in the game, restart!");
						//	if (ImGui::Button(("Save Font"), ImVec2(100, 20))) {
						//		static TCHAR pathqwq[MAX_PATH];
						//		std::string savedCreditsPathqwq;
						//		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, pathqwq);
						//		savedCreditsPathqwq = std::string(pathqwq) + ("\\AMTH.CSGO\\font.bin");
						//		std::ofstream out;
						//		out.open(savedCreditsPathqwq);
						//		out << custmomfontname;
						//		out.close();
						//		//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Font Saved!", "amphetamine.su" });
						//	}
						//	ImGui::SliderFloat(("TextSize"), &amphetamine::amphetamine_settings->textsize, 7.f, 14.f, "%00.00f");
						//}
						//ImGui::EndChild();

					}
					ImGui::EndGroup();
					break;
				case 1:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
				//	ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("LocalPlayer"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							ImGui::Checkbox(xorstr_("LocalPlayer ESP"), &amphetamine::amphetamine_settings->enable_localplayeresp_LocalPlayer_esp);
							const char* boxtypes[3] = { "None", "Default", "Corner" };
							ImGui::Combo(xorstr_("Box ESP"), &amphetamine::amphetamine_settings->combo_box_LocalPlayer_esp, boxtypes, 3);
							ImGui::SliderFloat((xorstr_("Box Size")), &amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp, 0.5, 2, "%.1f");

							ImGui::Checkbox((xorstr_("Fill Box")), &amphetamine::amphetamine_settings->Filled_box_LocalPlayer_esp);
							ImGui::ColorEdit4(xorstr_("Box Color"), (float*)&amphetamine::amphetamine_settings->Box_Color_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::Checkbox((xorstr_("Rainbow Box")), &amphetamine::amphetamine_settings->rainbowbox_LocalPlayer_esp);

							ImGui::Checkbox((xorstr_("Skeleton ESP")), &amphetamine::amphetamine_settings->skeleton_LocalPlayer_esp);
							ImGui::ColorEdit4((xorstr_("Visible Skeleton")), (float*)&amphetamine::amphetamine_settings->SkelColor_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4((xorstr_("InVisible Skeleton")), (float*)&amphetamine::amphetamine_settings->invisibleSkelColor_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);


							const char* Skeletonstyle[2] = { "Simple", "Detailled" };
							ImGui::Combo(xorstr_("Skeleton"), &amphetamine::amphetamine_settings->combo_skeleton_LocalPlayer_esp, Skeletonstyle, 2);




							const char* HealthBartypes[5] = { "Right", "Left", "Down", "Up", "None" };
							ImGui::Combo(xorstr_("HealthBar"), &amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp, HealthBartypes, 5);
							ImGui::Checkbox((xorstr_("ArmorBar")), &amphetamine::amphetamine_settings->ArmorBar_LocalPlayer_esp);

							ImGui::Checkbox((xorstr_("Player Name")), &amphetamine::amphetamine_settings->name_LocalPlayer_esp);
							ImGui::ColorEdit4(xorstr_("Visible name"), (float*)&amphetamine::amphetamine_settings->Name_Color_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4(xorstr_("InVisible name"), (float*)&amphetamine::amphetamine_settings->Name_Color_invisible_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::Checkbox((xorstr_("Weapon Name")), &amphetamine::amphetamine_settings->weapon_LocalPlayer_esp);

							ImGui::Checkbox((xorstr_("Distance ESP")), &amphetamine::amphetamine_settings->distance_LocalPlayer_esp);
							ImGui::ColorEdit4(xorstr_("VisibleDistance"), (float*)&amphetamine::amphetamine_settings->Dist_Color_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::ColorEdit4(xorstr_("InVisibleDistance"), (float*)&amphetamine::amphetamine_settings->invisibleDist_Color_LocalPlayer_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);



						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild("", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 420));
						{
							ImVec2 pos = ImGui::GetWindowPos();
							ImDrawList* draw = ImGui::GetWindowDrawList();

							if (true)
							{
								ImGui::SetCursorPos(ImVec2(42, 15));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								draw->AddRectFilled(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 0.0f);
								draw->AddShadowRect(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 14.0f, ImVec2(0, 0), 0, 0);
							}
							if (true)
							{
								ImGui::SetCursorPos(ImVec2(112, 0));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								draw->AddText(ImVec2(pos1.x, pos1.y), ImColor(255, 255, 255, 255), xorstr_("LocalPlayer"));
							}


						}
						ImGui::EndChild();
						ImGui::BeginChild("Others", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 80));
						{
							//	ImGui::SliderFloat("2D box thick", &boxtk, 1.f, 5.f, "%.1f");
							//	ImGui::SliderFloat("Head Size", &hdtk, 1.f, 10.f, "%.1f");
							//	ImGui::SliderFloat("Health Size", &hptk, 1.f, 5.f, "%.1f");
							//	ImGui::SliderFloat("Bone thick", &bonetk, 1.f, 5.f, "%.1f");
						}
						ImGui::EndChild();
						//ImGui::SetCursorPos(ImVec2(60 + tab_size, 500) + (s->ItemSpacing * 2));
						//ImGui::BeginChild("Team", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 80));
						//{
						//	//ImGui::Checkbox("Filter teams", &Filterteams);
						//	//ImGui::Checkbox("Filter teams on map", &Filterteams_map);
						//}
						//ImGui::EndChild();
					}
					ImGui::EndGroup();
					break;
				case 2:

					break;
				case 3:

					break;
				case 4:

					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("Object"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							static bool removecfg = false;
							static auto should_update = true;
	/*					    if (should_update)
							{
								should_update = false;
								Visuals::object_in_list();
								for (auto& current : filesobjectlist)
									if (current.size() > 2)
										current.erase(current.size() - 3, 3);
							}*/
							ImGui::Checkbox(xorstr_("Enable"), &amphetamine::amphetamine_settings->object_esp);
							ImGui::Checkbox(xorstr_("Show all hash"), &amphetamine::amphetamine_settings->object_esp_all);
							ImGui::Checkbox(xorstr_("Show Distance "), &amphetamine::amphetamine_settings->object_dist_esp);

							//if (ImGui::Button(xorstr_("Refresh List"), ImVec2(260, 20)))
							//{
							//	Visuals::object_in_list();
							//	for (auto& current : filesobjectlist)
							//		if (current.size() > 2)
							//			current.erase(current.size() - 3, 3);
							//	//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Refreshed Object List", "amphetamine.su" });
							//}

	/*						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ListBoxConfigArray(xorstr_("##onjecylist"), &selected_objectlist, filesobjectlist, 7);
							ImGui::PopStyleVar();*/
							
							map<int32_t, string> object_list = Visuals::m_save_hash;
							//static DWORD selected_object = -1;
							map<int32_t, string>::iterator it;
							for (it = object_list.begin(); it != object_list.end(); it++) {


								int32_t dHash = it->first;
								string dName = it->second;
								char label[32];
								sprintf(label, "%d\n", dHash);
								if (CustomSelectable(label, selected_objectlist == dHash, ImGuiSelectableFlags_SpanAllColumns)) {
									selected_objectlist = dHash;
								}
								ImGui::NextColumn();
								ImGui::Text(dName.c_str());
								ImGui::NextColumn();

							}


							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ImGui::InputText(xorstr_("Object Hash"), Visuals::toAddHash, sizeof(Visuals::toAddHash), ImGuiInputTextFlags_CharsDecimal); //ImGuiInputTextFlags_CharsDecimal
							ImGui::PopStyleVar();


							static char object_name[64] = "\0";
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ImGui::InputText(xorstr_("Object name"), object_name, sizeof(object_name));
							ImGui::PopStyleVar();


							//DWORD toAddInt;
							//ImGui::Text(to_string(toAddInt).c_str());

							if (ImGui::Button(xorstr_("Add"), ImVec2(126, 20)))
							{
				/*				new_object_name = object_name;
								Visuals::add_object();*/


								int32_t toAddInt;
								string toAddNameString1(object_name);
								
								//sscanf_s(Visuals::toAddHash, "%x", &toAddInt);
								sscanf(Visuals::toAddHash, "%d", &toAddInt);



								it = object_list.find(toAddInt);
								if (it == object_list.end()) {

									object_list.insert(make_pair(toAddInt, toAddNameString1));
									Visuals::m_save_hash = object_list;
									//config::set("misc", "object_esp_object_list", object_list);
								}
							}
							ImGui::SameLine();
							if (removecfg == false) {
								if (ImGui::Button(xorstr_("Remove"), ImVec2(126, 20)))
								{
									removecfg = true;
								}
							}
							if (removecfg == true) {
								if (ImGui::Button(xorstr_("Remove?"), ImVec2(59, 20))) {
									//Visuals::remove_object();

									char label[32];
									sprintf(label, "Remove %d\n", selected_objectlist);
									//if (ImGui::Button(label, ImVec2(140, 0))) {
										it = object_list.find(selected_objectlist);
										if (it != object_list.end()) {

											object_list.erase(it);
											Visuals::m_save_hash = object_list;
											//config::set("misc", "object_esp_object_list", object_list);
											selected_objectlist = -1;
										}
									//}
									removecfg = false;
								}
								ImGui::SameLine();
								if (ImGui::Button(xorstr_("Cancel"), ImVec2(59, 20))) {
									removecfg = false;
								}
							}
							ImGui::ColorEdit4(xorstr_("Object Color"), (float*)&amphetamine::amphetamine_settings->object_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
							ImGui::SliderInt((xorstr_("Show Distance")), &amphetamine::amphetamine_settings->DistanceObject, 5, 600);

						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();
					ImGui::BeginGroup();
					{

						ImGui::BeginChild(xorstr_("Vehicle"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 520));
						{


							ImGui::Checkbox((xorstr_("Enable Vehicle ESP")), &amphetamine::amphetamine_settings->VehicleEsp);

							ImGui::Checkbox((xorstr_("Name Vehicle")), &amphetamine::amphetamine_settings->VehicleEsp_Name);

							ImGui::Checkbox((xorstr_("Distance Vehicle")), &amphetamine::amphetamine_settings->VehicleEsp_Distance);

							ImGui::ColorEdit4(xorstr_("Color Vehicle ESP"), (float*)&amphetamine::amphetamine_settings->Name_Color_vehicle, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);


							ImGui::SliderInt((xorstr_("Distance")), &amphetamine::amphetamine_settings->DistanceVehicle, 5, 400);


						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					break;
				case 5:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("LocalPlayer"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{


							ImGui::Checkbox((xorstr_("Radar Enable")), &amphetamine::amphetamine_settings->radarhack);
							ImGui::Checkbox((xorstr_("Draw weapons")), &amphetamine::amphetamine_settings->radarhack_weapons);
							ImGui::Combo(xorstr_("Radar style"), &amphetamine::amphetamine_settings->radar_type, ("circle\0arrow\0both\0"));
							ImGui::Checkbox(xorstr_("Customize"), &amphetamine::amphetamine_settings->custom_radar);
							ImGui::SliderFloat(xorstr_("Point size"), &amphetamine::amphetamine_settings->radar_point_size_proportion, 0.5f, 2.f);
							ImGui::SliderFloat(xorstr_("Proportion"), &amphetamine::amphetamine_settings->proportion, 1200.f, 4500.f);
							ImGui::SliderFloat(xorstr_("Radar size"), &amphetamine::amphetamine_settings->radar_range, 100.f, 300.f);
							ImGui::SliderFloat(xorstr_("Background alpha"), &amphetamine::amphetamine_settings->radar_bg_alpha, 0.f, 1.f);
							ImGui::Checkbox(xorstr_("Crossline"), &amphetamine::amphetamine_settings->show_radar_crossline);
							ImGui::ColorEdit4("CrossLineColor", reinterpret_cast<float*>(&amphetamine::amphetamine_settings->radar_crossline_color), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);


						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild( "", ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 420));
						{
							ImVec2 pos = ImGui::GetWindowPos();
							ImDrawList* draw = ImGui::GetWindowDrawList();

							//if (true)
							//{
							//	ImGui::SetCursorPos(ImVec2(42, 15));
							//	ImVec2 pos1 = ImGui::GetCursorScreenPos();
							//	draw->AddRectFilled(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 0.0f);
							//	draw->AddShadowRect(ImVec2(pos1.x, pos1.y), ImVec2(pos1.x + 1, pos1.y + 360), ImColor(24, 248, 24, 255), 14.0f, ImVec2(0, 0), 0, 0);
							//}
							if (true)
							{
								ImGui::SetCursorPos(ImVec2(112, 0));
								ImVec2 pos1 = ImGui::GetCursorScreenPos();
								draw->AddText(ImVec2(pos1.x, pos1.y), ImColor(255, 255, 255, 255), xorstr_("Radar preview"));
							}


						}
						ImGui::EndChild();
						ImGui::BeginChild(xorstr_("Others"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 80));
						{

						}
						ImGui::EndChild();
						//ImGui::SetCursorPos(ImVec2(60 + tab_size, 500) + (s->ItemSpacing * 2));
						//ImGui::BeginChild(xorstr_("Team"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 80));
						//{

						//}
						//ImGui::EndChild();
					}
					ImGui::EndGroup();




					//
					//									//slider_float((("Radar Size")), &RadarSett.size, 100, 300, NULL);
					//									///slider_float((("Radar Range")), &RadarSett.range, 40, 200, NULL);

					break;
				}

			}
			if (tabs == 3)
			{
				switch (select_tab_misc)
				{
				case 0:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{


						ImGui::BeginChild(xorstr_("LocalPlayer"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{



							ImGui::Checkbox(xorstr_("Super Jump"), &amphetamine::amphetamine_settings->SuperJump);

							if (ImGui::Checkbox(xorstr_("God Mode"), &amphetamine::amphetamine_settings->God_Mode))
							{
								if (amphetamine::amphetamine_settings->God_Mode)
								{
									rage::native_queue->native_emplace([&]
										{
											player::set_player_invincible(player::player_ped_id(), true);
										});
								}
								else {
									rage::native_queue->native_emplace([&]
										{
											player::set_player_invincible(player::player_ped_id(), false);
										}
									);
								}
							}
							ImGui::Checkbox(xorstr_("Alternative Godmode"), &amphetamine::amphetamine_settings->Semi_Godmod);
							ImGui::Checkbox(xorstr_("Alternative Godmode On Key"), &amphetamine::amphetamine_settings->Semi_Godmod_on_key);
							ImGui::Keybind(xorstr_("Bind Godmode"), &amphetamine::amphetamine_settings->Semi_Godmod_bind, true);

						


							ImGui::Checkbox(xorstr_("Auto Anim Stoper"), &amphetamine::amphetamine_settings->autoanimstoper);
							
							if (ImGui::Button(xorstr_("Skip Anim"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										brain::clear_ped_tasks_immediately(player::player_ped_id());
									});
							}
							ImGui::Checkbox(xorstr_("Skip Anim "), &amphetamine::amphetamine_settings->skipanimaka);
							ImGui::Keybind(xorstr_("Skip Anim Key"), &amphetamine::amphetamine_settings->skip_anim_bind, true);


							if (ImGui::Checkbox(xorstr_("Slow-mo"), &amphetamine::amphetamine_settings->slowmo))
							{
								if (amphetamine::amphetamine_settings->slowmo)
								{
									GAMEPLAY::SET_TIME_SCALE(0.2);
								}
								else {
									GAMEPLAY::SET_TIME_SCALE(1.0);
								}
							}


							ImGui::Checkbox(xorstr_("Time Changer"), &amphetamine::amphetamine_settings->customtime);
							ImGui::SliderInt(xorstr_("Time Value"), &amphetamine::amphetamine_settings->customtimesize, 0, 14);

							ImGui::Checkbox(xorstr_("Slide Run"), &amphetamine::amphetamine_settings->isSlideRun);

						//	ImGui::Checkbox(xorstr_("Super Punch"), &amphetamine::amphetamine_settings->player_superpunch);

							//checkbox("Anti Cuff", &amphetamine::amphetamine_settings->anticuff);

							ImGui::Checkbox(xorstr_("Always Ragdoll"), &amphetamine::amphetamine_settings->AlwaysRagdoll);

							ImGui::Checkbox(xorstr_("Thermal Vision"), &amphetamine::amphetamine_settings->thermalvision);

							ImGui::Checkbox(xorstr_("Night Vision"), &amphetamine::amphetamine_settings->nightmode);

							ImGui::Checkbox(xorstr_("Fov Changer"), &amphetamine::amphetamine_settings->EnableFovChange);
							ImGui::SliderFloat(xorstr_("Fov"), &amphetamine::amphetamine_settings->FovValue, 30, 200, "%0.01f");
							

						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild(xorstr_("Other"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{


							ImGui::Checkbox(xorstr_("No Fall"), &amphetamine::amphetamine_settings->nofall);

							ImGui::Checkbox(xorstr_("Ghost Mode"), &amphetamine::amphetamine_settings->ghostmode);


							ImGui::Checkbox(xorstr_("Fast Run"), &amphetamine::amphetamine_settings->fastrun);

							ImGui::Checkbox(xorstr_("Heal"), &amphetamine::amphetamine_settings->healcheck);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("Heal Key"), &amphetamine::amphetamine_settings->healkey, true);

							ImGui::Checkbox(xorstr_("Armor"), &amphetamine::amphetamine_settings->armorhcheck);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("Armor Key"), &amphetamine::amphetamine_settings->armorkey, true);


							if (ImGui::Checkbox(xorstr_("No Ragdoll"), &amphetamine::amphetamine_settings->NoRagDoll))
							{
								rage::native_queue->native_emplace([&]
									{
										auto player = player::player_ped_id();
										if (amphetamine::amphetamine_settings->NoRagDoll)
										{
											ped::set_ped_can_ragdoll(player, false); // SET_PED_CAN_RAGDOLL
										}
										else {
											ped::set_ped_can_ragdoll(player, true);
										}
									});
							}





							ImGui::Checkbox(xorstr_("Enable NoClip"), &amphetamine::amphetamine_settings->NoClip);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("NoClip Key  "), &amphetamine::amphetamine_settings->NoclipKey, true);
							ImGui::Checkbox(xorstr_("Noclip Anim"), &amphetamine::amphetamine_settings->NoClipSpeed_bool);
							ImGui::SliderFloat(xorstr_("Speed Noclip"), &amphetamine::amphetamine_settings->Speed, 0.1, 2, "%0.01f");

							if (ImGui::Button(xorstr_("Suicide"), ImVec2(90, 20)))
							{
								//Set_Health(0.0f);
								rage::native_queue->native_emplace([&]
									{
										ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0);
									});
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Reset Health"), ImVec2(90, 20)))
							{
								//Set_Health(200.0f);
								rage::native_queue->native_emplace([&]
									{
										ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 200);
									});
							}
							if (ImGui::Button(xorstr_("Armour 100%"), ImVec2(90, 20)))
							{
								//Set_Armor(100.0f);
								rage::native_queue->native_emplace([&]
									{
										PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 100);
									}
								);
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Armour 50%"), ImVec2(90, 20)))
							{
								//Set_Armor(50.0f);
								rage::native_queue->native_emplace([&]
									{
										PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 50);
									}
								);

							}

						}
						ImGui::EndChild();

					}
					ImGui::EndGroup();
					break;
				case 1:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{


						ImGui::BeginChild(xorstr_("Vehicle"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							ImGui::Checkbox(xorstr_("Flyhack Car"), &amphetamine::amphetamine_settings->Flyhackcar);



							ImGui::Checkbox(xorstr_("Engine Always on"), &amphetamine::amphetamine_settings->enginealwayson);

							//ImGui::Checkbox(xorstr_("Auto pilot"), &amphetamine::amphetamine_settings->auto_pilot);
							//if (ImGui::Button(xorstr_("auto pilot b"), ImVec2(120, 20)))
							//{
							//	rage::native_queue->native_emplace([] {
							//		bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
							//		if (is_in_vehicle) {
							//			type::any blip = native::ui::get_first_blip_info_id(8);
							//			if (ui::does_blip_exist(blip)) {
							//				auto tpos = native::ui::get_blip_coords(blip);
							//				//float z = 0.0f;


							//				Ped player = PLAYER::PLAYER_PED_ID();
							//				//Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
							//				Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(-1), false);
							//				AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(player, Veh, tpos.x, tpos.y, tpos.z, 40.f, 786603, 30.f);
							//			}
							//		}
							//		});
							//}

						
							

							ImGui::Checkbox(xorstr_("God Mode"), &amphetamine::amphetamine_settings->godmode_vehicle);
							//checkbox("Unlock Door Cars", &amphetamine::amphetamine_settings->UseLockedCars);


					
							ImGui::Checkbox(xorstr_("Repair Car On damage"), &amphetamine::amphetamine_settings->Fix_On_damage);
							ImGui::Checkbox(xorstr_("Speed Vehicle"), &amphetamine::amphetamine_settings->speedhackVehicle);
							ImGui::SliderInt(xorstr_("Speed"), &amphetamine::amphetamine_settings->speedmultiplier, 0, 100);




							ImGui::Checkbox(xorstr_("Click Flip"), &amphetamine::amphetamine_settings->clickflipvehicle);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("Flip Key"), &amphetamine::amphetamine_settings->clickflipvehiclekey, true);



							ImGui::Checkbox(xorstr_("Gravity Vehicle"), &amphetamine::amphetamine_settings->gravityhackVehicle);
							ImGui::SliderInt(xorstr_("Gravity"), &amphetamine::amphetamine_settings->gravitymultiplier, 0, 100);


						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild(xorstr_("Other"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{


							if (ImGui::Checkbox(xorstr_("No fall bike"), &amphetamine::amphetamine_settings->Nofallfrombike))
							{
								auto player = player::player_ped_id();
								if (amphetamine::amphetamine_settings->Nofallfrombike)
								{
									//SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE
									rage::native_queue->native_emplace([&]
										{
											ped::set_ped_can_be_knocked_off_vehicle(player::get_player_ped_script_index(player::player_id()), 1);
										}
									);
								}
								else {
									rage::native_queue->native_emplace([&]
										{
											ped::set_ped_can_be_knocked_off_vehicle(player::get_player_ped_script_index(player::player_id()), 0);
										}
									);
									//ped::set_ped_can_be_knocked_off_vehicle(player::get_player_ped_script_index(player::player_id()), 0);
								}
							}

							if (ImGui::Button(xorstr_("TP in previous car"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										auto player = player::player_ped_id();
										int vehID = ped::get_vehicle_ped_is_in(player, 1);
										ped::set_ped_into_vehicle(player, vehID, -1);
									});
							}
							if (ImGui::Button(xorstr_("Open All Doors"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										Entity Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), TRUE);

										if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
										{
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 0, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 1, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 2, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 3, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 4, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 5, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 6, true, false);
											VEHICLE::SET_VEHICLE_DOOR_OPEN(Vehicle, 7, true, false);
										}
									});
							}

							if (ImGui::Button(xorstr_("Close All Doors"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										Entity Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), TRUE);

										if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
										{
											VEHICLE::SET_VEHICLE_DOORS_SHUT(Vehicle, false);
										}
									});
							}

							//ImGui::Checkbox(xorstr_("Get Vehicle Plates"), &amphetamine::amphetamine_settings->getvehicllenumberplates);
							//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							//ImGui::InputText(xorstr_("Get Plate"), amphetamine::amphetamine_settings->plate_textgetveh, IM_ARRAYSIZE(amphetamine::amphetamine_settings->plate_textgetveh));
							//ImGui::PopStyleVar();
							if (ImGui::Button(xorstr_("Delete Car Doors"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										for (int DoorIndex = 0; DoorIndex <= 6; DoorIndex++)
											VEHICLE::SET_VEHICLE_DOOR_BROKEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), DoorIndex, 1);
									});
							}

							ImGui::Checkbox(xorstr_("Super Brakes"), &amphetamine::amphetamine_settings->superbrakes);

							ImGui::Checkbox(xorstr_("Auto Flip"), &amphetamine::amphetamine_settings->autoflipvehicle);

							ImGui::Checkbox(xorstr_("Drift Mode [shift]"), &amphetamine::amphetamine_settings->driftmode);



							ImGui::Checkbox(xorstr_("Vehicle InVisible"), &amphetamine::amphetamine_settings->vehicleinvisible);


							ImGui::Text(xorstr_("Plate Text"));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ImGui::InputText(xorstr_("Text"), amphetamine::amphetamine_settings->plate_text, IM_ARRAYSIZE(amphetamine::amphetamine_settings->plate_text));
							ImGui::PopStyleVar();
							if (ImGui::Button(xorstr_("Update Plate "), ImVec2(120, 20)))
							{
								amphetamine::amphetamine_settings->update_plate = true;
							}

							if (ImGui::Button(xorstr_("Repair Car"), ImVec2(90, 20)))
							{

								rage::native_queue->native_emplace([&]
									{
										hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
										if (LocalPlayer) {
											hk_Vehicle* SelectedPed = LocalPlayer->VehicleManager();
											if (SelectedPed) {
												vehicle::set_vehicle_deformation_fixed(Memory::pointer_to_handle((DWORD64)SelectedPed)); //SET_VEHICLE_DEFORMATION_FIXED
												vehicle::set_vehicle_engine_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 1000); //SET_VEHICLE_ENGINE_HEALTH
												vehicle::set_vehicle_body_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 1000.0); //set_vehicle_body_health
												vehicle::set_vehicle_dirt_level(Memory::pointer_to_handle((DWORD64)SelectedPed), 0);
												vehicle::set_vehicle_fixed(Memory::pointer_to_handle((DWORD64)SelectedPed));
											}
										}
									});

							}
							//ImGui::SameLine();
							if (ImGui::Button(xorstr_("Destroy Car"), ImVec2(90, 20)))
							{				
								//VehicleQ::Set_Health(0.0f, 0.0f, 0.0f);
								rage::native_queue->native_emplace([&]
									{
										hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
										if (LocalPlayer) {
											hk_Vehicle* SelectedPed = LocalPlayer->VehicleManager();
											if (SelectedPed) {
												vehicle::set_vehicle_engine_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 0); //SET_VEHICLE_ENGINE_HEALTH
												vehicle::set_vehicle_body_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 0); //set_vehicle_body_health
											}
										}
									});
							}

						}
						ImGui::EndChild();

					}
					ImGui::EndGroup();




					break;
				case 2:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("Exploit"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{


							ImGui::Checkbox(xorstr_("No Object Collision"), &amphetamine::amphetamine_settings->collision);
							ImGui::Checkbox(xorstr_("No Vehicle Collision"), &amphetamine::amphetamine_settings->vehicle_collision);
							ImGui::Checkbox(xorstr_("No Players Collision"), &amphetamine::amphetamine_settings->collision_players);

						

							//ImGui::Checkbox("Gravity Gun", &amphetamine::amphetamine_settings->gravitygun);

							/*ImGui::Checkbox(xorstr_("Debug Camera"), &amphetamine::amphetamine_settings->debugcamera);
							ImGui::SliderFloat(xorstr_("Cam Fov"), &amphetamine::amphetamine_settings->freecam_fov, 30, 180);
							ImGui::SliderFloat(xorstr_("Cam Speed"), &amphetamine::amphetamine_settings->freecam_speed, 0.1, 20);
						*/
							//ImGui::Checkbox(xorstr_("Click Warp"), &amphetamine::amphetamine_settings->clickwarp);
							

							//slider_float("Gravity Velocity", &amphetamine::amphetamine_settings->m_gravityvelocity, 0.25f, 10.f, "%0.01f");

							//ImGui::Checkbox(xorstr_("One Shot Kill"), &amphetamine::amphetamine_settings->one_shoot_kill);


							ImGui::Text(xorstr_("Click Warp bind + left mouse"));
							ImGui::Checkbox(xorstr_("Click Warp Vehicle"), &amphetamine::amphetamine_settings->clickwarpvehicle);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("Warp Key"), &amphetamine::amphetamine_settings->clickwarp_vehicle_int_hot_key, true);


							

							if (ImGui::Button(xorstr_("TP to waypoint"), ImVec2(120, 20)))
							{
								Vector3 pos;
								rage::native_queue->native_emplace([] {
									//set_ped_shoots_at_coord
									type::any entity;
									bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
									if (is_in_vehicle) {
										entity = ped::get_vehicle_ped_is_in(player::get_player_ped(-1), false);
									}
									else {
										entity = player::get_player_ped(-1);
									}
									type::any blip = native::ui::get_first_blip_info_id(8);
									if (ui::does_blip_exist(blip)) {
										auto tpos = native::ui::get_blip_coords(blip);
										float z = 0.0f;
										native::entity::set_entity_coords_no_offset(entity, tpos.x, tpos.y, tpos.z, true, true, true);

										if (native::gameplay::get_ground_z_for_3d_coord(tpos.x, tpos.y, tpos.z + 1000, &z, false)) {
											native::entity::set_entity_coords_no_offset(entity, tpos.x, tpos.y, z, true, true, true);
										}
									}
									});


								//rage::native_queue->native_emplace([&]
								//	{
								//		//tp_to_waypoint();

								//		int WaypointHandle = ui::get_first_blip_info_id(8); //GET_FIRST_BLIP_INFO_ID

								//		if (ui::does_blip_exist(WaypointHandle))
								//		{
								//			auto playerpiiid = player::player_ped_id();
								//			rage::padvec3 waypoint1 = ui::get_blip_coords(WaypointHandle);
								//			ped::set_ped_coords_keep_vehicle(playerpiiid, waypoint1.x, waypoint1.y, waypoint1.z); //SET_PED_COORDS_KEEP_VEHICLE
								//		}





								//	}
								//);
							}
							ImGui::Checkbox(xorstr_("TP to waypoint Key"), &amphetamine::amphetamine_settings->TpToWaypoint);
							//ImGui::SameLine();
							ImGui::Keybind(xorstr_("TP Key  "), &amphetamine::amphetamine_settings->TpToWaypointkey, true);

							//checkbox("skip anim", &amphetamine::amphetamine_settings->skipanimaka);

							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ListBoxConfigArray(xorstr_("##WeaponList"), &weapon_current, weapon_list, 7);
							ImGui::PopStyleVar();

							if (ImGui::Button(xorstr_("Give Weapon"), ImVec2(120, 20)))
							{
								rage::native_queue->native_emplace([&]
									{
										switch (weapon_current)
										{
										case 0: weapon::give_weapon_to_ped(player::player_ped_id(), 0x92A27487, (int)999, (bool)false, (bool)true); break;
										case 1: weapon::give_weapon_to_ped(player::player_ped_id(), 0x958A4A8F, (int)999, (bool)false, (bool)true); break;
										case 2: weapon::give_weapon_to_ped(player::player_ped_id(), 0x99B507EA, (int)999, (bool)false, (bool)true); break;
										case 3: weapon::give_weapon_to_ped(player::player_ped_id(), 0xDD5DF8D9, (int)999, (bool)false, (bool)true); break;

										case 4: weapon::give_weapon_to_ped(player::player_ped_id(), 0x1B06D571, (int)999, (bool)false, (bool)true); break;
										case 5: weapon::give_weapon_to_ped(player::player_ped_id(), 0xBFE256D4, (int)999, (bool)false, (bool)true); break;
										case 6: weapon::give_weapon_to_ped(player::player_ped_id(), 0x5EF9FEC4, (int)999, (bool)false, (bool)true); break;
										case 7: weapon::give_weapon_to_ped(player::player_ped_id(), 0x22D8FE39, (int)999, (bool)false, (bool)true); break;

										case 8: weapon::give_weapon_to_ped(player::player_ped_id(), 0x3656C8C1, (int)999, (bool)false, (bool)true); break;
										case 9: weapon::give_weapon_to_ped(player::player_ped_id(), 0x99AEEB3B, (int)999, (bool)false, (bool)true); break;
										case 10: weapon::give_weapon_to_ped(player::player_ped_id(), 0xBFD21232, (int)999, (bool)false, (bool)true); break;
										case 11: weapon::give_weapon_to_ped(player::player_ped_id(), 0x88374054, (int)999, (bool)false, (bool)true); break;
										case 12: weapon::give_weapon_to_ped(player::player_ped_id(), 0xD205520E, (int)999, (bool)false, (bool)true); break;
										case 13: weapon::give_weapon_to_ped(player::player_ped_id(), 0x83839C4, (int)999, (bool)false, (bool)true); break;
										case 14: weapon::give_weapon_to_ped(player::player_ped_id(), 0x47757124, (int)999, (bool)false, (bool)true); break;
										case 15: weapon::give_weapon_to_ped(player::player_ped_id(), 0xDC4DB296, (int)999, (bool)false, (bool)true); break;
										case 16: weapon::give_weapon_to_ped(player::player_ped_id(), 0xC1B3C3D1, (int)999, (bool)false, (bool)true); break;
										case 17: weapon::give_weapon_to_ped(player::player_ped_id(), 0xCB96392F, (int)999, (bool)false, (bool)true); break;
										case 18: weapon::give_weapon_to_ped(player::player_ped_id(), 0x97EA20B8, (int)999, (bool)false, (bool)true); break;
										case 19: weapon::give_weapon_to_ped(player::player_ped_id(), 0x13532244, (int)999, (bool)false, (bool)true); break;
										case 20: weapon::give_weapon_to_ped(player::player_ped_id(), 0x2BE6766B, (int)999, (bool)false, (bool)true); break;
										case 21: weapon::give_weapon_to_ped(player::player_ped_id(), 0x78A97CD0, (int)999, (bool)false, (bool)true); break;

										case 22: weapon::give_weapon_to_ped(player::player_ped_id(), 0xEFE7E2DF, (int)999, (bool)false, (bool)true); break;
										case 23: weapon::give_weapon_to_ped(player::player_ped_id(), 0xA3D4D34, (int)999, (bool)false, (bool)true); break;
										case 24: weapon::give_weapon_to_ped(player::player_ped_id(), 0xDB1AA450, (int)999, (bool)false, (bool)true); break;
										case 25: weapon::give_weapon_to_ped(player::player_ped_id(), 0xBD248B55, (int)999, (bool)false, (bool)true); break;
										case 26: weapon::give_weapon_to_ped(player::player_ped_id(), 0x1D073A89, (int)999, (bool)false, (bool)true); break;
										case 27: weapon::give_weapon_to_ped(player::player_ped_id(), 0x555AF99A, (int)999, (bool)false, (bool)true); break;
										case 28: weapon::give_weapon_to_ped(player::player_ped_id(), 0x7846A318, (int)999, (bool)false, (bool)true); break;
										case 29: weapon::give_weapon_to_ped(player::player_ped_id(), 0xE284C527, (int)999, (bool)false, (bool)true); break;
										case 30: weapon::give_weapon_to_ped(player::player_ped_id(), 0x9D61E50F, (int)999, (bool)false, (bool)true); break;
										case 31: weapon::give_weapon_to_ped(player::player_ped_id(), 0xA89CB99E, (int)999, (bool)false, (bool)true); break;
										case 32: weapon::give_weapon_to_ped(player::player_ped_id(), 0x3AABBBAA, (int)999, (bool)false, (bool)true); break;
										case 33: weapon::give_weapon_to_ped(player::player_ped_id(), 0xEF951FBB, (int)999, (bool)false, (bool)true); break;
										case 34: weapon::give_weapon_to_ped(player::player_ped_id(), 0x12E82D3D, (int)999, (bool)false, (bool)true); break;
										case 35: weapon::give_weapon_to_ped(player::player_ped_id(), 0xBFEFFF6D, (int)999, (bool)false, (bool)true); break;
										case 36: weapon::give_weapon_to_ped(player::player_ped_id(), 0x394F415C, (int)999, (bool)false, (bool)true); break;
										case 37: weapon::give_weapon_to_ped(player::player_ped_id(), 0x83BF0278, (int)999, (bool)false, (bool)true); break;
										case 38: weapon::give_weapon_to_ped(player::player_ped_id(), 0xFAD1F1C9, (int)999, (bool)false, (bool)true); break;
										case 39: weapon::give_weapon_to_ped(player::player_ped_id(), 0xAF113F99, (int)999, (bool)false, (bool)true); break;
										case 40: weapon::give_weapon_to_ped(player::player_ped_id(), 0xC0A3098D, (int)999, (bool)false, (bool)true); break;
										case 41: weapon::give_weapon_to_ped(player::player_ped_id(), 0x969C3D67, (int)999, (bool)false, (bool)true); break;
										case 42: weapon::give_weapon_to_ped(player::player_ped_id(), 0x7F229F94, (int)999, (bool)false, (bool)true); break;
										case 43: weapon::give_weapon_to_ped(player::player_ped_id(), 0x84D6FAFD, (int)999, (bool)false, (bool)true); break;
										case 44: weapon::give_weapon_to_ped(player::player_ped_id(), 0x624FE830, (int)999, (bool)false, (bool)true); break;
										case 45: weapon::give_weapon_to_ped(player::player_ped_id(), 0x9D07F764, (int)999, (bool)false, (bool)true); break;
										case 46: weapon::give_weapon_to_ped(player::player_ped_id(), 0x7FD62962, (int)999, (bool)false, (bool)true); break;
										case 47: weapon::give_weapon_to_ped(player::player_ped_id(), 0xDBBD7280, (int)999, (bool)false, (bool)true); break;
										case 48: weapon::give_weapon_to_ped(player::player_ped_id(), 0x61012683, (int)999, (bool)false, (bool)true); break;

										case 49: weapon::give_weapon_to_ped(player::player_ped_id(), 0x5FC3C11, (int)999, (bool)false, (bool)true); break;
										case 50: weapon::give_weapon_to_ped(player::player_ped_id(), 0xC472FE2, (int)999, (bool)false, (bool)true); break;
										case 51: weapon::give_weapon_to_ped(player::player_ped_id(), 0xA914799, (int)999, (bool)false, (bool)true); break;
										case 52: weapon::give_weapon_to_ped(player::player_ped_id(), 0xC734385A, (int)999, (bool)false, (bool)true); break;
										case 53: weapon::give_weapon_to_ped(player::player_ped_id(), 0x6A6C02E0, (int)999, (bool)false, (bool)true); break;
										case 54: weapon::give_weapon_to_ped(player::player_ped_id(), 0xB1CA77B1, (int)999, (bool)false, (bool)true); break;
										case 55: weapon::give_weapon_to_ped(player::player_ped_id(), 0xA284510B, (int)999, (bool)false, (bool)true); break;
										case 56: weapon::give_weapon_to_ped(player::player_ped_id(), 0x42BF8A85, (int)999, (bool)false, (bool)true); break;
										case 57: weapon::give_weapon_to_ped(player::player_ped_id(), 0x7F7497E5, (int)999, (bool)false, (bool)true); break;
										case 58: weapon::give_weapon_to_ped(player::player_ped_id(), 0x6D544C99, (int)999, (bool)false, (bool)true); break;

										case 59: weapon::give_weapon_to_ped(player::player_ped_id(), 0x63AB0442, (int)999, (bool)false, (bool)true); break;
										case 60: weapon::give_weapon_to_ped(player::player_ped_id(), 0x781FE4A, (int)999, (bool)false, (bool)true); break;
										case 61: weapon::give_weapon_to_ped(player::player_ped_id(), 0x93E220BD, (int)999, (bool)false, (bool)true); break;
										case 62: weapon::give_weapon_to_ped(player::player_ped_id(), 0xA0973D5E, (int)999, (bool)false, (bool)true); break;
										case 63: weapon::give_weapon_to_ped(player::player_ped_id(), 0xFDBC8A50, (int)999, (bool)false, (bool)true); break;
										case 64: weapon::give_weapon_to_ped(player::player_ped_id(), 0x497FACC3, (int)999, (bool)false, (bool)true); break;
										case 65: weapon::give_weapon_to_ped(player::player_ped_id(), 0x24B17070, (int)999, (bool)false, (bool)true); break;
										case 66: weapon::give_weapon_to_ped(player::player_ped_id(), 0x2C3731D9, (int)999, (bool)false, (bool)true); break;
										case 67: weapon::give_weapon_to_ped(player::player_ped_id(), 0xAB564B93, (int)999, (bool)false, (bool)true); break;
										case 68: weapon::give_weapon_to_ped(player::player_ped_id(), 0x787F0BB, (int)999, (bool)false, (bool)true); break;

										case 69: weapon::give_weapon_to_ped(player::player_ped_id(), 0xBA45E8B8, (int)999, (bool)false, (bool)true); break;
										case 70: weapon::give_weapon_to_ped(player::player_ped_id(), 0x23C9F95C, (int)999, (bool)false, (bool)true); break;

										case 71: weapon::give_weapon_to_ped(player::player_ped_id(), 0x34A67B97, (int)999, (bool)false, (bool)true); break;
										case 72: weapon::give_weapon_to_ped(player::player_ped_id(), 0x60EC506, (int)999, (bool)false, (bool)true); break;
										case 73: weapon::give_weapon_to_ped(player::player_ped_id(), 0xFBAB5776, (int)999, (bool)false, (bool)true); break;
										}
									}
								);
							}

						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild(xorstr_("Other"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{



						}
						ImGui::EndChild();

					}
					ImGui::EndGroup();

					break;
				case 3:
					ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
					//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
					ImGui::BeginGroup();
					{
						ImGui::BeginChild(xorstr_("Vehicle List"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
							if (!ReplayInterface)
								return;
							hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
							if (!VehicleInterface)
								return;

							if (ListBoxHeader("    ", ImVec2(140, 120)))
							{
								for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {

									hk_Vehicle* Peds = VehicleInterface->VehicleList()->Vehicle(i);
									if (!Peds) continue;
									auto playerName = Peds->VehicleModelInfo()->GetCharName();
									const char* c = playerName;
									const char* items[] = { c };

									std::string VehicleName = playerName;
									VehicleName.append(" ##");
									VehicleName.append(std::to_string(i));
									bool is_selected = (selectedVeh_index == i);
									if (CustomSelectable(VehicleName.c_str(), is_selected))
									{
										selectedVeh_index = i;
									}
								}
								ImGui::ListBoxFooter();
							}
							hk_Vehicle* SelectedPed = VehicleInterface->VehicleList()->Vehicle(selectedVeh_index);




							if (SelectedPed->GetCoordinate().x != 0)
							{
								if (ImGui::Button(xorstr_("Destroy car "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											vehicle::set_vehicle_engine_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 0); //SET_VEHICLE_ENGINE_HEALTH
											vehicle::set_vehicle_body_health(Memory::pointer_to_handle((DWORD64)SelectedPed), 0); //set_vehicle_body_health
										});
								}
								if (ImGui::Button(xorstr_("Lock vehicle "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											vehicle::set_vehicle_doors_locked(Memory::pointer_to_handle((DWORD64)SelectedPed), 4);
										});
								}
								if (ImGui::Button(xorstr_("TP To Him "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											ped::set_ped_coords_keep_vehicle(player, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z); //SET_PED_COORDS_KEEP_VEHICLE
										});
								}
								if (ImGui::Button(xorstr_("Repair "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Memory::pointer_to_handle((DWORD64)SelectedPed)); //SET_VEHICLE_DEFORMATION_FIXED
											VEHICLE::SET_VEHICLE_ENGINE_HEALTH(Memory::pointer_to_handle((DWORD64)SelectedPed), 1000); //SET_VEHICLE_ENGINE_HEALTH
											VEHICLE::SET_VEHICLE_BODY_HEALTH(Memory::pointer_to_handle((DWORD64)SelectedPed), 1000.0); //set_vehicle_body_health
											VEHICLE::SET_VEHICLE_DIRT_LEVEL(Memory::pointer_to_handle((DWORD64)SelectedPed), 0);
											VEHICLE::SET_VEHICLE_FIXED(Memory::pointer_to_handle((DWORD64)SelectedPed));
										});
								}
								if (ImGui::Button(xorstr_("Warp "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto vehicle = Memory::pointer_to_handle((DWORD64)SelectedPed);
											if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), -1)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), -1);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 0)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 0);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 1)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 1);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 2)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 2);
											}
										});
								}
								if (ImGui::Button(xorstr_("Shoot bullet   "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto WeaponHash = weapon::get_selected_ped_weapon(player);
											auto WeaponDamage = weapon::_0x3133b907d8b32053(0xBFEFFF6D, NULL);
											gameplay::shoot_single_bullet_between_coords(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, (int)WeaponDamage, false, 0xBFEFFF6D, player, true, false, 3.f);
										}
									);
								}
							}

						}
						ImGui::EndChild();
					}
					ImGui::EndGroup();
					ImGui::SameLine();

					ImGui::BeginGroup();
					{

						ImGui::BeginChild(xorstr_("Player List"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 590));
						{

							hk_World* World = (hk_World*)*(uint64_t*)(Memory::World);
							if (!World)
								return;
							hk_Ped* LocalPlayer = World->LocalPlayer();
							if (!LocalPlayer)
								return;
							hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
							if (!ReplayInterface)
								return;

							hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
							if (!PedInterface)
								return;
							if (ListBoxHeader(" ", ImVec2(140, 160)))
							{
								for (int i = 0; i < PedInterface->PedMaximum(); i++) {

									hk_Ped* Peds = PedInterface->PedList()->Ped(i);
									if (!Peds) continue;
									int PlayerID = Memory::pointer_to_handle((DWORD64)Peds);
									auto playerName = std::to_string((DWORD64)Peds);
									const char* c = playerName.c_str();
									const char* items[] = { c };
									//if (playerName == "**Invalid**")
									//{
									//	//if (!Settings::misc::PedList)
									//		//continue;
									//	playerName = "Peds ##" + std::to_string(i);

									//}

									bool is_selected = (selected_index == i);
									if (CustomSelectable(playerName.c_str(), is_selected))
									{

										selected_index = i;

									}
								}
								ImGui::ListBoxFooter();
							}
							hk_Ped* SelectedPed = PedInterface->PedList()->Ped(selected_index);
							if (SelectedPed->GetCoordinate().x != 0)
							{
								if (ImGui::Button(xorstr_("Destroy car  "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto WeaponDamage = weapon::_0x3133b907d8b32053(0xBFEFFF6D, NULL);
											gameplay::shoot_single_bullet_between_coords(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, (int)10000, false, (int32_t)0xBFEFFF6D, player, true, false, 3.f);
										});
								}
								if (ImGui::Button(xorstr_("Lock vehicle  "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto vehicle = ped::get_vehicle_ped_is_in(Memory::pointer_to_handle((DWORD64)SelectedPed), false);
											vehicle::set_vehicle_doors_locked(vehicle, 4); //SET_VEHICLE_DOORS_LOCKED
										});
								}
								if (ImGui::Button(xorstr_("HandCuff "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											ped::set_enable_handcuffs(Memory::pointer_to_handle((DWORD64)SelectedPed), true);
										});
								}
								if (ImGui::Button(xorstr_("Clone pedestrian"), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											ped::clone_ped_to_target(Memory::pointer_to_handle((DWORD64)SelectedPed), player);
										});
								}
								if (ImGui::Button(xorstr_("Taze player"), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto WeaponHash = weapon::get_selected_ped_weapon(player);
											auto WeaponDamage = weapon::_0x3133b907d8b32053(0x8BB05FD7, NULL);
											gameplay::shoot_single_bullet_between_coords(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, (int)WeaponDamage, false, 0x8BB05FD7, player, true, false, 3.f);
										});
								}
								if (ImGui::Button(xorstr_("TP To Him  "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											if (SelectedPed != LocalPlayer)
											{
												auto player = player::player_ped_id();
												ped::set_ped_coords_keep_vehicle(player, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z); //SET_PED_COORDS_KEEP_VEHICLE
											}
										}
									);
								}
								if (ImGui::Button(xorstr_("Spectate"), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											network::network_set_in_spectator_mode(true, player::get_player_ped_script_index(selected_index)); //NETWORK_SET_IN_SPECTATOR_MODE
										});
								}
								//ImGui::SameLine();
								if (ImGui::Button(xorstr_("Off Spectate"), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											network::network_set_in_spectator_mode(false, player::get_player_ped_script_index(selected_index));
										});
								}
								if (ImGui::Button(xorstr_("Warp  "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto vehicle = ped::get_vehicle_ped_is_in(Memory::pointer_to_handle((DWORD64)SelectedPed), false);
											if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), -1)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), -1);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 0)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 0);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 1)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 1);
											}
											else if (vehicle::is_vehicle_seat_free(Memory::pointer_to_handle((DWORD64)SelectedPed), 2)) {
												ped::set_ped_into_vehicle(player, Memory::pointer_to_handle((DWORD64)SelectedPed), 2);
											}
										});
								}
								if (ImGui::Button(xorstr_("Shoot bullet  "), ImVec2(120, 20)))
								{
									rage::native_queue->native_emplace([&]
										{
											auto player = player::player_ped_id();
											auto WeaponHash = weapon::get_selected_ped_weapon(player);
											auto WeaponDamage = weapon::_0x3133b907d8b32053(0xBFEFFF6D, NULL);
											gameplay::shoot_single_bullet_between_coords(SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z + 2, SelectedPed->GetCoordinate().x, SelectedPed->GetCoordinate().y, SelectedPed->GetCoordinate().z - 1, (int)WeaponDamage, false, 0xBFEFFF6D, player, true, false, 3.f);
										});
								}

								//int PlayerID = FiveM::pointer_to_handle((DWORD64)SelectedPed);

								//if (ImGui::Button("Print Id"))
								//{
								//	std::cout << FiveM::pointer_to_handle((DWORD64)SelectedPed);
								//	std::cout << " + ";
								//	std::cout << std::to_string(FiveM::pointer_to_handle((DWORD64)SelectedPed));
								//}

								//auto it = std::find(FiveM::Friend.begin(), FiveM::Friend.end(), GetPlayerNameNew((DWORD64)SelectedPed));
								//if (it != FiveM::Friend.end())
								//{
								//	if (ImGui::Button("Remove Friend"))
								//	{
								//		//	auto it = std::find(FiveM::Friend.begin(), FiveM::Friend.end(), (DWORD64)SelectedPed);
								//		int index = it - FiveM::Friend.begin();
								//		FiveM::Friend.erase(FiveM::Friend.begin() + index);
								//	}
								//}
								//else
								//{
								//	if (ImGui::Button("Add Friend"))
								//	{
								//		FiveM::Friend.push_back(GetPlayerNameNew((DWORD64)SelectedPed));
								//	}
								//}

								std::string healthtoshow = xorstr_("Health: ") + std::to_string(SelectedPed->GetHealth());
								ImGui::Text(healthtoshow.c_str());

							}
						}
						ImGui::EndChild();

					}
					ImGui::EndGroup();



					break;
				case 4:


					break;
				}

			}
			if (tabs == 4)
			{
				for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i)
				{
					TextEditor::Identifier id;
					id.mDeclaration = ppvalues[i];
					lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
				}
				for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
				{
					TextEditor::Identifier id;
					id.mDeclaration = std::string(idecls[i]);
					lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
				}
				if (fsdjgnsifjdgjsdfjgjksdfgkj == true) {
					editor.SetLanguageDefinition(lang);
					///////////////////////////////////////
					{
						std::ifstream t(fileToEdit.c_str());
						if (t.good())
						{
							std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
							editor.SetText(str);
						}
					}
					////////////////////////////////////////
					fsdjgnsifjdgjsdfjgjksdfgkj = false;
				}
				if (imguieditscriptlua == 1 && loaded_script == false) {
					auto cpos = editor.GetCursorPosition();
					ImGui::Begin(xorstr_("Lua edit"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_HorizontalScrollbar);
					ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
					ImGui::BeginChild( "    ", ImVec2(800, 600));
					{
						ImGui::SetCursorPos(ImVec2(10, 10));
						ImGui::BeginGroup();
						{
							if (ImGui::Button(xorstr_("Save"), ImVec2(40, 20)))
							{
								auto textToSave = editor.GetText();
								std::string savedCreditsPathqwq;
								savedCreditsPathqwq = fileToEdit;
								std::ofstream out;
								out.open(savedCreditsPathqwq);
								out << textToSave;
								out.close();
								//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Script Saved", "amphetamine.su" });
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Quit"), ImVec2(40, 20)))
							{
								imguieditscriptlua = 0;
							}

							ImGui::SameLine();
							ImGui::Text(xorstr_("  Copy : Ctrl-C "));
							ImGui::SameLine();
							ImGui::Text(xorstr_("Paste : Ctrl-V "));



							ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
								editor.IsOverwrite() ? "Ovr" : "Ins",
								editor.CanUndo() ? "*" : " ",
								editor.GetLanguageDefinition().mName.c_str(), fileToEdit.c_str());

							editor.Render("Lua edit");
						}
						ImGui::EndGroup();
					}

					ImGui::EndChild();
					ImGui::End();

				}

				static bool savwecfg = false;
				static bool removecfg = false;
				static auto should_update = true;
				//.//	int selected_config;
				///	int selected_script;
				ImGui::SetCursorPos(ImVec2(60 + tab_size, -10) + (s->ItemSpacing * 2));
				//ImGui::SetCursorPos(ImVec2(60 + tab_size, 60) + (s->ItemSpacing * 2));
				ImGui::BeginGroup();
				{
					ImGui::BeginChild( xorstr_("Configs"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 420));
					{
						if (should_update)
						{
							should_update = false;
							cfg_manager->config_files();
							files = cfg_manager->files;
						}
						if (ImGui::Button(xorstr_("Refresh configs"), ImVec2(260, 20)))
						{
							cfg_manager->config_files();
							files = cfg_manager->files;
							// ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Refreshed Config", "amphetamine.su" });
						}
						{
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ListBoxConfigArray(xorstr_("##CONFIGS"), &selected_config, files, 7);
							ImGui::PopStyleVar();
						}

						static char config_name[64] = "\0";
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
						ImGui::InputText(xorstr_("Config Name"), config_name, sizeof(config_name));
						ImGui::PopStyleVar();
						if (ImGui::Button(xorstr_("Create Config"), ImVec2(126, 20)))
						{
							new_config_name = config_name;
							add_config();
						}
						ImGui::SameLine();
						if (removecfg == false) {
							if (ImGui::Button(xorstr_("Remove Config"), ImVec2(126, 20)))
							{
								removecfg = true;
							}
						}
						if (removecfg == true) {
							if (ImGui::Button(xorstr_("Remove?"), ImVec2(59, 20))) {
								remove_config();
								removecfg = false;
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Cancel "), ImVec2(59, 20))) {
								removecfg = false;
							}
						}


						if (savwecfg == false) {
							if (ImGui::Button(xorstr_("Save Config"), ImVec2(126, 20)))
							{
								savwecfg = true;
							}
						}
						if (savwecfg == true) {
							if (ImGui::Button(xorstr_("Save?"), ImVec2(59, 20))) {
								save_config();
								savwecfg = false;
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Cancel"), ImVec2(59, 20))) {
								savwecfg = false;
							}
						}


						ImGui::SameLine();
						if (ImGui::Button(xorstr_("Load Config"), ImVec2(126, 20)))
						{
							load_config();
						}

						static char shared_key[64] = "\0";
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
						ImGui::InputText(xorstr_("Shared Key"), shared_key, sizeof(shared_key));
						ImGui::PopStyleVar();
						if (ImGui::Button(xorstr_("Add Shared"), ImVec2(126, 20)))
						{
							if (shared_key != "\0") {
								amphetamine::amphetamine_settings->shared_cfg_add(shared_key);;
								cfg_manager->config_files();
								selected_config = cfg_manager->files.size() - 1;
								files = cfg_manager->files;
							}
						}
						ImGui::SameLine();
						if (ImGui::Button(xorstr_("Copy Shared code"), ImVec2(126, 20)))
						{
							amphetamine::amphetamine_settings->copy_shared_code_cfg(cfg_manager->files.at(selected_config));
						}






						/*if (should_update)
						{
							should_update = false;
							cfg_manager->config_files();
							files = cfg_manager->files;
							for (auto& current : files)
								if (current.size() > 2)
									current.erase(current.size() - 3, 3);
						}
						if (ImGui::Button(xorstr_("Refresh configs"), ImVec2(260, 20)))
						{
							cfg_manager->config_files();
							files = cfg_manager->files;
							for (auto& current : files)
								if (current.size() > 2)
									current.erase(current.size() - 3, 3);
						}
						{
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
							ListBoxConfigArray(xorstr_("##CONFIGS"), &selected_config, files, 7);
							ImGui::PopStyleVar();
						}

						static char config_name[64] = "\0";
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
						ImGui::InputText(xorstr_("Config Name"), config_name, sizeof(config_name));
						ImGui::PopStyleVar();
						if (ImGui::Button(xorstr_("Create Config"), ImVec2(260, 20)))
						{
							new_config_name = config_name;
							add_config();
						}
						if (savwecfg == false) {
							if (ImGui::Button(xorstr_("Save Config"), ImVec2(126, 20)))
							{
								savwecfg = true;
							}
						}
						if (savwecfg == true) {
							if (ImGui::Button(xorstr_("Save?"), ImVec2(59, 20))) {
								save_config();
								savwecfg = false;
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Cancel"), ImVec2(59, 20))) {
								savwecfg = false;
							}
						}


						ImGui::SameLine();
						if (ImGui::Button(xorstr_("Load Config"), ImVec2(126, 20)))
						{
							load_config();
						}
						if (removecfg == false) {
							if (ImGui::Button(xorstr_("Remove Config"), ImVec2(260, 20)))
							{
								removecfg = true;
							}
						}
						if (removecfg == true) {
							if (ImGui::Button(xorstr_("Remove?"), ImVec2(126, 20))) {
								remove_config();
								removecfg = false;
							}
							ImGui::SameLine();
							if (ImGui::Button(xorstr_("Cancel "), ImVec2(126, 20))) {
								removecfg = false;
							}
						}

						if (ImGui::Button(xorstr_("OpenFolder"), ImVec2(260, 20)))
						{
							std::string folder;

							auto get_dir = [&folder]() -> void
								{
									static TCHAR path[MAX_PATH];

									if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
										folder = std::string(path) + xorstr_("\\AMTH.CSGO\\");

									CreateDirectory(folder.c_str(), NULL);
								};

							get_dir();
							ShellExecute(NULL, xorstr_("open"), folder.c_str(), NULL, NULL, SW_SHOWNORMAL);
						}*/

					}

					ImGui::EndChild();
				}
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();
				{
					ImGui::BeginChild(xorstr_("Scripts"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 420));
					{
						static auto should_update = true;
						if (should_update)
						{
							should_update = false;
							scripts = c_lua::get().scripts;

							for (auto& current : scripts)
							{
								if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
									current.erase(current.size() - 5, 5);
								else if (current.size() >= 4)
									current.erase(current.size() - 4, 4);
							}
						}
						if (ImGui::Button(xorstr_("Refresh scripts"), ImVec2(260, 20)))
						{
							c_lua::get().refresh_scripts();
							scripts = c_lua::get().scripts;

							if (selected_script >= scripts.size())
								selected_script = scripts.size() - 1; //-V103

							for (auto& current : scripts)
							{
								if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
									current.erase(current.size() - 5, 5);
								else if (current.size() >= 4)
									current.erase(current.size() - 4, 4);
							}
							//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, "Refreshed Scripts", "amphetamine.su" });
						}

						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
						if (scripts.empty())
							ListBoxConfigArray(crypt_str("##LUAS"), &selected_script, scripts, 10);
						else
						{
							auto backup_scripts = scripts;

							for (auto& script : scripts)
							{
								auto script_id = c_lua::get().get_script_id(script + crypt_str(".lua"));

								if (script_id == -1)
									continue;

								if (c_lua::get().loaded.at(script_id))
									scripts.at(script_id) += crypt_str(" [+]");
							}

							ListBoxConfigArray(("##LUAS"), &selected_script, scripts, 10);
							scripts = std::move(backup_scripts);

						}
						ImGui::PopStyleVar();

						if (ImGui::Button(xorstr_("Load Script"), ImVec2(126, 20)))
						{
							c_lua::get().load_script(selected_script);
							c_lua::get().refresh_scripts();

							scripts = c_lua::get().scripts;

							if (selected_script >= scripts.size())
								selected_script = scripts.size() - 1; //-V103



							for (auto& current : scripts)
							{
								if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
									current.erase(current.size() - 5, 5);
								else if (current.size() >= 4)
									current.erase(current.size() - 4, 4);
							}
						}
						ImGui::SameLine();
						if (ImGui::Button(xorstr_("Unload script"), ImVec2(126, 20)))
						{

							c_lua::get().unload_script(selected_script);
							c_lua::get().refresh_scripts();

							scripts = c_lua::get().scripts;

							if (selected_script >= scripts.size())
								selected_script = scripts.size() - 1; //-V103

							for (auto& current : scripts)
							{
								if (current.size() >= 5 && current.at(current.size() - 1) == 'c')
									current.erase(current.size() - 5, 5);
								else if (current.size() >= 4)
									current.erase(current.size() - 4, 4);
							}
						}
						if (ImGui::Button(xorstr_("OpenFolder"), ImVec2(126, 20)))
						{
							std::string folder;

							auto get_dir = [&folder]() -> void
								{
									static TCHAR path[MAX_PATH];

									if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
										folder = std::string(path) + crypt_str("\\AMTH.CSGO\\Lua\\");

									CreateDirectory(folder.c_str(), NULL);
								};

							get_dir();
							ShellExecute(NULL, crypt_str("open"), folder.c_str(), NULL, NULL, SW_SHOWNORMAL);
						}
						ImGui::SameLine();
						if (ImGui::Button(xorstr_("Edit script"), ImVec2(126, 20))) {
							if (loaded_script == false) {
								auto path = c_lua::get().get_script_path(selected_script);

								if (path == crypt_str(""))
									return;

								fileToEdit = path;
								fsdjgnsifjdgjsdfjgjksdfgkj = true;


								imguieditscriptlua = 1;

							}
							else {
								// ImGui::InsertNotification({ ImGuiToastType_Error, 4000, "Unload scripts pls", "amphetamine.su" });
							}
						}

					}

					ImGui::EndChild();
				}
				ImGui::BeginChild( xorstr_("Settings Menu"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 150));
				{
					ImGui::Checkbox(xorstr_("Particles"), &popit);
					ImGui::ColorEdit4(xorstr_("Menu Color"), (float*)&c::menu_sett::menu_color_swither, picker_flags);

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(60 + tab_size, 430) + (s->ItemSpacing * 2));
				ImGui::BeginChild( xorstr_("Other"), ImVec2((c::bg::size.x - 60 - s->ItemSpacing.x * 4) / 2, 150));
				{
					ImGui::Keybind(xorstr_("Menu Key"), &amphetamine::amphetamine_settings->key_menu_global, true);
					
					if (ImGui::Button(xorstr_("Unload Cheat"), ImVec2(260, 20))) {
						global::Panicnoclear = true;
					}
					if (ImGui::Button(xorstr_("Unload + Clear Cheat"), ImVec2(260, 20))) {
						global::Panic = true;
					}
				}
				ImGui::EndChild();


				ImGui::EndGroup();


				auto previous_check_box = false;
				for (auto& current : c_lua::get().scripts)
				{
					auto& items = c_lua::get().items.at(c_lua::get().get_script_id(current));

					for (auto& item : items)
					{
						std::string item_name;

						auto first_point = false;
						auto item_str = false;

						for (auto& c : item.first)
						{
							if (c == '.')
							{
								if (first_point)
								{
									item_str = true;
									continue;
								}
								else
									first_point = true;
							}

							if (item_str)
								item_name.push_back(c);
						}

						switch (item.second.type)
						{
						case NEXT_LINE:
							previous_check_box = false;
							break;
						case CHECK_BOX:
							luawindow = true;
							break;
						case COMBO_BOX:
							previous_check_box = false;
							luawindow = true;
							break;
						case SLIDER_INT:
							luawindow = true;
							break;
						case SLIDER_FLOAT:
							luawindow = true;
							break;
						case COLOR_PICKER:
							luawindow = true;
							break;
						}
					}
				}
				if (luawindow == true)
				{
					ImGui::SetNextWindowSize({ 420, 820 });
					{
						ImGui::Begin(xorstr_("Scripts"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
						//ImGui::Begin("Scripts", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
						{
							ImGui::BeginGroup();
							{
								ImGui::SetCursorPos({ 10, 30 });
								ImGui::BeginChild( xorstr_("Scripts "), ImVec2(400, 800));
								{
									ImGui::SetCursorPos({ 10, 17 });
									ImGui::BeginGroup();
									{
										auto previous_check_box = false;

										for (auto& current : c_lua::get().scripts)
										{
											auto& items = c_lua::get().items.at(c_lua::get().get_script_id(current));

											for (auto& item : items)
											{
												std::string item_name;

												auto first_point = false;
												auto item_str = false;

												for (auto& c : item.first)
												{
													if (c == '.')
													{
														if (first_point)
														{
															item_str = true;
															continue;
														}
														else
															first_point = true;
													}

													if (item_str)
														item_name.push_back(c);
												}

												switch (item.second.type)
												{
												case NEXT_LINE:
													previous_check_box = false;
													break;
												case CHECK_BOX:
													previous_check_box = true;

													ImGui::Checkbox(item_name.c_str(), &item.second.check_box_value);

													break;
												case COMBO_BOX:
													previous_check_box = false;
													//SingleSelect(item_name.c_str(), &item.second.combo_box_value, [](void* data, int idx, const char** out_text)
													//	{
													//		auto labels = (std::vector <std::string>*)data;
													//		*out_text = labels->at(idx).c_str(); //-V106
													//		return true;
													//	},
													//	item.second.combo_box_labels.size());
													break;
												case SLIDER_INT:
													previous_check_box = false;

													ImGui::SliderInt(item_name.c_str(), &item.second.slider_int_value, item.second.slider_int_min, item.second.slider_int_max);

													break;
												case SLIDER_FLOAT:
													previous_check_box = false;

													ImGui::SliderFloat(item_name.c_str(), &item.second.slider_float_value, item.second.slider_float_min, item.second.slider_float_max, "%0.01f");

													break;
												case COLOR_PICKER:
													/*						if (previous_check_box)
																				previous_check_box = false;
																			else
																				ImGui::Text((item_name + ' ').c_str());


																			ColorEdit4Custom((crypt_str("##") + item_name).c_str(), &item.second.color_picker_value, ImGuiWindowFlags_NoTitleBar, 44);
																			break;*/
																			/*	if (previous_check_box)
																					previous_check_box = false;
																				else
																					ImGui::Text((item_name + ' ').c_str());

																				ImGui::ColorEdit4(("##" + item_name).c_str(), &item.second.color_picker_value, 44);
																				ColorEdit4Custom((crypt_str("##") + item_name).c_str(), &item.second.color_picker_value, 44);*/
													break;
												case HOTKEY:
													previous_check_box = false;
													//Hotkey(item_name.c_str(), &item.second.hotkey_value);
													break;
												}
											}
										}

									}
									ImGui::EndGroup();
								}
								ImGui::EndChild();
							}
							ImGui::EndGroup();
						}
						ImGui::End();
					}
				}

			}


			ImGui::PopStyleVar();
		}


		ImGui::End();
	}
}
