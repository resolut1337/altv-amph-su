
#define IMGUI_DEFINE_MATH_OPERATORS


bool sentmessage;
char messagechat[256] = { 0 };
std::string chatbox;
std::string message_to_send;
static int selected_tab = 0;
char requestchatmessage[999999];
std::string получениедатыподписки = "Active";

static float switch_alpha[3], open_alpha = 0;
bool popit = true;

#define IM_USE using namespace ImGui; 
#include <sstream>
#include <iostream>
#include <map>

std::map<ImGuiID, ImVec4> hover_color;
IMGUI_API bool          CustomSelectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
bool CustomSelectable(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns) // FIXME-OPT: Avoid if vertically clipped.
		ImGui::PushColumnsBackground();

	// Submit label or explicit size to ItemSize(), whereas ItemAdd() will submit a larger/spanning rectangle.
	ImGuiID id = window->GetID(label);
	ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size(size_arg.x != 0.0f ? size_arg.x : label_size.x, size_arg.y != 0.0f ? size_arg.y : label_size.y);
	ImVec2 pos = window->DC.CursorPos;
	pos.y += window->DC.CurrLineTextBaseOffset;
	ImGui::ItemSize(size, 0.0f);

	// Fill horizontal space
	const float min_x = (flags & ImGuiSelectableFlags_SpanAllColumns) ? window->ContentRegionRect.Min.x : pos.x;
	const float max_x = (flags & ImGuiSelectableFlags_SpanAllColumns) ? window->ContentRegionRect.Max.x : ImGui::GetContentRegionMaxAbs().x;
	if (size_arg.x == 0.0f || (flags & ImGuiSelectableFlags_SpanAvailWidth))
		size.x = ImMax(label_size.x, max_x - min_x);

	// Text stays at the submission position, but bounding box may be extended on both sides
	const ImVec2 text_min = pos;
	const ImVec2 text_max(min_x + size.x, pos.y + size.y);

	// Selectables are meant to be tightly packed together with no click-gap, so we extend their box to cover spacing between selectable.
	ImRect bb_enlarged(min_x, pos.y, text_max.x, text_max.y);
	const float spacing_x = style.ItemSpacing.x;
	const float spacing_y = style.ItemSpacing.y;
	const float spacing_L = IM_FLOOR(spacing_x * 0.50f);
	const float spacing_U = IM_FLOOR(spacing_y * 0.50f);
	bb_enlarged.Min.x -= spacing_L;
	bb_enlarged.Min.y -= spacing_U;
	bb_enlarged.Max.x += (spacing_x - spacing_L);
	bb_enlarged.Max.y += (spacing_y - spacing_U);
	//if (g.IO.KeyCtrl) { GetForegroundDrawList()->AddRect(bb_align.Min, bb_align.Max, IM_COL32(255, 0, 0, 255)); }
	//if (g.IO.KeyCtrl) { GetForegroundDrawList()->AddRect(bb_enlarged.Min, bb_enlarged.Max, IM_COL32(0, 255, 0, 255)); }

	bool item_add;
	if (flags & ImGuiSelectableFlags_Disabled)
	{
		ImGuiItemFlags backup_item_flags = window->DC.ItemFlags;
		window->DC.ItemFlags |= ImGuiItemFlags_Disabled | ImGuiItemFlags_NoNavDefaultFocus;
		item_add = ImGui::ItemAdd(bb_enlarged, id);
		window->DC.ItemFlags = backup_item_flags;
	}
	else
	{
		item_add = ImGui::ItemAdd(bb_enlarged, id);
	}
	if (!item_add)
	{
		if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns)
			ImGui::PopColumnsBackground();
		return false;
	}

	// We use NoHoldingActiveID on menus so user can click and _hold_ on a menu then drag to browse child entries
	ImGuiButtonFlags button_flags = 0;
	if (flags & ImGuiSelectableFlags_NoHoldingActiveID) { button_flags |= ImGuiButtonFlags_NoHoldingActiveId; }
	if (flags & ImGuiSelectableFlags_SelectOnNav) { button_flags |= ImGuiButtonFlags_PressedOnClick; }
	if (flags & ImGuiSelectableFlags_SelectOnClick) { button_flags |= ImGuiButtonFlags_PressedOnRelease; }
	if (flags & ImGuiSelectableFlags_Disabled) { button_flags |= ImGuiButtonFlags_Disabled; }
	if (flags & ImGuiSelectableFlags_AllowDoubleClick) { button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick; }
	if (flags & ImGuiSelectableFlags_AllowItemOverlap) { button_flags |= ImGuiButtonFlags_AllowItemOverlap; }

	if (flags & ImGuiSelectableFlags_Disabled)
		selected = false;

	const bool was_selected = selected;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb_enlarged, id, &hovered, &held, button_flags);

	// Update NavId when clicking or when Hovering (this doesn't happen on most widgets), so navigation can be resumed with gamepad/keyboard
	if (pressed || (hovered && (flags & ImGuiSelectableFlags_SetNavIdOnHover)))
	{
		if (!g.NavDisableMouseHover && g.NavWindow == window && g.NavLayer == window->DC.NavLayerCurrent)
		{
			g.NavDisableHighlight = true;
			ImGui::SetNavID(id, window->DC.NavLayerCurrent);
		}
	}
	if (pressed)
		ImGui::MarkItemEdited(id);

	if (flags & ImGuiSelectableFlags_AllowItemOverlap)
		ImGui::SetItemAllowOverlap();

	// In this branch, Selectable() cannot toggle the selection so this will never trigger.
	if (selected != was_selected) //-V547
		window->DC.LastItemStatusFlags |= ImGuiItemStatusFlags_ToggledSelection;

	const ImVec4 text_act = ImColor(c::menu_sett::menu_color_swither);
	const ImVec4 text_hov = ImVec4(251 / 255.f, 251 / 255.f, 251 / 255.f, 1.f);
	const ImVec4 text_dis = ImVec4(202 / 255.f, 202 / 255.f, 202 / 255.f, 1.f);
	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;

	//typedef std::map<ImGuiID, ImVec4> MyMap;
	//MyMap hover_color;

	 //std::map<ImGuiID, ImVec4> hover_color;
	auto it_hcolor = hover_color.find(id);
	if (it_hcolor == hover_color.end())
	{
		hover_color.insert({ id, text_dis });
		it_hcolor = hover_color.find(id);
	}

	if (hovered || selected)
	{
		ImVec4 to = (hovered && !selected) ? text_hov : text_act;
		if (it_hcolor->second.x != to.x)
		{
			if (it_hcolor->second.x < to.x)
				it_hcolor->second.x = ImMin(it_hcolor->second.x + deltatime, to.x);
			else if (it_hcolor->second.x > to.x)
				it_hcolor->second.x = ImMax(to.x, it_hcolor->second.x - deltatime);
		}

		if (it_hcolor->second.y != to.y)
		{
			if (it_hcolor->second.y < to.y)
				it_hcolor->second.y = ImMin(it_hcolor->second.y + deltatime, to.y);
			else if (it_hcolor->second.y > to.y)
				it_hcolor->second.y = ImMax(to.y, it_hcolor->second.y - deltatime);
		}

		if (it_hcolor->second.z != to.z)
		{
			if (it_hcolor->second.z < to.z)
				it_hcolor->second.z = ImMin(it_hcolor->second.z + deltatime, to.z);
			else if (it_hcolor->second.z > to.z)
				it_hcolor->second.z = ImMax(to.z, it_hcolor->second.z - deltatime);
		}
	}
	else
	{
		ImVec4 to = text_dis;
		if (it_hcolor->second.x != to.x)
		{
			if (it_hcolor->second.x < to.x)
				it_hcolor->second.x = ImMin(it_hcolor->second.x + deltatime, to.x);
			else if (it_hcolor->second.x > to.x)
				it_hcolor->second.x = ImMax(to.x, it_hcolor->second.x - deltatime);
		}

		if (it_hcolor->second.y != to.y)
		{
			if (it_hcolor->second.y < to.y)
				it_hcolor->second.y = ImMin(it_hcolor->second.y + deltatime, to.y);
			else if (it_hcolor->second.y > to.y)
				it_hcolor->second.y = ImMax(to.y, it_hcolor->second.y - deltatime);
		}

		if (it_hcolor->second.z != to.z)
		{
			if (it_hcolor->second.z < to.z)
				it_hcolor->second.z = ImMin(it_hcolor->second.z + deltatime, to.z);
			else if (it_hcolor->second.z > to.z)
				it_hcolor->second.z = ImMax(to.z, it_hcolor->second.z - deltatime);
		}
	}

	// Render
	if (held && (flags & ImGuiSelectableFlags_DrawHoveredWhenHeld))
		hovered = true;


	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.CurrentColumns)
		ImGui::PopColumnsBackground();

	ImGui::PushStyleColor(ImGuiCol_Text, it_hcolor->second);
	ImGui::RenderTextClipped(text_min, text_max, label, NULL, &label_size, ImVec2(0.f, 0.5f), &bb_enlarged);
	ImGui::PopStyleColor();

	//ImGui::SetWindowFontScale(c_menu::get().dpi_scale);

	// Automatically close popups
	if (pressed && (window->Flags & ImGuiWindowFlags_Popup) && !(flags & ImGuiSelectableFlags_DontClosePopups) && !(window->DC.ItemFlags & ImGuiItemFlags_SelectableDontClosePopup))
		ImGui::CloseCurrentPopup();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	return pressed;
}
IMGUI_API bool          ListBoxHeader(const char* label, int items_count, int height_in_items = -1);
bool ListBoxHeader(const char* label, const ImVec2& size_arg)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiStyle& style = g.Style;
	const ImGuiID id = ImGui::GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	// Size default to hold ~7 items. Fractional number of items helps seeing that we can scroll down/up without looking at scrollbar.
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), ImGui::GetTextLineHeightWithSpacing() * 7.4f + style.ItemSpacing.y);
	ImVec2 frame_size = ImVec2(size.x, ImMax(size.y, label_size.y));
	ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + frame_size);
	ImRect bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
	window->DC.LastItemRect = bb; // Forward storage for ListBoxFooter.. dodgy.
	g.NextItemData.ClearFlags();

	if (!ImGui::IsRectVisible(bb.Min, bb.Max))
	{
		ImGui::ItemSize(bb.GetSize(), style.FramePadding.y);
		ImGui::ItemAdd(bb, 0, &frame_bb);
		return false;
	}

	ImGui::BeginGroup();
	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	ImGui::BeginChildFrame(id, frame_bb.GetSize());
	return true;
}
bool ListBoxHeader(const char* label, int items_count, int height_in_items)
{
	// Size default to hold ~7.25 items.
	// We add +25% worth of item height to allow the user to see at a glance if there are more items up/down, without looking at the scrollbar.
	// We don't add this extra bit if items_count <= height_in_items. It is slightly dodgy, because it means a dynamic list of items will make the widget resize occasionally when it crosses that size.
	// I am expecting that someone will come and complain about this behavior in a remote future, then we can advise on a better solution.
	if (height_in_items < 0)
		height_in_items = ImMin(items_count, 7);
	const ImGuiStyle& style = ImGui::GetStyle();
	float height_in_items_f = (height_in_items < items_count) ? (height_in_items + 0.25f) : (height_in_items + 0.00f);

	// We include ItemSpacing.y so that a list sized for the exact number of items doesn't make a scrollbar appears. We could also enforce that by passing a flag to BeginChild().
	ImVec2 size;
	size.x = 260.0f;
	size.y = ImFloor(ImGui::GetTextLineHeightWithSpacing() * height_in_items_f + style.FramePadding.y * 2.0f);
	return ListBoxHeader(label, size);
}
void ImGui::ListBoxFooter()
{
	using namespace ImGui;
	ImGuiWindow* parent_window = GetCurrentWindow()->ParentWindow;
	const ImRect bb = parent_window->DC.LastItemRect;
	const ImGuiStyle& style = GetStyle();

	//EndChildFrame();
	ImGui::EndChild_CUSTOM();
	// Redeclare item size so that it includes the label (we have stored the full size in LastItemRect)
	// We call SameLine() to restore DC.CurrentLine* data
	SameLine();
	parent_window->DC.CursorPos = bb.Min;
	ItemSize(bb, style.FramePadding.y);
	EndGroup();
}
bool ListBox(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int height_in_items, bool custom_selectable)
{
	if (!ListBoxHeader(label, items_count, height_in_items))
		return false;
	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	ImGuiListClipper clipper;
	clipper.Begin(items_count, ImGui::GetTextLineHeightWithSpacing()); // We know exactly our line height here so we pass it as a minor optimization, but generally you don't need to.
	while (clipper.Step())
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			const bool item_selected = (i == *current_item);
			const char* item_text;
			if (!items_getter(data, i, &item_text))
				item_text = "*Unknown item*";

			ImGui::PushID(i);
			if (custom_selectable ? CustomSelectable(item_text, item_selected) : ImGui::Selectable(item_text, item_selected))
				//if (custom_selectable ? ImGui::Selectable(item_text, item_selected) : ImGui::Selectable(item_text, item_selected)) //fix xD
			{
				*current_item = i;
				value_changed = true;
			}
			if (item_selected)
				ImGui::SetItemDefaultFocus();
			ImGui::PopID();
		}

	ImGui::ListBoxFooter();
	if (value_changed)
		ImGui::MarkItemEdited(g.CurrentWindow->DC.LastItemId);

	return value_changed;
}
static auto vector_getter = [](void* vec, int idx, const char** out_text)
{
	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;
};

