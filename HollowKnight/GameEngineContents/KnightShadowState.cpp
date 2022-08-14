#include "PreCompile.h"
#include "KnightShadow.h"
#include "KnightShadowData.h"

void KnightShadow::ShadowDirectionCheck()
{
	float4 Dir = KnightShadowData::GetInst()->GetKnightPosition() - this->GetTransform().GetWorldPosition();
	Dir.Normalize();

	if (Dir.x > 0.0f)
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	else
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();

	}
}

void KnightShadow::ShadowAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("APPEAR_ANIMATION");
}

void KnightShadow::ShadowAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isApearEnd_ == true)
	{
		isApearEnd_ = false;
		KnightShadowManager_.ChangeState("IDLE");
	}
}

void KnightShadow::ShadowAppearEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowIdleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
}

void KnightShadow::ShadowIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Lenth = KnightShadowData::GetInst()->GetKnightPosition() - this->GetTransform().GetWorldPosition();
	float LenthAbs = Lenth.Length();

	if (LenthAbs < 400.f)
	{
		KnightShadowManager_.ChangeState("STARTLE");
	}



}

void KnightShadow::ShadowIdleEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowStartleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STARTLE_ANIMATION");

}

void KnightShadow::ShadowStartleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isStartleEnd_ == true)
	{
		isStartleEnd_ = false;
		KnightShadowManager_.ChangeState("FLY");
	}
}

void KnightShadow::ShadowStartleEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowFlyStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("FLY_ANIMATION");
}

void KnightShadow::ShadowFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ShadowDirectionCheck();
	float4 Dir = KnightShadowData::GetInst()->GetKnightPosition() - this->GetTransform().GetWorldPosition();
	Dir.Normalize();
	SetMoveDirection(Dir);

	GetTransform().SetWorldMove(Dir * GetSpeed() * _DeltaTime);


	// 플레이어하고 닿으면 FreeFly
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&KnightShadow::ShadowVSKnihgtCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		KnightShadowManager_.ChangeState("FREE_FLY");
	}

}

void KnightShadow::ShadowFlyEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowFreeFlyStart(const StateInfo& _Info)
{
}

void KnightShadow::ShadowFreeFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);


	MoveKnihgtTimer_ += _DeltaTime;

	if (MoveKnihgtTimer_ > 0.5f)
	{
		MoveKnihgtTimer_ = 0.f;
		KnightShadowManager_.ChangeState("FLY");

	}

}

void KnightShadow::ShadowFreeFlyEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SLASH_ANIMATION");

}

void KnightShadow::ShadowSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void KnightShadow::ShadowSlashEnd(const StateInfo& _Info)
{
}

void KnightShadow::ShadowTurnStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TURN_ANIMATION");
}

void KnightShadow::ShadowTurnUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void KnightShadow::ShadowTurnEnd(const StateInfo& _Info)
{
}

bool KnightShadow::ShadowVSKnihgtCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void KnightShadow::ShadowDeathStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DEATH_ANIMATION");

}

void KnightShadow::ShadowDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isDeathEnd_ == true)
	{
		isDeathEnd_ = false;
		this->Death();
	}
}

void KnightShadow::ShadowDeathEnd(const StateInfo& _Info)
{
}
