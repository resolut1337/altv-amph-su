struct RadarSett {
	float x = 300.f;
	float y = 300.f;
	float range = 26.f;
	float size = 110.f;
} RadarSett;


class Base_Radar
{
public:
	void SetSize(const float& Size);
	void SetPos(const Vector2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	float GetSize();
	Vector2 GetPos();
	void AddPoint(const Vector3& LocalPos, const float& LocalYaw, const Vector3& Pos, ImColor Color, int Type = 0, float Yaw = 0.0f, hk_Ped* Peds = 0);
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	bool ShowCrossLine = false;
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	float Proportion = 2680;
	float CircleSize = 6;
	float ArrowSize = 11;
	float ArcArrowSize = 7;
	float RenderRange = 250;
	float LocalYaw = 0.0f;
	hk_Ped* Peds_l;
	bool Opened = true;
	int  PointType = 0;
private:
	Vector2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<Vector2, ImColor, int, float>> Points;
};
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
Vector2 RevolveCoordinatesSystem(float RevolveAngle, Vector2 OriginPos, Vector2 DestPos)
{
	Vector2 ResultPos;
	if (RevolveAngle == 0)
		return DestPos;
	ResultPos.x = OriginPos.x + (DestPos.x - OriginPos.x) * cos(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * sin(RevolveAngle * M_PI / 180);
	ResultPos.y = OriginPos.y - (DestPos.x - OriginPos.x) * sin(RevolveAngle * M_PI / 180) + (DestPos.y - OriginPos.y) * cos(RevolveAngle * M_PI / 180);
	return ResultPos;
}


void Base_Radar::SetRange(const float& Range)
{
	this->RenderRange = Range;
}

void Base_Radar::SetCrossColor(const ImColor& Color)
{
	this->CrossColor = Color;
}

void Base_Radar::SetPos(const Vector2& Pos)
{
	this->Pos = Pos;
}

void Base_Radar::SetSize(const float& Size)
{
	this->Width = Size;
}

float Base_Radar::GetSize()
{
	return this->Width;
}

Vector2 Base_Radar::GetPos()
{
	return this->Pos;
}

void Base_Radar::SetProportion(const float& Proportion)
{
	this->Proportion = Proportion;
}

void Base_Radar::SetDrawList(ImDrawList* DrawList)
{
	this->DrawList = DrawList;
}

void Base_Radar::AddPoint(const Vector3& LocalPos, const float& LocalYaw, const Vector3& Pos, ImColor Color, int Type, float Yaw, hk_Ped* Peds )
{
	//this->Peds_l = Peds;

	Vector2 PointPos;
	float Distance;
	float Angle;

	this->LocalYaw = LocalYaw;

	Distance = sqrt(pow(LocalPos.x - Pos.x, 2) + pow(LocalPos.y - Pos.y, 2));

	Angle = atan2(Pos.y - LocalPos.y, Pos.x - LocalPos.x) * 180 / M_PI;
	Angle = (this->LocalYaw - Angle) * M_PI / 180;

	Distance = Distance / this->Proportion * this->RenderRange * 2;

	PointPos.x = this->Pos.x + Distance * sin(Angle);
	PointPos.y = this->Pos.y - Distance * cos(Angle);


	// Circle range
	//Distance = sqrt(pow(this->Pos.x - PointPos.x, 2) + pow(this->Pos.y - PointPos.y, 2));
	//if (Distance > this->RenderRange)
	//	return;

	if (PointPos.x < this->Pos.x - RenderRange || PointPos.x > this->Pos.x + RenderRange || PointPos.y > this->Pos.y + RenderRange || PointPos.y < this->Pos.y - RenderRange)
		return;

	std::tuple<Vector2, ImColor, int, float> Data(PointPos, Color, Type, Yaw);
	this->Points.push_back(Data);
}

void DrawTriangle(Vector2 Center, ImColor Color, float Width, float Height, float Yaw)
{
	Vector2 a, b, c;
	Vector2 Re_a, Re_b, Re_c;
	a = Vector2{ Center.x - Width / 2,Center.y };
	b = Vector2{ Center.x + Width / 2,Center.y };
	c = Vector2{ Center.x,Center.y - Height };
	a = RevolveCoordinatesSystem(-Yaw, Center, a);
	b = RevolveCoordinatesSystem(-Yaw, Center, b);
	c = RevolveCoordinatesSystem(-Yaw, Center, c);
	ImGui::GetForegroundDrawList()->AddTriangleFilled(
		ImVec2(a.x, a.y),
		ImVec2(b.x, b.y),
		ImVec2(c.x, c.y),
		Color);
}
void Base_Radar::Render()
{
	if (Width <= 0)
		return;

	std::pair<Vector2, Vector2> Line1;
	std::pair<Vector2, Vector2> Line2;

	Line1.first = Vector2(this->Pos.x - this->Width / 2, this->Pos.y);
	Line1.second = Vector2(this->Pos.x + this->Width / 2, this->Pos.y);
	Line2.first = Vector2(this->Pos.x, this->Pos.y - this->Width / 2);
	Line2.second = Vector2(this->Pos.x, this->Pos.y + this->Width / 2);

	if (this->Opened)
	{
		if (this->ShowCrossLine)
		{
			this->DrawList->AddLine(Line1.first.ToImVec2(), Line1.second.ToImVec2(), this->CrossColor, 1);
			this->DrawList->AddLine(Line2.first.ToImVec2(), Line2.second.ToImVec2(), this->CrossColor, 1);
		}

		for (auto PointSingle : this->Points)
		{
			Vector2	PointPos = std::get<0>(PointSingle);
			ImColor PointColor = std::get<1>(PointSingle);
			int		PointType = std::get<2>(PointSingle);
			float	PointYaw = std::get<3>(PointSingle);

			//if (amphetamine::amphetamine_settings->radarhack_weapons) {
			//	string str = "";
			//	hk_WeaponManager* PedsWeaponManager = this->Peds_l->WeaponManager();
			//	if (PedsWeaponManager != 0) {
			//		hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
			//		if (PedsWeaponInfo) {
			//			uint64_t Hash = PedsWeaponInfo->GetHash();
			//			str.append(get_weapon_name(Hash));
			//			ImVec2 TextSize = ImGui::CalcTextSize((char*)str.c_str());

			//			//Visuals::DrawOutlinedText(font::poppins_medium_low, str, ImVec2(PointPos.ToImVec2().x + 4, PointPos.ToImVec2().y + 4), 12.f, c::menu_sett::menu_color_swither, true);


			//			ImVec2 positt = ImVec2(PointPos.ToImVec2().x + 4, PointPos.ToImVec2().y + 4);
			//			float fontSize = 12.f;
			//			ImGuiContext& g = *GImGui;
			//			if (fontSize == 0.f)
			//				fontSize = g.Font->FontSize;
			//			std::string line;
			//			std::stringstream stream(str);
			//			ImVec2 textSize = font::poppins_medium_low->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, line.c_str());
			//			while (std::getline(stream, line))
			//			{
			//				if (true) {
			//					this->DrawList->AddText(font::poppins_medium_low, fontSize, ImVec2(positt.x + 1.3, positt.y), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
			//					this->DrawList->AddText(font::poppins_medium_low, fontSize, ImVec2(positt.x, positt.y + 1.3), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
			//					this->DrawList->AddText(font::poppins_medium_low, fontSize, ImVec2(positt.x + 1.3, positt.y), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
			//					this->DrawList->AddText(font::poppins_medium_low, fontSize, ImVec2(positt.x, positt.y + 1.3), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
			//				}
			//				this->DrawList->AddText(font::poppins_medium_low, fontSize, positt, c::menu_sett::menu_color_swither, line.c_str(), NULL, 0.0f, NULL);
			//			}
			//		}
			//	}
			//}

			if (PointType == 0)
			{
				this->DrawList->AddCircle(PointPos.ToImVec2(), this->CircleSize, ImColor(0, 0, 0));
				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), this->CircleSize, PointColor); //PointColor
			}
			else if (PointType == 1)
			{
				Vector2 a, b, c;
				Vector2 Re_a, Re_b, Re_c;
				Vector2 Re_Point;
				float Angle = (this->LocalYaw - PointYaw) + 180;
				Re_Point = RevolveCoordinatesSystem(Angle, this->Pos, PointPos);

				Re_a = Vector2(Re_Point.x, Re_Point.y + this->ArrowSize);
				Re_b = Vector2(Re_Point.x - this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);
				Re_c = Vector2(Re_Point.x + this->ArrowSize / 1.5, Re_Point.y - this->ArrowSize / 2);

				a = RevolveCoordinatesSystem(-Angle, this->Pos, Re_a);
				b = RevolveCoordinatesSystem(-Angle, this->Pos, Re_b);
				c = RevolveCoordinatesSystem(-Angle, this->Pos, Re_c);

				this->DrawList->AddQuadFilled(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					PointColor
				);
				this->DrawList->AddQuad(
					ImVec2(a.x, a.y),
					ImVec2(b.x, b.y),
					ImVec2(PointPos.x, PointPos.y),
					ImVec2(c.x, c.y),
					ImColor(0, 0, 0, 150),
					0.1
				);
			}
			else
			{
				ImVec2 TrianglePoint, TrianglePoint_1, TrianglePoint_2;
				float Angle = (this->LocalYaw - PointYaw) - 90;

				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), 0.85 * this->ArcArrowSize, PointColor, 30);
				this->DrawList->AddCircle(PointPos.ToImVec2(), 0.95 * this->ArcArrowSize, ImColor(0, 0, 0, 150), 0, 0.1);

				TrianglePoint.x = PointPos.x + (this->ArcArrowSize + this->ArcArrowSize / 3) * cos(-Angle * M_PI / 180);
				TrianglePoint.y = PointPos.y - (this->ArcArrowSize + this->ArcArrowSize / 3) * sin(-Angle * M_PI / 180);

				TrianglePoint_1.x = PointPos.x + this->ArcArrowSize * cos(-(Angle - 30) * M_PI / 180);
				TrianglePoint_1.y = PointPos.y - this->ArcArrowSize * sin(-(Angle - 30) * M_PI / 180);

				TrianglePoint_2.x = PointPos.x + this->ArcArrowSize * cos(-(Angle + 30) * M_PI / 180);
				TrianglePoint_2.y = PointPos.y - this->ArcArrowSize * sin(-(Angle + 30) * M_PI / 180);

				this->DrawList->PathLineTo(TrianglePoint);
				this->DrawList->PathLineTo(TrianglePoint_1);
				this->DrawList->PathLineTo(TrianglePoint_2);
				this->DrawList->PathFillConvex(ImColor(220, 220, 220, 240));
			}
		}
	}

	if (this->Points.size() > 0)
		this->Points.clear();
}
void radar_setting(Base_Radar& Radar)
{

//	ImGui::SetNextWindowBgAlpha(amphetamine::amphetamine_settings->radar_bg_alpha);
	ImGui::Begin(("AMPH.su"), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	const ImVec2& pos = ImGui::GetWindowPos();

	ImGui::SetWindowSize({ amphetamine::amphetamine_settings->radar_range * 2, amphetamine::amphetamine_settings->radar_range * 2 });
	ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(amphetamine::amphetamine_settings->radar_range * 2, amphetamine::amphetamine_settings->radar_range * 2), ImGui::GetColorU32(ImVec4(c::bg::background.x, c::bg::background.y, c::bg::background.z, amphetamine::amphetamine_settings->radar_bg_alpha)), c::bg::rounding);
	//ImGui::GetBackgroundDrawList()->AddRect(pos, pos + ImVec2(amphetamine::amphetamine_settings->radar_range * 2, amphetamine::amphetamine_settings->radar_range * 2), ImGui::GetColorU32(c::bg::outline_background), c::bg::rounding);

	if (!amphetamine::amphetamine_settings->custom_radar)
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		amphetamine::amphetamine_settings->show_radar_crossline = false;
		amphetamine::amphetamine_settings->proportion = 3300.f;
		amphetamine::amphetamine_settings->radar_point_size_proportion = 1.f;
		amphetamine::amphetamine_settings->radar_range = 150.f;
		amphetamine::amphetamine_settings->radar_bg_alpha = 0.1f;
	}
	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + amphetamine::amphetamine_settings->radar_range, ImGui::GetWindowPos().y + amphetamine::amphetamine_settings->radar_range });
	Radar.SetProportion(amphetamine::amphetamine_settings->proportion);
	Radar.SetRange(amphetamine::amphetamine_settings->radar_range);
	Radar.SetSize(amphetamine::amphetamine_settings->radar_range * 2);
	Radar.SetCrossColor(amphetamine::amphetamine_settings->radar_crossline_color);

	Radar.ArcArrowSize *= amphetamine::amphetamine_settings->radar_point_size_proportion;
	Radar.ArrowSize *= amphetamine::amphetamine_settings->radar_point_size_proportion;
	Radar.CircleSize *= amphetamine::amphetamine_settings->radar_point_size_proportion;

	Radar.ShowCrossLine = amphetamine::amphetamine_settings->radar_crossline_color;
	Radar.Opened = true;
}


