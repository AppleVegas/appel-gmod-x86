class C_GMOD_Player : public C_HL2MP_Player
{
public: // 392 - 11
	virtual bool		IsSprinting();
	virtual void		AchievementThink();
	virtual char const* GetNetworkIDString();
	virtual char const*	GetUniqueID();
	virtual double		GetSnapAngles();
	virtual Vector		SnapToGrid(Vector&);
	virtual int			GetViewEntity();
	virtual Vector		GetPlayerColor();
	virtual Vector		GetWeaponColor();
	virtual void		SetPlayerColor(Vector color);
	virtual void		SetWeaponColor(Vector color);
};
template< typename Function > Function getvfunc(PVOID Base, DWORD Index)
{

	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}
class CPlayerResource
{
public:
	int GetArmor(int index) {
		typedef int(__thiscall* OriginalFn)(void*, int);
		return getvfunc<OriginalFn>(this, 203/*Index 19*/)(this, index);
	}
};