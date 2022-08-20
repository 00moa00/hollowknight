#include "PreCompile.h"
#include "SideDarkEffect.h"
#include "GlobalContentsValue.h"

SideDarkEffect::SideDarkEffect() 

{
}

SideDarkEffect::~SideDarkEffect() 
{
}

void SideDarkEffect::Start()
{
	CreateRendererComponent(float4{ 1920, 1080, 1 }, "Darkcloud.png");

	GetRenderer()->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	GetRenderer()->GetTransform().SetLocalPosition({ 0, 0,  0 });

}

void SideDarkEffect::Update(float _DeltaTime)
{
}

