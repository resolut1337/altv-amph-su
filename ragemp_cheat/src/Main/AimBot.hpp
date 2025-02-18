#define get_array_size(array)	(sizeof(array) / sizeof(array[0]))
POINT pos_cursor;
POINT Move_mouse(int x, int y) {
	GetCursorPos(&pos_cursor);
	pos_cursor.x += (long)x; pos_cursor.y += (long)y;
	SAFE_CALL(SetCursorPos)(pos_cursor.x, pos_cursor.y);
	return pos_cursor;
}
#include <iostream>
#include <random>
float RandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}
HWND hwnd_outra_win;

void AimBot(hk_Ped* Peds, ImVec2 LocalPlayer_Location, ImVec2 Ped_Location, float Distance) {
	 
	if (!IsOnScreen(Ped_Location)) return;

	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
		};
	auto center_x = ImGui::GetIO().DisplaySize.x / 2;
	auto center_y = ImGui::GetIO().DisplaySize.y / 2;
	auto bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e);
	switch (amphetamine::amphetamine_settings->Aimbot_Bone)
	{
	case 0:
		//bone_pos = FiveM::GetBonePosW2S(entity, SKEL_Head);
		break;
	case 1:
		bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2);
		break;
	case 2:
		bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB);
		break;
	case 3:
		bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000);
		break;
	case 4:
		bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D);
		break;
	case 5:
		bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0xb1);
		break;
	case 6:
		auto bone1 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e)).y);
		auto bone2 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2)).y);
		auto bone3 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB)).y);
		auto bone4 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000)).y);
		auto bone5 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D)).y);
		auto bone6 = get_distance(center_x, center_y, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0xb1)).x, Memory::WorldToScreen(Memory::GetBonePosVec3((uintptr_t)Peds, 0xb1)).y);

		if (bone1 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e);
		}
		else if (bone2 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2);
		}
		else if (bone3 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB);
		}
		else if (bone4 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000);
		}
		else if (bone5 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D);
		}
		else if (bone6 < 20) {
			bone_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0xb1);
		}
		break;
	}

	DWORD64 cam = Memory::GetCamera();
	if (cam)
	{
		Vector3 CrosshairPos = *(Vector3*)(cam + 0x60);
		Vector3 caca(CrosshairPos.x - bone_pos.x, CrosshairPos.y - bone_pos.y, CrosshairPos.z - bone_pos.z);
		float distance = caca.length();
		float threshold = 0.5f / (amphetamine::amphetamine_settings->AimbotSmooth * 20);
		Vector3 Out = Vector3((bone_pos.x - CrosshairPos.x) / distance, (bone_pos.y - CrosshairPos.y) / distance, (bone_pos.z - CrosshairPos.z) / distance);


		

		ImVec2 screen = Memory::WorldToScreen(bone_pos);
		auto fov = get_distance(center_x, center_y, screen.x, screen.y);


		if (fov < 1 * 10)
		{
			if (amphetamine::amphetamine_settings->TriggerBot) {
				if (GetAsyncKeyState(amphetamine::amphetamine_settings->trigetbotHotkey) & 0x8000) {
					CONTROLS::_SET_CONTROL_NORMAL(0, 24, 1);
				}
			}
		}
		if (fov < amphetamine::amphetamine_settings->Aimbot_Fov * 10)
		{


			if (amphetamine::amphetamine_settings->Aimbot_Toggle) {

				if (GetAsyncKeyState(amphetamine::amphetamine_settings->HotKeyAim) & 0x8000) {

					if (amphetamine::amphetamine_settings->AimbotSmooth <= 1)
					{
						if (amphetamine::amphetamine_settings->aimmode == 0) {
							*(Vector3*)(cam + 0x40) = Out;  //FPS
							*(Vector3*)(cam + 0x3D0) = Out; //TPS
						}
						else if (amphetamine::amphetamine_settings->aimmode == 1) {
						/*	Out.x += RandomFloat(0.0f, 1.0f);
							Out.y += RandomFloat(0.0f, 1.0f);
							Out.z += RandomFloat(0.0f, 1.0f);*/
							//Move_mouse(float(screen.x - center_x), float(screen.y - center_y));

						//	mouse_event(MOUSEEVENTF_MOVE, float(screen.x - center_x), float(screen.y - center_y), NULL, NULL);
							*(Vector3*)(cam + 0x40) = Out;  //FPS
							*(Vector3*)(cam + 0x3D0) = Out; //TPS
						}
					}
					else
					{
						//First Person
						{
							Vector3 angles = *(Vector3*)(cam + 0x40);
							if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
							{
								if (angles.x > Out.x)
									*(float*)(cam + 0x40 + 0x0) -= threshold;
								else if (angles.x < Out.x)
									*(float*)(cam + 0x40 + 0x0) += threshold;
							}
							if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
							{
								if (angles.y > Out.y)
									*(float*)(cam + 0x40 + 0x4) -= threshold;
								else if (angles.y < Out.y)
									*(float*)(cam + 0x40 + 0x4) += threshold;
							}
							if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
							{
								if (angles.z > Out.z)
									*(float*)(cam + 0x40 + 0x8) -= threshold;
								else if (angles.z < Out.z)
									*(float*)(cam + 0x40 + 0x8) += threshold;
							}
						}
						//Third Person
						{
							Vector3 angles = *(Vector3*)(cam + 0x3D0);
							if (((Out.x - angles.x) > threshold) || ((angles.x - Out.x) > threshold))
							{
								if (angles.x > Out.x)
									*(float*)(cam + 0x3D0 + 0x0) -= threshold;
								else if (angles.x < Out.x)
									*(float*)(cam + 0x3D0 + 0x0) += threshold;
							}
							if (((Out.y - angles.y) > threshold) || ((angles.y - Out.y) > threshold))
							{
								if (angles.y > Out.y)
									*(float*)(cam + 0x3D0 + 0x4) -= threshold;
								else if (angles.y < Out.y)
									*(float*)(cam + 0x3D0 + 0x4) += threshold;
							}
							if (((Out.z - angles.z) > threshold) || ((angles.z - Out.z) > threshold))
							{
								if (angles.z > Out.z)
									*(float*)(cam + 0x3D0 + 0x8) -= threshold;
								else if (angles.z < Out.z)
									*(float*)(cam + 0x3D0 + 0x8) += threshold;
							}
						}
						//Move_mouse(float(screen.x - center_x), float(screen.y - center_y));
					}
				}
			}

			Vector3 bone_position_silent;
			if (amphetamine::amphetamine_settings->Silent_Aim) {
				//if (GetTickCount64() % Config::AimbotTick == 1)
				switch (amphetamine::amphetamine_settings->Aimbot_Bone)
				{
				case 0:
					//bone_pos = FiveM::GetBonePosW2S(entity, SKEL_Head);
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e);
					break;
				case 1:
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2);
					break;
				case 2:
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB);
					break;
				case 3:
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000);
					break;
				case 4:
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D);
					break;
				case 5:
					bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0xb1);
					break;
				case 6:

					switch (rand() % 10) {
					case 0:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F2);
						// public uint hitBone;
						break;
					case 1:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0xF9BB);
						// public uint hitBone;
						break;
					case 2:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9000);
						// public uint hitBone;
						break;
					case 3:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D);
						// public uint hitBone;
						break;
					case 4:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x60F0);

						break;
					case 5:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x2E28);

						break;
					case 6:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x083C);

						break;
					case 7:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x512D);

						break;
					case 8:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x9D4D);

						break;
					case 9:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0xCA72);

						break;
					case 10:
						bone_position_silent = Memory::GetBonePosVec3((uintptr_t)Peds, 0x796E);

						break;
					}
					break;
				}

				auto player = player::player_ped_id();
				auto WeaponHash = weapon::get_selected_ped_weapon(player); //GET_SELECTED_PED_WEAPON
				auto WeaponDamage = weapon::_0x3133b907d8b32053(WeaponHash, NULL);
				if (ped::is_ped_shooting(player))
				{
					auto Out = Vector3(bone_position_silent);
					auto playerPed = player::get_player_ped_script_index(player::player_id()); //GET_PLAYER_PED_SCRIPT_INDEX
					float h = ENTITY::GET_ENTITY_HEADING(playerPed);

					if (!amphetamine::amphetamine_settings->Silent_Aimhotkey) {
						gameplay::shoot_single_bullet_between_coords(Out.x + cos(h) * .15f, Out.y + sin(h) * .15f, Out.z, Out.x - cos(h) * .15f, Out.y - sin(h) * .15f, Out.z, (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);
					}
					else if (GetAsyncKeyState(amphetamine::amphetamine_settings->silenthotkeyaim) & 0x8000) {
						gameplay::shoot_single_bullet_between_coords(Out.x + cos(h) * .15f, Out.y + sin(h) * .15f, Out.z, Out.x - cos(h) * .15f, Out.y - sin(h) * .15f, Out.z, (int)WeaponDamage, false, WeaponHash, player, true, false, 3.f);
					}
				}
			}
			if (amphetamine::amphetamine_settings->damager) {
				if (GetAsyncKeyState(amphetamine::amphetamine_settings->damager_key) & 0x8000) {
					if (amphetamine::amphetamine_settings->_shotLimit != amphetamine::amphetamine_settings->__shotLimit) {
						amphetamine::amphetamine_settings->__shotLimit = amphetamine::amphetamine_settings->_shotLimit;
						amphetamine::amphetamine_settings->shotLimit = floor(amphetamine::amphetamine_settings->_shotLimit);
					}
					if (GetTickCount64() - amphetamine::amphetamine_settings->lastShot > 10000 / amphetamine::amphetamine_settings->shootRate) {
						amphetamine::amphetamine_settings->lastShot = GetTickCount64();
						if (!amphetamine::amphetamine_settings->shotLimiter || !amphetamine::amphetamine_settings->shootCounter || amphetamine::amphetamine_settings->shotCount < amphetamine::amphetamine_settings->shotLimit) {
							Hash WeaponHash;
							if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &WeaponHash, 1)) {
								auto playerPed = player::get_player_ped_script_index(player::player_id()); //GET_PLAYER_PED_SCRIPT_INDEX
								float h = ENTITY::GET_ENTITY_HEADING(playerPed);
								auto bonGDHDGHe_pos = Memory::GetBonePosVec3((uintptr_t)Peds, 0x796e);
								gameplay::shoot_single_bullet_between_coords(bonGDHDGHe_pos.x + cos(h) * .15f, bonGDHDGHe_pos.y + sin(h) * .15f, bonGDHDGHe_pos.z, bonGDHDGHe_pos.x - cos(h) * .15f, bonGDHDGHe_pos.y - sin(h) * .15f, bonGDHDGHe_pos.z, round(weapon::_0x3133b907d8b32053(WeaponHash, NULL)), true, WeaponHash, player::player_ped_id(), true, false, 5e4f);
								if (amphetamine::amphetamine_settings->shootCounter) {
									amphetamine::amphetamine_settings->shotCount++;
								}
							}
						}
					}
				}
			}

			//if (Config::slaper) {
			//	if (GetAsyncKeyState(Config::slaper_key) & 0x8000) {
			//		auto targetPed = PLAYER::GET_PLAYER_PED(Memory::pointer_to_handle((uintptr_t)Peds));

			//		auto playerPed = PLAYER::GET_PLAYER_PED(-1);

			//		Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, false);
			//		Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(playerPed, false);

			//		float distance = get_distance_between_coords_3d(targetPos, playerPos);

			//		if (distance <= 2.0) {
			//			// Наносим удар
			//			ENTITY::SET_ENTITY_VELOCITY(targetPed, 0.0, 0.0, 50.0);

			//			ENTITY::SET_ENTITY_HEALTH(targetPed, 0.0);
			//		}
			//	}
			//}



		}
	}
}