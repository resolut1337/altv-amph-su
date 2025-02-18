void Set_Health(float health)
{
	if (Memory::Check::isPlayerValid()) {
		*(float*)(Memory::LocalPlayer + 0x280) = health;
		//*(float*)(Memory::LocalPlayer + 0x2A0) = health; //max health
	}
}

void Set_Armor(float armor)
{
	if (Memory::Check::isPlayerValid())
		*(float*)(Memory::LocalPlayer + 0x150C) = armor; //old 0x14E0
}
namespace VehicleQ {
	bool Valid()
	{
		if (Helper::ValidPTR(Memory::World))
		{
			DWORD64 vehicle = *(DWORD64*)(Memory::LocalPlayer + 0xD28);
			if (vehicle != NULL)
				return true;
		}
		return false;
	}
	void Set_Health(float engine, float gastank, float ignition)
	{
		if (Valid() && Memory::Check::isPlayerVehicleValid())
		{
			DWORD64 veh = *(DWORD64*)(Memory::LocalPlayer + 0x0D10);
			if (veh != NULL)
			{
				*(float*)(veh + 0x08E8) = engine;   //Engine
				*(float*)(veh + 0x824) = gastank;  //Gas Tank
				*(float*)(veh + 0x854) = ignition; //Ignition
			}
		}

	}

	/*void Godmode(bool value)
	{
		if (Memory::Check::isPlayerValid()) {
			DWORD64 veh = *(DWORD64*)(Memory::LocalPlayer + 0x0D10);
			if (value) {
				*(byte*)(veh + 0x189) = 1;
				*(float*)(veh + 0x280) = 1000;
				*(float*)(veh + 0x8E8) = 1000;
				*(float*)(veh + 0x824) = 1000;
				*(float*)(veh + 0x0820) = 1000;
			}
			if (!value)
				*(byte*)(veh + 0x189) = 0;
		}
	}*/
}



bool norecoil_proverka = false;
void NoRecoil()
{
	if (Memory::Check::isPlayerValid())
	{
		DWORD64 Addr = *(DWORD64*)(Memory::LocalPlayer + 0x10B8); // new 0x10B8
		if (Helper::ValidPTR(Addr))
		{
			Addr = *(DWORD64*)(Addr + 0x20);
			if (amphetamine::amphetamine_settings->No_Recoil) {
				if (Helper::ValidPTR(Addr))
				{
					*(float*)(Addr + 0x2E4) = 0.0f;
					*(float*)(Addr + 0x2E8) = 0.0f;
					*(float*)(Addr + 0x84) = 0.0f;
				}
				norecoil_proverka = true;
			}
			else {
				if (norecoil_proverka == true) {
					float val1 = *(float*)(Addr + 0x2E4);
					float val2 = *(float*)(Addr + 0x2E8);
					float val3 = *(float*)(Addr + 0x84);

					if (val1 == 0.f && val2 == 0.f && val3 == 0.f) {
						*(float*)(Addr + 0x2E4) = 0.3f;
						*(float*)(Addr + 0x2E8) = 0.3f;
						*(float*)(Addr + 0x84) = 0.3f;
					}
					if (val1 == 0.3f && val2 == 0.3f && val3 == 0.3f) {
						norecoil_proverka = false;
					}
				}
			}
		}
	}

}
bool nospread_proverka = false;
void NoSpread()
{
	if (Memory::Check::isPlayerValid())
	{
		DWORD64 Addr = *(DWORD64*)(Memory::LocalPlayer + 0x10B8); // new 0x10B8
		if (Helper::ValidPTR(Addr))
		{
			Addr = *(DWORD64*)(Addr + 0x20);
			if (amphetamine::amphetamine_settings->No_Spread) {
				if (Helper::ValidPTR(Addr))
				{
					*(float*)(Addr + 0x74) = 0.0f;
				}
				nospread_proverka = true;
			}
			else
			{
				if (nospread_proverka == true) {
					float val = *(float*)(Addr + 0x74);
					if (val == 0.0f)
						*(float*)(Addr + 0x74) = 1.0f;

					if (val == 1.0f) {
						nospread_proverka = false;
					}
				}
			}
		}
	}
}
bool proverkanapidoraspeed = false;

