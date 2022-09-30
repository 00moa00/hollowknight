#include "PreCompile.h"
#include "UIPoint.h"

UIPoint::UIPoint() 
	:
	LeftPoint_(nullptr),
	RightPoint_(nullptr),

	PointScale_({ 99, 72 })

{
}

UIPoint::~UIPoint() 
{
}

void UIPoint::Start()
{
	LeftPoint_ = CreateComponent<GameEngineUIRenderer>();
	LeftPoint_->CreateFrameAnimationCutTexture("POINTER_UPDATE_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 0, 10, 0.070f));
	LeftPoint_->CreateFrameAnimationCutTexture("POINTER_IDLE_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 10, 10, 0.f));

	LeftPoint_->GetTransform().SetLocalScale(PointScale_ * 0.8f);
	LeftPoint_->ChangeFrameAnimation("POINTER_UPDATE_ANIMATION");
	LeftPoint_->GetTransform().SetLocalPosition({ -120, 0, 0 });

	//ftPoint_->AnimationBindEnd("POINTER_UPDATE_ANIMATION", &UIPoint::PointAnimationLeftEnd, this);

	LeftPoint_->AnimationBindEnd("POINTER_UPDATE_ANIMATION"
		, std::bind(&UIPoint::PointAnimationLeftEnd, this, std::placeholders::_1));




	LeftPoint_->SetSamplingModeLiner();


	RightPoint_ = CreateComponent<GameEngineUIRenderer>();
	RightPoint_->CreateFrameAnimationCutTexture("POINTER_UPDATE_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 0, 10, 0.070f));
	RightPoint_->CreateFrameAnimationCutTexture("POINTER_IDLE_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 10, 10, 0.f));

	RightPoint_->GetTransform().SetLocalScale(PointScale_ * 0.8f);
	RightPoint_->ChangeFrameAnimation("POINTER_UPDATE_ANIMATION");
	RightPoint_->GetTransform().SetLocalPosition({ 120, 0, 0 });
	RightPoint_->GetTransform().PixLocalNegativeX();

//ightPoint_->AnimationBindEnd("POINTER_UPDATE_ANIMATION", &UIPoint::PointAnimationRightEnd, this);
	RightPoint_->AnimationBindEnd("POINTER_UPDATE_ANIMATION"
		, std::bind(&UIPoint::PointAnimationRightEnd, this, std::placeholders::_1));
	RightPoint_->SetSamplingModeLiner();

}

void UIPoint::Update(float _DeltaTime)
{

}

void UIPoint::PointAnimationLeftEnd(const FrameAnimation_DESC& _Info)
{
	LeftPoint_->ChangeFrameAnimation("POINTER_IDLE_ANIMATION");
}

void UIPoint::PointAnimationRightEnd(const FrameAnimation_DESC& _Info)
{
	RightPoint_->ChangeFrameAnimation("POINTER_IDLE_ANIMATION");
}


void UIPoint::SetPointChangeUpdateAnimation()
{
	LeftPoint_->ChangeFrameAnimation("POINTER_UPDATE_ANIMATION");
	RightPoint_->ChangeFrameAnimation("POINTER_UPDATE_ANIMATION");
}

void UIPoint::SetPointChangeIdleAnimation()
{
	LeftPoint_->ChangeFrameAnimation("POINTER_IDLE_ANIMATION");
	RightPoint_->ChangeFrameAnimation("POINTER_IDLE_ANIMATION");
}

void UIPoint::SetLeffPointLocalPosition(float4 _LocalPosition)
{
}

void UIPoint::SetRightPointLocalPosition(float4 _LocalPosition)
{
}
