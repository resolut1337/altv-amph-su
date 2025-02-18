
typedef DWORD Hash;


#include <time.h>

#include <iostream>
#include <ctime>
#include <iomanip>




float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}
#define VK_NOTHING	0x00				/*NULL*/
#define VK_KEY_0	0x30                //('0')	0
#define VK_KEY_1	0x31                //('1')	1
#define VK_KEY_2	0x32                //('2')	2
#define VK_KEY_3	0x33                //('3')	3
#define VK_KEY_4	0x34                //('4')	4
#define VK_KEY_5	0x35                //('5')	5
#define VK_KEY_6	0x36                //('6')	6
#define VK_KEY_7	0x37                //('7')	7
#define VK_KEY_8	0x38                //('8')	8
#define VK_KEY_9	0x39                //('9')	9
#define VK_KEY_A	0x41                //('A')	A
#define VK_KEY_B	0x42                //('B')	B
#define VK_KEY_C	0x43                //('C')	C
#define VK_KEY_D	0x44                //('D')	D
#define VK_KEY_E	0x45                //('E')	E
#define VK_KEY_F	0x46                //('F')	F
#define VK_KEY_G	0x47                //('G')	G
#define VK_KEY_H	0x48                //('H')	H
#define VK_KEY_I	0x49                //('I')	I
#define VK_KEY_J	0x4A                //('J')	J
#define VK_KEY_K	0x4B                //('K')	K
#define VK_KEY_L	0x4C                //('L')	L
#define VK_KEY_M	0x4D                //('M')	M
#define VK_KEY_N	0x4E                //('N')	N
#define VK_KEY_O	0x4F                //('O')	O
#define VK_KEY_P	0x50                //('P')	P
#define VK_KEY_Q	0x51                //('Q')	Q
#define VK_KEY_R	0x52                //('R')	R
#define VK_KEY_S	0x53                //('S')	S
#define VK_KEY_T	0x54                //('T')	T
#define VK_KEY_U	0x55                //('U')	U
#define VK_KEY_V	0x56                //('V')	V
#define VK_KEY_W	0x57                //('W')	W
#define VK_KEY_X	0x58                //('X')	X
#define VK_KEY_Y	0x59                //('Y')	Y
#define VK_KEY_Z	0x5A                //('Z')	Z
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
enum eControl
{
	ControlNextCamera = 0,
	ControlLookLeftRight = 1,
	ControlLookUpDown = 2,
	ControlLookUpOnly = 3,
	ControlLookDownOnly = 4,
	ControlLookLeftOnly = 5,
	ControlLookRightOnly = 6,
	ControlCinematicSlowMo = 7,
	ControlFlyUpDown = 8,
	ControlFlyLeftRight = 9,
	ControlScriptedFlyZUp = 10,
	ControlScriptedFlyZDown = 11,
	ControlWeaponWheelUpDown = 12,
	ControlWeaponWheelLeftRight = 13,
	ControlWeaponWheelNext = 14,
	ControlWeaponWheelPrev = 15,
	ControlSelectNextWeapon = 16,
	ControlSelectPrevWeapon = 17,
	ControlSkipCutscene = 18,
	ControlCharacterWheel = 19,
	ControlMultiplayerInfo = 20,
	ControlSprint = 21,
	ControlJump = 22,
	ControlEnter = 23,
	ControlAttack = 24,
	ControlAim = 25,
	ControlLookBehind = 26,
	ControlPhone = 27,
	ControlSpecialAbility = 28,
	ControlSpecialAbilitySecondary = 29,
	ControlMoveLeftRight = 30,
	ControlMoveUpDown = 31,
	ControlMoveUpOnly = 32,
	ControlMoveDownOnly = 33,
	ControlMoveLeftOnly = 34,
	ControlMoveRightOnly = 35,
	ControlDuck = 36,
	ControlSelectWeapon = 37,
	ControlPickup = 38,
	ControlSniperZoom = 39,
	ControlSniperZoomInOnly = 40,
	ControlSniperZoomOutOnly = 41,
	ControlSniperZoomInSecondary = 42,
	ControlSniperZoomOutSecondary = 43,
	ControlCover = 44,
	ControlReload = 45,
	ControlTalk = 46,
	ControlDetonate = 47,
	ControlHUDSpecial = 48,
	ControlArrest = 49,
	ControlAccurateAim = 50,
	ControlContext = 51,
	ControlContextSecondary = 52,
	ControlWeaponSpecial = 53,
	ControlWeaponSpecial2 = 54,
	ControlDive = 55,
	ControlDropWeapon = 56,
	ControlDropAmmo = 57,
	ControlThrowGrenade = 58,
	ControlVehicleMoveLeftRight = 59,
	ControlVehicleMoveUpDown = 60,
	ControlVehicleMoveUpOnly = 61,
	ControlVehicleMoveDownOnly = 62,
	ControlVehicleMoveLeftOnly = 63,
	ControlVehicleMoveRightOnly = 64,
	ControlVehicleSpecial = 65,
	ControlVehicleGunLeftRight = 66,
	ControlVehicleGunUpDown = 67,
	ControlVehicleAim = 68,
	ControlVehicleAttack = 69,
	ControlVehicleAttack2 = 70,
	ControlVehicleAccelerate = 71,
	ControlVehicleBrake = 72,
	ControlVehicleDuck = 73,
	ControlVehicleHeadlight = 74,
	ControlVehicleExit = 75,
	ControlVehicleHandbrake = 76,
	ControlVehicleHotwireLeft = 77,
	ControlVehicleHotwireRight = 78,
	ControlVehicleLookBehind = 79,
	ControlVehicleCinCam = 80,
	ControlVehicleNextRadio = 81,
	ControlVehiclePrevRadio = 82,
	ControlVehicleNextRadioTrack = 83,
	ControlVehiclePrevRadioTrack = 84,
	ControlVehicleRadioWheel = 85,
	ControlVehicleHorn = 86,
	ControlVehicleFlyThrottleUp = 87,
	ControlVehicleFlyThrottleDown = 88,
	ControlVehicleFlyYawLeft = 89,
	ControlVehicleFlyYawRight = 90,
	ControlVehiclePassengerAim = 91,
	ControlVehiclePassengerAttack = 92,
	ControlVehicleSpecialAbilityFranklin = 93,
	ControlVehicleStuntUpDown = 94,
	ControlVehicleCinematicUpDown = 95,
	ControlVehicleCinematicUpOnly = 96,
	ControlVehicleCinematicDownOnly = 97,
	ControlVehicleCinematicLeftRight = 98,
	ControlVehicleSelectNextWeapon = 99,
	ControlVehicleSelectPrevWeapon = 100,
	ControlVehicleRoof = 101,
	ControlVehicleJump = 102,
	ControlVehicleGrapplingHook = 103,
	ControlVehicleShuffle = 104,
	ControlVehicleDropProjectile = 105,
	ControlVehicleMouseControlOverride = 106,
	ControlVehicleFlyRollLeftRight = 107,
	ControlVehicleFlyRollLeftOnly = 108,
	ControlVehicleFlyRollRightOnly = 109,
	ControlVehicleFlyPitchUpDown = 110,
	ControlVehicleFlyPitchUpOnly = 111,
	ControlVehicleFlyPitchDownOnly = 112,
	ControlVehicleFlyUnderCarriage = 113,
	ControlVehicleFlyAttack = 114,
	ControlVehicleFlySelectNextWeapon = 115,
	ControlVehicleFlySelectPrevWeapon = 116,
	ControlVehicleFlySelectTargetLeft = 117,
	ControlVehicleFlySelectTargetRight = 118,
	ControlVehicleFlyVerticalFlightMode = 119,
	ControlVehicleFlyDuck = 120,
	ControlVehicleFlyAttackCamera = 121,
	ControlVehicleFlyMouseControlOverride = 122,
	ControlVehicleSubTurnLeftRight = 123,
	ControlVehicleSubTurnLeftOnly = 124,
	ControlVehicleSubTurnRightOnly = 125,
	ControlVehicleSubPitchUpDown = 126,
	ControlVehicleSubPitchUpOnly = 127,
	ControlVehicleSubPitchDownOnly = 128,
	ControlVehicleSubThrottleUp = 129,
	ControlVehicleSubThrottleDown = 130,
	ControlVehicleSubAscend = 131,
	ControlVehicleSubDescend = 132,
	ControlVehicleSubTurnHardLeft = 133,
	ControlVehicleSubTurnHardRight = 134,
	ControlVehicleSubMouseControlOverride = 135,
	ControlVehiclePushbikePedal = 136,
	ControlVehiclePushbikeSprint = 137,
	ControlVehiclePushbikeFrontBrake = 138,
	ControlVehiclePushbikeRearBrake = 139,
	ControlMeleeAttackLight = 140,
	ControlMeleeAttackHeavy = 141,
	ControlMeleeAttackAlternate = 142,
	ControlMeleeBlock = 143,
	ControlParachuteDeploy = 144,
	ControlParachuteDetach = 145,
	ControlParachuteTurnLeftRight = 146,
	ControlParachuteTurnLeftOnly = 147,
	ControlParachuteTurnRightOnly = 148,
	ControlParachutePitchUpDown = 149,
	ControlParachutePitchUpOnly = 150,
	ControlParachutePitchDownOnly = 151,
	ControlParachuteBrakeLeft = 152,
	ControlParachuteBrakeRight = 153,
	ControlParachuteSmoke = 154,
	ControlParachutePrecisionLanding = 155,
	ControlMap = 156,
	ControlSelectWeaponUnarmed = 157,
	ControlSelectWeaponMelee = 158,
	ControlSelectWeaponHandgun = 159,
	ControlSelectWeaponShotgun = 160,
	ControlSelectWeaponSmg = 161,
	ControlSelectWeaponAutoRifle = 162,
	ControlSelectWeaponSniper = 163,
	ControlSelectWeaponHeavy = 164,
	ControlSelectWeaponSpecial = 165,
	ControlSelectCharacterMichael = 166,
	ControlSelectCharacterFranklin = 167,
	ControlSelectCharacterTrevor = 168,
	ControlSelectCharacterMultiplayer = 169,
	ControlSaveReplayClip = 170,
	ControlSpecialAbilityPC = 171,
	ControlPhoneUp = 172,
	ControlPhoneDown = 173,
	ControlPhoneLeft = 174,
	ControlPhoneRight = 175,
	ControlPhoneSelect = 176,
	ControlPhoneCancel = 177,
	ControlPhoneOption = 178,
	ControlPhoneExtraOption = 179,
	ControlPhoneScrollForward = 180,
	ControlPhoneScrollBackward = 181,
	ControlPhoneCameraFocusLock = 182,
	ControlPhoneCameraGrid = 183,
	ControlPhoneCameraSelfie = 184,
	ControlPhoneCameraDOF = 185,
	ControlPhoneCameraExpression = 186,
	ControlFrontendDown = 187,
	ControlFrontendUp = 188,
	ControlFrontendLeft = 189,
	ControlFrontendRight = 190,
	ControlFrontendRdown = 191,
	ControlFrontendRup = 192,
	ControlFrontendRleft = 193,
	ControlFrontendRright = 194,
	ControlFrontendAxisX = 195,
	ControlFrontendAxisY = 196,
	ControlFrontendRightAxisX = 197,
	ControlFrontendRightAxisY = 198,
	ControlFrontendPause = 199,
	ControlFrontendPauseAlternate = 200,
	ControlFrontendAccept = 201,
	ControlFrontendCancel = 202,
	ControlFrontendX = 203,
	ControlFrontendY = 204,
	ControlFrontendLb = 205,
	ControlFrontendRb = 206,
	ControlFrontendLt = 207,
	ControlFrontendRt = 208,
	ControlFrontendLs = 209,
	ControlFrontendRs = 210,
	ControlFrontendLeaderboard = 211,
	ControlFrontendSocialClub = 212,
	ControlFrontendSocialClubSecondary = 213,
	ControlFrontendDelete = 214,
	ControlFrontendEndscreenAccept = 215,
	ControlFrontendEndscreenExpand = 216,
	ControlFrontendSelect = 217,
	ControlScriptLeftAxisX = 218,
	ControlScriptLeftAxisY = 219,
	ControlScriptRightAxisX = 220,
	ControlScriptRightAxisY = 221,
	ControlScriptRUp = 222,
	ControlScriptRDown = 223,
	ControlScriptRLeft = 224,
	ControlScriptRRight = 225,
	ControlScriptLB = 226,
	ControlScriptRB = 227,
	ControlScriptLT = 228,
	ControlScriptRT = 229,
	ControlScriptLS = 230,
	ControlScriptRS = 231,
	ControlScriptPadUp = 232,
	ControlScriptPadDown = 233,
	ControlScriptPadLeft = 234,
	ControlScriptPadRight = 235,
	ControlScriptSelect = 236,
	ControlCursorAccept = 237,
	ControlCursorCancel = 238,
	ControlCursorX = 239,
	ControlCursorY = 240,
	ControlCursorScrollUp = 241,
	ControlCursorScrollDown = 242,
	ControlEnterCheatCode = 243,
	ControlInteractionMenu = 244,
	ControlMpTextChatAll = 245,
	ControlMpTextChatTeam = 246,
	ControlMpTextChatFriends = 247,
	ControlMpTextChatCrew = 248,
	ControlPushToTalk = 249,
	ControlCreatorLS = 250,
	ControlCreatorRS = 251,
	ControlCreatorLT = 252,
	ControlCreatorRT = 253,
	ControlCreatorMenuToggle = 254,
	ControlCreatorAccept = 255,
	ControlCreatorDelete = 256,
	ControlAttack2 = 257,
	ControlRappelJump = 258,
	ControlRappelLongJump = 259,
	ControlRappelSmashWindow = 260,
	ControlPrevWeapon = 261,
	ControlNextWeapon = 262,
	ControlMeleeAttack1 = 263,
	ControlMeleeAttack2 = 264,
	ControlWhistle = 265,
	ControlMoveLeft = 266,
	ControlMoveRight = 267,
	ControlMoveUp = 268,
	ControlMoveDown = 269,
	ControlLookLeft = 270,
	ControlLookRight = 271,
	ControlLookUp = 272,
	ControlLookDown = 273,
	ControlSniperZoomIn = 274,
	ControlSniperZoomOut = 275,
	ControlSniperZoomInAlternate = 276,
	ControlSniperZoomOutAlternate = 277,
	ControlVehicleMoveLeft = 278,
	ControlVehicleMoveRight = 279,
	ControlVehicleMoveUp = 280,
	ControlVehicleMoveDown = 281,
	ControlVehicleGunLeft = 282,
	ControlVehicleGunRight = 283,
	ControlVehicleGunUp = 284,
	ControlVehicleGunDown = 285,
	ControlVehicleLookLeft = 286,
	ControlVehicleLookRight = 287,
	ControlReplayStartStopRecording = 288,
	ControlReplayStartStopRecordingSecondary = 289,
	ControlScaledLookLeftRight = 290,
	ControlScaledLookUpDown = 291,
	ControlScaledLookUpOnly = 292,
	ControlScaledLookDownOnly = 293,
	ControlScaledLookLeftOnly = 294,
	ControlScaledLookRightOnly = 295,
	ControlReplayMarkerDelete = 296,
	ControlReplayClipDelete = 297,
	ControlReplayPause = 298,
	ControlReplayRewind = 299,
	ControlReplayFfwd = 300,
	ControlReplayNewmarker = 301,
	ControlReplayRecord = 302,
	ControlReplayScreenshot = 303,
	ControlReplayHidehud = 304,
	ControlReplayStartpoint = 305,
	ControlReplayEndpoint = 306,
	ControlReplayAdvance = 307,
	ControlReplayBack = 308,
	ControlReplayTools = 309,
	ControlReplayRestart = 310,
	ControlReplayShowhotkey = 311,
	ControlReplayCycleMarkerLeft = 312,
	ControlReplayCycleMarkerRight = 313,
	ControlReplayFOVIncrease = 314,
	ControlReplayFOVDecrease = 315,
	ControlReplayCameraUp = 316,
	ControlReplayCameraDown = 317,
	ControlReplaySave = 318,
	ControlReplayToggletime = 319,
	ControlReplayToggletips = 320,
	ControlReplayPreview = 321,
	ControlReplayToggleTimeline = 322,
	ControlReplayTimelinePickupClip = 323,
	ControlReplayTimelineDuplicateClip = 324,
	ControlReplayTimelinePlaceClip = 325,
	ControlReplayCtrl = 326,
	ControlReplayTimelineSave = 327,
	ControlReplayPreviewAudio = 328,
	ControlVehicleDriveLook = 329,
	ControlVehicleDriveLook2 = 330,
	ControlVehicleFlyAttack2 = 331,
	ControlRadioWheelUpDown = 332,
	ControlRadioWheelLeftRight = 333,
	ControlVehicleSlowMoUpDown = 334,
	ControlVehicleSlowMoUpOnly = 335,
	ControlVehicleSlowMoDownOnly = 336,
	ControlMapPointOfInterest = 337,
};

