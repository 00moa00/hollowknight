#include "PreCompile.h"
#include "AreaTitleBottom.h"

AreaTitleBottom::AreaTitleBottom() 
{
}

AreaTitleBottom::~AreaTitleBottom() 
{
}

void AreaTitleBottom::Start()
{
	CreateRendererComponent({ 544,181 }, "Area Title Cln_fleur_bottom0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("FIRST_ANIMATION", FrameAnimation_DESC("Area Title Cln_fleur_bottom0000-Sheet.png", 0, 10, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SECOND_ANIMATION", FrameAnimation_DESC("Area Title Cln_fleur_bottom0011-Sheet.png", 0, 10, 0.100f, false));
	GetRenderer()->ChangeFrameAnimation("FIRST_ANIMATION");

	GetRenderer()->AnimationBindEnd("FIRST_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("SECOND_ANIMATION");
		});
}

void AreaTitleBottom::Update(float _DeltaTime)
{
}

