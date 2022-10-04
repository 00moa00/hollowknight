#include "PreCompile.h"
#include "SettingPage.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"
#include "PointActorComponent.h"
#include "HollowKnightLevel.h"

SettingPage::SettingPage() 
	:
	BackGround_(nullptr),

	//CharmPage_(nullptr),

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
	BackGround_->GetPixelData().MulColor.a = 0.8f;
	BackGround_->GetTransform().SetLocalPosition({ 0,0,static_cast<float>(Z_ORDER::UI_BackBoard) });
	BackGround_->Off();

	PageName_ = CreateComponent<GameEngineFontRenderer>();
	PageName_->SetText("ºÎÀû", "Noto Serif KR");
	PageName_->SetColor({ 1.0f, 1.0f, 1.0f });
	PageName_->ChangeCamera(CAMERAORDER::UICAMERA);

	PageName_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(),
		(100.f ),
		static_cast<float>(Z_ORDER::UI) });

	PageName_->SetSize(38);
	PageName_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PageName_->SetTopAndBotSort(TopAndBotSort::VCENTER);
	//PageName_->SetLevelOverOn();

	BorderCornerLeftTop_ = GetLevel()->CreateActor<BorderCorner>();
	BorderCornerLeftTop_->GetTransform().SetLocalPosition({
		-(GameEngineWindow::GetInst()->GetScale().hx() - 200.f)
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
	-(GameEngineWindow::GetInst()->GetScale().hx() - 200.f)
	, -(GameEngineWindow::GetInst()->GetScale().hy() - 250.f)
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
	-(GameEngineWindow::GetInst()->GetScale().hx() - 70.f)
	, 0
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderLeftArrow_->SetPointerSize(BorderLeftArrow_->GetRenderer()->GetTransform().GetLocalScale());
	BorderLeftArrow_->Off();

	{
		PointActorComponent* BorderLeftArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderLeftArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow), PAGE_TYPE::Charm, BorderLeftArrow_);
	}

	{
		PointActorComponent* BorderLeftArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderLeftArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow), PAGE_TYPE::Inventory, BorderLeftArrow_);
	}

	{
		PointActorComponent* BorderLeftArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderLeftArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow), PAGE_TYPE::Map, BorderLeftArrow_);
	}

	BorderRightArrow_ = GetLevel()->CreateActor<BorderArrow>();
	BorderRightArrow_->GetTransform().SetLocalPosition({
	(GameEngineWindow::GetInst()->GetScale().hx() - 90.f)
	, 0
	, static_cast<float>(Z_ORDER::UI_Border) });
	BorderRightArrow_->GetRenderer()->GetTransform().PixLocalNegativeX();
	BorderRightArrow_->SetPointerSize({ -BorderRightArrow_->GetRenderer()->GetTransform().GetLocalScale().x ,BorderRightArrow_->GetRenderer()->GetTransform().GetLocalScale().y  });

	BorderRightArrow_->Off();

	{
		PointActorComponent* BorderRightArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderRightArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::RightArrow), PAGE_TYPE::Charm, BorderRightArrow_);
	}

	{
		PointActorComponent* BorderRightArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderRightArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::RightArrow), PAGE_TYPE::Inventory, BorderRightArrow_);
	}

	{
		PointActorComponent* BorderRightArrowComponent_ = CreateComponent<PointActorComponent>();
		BorderRightArrowComponent_->PushPointerActor(static_cast<int>(CHAR_PAGE_ACTOR::RightArrow), PAGE_TYPE::Map, BorderRightArrow_);
	}


	AllPage_.push_back(GetLevel()->CreateActor<CharmPage>());
	AllPage_[0]->SetCurrentPage(CURRENT_PAGE_INDEX::CurrentPage);


	AllPage_.push_back(GetLevel()->CreateActor<InventoryPage>());
	AllPage_[1]->SetCurrentPage(CURRENT_PAGE_INDEX::NextPage);

	AllPage_.push_back(GetLevel()->CreateActor<MapPage>());
	AllPage_[2]->SetCurrentPage(CURRENT_PAGE_INDEX::SincePage);

	SettingPointer_ = GetLevel()->CreateActor<SettingPointer>();
	SettingPointer_->SetCharmPageActorMax();
	SettingPointer_->SetFirstPosCharmPage();
	SettingPointer_->GetTransform().SetWorldPosition({0,0,100});


	for (int i = 0; i < AllPage_.size(); ++i)
	{
		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::SincePage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ -1920, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::CurrentPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 0, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::NextPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 1920, 0 });
		}
	}

	//================================
	//    CreateKey
	//================================
	if (false == GameEngineInput::GetInst()->IsKey("OnOffCheck"))
	{
		GameEngineInput::GetInst()->CreateKey("OnOffCheck", 'I');
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

	SettingPageManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPage::SettingIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPage::SettingIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPage::SettingIdleEnd, this, std::placeholders::_1));

	SettingPageManager_.CreateStateMember("RIGHT_MOVE"
		, std::bind(&SettingPage::SettingMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPage::SettingMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPage::SettingMoveRightEnd, this, std::placeholders::_1));

	SettingPageManager_.CreateStateMember("LEFT_MOVE"
		, std::bind(&SettingPage::SettingMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPage::SettingMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPage::SettingMoveLeftEnd, this, std::placeholders::_1));

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
	AllPage_[0]->SetCurrentPage(CURRENT_PAGE_INDEX::CurrentPage);
	AllPage_[1]->SetCurrentPage(CURRENT_PAGE_INDEX::NextPage);
	AllPage_[2]->SetCurrentPage(CURRENT_PAGE_INDEX::SincePage);

	SettingPointer_->SetFirstPosCharmPage();


	for (int i = 0; i < AllPage_.size(); ++i)
	{
		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::SincePage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ -1920, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::CurrentPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 0, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::NextPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 1920, 0 });
		}
	}

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
	PageName_->Off();

	for (int i = 0; i < AllPage_.size(); ++i)
	{
		AllPage_[i]->AllOff();
	}
}

