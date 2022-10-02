#include "PreCompile.h"
#include "KnightCast.h"
#include "KnightData.h"
#include "Monster.h"
#include "KnightCastImpactEffect.h"

KnightCast::KnightCast() 
	:
	Dir_(float4::ZERO),
	CastImPactRenderer_(nullptr)
{
}

KnightCast::~KnightCast() 
{
}

void KnightCast::Start()
{
	CreateCollisionComponent(float4{ 180.f, 123.f, 1 }, static_cast<int>(COLLISION_ORDER::Knight_Slash));
	CreateRendererComponent("Spell Effects_fireball_v020000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({317.f * 3.0f, 143.f * 3.0f });
		
	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects_fireball_v020000-Sheet.png", 0, 9, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_fireball_v020000-Sheet.png", 9, 9, 0.100f, false));

	//GetRenderer()->SetScaleModeImage();

	SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	Off();
	//etRenderer()->GetTransform().SetWorldPosition({ 0, 186 / 2, 0 });
}

void KnightCast::Update(float _DeltaTime)
{
	float4 Move = Dir_ * 2000.f * _DeltaTime;


	GetTransform().SetLocalMove(Move);

	GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightCast::EffectVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

	if (GetAccTime() > 1.5f)
	{
		Off();
	}
}

void KnightCast::EffectOn(float4 _Dir)
{
	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	Dir_ = _Dir;
	if (_Dir.x <= 0.f)
	{
		//	GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	if (_Dir.x >= 0.f)
	{
		//GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });
		GetRenderer()->GetTransform().PixLocalPositiveX();

	}

	GetTransform().SetLocalPosition({ 0, 0, 0 });
	On();
	GetCollision()->On();

	ReSetAccTime();
}

bool KnightCast::EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		Monster* Monster_ = dynamic_cast<Monster*>(_Other->GetActor());
		Monster_->SetMonsterHit(KnightData::GetInst()->GetHitDamage() * 2, GetEffectDirection(), Dir_);

		//KnightData::GetInst()->SetisSoulGrow(true);

		KnightCastImpactEffect* KnightCastImpactEffect_ = GetLevel()->CreateActor<KnightCastImpactEffect>();
		KnightCastImpactEffect_->SetDirScaleX(Dir_);

		KnightCastImpactEffect_->GetTransform().SetWorldPosition({ Monster_-> GetTransform().GetLocalPosition().x,
			Monster_->GetTransform().GetLocalPosition().y,
			static_cast<float>(Z_ORDER::Effect)});

		//KnightCastImpactEffect_->SetParent(this);

		//Off();
		GetRenderer()->ChangeFrameAnimation("IDLE");
		GetCollision()->Off();

		return true;
	}
	else
	{
		return false;
	}


	//return true;
}