bool on_car = false;
static float noclipspeed = 1.00001f;
static bool speed = false;

uintptr_t get_multilayer_pointer(uintptr_t base_address, std::vector<DWORD> offsets)
{
	uintptr_t ptr = *(uintptr_t*)(base_address);
	if (!ptr) {

		return NULL;
	}
	auto level = offsets.size();

	for (auto i = 0; i < level; i++)
	{
		if (i == level - 1)
		{
			ptr += offsets[i];
			if (!ptr) return NULL;
			return ptr;
		}
		else
		{
			ptr = *(uint64_t*)(ptr + offsets[i]);
			if (!ptr) return NULL;
		}
	}

	return ptr;
}
template <typename T>
T get_value(std::vector<DWORD> offsets) {

	uintptr_t Addr = get_multilayer_pointer(Memory::World, offsets);
	if (Addr == NULL) {
		return NULL;
	}

	return *((T*)Addr);
}
template <typename T>
void set_value(std::vector<DWORD> offsets, T value) {
	uintptr_t Addr = get_multilayer_pointer(Memory::World, offsets);
	if (Addr == NULL) {
		return;
	}

	*reinterpret_cast<T*>(Addr) = value;
}
namespace NoClip
{
	void SetPlayerPositionToCoord(D3DXVECTOR3 pos)
	{
		DWORD64 posbase = *(DWORD64*)(Memory::LocalPlayer + 0x30);
		*(D3DXVECTOR3*)(posbase + 0x50) = pos;
		*(D3DXVECTOR3*)(Memory::LocalPlayer + 0x90) = pos;
		uintptr_t dpos = *(uintptr_t*)(Memory::LocalPlayer + 0x30);
		D3DXVECTOR3 vec = *(D3DXVECTOR3*)(dpos + 0x50);
		*(D3DXVECTOR3*)(Memory::LocalPlayer + 0x90) = pos;
	}
	void SetVehiclePositionToCoord(D3DXVECTOR3 pos)
	{
		uintptr_t curveh = *(uintptr_t*)(Memory::LocalPlayer + 0x0D30);
		DWORD64 posbase = *(DWORD64*)(curveh + 0x30);
		*(D3DXVECTOR3*)(posbase + 0x50) = pos;
		*(D3DXVECTOR3*)(curveh + 0x90) = pos;
	}
	void SetFreeze(bool toggle)
	{
		if (toggle)
		{
			*(BYTE*)(Memory::LocalPlayer + 0x218) = 2;
		}
		else if (!toggle)
		{
			*(BYTE*)(Memory::LocalPlayer + 0x218) = 0;
		}
	}
	float degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}
	bool proverkanapidora = false;


}


