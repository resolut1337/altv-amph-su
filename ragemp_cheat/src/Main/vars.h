#pragma once
typedef unsigned long ulong_t;
typedef HRESULT(*Present)(IDXGISwapChain*, UINT, UINT);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

namespace global {
	int ScreenHeight = 0;
	int ScreenWidth = 0;

	bool Panic = false;
	bool Panicnoclear = false;
	bool init, show = false;
	bool noclip_bind = false;
	bool semi_godmode = false;
}
#include"map"
namespace amphetamine {
	class settings_t {
	public:
		/*bool SaveCFG(std::string file_name);
		bool LoadCFG(std::string file_name);*/
		void upload_cfg(const std::string name_cfg);
		void copy_shared_code_cfg(const std::string name_cfg);
		void shared_cfg_add(const std::string shared_key);
		void load_cloud_cfg(const std::string name_cfg);

		float freecam_fov = 60.f;
		float freecam_speed = 2.f;
		bool radarhack_weapons = false;
		int Silenthitchance = 1;
		bool anticuff = false;
		bool slaper = false;
		int slaper_key = 0;

		int damager_key = 0;
		int lastShot = 0;
		float maxRange = 500.0f;
		float _maxRange = 500.0f;
		int maxRangeT = 500;
		int shootRate = 200;
		bool shootCounter = false;
		int shotCount = 0;
		int shotLimit = 30;
		float _shotLimit = 30.0f;
		float __shotLimit = 30.0f;
		bool shotLimiter = false;




		bool damager = false;
		bool clickwarpvehicle = false;
		int clickwarp_vehicle_int_hot_key = 0;

		bool is_ped_is_any_vehicle = false;
		bool fire_ammo = false;
		bool explosive_melee = false;
		bool radarhack = false;

		/*RADAR*/
		float radar_range = 150;
		float radar_point_size_proportion = 1;
		bool show_radar_crossline = false;
		ImColor radar_crossline_color = ImColor(255, 255, 255, 255);
		int radar_type = 2;
		float proportion = 3300;
		bool custom_radar = true;
		float radar_bg_alpha = 0.1;
		/*///////////////////////////////////*/



		int TpToWaypointkey = 0;
		bool clickflipvehicle = false;
		int clickflipvehiclekey = 0;

		bool Draw_botvisuals = false;


		bool Draw_botsaim = false;
		bool Draw_Animalsaimbot = false;
		bool Silent_Aimhotkey = false;
		int trigetbotHotkey = 0;
		bool TriggerBot = false;
		bool emulator_mouse_aim = false;
		int int_emul_mouse_aim = 0;
		bool VisibleCheck = true;
		bool debugcamera = false;
		float m_gravityvelocity{ 3.f };
		bool gravitygun = false;
		
	
		bool vehicle_collision = false;
		bool isSlideRun = false;
		bool thermalvision = false;
		bool nightmode = false;
		bool superbrakes = false;
		bool autoflipvehicle = false;
		bool driftmode = false;
		bool vehicleinvisible = false;
		bool AlwaysRagdoll = false;
		bool RainBowweapon = false;

		bool nofall = false;
		bool ghostmode = false;
		int AimbotSmooth = 1;
		bool getvehicllenumberplates = false;
		bool enginealwayson = false;
		bool slowmo = false;
		bool Flyhackcar = false;

		bool rainbowbox = false;
		bool customtime = false;
		int customtimesize = 10;
		//bool player_superpunch = false;


		int tp_crosshair_bind = 0;
		bool tp_crosshair = false;

		bool SuperJump = false;
		bool fastrun = false;
		bool rapidfire = false;
		bool InfiniteAmmo = false;
		bool NoReload = false;
		bool ExplosiveAmmo = false;
		bool update_plate = false;
		bool untrusted_build = false;
		bool TpToWaypoint = false;
		bool skipanimaka = false;
		int skip_anim_bind = 0;
		//bool AntiHS = false;
		bool InVisible = false;
		bool collision = false;
		bool collision_players = false;

		bool godmode_vehicle = false;
		bool shift_boost_speed = false;
		bool enablevehicle = false;
		char plate_text[8] = "";
		char plate_textgetveh[8] = "";
		float FovValue = 50;
		bool EnableFovChange = false;
		bool one_shoot_kill = false;
		int fontsize = 15;
		bool unlock_doors_car = false;
		int speedmultiplier = 0;
		bool speedhackVehicle = false;

		bool gravityhackVehicle = false;
		int gravitymultiplier = 4;
		bool Fix_On_damage = false;
		int autorepair = 0;
		bool healcheck = false;
		
		bool armorhcheck = false;
		int armorkey = 0;
		int healkey = 0;

		bool isMenuVisible = false;
		int Current_Tab = 0;