void FlyingCarLoop()
{
	if (amphetamine::amphetamine_settings->Flyhackcar) {
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			int Vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
			if (CONTROLS::IS_CONTROL_PRESSED(2, 67) == true) //Forward
			{
				float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.5;
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehid, 25);

			}

			if ((CONTROLS::IS_CONTROL_PRESSED(2, 196) == true) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Left
			{
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z + 1.0;
				ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
			}

			if ((CONTROLS::IS_CONTROL_PRESSED(2, 197) == true) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Right
			{
				Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
				Rot.z = Rot.z - 1.0;
				ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
			}
		}



		//if (ped::is_ped_in_any_vehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 0))
		//{
		//	int Vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 0);

		//	if (IsKeyPressed(VK_LSHIFT) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRt) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Up
		//	{
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, 0, 5, 0, 0, 0, 1, false, true, true, false, true);
		//	}

		//	if (IsKeyPressed(VK_LCONTROL) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendLt) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Down
		//	{
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, 0, 5, 0, 0, 0, 1, false, true, true, false, true);
		//	}

		//	if (IsKeyPressed(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRup) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Forward
		//	{
		//		//float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.5;
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, 5, 0, 0, 0, 0, 1, false, true, true, false, true);
		//	}

		//	if (IsKeyPressed(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRdown) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Backward
		//	{
		//		//float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.5;
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, -5, 0, 0, 0, 0, 1, false, true, true, false, true);
		//	}

		//	if ((IsKeyPressed(VK_KEY_A)) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid)) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRleft) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Left
		//	{
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, -5, 0, 0, 0, 0, 0, 1, false, true, true, false, true);
		//	}

		//	if ((IsKeyPressed(VK_KEY_D)) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid)) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRright) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Right
		//	{
		//		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 5, 0, 0, 0, 0, 0, 1, false, true, true, false, true);
		//	}
		//}
	}
}
float degToRad(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}
struct VEHICLESPLATES
{
	Vector3 position;
};
VEHICLESPLATES Get_vehicle_plates[255];
void testmegafunk() {
	/*if (Config::getvehicllenumberplates) {
		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
		if (!ReplayInterface)
			return;
		hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
		if (!VehicleInterface)
			return;
		for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {

			hk_Vehicle* Peds = VehicleInterface->VehicleList()->Vehicle(i);
			if (!Peds) continue;

			ImVec2 vScreenPosition = Memory::WorldToScreen(Get_vehicle_plates[i].position);
			Visuals::DrawOutlinedText(font::poppins_medium_low, "VEHILE NUMBER PLATES", ImVec2(vScreenPosition.x, vScreenPosition.y), 17.f, ImColor(Config::object_color), true);

		}
	}*/
}
int func_schet()
{
	static int j = 0;

	j++;

	return j;
}
static int jqwqwqw = 0;
#include <vector>
#include <sysinfoapi.h>
#include <functional>
#include <stack>




HRESULT(*resize_original)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

HRESULT resize_hook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	//Renderer::ResetCanvas();


	//pContext->OMSetRenderTargets(1, &RenderTargetView, NULL);
	if (RenderTargetView) RenderTargetView->Release();

	if (pContext) pContext->Release();
	if (pDevice) pDevice->Release();

	pDevice = nullptr;

	return resize_original(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}


//void SemiGodMode(bool toggle)
//{
//	if (toggle == true && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))
//	{
//		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_ID(), 100.f);
//		BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
//		Player player = PLAYER::PLAYER_ID();
//		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID());
//		ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
//		PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
//		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
//		{
//			Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
//			if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
//				VEHICLE::SET_VEHICLE_FIXED(playerVeh);
//		}
//	}
//}
//void RequestControlOfid(Entity netid)
//{
//	int tick = 0;
//	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
//	{
//		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
//		tick++;
//	}
//}
//void RequestControlOfEnt(Entity entity)
//{
//	int tick = 0;
//	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
//	{
//		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
//		tick++;
//	}
//	if (NETWORK::NETWORK_IS_SESSION_STARTED())
//	{
//		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
//		RequestControlOfid(netID);
//		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
//	}
//}
//void deletenearbyvehicles(bool toggle)
//{
//	const int ElementAmount = 10;
//	const int ArrSize = ElementAmount * 2 + 2;
//
//	Vehicle* vehs = new Vehicle[ArrSize];
//	vehs[0] = ElementAmount;
//	int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), vehs);
//
//	for (int i = 0; i < VehFound; i++)
//	{
//		int OffsetID = i * 2 + 2;
//		if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false))
//		{
//			RequestControlOfEnt(vehs[OffsetID]);
//			ENTITY::_SET_ENTITY_COORDS_2(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
//		}
//	}
//	delete vehs;
//}

void enginealwayson()
{
	if (amphetamine::amphetamine_settings->enginealwayson) {
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, amphetamine::amphetamine_settings->enginealwayson, amphetamine::amphetamine_settings->enginealwayson, false);
		VEHICLE::SET_VEHICLE_LIGHTS(veh, 0);
	}
}
typedef void (*pIsDlcPresentqw)(int a1, int a2);
pIsDlcPresentqw OG_IS_DLC_PRESENTqwqwqw = nullptr;


static int selectedVeh_index_check_plates = 1;