bool ListBoxConfigArray(const char* label, int* currIndex, std::vector<std::string>& values, int height, bool custom_selectable)
{
	return ListBox(label, currIndex, vector_getter,
		static_cast<void*>(&values), values.size(), height, custom_selectable);
}
void AddCircleImageFilled(ImTextureID user_texture_id, const ImVec2& centre, float radius, ImU32 col, int num_segments)
{
	auto window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	window->DrawList->PathClear();

	if ((col & IM_COL32_A_MASK) == 0 || num_segments <= 2)
		return;


	const bool push_texture_id = window->DrawList->_TextureIdStack.empty() || user_texture_id != window->DrawList->_TextureIdStack.back();
	if (push_texture_id)
		window->DrawList->PushTextureID(user_texture_id);

	int vert_start_idx = window->DrawList->VtxBuffer.Size;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
	window->DrawList->PathArcTo(centre, radius, 0.0f, a_max, num_segments - 1);
	window->DrawList->PathFillConvex(col);
	int vert_end_idx = window->DrawList->VtxBuffer.Size;

	ImGui::ShadeVertsLinearUV(window->DrawList, vert_start_idx, vert_end_idx, ImVec2(centre.x - radius, centre.y - radius), ImVec2(centre.x + radius, centre.y + radius), ImVec2(0, 0), ImVec2(1, 1), true);

	if (push_texture_id)
		window->DrawList->PopTextureID();
}
ID3D11Device* pDevice = NULL;
#include "../ragemp_cheat/src/ResourceManager.h"
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
ID3D11ShaderResourceView* IconAvatar = NULL;
void IconAvatarInit(std::string pathpng)
{
	int LogoWidth = 16;
	int LogoHeight = 16;
	bool ImageLoaded = LoadTextureFromFile(pathpng.c_str(), &IconAvatar, &LogoWidth, &LogoHeight);
	IM_ASSERT(ImageLoaded);
}
ImFont* fontbigg;
namespace notification
{
	ImVec2 position;
	ImDrawList* draw;
	bool show_popup = false;
	static int timer = 0;
	static int tipotimer = 0;
	static int alpha = 0;
	static int alpha2 = 0;
	long getMils()
	{
		auto duration = std::chrono::system_clock::now().time_since_epoch();

		return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	}
	bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = size_arg;
		size.x -= style.FramePadding.x * 2;
		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;
		const float circleStart = size.x * (timer / 5000.f);
		const float circleEnd = size.x;
		const float circleWidth = circleEnd - circleStart;
		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);
		const float t = g.Time;
		const float r = size.y / 2;
		const float speed = 1.5f;
		const float a = speed * 0;
		const float b = speed * 0.333f;
		const float c = speed * 0.666f;
		const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
		const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
		const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
	}
	const wchar_t* GetWC(const char* c)
	{
		const size_t cSize = strlen(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, c, cSize);
		return wc;
	}
	void start(const char* text, const char* text2, bool* done)
	{
		if (!done)
			show_popup = true;
		if (&show_popup)
		{
			if (timer < 5000)
			{
				if (alpha < 255)
					alpha = alpha + 5;
				if (alpha2 < 255)
					alpha2 = alpha2 + 8;
			}
			if (timer < 5000)
				timer = timer + 20;
			if (timer > 5000)
				timer = 5000;
			if (timer >= 5000)
			{
				if (alpha > 0)
					alpha = alpha - 5;
				if (alpha2 > 0)
					alpha2 = alpha2 - 8;

				if (alpha <= 0 && alpha2 <= 0)
				{
					alpha = 0;
					timer = -1;
					show_popup = false;
					*done = true;
				}
			}
			if (timer <= 5000 && alpha > 0 && alpha2 > 0)
			{
				const auto vp_size = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

				auto window = ImGui::GetCurrentWindow();
				if (window->SkipItems)
					return;
				ImGuiContext& g = *GImGui;
				window->DrawList->PathClear();
				window->DrawList->AddRectFilledMultiColor({ position.x,position.y }, { position.x + vp_size.x, position.y + vp_size.y }, ImColor(36, 36, 36, alpha), ImColor(36, 36, 36, alpha), ImColor(0, 0, 0, alpha), ImColor(0, 0, 0, alpha)); //dark		
				ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(text).x / 2, ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(text).y / 2 + 22));
				//window->DrawList->AddTextqwqw(fontbigg, { (position.x + (vp_size.x / 2.47f)) - ImGui::CalcTextSize(text).x / 2, (position.y + (vp_size.y / 2.3f)) - ImGui::CalcTextSize(text2).y / 2 }, ImColor(255, 255, 255, alpha2), text);
				AddCircleImageFilled((void*)image::roll, { (position.x + (vp_size.x / 1.96f)) - ImGui::CalcTextSize(text2).x / 2, (position.y + (vp_size.y / 2.6f)) - ImGui::CalcTextSize(text2).y / 2 },
					40,
					ImColor(255, 255, 255),
					360
				);
				const ImU32 col = ImColor(c::menu_sett::menu_color_swither);
				ImGui::SetCursorPos(ImVec2(750, 550));
				BufferingBar("##buffer_bar", timer / 5000.f, ImVec2(440, 8), ImGui::GetColorU32(ImVec4(45, 45, 45, 255)), col);
			}
		}
	}
}
