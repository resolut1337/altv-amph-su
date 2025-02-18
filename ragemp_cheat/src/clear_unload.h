#include<sddl.h>
void regedit_clear() {
	PSECURITY_DESCRIPTOR pSD = nullptr;
	DWORD dwErr = 0;
	DWORD dwLengthNeeded = 0;

	if (GetFileSecurityA(".", OWNER_SECURITY_INFORMATION, pSD, 0, &dwLengthNeeded)) {
		pSD = static_cast<PSECURITY_DESCRIPTOR>(LocalAlloc(LPTR, dwLengthNeeded));

		if (GetFileSecurityA(".", OWNER_SECURITY_INFORMATION, pSD, dwLengthNeeded, &dwLengthNeeded)) {
			PSID pOwnerSid = nullptr;
			BOOL bDefaulted = FALSE;

			if (GetSecurityDescriptorOwner(pSD, &pOwnerSid, &bDefaulted)) {
				PSID pUserSid = nullptr;
				SID_IDENTIFIER_AUTHORITY authority = SECURITY_NT_AUTHORITY;

				if (AllocateAndInitializeSid(&authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_USERS, 0, 0, 0, 0, 0, 0, &pUserSid)) {
					CopySid(GetLengthSid(pOwnerSid), pUserSid, pOwnerSid);

					PSID usersid = pUserSid;

					LPSTR pSidString = nullptr;

					if (ConvertSidToStringSidA(usersid, &pSidString)) {
						std::string sidString(pSidString);
						LocalFree(pSidString);

						std::string command;

						command = "REG DELETE HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps /f";
						system(command.c_str());

						command = "REG ADD HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps /f";
						system(command.c_str());

						command = "REG DELETE HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\bam\\UserSettings\\" + sidString + " /va /f";
						system(command.c_str());

						command = "REG DELETE HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\bam\\UserSettings\\" + sidString + " /va /f";
						system(command.c_str());

						command = "REG DELETE HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store /va /f";
						system(command.c_str());

						command = "REG DELETE HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers /va /f";
						system(command.c_str());

						command = "REG DELETE HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2 /f";
						system(command.c_str());

						command = "REG ADD HKEY_USERS\\" + sidString + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2";

						system(command.c_str());
					}
					else {
						dwErr = GetLastError();
					}

					FreeSid(pUserSid);
				}
				else {
					dwErr = GetLastError();
				}
			}
			else {
				dwErr = GetLastError();
			}
		}
		else {
			dwErr = GetLastError();
		}

		LocalFree(pSD);
	}
	else {
		dwErr = GetLastError();
	}

	if (dwErr != 0) {
		std::cout << "Ошибка: " << dwErr << std::endl;
	}



	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache\" /va /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");

	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" /va /f");

	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\FirstFolder\" /va /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRU\" /va /f");
	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRULegacy\" /va /f");

	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\СomDlg32\\OpenSavePidlMRU\" /f");
	system("REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\"");

	system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\" /f");
	system("REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\"");

	system("REG DELETE \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCompatCache\" /va /f");
	system("REG DELETE \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\" /f");
	system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\"");

	system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\*.*");

	system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\CustomDestinations\\*.*");

	system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\*.*");
	system("DEL /f /q %systemroot%\\Panther\\*.*");

	system("DEL /f /q %systemroot%\\appcompat\\Programs\\*.txt");

	system("DEL /f /q %systemroot%\\appcompat\\Programs\\*.xml");

	system("DEL /f /q %systemroot%\\appcompat\\Programs\\Install\\*.txt");

	system("DEL /f /q %systemroot%\\Prefetch\\*.pf");
	system("DEL /f /q %systemroot%\\Prefetch\\*.ini");
	system("DEL /f /q %systemroot%\\Prefetch\\*.7db");
	system("DEL /f /q %systemroot%\\Prefetch\\*.ebd");
	system("DEL /f /q %systemroot%\\Prefetch\\*.bin");
	system("DEL /f /q %systemroot%\\Prefetch\\*.db");
	system("DEL /f /q %systemroot%\\Prefetch\\ReadyBoot\\*.fx");

	system("DEL /f /q %systemroot%\\Minidump\\*.*");

	//	return 0;

}


int clearwinr5() {
	std::cout << "Создание папки History" << std::endl;

	std::string folderPath = std::getenv("LOCALAPPDATA");
	folderPath += "\\Microsoft\\Windows\\INetCache\\IE";

	try {
		filesystem::create_directories(folderPath);
		std::cout << "Папка успешно создана" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Ошибка при создании папки: " << ex.what() << std::endl;
	}

	return 0;
}
int clearwinr4() {
	std::cout << "" << std::endl;

	std::string folderPath = std::getenv("LOCALAPPDATA");
	folderPath += "\\Microsoft\\Windows\\INetCache\\IE";

	if (filesystem::exists(folderPath)) {
		filesystem::remove_all(folderPath);
		std::cout << "Папка успешно удалена" << std::endl;
	}
	else {
		std::cout << "Папка не существует" << std::endl;
	}

	clearwinr5();

	return 0;
}
int clearwinr3() {
	std::cout << "Создание файла desktop.ini" << std::endl;

	std::string folderPath = std::getenv("LOCALAPPDATA");
	folderPath += "\\Microsoft\\Windows\\History";

	std::string filePath = folderPath + "\\desktop.ini";

	try {
		filesystem::create_directories(folderPath);

		std::ofstream myfile(filePath);
		if (!myfile) {
			std::cout << "Не удалось создать файл\n";
			return 1;
		}

		myfile << "[.ShellClassInfo]\n";
		myfile << "ConfirmFileOp=0\n";
		myfile << "CLSID={FF393560-C2A7-11CF-BFF4-444553540000}\n";
		myfile << "UICLSID={7BD29E00-76C1-11CF-9DD0-00A0C9034933}\n";

		myfile.close();
		std::cout << "Файл успешно создан\n";
	}
	catch (const std::exception& ex) {
		std::cerr << "Ошибка при создании файла: " << ex.what() << std::endl;
	}
	clearwinr4();
	return 0;
}
int clearwinr2() {
	std::cout << "Создание папки History" << std::endl;

	std::string folderPath = std::getenv("LOCALAPPDATA");
	folderPath += "\\Microsoft\\Windows\\History";

	try {
		filesystem::create_directories(folderPath);
		std::cout << "Папка успешно создана" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Ошибка при создании папки: " << ex.what() << std::endl;
	}

	clearwinr3();
	return 0;
}
int clearwinr1() {
	std::cout << "Очистка Win+R" << std::endl;

	std::string folderPath = std::getenv("LOCALAPPDATA");
	folderPath += "\\Microsoft\\Windows\\History";

	if (filesystem::exists(folderPath)) {
		filesystem::remove_all(folderPath);
		std::cout << "Папка успешно удалена" << std::endl;
	}
	else {
		std::cout << "Папка не существует" << std::endl;
	}

	clearwinr2();

	return 0;
}
int clearwinr() {
	clearwinr1();
	return 0;
}