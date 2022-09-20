#include "PreCompile.h"
#include "KnightDonutLightEffect.h"
#include "HollowKnightLevel.h"

KnightDonutLightEffect::KnightDonutLightEffect() 
{
}

KnightDonutLightEffect::~KnightDonutLightEffect() 
{
}

void KnightDonutLightEffect::Start()
{
	CreateRendererComponent(float4{ 450, 350, 1 }, "white_light_donut.png");
	GetRenderer()->GetPixelData().MulColor = { 1,1,1,0.3f };
	SetBlendMode(BlendMode::Add);
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 186 / 2, 0 });
}
void KnightDonutLightEffect::Update(float _DeltaTime)
{
	SetMulColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetDounutLightMulColor());
	SetPlusColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetDounutLightPlusColor());
	if (GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetisDonutLightOnOff() == true)
	{
		GetRenderer()->On();
	}

	else
	{
		GetRenderer()->Off();
	}
}