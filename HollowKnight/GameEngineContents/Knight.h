#pragma once
#include "MasterActor.h"
#include "KnightSlashEffect.h"

// 설명 :
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

private:

	bool isSlashEnd_;		// 공격 애니메이션 종료
	bool isDoubleSlashEnd_; // 더블 공격 애니메이션 종료
	bool isUpSlashEnd_;
	bool isDownSlashEnd_;
	bool isDoubleJumpEnd_;

	bool isKnightActtingMove_;
	bool isPressJumppingKey_;
	bool isPossibleDoubleSlash_;
	bool isPossibleDoubleJump_;

	bool isLookMap_;

	float KnightJumpPower_;
	float KnightDoubleJumpPower_;

	float KnightSlashTimer_; // 더블 공격 체크 타이머
	float KnightLookUpTimer_;
	float KnightLookDownTimer_;

	float4 ActtingMoveDirection_; //다른 행동중일 때 방향이 바뀌면 임시로 넣는 용도

	GameEngineStateManager KnightManager_;
	KnightSlashEffect* KnightSlashEffect_;

private:

	bool GetisKnightMove();
	void isKnihgtActtingMoveChack();

	void KnightDirectionCheck();
	void KnightActtingDirectionCheck();
	void KnightIsActtingCheck();

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
	void KnightStillStart( const StateInfo& _Info);
	void KnightStillUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

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

	void KnightFallStart(const StateInfo& _Info);
	void KnightFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFallEnd(const StateInfo& _Info);

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


	//맵

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

	//================================
	//    Bind Animation
	//================================




}; 