Vector3 get_cam_directions() {

	const double PI = 3.141592653589793238463;

	float heading = native::cam::get_gameplay_cam_relative_heading() + native::entity::get_entity_heading(native::player::player_ped_id());
	float pitch = native::cam::get_gameplay_cam_relative_pitch();

	float x = -sin(heading * PI / 180.0f);
	float y = cos(heading * PI / 180.0f);
	float z = sin(pitch * PI / 180.0f);

	double len = sqrt(x * x + y * y + z * z);
	if (len != 0) {
		x = x / len;
		y = y / len;
		z = z / len;
	}

	return Vector3(x, y, z);
}
//inline Vector3 get_cam_directions() {
//
//	const double PI = 3.141592653589793238463;
//	auto playerPed = player::get_player_ped_script_index(player::player_id()); //GET_PLAYER_PED_SCRIPT_INDEX
//	float heading = cam::get_gameplay_cam_relative_heading() + entity::get_entity_heading(playerPed);
//	float pitch = cam::get_gameplay_cam_relative_pitch();
//
//	float x = -sin(heading * PI / 180.0f);
//	float y = cos(heading * PI / 180.0f);
//	float z = sin(pitch * PI / 180.0f);
//
//	double len = sqrt(x * x + y * y + z * z);
//	if (len != 0) {
//		x = x / len;
//		y = y / len;
//		z = z / len;
//	}
//
//	return Vector3(x, y, z);
//}
void NoClipme()
{
	if (amphetamine::amphetamine_settings->NoClip) {
		if ((GetAsyncKeyState(amphetamine::amphetamine_settings->NoclipKey) & 1))
		{
			global::noclip_bind = !global::noclip_bind;
		}
	}

	if (amphetamine::amphetamine_settings->NoClip) {
		if (global::noclip_bind) {
			//if (GetAsyncKeyState(amphetamine::amphetamine_settings->NoclipKey) & 0x8000) { //
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), false, 0);
			using namespace native;
			int noclip_speed = 1;
			bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
			type::any entity;
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			if (!is_in_vehicle) {
				entity = player::get_player_ped(-1);
			}
			else
			{
				entity = ped::get_vehicle_ped_is_in(player::get_player_ped(-1), false);
			}
			auto pos = entity::get_entity_coords(entity, false); //GET_ENTITY_COORDS
			x = pos.x;
			y = pos.y;
			z = pos.z;
			auto cam_direction = get_cam_directions();

			float dx = cam_direction.x;
			float dy = cam_direction.y;
			float dz = cam_direction.z;

			if (GetAsyncKeyState(VK_LSHIFT))
				noclip_speed = 3;

			if (!GetAsyncKeyState(VK_LSHIFT))
				noclip_speed = 1;

			if (noclip_speed == NULL) noclip_speed = 1;

			if (GetAsyncKeyState(0x57))
			{
				x = x + noclip_speed * amphetamine::amphetamine_settings->Speed * dx;
				y = y + noclip_speed * amphetamine::amphetamine_settings->Speed * dy;
				z = z + noclip_speed * amphetamine::amphetamine_settings->Speed * dz;
			}

			if (GetAsyncKeyState(0x53))
			{
				x = x - noclip_speed * amphetamine::amphetamine_settings->Speed * dx;
				y = y - noclip_speed * amphetamine::amphetamine_settings->Speed * dy;
				z = z - noclip_speed * amphetamine::amphetamine_settings->Speed * dz;
			}

			if (GetAsyncKeyState(VK_SPACE))
				z = z + noclip_speed * amphetamine::amphetamine_settings->Speed;

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, x, y, z, amphetamine::amphetamine_settings->NoClipSpeed_bool, amphetamine::amphetamine_settings->NoClipSpeed_bool, amphetamine::amphetamine_settings->NoClipSpeed_bool);
		}
		else {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, 0);
		}
	}
}


void superpunch() {
	/*if (amphetamine::amphetamine_settings->player_superpunch) {
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 10000);
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 10000);

		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 10000);
		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 10000);

		PED::SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(10000);
	}*/
}
void explosive_ammo()
{
	//if (amphetamine::amphetamine_settings->ExplosiveAmmo) {
	//	Vector3 pos = {};
	//	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), &pos))
	//		FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 60, 1.f, true, false, 0.f);
	//}
}
bool fgkdlkdfkglk = false;
void ghostmode(bool toggle)
{
	if (toggle == true)
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false, 0);
		fgkdlkdfkglk = true;
	}
	else
	{
		if (fgkdlkdfkglk == true) {
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), true, 0);
			fgkdlkdfkglk = false;
		}
	}
}
bool nofallcheck = false;
void nofall(bool toggle) {
	if (toggle == true) {

		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 1);
		nofallcheck = true;
	}
	else
	{
		if (nofallcheck == true) {
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), 0);
			nofallcheck = false;
		}
	}
}
void RAINBOWguner() {
	Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID());
	static LPCSTR weaponNames[] = {
		"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
		"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
		"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
		"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
		"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
		"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
		"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
		"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
		"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
		"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN", "WEAPON_FLAREGUN",
		"WEAPON_KNUCKLE", "GADGET_NIGHTVISION", "GADGET_PARACHUTE", "WEAPON_MARKSMANPISTOL", "WEAPON_PISTOL_MK2", "WEAPON_SMG_MK2",
		"WEAPON_ASSAULTRIFLE_MK2", "WEAPON_CARBINERIFLE_MK2", "WEAPON_COMBATMG_MK2", "WEAPON_HEAVYSNIPER_MK2"
	};
	for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
	{
		if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY((char*)weaponNames[i]), 0))
		{
			WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, GAMEPLAY::GET_HASH_KEY((char*)weaponNames[i]), rand() % 8);
		}
	}
}

bool AlwaysRagdoll = false;
void alwaysragdoll(bool toggle)
{
	if (toggle)
	{

		PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
		AlwaysRagdoll = true;
	}
	else
	{
		if (AlwaysRagdoll == true) {
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
			AlwaysRagdoll = true;
		}
	}
}
bool Collision = false;
void collision(bool toggle)
{
	if (toggle)
	{
		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), false, 0);
		Collision = true;
	}
	else
	{
		if (Collision == true) {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, 0);
			Collision = false;
		}
	}
	//PED::SET_PED_RAGDOLL_ON_COLLISION;
}





inline bool raycast(Entity* ent)
{
	BOOL hit;
	Vector3 endCoords;
	Vector3 surfaceNormal;

	Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 dir = RotationToDirectionV3(rot);
	Vector3 farCoords;

	farCoords.x = camCoords.x + dir.x * 1000;
	farCoords.y = camCoords.y + dir.y * 1000;
	farCoords.z = camCoords.z + dir.z * 1000;

	int ray = WORLDPROBE::_START_SHAPE_TEST_RAY(camCoords.x,
		camCoords.y,
		camCoords.z,
		farCoords.x,
		farCoords.y,
		farCoords.z,
		-1,
		0,
		7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

	return (bool)hit;
}

inline bool raycast(Vector3* endcoor)
{
	Entity ent;
	BOOL hit;
	Vector3 surfaceNormal;

	Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 dir = RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(2));
	Vector3 farCoords;

	farCoords.x = camCoords.x + dir.x * 1000;
	farCoords.y = camCoords.y + dir.y * 1000;
	farCoords.z = camCoords.z + dir.z * 1000;

	int ray = WORLDPROBE::_START_SHAPE_TEST_RAY(camCoords.x,
		camCoords.y,
		camCoords.z,
		farCoords.x,
		farCoords.y,
		farCoords.z,
		-1,
		0,
		7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, endcoor, &surfaceNormal, &ent);

	return (bool)hit;
}





bool RapidFire = false;
Vector3 rot_to_direction(Vector3* rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
Vector3 add(Vector3* vectorA, Vector3* vectorB)
{
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;

	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;

	return result;
}

Vector3 multiply(Vector3* vector, float x)
{
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;

	result.x *= x;
	result.y *= x;
	result.z *= x;

	return result;
}
void rapidfire(bool toggle)
{
	if (toggle)
	{
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			Vector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
			Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			Vector3 gameplayCamDirection = rot_to_direction(&gameplayCamRot);
			Vector3 startCoords = add(&gameplayCam, (&multiply(&gameplayCamDirection, 1.0f)));
			Vector3 endCoords = add(&startCoords, &multiply(&gameplayCamDirection, 500.0f));
			Hash weaponhash;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);

			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
		}
	}
}
bool VehInvisible = false;
void vehinvisible(bool toggle)
{
	if (toggle)
	{
		Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
		ENTITY::SET_ENTITY_VISIBLE(Veh, false, 0);
		VehInvisible = true;
	}
	else
	{
		if (VehInvisible == true) {
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
			ENTITY::SET_ENTITY_VISIBLE(Veh, true, 0);
			VehInvisible = false;
		}
	}
}

void driftmode(bool toggle)
{
	if (toggle)
	{
		if (GetAsyncKeyState(VK_LSHIFT))
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		else
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}
}
void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}
void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

Vector3 get_gameplay_cam_front_coords(float toMove)
{
	using namespace Memory;
	Vector3 tmp;
	tmp.x = (Memory::viewPort->fViewMatrix[1]) + (viewPort->fViewMatrix[5] ) + (viewPort->fViewMatrix[9]) + viewPort->fViewMatrix[13];		//row 2
	tmp.y = (viewPort->fViewMatrix[2]) + (viewPort->fViewMatrix[6]) + (viewPort->fViewMatrix[10] ) + viewPort->fViewMatrix[14];	//row 3
	tmp.z = (viewPort->fViewMatrix[3]) + (viewPort->fViewMatrix[7] ) + (viewPort->fViewMatrix[11]) + viewPort->fViewMatrix[15];	//row 4
	//if (amphetamine::amphetamine_settings->clickwarpvehicle) {
	//	tmp.z = 1.0f / tmp.z;
	//	tmp.x *= tmp.z;
	//	tmp.y *= tmp.z;
	//}
	Vector3 calculated_position;

	DWORD64 cam = Memory::GetCamera();
	Vector3 CrosshairPos;
	if (amphetamine::amphetamine_settings->clickwarpvehicle) {
		CrosshairPos = CAM::GET_GAMEPLAY_CAM_COORD();
	}
	else {
		CrosshairPos = *(Vector3*)(cam + 0x60);
	}

	calculated_position.x = CrosshairPos.x + RotationToDirectionV3(tmp).x * toMove;
	calculated_position.y = CrosshairPos.y + RotationToDirectionV3(tmp).y * toMove;
	calculated_position.z = CrosshairPos.z + RotationToDirectionV3(tmp).z * toMove;


	//calculated_position.x = CAM::GET_GAMEPLAY_CAM_COORD().x + RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(2)).x * toMove;
	//calculated_position.y = CAM::GET_GAMEPLAY_CAM_COORD().y + RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(2)).y * toMove;
	//calculated_position.z = CAM::GET_GAMEPLAY_CAM_COORD().z + RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(2)).z * toMove;
	return calculated_position;
}

Vector3 click_warp_funk()
{
	Vector3 calculated_position;

	Vector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 cam_pos = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 cam_dir = RotationToDirectionV3(cam_rot);

	calculated_position.x = cam_pos.x + cam_dir.x;
	calculated_position.y = cam_pos.y + cam_dir.y;
	calculated_position.z = cam_pos.z + cam_dir.z;

	return calculated_position;
}


