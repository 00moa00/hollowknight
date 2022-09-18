#include "PreCompile.h"
#include "KnightSiblingLightEffect.h"
#include "HollowKnightLevel.h"

KnightSiblingLightEffect::KnightSiblingLightEffect() 
{
}

KnightSiblingLightEffect::~KnightSiblingLightEffect() 
{
}

void KnightSiblingLightEffect::Start()
{
	CreateRendererComponent(float4{ 600, 600, 1 }, "sibling_light_effect.png");
	GetRenderer()->GetPixelData().MulColor = { 1,1,1,0.3f };
	SetBlendMode(BlendMode::Alpha);
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 186/2,  0 });
}
void KnightSiblingLightEffect::Update(float _DeltaTime)
{
	SetMulColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetSlibingLightMulColor());
	SetPlusColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetSlibingLightPlusColor());
}