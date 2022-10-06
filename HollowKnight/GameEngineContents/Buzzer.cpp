#include "PreCompile.h"
#include "Buzzer.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "DropGeo.h"

Buzzer::Buzzer() 
	:
	isTurnEnd_(false),
	isDeathEnd_(false),
	isStartleEnd_(false),


	BuzzerKnockbackTimer_(0.f),
	BuzzerFreeFlyTimer_(0.f)
{
}

Buzzer::~Buzzer() 
{
}

void Buzzer::Start()
{
	SetName("Buzzer");

	CreateCollisionComponent(float4{ 110, 80, 1 }, static_cast<int>(COLLISION_ORDER::Monster));
	GetCollision()->GetTransform().SetWorldPosition({ 0, 0, 0 });

	CreateWallCollisionComponent(float4{ 20, 20, 1 });

	CreateRendererComponent(float4{ 188, 177, 1 }, "Crawler_goomba_death0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	GetRenderer()->GetTransform().SetLocalPosition({ 0,-60.f });

	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Buzzer_idle_01-Sheet.png", 0, 2, 0.080f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("STATLE_ANIMATION", FrameAnimation_DESC("Buzzer_startle_01-Sheet.png", 0, 3, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FLY_ANIMATION", FrameAnimation_DESC("Buzzer_fly0000-Sheet.png", 0, 3, 0.080f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Buzzer_death0000-Sheet.png", 0, 2, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_ANIMATION", FrameAnimation_DESC("Buzzer_turn001-Sheet.png", 0, 1, 0.080f, false));
	
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("STATLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isStartleEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("TURN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTurnEnd_ = true;
		});


	BuzzerManager_.CreateStateMember("IDLE"
		, std::bind(&Buzzer::BuzzerIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerIdleStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerIdleEnd, this, std::placeholders::_1));


	BuzzerManager_.CreateStateMember("STATLE"
		, std::bind(&Buzzer::BuzzerStatleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerStatleStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerStatleEnd, this, std::placeholders::_1));

	BuzzerManager_.CreateStateMember("DEATH"
		, std::bind(&Buzzer::BuzzerDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerDeathStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerDeathEnd, this, std::placeholders::_1));

	BuzzerManager_.CreateStateMember("FLY"
		, std::bind(&Buzzer::BuzzerFlyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerFlyStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerFlyEnd, this, std::placeholders::_1));

	BuzzerManager_.CreateStateMember("FREE_FLY"
		, std::bind(&Buzzer::BuzzerFreeFlyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerFreeFlyStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerFreeFlyEnd, this, std::placeholders::_1));

	BuzzerManager_.CreateStateMember("STUN"
		, std::bind(&Buzzer::BuzzerHitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerHitStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerHitEnd, this, std::placeholders::_1));

	BuzzerManager_.CreateStateMember("TURN"
		, std::bind(&Buzzer::BuzzerTurnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Buzzer::BuzzerTurnStart, this, std::placeholders::_1)
		, std::bind(&Buzzer::BuzzerTurnEnd, this, std::placeholders::_1));

	BuzzerManager_.ChangeState("IDLE");

	SetSpeed(400.f);
	SetHP(3);
	CreateMonsterHitParticle(3);
	CreateMonsterHitPuffParticle(3);
	CreateMonsterHitLight(3);
	CreateMonsterDeathPuffParticle();
	SetDropGeo(5);

	SetMoveDirection(float4::RIGHT);
}

void Buzzer::Update(float _DeltaTime)
{
	BuzzerManager_.Update(_DeltaTime);
}


void Buzzer::DirectionCheck()
{
	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 Dir = KnightPos - this->GetTransform().GetWorldPosition();
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

void Buzzer::SetMonsterHit(int _Damage, float4 _StunDir, float4 _KnightDir)
{
	SubHP(_Damage);
	SetCreateMonsterHitParticleOn(_KnightDir, float4{ 280, 177 });
	SetCreateMonsterHitPuffParticleOn(_KnightDir, float4{ 280, 177 });
	SetMonsterHitLightOn();

	if (_StunDir.CompareInt2D(float4::RIGHT))
	{
		SetMoveDirection(float4::LEFT);

	}
	else
	{
		SetMoveDirection(float4::RIGHT);
	}

	SetMonsterDirection();
	KnightData::GetInst()->SetisSoulGrow(true);
	BuzzerManager_.ChangeState("STUN");
}



void Buzzer::BuzzerStatleStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STATLE_ANIMATION");
}

