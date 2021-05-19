/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "MiscDefinitions.h"
#include "ClientRecvProps.h"
#include "offsets.h"
#include "Vector.h"

#define TEAM_CS_T 2
#define TEAM_CS_CT 3

#define BONE_USED_BY_HITBOX			0x00000100

#define ptr( x, x1, x2 ) *(x*)( (DWORD)x1 + (DWORD)x2 )

class IClientRenderable;
class IClientNetworkable;
class IClientUnknown;
class IClientThinkable;
class IClientEntity;
class CSWeaponInfo;
struct WeaponInfo_t;

class CHudTexture
{
public:
	char type[64]; //0x0000
	char subtype[64]; //0x0040
	char unknowndata00[2]; //0x0080
	char charinFont; //0x0082
	char unknowndata01[1]; //0x0083
};//Size=0x00AC

class CSWeaponInfo
{
public:
	virtual ~CSWeaponInfo() {};
	char pad_0x0000[0x4]; //0x0000
	char* szWeaponName; //0x0004 
	char pad_0x0008[0xC]; //0x0008
	__int32 iMaxClip1; //0x0014 
	char pad_0x0018[0xC]; //0x0018
	__int32 max_reserved_ammo; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* m_WeaponMdlPath; //0x002C 
	char pad_0x0030[0x4]; //0x0030
	char* m_DropWeaponMdlPath; //0x0034 
	char pad_0x0038[0x48]; //0x0038
	char* m_BulletType; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	char* hud_name; //0x0088 
	char pad_0x008C[0x40]; //0x008C
	__int32 m_WeaponType; //0x00CC 
	__int32 m_WeaponPrice; //0x00D0 
	__int32 m_WeaponReward; //0x00D4 
	char* m_WeaponGroupName; //0x00D8 
	char pad_0x00DC[0x10]; //0x00DC
	unsigned char bFullAuto; //0x00EC 
	char pad_0x00ED[0x3]; //0x00ED
	__int32 iDamage; //0x00F0 
	float flArmorRatio; //0x00F4 
	__int32 bullets;
	float flPenetration; //0x00F8
	char pad_0x00F8[0x8]; //0x00FC
	float flRange; //0x0108 
	float flRangeModifier; //0x010C 
	char pad_0x0110[0x10]; //0x0110
	unsigned char silencer; //0x0120 
	char pad_0x0121[0xF]; //0x0121
	float flMaxPlayerSpeed; //0x0130 
	float flMaxPlayerSpeedAlt; //0x0134 
	char pad_0x0138[0x4C]; //0x0138
	__int32 recoil_seed; //0x0184 
	char pad_0x0188[0x68]; //0x0188
	char* m_WeaponTracesType; //0x01F0 
	char pad_0x01F4[0x638]; //0x01F4
};


enum class CSGOClassID
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

enum moveTypes
{
	MOVETYPE_NONE = 0,			// never moves
	MOVETYPE_ISOMETRIC,					// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,						// Player only - moving on the ground
	MOVETYPE_STEP,						// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,						// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,				// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,					// uses VPHYSICS for simulation
	MOVETYPE_PUSH,						// no clip to world, push and crush
	MOVETYPE_NOCLIP,					// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,					// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,					// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,					// Allows the entity to describe its own physics
	MOVETYPE_LAST = MOVETYPE_CUSTOM,	// should always be defined as the last item in the list
	MOVETYPE_MAX_BITS = 4
};

enum class CSGOHitboxID
{
	Head = 0,
	Neck,
	NeckLower,
	Pelvis,
	Stomach,
	LowerChest,
	Chest,
	UpperChest,
	RightThigh,
	LeftThigh,
	RightShin,
	LeftShin,
	RightFoot,
	LeftFoot,
	RightHand,
	LeftHand,
	RightUpperArm,
	RightLowerArm,
	LeftUpperArm,
	LeftLowerArm,
	Max,
};

