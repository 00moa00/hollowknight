#include "PreCompile.h"
#include "KnightSiblingLightEffect.h"

KnightSiblingLightEffect::KnightSiblingLightEffect() 
{
}

KnightSiblingLightEffect::~KnightSiblingLightEffect() 
{
}

void KnightSiblingLightEffect::Start()
{
	CreateRendererComponent(float4{ 250, 150, 1 }, "sibling_light_effect.png");
	GetRenderer()->GetPixelData().MulColor = { 1,1,1,0.3f };
	SetBlendMode(BlendMode::Add);
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 80,  0 });
}
void KnightSiblingLightEffect::Update(float _DeltaTime)
{

}