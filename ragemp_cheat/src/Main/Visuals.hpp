inline ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));


#include <direct.h>
#include "../SimpleIni.h"
#include <shellapi.h>
CSimpleIniA cfg;
D3DCOLOR FLOAT4TOD3rwerLOR(ImColor Col)
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
inline void DrawHealthBarhorizontal(ImVec2 pos, ImVec2 pos2, ImVec2 dim, ImColor col)
{
	if (IsOnScreen(pos))
	{
		Render_D2::Line(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), FLOAT4TOD3rwerLOR(col), dim.x, true);
		//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), col, dim.x);
	}
}
inline void DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col)
{
	if (IsOnScreen(pos))
	{

		Render_D2::Line(pos, ImVec2(pos.x, pos.y - dim.y), FLOAT4TOD3rwerLOR(col), dim.x, true);
		//ImGui::GetBackgroundDrawList()->AddLine(pos, ImVec2(pos.x, pos.y - dim.y), FLOAT4TOD3rwerLOR(col), dim.x);
	}
}
namespace Visuals
{
	std::map<int32_t, std::string>m_save_hash;
	static char toAddHash[64] = "";
	inline const char* get_weapon_name(DWORD hash)
	{
		//removed xoring, cba to do properly.
		const char* dagger = ("Dagger");
		const char* bat = ("Bat");
		const char* bottle = ("Bottle");
		const char* crowbar = ("Crow Bar");
		const char* unarmed = ("None");
		const char* flashlight = ("Flash Light");
		const char* golfclub = ("Golf club");
		const char* hammer = ("Hammer");
		const char* hatchet = ("Hatchet");
		const char* knuckle = ("Knuckle");
		const char* knife = ("Knife");
		const char* machete = ("Machete");
		const char* switchblade = ("Switch Blade");
		const char* nightstick = ("Night Stick");
		const char* wrench = ("Wrench");
		const char* battleaxe = ("Battle Axe");
		const char* poolcue = ("Pool Cue");
		const char* pistol = ("Pistol");
		const char* pistolmk2 = ("Pistol MK2");
		const char* combatpistol = ("Combat Pistol");
		const char* appistol = ("AP Pistol");
		const char* stungun = ("Stungun");
		const char* pistol50 = ("Pistol 50");
		const char* snspistol = ("SNS PISTOL");
		const char* snspistolmk2 = ("SNS Pistol MK2");
		const char* heavypistol = ("Heavy Pistol");
		const char* vintagepistol = ("Vintage Pisol");
		const char* flaregun = ("Flare Gun");
		const char* marksmanpistol = ("marksmanpistol");
		const char* revolver = ("Revolver");
		const char* revolvermk2 = ("Revolver MK2");
		static auto doubleaction = ("Double Action");
		static auto microsmg = ("Micro Smg");
		static auto smg = ("Smg");
		static auto smgmk2 = ("Smg MK2");
		static auto assaultsmg = ("Assault Smg");
		static auto combatpdw = ("Combat PDW");
		static auto machinepistol = ("Machine Pistol");
		static auto minismg = ("Mini Smg");
		static auto pumpshotgun = ("Pump Shotgun");
		static auto pumpshotgun_mk2 = ("Pump Shotgun MK2");
		static auto sawnoffshotgun = ("Sawnoff Shotgun");
		static auto assaultshotgun = ("Sssault Shotgun");
		static auto bullpupshotgun = ("Bullpup Shotgun");
		static auto musket = ("Musket");
		static auto heavyshotgun = ("Heavy Shotgun");
		static auto dbshotgun = ("DB Shotgun");
		static auto autoshotgun = ("Auto Shotgun");
		static auto assaultrifle = ("Assault Rifle");
		static auto assaultrifle_mk2 = ("Assault Rifle MK2");
		static auto carbinerifle = ("Carbine Rifle");
		static auto carbinerifle_mk2 = ("Carbine Rifle MK2");
		static auto advancedrifle = ("Advanced Rifle");
		static auto specialcarbine = ("Special Carbine");
		static auto specialcarbine_mk2 = ("Special Carbine MK2");
		static auto bullpuprifle = ("Bullpup Rifle");
		static auto bullpuprifle_mk2 = ("Bullpup Rifle MK2");
		static auto compactrifle = ("Compact Rifle");
		static auto machine_gun = ("Machine Gun");
		static auto combatmg = ("Combat MG");
		static auto combatmg_mk2 = ("Combat MG MK2");
		static auto gusenberg = ("GUSENBERG");
		static auto sniperrifle = ("Sniper Rifle");
		static auto heavysniper = ("Heavy Sniper");
		static auto heavysniper_mk2 = ("Heavy Sniper MK2"); //
		static auto marksmanrifle = ("Marksman Rifle");
		static auto marksmanrifle_mk2 = ("Marksman Rifle MK2");
		static auto rpg = ("RPG");
		static auto grenadelauncher = ("Grenade Launcher");
		static auto grenadelauncher_smoke = ("Grenade Launcher Smoke");
		static auto minigun = ("MiniGun");
		static auto firework = ("FireWork");
		static auto railgun = ("RailGun");
		static auto hominglauncher = ("Homing Launcher");
		static auto compactlauncher = ("Compact Launcher");
		static auto grenade = ("Grenade");
		static auto bzgas = ("BZGAS");
		static auto smokegrenade = ("Smoke Grenade");
		static auto flare = ("Flare");
		static auto molotov = ("Molotov");
		static auto stickybomb = ("Sticky BOMB");
		static auto proxmine = ("Prox Mine");
		static auto snowball = ("SnowBall");
		static auto pipebomb = ("Pipe Bomb");
		static auto ball = ("Ball");
		static auto petrolcan = ("Petrol Can");
		static auto fireextinguisher = ("Fire Extinguisher");
		static auto parachute = ("Parachute");

		switch (hash)
		{
		case 0x92A27487:
			return dagger; break;
		case 0x958A4A8F:
			return bat; break;
		case 0xF9E6AA4B:
			return bottle; break;
		case 0x84BD7BFD:
			return crowbar; break;
		case 0xA2719263:
			return unarmed; break;
		case 0x8BB05FD7:
			return flashlight; break;
		case 0x440E4788:
			return golfclub; break;
		case 0x4E875F73:
			return hammer; break;
		case 0xF9DCBF2D:
			return hatchet; break;
		case 0xD8DF3C3C:
			return knuckle; break;
		case 0x99B507EA:
			return knife; break;
		case 0xDD5DF8D9:
			return machete; break;
		case 0xDFE37640:
			return switchblade; break;
		case 0x678B81B1:
			return nightstick; break;
		case 0x19044EE0:
			return wrench; break;
		case 0xCD274149:
			return battleaxe; break;
		case 0x94117305:
			return poolcue; break;
		case 0x1B06D571:
			return pistol; break;
		case 0xBFE256D4:
			return pistolmk2; break;
		case 0x5EF9FEC4:
			return combatpistol; break;
		case 0x22D8FE39:
			return appistol; break;
		case 0x3656C8C1:
			return stungun; break;
		case 0x99AEEB3B:
			return pistol50; break;
		case 0xBFD21232:
			return snspistol; break;
		case 0x88374054:
			return snspistolmk2; break;
		case 0xD205520E:
			return heavypistol; break;
		case 0x83839C4:
			return vintagepistol; break;
		case 0x47757124:
			return flaregun; break;
		case 0xDC4DB296:
			return marksmanpistol; break;
		case 0xC1B3C3D1:
			return revolver; break;
		case 0xCB96392F:
			return revolvermk2; break;
		case 0x97EA20B8:
			return doubleaction; break;
		case 0x13532244:
			return microsmg; break;
		case 0x2BE6766B:
			return smg; break;
		case 0x78A97CD0:
			return smgmk2; break;
		case 0xEFE7E2DF:
			return assaultsmg; break;
		case 0xA3D4D34:
			return combatpdw; break;
		case 0xDB1AA450:
			return machinepistol; break;
		case 0xBD248B55:
			return minismg; break;
		case 0x1D073A89:
			return pumpshotgun; break;
		case 0x555AF99A:
			return pumpshotgun_mk2; break;
		case 0x7846A318:
			return sawnoffshotgun; break;
		case 0xE284C527:
			return assaultshotgun; break;
		case 0x9D61E50F:
			return bullpupshotgun; break;
		case 0xA89CB99E:
			return musket; break;
		case 0x3AABBBAA:
			return heavyshotgun; break;
		case 0xEF951FBB:
			return dbshotgun; break;
		case 0x12E82D3D:
			return autoshotgun; break;
		case 0xBFEFFF6D:
			return assaultrifle; break;
		case 0x394F415C:
			return assaultrifle_mk2; break;
		case 0x83BF0278:
			return carbinerifle; break;
		case 0xFAD1F1C9:
			return carbinerifle_mk2; break;
		case 0xAF113F99:
			return advancedrifle; break;
		case 0xC0A3098D:
			return specialcarbine; break;
		case 0x969C3D67:
			return specialcarbine_mk2; break;
		case 0x7F229F94:
			return bullpuprifle; break;
		case 0x84D6FAFD:
			return bullpuprifle_mk2; break;
		case 0x624FE830:
			return compactrifle; break;
		case 0x9D07F764:
			return machine_gun; break;
		case 0x7FD62962:
			return combatmg; break;
		case 0xDBBD7280:
			return combatmg_mk2; break;
		case 0x61012683:
			return gusenberg; break;
		case 0x5FC3C11:
			return sniperrifle; break;
		case 0xC472FE2:
			return heavysniper; break;
		case 0xA914799:
			return heavysniper_mk2; break;
		case 0xC734385A:
			return marksmanrifle; break;
		case 0x6A6C02E0:
			return marksmanrifle_mk2; break;
		case 0xB1CA77B1:
			return rpg; break;
		case 0xA284510B:
			return grenadelauncher; break;
		case 0x4DD2DC56:
			return grenadelauncher_smoke; break;
		case 0x42BF8A85:
			return minigun; break;
		case 0x7F7497E5:
			return firework; break;
		case 0x6D544C99:
			return railgun; break;
		case 0x63AB0442:
			return hominglauncher; break;
		case 0x781FE4A:
			return compactlauncher; break;
		case 0x93E220BD:
			return grenade; break;
		case 0xA0973D5E:
			return bzgas; break;
		case 0xFDBC8A50:
			return smokegrenade; break;
		case 0x497FACC3:
			return flare; break;
		case 0x24B17070:
			return molotov; break;
		case 0x2C3731D9:
			return stickybomb; break;
		case 0xAB564B93:
			return proxmine; break;
		case 0x787F0BB:
			return snowball; break;
		case 0xBA45E8B8:
			return pipebomb; break;
		case 0x23C9F95C:
			return ball; break;
		case 0x34A67B97:
			return petrolcan; break;
		case 0x60EC506:
			return fireextinguisher; break;
		case 0xFBAB5776:
			return parachute; break;
		default:
			return unarmed; break;
		}
	}

