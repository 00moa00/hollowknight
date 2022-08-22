#include "PreCompile.h"
#include "AreaTitleTop.h"

AreaTitleTop::AreaTitleTop() 
{
}

AreaTitleTop::~AreaTitleTop() 
{
}

void AreaTitleTop::Start()
{
	CreateRendererComponent({624,166}, "Area Title Cln_fleur_top0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("FIRST_ANIMATION", FrameAnimation_DESC("Area Title Cln_fleur_top0000-Sheet.png", 0, 10, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SECOND_ANIMATION", FrameAnimation_DESC("Area Title Cln_fleur_top0011-Sheet.png", 0, 10, 0.100f, false));
	GetRenderer()->ChangeFrameAnimation("FIRST_ANIMATION");

	GetRenderer()->AnimationBindEnd("FIRST_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("SECOND_ANIMATION");
		});
}

void AreaTitleTop::Update(float _DeltaTime)
{
}

