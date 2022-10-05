#include "PreCompile.h"
#include "Crawlid.h"
#include "KnightData.h"
#include "DropGeo.h"

Crawlid::Crawlid() 
	:
	isTurnEnd_(false),
	isDeathEnd_(false),

	CrawildKnockbackTimer_(0.0f),

	CrawlidManager_()
{
}

Crawlid::~Crawlid() 
{
}

void Crawlid::Start()
{
	SetName("Crawlid");

	CreateCollisionComponent(float4{ 100, 100, 1 }, static_cast<int>(COLLISION_ORDER::Monster));
	GetCollision()->GetTransform().SetWorldPosition({0, 50, 0});

	CreateWallCollisionComponent(float4{ 20, 20, 1 });

	CreateRendererComponent(float4{ 303, 177, 1 }, "Crawler_goomba_death0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	GetTransform().SetLocalPosition({ 4650,-4638, static_cast<float>(Z_ORDER::Monster) });
	GetRenderer()->ScaleToCutTexture(0);

	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Crawler_goomba_death0000-Sheet.png", 0, 4, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Crawler_goomba_turn_r_0000-Sheet.png", 0, 1, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_LEFT_ANIMATION", FrameAnimation_DESC("Crawler_goomba_turn0000-Sheet.png", 0, 1, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_ANIMATION", FrameAnimation_DESC("Crawler_goomba_walk0000-Sheet.png", 0, 3, 0.100f));
	
	GetRenderer()->ChangeFrameAnimation("WALK_ANIMATION");

	GetRenderer()->GetTransform().SetLocalPosition({0,-5.f});
	CrawlidManager_.CreateStateMember("WALK"
		, std::bind(&Crawlid::CrawlidWalkUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Crawlid::CrawlidWalkStart, this, std::placeholders::_1));

	CrawlidManager_.CreateStateMember("FALL"
		, std::bind(&Crawlid::CrawlidFallUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Crawlid::CrawlidFallStart, this, std::placeholders::_1)
		, std::bind(&Crawlid::CrawlidFallEnd, this, std::placeholders::_1));


	CrawlidManager_.CreateStateMember("TURN"
		, std::bind(&Crawlid::CrawlidTurnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Crawlid::CrawlidTurnStart, this, std::placeholders::_1)
		, std::bind(&Crawlid::CrawlidTurnEnd, this, std::placeholders::_1));

	CrawlidManager_.CreateStateMember("STUN"
		, std::bind(&Crawlid::CrawlidStunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Crawlid::CrawlidStunStart, this, std::placeholders::_1)
		, std::bind(&Crawlid::CrawlidStunEnd, this, std::placeholders::_1));
	
	CrawlidManager_.CreateStateMember("DEATH"
		, std::bind(&Crawlid::CrawlidDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Crawlid::CrawlidDeathStart, this, std::placeholders::_1)
		, std::bind(&Crawlid::CrawlidDeathEnd, this, std::placeholders::_1));


	CrawlidManager_.ChangeState("WALK");

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTurnEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTurnEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("TURN_LEFT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTurnEnd_ = true;

		});


	GetRenderer()->AnimationBindEnd("DEATH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDeathEnd_ = true;

		});

	SetFallSpeed(2);
	SetGravity(400.f);
	SetSpeed(100.f);
	SetHP(2);
	CreateMonsterHitParticle(2);
	CreateMonsterHitPuffParticle(2);
	CreateMonsterHitLight(2);
	CreateMonsterDeathPuffParticle();
	SetDropGeo(5);

	SetMoveDirection(float4::RIGHT);

}

void Crawlid::Update(float _DeltaTime)
{
	CrawlidManager_.Update(_DeltaTime);
}

void Crawlid::SetMonsterHit(int _Damage, float4 _StunDir, float4 _KnightDir)
{
	SubHP(_Damage);
	SetCreateMonsterHitParticleOn(_KnightDir, float4{ 280, 177});
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
	CrawlidManager_.ChangeState("STUN");


}




