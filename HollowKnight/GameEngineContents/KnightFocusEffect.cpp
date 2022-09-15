#include "PreCompile.h"
#include "KnightFocusEffect.h"

KnightFocusEffect::KnightFocusEffect() 
{
}

KnightFocusEffect::~KnightFocusEffect() 
{
}



void KnightFocusEffect::Start()
{
	CreateRendererComponent("Spell Effects_focus_appear0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS_APPEAR", FrameAnimation_DESC("Spell Effects_focus_appear0000-Sheet.png", 0, 6, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS", FrameAnimation_DESC("Spell Effects_focus_effect0000-Sheet.png", 0, 8, 0.100f, false));

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("FOCUS_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("FOCUS");
		});

	GetRenderer()->ChangeFrameAnimation("FOCUS_APPEAR");
}


void KnightFocusEffect::Update(float _DeltaTime)
{
}
