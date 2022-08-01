#include "PreCompile.h"
#include "Knight.h"

void Knight::KnightStillStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
}

void Knight::KnightStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetisKnightMove() == true)
	{
		KnightManager_.ChangeState("WALK");
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isJumpping_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") && isJumpping_ == true)
	{
		isJumpping_ = false;
	}

	if (GetisOnGround() == false)
	{
		KnightManager_.ChangeState("FALL");
	}

}

void Knight::KnightWalkStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WALK_ANIMATION");
}

void Knight::KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->KnightDirectionCheck();
	this->KnightisOnGroundCheck(_DeltaTime);

	if (GetisOnGround() == true)
	{
		GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);

	}

	else
	{
		KnightManager_.ChangeState("FALL");
	}


	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isJumpping_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") && isJumpping_ == true)
	{
		isJumpping_ = false;
	}


	if (GetisKnightMove() == false)
	{
		KnightManager_.ChangeState("STILL");

	}

}


void Knight::KnightJumpStart(const StateInfo& _Info)
{
	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;
	isJumpping_ = true;

	GetRenderer()->ChangeFrameAnimation("JUMP_ANIMATION");
	SetJumpPower({ 0, 250, 0 });
}

void Knight::KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();
		ActtingMoveDirection_.Normalize();
		//KnightDirectionCheck();
		SubJumpPower((float4::UP + -ActtingMoveDirection_ / 2) * GetGravity() * _DeltaTime);

		GetTransform().SetWorldMove(GetJumpPower() * GetJumpSpeed() * _DeltaTime);

		if (GetJumpPower().y <= 0.f)
		{
			KnightManager_.ChangeState("FALL");
		}
	}

	else
	{
		KnightManager_.ChangeState("FALL");
	}


	if (GetPixelRed(GetKnightNextPos(_DeltaTime)) == true)
	{
		KnightManager_.ChangeState("FALL");

	}
}

void Knight::KnightJumpEnd(const StateInfo& _Info)
{
	this->SetisGround(false);
}

// ³«ÇÏ
void Knight::KnightFallStart(const StateInfo& _Info)
{
	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;

	GetRenderer()->ChangeFrameAnimation("FAll_ANIMATION");
}

void Knight::KnightFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	isKnihgtActtingMoveChack();
	KnightActtingDirectionCheck();
	KnightIsActtingCheck();
	ActtingMoveDirection_.Normalize();

	GetTransform().SetWorldMove((GetFallDownDirection() + ActtingMoveDirection_ / 2) * GetGravity() * GetFallSpeed() * _DeltaTime);

	if (GetPixelRed(GetKnightNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightFallEnd(const StateInfo& _Info)
{
	if (isKnightActtingMove_ == true)
	{
		SetMoveDirection(ActtingMoveDirection_);
	}
}

