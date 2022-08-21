#include "PreCompile.h"
#include "BorderBottom.h"

BorderBottom::BorderBottom() 
	:
	AnimationEnd_(false)
{
}

BorderBottom::~BorderBottom() 
{
}

void BorderBottom::Start()
{
	CreateRendererComponent(float4{ 62, 62, 1 }, "UI_inventory_animated_Border_Fleur_bottom0000-Sheet.png", 0, static_cast<int>(RENDERORDER::UI));

	//================================
	//    Create Animation
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("OPEN_ANIMATION", FrameAnimation_DESC("UI_inventory_animated_Border_Fleur_bottom0000-Sheet.png", 0, 8, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_inventory_animated_Border_Fleur_bottom0000-Sheet.png", 8, 8, 0.050f, false));

	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("OPEN_ANIMATION");
	//GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("OPEN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
		});
}

void BorderBottom::Update(float _DeltaTime)
{
}