void SettingPage::AllOn()
{
	BackGround_->On();
	//CharmPage_->On();
	BorderCornerLeftTop_->On();
	BorderCornerLeftTop_-> ChangeAnimation("OPEN_ANIMATION");

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
	PageName_->On();

	SettingPointer_->AllOn();

	for (int i = 0; i < AllPage_.size(); ++i)
	{
		AllPage_[i]->AllOn();
	}

}

void SettingPage::SettingOffStart(const StateInfo& _Info)
{
	AllOff();
}

void SettingPage::SettingOffUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPageManager_.ChangeState("IDLE");
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

	SettingPageManager_.ChangeState("IDLE");

}

void SettingPage::SettingOnEnd(const StateInfo& _Info)
{
}

void SettingPage::SettingIdleStart(const StateInfo& _Info)
{
	for (int i = 0; i < AllPage_.size(); ++i)
	{
		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::SincePage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ -1920, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::CurrentPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 0, 0 });
		}

		if (AllPage_[i]->GetCurrentPage() == CURRENT_PAGE_INDEX::NextPage)
		{
			AllPage_[i]->GetTransform().SetWorldPosition({ 1920, 0 });
		}

		if (AllPage_[i]->GetPageType() == PAGE_TYPE::Inventory)
		{
			GetLevel<HollowKnightLevel>()->GetInventoryPageInfo()->SetFontMove();
		}

		if (AllPage_[i]->GetPageType() == PAGE_TYPE::Charm)
		{
			GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetFontMove();
		}
	}

}

void SettingPage::SettingIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("OnOffCheck"))
	{
		if (KnightData::GetInst()->GetisSetting() == false)
		{
			OnOffPage();
			SettingPageManager_.ChangeState("OFF");
		}

		if (KnightData::GetInst()->GetisSetting() == true)
		{
			OnOffPage();
			SettingPageManager_.ChangeState("ON");
		}
	}

	if (SettingPointer_->GetisDownNextpageRight())
	{
		SettingPointer_->SetisDownNextPageRight(false);
		SettingPageManager_.ChangeState("RIGHT_MOVE");
	}


	if (SettingPointer_->GetisDownLextPageLeft())
	{
		SettingPointer_->SetisDownNextPageLeft(false);
		SettingPageManager_.ChangeState("LEFT_MOVE");
	}
}