void weapons_tick() {
	hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
	if (!LocalPlayer)
		return;
	hk_WeaponManager* WeaponManager = LocalPlayer->WeaponManager();
	if (!WeaponManager)
		return;
	hk_WeaponInfo* WeaponInfo = WeaponManager->WeaponInfo();
	if (!WeaponInfo)
		return;
	//if (Config::ExplosiveAmmo)
	//{
	//	WeaponInfo->SetAmmoType(0x5);
	//	WeaponInfo->SetAmmoExplosiveType(0x1);
	//}
	if (amphetamine::amphetamine_settings->NoReload)
	{
		WeaponInfo->SetReload(1000);
	}
	hk_AmmoInfo* AmmoInfo = WeaponInfo->AmmoInfo();
	if (!AmmoInfo)
		return;
	hk_AmmoCount* AmmoCount = AmmoInfo->AmmoCount();
	if (!AmmoCount)
		return;
	hk_FixedAmmoCount* FixedAmmoCount = AmmoCount->FixedAmmoCount();
	if (!FixedAmmoCount)
		return;
	if (amphetamine::amphetamine_settings->InfiniteAmmo)
	{
		FixedAmmoCount->SetAmmo(9999);
	}
	/*if (Config::rapidfire)
	{
		AmmoInfo->SetSpeedBullet(20000);
	}*/
}
D3DXVECTOR3 MainPosition;
void Set_Position()
{
	if (MainPosition.x == 0 && MainPosition.y == 0) return;
	if (Memory::Check::In_Vehicle())
	{
		DWORD64 curveh = *(DWORD64*)(Memory::LocalPlayer + 0xD30);
		if (curveh != 0) {
			DWORD64 posbase = *(DWORD64*)(curveh + 0x30);
			*(D3DXVECTOR3*)(posbase + 0x50) = MainPosition;
			*(D3DXVECTOR3*)(curveh + 0x90) = MainPosition;
		}
	}
	else
	{
		DWORD64 posbase = *(DWORD64*)(Memory::LocalPlayer + 0x30);
		*(D3DXVECTOR3*)(posbase + 0x50) = MainPosition;
		*(D3DXVECTOR3*)(Memory::LocalPlayer + 0x90) = MainPosition;
		uintptr_t dpos = *(uintptr_t*)(Memory::LocalPlayer + 0x30);
		D3DXVECTOR3 vec = *(D3DXVECTOR3*)(dpos + 0x50);
		*(D3DXVECTOR3*)(Memory::LocalPlayer + 0x90) = MainPosition;
	}
}
bool fastrunproverka = false;
void Set_Godmode(uint8_t value)
{
	*(uint8_t*)(Memory::LocalPlayer + 0x0189) = value;
}
bool proverkanapidoraakawaypoint = false;
bool proverkanapidorskipanim = false;
enum eFrameFlags : std::uint32_t
{
	eFrameFlagExplosiveAmmo = 1 << 3,
	eFrameFlagFireAmmo = 1 << 4,
	eFrameFlagExplosiveMelee = 1 << 5,
	eFrameFlagSuperJump = 1 << 6,
};
void WriteFlameFlagMelee(uint32_t Flag)
{
	uint32_t CurrentValue = get_value<uint32_t>({ 0x8, 0x10A8, 0x219 }); //0x10B8
	set_value<uint32_t>({ 0x8, 0x10A8, 0x219 }, CurrentValue |= Flag);
}
void RemoveFlameFlagMelee(uint32_t Flag)
{
	uint32_t CurrentValue = get_value<uint32_t>({ 0x8, 0x10A8, 0x219 }); //0x10B8
	set_value<uint32_t>({ 0x8, 0x10A8, 0x219 }, CurrentValue &= ~(1 << Flag));
}
bool proverkaexplosive_melee = false;
void explosive_melee(bool toggle)
{
	if (toggle)
	{
		WriteFlameFlagMelee(eFrameFlagExplosiveMelee);
		proverkaexplosive_melee = true;
	}
	else
	{
		if (proverkaexplosive_melee == true) {
			RemoveFlameFlagMelee(eFrameFlagExplosiveMelee);
			proverkaexplosive_melee = false;
		}
	}
}

void load_ground_and_tp_to(Vector3& location)
{
	auto player = PLAYER::PLAYER_PED_ID();

	if (!GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 100.f, &location.z, false))
	{
		static const float groundCheckH[] = {
			0.f, 50.f, 100.f, 150.f,  200.f, 250.f, 300.f, 350.f, 400.f,
				450.f, 500.f, 550.f, 600.f, 650.f, 700.f, 750.f, 800.f
		};


		//Loop trough all the step to check the ground distance
		//Then it load the collision and all the object near
		//Then set the position height so the player don't spawn under the map.
		for (auto const height : groundCheckH)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, location.x, location.y, height, false, false, false);


			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, height, &location.z, false))
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, height);
				STREAMING::LOAD_ALL_OBJECTS_NOW();
				location.z += 3.f;
				break;
			}
		}
	}

	auto playerHeading = ENTITY::GET_ENTITY_HEADING(player);
	ENTITY::SET_ENTITY_COORDS(player, location.x, location.y, location.z, false, false, true, false);
	ENTITY::SET_ENTITY_HEADING(player, playerHeading);

	//printf("Player teleported to : %f %f %f\n", location.x, location.y, location.z);
}