		int OpenMenuKey = 23;
		bool God_Mode = false;
		bool NoGravity = false;
		bool Invisible = false;
		bool NoRagdoll = false;
		bool Seatbelt = false;
		bool Crosshair = false;
		bool Wanted = false;
		bool VehicleEsp = false;
		bool VehicleEsp_Name = false;
		bool VehicleEsp_Distance = false;
		bool VehicleEsp_3Dbox = false;
		bool ObjectESP = false;

		int Max_Aimbot_Distance = 250;
		bool Aimbot_Toggle = false;
		bool Silent_Aim = false;



		int Aimbot_Type = 0;
		int Aimbot_Smooth = 0;
		bool Aimbot_HorizontalOnly = false;
		int Aimbot_Fov = 10;
		int max_distance_aim = 400;
		float Aimbot_Prediction = 0.05f;
		bool DrawFov = false;
		ImColor Fov_Color = ImColor(255, 22, 192);
		ImColor Name_Color = ImColor(255, 22, 192);
		ImColor Name_Color_vehicle = ImColor(0, 22, 192);
		ImColor Name_Color_invisible = ImColor(0, 22, 192);


		ImColor invisibleDist_Color = ImColor(0, 22, 192);

		ImColor Dist_Color = ImColor(255, 22, 192);
		ImColor Distance_Color = ImColor(255, 22, 192);
		ImColor SnapLines_Color = ImColor(255, 22, 192);
		ImColor Skeleton_Color = ImColor(255, 22, 192);
		ImColor Box_Color = ImColor(255, 22, 192);
		ImColor object_color = ImColor(255, 22, 192);


		int Aimbot_Bone = 0;
		bool Aimbot_VisibleCheck = false;

		bool No_Recoil = false;
		bool No_Spread = false;
		bool Fast_Reload = false;
		bool Super_Velocity = false;
		bool Super_Dmg = false;
		bool Sniper_Range = false;
		bool Rapide_Fire = false;
		bool Bullet_Type = false;
		int WeaponSpawn = 0;
		int WeaponSpawnAmmo = 0;

		bool Veh_God_Mode = false;
		bool Veh_Impulse = false;
		bool UseLockedCars = false;
		bool StartEngineCars = false;
		bool DrawLastVeh = false;

		bool Npc_Esp = false;
		bool Npc_IncludeSelf_Esp = false;
		bool Npc_IncludeNpc_Esp = false;
		int Npc_Max_Distance = 600;
		bool Npc_Name_Esp = false;
		bool Npc_Box_Esp = false;
		int Npc_Box_Esp_Type = 0;
		bool Npc_Health_Esp = false;

		bool LocalPlayerEsp = false;


		bool Npc_Weapon_Esp = false;
		bool Npc_Distance_Esp = false;
		bool Name = false;
		bool Npc_Barrel_Esp = false;
		bool Npc_Snapline_Esp = false;
		bool Npc_Bone_Esp = false;
		bool Npc_Full_Bone_Esp = false;
		bool Npc_HeadDot_Esp = false;
		float Npc_HeadDot_Size = 1.25f;

		bool Toggle_2D_Radar = false;

		bool UseRayCast = false;
		bool NoClip = false;
		float NoClipSpeed = 1.025f;
		bool FlyHack = false;
		float FlySpeed = 1.025f;

		int silenthotkeyaim = 0;
		int HotKeyAim = 2;
		int HotKeyAim2 = 2;
		int HotKeyFly = 0;
		int HotKeyNoClip = 0;
		int HotKeyTeleportToWayP = 0;
		int HotKeyResetHealth = 0;
		int HotKeyResetArmour = 0;
		int HotKeyFlipVeh = 0;
		int HotKeyVehImpulseIncreace = 0;
		int HotKeyVehImpulseDecrease = 0;
		int HotKeyVehImpulseConstant = 0;














		float Box_col[4] = { 255.f, 255.f, 255.f, 255.f };
		float BoxVisible[4] = { 255.f, 255.f, 255.f, 255.f };

		float Corner_col[4] = { 33.f, 140.f, 176.f, 255.f };
		float CornerVisible[4] = { 33.f, 140.f, 176.f, 255.f };

		float Fov[4] = { 255.f, 255.f, 255.f, 255.f };
		float Skeleton_col[4] = { 255.f, 255.f, 255.f, 255.f };
		float SkeletonVisible[4] = { 255.f, 255.f, 255.f, 255.f };

		float Menu[4] = { 255.f, 255.f, 255.f, 255.f };






		bool Godmod = false;
		bool Semi_Godmod = false;
		int Semi_Godmod_bind = 0;
		bool Infinite_Armor = false;
		bool SetHealth = false;

		bool SetArmor = false;
		int RunSpeedToSet = 1;

