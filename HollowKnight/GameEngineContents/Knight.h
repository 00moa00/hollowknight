#pragma once
#include "MasterActor.h"
#include "KnightSlashEffect.h"
#include "KnightMainLightEffect.h"
#include "KnightDonutLightEffect.h"
#include "KnightSiblingLightEffect.h"
#include "SideDarkEffect.h"
#include "ContentsFontRenderer.h"
#include "KnightStunEffect.h"
#include "LowHealth.h"

#include "KnightFocusEffect.h"

// 설명 :
// 이팩트 관리 : 공격 - 이펙트는 온오프
//				라이트 - 계속 따라다님
//				스펠 - 순간에만 만들고 삭제

//				* 이펙트는 객체 나눈걸로 통일

class GameEngineTextureRenderer;
class Knight : public MasterActor
{
public:
	// constrcuter destructer
	Knight();
	~Knight();

	// delete Function
	Knight(const Knight& _Other) = delete;
	Knight(Knight&& _Other) noexcept = delete;
	Knight& operator=(const Knight& _Other) = delete;
	Knight& operator=(Knight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	ContentsFontRenderer* ContentsFontRenderer_;

	bool isKnightPotal_;	// 포탈하고 닿았다
	bool isSlashEnd_;		// 공격 애니메이션 종료
	bool isDoubleSlashEnd_; // 더블 공격 애니메이션 종료
	bool isUpSlashEnd_;
	bool isDownSlashEnd_;
	bool isDoubleJumpEnd_;
	bool isWalkTurnEnd_;
	bool isMapWalkTurnEnd_;
	bool isFocusEnd_;
	bool isLandEnd_;
	bool isStunEnd_;
	bool isDeathEnd_;
	bool isGroundWakeUpEnd_;
	bool isWakeUpEnd_;
	bool isSitEnd_;
	bool isDoorEnd_;
	bool isReturnToIdle_;

	bool isRunTurnEnd_;

	bool isTalkingNPC_;

	bool isKnightActtingMove_;
	bool isPressJumppingKey_;
	bool isPossibleDoubleSlash_;
	bool isPossibleDoubleJump_;

	bool isLookMap_;
	bool isRunMode_;

	bool isDeath_;

	bool isInvincibility_;
	bool isKnightBlack_;

	bool isLowHealth_;					//탈진

	bool isKnihgtStillWall_;

	float KnightJumpPower_;
	float KnightDoubleJumpPower_;
	float KnightRunSpeed_;
	float KnightActtingMoveDirPower_;
	float KnightFallAccel_;
	float JumpAccel_;

	float KnightSlashCollisionTimer_;
	float KnightSlashTimer_;			// 더블 공격 체크 타이머
	float KnightLookUpTimer_;
	float KnightLookDownTimer_;
	float KnightDashTimer_;				// 대쉬 타이머
	float KnightKnockbackTimer_;		// 넉백 타이머
	float KnihgtInvincibilityTimer_;	// 무적 지속 시간
	float KnihgtInvincibilitingTimer_;	// 무적 스왑 시간
	float KnihgtFocusTimer_;

	float4 ActtingMoveDirection_;	//다른 행동중일 때 방향이 바뀌면 임시로 넣는 용도

	float4 KnockbackDirection_;

	GameEngineStateManager KnightManager_;

	KnightSlashEffect* KnightSlashEffect_;

	KnightMainLightEffect* KnightMainLightEffect_;
	KnightDonutLightEffect* KnightDonutLightEffect_;
	KnightSiblingLightEffect* KnightSiblingLightEffect_;

	SideDarkEffect* SideDarkEffect_;

	KnightStunEffect* KnightStunEffect_;

	KnightFocusEffect* KnightFocusEffect_;			//집중 이펙트 포인터 저장용


	GameEngineCollision* Test1_;
	GameEngineCollision* Test2_;

	std::string ChangeLevel_;


public:

	void SetDirInit(float4 _Dir);					// 레벨 세팅때 텍스처 반전
	void SetKnightisPotal(bool _b);

private:


	bool GetisKnightMove();
	void KnightDirectionCheck();

	void isKnihgtActtingMoveChack();
	void KnightActtingDirectionCheck();
	void KnightIsActtingCheck();


	void KnihgtSlideNegativeRenderer(); //벽타기 점프 랜더러 반전용
	void KnihgtSlidePositiveRenderer(); //벽타기 점프 랜더러 반전용

	void KnightInvincibiliting(float _DeltaTime);


	void DoubleSlashTimer(float _DeltaTime); //더블 공격(콤보) 타이머

	void LookUpTimerAndChangeState(float _DeltaTime);
	void LookDownTimerAndChangeState(float _DeltaTime);

	//================================
	//    State
	//================================

	void Walkking(float _DeltaTime);

	//================================
	//    Bind State
	//================================

	// ---- 기본 ----
	void KnightStillStart( const StateInfo& _Info);
	void KnightStillUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkTurnStart(const StateInfo& _Info);
	void KnightWalkTurnUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightRunStart(const StateInfo& _Info);
	void KnightRunUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightRunEnd(const StateInfo& _Info);

	void KnightLookDownStart(const StateInfo& _Info);
	void KnightLookDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLookDownEnd(const StateInfo& _Info);

	void KnightLookUpStart(const StateInfo& _Info);
	void KnightLookUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLookUpEnd(const StateInfo& _Info);

	void KnightJumpStart(const StateInfo& _Info);
	void KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightJumpEnd(const StateInfo& _Info);

	void KnightDoubleJumpStart(const StateInfo& _Info);
	void KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoubleJumpEnd(const StateInfo& _Info);

	void KnightLandStart(const StateInfo& _Info);
	void KnightLandUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLandEnd(const StateInfo& _Info);

	void KnightFallStart(const StateInfo& _Info);
	void KnightFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFallEnd(const StateInfo& _Info);

	void KnightDashStart(const StateInfo& _Info);
	void KnightDashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDashEnd(const StateInfo& _Info);

	void KnightFocusStart(const StateInfo& _Info);
	void KnightFocusUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFocusEnd(const StateInfo& _Info);

	// ---- 집중 폭발 ----
	void KnightFocusBurstStart(const StateInfo& _Info);
	void KnightFocusBurstUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFocusBurstEnd(const StateInfo& _Info);


	// ---- 스턴 ----
	void KnightStunStart(const StateInfo& _Info);
	void KnightStunUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightStunEnd(const StateInfo& _Info);

	// ---- 사망 ----
	void KnightDeathStart(const StateInfo& _Info);
	void KnightDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDeathEnd(const StateInfo& _Info);

	// ---- 땅에서 기상 ----
	void KnightWakeUpGroundStart(const StateInfo& _Info);
	void KnightWakeUpGroundUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWakeUpGroundEnd(const StateInfo& _Info);

	// ---- 기상 ----
	void KnightWakeUpStart(const StateInfo& _Info);
	void KnightWakeUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWakeUpEnd(const StateInfo& _Info);

	// ---- 공격 ----
	void KnightSlashStart(const StateInfo& _Info);
	void KnightSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSlashEnd(const StateInfo& _Info);

	void KnightDoubleSlashStart(const StateInfo& _Info);
	void KnightDoubleSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoubleSlashEnd(const StateInfo& _Info);

	void KnightUpSlashStart(const StateInfo& _Info);
	void KnightUpSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightUpSlashEnd(const StateInfo& _Info);

	void KnightDownSlashStart(const StateInfo& _Info);
	void KnightDownSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDownSlashEnd(const StateInfo& _Info);


	// ---- 지도 보기 ----
	void KnightMapStillStart(const StateInfo& _Info);
	void KnightMapStillUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapStillEnd(const StateInfo& _Info);

	void KnightMapWalkinglStart(const StateInfo& _Info);
	void KnightMapWalkinglUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapWalkinglEnd(const StateInfo& _Info);

	void KnightMapWalkingTurnlStart(const StateInfo& _Info);
	void KnightMapWalkingTurnlUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapWalkingTurnlEnd(const StateInfo& _Info);

	void KnightMapSitLooklStart(const StateInfo& _Info);
	void KnightMapSitLooklUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapSitLooklEnd(const StateInfo& _Info);

	void KnightMapSitWritelStart(const StateInfo& _Info);
	void KnightMapSitWritelUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapSitWritelEnd(const StateInfo& _Info);


	// ---- 슬라이드 ----
	void KnightSlideStart(const StateInfo& _Info);
	void KnightSlideUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSlideEnd(const StateInfo& _Info);

	void KnightWallJumpStart(const StateInfo& _Info);
	void KnightWallJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWallJumpEnd(const StateInfo& _Info);


	void KnightWallJumpLandStart(const StateInfo& _Info);
	void KnightWallJumpLandUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWallJumpLandEnd(const StateInfo& _Info);

	// ---- 의자 위 ----
	void KnightSitStart(const StateInfo& _Info);
	void KnightSitUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSitEnd(const StateInfo& _Info);

	// ---- NPC 대화 ----
	void KnightTalkingStart(const StateInfo& _Info);
	void KnightTalkingUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTalkingEnd(const StateInfo& _Info);

	void KnightShoppingStart(const StateInfo& _Info);
	void KnightShoppingUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightShoppingEnd(const StateInfo& _Info);

	// ---- 들어가기 ----
	void KnightDoorStart(const StateInfo& _Info);
	void KnightDoorUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoorEnd(const StateInfo& _Info);


	// ----  타블렛 본당 ----
	void KnightTabletStart(const StateInfo& _Info);
	void KnightTabletUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTabletEnd(const StateInfo& _Info);

	// ----  타블렛에서 대기로 간다 ----

	void KnightTabletReturnToIdleStart(const StateInfo& _Info);
	void KnightTabletReturnToIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTabletReturnToIdleEnd(const StateInfo& _Info);


	 
	//================================
	//    Bind 
	//================================
	bool KnightVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool KnightVSMonsterAttackCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	bool KnihgtVSBenchCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool KnihgtVSTabletCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	bool KnihgtVSNPCCollision(GameEngineCollision* _This, GameEngineCollision* _Other);		//NPC
	bool NPCNextDialogueCollision(GameEngineCollision* _This, GameEngineCollision* _Other); //NPC : 대화록 진행, 대화 종료
	bool ShopCloseCollision(GameEngineCollision* _This, GameEngineCollision* _Other);		// 상점 닫기 용

	bool KnightVSPotalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//포탈

	bool KnightVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//벽

	//================================
	//   Getter
	//================================

	KnightMainLightEffect* GetKnightMainLightEffect() const
	{
		return KnightMainLightEffect_;

	}

	KnightDonutLightEffect* GetKnightDonutLightEffect() const
	{
		return KnightDonutLightEffect_;
	}

	KnightSiblingLightEffect* GetKnightSiblingLightEffect() const
	{
		return 	KnightSiblingLightEffect_;
	}
	


}; 