void tp_to_waypoint()
{
	auto blip = UI::GET_FIRST_BLIP_INFO_ID(8);

	if (!UI::DOES_BLIP_EXIST(blip))
	{
	//	printf("Waypoint not foud !\n");
		return;
	}

	//Get the waypoint coords :
	auto waypoint = UI::GET_BLIP_COORDS(blip);
	load_ground_and_tp_to(waypoint);
}

#define IsValidPtr(x) (x && !IsBadReadPtr(&x, sizeof(void*) && x != nullptr && x > nullptr))

float SquareRootFloat(float number) {
	long i;
	float x, y;
	const float f = 1.5F;

	x = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (f - (x * y * y));
	y = y * (f - (x * y * y));
	return number * y;
}

float get_distance(Vector3 to, Vector3 from) {
	return (SquareRootFloat(
		((to.x - from.x) * (to.x - from.x)) +
		((to.y - from.y) * (to.y - from.y)) +
		((to.z - from.z) * (to.z - from.z))
	));
}

static bool was_no_veh_collision_set = false;
void do_veh_no_collision() {
	try {
		//bool is_in_vehicle = native::ped::is_ped_in_any_vehicle(native::player::player_ped_id(), false);
		//if (is_in_vehicle) {
		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
		if (IsValidPtr(ReplayInterface)) {
			Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
			//type::any lp_veh = native::ped::get_vehicle_ped_is_in(native::player::get_player_ped(-1), false);

			type::any lp_veh = rage::native::ped::is_ped_in_any_vehicle(rage::native::player::player_ped_id(), false) ? native::ped::get_vehicle_ped_is_in(native::player::get_player_ped(-1), false) : rage::native::player::player_ped_id();


			if (amphetamine::amphetamine_settings->vehicle_collision) {
				hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
				if (IsValidPtr(VehicleInterface)) {
					for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {
						if (auto vehicle = VehicleInterface->VehicleList()->Vehicle(i)) {
							if (IsValidPtr(vehicle)) {
								float dist = get_distance(localpos, vehicle->GetCoordinate());
								if (dist > 20.f) continue;
								auto veh_handle = Memory::pointer_to_handle((uintptr_t)vehicle);
								if (veh_handle) {
									native::entity::set_entity_no_collision_entity(veh_handle, lp_veh, false);
								}
							}
						}
					}
				}
				was_no_veh_collision_set = true;
			}
			else if (was_no_veh_collision_set && !amphetamine::amphetamine_settings->vehicle_collision) {
				hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
				if (IsValidPtr(VehicleInterface)) {
					for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {
						if (auto vehicle = VehicleInterface->VehicleList()->Vehicle(i)) {
							if (IsValidPtr(vehicle)) {
								float dist = get_distance(localpos, vehicle->GetCoordinate());
								if (dist > 20.f) continue;
								auto veh_handle = Memory::pointer_to_handle((uintptr_t)vehicle);
								if (veh_handle) {
									native::entity::set_entity_no_collision_entity(veh_handle, lp_veh, true);
								}
							}
						}
					}
				}

				was_no_veh_collision_set = false;
			}
		}
		//}
	}
	catch (const std::exception& e) { /* */
		//logs::add(enc("error in updating vehicle collision"));
		//logs::add(e.what());
	}

}
void vehicle_no_collisioon() {

	if (amphetamine::amphetamine_settings->vehicle_collision || was_no_veh_collision_set) {
		do_veh_no_collision();
	}
}

