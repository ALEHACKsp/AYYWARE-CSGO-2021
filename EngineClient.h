/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "MiscDefinitions.h"
#include "ClientRecvProps.h"
#include "offsets.h"
#include "Vector.h"

// EngineClient
//mp/src/public/cdll_int.h/IVEngineClient013
class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall * oGetScreenSize)(PVOID, int&, int&);
		return call_vfunc< oGetScreenSize >(this, 5)(this, width, height);
	}
	bool GetPlayerInfo(int ent_num, player_info_t* pinfo)
	{
		typedef bool(__thiscall * oGetPlayerInfo)(PVOID, int, player_info_t*);
		return call_vfunc< oGetPlayerInfo >(this, 8)(this, ent_num, pinfo);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall * oLocal)(PVOID);
		return call_vfunc< oLocal >(this, 12)(this);
	}
	float Time()
	{
		typedef float(__thiscall * oTime)(PVOID);
		return call_vfunc< oTime >(this, 14)(this);
	}
	void GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall * oSetViewAngles)(PVOID, Vector&);
		return call_vfunc< oSetViewAngles >(this, 18)(this, vAngles);
	}
	void SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall * oSetViewAngles)(PVOID, Vector&);
		return call_vfunc< oSetViewAngles >(this, 19)(this, vAngles);
	}
	int GetMaxClients()
	{
		typedef bool(__thiscall * oGetMaxClients)(PVOID);
		return call_vfunc< oGetMaxClients >(this, 20)(this);
	}
	bool IsConnected()
	{
		typedef bool(__thiscall * oGetScreenSize)(PVOID);
		return call_vfunc< oGetScreenSize >(this, 27)(this);
	}
	bool IsInGame()
	{
		typedef bool(__thiscall * oLocal)(PVOID);
		return call_vfunc< oLocal >(this, 26)(this);
	}
	const matrix3x4& WorldToScreenMatrix()
	{
		typedef const matrix3x4& (__thiscall * oWorldToScreenMatrix)(PVOID);
		return call_vfunc< oWorldToScreenMatrix >(this, 37)(this);
	}
	void ClientCmd_Unrestricted(char  const* cmd)
	{
		//ClientCmd_Unrestricted
		typedef void(__thiscall * oClientCmdUnres)(PVOID, const char*, char);
		return call_vfunc<oClientCmdUnres>(this, 114)(this, cmd, 0);
	}
};