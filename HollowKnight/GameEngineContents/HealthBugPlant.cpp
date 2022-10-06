#include "PreCompile.h"
#include "HealthBugPlant.h"

HealthBugPlant::HealthBugPlant() 
{
}

HealthBugPlant::~HealthBugPlant() 
{
}

void HealthBugPlant::Start()
{
	CreateRendererComponent({ 223  , 331 , 1 }, "Health Bugs_health_cocoon_top0000-Sheet.png");
	//CreateCollisionComponent({ 223  , 331 , 1 }, static_cast<int>(COLLISION_ORDER::NotAttack_Object));

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Health Bugs_health_plant_010013-Sheet.png", 0, 4, 0.120f));

	//GetCollision()->GetTransform().SetLocalPosition({ 0,331 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,331 / 2 });

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
}

void HealthBugPlant::Update(float _DeltaTime)
{
}

void HealthBugPlant::SetKnightCollision()
{
}

void HealthBugPlant::SetScaleXNegative()
{
	GetRenderer()->GetTransform().PixLocalNegativeX();
}