void no_collision_object() {
	try {
		if (amphetamine::amphetamine_settings->collision || amphetamine::amphetamine_settings->collision_players) {
			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
			if (IsValidPtr(ReplayInterface)) {

				auto handle = rage::native::ped::is_ped_in_any_vehicle(rage::native::player::player_ped_id(), false) ? rage::native::player::get_players_last_vehicle() : rage::native::player::player_ped_id();

				Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);


				if (amphetamine::amphetamine_settings->collision_players) {
					for (int i = 0; i < ReplayInterface->PedInterface()->PedMaximum(); i++) {
						if (auto ped = ReplayInterface->PedInterface()->get_ped(i)) {
							Vector3 GetCoordinate = *(Vector3*)(ped + 0x90);
							float dist = get_distance(localpos, GetCoordinate);
							if (dist > 10.f) continue;
							if ((DWORD64)ped == Memory::LocalPlayer)
								continue;

							rage::native::entity::set_entity_no_collision_entity(Memory::pointer_to_handle(std::uintptr_t(ped)), handle, true);
						}
					}
				}


				static bool no_collision_obj{ false };
				if (amphetamine::amphetamine_settings->collision) {
					uintptr_t ObjectReplayInterface = *(uintptr_t*)(ReplayInterface + 0x28);
					if (ObjectReplayInterface != 0) {
						int maxpickups = *(int*)(ObjectReplayInterface + 0x160);
						uintptr_t ObjectList = *(uintptr_t*)(ObjectReplayInterface + 0x0158);
						no_collision_obj = true;
						for (int i = 0; i < maxpickups; i++) {
							if (auto object = *(uintptr_t*)(ObjectList + (i * 0x10))) {
								Vector3 GetCoordinate = *(Vector3*)(object + 0x90);
								float dist = get_distance(localpos, GetCoordinate);
								if (dist > 20.f) continue;

								rage::native::entity::set_entity_no_collision_entity(Memory::pointer_to_handle(std::uintptr_t(object)), handle, true);
							}
						}
					}
				}
				else {
					if (no_collision_obj) {
						uintptr_t ObjectReplayInterface = *(uintptr_t*)(ReplayInterface + 0x28);
						if (ObjectReplayInterface != 0) {
							int maxpickups = *(int*)(ObjectReplayInterface + 0x160);
							uintptr_t ObjectList = *(uintptr_t*)(ObjectReplayInterface + 0x0158);
							for (int i = 0; i < maxpickups; i++) {
								if (auto object = *(uintptr_t*)(ObjectList + (i * 0x10))) {
									Vector3 GetCoordinate = *(Vector3*)(object + 0x90);
									float dist = get_distance(localpos, GetCoordinate);
									if (dist > 20.f) continue;

									rage::native::entity::set_entity_no_collision_entity(Memory::pointer_to_handle(std::uintptr_t(object)), handle, true);
								}
							}
							no_collision_obj = false;
						}
					}
				}
			}
		}
	}
	catch (const std::exception& e) { /* */

		//logs::add(enc("error in updating vehicle collision"));
		//logs::add(e.what());
	}
}
void superjump(bool toggle)
{
	if (toggle) {
		auto playerPed = player::get_player_ped_script_index(player::player_id());
		gameplay::set_super_jump_this_frame(player::player_id());
		gameplay::set_super_jump_this_frame(playerPed);
	}
}

