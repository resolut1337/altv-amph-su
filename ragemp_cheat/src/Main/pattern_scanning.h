enum IntersectOptions {
	IntersectEverything = -1,
	IntersectMap = 1,
	IntersectVehicles = 2,
	IntersectPeds1 = 4,
	IntersectPeds2 = 8,
	IntersectObjects = 16,
	IntersectVegetation = 256
};
namespace Memory
{
	DWORD LocalPlayerHandle = 0x0;
	//DWORD64 BASE = 0x0;

	typedef DWORD(__cdecl* tSTART_SHAPE_TEST_CAPSULE)(PVector3 From, PVector3 To, float radius, IntersectOptions flags, DWORD entity, int p9);
	tSTART_SHAPE_TEST_CAPSULE _START_SHAPE_TEST_CAPSULE = nullptr;

	//

	typedef BOOLEAN(__cdecl* WorldToScreen_t)(Vector3* WorldPos, float* x, float* y);
	typedef BOOL(__fastcall* fpRemoveWeaponFromPed)(DWORD ped, DWORD hash);
	typedef DWORD64(__fastcall* fpSetVehicleOnGroundProperly)(DWORD vehicle, DWORD unk);
	typedef DWORD64(__fastcall* SetVehicleForwardSpeed_t)(DWORD vehicle, float Speed);
	typedef DWORD64(__fastcall* fpGiveDelayedWeaponToPed)(DWORD ped, DWORD hash, int ammo, bool equipNow);
	typedef DWORD64(__fastcall* tSTART_SHAPE_TEST_RAY)(PVector3 From, PVector3 To, unsigned int flags, unsigned int entity, DWORD64* a8, DWORD64 a9);
	
	typedef int(__fastcall* CLEAR_PED_TASKS_IMMEDIATELY_t)(DWORD ped);
	typedef DWORD64(__fastcall* CLEAR_PED_TASKS_t)(DWORD HandleOfPed);
	typedef DWORD64(__fastcall* fpSetVehiclePlateText)(DWORD vehicle, const char* Text);

	typedef int(__cdecl* t_GET_RAYCAST_RESULT)(DWORD Handle, bool* hit, rage::padvec3* endCoords, rage::padvec3* surfaceNormal, DWORD* entityHit);
	static t_GET_RAYCAST_RESULT _GET_RAYCAST_RESULT = nullptr;

	WorldToScreen_t World2Screen = nullptr;
	fpRemoveWeaponFromPed RemoveWeaponFromPed = nullptr;
	fpSetVehicleOnGroundProperly pSetVehicleOnGroundProperly = nullptr;
	SetVehicleForwardSpeed_t SetVehicleForwardSpeed = nullptr;
	static fpGiveDelayedWeaponToPed GiveDelayedWeaponToPed = nullptr;
	tSTART_SHAPE_TEST_RAY _START_SHAPE_TEST_RAY = nullptr;

	CLEAR_PED_TASKS_IMMEDIATELY_t oCLEAR_PED_TASKS_IMMEDIATELY = NULL;
	CLEAR_PED_TASKS_t CLEAR_PED_TASKS = nullptr;
	fpSetVehiclePlateText pSetVehiclePlateText = nullptr;

	DWORD64 pGameCamManager;
	DWORD64 World;
	DWORD64 LocalPlayer;
	DWORD64 NPCTEST;
	DWORD64 LocalPlayerInfo;
	DWORD64 Camera;
	DWORD64 playerlist;
	DWORD64 ReplayInterface;
	DWORD64 WeaponBase;
	DWORD64 BonePositionAddress;
	DWORD64 BlipPointer;
	DWORD64 FlyPatt;

	CViewPort* viewPort = nullptr;
	//DWORD64 CPedFactoryPointer;
	//functions
	//ImVec2 WorldToScreen(Vector3 WorldPos)
	//{
	//	ImVec2 pos;
	//	if (Helper::ValidPTR((DWORD64)World2Screen))
	//	{
	//		if (static_cast<BOOLEAN>(World2Screen(&WorldPos, &pos.x, &pos.y)))
	//		{
	//			pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
	//			pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
	//			return pos;
	//		}
	//	}
	//	return pos;
	//}


