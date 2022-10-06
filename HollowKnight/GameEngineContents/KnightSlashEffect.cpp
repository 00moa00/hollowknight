#include "PreCompile.h"
#include "KnightSlashEffect.h"
#include "KnightData.h"
#include "Monster.h"
#include "HollowKnightLevel.h"
#include "MasterObject.h"
#include <GameEngineBase/GameEngineRandom.h>

KnightSlashEffect::KnightSlashEffect()
	:
	isSlashEnd_(false),
	isColl_(false),

	Dir_(float4::ZERO),

	KnightSlashAttackEffect_(nullptr)
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

	KnightSlashAttackEffect_ = GetLevel()->CreateActor<KnightSlashAttackEffect>();
	//KnightSlashAttackEffect_->SetParent(this);
	KnightSlashAttackEffect_->Off();

	GetRenderer()->AnimationBindEnd("SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
			GetRenderer()->ChangeFrameAnimation("STILL");
		});

	GetRenderer()->AnimationBindEnd("DOUBLE_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
			GetRenderer()->ChangeFrameAnimation("STILL");
		});

	GetRenderer()->AnimationBindEnd("UP_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
			GetRenderer()->ChangeFrameAnimation("STILL");
		});

	GetRenderer()->AnimationBindEnd("DOWN_SLASH", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
			GetRenderer()->ChangeFrameAnimation("STILL");
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
	
}

void KnightSlashEffect::SlashIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightSlashEffect::EffectVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

	GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Object, CollisionType::CT_OBB2D,
		std::bind(&KnightSlashEffect::EffectVSObjectCollision, this, std::placeholders::_1, std::placeholders::_2));


}

void KnightSlashEffect::SlashIdleEnd(const StateInfo& _Info)
{
}

void KnightSlashEffect::SlashHitEnemyStart(const StateInfo& _Info)
{
	isColl_ = true;

	GetCollision()->Off();
}

void KnightSlashEffect::SlashHitEnemyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSlashEnd_ == true)
	{
	//	isColl_ = false;

		isSlashEnd_ = false;
		KnightSlashEffectManager_.ChangeState("IDLE");
		return;
	}

	/*if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightSlashEffect::EffectVSWallFalseCheckCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{

	}
	else
	{
		isColl_ = false;
	}*/
}

void KnightSlashEffect::SlashHitEnemyEnd(const StateInfo& _Info)
{
	isColl_ = false;
}

void KnightSlashEffect::SetAnimationSlash()
{
	GetRenderer()->ChangeFrameAnimation("SLASH");
	KnightSlashEffectManager_.ChangeState("IDLE");
	Dir_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetMoveDirection();
	GetTransform().SetLocalPosition({ 0,-0 });

	int RamSound = GameEngineRandom::MainRandom.RandomInt(0,3);
	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("sword_1.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("sword_2.ogg");

	}

	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("sword_3.ogg");

	}

	else if (RamSound == 3)
	{
		GameEngineSound::SoundPlayOneShot("sword_4.ogg");
	}
}

void KnightSlashEffect::SetAnimationDoubleSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOUBLE_SLASH");
	KnightSlashEffectManager_.ChangeState("IDLE");
	Dir_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetMoveDirection();
	GetTransform().SetLocalPosition({ 0,-0 });

	int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 3);

	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("sword_1.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("sword_2.ogg");

	}

	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("sword_3.ogg");

	}

	else if (RamSound == 3)
	{
		GameEngineSound::SoundPlayOneShot("sword_4.ogg");
	}
}

void KnightSlashEffect::SetAnimationUpSlash()
{
	GetRenderer()->ChangeFrameAnimation("UP_SLASH");
	KnightSlashEffectManager_.ChangeState("IDLE");
	Dir_ = float4::UP;
	GetTransform().SetLocalPosition({ 0,-0 });

	int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 3);
	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("sword_1.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("sword_2.ogg");

	}

	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("sword_3.ogg");

	}

	else if (RamSound == 3)
	{
		GameEngineSound::SoundPlayOneShot("sword_4.ogg");
	}
}

void KnightSlashEffect::SetAnimationDownSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOWN_SLASH");
	KnightSlashEffectManager_.ChangeState("IDLE");
	Dir_ = float4::DOWN;
	GetTransform().SetLocalPosition({0,-80});

	int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 3);
	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("sword_1.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("sword_2.ogg");

	}

	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("sword_3.ogg");

	}

	else if (RamSound == 3)
	{
		GameEngineSound::SoundPlayOneShot("sword_4.ogg");
	}
}

void KnightSlashEffect::SetAnimationStill()
{
	GetRenderer()->ChangeFrameAnimation("STILL");
	KnightSlashEffectManager_.ChangeState("IDLE");
	GetTransform().SetLocalPosition({ 0,-0 });

}

bool KnightSlashEffect::EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		Monster* Monster_ = dynamic_cast<Monster*>(_Other->GetActor());
		Monster_->SetMonsterHit(KnightData::GetInst()->GetHitDamage(), GetEffectDirection(), Dir_);
		KnightData::GetInst()->SetisSoulGrow(true);
		KnightSlashAttackEffect_->EffectOn();

		if (Dir_.CompareInt2D(float4::RIGHT))
		{
			KnightSlashAttackEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x + 120.f,
			GetTransform().GetWorldPosition().y - 50.f  , static_cast<float>(Z_ORDER::Effect) });
		}
		if (Dir_.CompareInt2D(float4::LEFT))
		{
			KnightSlashAttackEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x - 120.f,
			GetTransform().GetWorldPosition().y - 50.f  , static_cast<float>(Z_ORDER::Effect) });
		}

		if (Dir_.CompareInt2D(float4::DOWN))
		{
			KnightSlashAttackEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,
			GetTransform().GetWorldPosition().y - 50.f  , static_cast<float>(Z_ORDER::Effect) });
		}

		if (Dir_.CompareInt2D(float4::UP))
		{
			KnightSlashAttackEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,
			GetTransform().GetWorldPosition().y + 50.f  , static_cast<float>(Z_ORDER::Effect) });
		}



		isColl_ = true;
		KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

		return true;
	}
	else
	{
		return false;
	}

}

bool KnightSlashEffect::EffectVSObjectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	isColl_ = true;
	MasterObject* MasterObject_ = dynamic_cast<MasterObject*>(_Other->GetActor());
	if (MasterObject_ != nullptr)
	{
		MasterObject_->SetHitCollision();

	}
	KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

	return true;
}

bool KnightSlashEffect::EffectVSWallFalseCheckCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