void players_tick() {
	hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
	if (!LocalPlayer)
		return;
	hk_PlayerInfo* PlayerInfo = LocalPlayer->PlayerInfo();
	if (!PlayerInfo)
		return;

	//explosive_melee(Config::explosive_melee);
	if (amphetamine::amphetamine_settings->explosive_melee) {
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player::player_id());
	}

	if (amphetamine::amphetamine_settings->fire_ammo) {
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player::player_id());
	}
	/*superjump(Config::SuperJump);
	if (Config::customtime) {
		network::network_override_clock_time(Config::customtimesize, 0, 0);
	}*/
	if (amphetamine::amphetamine_settings->God_Mode)
	{
		Set_Godmode(0x1);
	}
	if (amphetamine::amphetamine_settings->fastrun)
	{
		fastrunproverka = true;
		player::set_run_sprint_multiplier_for_player(player::player_id(), 1.49); //SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER
	}
	else
	{
		if (fastrunproverka == true) {
			player::set_run_sprint_multiplier_for_player(player::player_id(), 1.00);
			fastrunproverka = false;
		}
	}
	if (amphetamine::amphetamine_settings->TpToWaypoint) {
		if (GetAsyncKeyState(amphetamine::amphetamine_settings->TpToWaypointkey) & 0x8000) {
			if (proverkanapidoraakawaypoint == false) {


				Vector3 pos;
				rage::native_queue->native_emplace([] {
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

				proverkanapidoraakawaypoint = true;
			}
		}
		else {
			proverkanapidoraakawaypoint = false;
		}

		//Config::TpToWaypoint = false;
	}

	
	//if (Config::anticuff) {
	//	brain::uncuff_ped(PLAYER::PLAYER_PED_ID());
	//}


	//if (Config::skipanimaka) {
	//	if (GetAsyncKeyState(Config::TpToWaypointkey) & 0x8000) {
	//		if (proverkanapidorskipanim == false) {
	//			rage::native_queue->native_emplace([&]
	//				{

	//					//tp_to_waypoint();

	//					brain::clear_ped_secondary_task(PLAYER::PLAYER_PED_ID());
	//					brain::clear_ped_secondary_task(player::player_id());


	//					brain::stop_anim_playback(PLAYER::PLAYER_PED_ID(), 0, false);
	//					brain::stop_anim_playback(player::player_id(), 0, false);

	//				}
	//			);
	//			proverkanapidorskipanim = true;
	//		}
	//	}
	//	else {
	//		proverkanapidorskipanim = false;
	//	}
	//}

}
bool speedhackvehicle_proverka = false;
bool gravityhackvehicle_proverka = false;

void Vehicle_r::Tick()
{
	hk_World* World = (hk_World*)*(uint64_t*)(Memory::World);
	if (!World)
		return;
	hk_Ped* LocalPlayer = (hk_Ped*)Memory::LocalPlayer;
	if (!LocalPlayer)
		return;
	hk_Vehicle* ActualVehicle = LocalPlayer->VehicleManager();
	if (!ActualVehicle)
		return;

	if (amphetamine::amphetamine_settings->update_plate)
	{
		rage::native_queue->native_emplace([&]
			{
				auto current_vehicle = ped::get_vehicle_ped_is_in(player::player_ped_id(), true);
				vehicle::set_vehicle_number_plate_text(current_vehicle, amphetamine::amphetamine_settings->plate_text);
			}
		);
		amphetamine::amphetamine_settings->update_plate = false;
	}


	if (amphetamine::amphetamine_settings->speedhackVehicle)
	{
		speedhackvehicle_proverka = true;
		ActualVehicle->VehicleHandlingInfo()->SetAcceleration(amphetamine::amphetamine_settings->speedmultiplier);
	}
	else
	{
		if (speedhackvehicle_proverka == true) {
			ActualVehicle->VehicleHandlingInfo()->SetAcceleration(1.0f);
		}
	}
	if (amphetamine::amphetamine_settings->gravityhackVehicle)
	{
		gravityhackvehicle_proverka = true;
		ActualVehicle->SetGravity(amphetamine::amphetamine_settings->gravitymultiplier);
	}
	else
	{
		if (gravityhackvehicle_proverka == true)
		{
			ActualVehicle->SetGravity(9.7f);
		}
	}


	if (amphetamine::amphetamine_settings->godmode_vehicle) {
		*(uintptr_t*)(ActualVehicle + 0x189) = 1;
		*(float*)(ActualVehicle + 0x280) = 1000;
		*(float*)(ActualVehicle + 0x0820) = 1000;
		*(float*)(ActualVehicle + 0x0824) = 1000;
		*(float*)(ActualVehicle + 0x08E8) = 1000;
	}





	//	//if (Config::Fix_On_damage)
	//	//{

	//	//	vehicle::set_vehicle_deformation_fixed(current_vehicle); //SET_VEHICLE_DEFORMATION_FIXED

	//	//	ActualVehicle->SetEngineHealth(1000);
	//	//	ActualVehicle->SetBodyHealth(1000);

	//	//	Config::Fix_On_damage = false;
	//	//}
	//}
}

bool health_otmena = false;
bool armor_otmena = false;
bool scipanim_otmena = false;



namespace MiscFunk {
	void MiscF() {
		//	Hook();
			//weapon_one_shoot_kill();
		NoRecoil();
		NoSpread();
		//Memory::LocalPlayer

		//if () {
		//	hk_Ped* Peds = (hk_Ped*)Memory::LocalPlayer;
		//	hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
		//	if (PedsWeaponManager != 0) {
		//		hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
		//		if (PedsWeaponInfo) {
		//			//uint64_t Hash = PedsWeaponInfo->GetHash();

		//			*(float*)((DWORD64)PedsWeaponInfo + 0xB0) = dmg;
		//		}
		//	}
		//}

		if (amphetamine::amphetamine_settings->skipanimaka) {
			if (GetAsyncKeyState(amphetamine::amphetamine_settings->skip_anim_bind) & 0x8000) {
				if (scipanim_otmena == false) {

					
					rage::native_queue->native_emplace([&]
						{
							brain::clear_ped_tasks_immediately(player::player_ped_id());
						});


					scipanim_otmena = true;
				}
			}
			else {
				scipanim_otmena = false;
			}
		}

		if (amphetamine::amphetamine_settings->autoanimstoper) {
			rage::native_queue->native_emplace([] {
				Ped ped = player::player_ped_id();
				auto pos = entity::get_entity_coords(ped, false); //GET_ENTITY_COORDS
				float z = 0.0f;
				native::gameplay::get_ground_z_for_3d_coord(pos.x, pos.y, pos.z, &z, false);
				if (ped::is_ped_ragdoll(ped) && !ped::is_ped_falling(ped)) {
					brain::clear_ped_tasks_immediately(ped);

				}
				if (ped::is_ped_falling(ped) && z + 1 > pos.z - 1) {
					brain::clear_ped_tasks_immediately(ped);
				}
				});
		}

		if (amphetamine::amphetamine_settings->healcheck) {
			if (amphetamine::amphetamine_settings->healkey != 0) {
				if (GetAsyncKeyState(amphetamine::amphetamine_settings->healkey) & 0x8000) {
					if (health_otmena == false) {

						Set_Health(200.0f);

						health_otmena = true;
					}
				}
				else {
					health_otmena = false;
				}
			}
		}


		if (amphetamine::amphetamine_settings->armorhcheck) {
			if (amphetamine::amphetamine_settings->armorkey != 0) {
				if (GetAsyncKeyState(amphetamine::amphetamine_settings->armorkey) & 0x8000) {
					if (armor_otmena == false) {

						Set_Armor(200.0f);

						armor_otmena = true;
					}
				}
				else {
					armor_otmena = false;
				}
			}
		}

		if (amphetamine::amphetamine_settings->Semi_Godmod)
		{
			if (amphetamine::amphetamine_settings->Semi_Godmod_on_key) {
				if ((GetAsyncKeyState(amphetamine::amphetamine_settings->Semi_Godmod_bind) & 1))
				{
					global::semi_godmode = !global::semi_godmode;
				}
				if (global::semi_godmode) {
					if (Memory::Check::isPlayerValid()) {
						float getmaxhp = *(float*)(Memory::LocalPlayer + 0x2A0);
						if (getmaxhp < 200)
						{
							*(float*)(Memory::LocalPlayer + 0x280) = 200;
						}
					}
				}
			}
			else {
				if (Memory::Check::isPlayerValid()) {
					float getmaxhp = *(float*)(Memory::LocalPlayer + 0x2A0);
					if (getmaxhp < 200)
					{
						*(float*)(Memory::LocalPlayer + 0x280) = 200;
					}
				}
			}


		}
		//VEHICLE
		/*if (Config::Fix_On_damage)
		{
			VehicleQ::Set_Health(1000.0f, 1000.0f, 65.0f);
		}*/
		/*if (Config::speedhackVehicle)
		{
			VehicleQ::Set_Acceleration(1.0f * Config::speedmultiplier);
			VehicleQ::Set_Gravity((9.7f * Config::speedmultiplier) / 2);
			proverkanapidoraspeed = true;
		}
		else
		{
			if (proverkanapidoraspeed == true) {
				VehicleQ::Set_Acceleration(1.0f);
				VehicleQ::Set_Gravity(9.7f);
				proverkanapidoraspeed = false;
			}
		}*/
		if (amphetamine::amphetamine_settings->EnableFovChange)
		{
			DWORD64 addr = Memory::GetCameraqw();
			uintptr_t CameraData = *(uintptr_t*)(addr + 0x10);
			*(float*)(CameraData + 0x30) = amphetamine::amphetamine_settings->FovValue;
		}


	}
}
