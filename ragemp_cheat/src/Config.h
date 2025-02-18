#include <ShlObj_core.h>
//SaveColorValue("Menu", "Menu Color", (float*)&c::menu_sett::menu_color_swither);
//cfg.SetBoolValue("Misc", "Particles", popit);

typedef unsigned char byteqw;
vector<string> json;
static struct {
	string product_amph = "alt_v_cheat";
} prodect_amphetamine;
void amphetamine::settings_t::upload_cfg(const std::string name_cfg) {

	nlohmann::json json{};
	//auto& object = json["cfg"];
	const size_t settings_size = sizeof(amphetamine::settings_t);
	for (int i = 0; i < settings_size; i++) {
		byteqw current_byte = *reinterpret_cast<byteqw*>(uintptr_t(this) + i);
		for (int x = 0; x < 8; x++) {
			json.push_back((int)((current_byte >> x) & 1));
		}
	}
	auto str = json.dump();
	try
	{
		cpr::Header m_cprHeader = cpr::Header
		{
			{"Content-Type", "application/json"}
		};
		auto cprRequest = cpr::Post(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&upload" + "&name_cfg=" + name_cfg + "&product_amph=" + prodect_amphetamine.product_amph }, cpr::Body{ str }, m_cprHeader);
		if (cprRequest.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		std::string szResponse = cprRequest.text;
		//std::cout << szResponse << std::endl;
	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}

}
void amphetamine::settings_t::copy_shared_code_cfg(const std::string name_cfg) {
	try
	{
		auto shared_request = cpr::Get(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&get" + "&copy_shared_cfg" + "&name_cfg=" + name_cfg + "&product_amph=" + prodect_amphetamine.product_amph });
		if (shared_request.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		std::string szResponse = shared_request.text;

		if (OpenClipboard(NULL))//открываем буфер обмена
		{
			HGLOBAL hgBuffer;
			char* chBuffer;
			EmptyClipboard(); //очищаем буфер
			hgBuffer = GlobalAlloc(GMEM_DDESHARE, szResponse.length() + 1);//выделяем память
			chBuffer = (char*)GlobalLock(hgBuffer); //блокируем память
			strcpy(chBuffer, LPCSTR(szResponse.c_str()));
			GlobalUnlock(hgBuffer);//разблокируем память
			SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
			CloseClipboard(); //закрываем буфер обмена
		}
	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}
}
void amphetamine::settings_t::shared_cfg_add(const std::string shared_key) {
	try
	{
		auto shared_request = cpr::Get(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&get" + "&shared_key=" + shared_key + "&product_amph=" + prodect_amphetamine.product_amph });
		if (shared_request.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		std::string szResponse = shared_request.text;
		if (szResponse.empty()) {
			return;
		}
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), '['), szResponse.end());
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), ']'), szResponse.end());
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), ','), szResponse.end());
		const size_t settings_size = sizeof(amphetamine::settings_t);
		if (szResponse.size() > settings_size * 8) {
			return;
		}
		for (int i = 0; i < settings_size; i++) {
			byteqw current_byte = *reinterpret_cast<byteqw*>(uintptr_t(this) + i);
			for (int x = 0; x < 8; x++) {
				if (szResponse[(i * 8) + x] == '1')
					current_byte |= 1 << x;
				else
					current_byte &= ~(1 << x);
			}
			*reinterpret_cast<byteqw*>(uintptr_t(this) + i) = current_byte;
		}

	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}
}