void autoflip(bool toggle)
{
	if (toggle)
	{
		auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		float roll = ENTITY::GET_ENTITY_ROLL(veh);
		if (ENTITY::IS_ENTITY_UPSIDEDOWN(veh) && (roll > 160 || roll < -160))
		{
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (!ENTITY::IS_ENTITY_IN_AIR(veh) && !ENTITY::IS_ENTITY_IN_WATER(veh) && !VEHICLE::IS_THIS_MODEL_A_PLANE(veh) && !VEHICLE::IS_THIS_MODEL_A_HELI(veh))
			{
				RequestControlOfEnt(veh);
				ENTITY::SET_ENTITY_ROTATION(veh, 0, 0, ENTITY::GET_ENTITY_ROTATION(veh, 2).z, 2, 1);
			}
		}
	}
}
enum ControllerInputs
{
	INPUT_NEXT_CAMERA = 0,
	INPUT_LOOK_LR = 1,
	INPUT_LOOK_UD = 2,
	INPUT_LOOK_UP_ONLY = 3,
	INPUT_LOOK_DOWN_ONLY = 4,
	INPUT_LOOK_LEFT_ONLY = 5,
	INPUT_LOOK_RIGHT_ONLY = 6,
	INPUT_CINEMATIC_SLOWMO = 7,
	INPUT_SCRIPTED_FLY_UD = 8,
	INPUT_SCRIPTED_FLY_LR = 9,
	INPUT_SCRIPTED_FLY_ZUP = 10,
	INPUT_SCRIPTED_FLY_ZDOWN = 11,
	INPUT_WEAPON_WHEEL_UD = 12,
	INPUT_WEAPON_WHEEL_LR = 13,
	INPUT_WEAPON_WHEEL_NEXT = 14,
	INPUT_WEAPON_WHEEL_PREV = 15,
	INPUT_SELECT_NEXT_WEAPON = 16,
	INPUT_SELECT_PREV_WEAPON = 17,
	INPUT_SKIP_CUTSCENE = 18,
	INPUT_CHARACTER_WHEEL = 19,
	INPUT_MULTIPLAYER_INFO = 20,
	INPUT_SPRINT = 21,
	INPUT_JUMP = 22,
	INPUT_ENTER = 23,
	INPUT_ATTACK = 24,
	INPUT_AIM = 25,
	INPUT_LOOK_BEHIND = 26,
	INPUT_PHONE = 27,
	INPUT_SPECIAL_ABILITY = 28,
	INPUT_SPECIAL_ABILITY_SECONDARY = 29,
	INPUT_MOVE_LR = 30,
	INPUT_MOVE_UD = 31,
	INPUT_MOVE_UP_ONLY = 32,
	INPUT_MOVE_DOWN_ONLY = 33,
	INPUT_MOVE_LEFT_ONLY = 34,
	INPUT_MOVE_RIGHT_ONLY = 35,
	INPUT_DUCK = 36,
	INPUT_SELECT_WEAPON = 37,
	INPUT_PICKUP = 38,
	INPUT_SNIPER_ZOOM = 39,
	INPUT_SNIPER_ZOOM_IN_ONLY = 40,
	INPUT_SNIPER_ZOOM_OUT_ONLY = 41,
	INPUT_SNIPER_ZOOM_IN_SECONDARY = 42,
	INPUT_SNIPER_ZOOM_OUT_SECONDARY = 43,
	INPUT_COVER = 44,
	INPUT_RELOAD = 45,
	INPUT_TALK = 46,
	INPUT_DETONATE = 47,
	INPUT_HUD_SPECIAL = 48,
	INPUT_ARREST = 49,
	INPUT_ACCURATE_AIM = 50,
	INPUT_CONTEXT = 51,
	INPUT_CONTEXT_SECONDARY = 52,
	INPUT_WEAPON_SPECIAL = 53,
	INPUT_WEAPON_SPECIAL_TWO = 54,
	INPUT_DIVE = 55,
	INPUT_DROP_WEAPON = 56,
	INPUT_DROP_AMMO = 57,
	INPUT_THROW_GRENADE = 58,
	INPUT_VEH_MOVE_LR = 59,
	INPUT_VEH_MOVE_UD = 60,
	INPUT_VEH_MOVE_UP_ONLY = 61,
	INPUT_VEH_MOVE_DOWN_ONLY = 62,
	INPUT_VEH_MOVE_LEFT_ONLY = 63,
	INPUT_VEH_MOVE_RIGHT_ONLY = 64,
	INPUT_VEH_SPECIAL = 65,
	INPUT_VEH_GUN_LR = 66,
	INPUT_VEH_GUN_UD = 67,
	INPUT_VEH_AIM = 68,
	INPUT_VEH_ATTACK = 69,
	INPUT_VEH_ATTACK2 = 70,
	INPUT_VEH_ACCELERATE = 71,
	INPUT_VEH_BRAKE = 72,
	INPUT_VEH_DUCK = 73,
	INPUT_VEH_HEADLIGHT = 74,
	INPUT_VEH_EXIT = 75,
	INPUT_VEH_HANDBRAKE = 76,
	INPUT_VEH_HOTWIRE_LEFT = 77,
	INPUT_VEH_HOTWIRE_RIGHT = 78,
	INPUT_VEH_LOOK_BEHIND = 79,
	INPUT_VEH_CIN_CAM = 80,
	INPUT_VEH_NEXT_RADIO = 81,
	INPUT_VEH_PREV_RADIO = 82,
	INPUT_VEH_NEXT_RADIO_TRACK = 83,
	INPUT_VEH_PREV_RADIO_TRACK = 84,
	INPUT_VEH_RADIO_WHEEL = 85,
	INPUT_VEH_HORN = 86,
	INPUT_VEH_FLY_THROTTLE_UP = 87,
	INPUT_VEH_FLY_THROTTLE_DOWN = 88,
	INPUT_VEH_FLY_YAW_LEFT = 89,
	INPUT_VEH_FLY_YAW_RIGHT = 90,
	INPUT_VEH_PASSENGER_AIM = 91,
	INPUT_VEH_PASSENGER_ATTACK = 92,
	INPUT_VEH_SPECIAL_ABILITY_FRANKLIN = 93,
	INPUT_VEH_STUNT_UD = 94,
	INPUT_VEH_CINEMATIC_UD = 95,
	INPUT_VEH_CINEMATIC_UP_ONLY = 96,
	INPUT_VEH_CINEMATIC_DOWN_ONLY = 97,
	INPUT_VEH_CINEMATIC_LR = 98,
	INPUT_VEH_SELECT_NEXT_WEAPON = 99,
	INPUT_VEH_SELECT_PREV_WEAPON = 100,
	INPUT_VEH_ROOF = 101,
	INPUT_VEH_JUMP = 102,
	INPUT_VEH_GRAPPLING_HOOK = 103,
	INPUT_VEH_SHUFFLE = 104,
	INPUT_VEH_DROP_PROJECTILE = 105,
	INPUT_VEH_MOUSE_CONTROL_OVERRIDE = 106,
	INPUT_VEH_FLY_ROLL_LR = 107,
	INPUT_VEH_FLY_ROLL_LEFT_ONLY = 108,
	INPUT_VEH_FLY_ROLL_RIGHT_ONLY = 109,
	INPUT_VEH_FLY_PITCH_UD = 110,
	INPUT_VEH_FLY_PITCH_UP_ONLY = 111,
	INPUT_VEH_FLY_PITCH_DOWN_ONLY = 112,
	INPUT_VEH_FLY_UNDERCARRIAGE = 113,
	INPUT_VEH_FLY_ATTACK = 114,
	INPUT_VEH_FLY_SELECT_NEXT_WEAPON = 115,
	INPUT_VEH_FLY_SELECT_PREV_WEAPON = 116,
	INPUT_VEH_FLY_SELECT_TARGET_LEFT = 117,
	INPUT_VEH_FLY_SELECT_TARGET_RIGHT = 118,
	INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE = 119,
	INPUT_VEH_FLY_DUCK = 120,
	INPUT_VEH_FLY_ATTACK_CAMERA = 121,
	INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE = 122,
	INPUT_VEH_SUB_TURN_LR = 123,
	INPUT_VEH_SUB_TURN_LEFT_ONLY = 124,
	INPUT_VEH_SUB_TURN_RIGHT_ONLY = 125,
	INPUT_VEH_SUB_PITCH_UD = 126,
	INPUT_VEH_SUB_PITCH_UP_ONLY = 127,
	INPUT_VEH_SUB_PITCH_DOWN_ONLY = 128,
	INPUT_VEH_SUB_THROTTLE_UP = 129,
	INPUT_VEH_SUB_THROTTLE_DOWN = 130,
	INPUT_VEH_SUB_ASCEND = 131,
	INPUT_VEH_SUB_DESCEND = 132,
	INPUT_VEH_SUB_TURN_HARD_LEFT = 133,
	INPUT_VEH_SUB_TURN_HARD_RIGHT = 134,
	INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE = 135,
	INPUT_VEH_PUSHBIKE_PEDAL = 136,
	INPUT_VEH_PUSHBIKE_SPRINT = 137,
	INPUT_VEH_PUSHBIKE_FRONT_BRAKE = 138,
	INPUT_VEH_PUSHBIKE_REAR_BRAKE = 139,
	INPUT_MELEE_ATTACK_LIGHT = 140,
	INPUT_MELEE_ATTACK_HEAVY = 141,
	INPUT_MELEE_ATTACK_ALTERNATE = 142,
	INPUT_MELEE_BLOCK = 143,
	INPUT_PARACHUTE_DEPLOY = 144,
	INPUT_PARACHUTE_DETACH = 145,
	INPUT_PARACHUTE_TURN_LR = 146,
	INPUT_PARACHUTE_TURN_LEFT_ONLY = 147,
	INPUT_PARACHUTE_TURN_RIGHT_ONLY = 148,
	INPUT_PARACHUTE_PITCH_UD = 149,
	INPUT_PARACHUTE_PITCH_UP_ONLY = 150,
	INPUT_PARACHUTE_PITCH_DOWN_ONLY = 151,
	INPUT_PARACHUTE_BRAKE_LEFT = 152,
	INPUT_PARACHUTE_BRAKE_RIGHT = 153,
	INPUT_PARACHUTE_SMOKE = 154,
	INPUT_PARACHUTE_PRECISION_LANDING = 155,
	INPUT_MAP = 156,
	INPUT_SELECT_WEAPON_UNARMED = 157,
	INPUT_SELECT_WEAPON_MELEE = 158,
	INPUT_SELECT_WEAPON_HANDGUN = 159,
	INPUT_SELECT_WEAPON_SHOTGUN = 160,
	INPUT_SELECT_WEAPON_SMG = 161,
	INPUT_SELECT_WEAPON_AUTO_RIFLE = 162,
	INPUT_SELECT_WEAPON_SNIPER = 163,
	INPUT_SELECT_WEAPON_HEAVY = 164,
	INPUT_SELECT_WEAPON_SPECIAL = 165,
	INPUT_SELECT_CHARACTER_MICHAEL = 166,
	INPUT_SELECT_CHARACTER_FRANKLIN = 167,
	INPUT_SELECT_CHARACTER_TREVOR = 168,
	INPUT_SELECT_CHARACTER_MULTIPLAYER = 169,
	INPUT_SAVE_REPLAY_CLIP = 170,
	INPUT_SPECIAL_ABILITY_PC = 171,
	INPUT_CELLPHONE_UP = 172,
	INPUT_CELLPHONE_DOWN = 173,
	INPUT_CELLPHONE_LEFT = 174,
	INPUT_CELLPHONE_RIGHT = 175,
	INPUT_CELLPHONE_SELECT = 176,
	INPUT_CELLPHONE_CANCEL = 177,
	INPUT_CELLPHONE_OPTION = 178,
	INPUT_CELLPHONE_EXTRA_OPTION = 179,
	INPUT_CELLPHONE_SCROLL_FORWARD = 180,
	INPUT_CELLPHONE_SCROLL_BACKWARD = 181,
	INPUT_CELLPHONE_CAMERA_FOCUS_LOCK = 182,
	INPUT_CELLPHONE_CAMERA_GRID = 183,
	INPUT_CELLPHONE_CAMERA_SELFIE = 184,
	INPUT_CELLPHONE_CAMERA_DOF = 185,
	INPUT_CELLPHONE_CAMERA_EXPRESSION = 186,
	INPUT_FRONTEND_DOWN = 187,
	INPUT_FRONTEND_UP = 188,
	INPUT_FRONTEND_LEFT = 189,
	INPUT_FRONTEND_RIGHT = 190,
	INPUT_FRONTEND_RDOWN = 191,
	INPUT_FRONTEND_RUP = 192,
	INPUT_FRONTEND_RLEFT = 193,
	INPUT_FRONTEND_RRIGHT = 194,
	INPUT_FRONTEND_AXIS_X = 195,
	INPUT_FRONTEND_AXIS_Y = 196,
	INPUT_FRONTEND_RIGHT_AXIS_X = 197,
	INPUT_FRONTEND_RIGHT_AXIS_Y = 198,
	INPUT_FRONTEND_PAUSE = 199,
	INPUT_FRONTEND_PAUSE_ALTERNATE = 200,
	INPUT_FRONTEND_ACCEPT = 201,
	INPUT_FRONTEND_CANCEL = 202,
	INPUT_FRONTEND_X = 203,
	INPUT_FRONTEND_Y = 204,
	INPUT_FRONTEND_LB = 205,
	INPUT_FRONTEND_RB = 206,
	INPUT_FRONTEND_LT = 207,
	INPUT_FRONTEND_RT = 208,
	INPUT_FRONTEND_LS = 209,
	INPUT_FRONTEND_RS = 210,
	INPUT_FRONTEND_LEADERBOARD = 211,
	INPUT_FRONTEND_SOCIAL_CLUB = 212,
	INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY = 213,
	INPUT_FRONTEND_DELETE = 214,
	INPUT_FRONTEND_ENDSCREEN_ACCEPT = 215,
	INPUT_FRONTEND_ENDSCREEN_EXPAND = 216,
	INPUT_FRONTEND_SELECT = 217,
	INPUT_SCRIPT_LEFT_AXIS_X = 218,
	INPUT_SCRIPT_LEFT_AXIS_Y = 219,
	INPUT_SCRIPT_RIGHT_AXIS_X = 220,
	INPUT_SCRIPT_RIGHT_AXIS_Y = 221,
	INPUT_SCRIPT_RUP = 222,
	INPUT_SCRIPT_RDOWN = 223,
	INPUT_SCRIPT_RLEFT = 224,
	INPUT_SCRIPT_RRIGHT = 225,
	INPUT_SCRIPT_LB = 226,
	INPUT_SCRIPT_RB = 227,
	INPUT_SCRIPT_LT = 228,
	INPUT_SCRIPT_RT = 229,
	INPUT_SCRIPT_LS = 230,
	INPUT_SCRIPT_RS = 231,
	INPUT_SCRIPT_PAD_UP = 232,
	INPUT_SCRIPT_PAD_DOWN = 233,
	INPUT_SCRIPT_PAD_LEFT = 234,
	INPUT_SCRIPT_PAD_RIGHT = 235,
	INPUT_SCRIPT_SELECT = 236,
	INPUT_CURSOR_ACCEPT = 237,
	INPUT_CURSOR_CANCEL = 238,
	INPUT_CURSOR_X = 239,
	INPUT_CURSOR_Y = 240,
	INPUT_CURSOR_SCROLL_UP = 241,
	INPUT_CURSOR_SCROLL_DOWN = 242,
	INPUT_ENTER_CHEAT_CODE = 243,
	INPUT_INTERACTION_MENU = 244,
	INPUT_MP_TEXT_CHAT_ALL = 245,
	INPUT_MP_TEXT_CHAT_TEAM = 246,
	INPUT_MP_TEXT_CHAT_FRIENDS = 247,
	INPUT_MP_TEXT_CHAT_CREW = 248,
	INPUT_PUSH_TO_TALK = 249,
	INPUT_CREATOR_LS = 250,
	INPUT_CREATOR_RS = 251,
	INPUT_CREATOR_LT = 252,
	INPUT_CREATOR_RT = 253,
	INPUT_CREATOR_MENU_TOGGLE = 254,
	INPUT_CREATOR_ACCEPT = 255,
	INPUT_CREATOR_DELETE = 256,
	INPUT_ATTACK2 = 257,
	INPUT_RAPPEL_JUMP = 258,
	INPUT_RAPPEL_LONG_JUMP = 259,
	INPUT_RAPPEL_SMASH_WINDOW = 260,
	INPUT_PREV_WEAPON = 261,
	INPUT_NEXT_WEAPON = 262,
	INPUT_MELEE_ATTACK1 = 263,
	INPUT_MELEE_ATTACK2 = 264,
	INPUT_WHISTLE = 265,
	INPUT_MOVE_LEFT = 266,
	INPUT_MOVE_RIGHT = 267,
	INPUT_MOVE_UP = 268,
	INPUT_MOVE_DOWN = 269,
	INPUT_LOOK_LEFT = 270,
	INPUT_LOOK_RIGHT = 271,
	INPUT_LOOK_UP = 272,
	INPUT_LOOK_DOWN = 273,
	INPUT_SNIPER_ZOOM_IN = 274,
	INPUT_SNIPER_ZOOM_OUT = 275,
	INPUT_SNIPER_ZOOM_IN_ALTERNATE = 276,
	INPUT_SNIPER_ZOOM_OUT_ALTERNATE = 277,
	INPUT_VEH_MOVE_LEFT = 278,
	INPUT_VEH_MOVE_RIGHT = 279,
	INPUT_VEH_MOVE_UP = 280,
	INPUT_VEH_MOVE_DOWN = 281,
	INPUT_VEH_GUN_LEFT = 282,
	INPUT_VEH_GUN_RIGHT = 283,
	INPUT_VEH_GUN_UP = 284,
	INPUT_VEH_GUN_DOWN = 285,
	INPUT_VEH_LOOK_LEFT = 286,
	INPUT_VEH_LOOK_RIGHT = 287,
	INPUT_REPLAY_START_STOP_RECORDING = 288,
	INPUT_REPLAY_START_STOP_RECORDING_SECONDARY = 289,
	INPUT_SCALED_LOOK_LR = 290,
	INPUT_SCALED_LOOK_UD = 291,
	INPUT_SCALED_LOOK_UP_ONLY = 292,
	INPUT_SCALED_LOOK_DOWN_ONLY = 293,
	INPUT_SCALED_LOOK_LEFT_ONLY = 294,
	INPUT_SCALED_LOOK_RIGHT_ONLY = 295,
	INPUT_REPLAY_MARKER_DELETE = 296,
	INPUT_REPLAY_CLIP_DELETE = 297,
	INPUT_REPLAY_PAUSE = 298,
	INPUT_REPLAY_REWIND = 299,
	INPUT_REPLAY_FFWD = 300,
	INPUT_REPLAY_NEWMARKER = 301,
	INPUT_REPLAY_RECORD = 302,
	INPUT_REPLAY_SCREENSHOT = 303,
	INPUT_REPLAY_HIDEHUD = 304,
	INPUT_REPLAY_STARTPOINT = 305,
	INPUT_REPLAY_ENDPOINT = 306,
	INPUT_REPLAY_ADVANCE = 307,
	INPUT_REPLAY_BACK = 308,
	INPUT_REPLAY_TOOLS = 309,
	INPUT_REPLAY_RESTART = 310,
	INPUT_REPLAY_SHOWHOTKEY = 311,
	INPUT_REPLAY_CYCLEMARKERLEFT = 312,
	INPUT_REPLAY_CYCLEMARKERRIGHT = 313,
	INPUT_REPLAY_FOVINCREASE = 314,
	INPUT_REPLAY_FOVDECREASE = 315,
	INPUT_REPLAY_CAMERAUP = 316,
	INPUT_REPLAY_CAMERADOWN = 317,
	INPUT_REPLAY_SAVE = 318,
	INPUT_REPLAY_TOGGLETIME = 319,
	INPUT_REPLAY_TOGGLETIPS = 320,
	INPUT_REPLAY_PREVIEW = 321,
	INPUT_REPLAY_TOGGLE_TIMELINE = 322,
	INPUT_REPLAY_TIMELINE_PICKUP_CLIP = 323,
	INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP = 324,
	INPUT_REPLAY_TIMELINE_PLACE_CLIP = 325,
	INPUT_REPLAY_CTRL = 326,
	INPUT_REPLAY_TIMELINE_SAVE = 327,
	INPUT_REPLAY_PREVIEW_AUDIO = 328,
	INPUT_VEH_DRIVE_LOOK = 329,
	INPUT_VEH_DRIVE_LOOK2 = 330,
	INPUT_VEH_FLY_ATTACK2 = 331,
	INPUT_RADIO_WHEEL_UD = 332,
	INPUT_RADIO_WHEEL_LR = 333,
	INPUT_VEH_SLOWMO_UD = 334,
	INPUT_VEH_SLOWMO_UP_ONLY = 335,
	INPUT_VEH_SLOWMO_DOWN_ONLY = 336,
	INPUT_MAP_POI = 337
};
void superbrakes(bool toggle)
{
	if (toggle)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if ((CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_VEH_BRAKE) && ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, true).y > 1.f) ||
			(CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_VEH_ACCELERATE) && ENTITY::GET_ENTITY_SPEED_VECTOR(vehicle, true).y < -1.f))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.f);
		}
	}
	else
	{

	}
}

