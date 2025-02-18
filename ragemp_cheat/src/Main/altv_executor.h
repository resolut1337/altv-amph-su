







namespace Executor
{
	void Initialize();
	void File(std::string const& str);
	void Find(std::string const& str);
	void Remove(std::string const& str);
	void Dump();
};
typedef __int64(__fastcall* _CreateHook)(__int64 a1, __int64 a2, unsigned __int64* a3);
typedef __int64(__fastcall* _EnableHook)(__int64 a1);
typedef unsigned __int64* (__fastcall* _ConsoleMessage)(__int64 a1, const char* a2);
typedef __int64(__fastcall* _NewString)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, int a5);

_ConsoleMessage ConsoleMessagePtr = nullptr;
_NewString NewStringPtr = nullptr;

class Script
{
public:
	std::string Path = "strc.js";
	std::string Code;

	Script(const char* path, const char* code)
	{
		Path = path;
		Code = code;
	}
};

class Resource
{
public:
	std::string Name = "server";
	std::vector<Script> Scripts;

	Resource(const char* name)
	{
		Name = name;
	}
};

std::vector<Script> scripts_exec;
std::vector<Resource> resources;

std::string findstr = "import";
std::string tmpstr;
std::string codestr;
std::string rmvstr;
std::string execstr;

bool found = false;
bool active = false;

void remove_all(std::string& from, std::string const& to)
{
	size_t start_pos = 0;
	while ((start_pos = from.find(to, start_pos)) != std::string::npos) {
		from.replace(start_pos, to.length(), "");
		start_pos += 1;
	}
}

bool ends_with(std::string const& str, std::string const& ending)
{
	if (ending.size() > str.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), str.rbegin());
}

__int64 __fastcall DetourNewString(__int64 a1, __int64 a2, __int64 a3, __int64 a4, int a5)
{
	tmpstr = (const char*)a3;
	std::cout << a3 << endl;

	if (ends_with(tmpstr, ".js") || ends_with(tmpstr, ".mjs"))
		scripts.emplace_back(tmpstr.c_str(), codestr.c_str());
	else
	{
		codestr = (const char*)a3;
		remove_all(codestr, "\r");
	}

	if (!rmvstr.empty())
		remove_all(tmpstr, rmvstr);

	if (!found)
		if (tmpstr.find(findstr) != std::string::npos)
		{
			found = true;
			tmpstr += execstr;
		}

	return NewStringPtr(a1, a2, (__int64)tmpstr.c_str(), a4, -1);
}

unsigned __int64* __fastcall DetourConsoleMessage(__int64 a1, const char* a2)
{
	if (active)
	{
		resources.emplace_back((const char*)a2);

		for (auto it = scripts_exec.begin(); it != scripts_exec.end(); ++it)
			resources.back().Scripts.push_back(*it);

		scripts_exec.clear();
		active = false;
	}
	std::cout << a2 << endl;

	if (std::string((const char*)a2) == "Loaded resource")
		active = true;

	return ConsoleMessagePtr(a1, a2);
}

