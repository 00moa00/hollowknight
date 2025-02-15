#include "PreCompile.h"
#include "KnightMainLightEffect.h"
#include "HollowKnightLevel.h"

KnightMainLightEffect::KnightMainLightEffect() 
{
}

KnightMainLightEffect::~KnightMainLightEffect() 
{
}

void KnightMainLightEffect::Start()
{
	CreateRendererComponent(float4{ 1000, 800, 1 }, "white_light.png");
	SetBlendMode(BlendMode::Add);
	GetRenderer()->GetPixelData().MulColor.a = 0.6f;
	GetRenderer()->GetTransform().SetWorldPosition({0, 186 / 2, 0 });
}

void KnightMainLightEffect::Update(float _DeltaTime)
{
	SetMulColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetMainLightMulColor());
	SetPlusColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetMainLightPlusColor());
	if (GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetisMainLightOnOff() == true)
	{
		GetRenderer()->On();
	}

	else
	{
		GetRenderer()->Off();
	}
}