// Weapon IDs
enum ItemDefinitionIndex : int
{
	WEAPON_NONE = 0,

	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER
};

class ScriptCreatedItem
{
public:
	CPNETVAR_FUNC(int*, ItemDefinitionIndex, 0xE67AB3B8); //m_iItemDefinitionIndex
	CPNETVAR_FUNC(int*, ItemIDHigh, 0x714778A); //m_iItemIDHigh
	CPNETVAR_FUNC(int*, ItemIDLow, 0x3A3DFC74); //m_iItemIDLow
};

class AttributeContainer
{
public:
	CPNETVAR_FUNC(ScriptCreatedItem*, m_Item, 0x7E029CE5);
};


class CBaseCombatWeapon
{
public:
	CNETVAR_FUNC(float, GetNextPrimaryAttack, 0xDB7B106E); //m_flNextPrimaryAttack
	CNETVAR_FUNC(int, GetAmmoInClip, 0x97B6F70C); //m_iClip1
	CNETVAR_FUNC(HANDLE, GetOwnerHandle, 0xC32DF98D); //m_hOwner
	CNETVAR_FUNC(Vector, GetOrigin, 0x1231CE10); //m_vecOrigin
	CPNETVAR_FUNC(int*, FallbackPaintKit, 0xADE4C870); // m_nFallbackPaintKit
	CPNETVAR_FUNC(int*, FallbackSeed, 0xC2D0683D); // m_nFallbackSeed
	CPNETVAR_FUNC(float*, FallbackWear, 0xA263576C); //m_flFallbackWear
	CPNETVAR_FUNC(int*, FallbackStatTrak, 0x1ED78768); //m_nFallbackStatTrak
	CPNETVAR_FUNC(int*, OwnerXuidLow, 0xAD8D897F);
	CPNETVAR_FUNC(int*, OwnerXuidHigh, 0x90511E77);
	CPNETVAR_FUNC(int*, ViewModelIndex, 0x7F7C89C1);
	CPNETVAR_FUNC(int*, ModelIndex, 0x27016F83);
	CPNETVAR_FUNC(int*, WorldModelIndex, 0x4D8AD9F3);
	CPNETVAR_FUNC(char*, szCustomName, 0x0);

	CPNETVAR_FUNC(AttributeContainer*, m_AttributeManager, 0xCFFCE089);

	CNETVAR_FUNC(int, GetZoomLevel, 0x26553F1A);

	float GetInaccuracy()
	{
		typedef float(__thiscall* oInaccuracy)(PVOID);
		return call_vfunc< oInaccuracy >(this, 469)(this);
	}

	float GetInnacc()
	{
		typedef float(__thiscall *OrigFn)(void *);
		return call_vfunc<OrigFn>(this, 469)(this);
	}

	void UpdateAccPenalty() 
	{
		typedef void(__thiscall *OrigFn)(void *);
		return call_vfunc<OrigFn>(this, 470)(this);
	}

	bool IsScoped(int x = 0)
	{
		return GetZoomLevel() > 0;
	}

	CSWeaponInfo* GetCSWpnData()
	{
		if (!this) return nullptr;

		typedef CSWeaponInfo*(__thiscall* OriginalFn)(void*);
		return  call_vfunc<OriginalFn>(this, 446)(this);
	}
};

class CCSBomb
{
public:
	CNETVAR_FUNC(HANDLE, GetOwnerHandle, 0xC32DF98D); //m_hOwner 0x29BC
	CNETVAR_FUNC(float, GetC4BlowTime, 0x297C); //m_flC4Blow 0x297C
	CNETVAR_FUNC(float, GetC4DefuseCountDown, 0x2994); //m_flDefuseCountDown 0x2994
};

class CLocalPlayerExclusive
{
public:
	CNETVAR_FUNC(Vector, GetViewPunchAngle, 0x68F014C0);//m_viewPunchAngle
	CNETVAR_FUNC(Vector, GetAimPunchAngle, 0xBF25C290);//m_aimPunchAngle
	CNETVAR_FUNC(Vector, GetAimPunchAngleVel, 0x8425E045);//m_aimPunchAngleVel
};