void numberplatesfindvehicle() {
	if (amphetamine::amphetamine_settings->getvehicllenumberplates) {
		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
		if (!ReplayInterface)
			return;
		hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
		if (!VehicleInterface)
			return;
		for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {

			hk_Vehicle* Peds = VehicleInterface->VehicleList()->Vehicle(i);
			if (!Peds) continue;

			auto GET_NUMBER_VEHICLE = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(Memory::pointer_to_handle((DWORD64)Peds));

			if (GET_NUMBER_VEHICLE == amphetamine::amphetamine_settings->plate_textgetveh) {
				ImVec2 vScreenPosition = Memory::WorldToScreen(Peds->GetCoordinate());
				Visuals::DrawOutlinedText(font::poppins_medium_low, "VEHILE NUMBER PLATES", ImVec2(vScreenPosition.x, vScreenPosition.y), 17.f, ImColor(amphetamine::amphetamine_settings->object_color), true);

			}
		}
	}
}
bool NightVision = false;
void nightvision(bool toggle)
{
	if (global::Panic || global::Panicnoclear) {
		if (NightVision == true) {
			GRAPHICS::SET_NIGHTVISION(false);
			NightVision = false;
		}
	}
	else {
		if (toggle)
		{
			GRAPHICS::SET_NIGHTVISION(true);
			NightVision = true;
		}
		else
		{
			if (NightVision == true) {
				GRAPHICS::SET_NIGHTVISION(false);
				NightVision = false;
			}
		}
	}
}
bool ThermalVision = false;
void thermalvision(bool toggle)
{
	if (global::Panic || global::Panicnoclear) {
		if (ThermalVision == true) {
			GRAPHICS::SET_SEETHROUGH(false);
			ThermalVision = false;
		}
	}
	else {
		if (toggle)
		{
			GRAPHICS::SET_SEETHROUGH(true);
			ThermalVision = true;
		}
		else
		{
			if (ThermalVision == true) {
				GRAPHICS::SET_SEETHROUGH(false);
				ThermalVision = false;
			}
		}
	}
}
void slideRun()
{
	if (global::Panic || global::Panicnoclear) {
	}
	else {
		if (amphetamine::amphetamine_settings->isSlideRun) {
			Ped ped = PLAYER::PLAYER_PED_ID();

			if (AI::IS_PED_RUNNING(ped) || AI::IS_PED_SPRINTING(ped))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.f, 1.5f, 0.f, 0.f, 0.f, 0.f, 1, true, true, true, false, true);
			}
		}
	}
}
bool checkvehicle_collision = false;
void vehicle_collision(bool toggle)
{
	if (global::Panic || global::Panicnoclear) {
		if (checkvehicle_collision == true) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true);
			}
			checkvehicle_collision = false;
		}
	}
	else {
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false, true);
			}

			checkvehicle_collision = true;
		}
		else
		{
			if (checkvehicle_collision == true) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
				{
					ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true);
				}
				checkvehicle_collision = false;
			}
		}
	}
}

