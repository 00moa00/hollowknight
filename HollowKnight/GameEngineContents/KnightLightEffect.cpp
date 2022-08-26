#include "PreCompile.h"
#include "KnightLightEffect.h"

KnightLightEffect::KnightLightEffect() 
{
}

KnightLightEffect::~KnightLightEffect() 
{
}

void KnightLightEffect::Start()
{
	CreateRendererComponent(float4{ 1645, 1448, 1 }, "light_effect_v03.png");
	GetRenderer()->GetPipeLine()->SetOutputMergerBlend("AddBlend");
	GetRenderer()->GetPixelData().MulColor.a = 0.3f;
	GetRenderer()->GetTransform().SetWorldPosition({0, 0,  0 });
}

void KnightLightEffect::Update(float _DeltaTime)
{
}

