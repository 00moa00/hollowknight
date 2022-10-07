#include "PreCompile.h"
#include "HealthBug.h"
#include "KnightData.h"
#include "KnightHatchlingBurst.h"
#include "HollowKnightLevel.h"

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
	CreateRendererComponent({ 285 * 1.6f , 506 * 1.6f , 1 }, "Health Bugs_health_cocoon_top0000-Sheet.png");
	CreateCollisionComponent({ 258 * 1.3f ,200.f , 1 }, static_cast<int>(COLLISION_ORDER::Object));

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Health Bugs_health_cocoon_top0000-Sheet.png", 0, 22, 0.120f));

	GetCollision()->GetTransform().SetLocalPosition({ 0,506 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,506 / 2 });

	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	HitCount_ = 5;
}

void HealthBug::Update(float _DeltaTime)
{
}

void HealthBug::SetHitCollision()
{
	KnightData::GetInst()->SetisSoulGrow(true);
	//GetLevel<HollowKnightLevel>()->GetKnight()->SethatchlingEffectOn();
	//KnightHatchlingBurst* KnightHatchlingBurst_->EffectOn();
	//KnightHatchlingBurst_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x,  this->GetTransform().GetWorldPosition().y, -150.f });
}

