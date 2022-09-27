#include "PreCompile.h"
#include "BossRoarEffect.h"
#include "BossRoarRingEffect.h"

BossRoarEffect::BossRoarEffect() 
	:
	AddScale_(),

	Alpha_(1.0f),
	CreateTimer_(0.0f),

	RoarLineRenderer(nullptr)
{
}

BossRoarEffect::~BossRoarEffect() 
{
}

void BossRoarEffect::Start()
{
	BossRoarRingEffect* BossRoarRingEffect_ = GetLevel()->CreateActor<BossRoarRingEffect>();
	BossRoarRingEffect_->SetParent(this);

	RoarLineRenderer = CreateComponent<GameEngineTextureRenderer>();
	RoarLineRenderer->SetTexture("Roar_lines_white.png");
	RoarLineRenderer->GetTransform().SetLocalScale({ 294.f * 0.8f, 283.f * 0.8f });
}

void BossRoarEffect::Update(float _DeltaTime)
{

	AddScale_ += 80.f * _DeltaTime;
	Alpha_ -= 1.4f * _DeltaTime;
	RoarLineRenderer->GetTransform().SetWorldScale({ RoarLineRenderer->GetTransform().GetWorldScale().x + AddScale_.x, RoarLineRenderer->GetTransform().GetWorldScale().y + AddScale_.y });
	RoarLineRenderer->GetPixelData().MulColor.a = Alpha_;



	CreateTimer_ += _DeltaTime;
	if (CreateTimer_ > 0.2f)
	{
		CreateTimer_ = 0.0f;
		BossRoarRingEffect* BossRoarRingEffect_ = GetLevel()->CreateActor<BossRoarRingEffect>();
		BossRoarRingEffect_->SetParent(this);
	}

	if (GetAccTime() > 1.f)
	{
		this->Death();
	}
}

