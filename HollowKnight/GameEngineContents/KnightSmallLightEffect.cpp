#include "PreCompile.h"
#include "KnightSmallLightEffect.h"

KnightSmallLightEffect::KnightSmallLightEffect() 
{
}

KnightSmallLightEffect::~KnightSmallLightEffect() 
{
}

void KnightSmallLightEffect::Start()
{
	CreateRendererComponent(float4{ 1208, 943, 1 }, "light_effect_v05.png");
	GetRenderer()->GetColorData().MulColor = { 1,1,1,0.5f };
	GetRenderer()->GetPipeLine()->SetOutputMergerBlend("LightenBlend");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0,  0 });
}
void KnightSmallLightEffect::Update(float _DeltaTime)
{

}