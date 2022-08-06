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

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") && isJumpping_ == true)
	{
		isJumpping_ = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightJump") && isJumpping_ == false)
	{
		KnightManager_.ChangeState("JUMP");
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
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);

	}
	else if (GetisOnGround() == true)
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

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") )
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
	GetRenderer()->ChangeFrameAnimation("JUMP_ANIMATION");

	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;
	isJumpping_ = true;

	SetJumpPower({ 0, KnightJumpPower_, 0 });
}

void Knight::KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		SubJumpPower((float4::UP + -ActtingMoveDirection_ / 2) * GetGravity() * _DeltaTime);

		GetTransform().SetWorldMove(GetJumpPower() * GetJumpSpeed() * _DeltaTime);

		if (GetJumpPower().y <= 0.f)
		{
			KnightManager_.ChangeState("FALL");
		}
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		KnightManager_.ChangeState("FALL");
	}


	//if (GetPixelRed(GetNextPos(_DeltaTime)) == true)
	//{
	//	KnightManager_.ChangeState("FALL");

	//}
}

void Knight::KnightJumpEnd(const StateInfo& _Info)
{
	SetJumpPower({ 0, KnightJumpPower_, 0 });

	this->SetisGround(false);
}



void Knight::KnightDoubleJumpStart(const StateInfo& _Info)
{
	GetRenderer()->GetTransform().SetLocalScale({ 503,300,1 });
	GetRenderer()->ChangeFrameAnimation("DOUBLE_JUMP_ANIMATION");

	SetJumpPower({ 0, KnightDoubleJumpPower_, 0 });
}

void Knight::KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		ActtingMoveDirection_.Normalize();
		SubJumpPower((float4::UP + -ActtingMoveDirection_ / 2) * GetGravity() * _DeltaTime);

		GetTransform().SetWorldMove(GetJumpPower() * GetJumpSpeed() * _DeltaTime);


		if (GetJumpPower().y <= 0.f)
		{
			KnightManager_.ChangeState("FALL");
		}
	}
	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		KnightManager_.ChangeState("FALL");
	}


}

void Knight::KnightDoubleJumpEnd(const StateInfo& _Info)
{
	GetRenderer()->GetTransform().SetLocalScale({ 349, 186, 1 });

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

	if (GetPixelRed(GetNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
		KnightManager_.ChangeState("STILL");
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightJump"))
	{
		KnightManager_.ChangeState("DOUBLE_JUMP");
	}
}

void Knight::KnightFallEnd(const StateInfo& _Info)
{
	if (isKnightActtingMove_ == true)
	{
		SetMoveDirection(ActtingMoveDirection_);
	}
}