	ImVec2 WorldToScreen(Vector3 pos) {
		if (Helper::ValidPTR((DWORD64)viewPort)) {
			ImVec2 out = ImVec2(0, 0);
			Vector3	tmp;

			tmp.x = (viewPort->fViewMatrix[1] * pos.x) + (viewPort->fViewMatrix[5] * pos.y) + (viewPort->fViewMatrix[9] * pos.z) + viewPort->fViewMatrix[13];		//row 2
			tmp.y = (viewPort->fViewMatrix[2] * pos.x) + (viewPort->fViewMatrix[6] * pos.y) + (viewPort->fViewMatrix[10] * pos.z) + viewPort->fViewMatrix[14];	//row 3
			tmp.z = (viewPort->fViewMatrix[3] * pos.x) + (viewPort->fViewMatrix[7] * pos.y) + (viewPort->fViewMatrix[11] * pos.z) + viewPort->fViewMatrix[15];	//row 4

			if (tmp.z < 0.001f)
				return out;

			tmp.z = 1.0f / tmp.z;

			tmp.x *= tmp.z;
			tmp.y *= tmp.z;

			int w = ImGui::GetIO().DisplaySize.x;
			int h = ImGui::GetIO().DisplaySize.y;

			out.x = ((w / 2.f) + (.5f * tmp.x * w + 1.f)); /// ScreenWidth;
			out.y = ((h / 2.f) - (.5f * tmp.y * h + 1.f)); /// ScreenHeight;
			return out;
		}
		return ImVec2(0, 0);
	}



	inline DWORD64 GetCameraqw()
	{
		if (Camera)
			return *(DWORD64*)(Camera + 0x0);
	}

	DWORD64 GetCamera()
	{
		if (Helper::ValidPTR(Camera))
			return *(DWORD64*)(Camera + 0x0);
	}


	ImVec2 WorldToScreen2(D3DXVECTOR3 WorldPos)
	{
		return WorldToScreen(Vector3(WorldPos.x, WorldPos.y, WorldPos.z));
	}

	ImVec2 GetBonePosW2S(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return WorldToScreen(x);
	}

	Vector3 GetBonePosVec3(const int64_t cPed, const int32_t wMask)
	{
		__m128 tempVec4;
		reinterpret_cast<void* (__fastcall*)(int64_t, __m128*, int32_t)>(BonePositionAddress)(cPed, &tempVec4, wMask);
		Vector3 x(Vector3::FromM128(tempVec4).x, Vector3::FromM128(tempVec4).y, Vector3::FromM128(tempVec4).z);
		return x;
	}

	Vector3 ToVector3(PVector3 pVec) {
		return Vector3(pVec.x, pVec.y, pVec.z);
	}