class CollisionProperty
{
public:
	CNETVAR_FUNC(Vector, GetMins, 0xF6F78BAB);//m_vecMins
	CNETVAR_FUNC(Vector, GetMaxs, 0xE47C6FC4);//m_vecMaxs
	CNETVAR_FUNC(unsigned char, GetSolidType, 0xB86722A1);//m_nSolidType
	CNETVAR_FUNC(unsigned short, GetSolidFlags, 0x63BB24C1);//m_usSolidFlags
	CNETVAR_FUNC(int, GetSurroundsType, 0xB677A0BB); //m_nSurroundType

	bool IsSolid()
	{
		return (GetSolidType() != SOLID_NONE) && ((GetSolidFlags() & FSOLID_NOT_SOLID) == 0);
	}
};

class IClientRenderable
{
public:
	//virtual void*					GetIClientUnknown() = 0;
	virtual Vector const&			GetRenderOrigin(void) = 0;
	virtual Vector const&			GetRenderAngles(void) = 0;
	virtual bool					ShouldDraw(void) = 0;
	virtual bool					IsTransparent(void) = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual void					GetShadowHandle() const = 0;
	virtual void*					RenderHandle() = 0;
	virtual const model_t*				GetModel() const = 0;
	virtual int						DrawModel(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBlend() = 0;

	bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		typedef bool(__thiscall* oSetupBones)(PVOID, matrix3x4*, int, int, float);
		return call_vfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
};

class IClientNetworkable
{
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass*	GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
	virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			OnDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PreDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual void			unknown();
	virtual bool			IsDormant(void) = 0;
	virtual int				GetIndex(void) const = 0;
	virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
};

class IClientUnknown
{
public:
	virtual void*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual IClientEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};

class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};

