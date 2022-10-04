#include "PreCompile.h"
#include "KnightRoarEffect.h"

KnightRoarEffect::KnightRoarEffect() 
	:
	AddScale_(),

	Alpha_(1.0f),
	CreateTimer_(0.0f),

	RoarLineRenderer(nullptr)
{
}

KnightRoarEffect::~KnightRoarEffect() 
{
}

void KnightRoarEffect::Start()
{
	RoarLineRenderer = CreateComponent<GameEngineTextureRenderer>();
	RoarLineRenderer->SetTexture("Roar_lines_white.png");
	RoarLineRenderer->GetTransform().SetLocalScale({ 294.f * 0.8f, 283.f * 0.8f });
}

void KnightRoarEffect::Update(float _DeltaTime)
{
	AddScale_ += 220.f * _DeltaTime;
	//Alpha_ -= 1.4f * _DeltaTime;
	RoarLineRenderer->GetTransform().SetWorldScale({ RoarLineRenderer->GetTransform().GetWorldScale().x + AddScale_.x, RoarLineRenderer->GetTransform().GetWorldScale().y + AddScale_.y });
	//RoarLineRenderer->GetPixelData().MulColor.a = Alpha_;


	if (GetAccTime() > 2.f)
	{
		this->Death();
	}

}