void Executor::Initialize()
{
	uintptr_t moduleBase = (uintptr_t)GetModuleHandleA("altv-client.dll");

	//const _CreateHook CreateHook = (_CreateHook)(moduleBase + 0x6AAC0);
	//const _EnableHook EnableHook = (_EnableHook)(moduleBase + 0x6AD40);

	//const _ConsoleMessage ConsoleMessage = (_ConsoleMessage)(moduleBase + 0x125A0);
	//_NewString NewString = (_NewString)(moduleBase + 0x1AEEBE);

	//CreateHook((__int64)ConsoleMessage, (__int64)DetourConsoleMessage, (unsigned __int64*)(&ConsoleMessagePtr));
	//CreateHook((__int64)NewString, (__int64)DetourNewString, (unsigned __int64*)(&NewStringPtr));
	//EnableHook((__int64)ConsoleMessage);
	//EnableHook((__int64)NewString);

	//Memoryqe::module_t altv_module = Memoryqe::module_t("altv-client.dll");
	_NewString NewString = _NewString(Helper::FindPattern("altv-client.dll", "E8 ? ? ? ? 4C 8B 4D 48 4D 85 C9 0F 84 ? ? ? ? 48 8B 46 10 4C 8B 00 4C 89 7C 24 ? 48 8D 55 48 4C 89 F1 E8 ? ? ? ? 48 89 F9"));

	//	_ConsoleMessage ConsoleMessage = _ConsoleMessage(Helper::FindPattern("altv-client.dll",  "E8 ? ? ? ? 0F B7 13"));
	//
	//	std::cout << ConsoleMessage << endl;

	std::cout << NewString << endl;

	//MH_CreateHook(ConsoleMessage, DetourConsoleMessage, reinterpret_cast<void**>(&ConsoleMessagePtr));
	//if (ConsoleMessage) {
	//	if (MH_EnableHook(ConsoleMessage) == MH_OK) {
	//		Beep(1000, 1000);
	//		std::cout << "created hook";
	//	}
	//	else {
	//		std::cout << "error hook";
	//	}
	//}


	MH_CreateHook(NewString, DetourNewString, reinterpret_cast<void**>(&NewStringPtr));
	if (NewString) {
		if (MH_EnableHook(NewString) == MH_OK) {
			Beep(1000, 1000);
			std::cout << "created hook";
		}
		else {
			std::cout << "error hook";
		}
	}



	CreateDirectoryA("C:\\AltCheat", NULL);
}



void Executor::File(std::string const& str)
{
	std::ifstream script;

	script.open("C:/AltCheat/" + str);
	if (script)
	{
		std::getline(script, execstr, '\0');
		std::cout << "Successfully loaded file!" << std::endl;
	}
	else
		std::cout << "Couldn't find file!" << std::endl;

	script.close();
}

void Executor::Find(std::string const& str)
{
	findstr = str;
	std::cout << "Succesfully set the find string!" << std::endl;
}

void Executor::Remove(std::string const& str)
{
	rmvstr = str;
	std::cout << "Succesfully set the remove string!" << std::endl;
}

void Executor::Dump()
{
	std::cout << "Started dumping resources..." << std::endl;

	resources.emplace_back((const char*)"xyufgh");
	for (auto it = scripts_exec.begin(); it != scripts_exec.end(); ++it)
		resources.back().Scripts.push_back(Script{ "gdfg.js","alt.log('WORK!');" });

	CreateDirectoryA("C:\\AltCheat", NULL);
	CreateDirectoryA("C:\\AltCheat\\dumper", NULL);

	for (auto res = resources.begin(); res != resources.end(); ++res)
	{
		CreateDirectoryA(std::string("C:\\AltCheat\\dumper\\" + res->Name).c_str(), NULL);
		std::cout << "Created directory: " << res->Name << std::endl;

		for (auto script = res->Scripts.begin(); script != res->Scripts.end(); ++script)
		{
			std::string dirPath = "C:\\AltCheat\\dumper\\" + res->Name;
			std::string scriptPath = script->Path;

			while (scriptPath.find("/") != std::string::npos)
			{
				std::size_t pos = scriptPath.find("/");
				dirPath += "\\" + scriptPath.substr(0, pos);
				scriptPath = scriptPath.substr(pos + 1);

				CreateDirectoryA(dirPath.c_str(), NULL);
			}

			std::ofstream file("C:/AltCheat/dumper/" + res->Name + "/" + script->Path);
			file << script->Code;

			std::cout << "Created file: " << script->Path << std::endl;
		}
	}

	std::cout << "Successfully dumped resources!" << std::endl;
}


DWORD WINAPI Main_exec()
{
	AllocConsole();

	freopen_s((FILE**)stdin, "conin$", "r", stdin);
	freopen_s((FILE**)stdout, "conout$", "w", stdout);

	Executor::Initialize();

	std::string buffer;
	std::size_t split;

	while (true)
	{
		std::getline(std::cin, buffer);

		split = buffer.find(" ");

		if (split == std::string::npos)
		{
			if (buffer.find("dump") != std::string::npos)
				Executor::Dump();

			continue;
		}

		if (buffer.find("exec") != std::string::npos)
			Executor::File(buffer.substr(split + 1));
		else if (buffer.find("find") != std::string::npos)
			Executor::Find(buffer.substr(split + 1));
		else if (buffer.find("remove") != std::string::npos)
			Executor::Remove(buffer.substr(split + 1));
	}
}