void vehicle_auto_fix(bool toggle)
{
	if (toggle)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
		{
			if (VEHICLE::_IS_VEHICLE_DAMAGED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)))
			{
				VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			}
			VEHICLE::_0x1AA8A837D2169D94(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
			VEHICLE::SET_VEHICLE_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true, false);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		}
	}
}


bool is_ped_shooting(Ped ped) {
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
}
bool is_ped_aiming(Ped ped)
{
	return PED::GET_PED_CONFIG_FLAG(ped, 78, true);
}
Entity get_raycast_entity()
{
	Vector3 cam_coord = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 cam_dir = RotationToDirectionV3(cam_rot);
	static Entity entity;

	static float start_x, start_y, start_z, end_x, end_y, end_z;
	static int hit;
	static int ent;

	start_x = cam_coord.x + cam_dir.x;
	start_y = cam_coord.y + cam_dir.y;
	start_z = cam_coord.z + cam_dir.z;

	end_x = cam_coord.x + (cam_dir.x * 0x800);
	end_y = cam_coord.y + (cam_dir.y * 0x800);
	end_z = cam_coord.z + (cam_dir.z * 0x800);

	int handle = WORLDPROBE::_START_SHAPE_TEST_RAY(start_x, start_y, start_z, end_x, end_y, end_z, -1, 0, true);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(handle, &hit, &Vector3(end_x, end_y, end_z), &Vector3(start_x, start_y, start_z), &entity);

	if (entity == NULL)
		return 0;
	if (!ENTITY::DOES_ENTITY_EXIST(entity))
		return 0;

	return entity;
}


void set_entity_velocity(std::int32_t entity, Vector3 velocity)
{
	if (!ENTITY::DOES_ENTITY_EXIST(entity))
		return;

	Vector3 coords = ENTITY::GET_ENTITY_COORDS(entity, false);
	ENTITY::SET_ENTITY_VELOCITY(entity, (velocity.x - coords.x) * amphetamine::amphetamine_settings->m_gravityvelocity, (velocity.y - coords.y) * amphetamine::amphetamine_settings->m_gravityvelocity, (velocity.z - coords.z) * amphetamine::amphetamine_settings->m_gravityvelocity);
}
void Get_Entity_From_RayCast_Hit()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 CamCrd = CAM::GET_GAMEPLAY_CAM_COORD(); Vector3 CamRot = CAM::GET_GAMEPLAY_CAM_ROT(1);
	Vector3 CamCoords = PED::GET_PED_BONE_COORDS(player, 0x0, 0.f, 0.f, 0.f);
	Vector3 FarCoords = add(&CamCrd, &multiply(&RotationToDirectionV3(CamRot), 1000.f));
	int RayHandle = WORLDPROBE::_START_SHAPE_TEST_RAY(CamCoords.x, CamCoords.y, CamCoords.z, FarCoords.x, FarCoords.y, FarCoords.z, -1, player, 7);

	BOOL RayCastHit; Vector3 RayHitCoords, surfaceNormalVector; Entity EntityHandle;
	int RayResult = WORLDPROBE::GET_SHAPE_TEST_RESULT(RayHandle, &RayCastHit, &RayHitCoords, &surfaceNormalVector, &EntityHandle);
	GRAPHICS::DRAW_LINE(CamCoords.x, CamCoords.y, CamCoords.z, FarCoords.x, FarCoords.y, FarCoords.z, 255, 0, 0, 255);
	Vector3 NormalVector = add(&RayHitCoords, &multiply(&surfaceNormalVector, 5.f));
	GRAPHICS::DRAW_LINE(RayHitCoords.x, RayHitCoords.y, RayHitCoords.z, NormalVector.x, NormalVector.y, NormalVector.z, 0, 0, 255, 255);
}
void auto_pilot() {
	if (amphetamine::amphetamine_settings->auto_pilot) {
		//bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
		//if (is_in_vehicle) {
		//	//type::any blip = native::ui::get_first_blip_info_id(8);
		//	//if (ui::does_blip_exist(blip)) {
		//	//auto tpos = native::ui::get_blip_coords(blip);
		//	//float z = 0.0f;


		//	Ped player = PLAYER::PLAYER_PED_ID();
		//	//Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
		//	Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(-1), false);


		//	AI::TASK_VEHICLE_DRIVE_WANDER(player, Veh, 40.f, 786603);
		//	//AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(player, Veh, tpos.x, tpos.y, tpos.z, 40.f, 786603, 30.f);
		////}
		//}

	}
}
static bool freecamCreated = false;
type::cam freecamEntity;
Vector3 GetLookAtCoordinates(Vector3* normal)
{
	auto player = player::player_ped_id();
	Vector3 pLoooAt = get_gameplay_cam_front_coords(0x2000);
	rage::padvec3 pBone = ped::get_ped_bone_coords(player, 0x796E, 0.f, 0.f, 0.f);
	int rHandle = worldprobe::_start_shape_test_ray(pBone.x, pBone.y, pBone.z, pLoooAt.x, pLoooAt.y, pLoooAt.z, -1, player, 7);
	bool RayCastHit;
	rage::padvec3 RayHitCoords, surfaceNormalVector;
	rage::type::entity Entity;
	int rayResult = worldprobe::get_shape_test_result(rHandle, &RayCastHit, &RayHitCoords, &surfaceNormalVector, &Entity);

	if (RayCastHit) {
		*normal = Vector3(surfaceNormalVector.x, surfaceNormalVector.y, surfaceNormalVector.z);
		return Vector3(RayHitCoords.x, RayHitCoords.y, RayHitCoords.z);
	}

	return { 0.f, 0.f, 0.f };
}
Vector3 GetCoordsInfrontOfCam(float distance) //GetCoordAimingAhead
{
	Vector3 GameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 GameplayCamCoord = CAM::GET_GAMEPLAY_CAM_COORD();

	float tan = cos(GameplayCamRot.y) * distance;
	float xPlane = (sin(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.y;
	float yPlane = (cos(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.y;
	float zPlane = (sin(GameplayCamRot.y) * distance) + GameplayCamCoord.z;

	Vector3 Output;
	Output.x = xPlane;
	Output.y = yPlane;
	Output.z = zPlane;

	return Output;
}
void clickwarp_player() {





	DWORD64 addr = Memory::GetCameraqw();

	bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
	type::any entity;

	if (!is_in_vehicle) {
		entity = player::get_player_ped(-1);
	}
	else
	{
		entity = ped::get_vehicle_ped_is_in(player::get_player_ped(-1), false);
	}



	//Vector3 get_entity_cords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	//Vector3 get_entity_cords = *(Vector3*)(Memory::LocalPlayer + 0x90);
	////	Vector3 get_entity_cords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	//	//Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	//Vector3 dir = RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(3));

	//Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	////Vector3 cam_rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);




	////Radar.AddPoint(localpos, rot, pedPos, ImColor(c::menu_sett::menu_color_swither), amphetamine::amphetamine_settings->radar_type, 1 /*pPawn->m_angEyeAngles_vec2().y*/);

	////camCoords = camCoordsPS;
	////Vector3 dir = cam_rot;

	////Vector3 cam_rot___ = click_warp_funk();

	////GRAPHICS::DRAW_LINE(cam_rot___.x, cam_rot___.y, cam_rot___.z, get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, 0, 255, 255, 255);
	////GRAPHICS::DRAW_LINE(get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, cam_rot___.x, cam_rot___.y, cam_rot___.z, 255, 255, 255, 255);


	////float distance_3d = get_distance_between_coords_3d(get_entity_cords, dir);


	////Vector3 cur_pos_dir = Vector3((dir.x * .5) + get_entity_cords.x, (dir.y * .5) + get_entity_cords.y, (dir.z * .5) + get_entity_cords.z);

	////Vector3 for_away = Vector3((dir.x * 250) + cur_pos_dir.x, (dir.y * 250) + cur_pos_dir.y, (dir.z * 250) + cur_pos_dir.z);

	////GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD();
	////Vector3 cam_coords = get_gameplay_cam_front_coords(entity_distance);
	////set_entity_velocity(lock, cam_coords);

	//





	//static Entity entity;

	//Vector3 start, end;
	//static int hit;
	//static int ent;

	//start.x = camCoords.x + dir.x;
	//start.y = camCoords.y + dir.y;
	//start.z = camCoords.z + dir.z;

	//end.x = camCoords.x * (dir.x * 10000 );
	//end.y = camCoords.y * (dir.y * 10000);
	//end.z = camCoords.z * (dir.z * 10000);

	//int handle = WORLDPROBE::_START_SHAPE_TEST_RAY(start.x, start.y, start.z, end.x, end.y, end.z, -1, 0, 0); // -1, 0, 7
	//WORLDPROBE::GET_SHAPE_TEST_RESULT(handle, &hit, &end, &start, &entity);
	////GRAPHICS::DRAW_LINE(end_x, end_y, end_z, get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, 0, 0, 255, 255);

	//Vector3 NormalVector = add(&end, &multiply(&start, 5.f));
	////GRAPHICS::DRAW_LINE(end_x, end_y, end_z, NormalVector.x, NormalVector.y, NormalVector.z, 0, 0, 255, 255);

	////Vector3 GETED_ENTITY_COORDS = ENTITY::GET_ENTITY_COORDS(entity, false);


	////GRAPHICS::DRAW_LINE(get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, GETED_ENTITY_COORDS.x, GETED_ENTITY_COORDS.y, GETED_ENTITY_COORDS.z, 255, 0, 255, 255);
	//GRAPHICS::DRAW_LINE(end.x, end.y, end.z, get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, 255, 0, 255, 255);

	//GRAPHICS::DRAW_LINE(NormalVector.x, NormalVector.y, NormalVector.z, get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, 255, 0, 255, 255);

	//GRAPHICS::DRAW_LINE(get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, NormalVector.x, NormalVector.y, NormalVector.z, 255, 0, 255, 255);

	//char* lololol = (char*)std::to_string(end.x).c_str();
	//GRAPHICS::DRAW_DEBUG_TEXT_2D(lololol, get_entity_cords.x, get_entity_cords.y, get_entity_cords.z, 255, 0, 255, 255);
	//if (amphetamine::amphetamine_settings->clickwarpvehicle)
	//	Get_Entity_From_RayCast_Hit();

	//Vector3 normal;
	//Vector3 look_cords = GetLookAtCoordinates(&normal);
	auto player = player::player_ped_id();
	rage::padvec3 pBone = ped::get_ped_bone_coords(player, 0x796E, 0.f, 0.f, 0.f);
	
	//Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 pLoooAt = get_gameplay_cam_front_coords(5000);

	//DWORD64 pMyFPSAngles = *(DWORD64*)(addr + 0x03C0);


	//rot = acosf(CamRotFPS.x) * 180.0f / DirectX::XM_PI;
	//if (asinf(CamRotFPS.y) * 180.0f / DirectX::XM_PI < 0.0f) rot *= -1.0f;

	//float radiansZ = CamRotFPS.z * 0.0174532924f;
	//float radiansX = CamRotFPS.x * 0.0174532924f;
	//float num = std::abs((float)std::cos((double)radiansX));
	//rot = num;
	//dir.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
	

	Vector3 CrosshairPos = *(Vector3*)(addr + 0x60);
	//CrosshairPos.z = 1000;
	using namespace Memory;
	Vector3 tmp;
	tmp.y = (viewPort->fViewMatrix[2]) + (viewPort->fViewMatrix[6]) + (viewPort->fViewMatrix[10]) + viewPort->fViewMatrix[14];	//row 3
	tmp.x = (Memory::viewPort->fViewMatrix[1]) + (viewPort->fViewMatrix[5]) + (viewPort->fViewMatrix[9]) + viewPort->fViewMatrix[13];
	tmp.z = (viewPort->fViewMatrix[3]) + (viewPort->fViewMatrix[7]) + (viewPort->fViewMatrix[11]) + viewPort->fViewMatrix[15];	//row 4

	//rot = rot - (M_PI / 360.0f);
	int rHandle = worldprobe::_start_shape_test_ray(pBone.x, pBone.y, pBone.z, tmp.z, tmp.x, tmp.y, -1, player, 7);//  -1
	bool RayCastHit;
	rage::padvec3 RayHitCoords, surfaceNormalVector;
	rage::type::entity Entity;
	int rayResult = worldprobe::get_shape_test_result(rHandle, &RayCastHit, &RayHitCoords, &surfaceNormalVector, &Entity);
	
	/*GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, CrosshairPos.x, CrosshairPos.y, CrosshairPos.z, 255, 0, 255, 255);
	GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, cam_root.x, cam_root.y, cam_root.z, 255, 0, 255, 255);
	GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, cam_root_2.x, cam_root_2.y, cam_root_2.z, 255, 0, 255, 255);
	GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, camCoords.x, camCoords.y, camCoords.z, 255, 0, 255, 255);*/

	//if (RayCastHit) 
	{
		//return Vector3(RayHitCoords.x, RayHitCoords.y, RayHitCoords.z);
		

		
				//row 2
		//tmp.y = (viewPort->fViewMatrix[2]) + (viewPort->fViewMatrix[6]) + (viewPort->fViewMatrix[10]) + viewPort->fViewMatrix[14];	//row 3
		
		GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, CrosshairPos.x, CrosshairPos.y, CrosshairPos.z, 255, 255, 255, 255);


	//	GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, RayHitCoords.x, RayHitCoords.y, RayHitCoords.z, 255, 0, 255, 255);
		GRAPHICS::DRAW_LINE(pBone.x, pBone.y, pBone.z, RayHitCoords.x, RayHitCoords.y, RayHitCoords.z, 255, 0, 255, 255);
	

		if (amphetamine::amphetamine_settings->healkey != 0) {
			if (GetAsyncKeyState(amphetamine::amphetamine_settings->healkey) & 0x8000) {
				if (health_otmena == false) {

					
				

					native::entity::set_entity_coords_no_offset(entity, RayHitCoords.x, RayHitCoords.y, RayHitCoords.z, true, true, true);
					//native::entity::set_entity_coords_no_offset(entity, CrosshairPos.x, CrosshairPos.y, CrosshairPos.z, true, true, true);


					health_otmena = true;
				}
			}
			else {
				health_otmena = false;
			}
		}

	}
}
		
		
	



void gravitygun(bool toggle)
{
	if (toggle)
	{
		static float entity_distance;
		static std::int32_t picked, lock, last_entity;
		static float zoom = 10.f;
		if (is_ped_aiming(PLAYER::PLAYER_PED_ID()))
		{
			picked = get_raycast_entity();

			RequestControlOfEnt(picked);
			if (ENTITY::DOES_ENTITY_EXIST(picked))
			{
				RequestControlOfEnt(picked);
				if (!lock && last_entity != picked && get_distance_between_coords_3d(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), ENTITY::GET_ENTITY_COORDS(picked, false)) <= 285.5f)
				{
					entity_distance = zoom;
					lock = picked;
				}
			}

			RequestControlOfEnt(picked);
			if (is_ped_shooting(PLAYER::PLAYER_PED_ID()))
			{
				entity_distance = 2000.0f;
				last_entity = lock;
			}
			RequestControlOfEnt(picked);
			Vector3 cam_coords = get_gameplay_cam_front_coords(entity_distance);
			set_entity_velocity(lock, cam_coords);
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, 261) && zoom < 20.f)
			{
				zoom += 1.f;
			}
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, 262) && zoom > 5.f)
			{
				zoom -= 1.f;
			}
		}
		else if (lock)
			lock = false;
	}
}
Vector3 AddV3(Vector3 vectorA, Vector3 vectorB) {
	Vector3 result;
	result.x = vectorA.x;
	result.y = vectorA.y;
	result.z = vectorA.z;
	result.x += vectorB.x;
	result.y += vectorB.y;
	result.z += vectorB.z;
	return result;
}
Vector3 MultiplyV3(Vector3 vector, float x) {
	Vector3 result;
	result.x = vector.x;
	result.y = vector.y;
	result.z = vector.z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}
