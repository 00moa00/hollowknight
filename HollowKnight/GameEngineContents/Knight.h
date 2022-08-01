#pragma once
#include "MasterActor.h"

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
	void Update(float _DeltaTime);
	void End()  {}

private:

	bool isKnightActtingMove_;
	bool isJumpping_;
	float KnightJumpPower_;
	float KnightDoubleJumpPower_;

	float4 ActtingMoveDirection_;


	GameEngineStateManager KnightManager_;

private:
	float4 GetKnightNextPos(float4 _DeltaTime);

	//bgr
	bool GetPixelRed(float4 _NextDir);
	bool GetPixelBlue(float4 _NextDir);

	//픽셀 충돌 체크
	void KnightisOnGroundCheck(float _DeltaTime);
	void KnightisWallCheck(float _DeltaTime);

	bool GetisKnightMove();
	void isKnihgtActtingMoveChack();

	void KnightDirectionCheck();
	void KnightActtingDirectionCheck();
	void KnightIsActtingCheck();



	//================================
	//    Bind State
	//================================
	void KnightStillStart( const StateInfo& _Info);
	void KnightStillUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightJumpStart(const StateInfo& _Info);
	void KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightJumpEnd(const StateInfo& _Info);

	//void KnightoubleJumpCheckUpdate(float _DeltaTime, const StateInfo& _Info);


	void KnightDoubleJumpStart(const StateInfo& _Info);
	void KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoubleJumpEnd(const StateInfo& _Info);

	void KnightFallStart(const StateInfo& _Info);
	void KnightFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFallEnd(const StateInfo& _Info);
}; 

