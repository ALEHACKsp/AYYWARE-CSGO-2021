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
	//NetVar.RetrieveClasses(); // Setup our NetVar manager (thanks shad0w bby)
	//NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	//Hacks::SetupHacks();
	Menu::SetupMenu();
	Utilities::Log("Menu::SetupMenu excute!");
	//Hooks::Initialise();
	//ApplyAAAHooks();



	//GUI.LoadWindowState(&Menu::Window, "config.xml");

	//Dumping
	//Dump::DumpClassIds();

	//---------------------------------------------------------
	Utilities::Log("Ready");

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