	bool isInScreen(const ImVec2& from, const ImVec2& to) {
		float ScreenCX = ImGui::GetIO().DisplaySize.x;
		float ScreenCY = ImGui::GetIO().DisplaySize.y;
		if ((from.x >= 0) && (from.x <= (ScreenCX)) & (from.y >= 0) & (from.y <= (ScreenCY)))
		{
			if ((to.x >= 0) & (to.x <= (ScreenCX)) & (to.y >= 0) & (to.y <= (ScreenCY)))
			{
				return true;
			}
		}
		return false;
	}

	void DrawBoneLine(ImVec2 start, ImVec2 stop)
	{
		auto draw_list = ImGui::GetBackgroundDrawList();
		if (isInScreen(start, stop))
			draw_list->AddLine(start, stop, ImColor(amphetamine::amphetamine_settings->Skeleton_Color), 1.7f);
	}

	void __fastcall DrawOutlinedText(ImFont* font, std::string strText, ImVec2 pos, float fontSize, ImColor color, bool center, bool outline = true)
	{
		ImGuiContext& g = *GImGui;
		if (fontSize == 0.f)
			fontSize = g.Font->FontSize;
		std::string line;
		std::stringstream stream(strText);
		ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, line.c_str());
		while (std::getline(stream, line))
		{
			if (outline) {
				ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(pos.x + 1.3, pos.y), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
				ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(pos.x, pos.y + 1.3), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
				ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(pos.x + 1.3, pos.y), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
				ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(pos.x, pos.y + 1.3), ImColor(0, 0, 0, 255), line.c_str(), NULL, 0.0f, NULL);
			}
			ImGui::GetBackgroundDrawList()->AddText(font, fontSize, pos, color, line.c_str(), NULL, 0.0f, NULL);
		}
	}

	void draw_bones(DWORD64 cPed) {
		const auto rToe = Memory::GetBonePosW2S(cPed, 0x512D);
		const auto rFoot = Memory::GetBonePosW2S(cPed, 0xCC4D);
		const auto rCalf = Memory::GetBonePosW2S(cPed, 0x9000);
		const auto rThigh = Memory::GetBonePosW2S(cPed, 0xCA72);

		const auto lToe = Memory::GetBonePosW2S(cPed, 0x083C);
		const auto lFoot = Memory::GetBonePosW2S(cPed, 0x3779);
		const auto lCalf = Memory::GetBonePosW2S(cPed, 0xF9BB);
		const auto lThigh = Memory::GetBonePosW2S(cPed, 0xE39F);

		const auto pelvis = Memory::GetBonePosW2S(cPed, 0x2E28);
		const auto spineRoot = Memory::GetBonePosW2S(cPed, 0xE0FD);
		const auto spine0 = Memory::GetBonePosW2S(cPed, 0x5C01);
		const auto spine1 = Memory::GetBonePosW2S(cPed, 0x60F0);
		const auto spine2 = Memory::GetBonePosW2S(cPed, 0x60F1);
		const auto spine3 = Memory::GetBonePosW2S(cPed, 0x60F2);

		const auto lClavicle = Memory::GetBonePosW2S(cPed, 0xFCD9);
		const auto lUpperArm = Memory::GetBonePosW2S(cPed, 0xB1C5);
		const auto lForearm = Memory::GetBonePosW2S(cPed, 0xEEEB);
		const auto lHand = Memory::GetBonePosW2S(cPed, 0x49D9);

		const auto rClavicle = Memory::GetBonePosW2S(cPed, 0x29D2);
		const auto rUpperArm = Memory::GetBonePosW2S(cPed, 0x9D4D);
		const auto rForearm = Memory::GetBonePosW2S(cPed, 0x6E5C);
		const auto rHand = Memory::GetBonePosW2S(cPed, 0xDEAD);

		const auto neck = Memory::GetBonePosW2S(cPed, 0x9995);
		const auto head = Memory::GetBonePosW2S(cPed, 0x796E);

		DrawBoneLine(rToe, rFoot);
		DrawBoneLine(rFoot, rCalf);
		DrawBoneLine(rCalf, rThigh);
		DrawBoneLine(rThigh, pelvis);

		DrawBoneLine(lToe, lFoot);
		DrawBoneLine(lFoot, lCalf);
		DrawBoneLine(lCalf, lThigh);
		DrawBoneLine(lThigh, pelvis);

		DrawBoneLine(pelvis, spineRoot);
		DrawBoneLine(spineRoot, spine0);
		DrawBoneLine(spine0, spine1);
		DrawBoneLine(spine1, spine2);
		DrawBoneLine(spine2, spine3);
		DrawBoneLine(spine3, neck);
		DrawBoneLine(neck, head);

		DrawBoneLine(lClavicle, lUpperArm);
		DrawBoneLine(lUpperArm, lForearm);
		DrawBoneLine(lForearm, lHand);

		DrawBoneLine(rClavicle, rUpperArm);
		DrawBoneLine(rUpperArm, rForearm);
		DrawBoneLine(rForearm, rHand);

		DrawBoneLine(rClavicle, neck);
		DrawBoneLine(lClavicle, neck);
	}



	void object_in_list()
	{


		map<int32_t, string> object_list ;

		


		std::string folder;
		auto get_dir = [&folder]() -> void
		{
			static TCHAR path[MAX_PATH];

			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
				folder = std::string(path) + xorstr_("\\AMTH.CSGO\\HASH\\");

			CreateDirectory(folder.c_str(), NULL);
		};

		get_dir();
		filesobjectlist.clear();

		std::string path = folder + xorstr_("/*.txt"); //wan4re
		WIN32_FIND_DATA fd;

		HANDLE hFind = FindFirstFile(path.c_str(), &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{

					filesobjectlist.push_back(fd.cFileName);

					std::istringstream iss(fd.cFileName);
					std::string item;
					vector<string> lol_test; //  0 - это hash    1 это нейм
					while (iss >> item) {
						//files.push_back(item);
						lol_test.push_back(item);
					}
					int32_t toAddInt;
					sscanf(lol_test[0].c_str(), "%d", &toAddInt);
					object_list.insert(make_pair(toAddInt, lol_test[1]));
					Visuals::m_save_hash = object_list;
					//CRT::String_t<MAX_PATH> szFieldClassBuffer(xorstr_("%s->%s"), _ClassName, _FieldName);
				}
			} 
			while (FindNextFile(hFind, &fd));

			FindClose(hFind);
		}
	}
	void Save_object_file(std::string Namecfg)
	{
		std::string folder, file;
		auto get_dir = [&folder, &file, &Namecfg]() -> void
		{
			static TCHAR path[MAX_PATH];

			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
			{
				folder = std::string(path) + ("\\AMTH.CSGO\\HASH\\");
				file = std::string(path) + ("\\AMTH.CSGO\\HASH\\") + Namecfg;
			}

			CreateDirectory(folder.c_str(), NULL);
		};
		get_dir();
		cfg.SaveFile(file.c_str());
	}
	void add_object()
	{
		auto empty = true;
		for (auto current : new_object_name)
		{
			if (current != ' ')
			{
				empty = false;
				break;
			}
		}
		if (empty)
		{
			std::string remnot = "Write a hash";
			//ImGui::InsertNotification({ ImGuiToastType_Error, 4000, remnot.c_str(), "amphetamine.su" });
		}
		else {
			if (new_object_name.find((".txt")) == std::string::npos)
				new_object_name += (".txt");
			Save_object_file(new_object_name);
			std::string remnot = "Added hash: " + new_object_name;
			object_in_list();
			selected_objectlist = filesobjectlist.size() - 1;
			//files = filesobjectlist;
			for (auto& current : filesobjectlist)
				if (current.size() > 2)
					current.erase(current.size() - 3, 3);
		}
	}


	void remove_objecttt(std::string config)
	{
		std::string folder, file;
		auto get_dir = [&folder, &file, &config]() -> void
		{
			static TCHAR path[MAX_PATH];

			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
			{
				folder = std::string(path) + xorstr_("\\AMTH.CSGO\\HASH\\");
				file = std::string(path) + xorstr_("\\AMTH.CSGO\\HASH\\") + config + "txt";
			}

			CreateDirectory(folder.c_str(), NULL);
		};
		get_dir();
		std::string path = file + '\0';
		std::remove(path.c_str());
		std::string remnot = "Removed Object: " + config;
		//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, remnot.c_str(), "amphetamine.su" });
	}
	void remove_object()
	{
		if (filesobjectlist.empty())
			return;
		remove_objecttt(filesobjectlist.at(selected_objectlist));
		object_in_list();
		//files = cfg_manager->files;
		if (selected_objectlist >= filesobjectlist.size())
			selected_objectlist = filesobjectlist.size() - 1;
		for (auto& current : filesobjectlist)
			if (current.size() > 2)
				current.erase(current.size() - 3, 3);
	}

	void draw_object_esp() {
		if (amphetamine::amphetamine_settings->object_esp)
		{
			uintptr_t ReplayInterfacePatternFixed = *(uintptr_t*)(Memory::ReplayInterface);
			uintptr_t ObjectReplayInterface = *(uintptr_t*)(ReplayInterfacePatternFixed + 0x28);
			int maxpickups = *(int*)(ObjectReplayInterface + 0x160);
			uintptr_t ObjectList = *(uintptr_t*)(ObjectReplayInterface + 0x0158);
			for (int i = 0; i < maxpickups; i++) {
				uintptr_t Object = *(uintptr_t*)(ObjectList + (i * 0x10));
				if (!Object) continue;
				uintptr_t ObjectInfo = *(uintptr_t*)(Object + 0x20);
				int32_t WeaponHash = *(int32_t*)(ObjectInfo + 0x18);
				Vector3 vPosition = *(Vector3*)(Object + 0x90);
				ImVec2 vScreenPosition = Memory::WorldToScreen(vPosition);
				if (!IsOnScreen(vScreenPosition)) continue;

				Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
				if (Aimbot::get_distance(localpos, vPosition) > amphetamine::amphetamine_settings->DistanceObject)
					continue;			
				if (amphetamine::amphetamine_settings->object_esp_all) {
					std::string text = std::to_string(WeaponHash);
					std::string str = "";
					std::string text_distance = std::to_string((int)round(Aimbot::get_distance(localpos, vPosition)));
					str.append(text);
					if (amphetamine::amphetamine_settings->object_dist_esp)
					{
						std::string strr = "  [" + text_distance + "m]";
						str.append(strr);
					}
					DrawOutlinedText(font::poppins_medium_low, str, ImVec2(vScreenPosition.x, vScreenPosition.y), 14.f, ImColor(amphetamine::amphetamine_settings->object_color), true);
				}
				else {


					map<int32_t, string> object_list = Visuals::m_save_hash;

				
					map<int32_t, string>::iterator it = object_list.find(WeaponHash);
					if (it != object_list.end()) {

						char tHash[32];
						sprintf(tHash, "%d\n", WeaponHash);
						string name(tHash);

						if (it != object_list.end()) {
							name = it->second;
						}
						std::string text_distance = std::to_string((int)round(Aimbot::get_distance(localpos, vPosition)));
						if (amphetamine::amphetamine_settings->object_dist_esp)
						{
							std::string strr = "  [" + text_distance + "m]";
							name.append(strr);
						}

						DrawOutlinedText(font::poppins_medium_low, name, ImVec2(vScreenPosition.x, vScreenPosition.y), 16.f, ImColor(amphetamine::amphetamine_settings->object_color), true);

					}



					/*std::string namee = "";	
					std::vector<int32_t> new_variable;
					for (string str : filesobjectlist)
						new_variable.push_back(static_cast<int32_t>(std::stoul(str)));	
					std::string text_distance = std::to_string((int)round(Aimbot::get_distance(localpos, vPosition)));
					for (auto hash : new_variable) {
						if (WeaponHash == hash)
						{
							namee = std::to_string(hash);
							if (amphetamine::amphetamine_settings->object_dist_esp)
							{
								std::string strr = "  [" + text_distance + "m]";
								namee.append(strr);
							}
						}
					}
					DrawOutlinedText(font::poppins_medium_low, namee, ImVec2(vScreenPosition.x, vScreenPosition.y), 14.f, ImColor(amphetamine::amphetamine_settings->object_color), true);*/
				}
			}
		}
	}
	void __fastcall DrawFilledRect(float x, float y, float w, float h, ImVec4 color)
	{
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), NULL, NULL);
	}
	enum ped_types
	{
		PLAYER_0, // michael
		PLAYER_1, // franklin
		NETWORK_PLAYER, // mp character
		PLAYER_2, // trevor
		CIVMALE,
		CIVFEMALE,
		COP,
		GANG_ALBANIAN,
		GANG_BIKER_1,
		GANG_BIKER_2,
		GANG_ITALIAN,
		GANG_RUSSIAN,
		GANG_RUSSIAN_2,
		GANG_IRISH,
		GANG_JAMAICAN,
		GANG_AFRICAN_AMERICAN,
		GANG_KOREAN,
		GANG_CHINESE_JAPANESE,
		GANG_PUERTO_RICAN,
		DEALER,
		MEDIC,
		FIREMAN,
		CRIMINAL,
		BUM,
		PROSTITUTE,
		SPECIAL,
		MISSION,
		SWAT,
		ANIMAL,
		ARMY
	};
	void waypoint_esp() {
		//if (vars::player::teleport_to_waypoint || vars::esp::draw_waypoint) {

		//	//int WaypointHandle = ui::get_first_blip_info_id(8); //GET_FIRST_BLIP_INFO_ID
		//	//if (ui::does_blip_exist(WaypointHandle))
		//	//{
		//	//	auto playerpiiid = player::player_ped_id();
		//	//	rage::padvec3 waypoint1 = ui::get_blip_coords(WaypointHandle);
		//	//	ped::set_ped_coords_keep_vehicle(playerpiiid, waypoint1.x, waypoint1.y, waypoint1.z); //SET_PED_COORDS_KEEP_VEHICLE
		//	//}

		//	auto blip_list = (uint64_t)(g::base_address.modBaseAddr + 0x206B4E0);
		//	auto teleport_height = -200.f;
		//	for (int i = 0; i < 2000; i++) {
		//		auto blip = c_mem::get()->read_mem<uintptr_t>(blip_list + (i * 8));
		//		if (!blip)
		//			continue;

		//		auto blip_color = c_mem::get()->read_mem<int>(blip + 0x48);
		//		auto blip_icon = c_mem::get()->read_mem<int>(blip + 0x40);
		//		if ((blip_color != /*BlipColor::ColorWaypoint*/84) || (blip_icon != /*BlipSprite::SpriteWaypoint*/8))
		//			continue;

		//		auto waypoint_pos = c_mem::get()->read_mem<D3DXVECTOR3>(blip + 0x10);
		//		if (waypoint_pos != D3DXVECTOR2(0.f, 0.f)) {
		//			auto waypoint_up = world_to_screen(D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, waypoint_pos.z + 220.f));
		//			auto screen_waypoint_pos = world_to_screen(D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, waypoint_pos.z));
		//			if (waypoint_up != D3DXVECTOR2(0, 0) && screen_waypoint_pos != D3DXVECTOR2(0, 0)) {
		//				rendering::c_renderer::get()->draw_line(screen_waypoint_pos.x, screen_waypoint_pos.y, waypoint_up.x, waypoint_up.y, D3DCOLOR_RGBA(255, 0, 0, 255));
		//				rendering::c_renderer::get()->draw_string(waypoint_up.x, waypoint_up.y - 14.f, d3d9::tahoma_13, D3DCOLOR_RGBA(255, 0, 0, 255), DT_CENTER, false, (L"WAYPOINT - " + std::to_wstring(int(D3DXVec3Length(&(local_origin - waypoint_pos)))) + L"m").c_str());
		//			}

		//			if (vars::player::teleport_to_waypoint) {
		//				for (int i = 0; i < 5; i++) {
		//					if (waypoint_pos != D3DXVECTOR2(0.f, 0.f)) {
		//						auto vehicle_navigation = c_mem::get()->read_mem<uintptr_t>(local_ped.get_vehicle() + 0x0030);
		//						c_mem::get()->write_mem<D3DXVECTOR3>(vehicle_navigation + 0x50, D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, teleport_height));
		//						c_mem::get()->write_mem<D3DXVECTOR3>(local_ped.get_navigation() + 0x50, D3DXVECTOR3(waypoint_pos.x, waypoint_pos.y, teleport_height));
		//					}
		//				}
		//				vars::player::teleport_to_waypoint = false;
		//			}
		//		}

		//	}
		//}



	}
	void localplayer_esp(bool IsVisible = false) {
		if (amphetamine::amphetamine_settings->enable_localplayeresp_LocalPlayer_esp) {
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
			ImColor rgbcolor = ImColor(r, g, b);

			hk_Ped* Peds = (hk_Ped*)Memory::LocalPlayer;
			if (!Peds)
				return;
			ImVec2 Ped_Location = Memory::WorldToScreen(Peds->GetCoordinate());
			if (!IsOnScreen(Ped_Location)) return;
			Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
			auto Distance = Aimbot::get_distance(localpos, localpos);

			ImVec2 Head = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x796E);
			if (!IsOnScreen(Head)) return;

			ImVec2 Left_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x3779);
			if (!IsOnScreen(Left_Foot)) return;

			ImVec2 Right_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xCC4D);
			if (!IsOnScreen(Right_Foot)) return;

			float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
			float Height = abs(Head.y - Foot_Middle) * 1.35f;
			float Width = (Height / 1.80f);
			float HealthDistance = Width / 16;
			ImVec2 CordsToDraw = ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2);
			if (amphetamine::amphetamine_settings->combo_box_LocalPlayer_esp == 1) {
				ImColor caca = { amphetamine::amphetamine_settings->Box_Color_LocalPlayer_esp };
				if (amphetamine::amphetamine_settings->rainbowbox_LocalPlayer_esp) {
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImColor(0, 0, 0, 255), 0, 0, 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), rgbcolor, 0, 0, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				}
				else {
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImColor(0, 0, 0, 255), 0, 0, 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), caca, 0, 0, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				}
			}
			if (amphetamine::amphetamine_settings->combo_box_LocalPlayer_esp == 2) {




				float CornerSize = (Width) / 4.f;
				ImColor caca;
				if (amphetamine::amphetamine_settings->rainbowbox_LocalPlayer_esp) {
					caca = rgbcolor;
				}
				else {
					caca = { amphetamine::amphetamine_settings->Box_Color_LocalPlayer_esp };
				}


				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), ImColor(0, 0, 0, 255), 1.8 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), caca, 1 * amphetamine::amphetamine_settings->BoxSize_LocalPlayer_esp);
			}
			if (amphetamine::amphetamine_settings->combo_box_LocalPlayer_esp == 1 || amphetamine::amphetamine_settings->combo_box_LocalPlayer_esp == 2)
			{
				if (amphetamine::amphetamine_settings->Filled_box_LocalPlayer_esp)
				{
					ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImColor(0, 0, 0, amphetamine::amphetamine_settings->FillBoxAlpha));
				}
			}



			if (amphetamine::amphetamine_settings->skeleton_LocalPlayer_esp)
			{
				if (amphetamine::amphetamine_settings->combo_skeleton_LocalPlayer_esp == 1)
				{


					ImVec2 Pelvis = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x2e28);
					if (!IsOnScreen(Pelvis)) return;

					ImVec2 Neck = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x9995);
					if (!IsOnScreen(Neck)) return;

					ImVec2 Clavicle_Left = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xFCD9);
					if (!IsOnScreen(Clavicle_Left)) return;

					ImVec2 Clavicle_Right = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x29D2);
					if (!IsOnScreen(Clavicle_Right)) return;

					ImVec2 Uperarm_left = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xB1C5);
					if (!IsOnScreen(Uperarm_left)) return;

					ImVec2 Uperarm_right = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x9D4D);
					if (!IsOnScreen(Uperarm_right)) return;

					ImVec2 Elbow_l = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x58B7);
					if (!IsOnScreen(Elbow_l)) return;

					ImVec2 Elbow_r = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xBB0);
					if (!IsOnScreen(Elbow_r)) return;

					ImVec2 R_FormArm = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x6E5C);
					if (!IsOnScreen(R_FormArm)) return;

					ImVec2 L_FormArm = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xEEEB);
					if (!IsOnScreen(L_FormArm)) return;

					ImVec2 SKEL_R_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xDEAD);
					if (!IsOnScreen(SKEL_R_Hand)) return;

					ImVec2 SKEL_L_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x49D9);
					if (!IsOnScreen(SKEL_L_Hand)) return;


					ImVec2 SKEL_L_Thigh = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xE39F);
					if (!IsOnScreen(SKEL_L_Thigh)) return;

					ImVec2 SKEL_L_Calf = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xF9BB);
					if (!IsOnScreen(SKEL_L_Calf)) return;

					ImVec2 SKEL_R_Thigh = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xCA72);
					if (!IsOnScreen(SKEL_R_Thigh)) return;

					ImVec2 SKEL_R_Calf = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x9000);
					if (!IsOnScreen(SKEL_R_Calf)) return;

					ImVec2 SKEL_L_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x3779);
					if (!IsOnScreen(SKEL_L_Foot)) return;

					ImVec2 SKEL_R_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xCC4D);
					if (!IsOnScreen(SKEL_R_Foot)) return;

					ImColor caca = { 0, 0, 0 ,255 };
					if (IsVisible)
					{
						caca = amphetamine::amphetamine_settings->SkelColor_LocalPlayer_esp;
					}
					else
					{
						caca = amphetamine::amphetamine_settings->invisibleSkelColor_LocalPlayer_esp;
					}
					ImGui::GetBackgroundDrawList()->AddLine(Neck, Clavicle_Right, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Neck, Clavicle_Left, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Clavicle_Right, Uperarm_right, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Clavicle_Left, Uperarm_left, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Uperarm_right, Elbow_r, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Uperarm_left, Elbow_l, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Elbow_r, R_FormArm, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Elbow_l, L_FormArm, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(R_FormArm, SKEL_R_Hand, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(L_FormArm, SKEL_L_Hand, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Neck, Pelvis, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, SKEL_L_Thigh, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, SKEL_R_Thigh, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(SKEL_L_Thigh, SKEL_L_Calf, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(SKEL_R_Thigh, SKEL_R_Calf, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(SKEL_L_Calf, SKEL_L_Foot, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(SKEL_R_Calf, SKEL_R_Foot, caca, 1.f);


				}
				else {

					ImColor caca = { 0, 0, 0 ,255 };
					if (IsVisible)
					{
						caca = amphetamine::amphetamine_settings->SkelColor_LocalPlayer_esp;
					}
					else
					{
						caca = amphetamine::amphetamine_settings->invisibleSkelColor_LocalPlayer_esp;
					}

					ImVec2 Pelvis = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x2e28);
					if (!IsOnScreen(Pelvis)) return;

					ImVec2 Neck = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x9995);
					if (!IsOnScreen(Neck)) return;
					ImVec2 Left_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x49D9);
					if (!IsOnScreen(Left_Hand)) return;

					ImVec2 Right_Hand = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xDEAD);
					if (!IsOnScreen(Right_Hand)) return;


					//ImGui::GetBackgroundDrawList()->AddLine(Head,Neck,ImColor(255, 255, 255, 255), 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Neck, Left_Hand, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Neck, Right_Hand, caca, 1.f);

					ImGui::GetBackgroundDrawList()->AddLine(Neck, Pelvis, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, Left_Foot, caca, 1.f);
					ImGui::GetBackgroundDrawList()->AddLine(Pelvis, Right_Foot, caca, 1.f);

				}
			}
			bool IsOnGlife = false;
			if (Peds->GetMaxHealth() > 201)
				IsOnGlife = true;

			if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp != 4) {

				float HealthPercentage = Height / 100 * (Peds->GetHealth() - 100);
				float HealthPercentagee = Height / 100 * 100;
				if (IsOnGlife)
					HealthPercentage = Height / 100 * ((Peds->GetHealth() - 100) / 2);

				float fixedhealth = Peds->GetHealth() / 2;
				if (IsOnGlife)
					(Peds->GetHealth() - 100) / 2;
				float fixedhealthh = 100;

				ImColor	col = ImColor(52, 176, 48, 255);
				ImColor coll = ImColor(0, 0, 0, 255);

				float  caca = (Width) / 8.f;
				if (Distance < 20)
				{
					caca = (Width) / 10.f;
				}
				float HealthPercentageeee = Width / 100 * (Peds->GetHealth() - 100);


				if (fixedhealth > 0 && fixedhealth < 101)
				{
					if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 0)
					{
						if (fixedhealth != 0)
							DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
						DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 1)
					{
						if (fixedhealth != 0)
							DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
						DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 2)
					{

						if (fixedhealth != 0)
							DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 22), ImVec2(5.4, Width), coll);
						DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 22), ImVec2(5, HealthPercentageeee), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 3)
					{
						if (fixedhealth != 0)
							DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 22), ImVec2(5.4, Width), coll);
						DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 22), ImVec2(5, Width / 100 * (Peds->GetHealth() - 100.f)), col);

					}
				}
			}
			if (amphetamine::amphetamine_settings->ArmorBar_LocalPlayer_esp)
			{

				float HealthPercentage = Height / 100 * (Peds->GetArmor());
				float HealthPercentagee = Height / 100 * 100;

				float fixedArmor = Peds->GetArmor();

				float fixedhealthh = 100;

				ImColor col = ImColor(10, 145, 255, 255);
				ImColor coll = ImColor(0, 0, 0, 255);

				float  caca = (Width) / 8.f;
				if (Distance < 20)
				{
					caca = (Width) / 10.f;
				}
				float HealthPercentageeee = Width / 100 * (Peds->GetArmor());

				if (fixedArmor > 0 && fixedArmor < 101)
				{
					//DrawHealthBar(ImVec2((Ped_Location.x +  Width / 2) + HealthDistance , Ped_Location.y + Height / 2), ImVec2(1.8, HealthPercentagee), coll);
					if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 0)
					{
						if (fixedArmor != 0)
							DrawHealthBar(ImVec2((Ped_Location.x + 9 + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
						DrawHealthBar(ImVec2((Ped_Location.x + 9 + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 1)
					{
						if (fixedArmor != 0)
							DrawHealthBar(ImVec2((Ped_Location.x - 9 - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
						DrawHealthBar(ImVec2((Ped_Location.x - 9 - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 2)
					{

						if (fixedArmor != 0)
							DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 32), ImVec2(5.4, Width), coll);
						DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 32), ImVec2(5, HealthPercentageeee), col);

					}
					else if (amphetamine::amphetamine_settings->HealthBar_idx_LocalPlayer_esp == 3)
					{
						if (fixedArmor != 0)
							DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 32), ImVec2(5.4, Width), coll);
						DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 32), ImVec2(5, HealthPercentageeee), col);

					}
				}



			}

			std::string str = "";

			if (amphetamine::amphetamine_settings->weapon_LocalPlayer_esp)
			{
				hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
				if (!PedsWeaponManager) return;
				hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
				if (!PedsWeaponInfo) return;
				uint64_t Hash = PedsWeaponInfo->GetHash();
				str.append(get_weapon_name(Hash));

				//DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 5), 15.0f, ImColor(255, 255, 255), true);

			}

			if (amphetamine::amphetamine_settings->distance_LocalPlayer_esp) {
				std::string strr = " [" + std::to_string((int)round(Distance)) + "m]";
				if (!amphetamine::amphetamine_settings->weapon_LocalPlayer_esp)
					strr = "[" + std::to_string((int)round(Distance)) + "m]";
				str.append(strr);
			}
			if (amphetamine::amphetamine_settings->distance_LocalPlayer_esp || amphetamine::amphetamine_settings->weapon_LocalPlayer_esp)
			{
				ImColor caca = { 0, 0, 0 ,255 };
				if (IsVisible)
				{
					caca = ImColor(amphetamine::amphetamine_settings->Dist_Color_LocalPlayer_esp);
				}
				else
				{
					caca = ImColor(amphetamine::amphetamine_settings->invisibleDist_Color_LocalPlayer_esp);
				}
				ImVec2 TextSize = ImGui::CalcTextSize((char*)str.c_str());
				DrawOutlinedText(font::poppins_medium_low, str, ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y + Height / 2 + 5), 15.f, caca, true);

			}
			if (amphetamine::amphetamine_settings->name_LocalPlayer_esp)
			{
				auto playerName = std::to_string((DWORD64)Peds);
				ImColor caca = { 0, 0, 0 ,255 };
				if (IsVisible)
				{
					caca = ImColor(amphetamine::amphetamine_settings->Name_Color_LocalPlayer_esp);
				}
				else
				{
					caca = ImColor(amphetamine::amphetamine_settings->Name_Color_invisible_LocalPlayer_esp);
				}
				ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName.c_str());
				DrawOutlinedText(font::poppins_medium_low, playerName, ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y - Height / 2 - 5 - 12), 15.f, caca, true);
			}
		}
	}
	void draw_rect_bar(float x, float y, float w, float h, float health, float max, bool armor, bool horizontal = false) {
		if (!max)
			return;

		if (health < 0)
			health = 0;

		float ratio = health / max;
		ImColor col = ImColor(0, 0, 0, 0);
		if (armor == true) {
			col = ImColor(46, 175, 230, 255);//Color
		}
		else {
			col = ImColor(46, 230, 46, 200);//Color
		}
		if (!horizontal) {

			float step = (w / max);
			float draw = (step * health);


			Render_D2::FillRectangle(ImVec2(x - 1, y - 1), ImVec2(x + w + 2, y + h + 2), D2D1::ColorF::Black);
			Render_D2::FillRectangle(ImVec2(x, y), ImVec2(x + draw, y + h), FLOAT4TOD3rwerLOR(col));

			//renderer.RenderRectFilled(ImVec2(x - 1, y - 1), ImVec2(x + w + 2, y + h + 2), RGBA(0, 0, 0, 150), 0.0f, 0);
			//renderer.RenderRectFilled(ImVec2(x, y), ImVec2(x + draw, y + h), col, 0.0f, 0);
		}
		else {

			float step = (h / max);
			float draw = (step * health);

			Render_D2::FillRectangle(ImVec2(x - 1, y - 1), ImVec2(x + w + 2, y + h + 2), D2D1::ColorF::Black);
			Render_D2::FillRectangle(ImVec2(x, y), ImVec2(x + w, y + draw), FLOAT4TOD3rwerLOR(col));

			//renderer.RenderRectFilled(ImVec2(x - 1, y - 1), ImVec2(x + w + 2, y + h + 2), RGBA(0, 0, 0, 150), 0.0f, 0);
			//renderer.RenderRectFilled(ImVec2(x, y), ImVec2(x + w, y + draw), col, 0.0f, 0);
		}
	}


	void Visuals(int i, Vector3 pedCoordinate, ImVec2 LocalPlayer_Location, ImVec2 Ped_Location, ImColor rgbcolor, float Distance, bool IsVisible = false, bool is_ped_is_any_vehicle = false) {
		ImVec2 Head = Pool::new_list[i].Head;
		if (!IsOnScreen(Head)) return;
		ImVec2 Left_Foot = Pool::new_list[i].Left_Foot;
		if (!IsOnScreen(Left_Foot)) return;
		ImVec2 Right_Foot = Pool::new_list[i].Right_Foot;
		if (!IsOnScreen(Right_Foot)) return;
		auto Top = Vector3(Pool::new_list[i].position.x, Pool::new_list[i].position.y, Pool::new_list[i].position.z + 0.85f);
		auto Bottom = Vector3(Pool::new_list[i].position.x, Pool::new_list[i].position.y, Pool::new_list[i].position.z - 1.0f);
		ImVec2 top2d;
		ImVec2 bottom2d;
		top2d = Memory::WorldToScreen(Top);
		bottom2d = Memory::WorldToScreen(Bottom);

		float BoxHeight = abs(top2d.y - bottom2d.y);
		float BoxWidth = BoxHeight / 2.0f;
		float TextStartY = top2d.y + BoxHeight;
		int textRow = 0;


		if (amphetamine::amphetamine_settings->Snapline)
		{
			Render_D2::lineqwas(ImVec2(LocalPlayer_Location.x, (LocalPlayer_Location.y + 200)), Ped_Location, FLOAT4TOD3rwerLOR(ImColor(amphetamine::amphetamine_settings->SnapLines_Color)), true, 0.75f);
		}

		float thickness_box = 1.8 * amphetamine::amphetamine_settings->BoxSize;
		{
			ImColor current_color;
			if (amphetamine::amphetamine_settings->rainbowbox)
				current_color = rgbcolor;
			else
				current_color = { amphetamine::amphetamine_settings->Box_Color };
			if ((amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 1) || (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 2)) {

				if (amphetamine::amphetamine_settings->Filled)
				{
					Render_D2::FillRectangle(ImVec2(top2d.x - (BoxWidth / 2.0f), top2d.y), ImVec2(top2d.x - (BoxWidth / 2.0f) + BoxWidth, top2d.y + BoxHeight), FLOAT4TOD3rwerLOR(ImColor(0, 0, 0, amphetamine::amphetamine_settings->FillBoxAlpha)));
				}
			}
			if (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 1) {
				Render_D2::Rectangle(ImVec2(top2d.x - (BoxWidth / 2.0f), top2d.y), ImVec2(top2d.x - (BoxWidth / 2.0f) + BoxWidth, top2d.y + BoxHeight), FLOAT4TOD3rwerLOR(current_color), thickness_box);
			}
			if (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 2) {
				auto top_left = ImVec2(top2d.x - (BoxWidth / 2.0f), top2d.y);
				auto bottom_right = ImVec2(top2d.x - (BoxWidth / 2.0f) + BoxWidth, top2d.y + BoxHeight);
				//top left corner
				Render_D2::Line(ImVec2(top_left.x - thickness_box / 2, top_left.y), ImVec2(top_left.x + BoxWidth / 4.f, top_left.y), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				Render_D2::Line(ImVec2(top_left.x, top_left.y - thickness_box / 2), ImVec2(top_left.x, top_left.y + BoxHeight / 4.f), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				//bottom left corner
				Render_D2::Line(ImVec2(top_left.x, top_left.y + BoxHeight + thickness_box / 2), ImVec2(top_left.x, top_left.y + BoxHeight - BoxHeight / 4.f), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				Render_D2::Line(ImVec2(top_left.x - thickness_box / 2, top_left.y + BoxHeight), ImVec2(top_left.x + BoxWidth / 4.f, top_left.y + BoxHeight), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				//top right corner
				Render_D2::Line(ImVec2(bottom_right.x, bottom_right.y - BoxHeight - thickness_box / 2), ImVec2(bottom_right.x, bottom_right.y - BoxHeight + BoxHeight / 4.f), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				Render_D2::Line(ImVec2(bottom_right.x + thickness_box / 2, bottom_right.y - BoxHeight), ImVec2(bottom_right.x - BoxWidth / 4.f, bottom_right.y - BoxHeight), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				//bottom right corner
				Render_D2::Line(ImVec2(bottom_right.x, bottom_right.y + thickness_box / 2), ImVec2(bottom_right.x, bottom_right.y - BoxHeight / 4.f), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
				Render_D2::Line(ImVec2(bottom_right.x + thickness_box / 2, bottom_right.y), ImVec2(bottom_right.x - BoxWidth / 4.f, bottom_right.y), FLOAT4TOD3rwerLOR(current_color), thickness_box, true);
			}
		}
	
		

		if (amphetamine::amphetamine_settings->HealthBar_idx != 4) {
			int bar_mode = amphetamine::amphetamine_settings->HealthBar_idx;
			if ((bar_mode == 0)) {
				// top
				float w_health = 20.0;
				draw_rect_bar(top2d.x - (BoxWidth > w_health ? BoxWidth / 2 : (w_health / 2)), (top2d.y - thickness_box) - 8.0f, (BoxWidth > w_health ? BoxWidth : w_health), 3, Pool::new_list[i].health - 100.0f, 200 - 100.0f, false);
				if (Pool::new_list[i].armor > 1.0f) {
					draw_rect_bar(top2d.x - (BoxWidth > w_health ? BoxWidth / 2 : (w_health / 2)), (top2d.y - thickness_box) - 15.0f, (BoxWidth > w_health ? BoxWidth : w_health), 3, Pool::new_list[i].armor, 100.0f, true);
				}
			}
			if ((bar_mode == 1)) {
				// bottom

				textRow += 1;
				float w_health = 20.0;
				draw_rect_bar(top2d.x - (BoxWidth > w_health ? BoxWidth / 2 : (w_health / 2)), (top2d.y + thickness_box + BoxHeight) + 8.0f, (BoxWidth > w_health ? BoxWidth : w_health), 3, Pool::new_list[i].health - 100.0f, 200 - 100.0f, false);
				if (Pool::new_list[i].armor > 1.0f) {
					textRow += 1;
					draw_rect_bar(top2d.x - (BoxWidth > w_health ? BoxWidth / 2 : (w_health / 2)), (top2d.y + thickness_box + BoxHeight) + 15.0f, (BoxWidth > w_health ? BoxWidth : w_health), 3, Pool::new_list[i].armor, 100.0f, true);
				}
			}
			if (bar_mode == 2) {
				// left
				float w_health = 20.0;
				draw_rect_bar(top2d.x - BoxWidth / 2 - 12.f, top2d.y, 4.f, BoxHeight, Pool::new_list[i].health - 100.0f, 200 - 100.0f, false, true);
				if (Pool::new_list[i].armor > 1.0f) {
					draw_rect_bar(top2d.x - BoxWidth / 2 - 24.f, top2d.y, 4.f, BoxHeight, Pool::new_list[i].armor, 100.0f, true, true);
				}
			}
			if (bar_mode == 3) {
				// right
				float w_health = 20.0;
				draw_rect_bar(top2d.x + BoxWidth / 2 + 8.f, top2d.y, 4.f, BoxHeight, Pool::new_list[i].health - 100.0f, 200 - 100.0f, false, true);
				if (Pool::new_list[i].armor > 1.0f) {
					draw_rect_bar(top2d.x + BoxWidth / 2 + 20.f, top2d.y, 4.f, BoxHeight, Pool::new_list[i].armor, 100.0f, true, true);
				}
			}
		}
		if (amphetamine::amphetamine_settings->Skeleton)
		{
			ImVec2 Pelvis = Pool::new_list[i].Pelvis;
			if (!IsOnScreen(Pelvis)) return;
			ImVec2 Neck = Pool::new_list[i].Neck;
			if (!IsOnScreen(Neck)) return;
			ImVec2 Clavicle_Left = Pool::new_list[i].Clavicle_Left;
			if (!IsOnScreen(Clavicle_Left)) return;
			ImVec2 Clavicle_Right = Pool::new_list[i].Clavicle_Right;
			if (!IsOnScreen(Clavicle_Right)) return;
			ImVec2 Uperarm_left = Pool::new_list[i].Uperarm_left;
			if (!IsOnScreen(Uperarm_left)) return;
			ImVec2 Uperarm_right = Pool::new_list[i].Uperarm_right;
			if (!IsOnScreen(Uperarm_right)) return;
			ImVec2 Elbow_l = Pool::new_list[i].Elbow_l;
			if (!IsOnScreen(Elbow_l)) return;
			ImVec2 Elbow_r = Pool::new_list[i].Elbow_r;
			if (!IsOnScreen(Elbow_r)) return;
			ImVec2 R_FormArm = Pool::new_list[i].R_FormArm;
			if (!IsOnScreen(R_FormArm)) return;
			ImVec2 L_FormArm = Pool::new_list[i].L_FormArm;
			if (!IsOnScreen(L_FormArm)) return;
			ImVec2 SKEL_R_Hand = Pool::new_list[i].SKEL_R_Hand;
			if (!IsOnScreen(SKEL_R_Hand)) return;
			ImVec2 SKEL_L_Hand = Pool::new_list[i].SKEL_L_Hand;
			if (!IsOnScreen(SKEL_L_Hand)) return;
			ImVec2 SKEL_L_Thigh = Pool::new_list[i].SKEL_L_Thigh;
			if (!IsOnScreen(SKEL_L_Thigh)) return;
			ImVec2 SKEL_L_Calf = Pool::new_list[i].SKEL_L_Calf;
			if (!IsOnScreen(SKEL_L_Calf)) return;
			ImVec2 SKEL_R_Thigh = Pool::new_list[i].SKEL_R_Thigh;
			if (!IsOnScreen(SKEL_R_Thigh)) return;
			ImVec2 SKEL_R_Calf = Pool::new_list[i].SKEL_R_Calf;
			if (!IsOnScreen(SKEL_R_Calf)) return;
			ImVec2 SKEL_L_Foot = Pool::new_list[i].Left_Foot;
			if (!IsOnScreen(SKEL_L_Foot)) return;
			ImVec2 SKEL_R_Foot = Pool::new_list[i].Right_Foot;
			if (!IsOnScreen(SKEL_R_Foot)) return;
			if (amphetamine::amphetamine_settings->Skeleton_idx == 1)
			{

				ImColor caca = { 0, 0, 0 ,255 };
				if (IsVisible)
				{
					caca = amphetamine::amphetamine_settings->SkelColor;
				}
				else
				{
					caca = amphetamine::amphetamine_settings->invisibleSkelColor;
				}

				Render_D2::Line(Neck, Clavicle_Right, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Neck, Clavicle_Left, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Clavicle_Right, Uperarm_right, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Clavicle_Left, Uperarm_left, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Uperarm_right, Elbow_r, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Uperarm_left, Elbow_l, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Elbow_r, R_FormArm, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Elbow_l, L_FormArm, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(R_FormArm, SKEL_R_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(L_FormArm, SKEL_L_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Neck, Pelvis, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Pelvis, SKEL_L_Thigh, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Pelvis, SKEL_R_Thigh, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(SKEL_L_Thigh, SKEL_L_Calf, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(SKEL_R_Thigh, SKEL_R_Calf, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(SKEL_L_Calf, SKEL_L_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(SKEL_R_Calf, SKEL_R_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

			}
			else {
				ImColor caca = { 0, 0, 0 ,255 };
				if (IsVisible)
					caca = amphetamine::amphetamine_settings->SkelColor;
				else
					caca = amphetamine::amphetamine_settings->invisibleSkelColor;
				Render_D2::Line(Neck, SKEL_L_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Neck, SKEL_R_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

				Render_D2::Line(Neck, Pelvis, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Pelvis, Left_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
				Render_D2::Line(Pelvis, Right_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
			}
		}






		if (amphetamine::amphetamine_settings->DistanceESP || amphetamine::amphetamine_settings->Weapon)
		{
			ImColor caca = { 0, 0, 0 ,255 };
			if (IsVisible)
				caca = ImColor(amphetamine::amphetamine_settings->Dist_Color);
			else
				caca = ImColor(amphetamine::amphetamine_settings->invisibleDist_Color);
			//ImVec2 TextSize = ImGui::CalcTextSize((char*)Pool::new_list[i].weapon_and_dist.c_str());
			Render_D2::Text(ImVec2(top2d.x, (TextStartY + thickness_box) + (textRow * 14)), FLOAT4TOD3rwerLOR(caca), true, true, GetWC(Pool::new_list[i].weapon_and_dist.c_str()));
		}

		float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
		float Height = abs(Head.y - Foot_Middle) * 1.35f;
		if (amphetamine::amphetamine_settings->PlayerName)
		{
			auto playerName = std::to_string((DWORD64)Pool::new_list[i].ped);
			ImColor caca = { 0, 0, 0 ,255 };
			if (IsVisible)
				caca = ImColor(amphetamine::amphetamine_settings->Name_Color);
			else
				caca = ImColor(amphetamine::amphetamine_settings->Name_Color_invisible);
			ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName.c_str());

			Render_D2::Text(ImVec2(Ped_Location.x, Ped_Location.y - Height / 2 - 12), FLOAT4TOD3rwerLOR(caca), true, true, GetWC(playerName.c_str()));

		}

		if (amphetamine::amphetamine_settings->is_ped_is_any_vehicle) {
			if (is_ped_is_any_vehicle) {
				auto playerName = ("*IN CAR*");
				ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName);
				Render_D2::Text(ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 20), FLOAT4TOD3rwerLOR(ImColor(255, 0, 0, 255)), true, true, GetWC(playerName));
			}
		}















		//ImVec2 Head = Pool::new_list[i].Head;
		//if (!IsOnScreen(Head)) return;
		//ImVec2 Left_Foot = Pool::new_list[i].Left_Foot;
		//if (!IsOnScreen(Left_Foot)) return;
		//ImVec2 Right_Foot = Pool::new_list[i].Right_Foot;
		//if (!IsOnScreen(Right_Foot)) return;

		//float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
		//float Height = abs(Head.y - Foot_Middle) * 1.35f;
		//float Width = (Height / 1.80f);
		//float HealthDistance = Width / 16;
		//if (amphetamine::amphetamine_settings->StaticESP)
		//{
		//	Vector3 mins = Vector3(Pool::new_list[i].PedModelInfo_GetMin.x, Pool::new_list[i].PedModelInfo_GetMin.y, Pool::new_list[i].PedModelInfo_GetMin.z);
		//	Vector3 maxs = Vector3(Pool::new_list[i].PedModelInfo_GetMax.x, Pool::new_list[i].PedModelInfo_GetMax.y, Pool::new_list[i].PedModelInfo_GetMax.z);

		//	Vector3 min = Vector3(pedCoordinate.x + mins.x, pedCoordinate.y + mins.y, pedCoordinate.z + mins.z);
		//	Vector3 max = Vector3(pedCoordinate.x + maxs.x, pedCoordinate.y + maxs.y, pedCoordinate.z + maxs.z);
		//	Vector3 points[] = {
		//			Vector3(min.x, min.y, min.z),
		//			Vector3(min.x, max.y, min.z),
		//			Vector3(max.x, max.y, min.z),
		//			Vector3(max.x, min.y, min.z),
		//			Vector3(max.x, max.y, max.z),
		//			Vector3(min.x, max.y, max.z),
		//			Vector3(min.x, min.y, max.z),
		//			Vector3(max.x, min.y, max.z)
		//	};
		//	ImVec2 w2s_points[8];
		//	auto index = 0;
		//	for (Vector3 point : points) {
		//		w2s_points[index] = Memory::WorldToScreen(point);
		//		if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
		//			continue;
		//		index++;
		//	}

		//	float x = w2s_points[0].x;
		//	float y = w2s_points[0].y;
		//	float width = w2s_points[0].x;
		//	float height = w2s_points[0].y;
		//	for (auto point : w2s_points) {
		//		if (x > point.x)
		//			x = point.x;
		//		if (width < point.x)
		//			width = point.x;
		//		if (y > point.y)
		//			y = point.y;
		//		if (height < point.y)
		//			height = point.y;
		//	}

		//	int out_x = x;
		//	int out_y = y;
		//	int out_w = width - x;
		//	int out_h = height - y;
		//	Height = out_h;
		//	Width = out_w;

		//	Width = (Height / 1.80f);
		//	if (((Ped_Location.x + Width / 2) - (Ped_Location.x - Width / 2)) > 600)
		//		return;
		//}
		//if (amphetamine::amphetamine_settings->Snapline)
		//{
		//	Render_D2::Line(ImVec2(LocalPlayer_Location.x, (LocalPlayer_Location.y + 200)), Ped_Location, FLOAT4TOD3rwerLOR(ImColor(amphetamine::amphetamine_settings->SnapLines_Color)), 1.f, true);
		//}
		//ImVec2 CordsToDraw = ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2);
		//if (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 1) {
		//	ImColor caca = { amphetamine::amphetamine_settings->Box_Color };
		//	if (amphetamine::amphetamine_settings->rainbowbox) {
		//		Render_D2::Rectangle(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2( Width,  Height), D2D1::ColorF::Black, 1.8 * amphetamine::amphetamine_settings->BoxSize);
		//		Render_D2::Rectangle(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2( Width,  Height), FLOAT4TOD3rwerLOR(rgbcolor), 1 * amphetamine::amphetamine_settings->BoxSize);
		//	}
		//	else {
		//		Render_D2::Rectangle(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Width, Height), D2D1::ColorF::Black, 1.8 * amphetamine::amphetamine_settings->BoxSize);
		//		Render_D2::Rectangle(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Width, Height), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize);
		//	}
		//}
		//if (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 2) {
		//	float CornerSize = (Width) / 4.f;
		//	ImColor caca;
		//	if (amphetamine::amphetamine_settings->rainbowbox) 
		//		caca = rgbcolor;
		//	else 
		//		caca = { amphetamine::amphetamine_settings->Box_Color };

		//	Render_D2::Line(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);
		//	Render_D2::Line(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);

		//	Render_D2::Line(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);
		//	Render_D2::Line(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);

		//	Render_D2::Line(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);
		//	Render_D2::Line(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);

		//	Render_D2::Line(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);
		//	Render_D2::Line(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), FLOAT4TOD3rwerLOR(caca), 1 * amphetamine::amphetamine_settings->BoxSize, true);
		//}
		//if (amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 1 || amphetamine::amphetamine_settings->Npc_Box_Esp_Type == 2)
		//{
		//	if (amphetamine::amphetamine_settings->Filled)
		//	{
		//		Render_D2::FillRectangle(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), FLOAT4TOD3rwerLOR(ImColor(0, 0, 0, amphetamine::amphetamine_settings->FillBoxAlpha)));
		//	}
		//}
		//if (amphetamine::amphetamine_settings->Skeleton)
		//{
		//	ImVec2 Pelvis = Pool::new_list[i].Pelvis;
		//	if (!IsOnScreen(Pelvis)) return;
		//	ImVec2 Neck = Pool::new_list[i].Neck;
		//	if (!IsOnScreen(Neck)) return;
		//	ImVec2 Clavicle_Left = Pool::new_list[i].Clavicle_Left;
		//	if (!IsOnScreen(Clavicle_Left)) return;
		//	ImVec2 Clavicle_Right = Pool::new_list[i].Clavicle_Right;
		//	if (!IsOnScreen(Clavicle_Right)) return;
		//	ImVec2 Uperarm_left = Pool::new_list[i].Uperarm_left;
		//	if (!IsOnScreen(Uperarm_left)) return;
		//	ImVec2 Uperarm_right = Pool::new_list[i].Uperarm_right;
		//	if (!IsOnScreen(Uperarm_right)) return;
		//	ImVec2 Elbow_l = Pool::new_list[i].Elbow_l;
		//	if (!IsOnScreen(Elbow_l)) return;
		//	ImVec2 Elbow_r = Pool::new_list[i].Elbow_r;
		//	if (!IsOnScreen(Elbow_r)) return;
		//	ImVec2 R_FormArm = Pool::new_list[i].R_FormArm;
		//	if (!IsOnScreen(R_FormArm)) return;
		//	ImVec2 L_FormArm = Pool::new_list[i].L_FormArm;
		//	if (!IsOnScreen(L_FormArm)) return;
		//	ImVec2 SKEL_R_Hand = Pool::new_list[i].SKEL_R_Hand;
		//	if (!IsOnScreen(SKEL_R_Hand)) return;
		//	ImVec2 SKEL_L_Hand = Pool::new_list[i].SKEL_L_Hand;
		//	if (!IsOnScreen(SKEL_L_Hand)) return;
		//	ImVec2 SKEL_L_Thigh = Pool::new_list[i].SKEL_L_Thigh;
		//	if (!IsOnScreen(SKEL_L_Thigh)) return;
		//	ImVec2 SKEL_L_Calf = Pool::new_list[i].SKEL_L_Calf;
		//	if (!IsOnScreen(SKEL_L_Calf)) return;
		//	ImVec2 SKEL_R_Thigh = Pool::new_list[i].SKEL_R_Thigh;
		//	if (!IsOnScreen(SKEL_R_Thigh)) return;
		//	ImVec2 SKEL_R_Calf = Pool::new_list[i].SKEL_R_Calf;
		//	if (!IsOnScreen(SKEL_R_Calf)) return;
		//	ImVec2 SKEL_L_Foot = Pool::new_list[i].Left_Foot;
		//	if (!IsOnScreen(SKEL_L_Foot)) return;
		//	ImVec2 SKEL_R_Foot = Pool::new_list[i].Right_Foot;
		//	if (!IsOnScreen(SKEL_R_Foot)) return;
		//	if (amphetamine::amphetamine_settings->Skeleton_idx == 1)
		//	{

		//		ImColor caca = { 0, 0, 0 ,255 };
		//		if (IsVisible)
		//		{
		//			caca = amphetamine::amphetamine_settings->SkelColor;
		//		}
		//		else
		//		{
		//			caca = amphetamine::amphetamine_settings->invisibleSkelColor;
		//		}

		//		Render_D2::Line(Neck, Clavicle_Right, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Neck, Clavicle_Left, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Clavicle_Right, Uperarm_right, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Clavicle_Left, Uperarm_left, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Uperarm_right, Elbow_r, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Uperarm_left, Elbow_l, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Elbow_r, R_FormArm, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Elbow_l, L_FormArm, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(R_FormArm, SKEL_R_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(L_FormArm, SKEL_L_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Neck, Pelvis, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Pelvis, SKEL_L_Thigh, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Pelvis, SKEL_R_Thigh, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(SKEL_L_Thigh, SKEL_L_Calf, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(SKEL_R_Thigh, SKEL_R_Calf, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(SKEL_L_Calf, SKEL_L_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(SKEL_R_Calf, SKEL_R_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//	}
		//	else {
		//		ImColor caca = { 0, 0, 0 ,255 };
		//		if (IsVisible)
		//			caca = amphetamine::amphetamine_settings->SkelColor;
		//		else
		//			caca = amphetamine::amphetamine_settings->invisibleSkelColor;
		//		Render_D2::Line(Neck, SKEL_L_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Neck, SKEL_R_Hand, FLOAT4TOD3rwerLOR(caca), 1.5f, true);

		//		Render_D2::Line(Neck, Pelvis, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Pelvis, Left_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//		Render_D2::Line(Pelvis, Right_Foot, FLOAT4TOD3rwerLOR(caca), 1.5f, true);
		//	}


		//}
		//bool IsOnGlife = false;
		//if (Pool::new_list[i].maxhealth > 201)
		//	IsOnGlife = true;





		//if (amphetamine::amphetamine_settings->HealthBar_idx != 4) {

		//	float HealthPercentage = Height / 100 * (Pool::new_list[i].health - 100);
		//	float HealthPercentagee = Height / 100 * 100;
		//	if (IsOnGlife)
		//		HealthPercentage = Height / 100 * ((Pool::new_list[i].health - 100) / 2);

		//	float fixedhealth = Pool::new_list[i].health / 2;
		//	if (IsOnGlife)
		//		(Pool::new_list[i].health - 100) / 2;
		//	float fixedhealthh = 100;

		//	ImColor	col = ImColor(52, 176, 48, 255);
		//	ImColor coll = ImColor(0, 0, 0, 255);

		//	float  caca = (Width) / 8.f;
		//	if (Distance < 20)
		//	{
		//		caca = (Width) / 10.f;
		//	}
		//	float HealthPercentageeee = Width / 100 * (Pool::new_list[i].health - 100);


		//	if (fixedhealth > 0 && fixedhealth < 101)
		//	{
		//		if (amphetamine::amphetamine_settings->HealthBar_idx == 0)
		//		{
		//			if (fixedhealth != 0)
		//				DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
		//			DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 1)
		//		{
		//			if (fixedhealth != 0)
		//				DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
		//			DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 2)
		//		{

		//			if (fixedhealth != 0)
		//				DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 22), ImVec2(5.4, Width), coll);
		//			DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 22), ImVec2(5, HealthPercentageeee), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 3)
		//		{
		//			if (fixedhealth != 0)
		//				DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 22), ImVec2(5.4, Width), coll);
		//			DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 22), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 22), ImVec2(5, Width / 100 * (Pool::new_list[i].health - 100.f)), col);



		//			/*const auto health_pc = min(Peds->GetHealth() / 100, 1);
		//			const auto health_color =
		//				ImColor::HSV((health_pc * .25f), 1, .875f * 1);
		//			float flBoxes = std::ceil(Peds->GetHealth() / 10.f);
		//			float flX = Ped_Location.x + 4; float flY = Ped_Location.y;
		//			float flHeight = Height / 10.f;
		//			ImVec2 Head = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x796E);
		//			if (!IsOnScreen(Head)) continue;
		//			ImVec2 Left_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x3779);
		//			if (!IsOnScreen(Left_Foot)) continue;
		//			ImVec2 Right_Foot = Memory::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xCC4D);
		//			if (!IsOnScreen(Right_Foot)) continue;
		//			ImVec2 tempFeet = (Right_Foot + Left_Foot) / 2.f;
		//			float Entity_h = (Head.y + 0.2f) - tempFeet.y;
		//			float Entity_w = Entity_h / 2;
		//			float w = Entity_h / 4;
		//			float Entity_x = tempFeet.x - w;
		//			float Entity_y = tempFeet.y;
		//			float health = Peds->GetHealth();
		//			float maxheal = 201.f;
		//			DrawFilledRect(Entity_x + (Entity_w / 2) - 19, Entity_y + 27, 35, 4, ImColor(0, 0, 0, 255));
		//			DrawFilledRect(Entity_x + (Entity_w / 2) - 19, Entity_y + 27, 35 * (health / maxheal), 3, health_color);*/


		//			//	Renderer::FillRectangle({ Entity_x + (Entity_w / 2) - 19, Entity_y + 27 }, { 35, 4 }, D2D1::ColorF::Black);
		//				//Renderer::FillRectangle({ Entity_x + (Entity_w / 2) - 19, Entity_y + 27 }, { 35 * (health / maxheal), 3 }, colorf);
		//		}



		//		//DrawMultiColorHealthBar(ImVec2((Ped_Location.x + Width / 2) + HealthDistance + 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) + HealthDistance, (Ped_Location.y + Height / 2) - HealthPercentage), col, ImColor(255, 0, 0, 255));
		//	}
		//}
		//if (amphetamine::amphetamine_settings->ArmorBar)
		//{
		//	float HealthPercentage = Height / 100 * (Pool::new_list[i].armor);
		//	float HealthPercentagee = Height / 100 * 100;
		//	float fixedArmor = Pool::new_list[i].armor;

		//	float fixedhealthh = 100;

		//	ImColor col = ImColor(10, 145, 255, 255);
		//	ImColor coll = ImColor(0, 0, 0, 255);

		//	float  caca = (Width) / 8.f;
		//	if (Distance < 20)
		//	{
		//		caca = (Width) / 10.f;
		//	}
		//	float HealthPercentageeee = Width / 100 * (Pool::new_list[i].armor);

		//	if (fixedArmor > 0 && fixedArmor < 101)
		//	{
		//		if (amphetamine::amphetamine_settings->HealthBar_idx == 0)
		//		{
		//			if (fixedArmor != 0)
		//				DrawHealthBar(ImVec2((Ped_Location.x + 9 + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
		//			DrawHealthBar(ImVec2((Ped_Location.x + 9 + Width / 2) + HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 1)
		//		{
		//			if (fixedArmor != 0)
		//				DrawHealthBar(ImVec2((Ped_Location.x - 9 - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(4.2, Height), coll);
		//			DrawHealthBar(ImVec2((Ped_Location.x - 9 - Width / 2) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 2)
		//		{

		//			if (fixedArmor != 0)
		//				DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 32), ImVec2(5.4, Width), coll);
		//			DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y + Height / 2) + caca + 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) + caca + 32), ImVec2(5, HealthPercentageeee), col);

		//		}
		//		else if (amphetamine::amphetamine_settings->HealthBar_idx == 3)
		//		{
		//			if (fixedArmor != 0)
		//				DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 32), ImVec2(5.4, Width), coll);
		//			DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 32), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 32), ImVec2(5, HealthPercentageeee), col);

		//		}
		//	}
		//}
		//if (amphetamine::amphetamine_settings->DistanceESP || amphetamine::amphetamine_settings->Weapon)
		//{
		//	ImColor caca = { 0, 0, 0 ,255 };
		//	if (IsVisible)
		//		caca = ImColor(amphetamine::amphetamine_settings->Dist_Color);
		//	else
		//		caca = ImColor(amphetamine::amphetamine_settings->invisibleDist_Color);
		//	ImVec2 TextSize = ImGui::CalcTextSize((char*)Pool::new_list[i].weapon_and_dist.c_str());
		//	//DrawOutlinedText(font::poppins_medium_low, Pool::new_list[i].weapon_and_dist, ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y + Height / 2 + 5), 15.f, caca, true);



		//	Render_D2::Text(ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 5), FLOAT4TOD3rwerLOR(caca), true, true, GetWC(Pool::new_list[i].weapon_and_dist.c_str()));

		//}
		//if (amphetamine::amphetamine_settings->PlayerName)
		//{
		//	auto playerName = std::to_string((DWORD64)Pool::new_list[i].ped);
		//	ImColor caca = { 0, 0, 0 ,255 };
		//	if (IsVisible)
		//		caca = ImColor(amphetamine::amphetamine_settings->Name_Color);
		//	else
		//		caca = ImColor(amphetamine::amphetamine_settings->Name_Color_invisible);
		//	ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName.c_str());
		//	//DrawOutlinedText(font::poppins_medium_low, playerName, ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y - Height / 2 - 5 - 12), 15.f, caca, true);

		//	Render_D2::Text(ImVec2(Ped_Location.x, Ped_Location.y - Height / 2  - 12), FLOAT4TOD3rwerLOR(caca), true, true, GetWC(playerName.c_str()));

		//}

		//if (amphetamine::amphetamine_settings->is_ped_is_any_vehicle) {
		//	if (is_ped_is_any_vehicle) {
		//		auto playerName = ("*IN CAR*");
		//		ImVec2 TextSize = ImGui::CalcTextSize((char*)playerName);
		//		//DrawOutlinedText(font::poppins_medium_low, playerName, ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y + Height / 2 + 20), 14.f, ImColor(255, 0, 0, 255), true);
		//		Render_D2::Text(ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 20), FLOAT4TOD3rwerLOR(ImColor(255, 0, 0, 255)), true, true, GetWC(playerName));

		//		//Render_D2::Textplussize(ImVec2(Ped_Location.x - TextSize.x / 2, Ped_Location.y - Height / 2 - 5 - 12), FLOAT4TOD3rwerLOR(caca), true, true, GetWC(playerName.c_str()));

		//	}
		//}
	}
	void VehicleESP() {
		if (amphetamine::amphetamine_settings->VehicleEsp) {
			hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(Memory::ReplayInterface);
			if (!ReplayInterface)
				return;
			hk_VehicleInterface* VehicleInterface = ReplayInterface->VehicleInterface();
			if (!VehicleInterface)
				return;
			for (int i = 0; i < VehicleInterface->VehicleMaximum(); i++) {

				hk_Vehicle* Peds = VehicleInterface->VehicleList()->Vehicle(i);
				if (!Peds) continue;
				Vector3 localpos = *(Vector3*)(Memory::LocalPlayer + 0x90);
				auto Distance = Aimbot::get_distance(localpos, Peds->GetCoordinate());
				if (Aimbot::get_distance(localpos, Peds->GetCoordinate()) > amphetamine::amphetamine_settings->DistanceVehicle)
					continue;
				auto playerName = Peds->VehicleModelInfo()->GetCharName();
				std::string VehicleName = playerName;
				ImVec2 peds_location = Memory::WorldToScreen(Peds->GetCoordinate());
				if (!IsOnScreen(peds_location)) continue;
				std::string str = "";
				if (amphetamine::amphetamine_settings->VehicleEsp_Name)
				{
					str.append(VehicleName);
				}
				if (amphetamine::amphetamine_settings->VehicleEsp_Distance) {
					std::string strr = " [" + std::to_string((int)round(Distance)) + "m]";
					if (!amphetamine::amphetamine_settings->VehicleEsp_Name)
						strr = "[" + std::to_string((int)round(Distance)) + "m]";
					str.append(strr);
				}
				if (amphetamine::amphetamine_settings->VehicleEsp_Distance || amphetamine::amphetamine_settings->VehicleEsp_Name)
				{
					ImVec2 TextSize = ImGui::CalcTextSize((char*)str.c_str());
					DrawOutlinedText(font::poppins_medium_low, str, ImVec2(peds_location.x - TextSize.x / 2, peds_location.y), 14.f, ImColor(amphetamine::amphetamine_settings->Name_Color_vehicle), true);
			
				}
				if (amphetamine::amphetamine_settings->VehicleEsp_3Dbox) {

					//vehicle::get_vehicle_doors_locked_for_player(); //закрыта ли

					//vehicle::get_is_vehicle_engine_running(); //заведена ли машина

				}
			}
		}
	}
}
#include "AimBot.hpp"
#include "Entity.hpp"