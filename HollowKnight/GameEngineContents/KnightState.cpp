#include "PreCompile.h"
#include "Knight.h"

void Knight::KnightStillStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
}

void Knight::KnightStillUpdate(float _DeltaTime, const StateInfo& _Info)
{

	//this->isWallCheck(_DeltaTime);

	//if (GetisWall() == true)
	//{
	//	SetMoveDirection(float4::ZERO);
	//	GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);

	//}

 	if (GetisKnightMove() == true)
	{
		KnightManager_.ChangeState("WALK");
	}

	if (GetisOnGround() == false)
	{
		KnightManager_.ChangeState("FALL");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") && isPressJumppingKey_ == true)
	{
		isPressJumppingKey_ = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash"))
	{
		KnightManager_.ChangeState("SLASH");
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
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}

		//if (GetMoveDirection().CompareInt2D(float4::RIGHT) || GetMoveDirection().CompareInt2D(float4::LEFT))
		//{
		//	GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);
		//}

		//else
		//{
		//	SetMoveDirection(float4::ZERO);
		//	GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//}
	}


	else
	{
		KnightManager_.ChangeState("FALL");
	}



	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") )
	{
		isPressJumppingKey_ = false;
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
	isPressJumppingKey_ = true;

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

	if (GetPixelRed(GetNextPos(_DeltaTime)) == true || GetPixelBlue(GetNextPos(_DeltaTime)) == true)
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

void Knight::KnightSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SLASH_ANIMATION");
	KnightSlashEffect_->SetAnimationSlash();
}

void Knight::KnightSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());

	if (isSlashEnd_ == true)
	{
		isSlashEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}

}

void Knight::KnightSlashEnd(const StateInfo& _Info)
{
}

void Knight::KnightDoubleSlashStart(const StateInfo& _Info)
{
}

void Knight::KnightDoubleSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightDoubleSlashEnd(const StateInfo& _Info)
{
}

void Knight::KnightUpSlashStart(const StateInfo& _Info)
{
}

void Knight::KnightUpSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightUpSlashEnd(const StateInfo& _Info)
{
}

void Knight::KnightDownSlashStart(const StateInfo& _Info)
{
}

void Knight::KnightDownSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightDownSlashEnd(const StateInfo& _Info)
{
}

