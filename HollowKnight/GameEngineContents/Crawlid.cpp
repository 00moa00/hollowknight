#include "PreCompile.h"
#include "Crawlid.h"

Crawlid::Crawlid() 
	:
	CrawlidManager_()
{
}

Crawlid::~Crawlid() 
{
}

void Crawlid::Start()
{
	SetName("Crawlid");

	SetMoveDirection(float4::ZERO);

	CreateCollisionComponent(float4{ 100, 100, 10000 }, static_cast<int>(OBJECTORDER::Monster));
	GetCollision()->GetTransform().SetWorldPosition({0, 50, 0});

	CreateRendererComponent(float4{ 303, 177, 1 }, "Crawler_goomba_death0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	GetTransform().SetLocalPosition({ 700,-4000, -static_cast<float>(Z_ORDER::Monster) });

	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Crawler_goomba_death0000-Sheet.png", 0, 4, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Crawler_goomba_turn_r_0000-Sheet.png", 0, 1, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_LEFT_ANIMATION", FrameAnimation_DESC("Crawler_goomba_turn0000-Sheet.png", 0, 1, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_WALK_ANIMATION", FrameAnimation_DESC("Crawler_goomba_walk0000-Sheet.png", 0, 3, 0.100f));
	
	GetRenderer()->ChangeFrameAnimation("TURN_WALK_ANIMATION");


	CrawlidManager_.CreateStateMember("WALK"
		, std::bind(&Crawlid::CrawlidWalkUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Crawlid::CrawlidWalkStart, this, std::placeholders::_1));

	CrawlidManager_.CreateStateMember("FALL"
		, std::bind(&Crawlid::CrawlidFallUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Crawlid::CrawlidFallStart, this, std::placeholders::_1), std::bind(&Crawlid::CrawlidFallEnd, this, std::placeholders::_1));

	CrawlidManager_.ChangeState("WALK");

	SetallDownDirection({ 0, -1, 0 });
	SetFallSpeed(2);
	SetGravity(400.f);
	SetSpeed(300.f);

	SetMoveDirection(float4::RIGHT);

}

void Crawlid::Update(float _DeltaTime)
{
	CrawlidManager_.Update(_DeltaTime);
}



void Crawlid::CrawlidWalkStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TURN_WALK_ANIMATION");
}

void Crawlid::CrawlidWalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
	}

	else if (GetisOnGround() == true)
	{
		//GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);
	}

	else
	{
		CrawlidManager_.ChangeState("FALL");
	}

}

void Crawlid::CrawlidFallStart(const StateInfo& _Info)
{
	//GetRenderer()->ChangeFrameAnimation("TURN_WALK_ANIMATION");
}

void Crawlid::CrawlidFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove((GetFallDownDirection()) * GetGravity() * GetFallSpeed() * _DeltaTime);

	if (GetPixelRed(GetNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
		CrawlidManager_.ChangeState("WALK");
	}
}

void Crawlid::CrawlidFallEnd(const StateInfo& _Info)
{

}