		int HealthToSet = 100;
		int ArmorToSet = 100;
		int noclipspeed = false;
		int isNoclipWorking = true;
		bool Infinite_stamina = false;
		int HotkeyArmor = 0;
		int HotkeyHealth = 0;
		bool flymode = false;
		int ForwardHotkey = 90;
		int BackwardHotkey = 0x53;



		bool NoRagDoll = false;
		bool Nofallfrombike = false;

		bool NoClipSpeed_bool = false;
		float Speed = 0.4f;
		bool Gravity = false;
		bool AirStuck = false;
		int Airstuck_hotkey = 0;
		bool godnoclip = false;



		bool menu = true;
		bool customization = false;
		bool informations = false;
		bool isPanic = false;
		int Menu_Hotkey = 45;
		bool PlayerList = false;
		bool PedList = false;
		bool VehicleList = false;

		int NoclipKey = 0;
		bool security_1 = false;
		bool security_2 = false;
		char cfg_name[10] = "";
		bool EnableChat = false;



		bool rainbowbox_LocalPlayer_esp = false;
		bool enable_localplayeresp_LocalPlayer_esp = false;
		bool name_LocalPlayer_esp = false;
		bool weapon_LocalPlayer_esp = false;
		bool distance_LocalPlayer_esp = false;
		int combo_box_LocalPlayer_esp = 0;
		float BoxSize_LocalPlayer_esp = 1;
		bool Filled_box_LocalPlayer_esp = false;
		bool skeleton_LocalPlayer_esp = false;
		ImColor Box_Color_LocalPlayer_esp = ImColor(255, 22, 192);
		ImColor SkelColor_LocalPlayer_esp = ImColor(255, 255, 255, 255);
		ImColor invisibleSkelColor_LocalPlayer_esp = ImColor(0, 255, 255, 255);
		ImColor invisibleDist_Color_LocalPlayer_esp = ImColor(0, 22, 192);
		ImColor Dist_Color_LocalPlayer_esp = ImColor(255, 22, 192);
		ImColor Name_Color_LocalPlayer_esp = ImColor(255, 22, 192);
		ImColor Name_Color_invisible_LocalPlayer_esp = ImColor(0, 22, 192);
		bool ArmorBar_LocalPlayer_esp = false;
		int HealthBar_idx_LocalPlayer_esp = 4;
		int combo_skeleton_LocalPlayer_esp = 0;



		bool object_esp_all = false;
		bool object_dist_esp = false;
		bool object_esp = false;
		bool enable = false;
		bool Box = false;
		bool Filled = false;
		bool Corner = false;
		bool TroiDBox = false;
		bool Skeleton = false;
		bool Snapline = false;
		bool flags = false;
		bool HealthBar = false;
		bool ArmorBar = false;
		bool Weapon = false;
		bool DistanceESP = false;
		bool NameEsp = false;
		bool PreviewEsp = false;
		bool tpped = false;
		bool invisibleped = false;
		bool killped = false;
		bool PlayerName = false;

		float CornerSize = 1;
		float BoxSize = 0.7;

		int Skeleton_idx = 0;
		int HealthBar_idx = 4;
		bool HealthBar_Multicolor = false;

		bool oofindicators_players = false;
		bool oofindicators_players_weapon = false;
		bool Skeleton_Detailled = false;
		bool Keybinds = false;
		bool Watermark = false;
		bool Draw_npc_esp = false;
		bool Draw_LocalPlayer = false;
		bool Draw_Dead = false;
		bool Draw_Ped = false;
		bool Draw_Animals = false;
		bool StaticESP = false;

		int Distance = 200;

		int DistanceVehicle = 150;

		int DistanceObject = 150;

		bool autoanimstoper = false;

		int FillBoxAlpha = 75;

		ImColor FovColor = ImColor(255, 255, 255, 255);
		ImColor BoxColor = ImColor(255, 255, 255, 255);
		ImColor BoxColorVisible = ImColor(252, 3, 23, 255);

		ImColor CornerColor = ImColor(33, 140, 176, 255);
		ImColor CornerColorVisible = ImColor(252, 3, 23, 255);

		ImColor SkelColor = ImColor(255, 255, 255, 255);

		ImColor invisibleSkelColor = ImColor(0, 255, 255, 255);


		ImColor SkelColorVisible = ImColor(252, 3, 23, 255);

		ImColor MenuColor = ImColor(255, 255, 255, 255);

		float textsize = 12.f;
		int aimmode = 0;

		int key_menu_global = VK_DELETE;

		bool clickwarp = false;
		int clickwarp_key = 0;
		bool auto_pilot = false;
		bool Semi_Godmod_on_key = false;
	};
	inline const auto amphetamine_settings = std::make_unique< settings_t >();
}