Vector3 RotationToDirectionV3(Vector3 rot) {
	//Vector3 dir;
	//float radiansZ = rot.z * 0.0174532924f;
	//float radiansX = rot.x * 0.0174532924f;
	//float num = abs((float)cos((double)radiansX));
	//dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	//dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	//dir.z = (float)sin((double)radiansX);
	//return dir;

	Vector3 dir;
	float radiansZ = rot.z * 0.0174532924f;
	float radiansX = rot.x * 0.0174532924f;
	float num = std::abs((float)std::cos((double)radiansX));
	dir.x = (float)((double)((float)(-(float)std::sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
	dir.z = (float)std::sin((double)radiansX);
	return dir;
}
#include <DirectXMath.h>




#define PIq 3.14159265358979323846
Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float nigga = flAngle;
	nigga += 25.f;

	float flYaw = (nigga) * (PIq / 180.0);

	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));

	return Vector2(posonscreenX, posonscreenY);
}
__forceinline float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
	return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
}
bool OOFdsf(Vector3 ped_pos) {
	Vector3 pos = ped_pos;
	float x_screen = GetSystemMetrics(SM_CXSCREEN) / 2;
	float y_screen = GetSystemMetrics(SM_CYSCREEN) / 2;
	Vector2 screensenter = { x_screen, y_screen };
	Vector2 screen = Vector2(Memory::WorldToScreen(pos).x, Memory::WorldToScreen(pos).y);

	float num = Calc2D_Dist(screensenter, screen);
	return num > 1000.f;
}
void OOF_(Vector3 ped_pos, int index) {
	if (amphetamine::amphetamine_settings->oofindicators_players) {
		float x_screen = GetSystemMetrics(SM_CXSCREEN) / 2;
		float y_screen = GetSystemMetrics(SM_CYSCREEN) / 2;
		if (OOFdsf(ped_pos)) {
			DWORD64 pGameCamManager = Memory::pGameCamManager;
			if (pGameCamManager) {
				DWORD64 pMyCameraManagerAngles = *(DWORD64*)(pGameCamManager + 0x0000);
				if (pMyCameraManagerAngles) {
					DWORD64 pMyCameraAngles = *(DWORD64*)(pMyCameraManagerAngles + 0x0000); //0x0000  
					if (pMyCameraAngles) {
						DWORD64 pMyFPSAngles = *(DWORD64*)(pMyCameraAngles + 0x03C0);
						if (pMyFPSAngles) {
							Vector3 CamRotFPS = *(Vector3*)(pMyFPSAngles + 0x0040);
							float rot = 0.0f;
							rot = acosf(CamRotFPS.x) * 180.0f / DirectX::XM_PI;
							if (asinf(CamRotFPS.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;
							//Radar.AddPoint(localpos, rot, pedPos, ImColor(c::menu_sett::menu_color_swither), amphetamine::amphetamine_settings->radar_type, 1 /*pPawn->m_angEyeAngles_vec2().y*/);


							Vector3 local = *(Vector3*)(Memory::LocalPlayer + 0x90);
							//Vector3 local = m_pLocalPlayerPawn->m_vecLastClipCameraPos();
							Vector3 plyq = ped_pos;
							float y = local.x - plyq.x;
							float x = local.z - plyq.z;
							float Angle = atan2(plyq.y - local.y, plyq.x - local.x) * 180 / M_PI;
							Angle = (rot - Angle) - (M_PI / 180);
							ImU32 color = ImColor(c::menu_sett::menu_color_swither);
							Vector2 tp0 = CosTanSinLineH(Angle, 5.f, x_screen, y_screen, 210.f);
							Vector2 tp1 = CosTanSinLineH((Angle)+2.f, 5.f, x_screen, y_screen, 200.f);
							Vector2 tp2 = CosTanSinLineH((Angle)-2.f, 5.f, x_screen, y_screen, 200.f);
							ImGui::GetBackgroundDrawList()->PathLineTo(ImVec2(tp0.x, tp0.y));
							ImGui::GetBackgroundDrawList()->PathLineTo(ImVec2(tp1.x, tp1.y));
							ImGui::GetBackgroundDrawList()->PathLineTo(ImVec2(tp2.x, tp2.y));
							ImGui::GetBackgroundDrawList()->PathFillConvex(ImColor(220, 220, 220, 240));
							ImGui::GetBackgroundDrawList()->AddTriangleFilled({ tp0.x,tp0.y }, { tp1.x,tp1.y }, { tp2.x,tp2.y }, color);
							ImGui::GetBackgroundDrawList()->AddTriangle({ tp0.x,tp0.y }, { tp1.x,tp1.y }, { tp2.x,tp2.y }, ImColor(0, 0, 0, 255), 2.f);


							if (amphetamine::amphetamine_settings->oofindicators_players_weapon) {
								//ImVec2 TextSize = ImGui::CalcTextSize((char*)str.c_str());
								Visuals::DrawOutlinedText(font::poppins_medium_low, Pool::new_list[index].weapon_for_arrow.c_str(), ImVec2(tp0.x, tp0.y + 15), 14.f, c::menu_sett::menu_color_swither, false);

								//ImGui::GetBackgroundDrawList()->AddText();
							}
						}
					}
				}
			}
		}
	}
}


void Entity_Tick()
{
	if (amphetamine::amphetamine_settings->enable)
	{
		hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
		if (LocalPlayer) {
			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
			if (ReplayInterface) {
				hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
				if (PedInterface) {
					Base_Radar Radar;
					if (amphetamine::amphetamine_settings->radarhack)
						radar_setting(Radar);
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
					ImVec2 LocalPlayer_Location = Memory::WorldToScreen(LocalPlayer->GetCoordinate());
					Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
					for (int i = 0; i < 512; i++) {
						hk_Ped* Peds_ = Pool::new_list[i].ped;
						if (!Peds_) continue;
						if ((DWORD64)Pool::new_list[i].ped == Memory::LocalPlayer)
							continue;
						Vector3 pedPos = Vector3(Pool::new_list[i].position.x, Pool::new_list[i].position.y, Pool::new_list[i].position.z);
						if (pedPos.x == 0.0f || pedPos.y == 0.0f || pedPos.z == 0.0f)
							continue;
						float health = Pool::new_list[i].health;
						if (!amphetamine::amphetamine_settings->Draw_Dead)
						{
							if (health <= 0) continue;
						}
						if (!amphetamine::amphetamine_settings->Draw_botvisuals)
						{
							if (!Pool::new_list[i].is_ped_a_player) {
								continue;
							}
						}
						if (Aimbot::get_distance(localpos, pedPos) > amphetamine::amphetamine_settings->Distance)
							continue;
						if (amphetamine::amphetamine_settings->radarhack) {
							DWORD64 pGameCamManager = Memory::pGameCamManager;
							if (pGameCamManager) {
								DWORD64 pMyCameraManagerAngles = *(DWORD64*)(pGameCamManager + 0x0000);
								if (pMyCameraManagerAngles) {
									DWORD64 pMyCameraAngles = *(DWORD64*)(pMyCameraManagerAngles + 0x0000); //0x0000  
									if (pMyCameraAngles) {
										DWORD64 pMyFPSAngles = *(DWORD64*)(pMyCameraAngles + 0x03C0);
										if (pMyFPSAngles) {
											Vector3 CamRotFPS = *(Vector3*)(pMyFPSAngles + 0x0040);
											float rot = 0.0f;
											rot = acosf(CamRotFPS.x) * 180.0f / DirectX::XM_PI;
											if (asinf(CamRotFPS.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;
											Radar.AddPoint(localpos, rot, pedPos, ImColor(c::menu_sett::menu_color_swither), amphetamine::amphetamine_settings->radar_type, 1 /*pPawn->m_angEyeAngles_vec2().y*/);
										}
									}
								}
							}
						}
						OOF_(pedPos, i);
						ImVec2 Ped_Location = Memory::WorldToScreen(pedPos);
						if (!IsOnScreen(Ped_Location)) continue;
						auto Distance = Aimbot::get_distance(localpos, pedPos);

						Visuals::Visuals(i, pedPos, LocalPlayer_Location, Ped_Location, ImColor(r, g, b, 255.f), Distance, Pool::new_list[i].visible , Pool::new_list[i].is_ped_is_any_vehicle);
					}
					if (amphetamine::amphetamine_settings->radarhack)
					{
						Radar.Render();
						ImGui::End();
					}
				}		
			}
		}
	}
}
