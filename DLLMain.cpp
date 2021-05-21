// Don't take credits for this ;) Joplin / Manhhao are the first uploaders ;)

//#define AYY_DEBUG

// General shit
#include "DLLMain.h"
#include "Utilities.h"

// Injection stuff
#include "INJ/ReflectiveLoader.h"

// Stuff to initialise
#include "Offsets.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "RenderManager.h"
#include "Hacks.h"
#include "Menu.h"
#include "AntiAntiAim.h"
#include <DbgHelp.h>

#include "Dumping.h"

#pragma comment(lib,"DbgHelp.lib")

// Used as part of the reflective DLL injection
extern HINSTANCE hAppInstance;

// Our DLL Instance
HINSTANCE HThisModule;
bool DoUnload;

//Game Crash Handler
#ifdef AYY_DEBUG

BOOL (*pMiniDumpWriteDump)(
	HANDLE                            hProcess,
	DWORD                             ProcessId,
	HANDLE                            hFile,
	MINIDUMP_TYPE                     DumpType,
	PMINIDUMP_EXCEPTION_INFORMATION   ExceptionParam,
	PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	PMINIDUMP_CALLBACK_INFORMATION    CallbackParam
)= nullptr;

LONG  GameCrashHandler(_EXCEPTION_POINTERS* ExceptionInfo) {

	HANDLE hDumpFile = CreateFile("C:\\Users\\sbb\\Desktop\\Crash.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = ExceptionInfo;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	if(pMiniDumpWriteDump){
	bool isSuccess = pMiniDumpWriteDump(GetCurrentProcess(),
		GetCurrentProcessId(),
		hDumpFile,
		MiniDumpNormal,
		&dumpInfo,
		NULL,
		NULL
	);
	if(!isSuccess)
		Utilities::Log("MiniDumpWriteDump Faied!");
		}


	return EXCEPTION_EXECUTE_HANDLER;
}
#endif // AYY_DEBUG



// Our thread we use to setup everything we need
// Everything appart from code in hooks get's called from inside 
// here.

int InitialThread()
{
	//--------------------------------------------------------------

#ifdef AYY_DEBUG
	Utilities::OpenConsole("AyyWare");
#endif
	// Intro banner with info
	PrintMetaHeader();

	//-----------------------------------------------------

	//BugLog.txt for code test when game update
	//Users[Administor]
	Utilities::EnableLogFile("C:\\Users\\sbb\\Desktop\\BugLog.txt");

	//ZwTerminateProcess
#ifdef  AYY_DEBUG
	//HMODULE hDbg = LoadLibraryW(L"‪C:\\Program Files (x86)\\Windows Kits\\10\\Debuggers\\x86\\dbghelp.dll");
	HMODULE hDbg = GetModuleHandle("dbghelp.dll");
	if(!hDbg)
		Utilities::Log("dbghelpdll not found");
	pMiniDumpWriteDump = (decltype(pMiniDumpWriteDump))GetProcAddress(hDbg,"MiniDumpWriteDump");
	Utilities::Log("MiniDumpWriteDump Base %x", pMiniDumpWriteDump);

	if(!pMiniDumpWriteDump)
		Utilities::Log("pMiniDumpWriteDump func pointer get failed!");
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)GameCrashHandler);
#endif //  AYY_DEBUG



	//---------------------------------------------------------
	// Initialise all our shit
	// 
	Offsets::Initialise(); // Set our VMT offsets and do any pattern scans
	Interfaces::Initialise(); // Get pointers to the valve classes
	NetVar.RetrieveClasses(); // Setup our NetVar manager (thanks shad0w bby)
	NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	Hacks::SetupHacks();
	Menu::SetupMenu();
	Hooks::Initialise();
	ApplyAAAHooks();

	//Test Call (Make Sure Something Correct)

#define if_non_null(X) if(!X) {\
		Utilities::Log("[ERROR]" #X "is nullptr");\
		return 0;\
	}

#define printf_interfaces_addr(X)  Utilities::Log(#X" %x",X);

	if_non_null(Interfaces::Engine);
	if_non_null(Interfaces::Client);
	if_non_null(Interfaces::Panels);
	if_non_null(Interfaces::EntList);
	if_non_null(Interfaces::Surface);
	if_non_null(Interfaces::DebugOverlay);
	if_non_null(Interfaces::ClientMode);
	if_non_null(Interfaces::Globals);
	if_non_null(Interfaces::Prediction);
	if_non_null(Interfaces::MaterialSystem);
	if_non_null(Interfaces::RenderView);
	if_non_null(Interfaces::ModelRender);
	if_non_null(Interfaces::ModelInfo);
	if_non_null(Interfaces::Trace);
	if_non_null(Interfaces::PhysProps);
	if_non_null(Interfaces::CVar);
	if_non_null(Interfaces::pInput);
	if_non_null(Interfaces::InputSystem);

	printf_interfaces_addr(Interfaces::Engine);
	printf_interfaces_addr(Interfaces::Client);
	printf_interfaces_addr(Interfaces::Panels);
	printf_interfaces_addr(Interfaces::EntList);
	printf_interfaces_addr(Interfaces::Surface);
	printf_interfaces_addr(Interfaces::DebugOverlay);
	printf_interfaces_addr(Interfaces::ClientMode);
	printf_interfaces_addr(Interfaces::Globals);
	printf_interfaces_addr(Interfaces::Prediction);
	printf_interfaces_addr(Interfaces::MaterialSystem);
	printf_interfaces_addr(Interfaces::RenderView);
	printf_interfaces_addr(Interfaces::ModelRender);
	printf_interfaces_addr(Interfaces::ModelInfo);
	printf_interfaces_addr(Interfaces::Trace);
	printf_interfaces_addr(Interfaces::PhysProps);
	printf_interfaces_addr(Interfaces::CVar);
	printf_interfaces_addr(Interfaces::pInput);
	printf_interfaces_addr(Interfaces::InputSystem);


	//// Get the entity index of the local player
	auto LocalPlayer = Interfaces::Engine->GetLocalPlayer();


	auto AllClasses = Interfaces::Client->GetAllClasses();


	Utilities::Log(">>>Interfaces Debug Start");

	Utilities::Log("LocalPlayer %x",Interfaces::EntList->GetClientEntity(LocalPlayer));
	Utilities::Log("AllClasses %x",AllClasses);




	Utilities::Log(">>>Interfaces Debug End");










	//--------------------------------------------------------------------------



	//GUI.LoadWindowState(&Menu::Window, "config.xml");

	//Dumping
	//Dump::DumpClassIds();

	//---------------------------------------------------------

	Utilities::SetConsoleColor(FOREGROUND_GREEN);
	Utilities::Log("[*]EveryThing have Ready,Have Fun");

	// While our cheat is running
	//click Unload Button And Callback will set DoUnload
	while (DoUnload == false)
	{
		Sleep(1000);
	}

	Hooks::UndoHooks();
	Sleep(2000); // Make sure none of our hooks are running
	FreeLibraryAndExitThread(HThisModule, 0);

	return 0;
}

// DllMain
// Entry point for our module
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
	)
{
	switch (fdwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpvReserved != NULL)
			*(HMODULE *)lpvReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		HThisModule = hinstDLL;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitialThread, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}