void Buzzer::BuzzerStatleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isStartleEnd_ == true)
	{
		isStartleEnd_ = false;
		BuzzerManager_.ChangeState("FLY");
	}
}

void Buzzer::BuzzerStatleEnd(const StateInfo& _Info)
{
}

void Buzzer::BuzzerIdleStart(const StateInfo& _Info)
{
}

void Buzzer::BuzzerIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	float4 Lenth = KnightPos - this->GetTransform().GetWorldPosition();
	float LenthAbs = Lenth.Length();

	if (LenthAbs < 400.f)
	{
		BuzzerManager_.ChangeState("STATLE");
	}
}

void Buzzer::BuzzerIdleEnd(const StateInfo& _Info)
{
}

void Buzzer::BuzzerFlyStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("FLY_ANIMATION");

}

void Buzzer::BuzzerFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DirectionCheck();
	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	float4 Dir = KnightPos - this->GetTransform().GetWorldPosition();
	Dir.Normalize();
	SetMoveDirection(Dir);

	GetTransform().SetWorldMove(Dir * GetSpeed() * _DeltaTime);


	// 플레이어하고 닿으면 FreeFly
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Buzzer::ThisVSKnihgtCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		BuzzerManager_.ChangeState("FREE_FLY");
	}

}

void Buzzer::BuzzerFlyEnd(const StateInfo& _Info)
{
}

void Buzzer::BuzzerFreeFlyStart(const StateInfo& _Info)
{
	BuzzerFreeFlyTimer_ = 0.f;
}

void Buzzer::BuzzerFreeFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{


	GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);


	BuzzerFreeFlyTimer_ += _DeltaTime;

	if (BuzzerFreeFlyTimer_ > 0.5f)
	{
		BuzzerFreeFlyTimer_ = 0.f;
		BuzzerManager_.ChangeState("FLY");

	}

}

void Buzzer::BuzzerFreeFlyEnd(const StateInfo& _Info)
{
}

void Buzzer::BuzzerHitStart(const StateInfo& _Info)
{
}

void Buzzer::BuzzerHitUpdate(float _DeltaTime, const StateInfo& _Info)
{

	BuzzerKnockbackTimer_ += _DeltaTime;

	if (BuzzerKnockbackTimer_ > 0.1f)
	{
		BuzzerKnockbackTimer_ = 0.f;
		if (GetisMonsterDeath() == true)
		{
			SetMonsterDeathPuffParticleOn();

			for (int i = 0; i < GetDropGeo(); ++i)
			{
				DropGeo* DropGeo_ = GetLevel()->CreateActor<DropGeo>();
				DropGeo_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,
					GetTransform().GetWorldPosition().y + 50.f });
			}

			BuzzerManager_.ChangeState("DEATH");
		}

		else
		{
			BuzzerManager_.ChangeState("FLY");
		}
	}

	GetTransform().SetWorldMove(-GetMoveDirection() * (GetSpeed() * 7) * _DeltaTime);
}

void Buzzer::BuzzerHitEnd(const StateInfo& _Info)
{
}

void Buzzer::BuzzerTurnStart(const StateInfo& _Info)
{
}

void Buzzer::BuzzerTurnUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Buzzer::BuzzerTurnEnd(const StateInfo& _Info)
{
}

bool Buzzer::ThisVSKnihgtCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}



void Buzzer::BuzzerDeathStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DEATH_ANIMATION");
	GetCollision()->Off();

}

void Buzzer::BuzzerDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->isPixelCheck(_DeltaTime, float4::DOWN);
	if (GetisOnGround() == false)
	{
		GetTransform().SetWorldMove(float4::DOWN * GetSpeed() * _DeltaTime);

	}
}

void Buzzer::BuzzerDeathEnd(const StateInfo& _Info)
{
}
