#include "PreCompile.h"
#include "KnightDonutLightEffect.h"

KnightDonutLightEffect::KnightDonutLightEffect() 
{
}

KnightDonutLightEffect::~KnightDonutLightEffect() 
{
}

void KnightDonutLightEffect::Start()
{
	CreateRendererComponent(float4{ 1208, 943, 1 }, "light_effect_v04.png");
	GetRenderer()->GetColorData().MulColor = { 1,1,1,0.4f };
	GetRenderer()->GetPipeLine()->SetOutputMergerBlend("LightenBlend");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0,  0 });
}
void KnightDonutLightEffect::Update(float _DeltaTime)
{

}