#include "PreCompile.h"
#include "SettingPage.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"
#include "PointActorComponent.h"
#include "HollowKnightLevel.h"

SettingPage::SettingPage() 
	:
	BackGround_(nullptr),

	CharmPage_(nullptr),

	BorderCornerLeftTop_(nullptr),
	BorderCornerRightTop_(nullptr),
	BorderCornerLeftBottom_(nullptr),
	BorderCornerRightBottom_(nullptr),

	BorderBottom_(nullptr),

	BorderTop_(nullptr),

	BorderLeftArrow_(nullptr),
	BorderRightArrow_(nullptr),

	OnOffPage_(false)
{
}

SettingPage::~SettingPage() 
{
}

void SettingPage::Start()
{

	//================================
	//    Initialize
	//================================
	BackGround_ = CreateComponent<GameEngineUIRenderer>();
	BackGround_->SetTexture("Black.png");
	BackGround_->ScaleToTexture();
	BackGround_->GetColorData().MulColor.a = 0.8f;
	BackGround_->SetPivot(PIVOTMODE::LEFTTOP);
	BackGround_->GetTransform().SetLocalPosition({0,0,static_cast<float>(Z_ORDER::UI)});
	BackGround_->Off();




	BorderCornerLeftTop_ = GetLevel()->CreateActor<BorderCorner>();
	BorderCornerLeftTop_->GetTransform().SetLocalPosition({
		- (GameEngineWindow::GetInst()->GetScale().hx() - 200.f)
		, GameEngineWindow::GetInst()->GetScale().hy() - 250.f
		, static_cast<float>(Z_ORDER::UI_Border) });

	BorderCornerLeftTop_->Off();



	BorderCornerRightTop_ = GetLevel()->CreateActor<BorderCorner>();
	BorderCornerRightTop_->GetRenderer()->GetTransform().PixLocalNegativeX();
	BorderCornerRightTop_->GetTransform().SetLocalPosition({
	GameEngineWindow::GetInst()->GetScale().hx() - 200.f 
	, GameEngineWindow::GetInst()->GetScale().hy() - 250.f
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderCornerRightTop_->Off();



	BorderCornerLeftBottom_ = GetLevel()->CreateActor<BorderCorner>();
	BorderCornerLeftBottom_->PixLocalNegativeY();
	BorderCornerLeftBottom_->GetTransform().SetLocalPosition({
	- (GameEngineWindow::GetInst()->GetScale().hx() - 200.f)
	, - (GameEngineWindow::GetInst()->GetScale().hy() - 250.f)
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderCornerLeftBottom_->Off();



	BorderCornerRightBottom_ = GetLevel()->CreateActor<BorderCorner>();
	BorderCornerRightBottom_->PixLocalNegativeY();
	BorderCornerRightBottom_->GetRenderer()->GetTransform().PixLocalNegativeX();
	BorderCornerRightBottom_->GetTransform().SetLocalPosition({
	GameEngineWindow::GetInst()->GetScale().hx() - 200.f
	,  -(GameEngineWindow::GetInst()->GetScale().hy() - 250.f)
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderCornerRightBottom_->Off();



	BorderBottom_ = GetLevel()->CreateActor<BorderBottom>();
	BorderBottom_->GetTransform().SetLocalPosition({
	0
	,  -(GameEngineWindow::GetInst()->GetScale().hy() - 150.f)
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderBottom_->Off();


	BorderTop_ = GetLevel()->CreateActor<BorderTop>();
	BorderTop_->GetTransform().SetLocalPosition({
	140.f
	, (GameEngineWindow::GetInst()->GetScale().hy() - 100.f)
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderTop_->Off();




	BorderLeftArrow_ = GetLevel()->CreateActor<BorderArrow>();
	BorderLeftArrow_->GetTransform().SetLocalPosition({
	- (GameEngineWindow::GetInst()->GetScale().hx() - 70.f)
	, 0
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderLeftArrow_->Off();

	PointActorComponent* BorderLeftArrowComponent_ = CreateComponent<PointActorComponent>();
	BorderLeftArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow), PAGE_TYPE::Charm, BorderLeftArrow_);
	BorderLeftArrowComponent_->GetTransform().SetLocalPosition({ BorderLeftArrow_->GetTransform().GetLocalPosition()});

	BorderRightArrow_ = GetLevel()->CreateActor<BorderArrow>();
	//BorderRightArrow_->
	BorderRightArrow_->GetTransform().SetLocalPosition({
	(GameEngineWindow::GetInst()->GetScale().hx() - 90.f)
	, 0
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderRightArrow_->Off();

	PointActorComponent* BorderRightArrowComponent_ = CreateComponent<PointActorComponent>();
	BorderRightArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::RightArrow), PAGE_TYPE::Charm, BorderRightArrow_);
	BorderRightArrowComponent_->GetTransform().SetLocalPosition({ BorderRightArrow_->GetTransform().GetLocalPosition() });


	SettingPointer_ = GetLevel()->CreateActor<SettingPointer>();

	SettingPointer_->SetCharmPageActorMax();
	SettingPointer_->SetFirstPosCharmPage();


	CharmPage_ = GetLevel()->CreateActor<CharmPage>();

	//================================
	//    CreateKey
	//================================
	if (false == GameEngineInput::GetInst()->IsKey("OnOffSettingPage"))
	{
		GameEngineInput::GetInst()->CreateKey("OnOffSettingPage", 'I');
	}

	//================================
	//    Create State
	//================================
	SettingPageManager_.CreateStateMember("ON"
		, std::bind(&SettingPage::SettingOnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPage::SettingOnStart, this, std::placeholders::_1)
		, std::bind(&SettingPage::SettingOnEnd, this, std::placeholders::_1));

	SettingPageManager_.CreateStateMember("OFF"
		, std::bind(&SettingPage::SettingOffUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPage::SettingOffStart, this, std::placeholders::_1)
		, std::bind(&SettingPage::SettingOffEnd, this, std::placeholders::_1));

	SettingPageManager_.ChangeState("OFF");

}

void SettingPage::Update(float _DeltaTime)
{
	SettingPageManager_.Update(_DeltaTime);

}

void SettingPage::OnOffPage()
{
	OnOffPage_ = !OnOffPage_;
}

void SettingPage::AllOff()
{
	BackGround_->Off();
	//CharmPage_->Off();
	BorderCornerLeftTop_->Off();
	BorderCornerRightTop_->Off();
	BorderCornerLeftBottom_->Off();
	BorderCornerRightBottom_->Off();
	BorderBottom_->Off();
	BorderTop_->Off();
	BorderLeftArrow_->Off();
	BorderRightArrow_->Off();
	SettingPointer_->AllOff();
	


}

void SettingPage::AllOn()
{
	BackGround_->On();
	//CharmPage_->On();
	BorderCornerLeftTop_->On();
	BorderCornerLeftTop_->ChangeAnimation("OPEN_ANIMATION");

	BorderCornerRightTop_->On();
	BorderCornerRightTop_->ChangeAnimation("OPEN_ANIMATION");

	BorderCornerLeftBottom_->On();
	BorderCornerLeftBottom_->ChangeAnimation("OPEN_ANIMATION");

	BorderCornerRightBottom_->On();
	BorderCornerRightBottom_->ChangeAnimation("OPEN_ANIMATION");

	BorderBottom_->On();
	BorderBottom_->ChangeAnimation("OPEN_ANIMATION");

	BorderTop_->On();
	BorderTop_->ChangeAnimation("OPEN_ANIMATION");

	BorderLeftArrow_->On();
	BorderLeftArrow_->ChangeAnimation("OPEN_ANIMATION");

	BorderRightArrow_->On();
	BorderRightArrow_->ChangeAnimation("OPEN_ANIMATION");

	SettingPointer_->AllOn();

}

void SettingPage::SettingOffStart(const StateInfo& _Info)
{
	AllOff();
}

void SettingPage::SettingOffUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("OnOffSettingPage") && KnightData::GetInst()->GetisSetting() == true)
	{
		OnOffPage();
		SettingPageManager_.ChangeState("ON");
	}


}

void SettingPage::SettingOffEnd(const StateInfo& _Info)
{
}

void SettingPage::SettingOnStart(const StateInfo& _Info)
{
	AllOn();
}

void SettingPage::SettingOnUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsDown("OnOffSettingPage") 
		&& KnightData::GetInst()->GetisSetting() == true)
	{
		OnOffPage();
		SettingPageManager_.ChangeState("OFF");
	}

}

void SettingPage::SettingOnEnd(const StateInfo& _Info)
{
}