float speedqq = 0.5f;
float mult = 0.f;

Cam camera = -1;
Vector3 position;
Vector3 rotation;
static const ControllerInputs controlsQ[] = { ControllerInputs::INPUT_LOOK_LR, ControllerInputs::INPUT_LOOK_UD, ControllerInputs::INPUT_LOOK_UP_ONLY, ControllerInputs::INPUT_LOOK_DOWN_ONLY, ControllerInputs::INPUT_LOOK_LEFT_ONLY, ControllerInputs::INPUT_LOOK_RIGHT_ONLY, ControllerInputs::INPUT_LOOK_LEFT, ControllerInputs::INPUT_LOOK_RIGHT, ControllerInputs::INPUT_LOOK_UP, ControllerInputs::INPUT_LOOK_DOWN };

namespace freecam {
	Vector3 rot;
	Vector3 pos;
	Vector3 vecX;
	Vector3 vecY;
	Vector3 vecZ;

	type::any target_entity;
}
struct RawRaycastResult {
	int Result = 0;
	bool DidHitAnything = false;
	bool DidHitEntity = false;
	DWORD HitEntity = (DWORD)0;
	Vector3 HitCoords;
};


typedef struct
{
	int Result;
	bool DidHitAnything;
	bool DidHitEntity;
	int32_t HitEntity;
	Vector3 HitCoords;
	Vector3 HitNormal;
} RaycastResult;

float to_rad(float e) {
	return (e * 3.14159265) / 180;
}
void update_vec(Vector3 rot) {
	float radX = to_rad(rot.x);
	float radY = to_rad(rot.y);
	float radZ = to_rad(rot.z);

	float sinX = sin(radX);
	float sinY = sin(radY);
	float sinZ = sin(radZ);
	float cosX = cos(radX);
	float cosY = cos(radY);
	float cosZ = cos(radZ);

	Vector3 vecX;
	Vector3 vecY;
	Vector3 vecZ;

	vecX.x = cosY * cosZ;
	vecX.y = cosY * sinZ;
	vecX.z = -sinY;

	vecY.x = cosZ * sinX * sinY - cosX * sinZ;
	vecY.y = cosX * cosZ - sinX * sinY * sinZ;
	vecY.z = cosY * sinX;

	vecZ.x = -cosX * cosZ * sinY + sinX * sinZ;
	vecZ.y = -cosZ * sinX + cosX * sinY * sinZ;
	vecZ.z = cosX * cosY;

	freecam::vecX = Vector3(vecX.x, vecX.y, vecX.z);
	freecam::vecY = Vector3(vecY.x, vecY.y, vecY.z);
	freecam::vecZ = Vector3(vecZ.x, vecZ.y, vecZ.z);
}

