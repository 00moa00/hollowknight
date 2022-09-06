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
	CreateRendererComponent(float4{ 400, 400, 1 }, "light_effect_v06.png");
	GetRenderer()->GetPixelData().MulColor = { 1,1,1,0.4f };
	GetRenderer()->GetPipeLine()->SetOutputMergerBlend("AddBlend");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 95,  0 });
}
void KnightSmallLightEffect::Update(float _DeltaTime)
{

}