void Crawlid::CrawlidStillStart(const StateInfo& _Info)
{
}

void Crawlid::CrawlidStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Crawlid::CrawlidStillEnd(float _DeltaTime, const StateInfo& _Info)
{
}

void Crawlid::CrawlidWalkStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WALK_ANIMATION");
}

void Crawlid::CrawlidWalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SetMonsterDirection();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	// ======== Crawlid VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Crawlid::MonsterVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	if (GetisWall() == true || GetisOnGround() == false || GetisCollWall() == true)
	{

		if (GetMoveDirection().CompareInt2D(float4::LEFT))
		{
			GetRenderer()->ChangeFrameAnimation("TURN_RIGHT_ANIMATION");
			CrawlidManager_.ChangeState("TURN");
			return;

		}

		if (GetMoveDirection().CompareInt2D(float4::RIGHT))
		{
			GetRenderer()->ChangeFrameAnimation("TURN_LEFT_ANIMATION");
			CrawlidManager_.ChangeState("TURN");
			return;

		}
	}

	else
	{
		GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);
	}



	

}

void Crawlid::CrawlidWalkEnd(const StateInfo& _Info)
{
}

void Crawlid::CrawlidFallStart(const StateInfo& _Info)
{
	//GetRenderer()->ChangeFrameAnimation("TURN_WALK_ANIMATION");
}

void Crawlid::CrawlidFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove((float4::DOWN) * GetGravity() * GetFallSpeed() * _DeltaTime);
	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	if ( GetisOnGround() == true)
	{
		this->SetisGround(true);
		CrawlidManager_.ChangeState("WALK");
	}
}

void Crawlid::CrawlidFallEnd(const StateInfo& _Info)
{

}

void Crawlid::CrawlidTurnStart(const StateInfo& _Info)
{
	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		SetMoveDirection(float4::RIGHT);
	}

	else if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		SetMoveDirection(float4::LEFT);
	}
	SetMonsterDirection();
	GetTransform().SetWorldMove(GetMoveDirection() * 2 );

}

void Crawlid::CrawlidTurnUpdate(float _DeltaTime, const StateInfo& _Info)
{


	if (isTurnEnd_ == true)
	{
		isTurnEnd_ = false;
		CrawlidManager_.ChangeState("WALK");
	}
}

void Crawlid::CrawlidTurnEnd(const StateInfo& _Info)
{


}

void Crawlid::CrawlidStunUpdate(float _DeltaTime, const StateInfo& _Info)
{

	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	// ======== Knight VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Crawlid::MonsterVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}

	CrawildKnockbackTimer_ += _DeltaTime;

	if (CrawildKnockbackTimer_ > 0.2f)
	{
		CrawildKnockbackTimer_ = 0.f;
		if (GetisMonsterDeath() == true)
		{
			SetMonsterDeathPuffParticleOn();

			for (int i = 0; i < GetDropGeo(); ++i)
			{

				DropGeo* DropGeo_ = GetLevel()->CreateActor<DropGeo>();
				DropGeo_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,
					GetTransform().GetWorldPosition().y + 50.f });
			}

			CrawlidManager_.ChangeState("DEATH");
		}

		else
		{
			CrawlidManager_.ChangeState("WALK");

		}
	}
	if (GetisOnGround() == true && GetisCollWall() == false)
	{
		GetTransform().SetWorldMove(-GetMoveDirection() * (GetSpeed()*7) * _DeltaTime);
	}


}

void Crawlid::CrawlidStunEnd(const StateInfo& _Info)
{
}

void Crawlid::CrawlidDeathStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DEATH_ANIMATION");
	GetCollision()->Off();
}

void Crawlid::CrawlidDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//if (isDeathEnd_ == true)
	//{
	//	isDeathEnd_ = false;
	//	this->Death();

	//}
}

void Crawlid::CrawlidDeathEnd(const StateInfo& _Info)
{
}

bool Crawlid::MonsterVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Crawlid::CrawlidStunStart(const StateInfo& _Info)
{
}
