#include "PreCompile.h"
#include "KnightSlashEffect.h"
#include "KnightData.h"

KnightSlashEffect::KnightSlashEffect() 
	:
	isSlashEnd_(false)
{
}

KnightSlashEffect::~KnightSlashEffect() 
{
}

void KnightSlashEffect::Start()
{
	SetName("KnightSlashEffect");

	CreateCollisionComponent(float4{ 140, 120, 1 }, static_cast<int>(COLLISION_ORDER::Knight_Slash));
	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_double_slashes_effect-Sheet.png", 2, static_cast<int>(RENDERORDER::Knight));
	
	//GetRenderer()->GetTransform().SetLocalPosition({0,0,static_cast<float>(Z_ORDER::Knight_Slash) });
	GetRenderer()->SetScaleModeImage();

	GetRenderer()->CreateFrameAnimationCutTexture("STILL", FrameAnimation_DESC("Knight_double_slashes_effect-Sheet.png", 2, 2, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH", FrameAnimation_DESC("Knight_slashes_effect0001-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_SLASH", FrameAnimation_DESC("Knight_double_slashes_effect-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("UP_SLASH", FrameAnimation_DESC("Knight_up_slash_effect0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOWN_SLASH", FrameAnimation_DESC("Knight_down_slash_effect0001-Sheet.png", 0, 1, 0.100f, false));

	GetRenderer()->ChangeFrameAnimation("STILL");



	GetRenderer()->AnimationBindEnd("SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DOUBLE_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("UP_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("DOWN_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;

		});

	//================================
	//    Create State
	//================================
	KnightSlashEffectManager_.CreateStateMember("IDLE",
		std::bind(&KnightSlashEffect::SlashIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightSlashEffect::SlashIdleStart, this, std::placeholders::_1),
		std::bind(&KnightSlashEffect::SlashIdleEnd, this, std::placeholders::_1));

	KnightSlashEffectManager_.CreateStateMember("HIT_ENEMY",
		std::bind(&KnightSlashEffect::SlashHitEnemyUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightSlashEffect::SlashHitEnemyStart, this, std::placeholders::_1),
		std::bind(&KnightSlashEffect::SlashHitEnemyEnd, this, std::placeholders::_1));


	KnightSlashEffectManager_.ChangeState("IDLE");


}

void KnightSlashEffect::Update(float _DeltaTime)
{

	KnightSlashEffectManager_.Update(_DeltaTime);

}

void KnightSlashEffect::SlashIdleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL");

}

void KnightSlashEffect::SlashIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightSlashEffect::EffectVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void KnightSlashEffect::SlashIdleEnd(const StateInfo& _Info)
{
}

void KnightSlashEffect::SlashHitEnemyStart(const StateInfo& _Info)
{

}

void KnightSlashEffect::SlashHitEnemyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSlashEnd_ == true)
	{
		isSlashEnd_ = false;
		KnightSlashEffectManager_.ChangeState("IDLE");
	}

}

void KnightSlashEffect::SlashHitEnemyEnd(const StateInfo& _Info)
{
}

void KnightSlashEffect::SetAnimationSlash()
{
	GetRenderer()->ChangeFrameAnimation("SLASH");
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

}

void KnightSlashEffect::SetAnimationDoubleSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOUBLE_SLASH");
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

}

void KnightSlashEffect::SetAnimationUpSlash()
{
	GetRenderer()->ChangeFrameAnimation("UP_SLASH");
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

}

void KnightSlashEffect::SetAnimationDownSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOWN_SLASH");
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

}

void KnightSlashEffect::SetAnimationStill()
{
	GetRenderer()->ChangeFrameAnimation("STILL");
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

}

bool KnightSlashEffect::EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		KnightData::GetInst()->SetisSoulGrow(true);
		//_Other->GetActor()->Death();
		KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

		return true;
	}

}

