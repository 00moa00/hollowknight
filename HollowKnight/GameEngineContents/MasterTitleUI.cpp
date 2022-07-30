#include "PreCompile.h"
#include "MasterTitleUI.h"

MasterTitleUI::MasterTitleUI() 
	:
	LeftPointGameStart_(nullptr),
	RightPointGameStart_(nullptr),
	LeftPointMapEditor_(nullptr),
	RightPointMapEditor_(nullptr),
	LeftPointGameExit_(nullptr),
	RightPointGameExit_(nullptr),

	PointScale_({ 99, 72 })
{
}

MasterTitleUI::~MasterTitleUI() 
{
}

void MasterTitleUI::Start()
{
	LeftPointGameStart_ = CreateComponent<GameEngineUIRenderer>();
	LeftPointGameStart_->CreateFrameAnimation("POINTER_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 0, 10, 0.05f));
	LeftPointGameStart_->CreateFrameAnimation("POINTER_IDLE", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 10, 10, 0.05f));

	
	LeftPointGameStart_->GetTransform().SetLocalScale(PointScale_);
	LeftPointGameStart_->ChangeFrameAnimation("POINTER_ANIMATION");
	LeftPointGameStart_->GetTransform().SetLocalPosition({-100, 0, 0});
	//LeftPointGameStart_->ScaleToTexture();

	LeftPointGameStart_->AnimationBindEnd("POINTER_ANIMATION", &MasterTitleUI::GameStartAnimationEnd, this);


	RightPointGameStart_ = CreateComponent<GameEngineUIRenderer>();
	RightPointGameStart_->CreateFrameAnimation("POINTER_ANIMATION", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 0, 10, 0.05f));
	RightPointGameStart_->CreateFrameAnimation("POINTER_IDLE", FrameAnimation_DESC("main_menu_pointer_anim0000-Sheet.png", 10, 10, 0.05f));

	RightPointGameStart_->GetTransform().SetLocalScale(PointScale_);
	RightPointGameStart_->ChangeFrameAnimation("POINTER_ANIMATION");
	RightPointGameStart_->GetTransform().SetLocalPosition({ 100, 0, 0 });
	RightPointGameStart_->GetTransform().PixLocalNegativeX();







	//단일
	LeftPointMapEditor_ = CreateComponent<GameEngineUIRenderer>();
	LeftPointMapEditor_->SetTexture("main_menu_pointer_anim0009.png");
	LeftPointMapEditor_->GetTransform().SetLocalScale(PointScale_);
	LeftPointMapEditor_->GetTransform().SetLocalPosition({ 400, 0, 0 });
	LeftPointMapEditor_->SetSamplingModeLiner();


	//시트에서 자른거
	RightPointMapEditor_ = CreateComponent<GameEngineUIRenderer>();
	RightPointMapEditor_->SetTexture("main_menu_pointer_anim0000-Sheet.png", 10);
	RightPointMapEditor_->GetTransform().SetLocalScale(PointScale_);
	RightPointMapEditor_->GetTransform().SetLocalPosition({ 500, 0, 0 });


	LeftPointGameExit_ = CreateComponent<GameEngineUIRenderer>();
	RightPointGameExit_ = CreateComponent<GameEngineUIRenderer>();



}

void MasterTitleUI::Update()
{
}

void MasterTitleUI::EventOffGameStart()
{
	LeftPointGameStart_->Off();
	RightPointGameStart_->Off();
}

void MasterTitleUI::EventOffMapEditor()
{
}

void MasterTitleUI::EventOffGameExit()
{
}

void MasterTitleUI::GameStartAnimationEnd(const FrameAnimation_DESC& _Info)
{
	LeftPointGameStart_->ChangeFrameAnimation("POINTER_IDLE");
	RightPointGameStart_->ChangeFrameAnimation("POINTER_IDLE");
}