class __declspec (novtable)IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
public:
	virtual void			Release(void) = 0;
	virtual void			blahblahpad(void) = 0;
	virtual Vector&	GetAbsOrigin(void) const = 0;//in broken place use GetOrigin Below
	virtual const Vector&	GetAbsAngles(void) const = 0;

	//---                 NetVars                  ---//

	int GetGlowIndex()
	{
		return *(int*)(this + 0xA310);
	}

	CPNETVAR_FUNC(CLocalPlayerExclusive*, localPlayerExclusive, 0x7177BC3E);// m_Local
	CPNETVAR_FUNC(CollisionProperty*, collisionProperty, 0xE477CBD0);//m_Collision

	CNETVAR_FUNC(float, GetLowerBodyYaw, 0xE6996CCF); //m_flLowerBodyYawTarget
	CNETVAR_FUNC(int, GetFlags, 0xE456D580); //m_fFlags
	CNETVAR_FUNC(float, GetTargetYaw, 0xE6996CCF)
		CNETVAR_FUNC(Vector, GetOrigin, 0x1231CE10); //m_vecOrigin 0x0134
	CNETVAR_FUNC(Vector, GetRotation, 0x6BEA197A); //m_angRotation
	CNETVAR_FUNC(int, GetTeamNum, 0xC08B6C6E); //m_iTeamNum
	CNETVAR_FUNC(int, GetMaxHealth, 0xC52E1C28); //m_iMaxHealth
	CNETVAR_FUNC(int, GetHealth, 0xA93054E3); //m_iHealth
	CNETVAR_FUNC(float, GetFlashDuration, 0x4B5938D5); //m_flFlashDuration
	CNETVAR_FUNC(float, GetFlashAlpha, 0xFE79FB98); //m_flFlashMaxAlpha
	CNETVAR_FUNC(unsigned char, GetLifeState, 0xD795CCFC); //m_lifeState
	CNETVAR_FUNC(HANDLE, GetActiveWeaponHandle, 0xB4FECDA3); //m_hActiveWeapon
	CNETVAR_FUNC(int, GetTickBase, 0xD472B079); //m_nTickBase
	CNETVAR_FUNC(Vector, GetViewOffset, 0xA9F74931); //m_vecViewOffset[0]
	CNETVAR_FUNC(Vector, GetViewPunch, 0x68F014C0);
	CNETVAR_FUNC(Vector, GetPunch, 0xBF25C290);
	CNETVAR_FUNC(Vector, GetVelocity, 0x40C1CA24); //m_vecVelocity[0]
	CNETVAR_FUNC(bool, HasGunGameImmunity, 0x6AD6FA0D); //m_bGunGameImmunity
	CNETVAR_FUNC(int, ArmorValue, 0x3898634); //m_ArmorValue
	CNETVAR_FUNC(bool, HasHelmet, 0x7B97F18A); //m_bHasHelmet
	CNETVAR_FUNC(int, GetObserverMode, 0x2441D093); // m_iObserverMode
	CNETVAR_FUNC(HANDLE, GetObserverTargetHandle, 0x8660FD83); //m_hObserverTarget
	CNETVAR_FUNC(int, GetShotsFired, 0x3F2F6C66); //m_nTickBase
	CNETVAR_FUNC(float, GetSimulationTime, 0xC4560E44); //m_flSimulationTime
	CNETVAR_FUNC(float, GetAnimTime, 0xD27E8416);
	CNETVAR_FUNC(bool, IsScoped, 0x61B9C22C); //m_bIsScoped
	//CNETVAR_FUNC(int, GetPlayerCompRank, 0x75671F7F);
	// ----------------------------------------------//

	bool IsAlive()
	{
		return (GetLifeState() == LIFE_ALIVE && GetHealth() > 0);
	}

	int GetMoveType() 
	{
		if (!this)
			return 0;

		return ptr(int, this, 0x258);
	}

	QAngle* GetEyeAnglesPointer()
	{
		return reinterpret_cast<QAngle*>((DWORD)this + (DWORD)0xB344);
	}

	QAngle GetEyeAngles()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + (DWORD)0xB344);
	}

	QAngle GetEyeAnglesXY()
	{
		return *(QAngle*)((DWORD)this + GET_NETVAR("DT_CSPlayer", "m_angEyeAngles"));
	}

	Vector GetBonePos(int i)
	{
		matrix3x4 boneMatrix[128];
		if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, GetTickCount64()))
		{
			return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
		}
		return Vector(0, 0, 0);
	}

	Vector GetHeadPos()
	{
		return this->GetBonePos(6);
	}

	Vector GetHeadAngle()
	{
		return GetAbsOrigin() + GetViewOffset();
	}

	bool IsPlayer()
	{
		return GetClientClass()->m_ClassID == (int)CSGOClassID::CCSPlayer;
	}

	Vector GetOrigin2() {
		return *(Vector*)((DWORD)this + 0x00000134);
	}

	Vector GetViewAngles2() {
		return *(Vector*)((DWORD)this + 0x00000104);
	}

	Vector GetAbsOrigin2() {
		__asm {
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
			CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	Vector GetAbsAngles2() {
		__asm {
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX];
			CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}


	Vector GetEyePosition() {
		Vector Origin = *(Vector*)((DWORD)this + 0x138);
		Vector View = *(Vector*)((DWORD)this + 0x108);
		return(Origin + View);
	}
	Vector GetAimPunch() {
		return *(Vector*)((DWORD)this + 0x00003018);
	}
	bool IsImmune() {
		return *(bool*)((DWORD)this + 0x000038A0);
	}
	ClientClass *GetClientClass2() {
		PVOID Networkable = (PVOID)((DWORD)(this) + 0x8);
		using Original = ClientClass*(__thiscall*)(PVOID);
		return call_vfunc<Original>(Networkable, 2)(Networkable);
	}
	HANDLE GetWeaponHandle() {
		return *(HANDLE*)((DWORD)this + 0x00002EE8);
	}
};