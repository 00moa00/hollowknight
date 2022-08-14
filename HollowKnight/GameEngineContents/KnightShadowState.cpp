#include "PreCompile.h"
#include "KnightShadow.h"



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

void KnightShadow::ShadowFlyStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("FLY_ANIMATION");
}

void KnightShadow::ShadowFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void KnightShadow::ShadowFlyEnd(const StateInfo& _Info)
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