	/*OFFSET_PLAYER 0x8
		OFFSET_PLAYER_INFO 0x10A8
		OFFSET_PLAYER_INFO_WANTED 0x8E8
		OFFSET_PLAYER_INFO_SWIM_SPD 0x1D0
		OFFSET_PLAYER_INFO_RUN_SPD 0xD50*/
	template <typename T = uint8_t*>
	inline T sub(uint8_t* address, int offset) {
		return reinterpret_cast<T>(address) - offset;
	}
	void initGame()
	{
		const char* process = "GTA5.exe";
		World = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32"), 0x3);
		World = *(DWORD64*)(World + 0x0);
		LocalPlayer = *(DWORD64*)(World + 0x8);
		if (LocalPlayer == 0) {
			std::cout << "error LocalPlayer" << endl;
			///	MessageBoxA(0, "error LocalPlayer", "error LocalPlayer", 0);
		}
		pointer_to_handle = (pointer_handler_t)Helper::FindPattern(process, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB");
		if (pointer_to_handle == 0) {
			std::cout << "error pointer_to_handle" << endl;
		}
		ReplayInterface = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D"), 0x3);
		if (ReplayInterface == 0) {
			std::cout << "error ReplayInterface" << endl;
		}
		viewPort = *(CViewPort**)Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD"), 0x3);
		//viewPort = *(CViewPort**)fix_mov(findPattern(game_executable, enc("48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD")));
		if (viewPort == 0) {
			std::cout << "error viewPort" << endl;
		}

		//World2Screen = (WorldToScreen_t)Helper::FindPattern(process, "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25 ?? 00 00 00 8B");	 //E8 ? ? ? ? 84 C0 74 19 F3 0F 10 44 24
		//if (World2Screen == 0) {
		//	std::cout << "error World2Screen" << endl;
		//}


		_START_SHAPE_TEST_CAPSULE = (tSTART_SHAPE_TEST_CAPSULE)(Helper::FindPattern(process, ("41 8B CF C7 85 ? ? ? ? ? ? ? ? E8 ? ? ? ? B2 01")) - 0xBE);

		_GET_RAYCAST_RESULT = (t_GET_RAYCAST_RESULT)(Helper::FindPattern(process, ("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 83 EC 60 33 DB")));




		Camera = Helper::GetPointerAddress(Helper::FindPattern(process, "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB"), 0x3);
		if (Camera == 0) {
			std::cout << "error Camera" << endl;
		}
		BonePositionAddress = Helper::FindPattern(process, "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 83 EC 60 48 8B 01 41 8B E8 48 8B F2 48 8B F9 33 DB");
		if (BonePositionAddress == 0) {
			std::cout << "error BonePositionAddress" << endl;
		}

		auto gta = sy::pattern::pattern("GTA5.exe");
		m_native_registration_table = gta.scanNow("NATVS", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").getResult().add(3).rip().as<rage::scrNativeRegistrationTable*>();
		if (m_native_registration_table == 0) {
			std::cout << "error m_native_registration_table" << endl;
		}
		m_get_native_handler = gta.scanNow("GNH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").getResult().add(12).rip().as<get_native_handler_t>();
		if (m_get_native_handler == 0) {
			std::cout << "error m_get_native_handler" << endl;
		}
		ptr_gta_fix_context_vector = gta.scanNow("FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA").getResult().as<fix_context_vector_t>();
		if (ptr_gta_fix_context_vector == 0) {
			std::cout << "error ptr_gta_fix_context_vector" << endl;
		}

		DWORD64 FrameCount_pattern = (DWORD64)Helper::FindPattern(process, "8B 15 ? ? ? ? 41 FF CF");
		FrameCount = (FrameCount_pattern + *(DWORD*)(FrameCount_pattern + 0x2) + 0x6);
		if (!FrameCount) {
			MessageBoxA(0, "error m_FrameCount", "error m_FrameCount", 0);
			return;
		}
#define IsValidPtr(x) (x && !IsBadReadPtr(&x, sizeof(void*) && x != nullptr && x > nullptr))
		gta_script_thread_tick = reinterpret_cast<script_thread_tick_t>(sub((uint8_t*)Helper::FindPattern(process, ("48 83 EC 20 80 B9 4E 01 00 00 00")), 0xB)); // for 1.61
		if (!IsValidPtr(gta_script_thread_tick)) {
			MessageBoxA(0, "error gta_script_thread_tick", "error gta_script_thread_tick", 0);
			return;
		}
		DWORD64 pGameCamManager_pattern = Helper::FindPattern(process, "48 8B 05 ?? ?? ?? ?? 4A 8B 1C F0");
		pGameCamManager = (pGameCamManager_pattern + *(DWORD*)(pGameCamManager_pattern + 0x3) + 0x7);

		if (pGameCamManager == 0) {
			std::cout << "error pcamera" << endl;
		}


	}



	DWORD64 GetReplayInterface()
	{
		if (Helper::ValidPTR(ReplayInterface))
			return *(DWORD64*)(ReplayInterface + 0x0);
	}

	namespace Check
	{
		bool isPlayerValid()
		{
			if (Helper::ValidPTR(Memory::World))
			{
				Memory::LocalPlayer = *(DWORD64*)(Memory::World + 0x8);
				if (Memory::LocalPlayer != NULL)
					return true;
			}
			return false;
		}

		bool isPlayerVehicleValid()
		{
			if (Helper::ValidPTR(Memory::LocalPlayer))
			{
				uintptr_t curveh = *(DWORD64*)(Memory::LocalPlayer + 0x0D10);
				if (curveh != NULL)
					return true;
			}
			return false;
		}
		bool In_Vehicle()
		{
			if (isPlayerValid())
			{
				BYTE state = *(BYTE*)(Memory::LocalPlayer + 0xE50);
				if (state == 12)
					return true;
			}
			return false;
		}
		int32_t isPlayerInVehicle()
		{
			int32_t state = *(int32_t*)(Memory::LocalPlayer + 0xE50);
			if (state != 0)
				return true;
			else
				return false;
		}

		bool IsInsideFirstPerson() {
			return *reinterpret_cast<BYTE*>((char*)Memory::LocalPlayer + 0x642) ? true : false;
		}
	}
}
