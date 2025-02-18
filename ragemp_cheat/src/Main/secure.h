#pragma once
#include <windows.h>
#include <vector>
#include <algorithm>

#include <TlHelp32.h>
#include <Psapi.h>
#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN64
struct HookContext {
	BYTE original_code[64];
	SIZE_T dst_ptr;
	BYTE far_jmp[6];
};
HookContext* presenthook64;

#endif
typedef struct _PEB_LDR_DATAq {
	UINT8 _PADDING_[12];
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATAq, * PPEB_LDR_DATAq;

typedef struct _PEBq {
#ifdef _WIN64
	UINT8 _PADDING_[24];
#else
	UINT8 _PADDING_[12];
#endif
	PEB_LDR_DATAq* Ldr;
} PEBq, * PPEBq;

typedef struct _LDR_DATA_TABLE_ENTRYq {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	VOID* DllBase;
} LDR_DATA_TABLE_ENTRYq, * PLDR_DATA_TABLE_ENTRYq;

typedef struct _UNLINKED_MODULEq {
	HMODULE hModule;
	PLIST_ENTRY RealInLoadOrderLinks;
	PLIST_ENTRY RealInMemoryOrderLinks;
	PLIST_ENTRY RealInInitializationOrderLinks;
	PLDR_DATA_TABLE_ENTRYq Entry;
} UNLINKED_MODULEq;

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

std::vector<UNLINKED_MODULEq> UnlinkedModules;

struct FindModuleHandle {
	HMODULE m_hModule;
	FindModuleHandle(HMODULE hModule) : m_hModule(hModule) {
	}
	bool operator() (UNLINKED_MODULEq const& Module) const {
		return (Module.hModule == m_hModule);
	}
};
namespace tools {
	void relink_module_peb(HMODULE hModule) {
		std::vector<UNLINKED_MODULEq>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));

		if (it == UnlinkedModules.end()) {
			//DBGOUT(TEXT("Module Not Unlinked Yet!"));
			return;
		}

		RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks);
		RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks);
		RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks);
		UnlinkedModules.erase(it);
	}




	void unlink_module_peb(HMODULE hModule) {
		std::vector<UNLINKED_MODULEq>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));
		if (it != UnlinkedModules.end()) {
			return;
		}

#ifdef _WIN64
		PPEBq pPEB = (PPEBq)__readgsqword(0x60);
#else
		PPEBq pPEB = (PPEBq)__readfsdword(0x30);
#endif

		PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
		PLDR_DATA_TABLE_ENTRYq Current = NULL;

		while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL) {
			Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRYq, InLoadOrderLinks);
			if (Current->DllBase == hModule) {
				UNLINKED_MODULEq CurrentModule = { 0 };
				CurrentModule.hModule = hModule;
				CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderLinks.Blink->Flink;
				CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderLinks.Blink->Flink;
				CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderLinks.Blink->Flink;
				CurrentModule.Entry = Current;
				UnlinkedModules.push_back(CurrentModule);

				UNLINK(Current->InLoadOrderLinks);
				UNLINK(Current->InInitializationOrderLinks);
				UNLINK(Current->InMemoryOrderLinks);
				break;
			}

			CurrentEntry = CurrentEntry->Flink;
		}

		return;
	}
}