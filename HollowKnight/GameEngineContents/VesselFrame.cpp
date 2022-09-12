#include "PreCompile.h"
#include "VesselFrame.h"
#include "GlobalContentsValue.h"

VesselFrame::VesselFrame() 
{
}

VesselFrame::~VesselFrame() 
{
}

void VesselFrame::Start()
{
	//CreateCollisionComponent(float4{ 257, 164, 1 }, static_cast<int>(OBJECTORDER::UI));
	CreateRendererComponent(float4{ 257, 164, 1 }, "HUD Cln_HUD_frame_v020000-Sheet.png", 5, static_cast<int>(RENDERORDER::UI));

	GetRenderer()->CreateFrameAnimationCutTexture("VESSELFRAME_IDLE", FrameAnimation_DESC("HUD Cln_HUD_frame_v020000-Sheet.png", 5, 5, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("VESSELFRAME_APPEAR", FrameAnimation_DESC("HUD Cln_HUD_frame_v020000-Sheet.png", 0, 5, 0.150f, false));

	GetRenderer()->ChangeFrameAnimation("VESSELFRAME_APPEAR");
	GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);

	GetRenderer()->AnimationBindEnd("VESSELFRAME_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("VESSELFRAME_IDLE");
		});

}

void VesselFrame::Update(float _DeltaTime)
{
}

void VesselFrame::SetIdleAnimation()
{
	GetRenderer()->ChangeFrameAnimation("VESSELFRAME_IDLE");
}