void SettingPage::SettingIdleEnd(const StateInfo& _Info)
{
}

void SettingPage::SettingMoveRightStart(const StateInfo& _Info)
{
	for (int i = 0; i < AllPage_.size(); ++i)
	{
		int Setindex = (static_cast<int>(AllPage_[i]->GetCurrentPage())) - 1;

		if (Setindex == (static_cast<int>(CURRENT_PAGE_INDEX::MAX)))
		{
			Setindex = (static_cast<int>(CURRENT_PAGE_INDEX::SincePage));
		}

		else if (Setindex == (static_cast<int>(CURRENT_PAGE_INDEX::MIN)))
		{
			Setindex = (static_cast<int>(CURRENT_PAGE_INDEX::NextPage));
		}

		AllPage_[i]->SetCurrentPage(static_cast<CURRENT_PAGE_INDEX>(Setindex));
	}

}

void SettingPage::SettingMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//CharmPage_->GetTransform().SetWorldMove(float4::LEFT * _DeltaTime * 200.f);
	for (int i = 0; i < AllPage_.size(); ++i)
	{
		if (AllPage_[i]->isCurrentPage() == true)
		{

			if (AllPage_[i]->GetTransform().GetWorldPosition().x < 0)
			{
				PageName_->SetText(AllPage_[i]->GetPageName(), "Noto Serif KR");
				SettingPageManager_.ChangeState("IDLE");
			}
		}

		GetLevel<HollowKnightLevel>()->GetInventoryPageInfo()->SetFontMove();
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetFontMove();

		AllPage_[i]->GetTransform().SetWorldMove(float4::LEFT * _DeltaTime * 700.f);
	}

	//if()
}

void SettingPage::SettingMoveRightEnd(const StateInfo& _Info)
{
	SettingPointer_->SetisDownNextPageRight(false);
	for (int i = 0; i < AllPage_.size(); ++i)
	{

		if (AllPage_[i]->isCurrentPage() == true)
		{
			SettingPointer_->SetCurrentPage(AllPage_[i]->GetPageType());
		}
	}


}

void SettingPage::SettingMoveLeftStart(const StateInfo& _Info)
{
	for (int i = 0; i < AllPage_.size(); ++i)
	{

		int Setindex = (static_cast<int>(AllPage_[i]->GetCurrentPage())) + 1;

		if (Setindex == (static_cast<int>(CURRENT_PAGE_INDEX::MAX)))
		{
			Setindex = (static_cast<int>(CURRENT_PAGE_INDEX::SincePage));
		}

		else if (Setindex == (static_cast<int>(CURRENT_PAGE_INDEX::MIN)))
		{
			Setindex = (static_cast<int>(CURRENT_PAGE_INDEX::NextPage));
		}

		AllPage_[i]->SetCurrentPage(static_cast<CURRENT_PAGE_INDEX>(Setindex));
	}

}

void SettingPage::SettingMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < AllPage_.size(); ++i)
	{
		if (AllPage_[i]->isCurrentPage() == true)
		{
			if (AllPage_[i]->GetTransform().GetWorldPosition().x > 0)
			{
				PageName_->SetText(AllPage_[i]->GetPageName(), "Noto Serif KR");
				SettingPageManager_.ChangeState("IDLE");
			}
		}

		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetFontMove();
		GetLevel<HollowKnightLevel>()->GetInventoryPageInfo()->SetFontMove();
		AllPage_[i]->GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime * 700.f);
	}
}

void SettingPage::SettingMoveLeftEnd(const StateInfo& _Info)
{
	SettingPointer_->SetisDownNextPageRight(false);
	for (int i = 0; i < AllPage_.size(); ++i)
	{

		if (AllPage_[i]->isCurrentPage() == true)
		{
			SettingPointer_->SetCurrentPage(AllPage_[i]->GetPageType());
		}
	}


}

