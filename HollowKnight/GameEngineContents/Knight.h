#pragma once
#include "MasterActor.h"

// Ό³Έν :
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

	GameEngineStateManager KnightManager_;
	float GravityY;
	float4 JumpPower_;
	float4 Jumpping_;
	float4 FallDownDirection_;
	float4 CollisionSize_;
	float FallSpeed_;

private:
	//float4 
	//bool CheckMapCollision();

	bool GetPixelRed(float4 _NextDir);

	bool GetisPlayerMove();

	void KnightDirectionCheck();
	void KnightisOnGroundCheck(float _DeltaTime);

	float4 GetKnightNextPos(float4 _DeltaTime);

	void KnightStillStart( const StateInfo& _Info);
	void KnightStillUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightJumpStart(const StateInfo& _Info);
	void KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightJumpEnd(const StateInfo& _Info);

	void KnightFallStart(const StateInfo& _Info);
	void KnightFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFallEnd(const StateInfo& _Info);
}; 

