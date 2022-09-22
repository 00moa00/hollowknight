#pragma once
#include "Monster.h"
#include "GrimmBeam.h"
#include "GrimmSpotLight.h"

#include "BossRoomGate.h"


enum class PatternType
{
	BATTLE_BALLOON_START,
	BATTLE_SLASH_START,
	BATTLE_AIR_DASH_START,
	BATTLE_SPIKE_START,
	BATTLE_CAST_START,
	MAX,
};



//각 스프라이트 시트마다 프레임 크기가 다르니 애니메이션 변경할때면 ScaleToCutTexture 할것
//규칙
//1. 모든 스테이트 이동의 시작과 끝에는 텔레포트가 있따
//2. 중심값(6092) 기준으로 좌우 팝업
//3. 칼질, 에어 대쉬는 플레이어 거리를 계산해서 한다.
 

enum class EventState
{
	Wait,
	Appear,
	Battle,
	Talking,
	MAX
};


class Grimm : public Monster
{
public:
	// constrcuter destructer
	Grimm();
	~Grimm();

	// delete Function
	Grimm(const Grimm& _Other) = delete;
	Grimm(Grimm&& _Other) noexcept = delete;
	Grimm& operator=(const Grimm& _Other) = delete;
	Grimm& operator=(Grimm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMonsterHit(int _Damage, float4 _StunDir) override;

private:
	bool isTeleportAppearEnd_;
	bool isTeleportDiappearEnd_;
	bool isPillarEnd_;
	bool isBowEnd_;
	bool isRoarEnd_;

	bool isBllonStartEnd_;

	bool isSprikeStartEnd_;

	bool isCastStartEnd_;
	bool isCastEndEnd_;

	bool isSlashStartEnd_;
	bool isSlashEnd_;
	bool isSlashEndEnd_;

	bool isDashStartEnd_;
	bool isDashUpEnd_;

	bool isStunHitEnd_;

	float MapCenterX_;
	float AirDashRotation_;
	float FireCreateTimer_;

	float4 AirDashDest_;

	std::string ChangeState_;

	//bool isTeleportEnd_;

	GrimmBeam* GrimmBeam_;
	GrimmSpotLight* GrimmSpotLight_;
	BossRoomGate* BossRoomGate_;
	BossRoomGate* BossRoomRightGate_;

	EventState EventState_;

	GameEngineStateManager GrimmAppearManager_;
	GameEngineStateManager GrimmBattleManager_;

	GameEngineStateManager GrimmManager_;

public:
	void SetEventState(EventState _State)
	{
		EventState_ = _State;
	}

private:
	void SetChangeStateString(PatternType _type);
	void SetRamdomPattern();


	//================================
	//    Bind State | Appear
	//================================

	void GrimmAppearWaitStart(const StateInfo& _Info);
	void GrimmAppearWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearWaitEnd(const StateInfo& _Info);

	void GrimmAppearTeleportStart(const StateInfo& _Info);
	void GrimmAppearTeleportUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearTeleportEnd(const StateInfo& _Info);

	void GrimmAppearIdle1Start(const StateInfo& _Info);
	void GrimmAppearIdle1Update(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearIdle1End(const StateInfo& _Info);

	void GrimmAppearPillarStart(const StateInfo& _Info);
	void GrimmAppearPillarUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearPillarEnd(const StateInfo& _Info);

	void GrimmAppearPillarLoopStart(const StateInfo& _Info);
	void GrimmAppearPillarLoopUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearPillarLoopEnd(const StateInfo& _Info);
	
	void GrimmAppearIdle2Start(const StateInfo& _Info);
	void GrimmAppearIdle2Update(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearIdle2End(const StateInfo& _Info);

	void GrimmAppearChangeMapStart(const StateInfo& _Info);
	void GrimmAppearChangeMapUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearChangeMapEnd(const StateInfo& _Info);

	void GrimmAppearBowStart(const StateInfo& _Info);
	void GrimmAppearBowUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearBowEnd(const StateInfo& _Info);

	void GrimmAppearRoarStart(const StateInfo& _Info);
	void GrimmAppearRoarUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearRoarEnd(const StateInfo& _Info);


	//================================
	//    Bind State | Battle
	//================================

	void GrimmBattleTeleportAppearStart(const StateInfo& _Info);
	void GrimmBattleTeleportAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleTeleportAppearEnd(const StateInfo& _Info);

	void GrimmBattleTeleportDisappearStart(const StateInfo& _Info);
	void GrimmBattleTeleportDisappearUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleTeleportDisappearEnd(const StateInfo& _Info);

	void GrimmBattleBalloonStartStart(const StateInfo& _Info);
	void GrimmBattleBalloonStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleBalloonStartEnd(const StateInfo& _Info);

	void GrimmBattleBalloonStart(const StateInfo& _Info);
	void GrimmBattleBalloonUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleBalloonEnd(const StateInfo& _Info);

	void GrimmBattleAirDashStartStart(const StateInfo& _Info);
	void GrimmBattleAirDashStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleAirDashStartEnd(const StateInfo& _Info);

	void GrimmBattleAirDashStart(const StateInfo& _Info);
	void GrimmBattleAirDashUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleAirDashEnd(const StateInfo& _Info);

	void GrimmBattleAirDashEndtStart(const StateInfo& _Info);
	void GrimmBattleAirDashEndtUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleAirDashEndtEnd(const StateInfo& _Info);

	void GrimmBattleSlashStartStart(const StateInfo& _Info);
	void GrimmBattleSlashStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleSlashStartEnd(const StateInfo& _Info);

	void GrimmBattleSlashStart(const StateInfo& _Info);
	void GrimmBattleSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleSlashEnd(const StateInfo& _Info);

	void GrimmBattleSlashUpStart(const StateInfo& _Info);
	void GrimmBattleSlashUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleSlashUpEnd(const StateInfo& _Info);

	void GrimmBattleFireStart(const StateInfo& _Info);
	void GrimmBattleFireUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleFireEnd(const StateInfo& _Info);

	void GrimmBattleSpikeStartStart(const StateInfo& _Info);
	void GrimmBattleSpikeStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleSpikeStartEnd(const StateInfo& _Info);

	void GrimmBattleSpikeStart(const StateInfo& _Info);
	void GrimmBattleSpikeUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattleSpikeEnd(const StateInfo& _Info);

	void GrimmBattlCastStartStart(const StateInfo& _Info);
	void GrimmBattlCastStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattlCastStartEnd(const StateInfo& _Info);

	void GrimmBattlCastStart(const StateInfo& _Info);
	void GrimmBattlCastUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattlCastEnd(const StateInfo& _Info);

	void GrimmBattlCastEndStart(const StateInfo& _Info);
	void GrimmBattlCastEndUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattlCastEndEnd(const StateInfo& _Info);

	void GrimmBattlStunStart(const StateInfo& _Info);
	void GrimmBattlStunUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattlStunEnd(const StateInfo& _Info);

	void GrimmBattlStunBatStart(const StateInfo& _Info);
	void GrimmBattlStunBatUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmBattlStunBatEnd(const StateInfo& _Info);

	//================================
	//    Bind 
	//================================
	bool MonsterVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
};

