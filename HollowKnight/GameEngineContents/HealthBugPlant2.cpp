#include "PreCompile.h"
#include "HealthBugPlant2.h"
#include "KnightData.h"

HealthBugPlant2::HealthBugPlant2() 
{
}

HealthBugPlant2::~HealthBugPlant2() 
{
}

void HealthBugPlant2::Start()
{
	CreateRendererComponent({ 223  , 331 , 1 }, "Health Bugs_health_plant_020007-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Health Bugs_health_plant_020007-Sheet.png", 0, 15, 0.120f));

	//GetCollision()->GetTransform().SetLocalPosition({ 0,331 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,331 / 2 });

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
}

void HealthBugPlant2::Update(float _DeltaTime)
{
}

void HealthBugPlant2::SetKnightCollision()
{

}

void HealthBugPlant2::SetScaleXNegative()
{
	GetRenderer()->GetTransform().PixLocalNegativeX();
}