void C_ConfigManager::config_files()
{
	try
	{
		files.clear();
		auto cprRequest = cpr::Get(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&get" + "&cfg_name_search" + "&product_amph=" + prodect_amphetamine.product_amph });
		if (cprRequest.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		std::string szResponse = cprRequest.text;
		std::cout << szResponse << endl;
		//	system("pause");
			//string to_delete = ".txt";
		std::istringstream iss(szResponse);
		std::string item;
		while (iss >> item) {
			/*	for (std::string::size_type pos = 0; (pos = item.find(to_delete, pos)) != std::string::npos; )
					item.erase(pos, to_delete.length());*/
			files.push_back(item);
		}
		//files.push_back(szResponse);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}
}
void C_ConfigManager::remove(const std::string config)
{
	try
	{
		auto cprRequest = cpr::Get(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&remove" + "&name_cfg=" + config + "&product_amph=" + prodect_amphetamine.product_amph });
		if (cprRequest.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		//ImGui::InsertNotification({ ImGuiToastType_Success, 4000, remnot.c_str(), "amphetamine.su" });
	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}
}
void amphetamine::settings_t::load_cloud_cfg(const std::string name_cfg) {
	try
	{
		auto cprRequest = cpr::Get(cpr::Url{ "https://amph.su/client/cloud_cfg_sql.php?username=" + Global::client.username + "&get" + "&name_cfg=" + name_cfg + "&product_amph=" + prodect_amphetamine.product_amph });
		if (cprRequest.elapsed >= 5)
		{
			std::cout << "[cpr] Connection timeout." << std::endl;
		}
		std::string szResponse = cprRequest.text;
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), '['), szResponse.end());
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), ']'), szResponse.end());
		szResponse.erase(std::remove(szResponse.begin(), szResponse.end(), ','), szResponse.end());
		const size_t settings_size = sizeof(amphetamine::settings_t);
		if (szResponse.size() > settings_size * 8) {
			return;
		}
		for (int i = 0; i < settings_size; i++) {
			byteqw current_byte = *reinterpret_cast<byteqw*>(uintptr_t(this) + i);
			for (int x = 0; x < 8; x++) {
				if (szResponse[(i * 8) + x] == '1')
					current_byte |= 1 << x;
				else
					current_byte &= ~(1 << x);
			}
			*reinterpret_cast<byteqw*>(uintptr_t(this) + i) = current_byte;
		}
	}
	catch (const std::exception& e)
	{
		MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
		return;
	}
}

//
//bool amphetamine::settings_t::SaveCFG(std::string file_name) {
//
//	std::string folder, fileq;
//
//	auto get_dir = [&folder, &fileq, &file_name]() -> void
//		{
//			static TCHAR path[MAX_PATH];
//
//			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
//			{
//				folder = std::string(path) + ("\\AMTH.CSGO\\");
//				fileq = std::string(path) + ("\\AMTH.CSGO\\") + file_name;
//			}
//
//			CreateDirectory(folder.c_str(), NULL);
//		};
//	get_dir();
//
//
//	std::string file_path = fileq.c_str();
//	std::fstream file(file_path, std::ios::out | std::ios::in | std::ios::trunc);
//	file.close();
//	file.open(file_path, std::ios::out | std::ios::in);
//	if (!file.is_open()) {
//		file.close();
//		return false;
//	}
//	const size_t settings_size = sizeof(amphetamine::settings_t);
//	for (int i = 0; i < settings_size; i++) {
//		byteq current_byte = *reinterpret_cast<byteq*>(uintptr_t(this) + i);
//		for (int x = 0; x < 8; x++) {
//			file << (int)((current_byte >> x) & 1);
//		}
//	}
//	file.close();
//
//	return true;
//}
//
//bool amphetamine::settings_t::LoadCFG(std::string file_name) {
//
//	std::string folder, fileq;
//	auto get_dir = [&folder, &fileq, &file_name]() ->void
//		{
//			static TCHAR path[MAX_PATH];
//
//			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
//			{
//				folder = std::string(path) + ("\\AMTH.CSGO\\");
//				fileq = std::string(path) + ("\\AMTH.CSGO\\") + file_name;
//			}
//
//			CreateDirectory(folder.c_str(), NULL);
//		};
//	get_dir();
//
//
//	std::string file_path = fileq.c_str();
//	std::fstream file;
//	file.open(file_path, std::ios::out | std::ios::in);
//	if (!file.is_open()) {
//		file.close();
//		return false;
//	}
//	std::string line;
//	while (file) {
//		std::getline(file, line);
//		const size_t settings_size = sizeof(amphetamine::settings_t);
//		if (line.size() > settings_size * 8) {
//			file.close();
//			return false;
//		}
//		for (int i = 0; i < settings_size; i++) {
//			byteq current_byte = *reinterpret_cast<byteq*>(uintptr_t(this) + i);
//			for (int x = 0; x < 8; x++) {
//				if (line[(i * 8) + x] == '1')
//					current_byte |= 1 << x;
//				else
//					current_byte &= ~(1 << x);
//			}
//			*reinterpret_cast<byteq*>(uintptr_t(this) + i) = current_byte;
//		}
//	}
//	file.close();
//
//	return true;
//}