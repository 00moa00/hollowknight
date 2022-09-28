#include "PreCompile.h"
#include "BossRoarRingEffect.h"

BossRoarRingEffect::BossRoarRingEffect() 
	:
	Alpha_(1.0f),

	RoarRingRenderer_(nullptr)
{
}

BossRoarRingEffect::~BossRoarRingEffect() 
{
}

void BossRoarRingEffect::Start()
{
	RoarRingRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	RoarRingRenderer_->SetTexture("roar_effect.png");
	RoarRingRenderer_->GetTransform().SetLocalScale({ 250 * 0.8, 245 * 0.8 });
	//RoarRingRenderer_->SetPivot(PIVOTMODE::CUSTOM);
	//RoarRingRenderer_->GetAtlasData().PivotPos = float4(0.3f, 0.5f, 0.0f, 0.0f);


}

void BossRoarRingEffect::Update(float _DeltaTime)
{
	AddScale_ += 100.f * _DeltaTime;
	Alpha_ -= 1.0f * _DeltaTime;
	RoarRingRenderer_->GetTransform().SetWorldScale({ RoarRingRenderer_->GetTransform().GetWorldScale().x + AddScale_.x, RoarRingRenderer_->GetTransform().GetWorldScale().y + AddScale_.y });
	RoarRingRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ <= 0.f)
	{
		this->Death();
	}
}