void debugcamera() {
	using namespace native;

	cam::_0x9e4cfff989258472();
	cam::_f4f2c0d4ee209e20();

	if (freecamCreated && !amphetamine::amphetamine_settings->debugcamera) {
		//Destroy freecam


		freecamCreated = false;
		cam::destroy_cam(freecamEntity, false);


		player::set_player_control(native::player::player_id(), true, (1 << 8));
		cam::render_script_cams(false, false, 0, false, false);

		freecamEntity = 0;
		return;
	}
	if (amphetamine::amphetamine_settings->debugcamera) {
		//freecamCreated = true;
		if (!CAM::DOES_CAM_EXIST(freecamEntity)) {
			freecamEntity = native::cam::create_cam("DEFAULT_SCRIPTED_CAMERA", 0);
			cam::set_cam_fov(freecamEntity, amphetamine::amphetamine_settings->freecam_fov);

			auto gameplay_cam_pos = cam::get_gameplay_cam_coord();
			auto gameplay_cam_rot = cam::get_gameplay_cam_rot(2);



			freecam::rot = Vector3(gameplay_cam_rot.x, gameplay_cam_rot.y, gameplay_cam_rot.z);
			freecam::pos = Vector3(gameplay_cam_pos.x, gameplay_cam_pos.y, gameplay_cam_pos.z);
			cam::set_cam_coord(freecamEntity, gameplay_cam_pos.x, gameplay_cam_pos.y, gameplay_cam_pos.z);
			cam::set_cam_rot(freecamEntity, gameplay_cam_rot.x, gameplay_cam_rot.y, gameplay_cam_rot.z, 2);

			cam::set_cam_active(freecamEntity, true);
			//player::set_player_control(native::player::player_id(), false, (1 << 8));
			cam::render_script_cams(true, true, 500, true, true);
		}
		//return;
	}

	if (freecamCreated && freecamEntity && amphetamine::amphetamine_settings->debugcamera) {
		auto lookX = controls::get_disabled_control_normal(0, 1);
		auto lookY = controls::get_disabled_control_normal(0, 2);

		auto moveX = controls::get_disabled_control_normal(0, 30);
		auto moveY = controls::get_disabled_control_normal(0, 31);

		auto moveZ1 = controls::get_disabled_control_normal(0, 152);
		auto moveZ2 = controls::get_disabled_control_normal(0, 153);


		freecam::rot.x = freecam::rot.x + (-lookY * 5);
		freecam::rot.z = freecam::rot.z + (-lookX * 5);
		freecam::rot.y = freecam::rot.y;


		float speedMultiplier = amphetamine::amphetamine_settings->freecam_speed;
		freecam::pos = freecam::pos + (freecam::vecX * moveX * speedMultiplier);
		freecam::pos = freecam::pos + (freecam::vecY * -moveY * speedMultiplier);

		if (moveZ1) {
			freecam::pos = freecam::pos + (freecam::vecZ * -1 * speedMultiplier);
		}
		else if (moveZ2) {
			freecam::pos = freecam::pos + (freecam::vecZ * 1 * speedMultiplier);
		}

		cam::set_cam_coord(freecamEntity, freecam::pos.x, freecam::pos.y, freecam::pos.z);
		cam::set_cam_rot(freecamEntity, freecam::rot.x, freecam::rot.y, freecam::rot.z, 0);



		cam::set_cam_fov(freecamEntity, amphetamine::amphetamine_settings->freecam_fov);

		update_vec(freecam::rot);


		//if (amphetamine::amphetamine_settings->debugcamera) {

		//	PVector3 HitNormal = PVector3(0, 0, 0);
		//	PVector3 HitCoords = PVector3(0, 0, 0);
		//	Vector3 target;
		//	Vector3 start;
		//	start = freecam::pos + (freecam::vecX * 1);
		//	start = freecam::pos + (freecam::vecY * 1);
		//	start = freecam::pos + (freecam::vecZ * 1);


		//	target = freecam::pos + (freecam::vecX * 1000000);
		//	target = freecam::pos + (freecam::vecY * 1000000);

		//	RaycastResult result;
		//	worldprobe::get_shape_test_result(worldprobe::start_shape_test_capsule(start.x, start.y, start.z,
		//		target.x, target.y, target.z, 0.2f, IntersectVehicles, 0, 7), (bool*)&result.DidHitAnything, &result.HitCoords, &result.HitNormal, &result.HitEntity);



		//	if (result.DidHitAnything) {
		//		if (result.HitEntity) {
		//			if (player::get_player_ped(-1) != result.HitEntity) {
		//				freecam::target_entity = result.HitEntity;
		//				auto snatch = controls::is_disabled_control_just_pressed(0, 24);
		//				if (snatch) {
		//					auto pos = local.player->fPosition;
		//					native::entity::set_entity_coords_no_offset(freecam::target_entity, pos.x + 1, pos.y + 1, pos.z, true, true, true);
		//				}
		//			}
		//			else {
		//				freecam::target_entity = 0;
		//			}
		//		}
		//		else {
		//			freecam::target_entity = 0;
		//		}
		//	}
		//	else {
		//		freecam::target_entity = 0;
		//	}

		//}

	}

}

namespace freecam_era {


	inline float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}
	using joaat_t = std::uint32_t;
	inline constexpr char joaat_to_lower(char c)
	{
		return c >= 'A' && c <= 'Z' ? c | 1 << 5 : c;
	}

	inline constexpr joaat_t joaat(const std::string_view str)
	{
		joaat_t hash = 0;
		for (auto c : str)
		{
			hash += joaat_to_lower(c);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}
	void on_tick()
	{

		if (amphetamine::amphetamine_settings->debugcamera) {
			float speed = 0.5f;
			float mult = 0.f;

			Cam camera = -1;
			Vector3 position;
			Vector3 rotation;

			if (camera == -1) {
				//char* xuixuix = "DEFAULT_SCRIPTED_CAMERA";
				//camera = CAM::CREATE_CAM("FRONTAL_CAMERA", 0);
				camera = CAM::CREATE_CAMERA(joaat("DEFAULT_SCRIPTED_CAMERA"), 0);

				
				//camera = CAM::GET_RENDERING_CAM();
				position = CAM::GET_GAMEPLAY_CAM_COORD();
				rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
				//////////////////////////////camera = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", position.x, position.y, position.z, 0.0, 0.0, 0.0, 40.0, 1, 2);


				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);

				CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
				CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
				CAM::SET_CAM_ACTIVE(camera, true);
				CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true);
			}





			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);

			for (const auto& control : controlsQ)
				CONTROLS::ENABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

			Vector3 vecChange = { 0.f, 0.f, 0.f };
			

			//if (can_update_location())
			{
				// Left Shift
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
					vecChange.z += speed / 2;
				// Left Control
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
					vecChange.z -= speed / 2;
				// Forward
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
					vecChange.y += speed;
				// Backward
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
					vecChange.y -= speed;
				// Left
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
					vecChange.x -= speed;
				// Right
				if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
					vecChange.x += speed;
			}

			if (vecChange.x == 0.f && vecChange.y == 0.f && vecChange.z == 0.f)
				mult = 0.f;
			else if (mult < 10)
				mult += 0.15f;

			Vector3 rot = CAM::GET_CAM_ROT(camera, 2);
			//float pitch = math::deg_to_rad(rot.x); // vertical
			//float roll = rot.y;
			float yaw = deg_to_rad(rot.z); // horizontal

			position.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
			position.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
			position.z += vecChange.z * mult;

			CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
			STREAMING::_SET_FOCUS_AREA(position.x, position.y, position.z, 0.f, 0.f, 0.f);

			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
		}
		if (!amphetamine::amphetamine_settings->debugcamera && camera != -1) {
		//	CAM::SET_CAM_ACTIVE(camera, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true);
			//CAM::DESTROY_CAM(camera, false);
			STREAMING::CLEAR_FOCUS();

			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
		}
	}

}

bool IsVisibleAimBot(DWORD64 pPed, DWORD64 Peddd) {
	auto handle = Memory::pointer_to_handle(pPed);
	auto handle1 = Memory::pointer_to_handle(Peddd);
	if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(handle1, handle, 17)) {

		return true;
	}
	return false;
}

bool proverkanapidoraclickflipvehicle = false;
void clickflipvehicle(bool toggle)
{
	if (global::Panic || global::Panicnoclear) {
	}
	else {
		if (toggle)
		{
			if (GetAsyncKeyState(amphetamine::amphetamine_settings->clickflipvehiclekey) & 0x8000) {
				if (proverkanapidoraclickflipvehicle == false) {
					auto veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					float roll = ENTITY::GET_ENTITY_ROLL(veh);
					if (!ENTITY::IS_ENTITY_IN_AIR(veh) && !ENTITY::IS_ENTITY_IN_WATER(veh) && !VEHICLE::IS_THIS_MODEL_A_PLANE(veh) && !VEHICLE::IS_THIS_MODEL_A_HELI(veh))
					{
						RequestControlOfEnt(veh);
						ENTITY::SET_ENTITY_ROTATION(veh, 0, 0, ENTITY::GET_ENTITY_ROTATION(veh, 2).z, 2, 1);
					}
					proverkanapidoraclickflipvehicle = true;
				}
			}
			else {
				proverkanapidoraclickflipvehicle = false;
			}
		}
	}
}
//enum Bones {
//	SKEL_Head = 0x0,
//	SKEL_L_Foot = 0x1,
//	SKEL_R_Foot = 0x2,
//	SKEL_L_Ankle = 0x3,
//	SKEL_R_Ankle = 0x4,
//	SKEL_L_Wrist = 0x5,
//	SKEL_R_Wrist = 0x6,
//	SKEL_Neck = 0x7,
//	SKEL_Spine = 0x8,
//};

static int selected_clicl_warp_vehiucle = 1;
bool probfsndggdfkhjdkgh = false;
void click_warp_vehicle() {
	if (amphetamine::amphetamine_settings->clickwarpvehicle && GetAsyncKeyState(amphetamine::amphetamine_settings->clickwarp_vehicle_int_hot_key)) {
		hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
		if (!ReplayInterface)
			return;
		hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
		if (!VehicleInterface)
			return;
		auto get_distance = [](double x1, double y1, double x2, double y2) {
			return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
			};
		auto center_x = ImGui::GetIO().DisplaySize.x / 2;
		auto center_y = ImGui::GetIO().DisplaySize.y / 2;

		auto draw_list = ImGui::GetBackgroundDrawList();

		draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), 4.5 * 10, ImColor(0, 0, 0, 255), 35, 3.6f);
		draw_list->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), 4.5 * 10, ImColor(255, 0, 0, 255), 35, 2.f);


		for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {
			hk_Vehicle* Peds = VehicleInterface->VehicleList()->Vehicle(i);
			if (!Peds) continue;
			Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
			if (Aimbot::get_distance(localpos, Peds->GetCoordinate()) > 200)
				continue;
			ImVec2 peds_location = Memory::WorldToScreen(Peds->GetCoordinate());
			if (!IsOnScreen(peds_location)) continue;
			Vector3 peds_locationq = Peds->GetCoordinate();
			ImVec2 screen = Memory::WorldToScreen(peds_locationq);
			auto fov = get_distance(center_x, center_y, screen.x, screen.y);
			if (fov < 5 * 10)
			{
				selected_clicl_warp_vehiucle = i;
			}
		}



		hk_Vehicle* SelectedPed = VehicleInterface->VehicleList()->Vehicle(selected_clicl_warp_vehiucle);
		if (SelectedPed->GetCoordinate().x != 0)
		{
			auto playerName = SelectedPed->VehicleModelInfo()->GetCharName();
			ImVec2 peds_location = Memory::WorldToScreen(SelectedPed->GetCoordinate());
			if (!IsOnScreen(peds_location)) return;

			ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName);
			Visuals::DrawOutlinedText(font::poppins_medium_low, playerName, ImVec2(peds_location.x - TextSize.x / 2, peds_location.y), 22.f, ImColor(c::menu_sett::menu_color_swither), true);



			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (probfsndggdfkhjdkgh == false) {
					//rage::native_queue->native_emplace([&]
						//{
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
					//}
			//	);

					probfsndggdfkhjdkgh = true;
				}
			}
			else {
				if (probfsndggdfkhjdkgh == true) {
					probfsndggdfkhjdkgh = false;
				}
			}

		}
	}
}

bool checkfmlkdsgmslfgm = false;
void skip_anim_localplayer() {
	if (amphetamine::amphetamine_settings->skipanimaka)
	{
		if (GetAsyncKeyState(amphetamine::amphetamine_settings->TpToWaypointkey) & 0x8000) {
			set_value<DWORD>({ 0x08, 0x10A8, 0x10B8 }, 0x01); //rogdool
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
			checkfmlkdsgmslfgm = true;
		}
		else
		{
			if (checkfmlkdsgmslfgm == true) {

				set_value<DWORD>({ 0x08, 0x10A8, 0x10B8 }, 0x20);
				PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
				PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
				checkfmlkdsgmslfgm = false;
			}
		}

	}


}
