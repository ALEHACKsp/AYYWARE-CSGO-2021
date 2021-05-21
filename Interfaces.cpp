/*
Syn's AyyWare Framework 2015
*/

#include "Interfaces.h"
#include "Utilities.h"

//SDK Specific Definitions
typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

//Some globals for later
CreateInterface_t EngineFactory = NULL; // These are used to store the individual
CreateInterface_t ClientFactory = NULL; //  CreateInterface functions for each game
CreateInterface_t VGUISurfaceFactory = NULL; //  dll that we need access to. Can call
CreateInterface_t VGUI2Factory = NULL; //  them to recieve pointers to game classes.
CreateInterface_t MatFactory = NULL;
CreateInterface_t PhysFactory = NULL;
CreateInterface_t StdFactory = NULL;
CreateInterface_t InputSystemPointer = NULL;

void Interfaces::Initialise()
{
	
	//Get function pointers to the CreateInterface function of each module
	EngineFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Engine, "CreateInterface");
	ClientFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Client, "CreateInterface");
	VGUI2Factory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VGUI2, "CreateInterface");
	VGUISurfaceFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VGUISurface, "CreateInterface");
	MatFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Material, "CreateInterface");
	PhysFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::VPhysics, "CreateInterface");
	StdFactory = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::Modules::Stdlib, "CreateInterface");
	InputSystemPointer = (CreateInterface_t)GetProcAddress((HMODULE)Utilities::Memory::WaitOnModuleHandle("inputsystem.dll"), "CreateInterface");

	//Get the interface names regardless of their version number by scanning for each string
	//#define CLIENT_DLL_INTERFACE_VERSION		"VClient017" 
	char* CHLClientInterfaceName = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClient0");
	char* VGUI2PanelsInterfaceName = (char*)Utilities::Memory::FindTextPattern("vgui2.dll", "VGUI_Panel0");
	char* VGUISurfaceInterfaceName = (char*)Utilities::Memory::FindTextPattern("vguimatsurface.dll", "VGUI_Surface0");
	char* EntityListInterfaceName = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClientEntityList0");
	char* EngineDebugThingInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VDebugOverlay0");
	char* EngineClientInterfaceName = (char*)Utilities::Memory::FindTextPattern("engine.dll","VEngineClient0");
	char* ClientPredictionInterface = (char*)Utilities::Memory::FindTextPattern("client.dll", "VClientPrediction0");
	char* MatSystemInterfaceName = (char*)Utilities::Memory::FindTextPattern("materialsystem.dll", "VMaterialSystem0");
	char* EngineRenderViewInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineRenderView0");
	char* EngineModelRenderInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineModel0");
	char* EngineModelInfoInterface = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VModelInfoClient0");
	char* EngineTraceInterfaceName = (char*)Utilities::Memory::FindTextPattern("engine.dll", "EngineTraceClient0");
	char* PhysPropsInterfaces = (char*)Utilities::Memory::FindTextPattern("client.dll", "VPhysicsSurfaceProps0");
	char* VEngineCvarName = (char*)Utilities::Memory::FindTextPattern("engine.dll", "VEngineCvar00");

	Utilities::Log("CHLClientInterfaceName Base %x", CHLClientInterfaceName);
	Utilities::Log("VGUI2PanelsInterfaceName Base %x", VGUI2PanelsInterfaceName);
	Utilities::Log("VGUISurfaceInterfaceName Base %x", VGUISurfaceInterfaceName);
	Utilities::Log("EntityListInterfaceName Base %x", EntityListInterfaceName);
	Utilities::Log("EngineDebugThingInterface Base %x", EngineDebugThingInterface);
	Utilities::Log("EngineClientInterfaceName Base %x", EngineClientInterfaceName);
	Utilities::Log("ClientPredictionInterface Base %x", ClientPredictionInterface);
	Utilities::Log("MatSystemInterfaceName Base %x", MatSystemInterfaceName);
	Utilities::Log("EngineRenderViewInterface Base %x", EngineRenderViewInterface);
	Utilities::Log("EngineModelRenderInterface Base %x", EngineModelRenderInterface);
	Utilities::Log("EngineModelInfoInterface Base %x", EngineModelInfoInterface);
	Utilities::Log("EngineTraceInterfaceName Base %x", EngineTraceInterfaceName);
	Utilities::Log("PhysPropsInterfaces Base %x", PhysPropsInterfaces);
	Utilities::Log("VEngineCvarName Base %x", VEngineCvarName);



	// Use the factory function pointers along with the interface versions to grab
	//  pointers to the interfaces
	Client = (IBaseClientDLL*)ClientFactory(CHLClientInterfaceName, NULL);
	Engine = (IVEngineClient*)EngineFactory(EngineClientInterfaceName, NULL);
	Panels = (IPanel*)VGUI2Factory(VGUI2PanelsInterfaceName, NULL);
	Surface = (ISurface*)VGUISurfaceFactory(VGUISurfaceInterfaceName, NULL);
	EntList = (IClientEntityList*)ClientFactory(EntityListInterfaceName, NULL);
	DebugOverlay = (IVDebugOverlay*)EngineFactory(EngineDebugThingInterface, NULL);
	Prediction = (DWORD*)ClientFactory(ClientPredictionInterface, NULL);
	MaterialSystem = (CMaterialSystem*)MatFactory(MatSystemInterfaceName, NULL);
	RenderView = (CVRenderView*)EngineFactory(EngineRenderViewInterface, NULL);
	ModelRender = (IVModelRender*)EngineFactory(EngineModelRenderInterface, NULL);
	ModelInfo = (CModelInfo*)EngineFactory(EngineModelInfoInterface, NULL);
	Trace = (IEngineTrace*)EngineFactory(EngineTraceInterfaceName, NULL);
	PhysProps = (IPhysicsSurfaceProps*)PhysFactory(PhysPropsInterfaces, NULL);
	CVar = (ICVar*)StdFactory(VEngineCvarName, NULL);
	ClientMode = **(IClientModeShared***)((*(DWORD**)Interfaces::Client)[10] + 0x5);

	Utilities::Log("Interface Create Complete");

	// Get ClientMode Pointer
	DWORD p = Utilities::Memory::FindPattern("client.dll", (BYTE*)"\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xA8\x01\x75\x1A\x83\xC8\x01\xA3\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56", "xx????????xxxxxxxx????x????x????x????xxxx????x????x");
	InputSystem = (IInputSystem*)InputSystemPointer("InputSystemVersion001", NULL);

	// Search through the first entry of the Client VTable
	// The initializer contains a pointer to the 'GlobalsVariables' Table

	/*
304F0C10          | 55                  | push ebp                                              |
304F0C11          | 8BEC                | mov ebp,esp                                           |
304F0C13          | 83E4 F8             | and esp,FFFFFFF8                                      |
304F0C16          | 81EC 0C010000       | sub esp,10C                                           |
304F0C1C          | 56                  | push esi                                              |
304F0C1D          | 83EC 0C             | sub esp,C                                             |
304F0C20          | E8 4B665C00         | call client.30AB7270                                  |
304F0C25          | 8B45 0C             | mov eax,dword ptr ss:[ebp+C]                          |
304F0C28          | 8D4D 08             | lea ecx,dword ptr ss:[ebp+8]                          |
304F0C2B          | 83C4 0C             | add esp,C                                             |
304F0C2E          | A3 D0B8FE30         | mov dword ptr ds:[30FEB8D0],eax           	gpGlobals = pGlobals;            |
	*/
	Globals = **(CGlobalVarsBase * **)((*(DWORD * *)Interfaces::Client)[0] + 0x1F); //psilent fix

	//Client vtable
	PDWORD pdwClientVMT = *(PDWORD*)Client;
	pInput = *(CInput * *)(Utilities::Memory::FindPatternV2("client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);

	Utilities::Log("pInput Base %x", pInput);


	Utilities::Log("Interfaces Ready");
}

// Namespace to contain all the valve interfaces
namespace Interfaces
{
	IBaseClientDLL* Client = nullptr;
	IVEngineClient* Engine = nullptr;
	IPanel* Panels = nullptr;
	IClientEntityList* EntList = nullptr;
	ISurface* Surface = nullptr;
	IVDebugOverlay* DebugOverlay = nullptr;
	IClientModeShared* ClientMode = nullptr;
	CGlobalVarsBase *Globals = nullptr;
	DWORD *Prediction = nullptr;
	CMaterialSystem* MaterialSystem = nullptr;
	CVRenderView* RenderView = nullptr;
	IVModelRender* ModelRender = nullptr;
	CModelInfo* ModelInfo = nullptr;
	IEngineTrace* Trace = nullptr;
	IPhysicsSurfaceProps* PhysProps = nullptr;
	ICVar *CVar = nullptr;
	CInput* pInput = nullptr;
	IInputSystem* InputSystem = nullptr;

};