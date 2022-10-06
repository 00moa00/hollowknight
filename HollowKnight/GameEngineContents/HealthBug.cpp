#include "PreCompile.h"
#include "HealthBug.h"

HealthBug::HealthBug() 
	:
	HitCount_(0)
{
}

HealthBug::~HealthBug() 
{
}

void HealthBug::Start()
{
	CreateRendererComponent({ 285, 506, 1 }, "Health Bugs_health_cocoon_top0000-Sheet.png");
	CreateCollisionComponent({ 258, 506, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Health Bugs_health_cocoon_top0000-Sheet.png", 0, 22, 0.120f));

	GetCollision()->GetTransform().SetLocalPosition({ 0,252 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,252 / 2 });

	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	HitCount_ = 5;
}

void HealthBug::Update(float _DeltaTime)
{
}

void HealthBug::SetHitCollision()
{
	int a = 0;
}

