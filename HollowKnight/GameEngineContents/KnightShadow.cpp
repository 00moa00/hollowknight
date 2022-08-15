#include "PreCompile.h"
#include "KnightShadow.h"

KnightShadow::KnightShadow() 
	:
	isApearEnd_(false),
	isStartleEnd_(false),
	isDeathEnd_(false),
	isSlashEnd_(false),

	ShadowMoveTimer_(0),
	ShadowKnockbackTimer_(0),
	HP_(2),

	KnightShadowManager_()
{
}

KnightShadow::~KnightShadow() 
{
}

void KnightShadow::Start()
{

	SetSpeed(300.f);

	CreateCollisionComponent(float4{ 60, 120, 1 }, static_cast<int>(OBJECTORDER::Knight_Shadow));
	GetCollision()->GetTransform().SetWorldPosition({ 0, 120, 0 });

	CreateRendererComponent(float4{ 431, 287, 1 }, "Hollow Shade Cln_idle0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight_Shadow));

	GetTransform().SetWorldPosition({ 500,-4000, -1 });

	//================================
	//    Create Animation
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("APPEAR_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_appear0000-Sheet.png", 0, 29, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_idle0000-Sheet.png", 0, 11, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("STARTLE_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_startle0000-Sheet.png", 0, 6, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_death000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FLY_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_fly000-Sheet.png", 0, 4, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_slash000-Sheet.png", 0, 10, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("TURN_ANIMATION", FrameAnimation_DESC("Hollow Shade Cln_turn000-Sheet.png", 0, 3, 0.100f));
	
	GetRenderer()->ChangeFrameAnimation("APPEAR_ANIMATION");


	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isApearEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("STARTLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isStartleEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DEATH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDeathEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
		});

	//================================
	//    Create State
	//================================

	KnightShadowManager_.CreateStateMember("APPEAR"
		, std::bind(&KnightShadow::ShadowAppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowAppearStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowAppearEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("IDLE"
		, std::bind(&KnightShadow::ShadowIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowIdleStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowIdleEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("STARTLE"
		, std::bind(&KnightShadow::ShadowStartleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowStartleStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowStartleEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("DEATH"
		, std::bind(&KnightShadow::ShadowDeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowDeathStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowDeathEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("FLY"
		, std::bind(&KnightShadow::ShadowFlyUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowFlyStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowFlyEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("FREE_FLY"
		, std::bind(&KnightShadow::ShadowFreeFlyUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowFreeFlyStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowFreeFlyEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("SLASH"
		, std::bind(&KnightShadow::ShadowSlashUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowSlashStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowSlashEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("TURN"
		, std::bind(&KnightShadow::ShadowTurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowTurnStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowTurnEnd, this, std::placeholders::_1));

	KnightShadowManager_.CreateStateMember("HIT"
		, std::bind(&KnightShadow::ShadowHitUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&KnightShadow::ShadowHitStart, this, std::placeholders::_1),
		std::bind(&KnightShadow::ShadowHitEnd, this, std::placeholders::_1));

	KnightShadowManager_.ChangeState("APPEAR");

}

void KnightShadow::Update(float _DeltaTime)
{
	KnightShadowManager_.Update(_DeltaTime);
}
