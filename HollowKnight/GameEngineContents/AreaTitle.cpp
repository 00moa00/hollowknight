#include "PreCompile.h"
#include "AreaTitle.h"

AreaTitle::AreaTitle() 
	:

	Alpha_(0.0f),

	AreaTitleTop_(nullptr),
	AreaTitleBottom_(nullptr),

	GameTitleBottomFont_(nullptr),
	GameTitleFont_(nullptr)

{
}

AreaTitle::~AreaTitle() 
{
}

void AreaTitle::Start()
{
	AreaTitleTop_ = GetLevel()->CreateActor<AreaTitleTop>();
	AreaTitleBottom_ = GetLevel()->CreateActor<AreaTitleBottom>();

	AreaTitleTop_->GetTransform().SetLocalPosition({0, 380.f});
	AreaTitleBottom_->GetTransform().SetLocalPosition({ 0, 50.f });

	GameTitleFont_ = CreateComponent<GameEngineFontRenderer>();

	GameTitleFont_->SetText("흙의 마을", "Noto Serif KR");
	GameTitleFont_->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	GameTitleFont_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), (GameEngineWindow::GetInst()->GetScale().hy() - 250.0f) });
	GameTitleFont_->SetSize(100);
	GameTitleFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	GameTitleFont_->SetTopAndBotSort(TopAndBotSort::VCENTER);

	GameTitleBottomFont_ = CreateComponent<GameEngineFontRenderer>();

	GameTitleBottomFont_->SetText("사라져가는 땅의 입구", "Noto Serif KR");
	GameTitleBottomFont_->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	GameTitleBottomFont_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), (GameEngineWindow::GetInst()->GetScale().hy() - 170.0f) });
	GameTitleBottomFont_->SetSize(50);
	GameTitleBottomFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	GameTitleBottomFont_->SetTopAndBotSort(TopAndBotSort::VCENTER);



	AreaTitleStateManager_.CreateStateMember("APPEAR"
		, std::bind(&AreaTitle::AreaTitleAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&AreaTitle::AreaTitleAppearStart, this, std::placeholders::_1)
		, std::bind(&AreaTitle::AreaTitleAppearEnd, this, std::placeholders::_1));

	AreaTitleStateManager_.CreateStateMember("BYE"
		, std::bind(&AreaTitle::AreaTitleByeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&AreaTitle::AreaTitleByeStart, this, std::placeholders::_1)
		, std::bind(&AreaTitle::AreaTitleByeEnd, this, std::placeholders::_1));

	AreaTitleStateManager_.CreateStateMember("IDLE"
		, std::bind(&AreaTitle::AreaTitleIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&AreaTitle::AreaTitleIdleStart, this, std::placeholders::_1)
		, std::bind(&AreaTitle::AreaTitleIdleEnd, this, std::placeholders::_1));

	AreaTitleStateManager_.ChangeState("APPEAR");

}

void AreaTitle::Update(float _DeltaTime)
{
	AreaTitleStateManager_.Update(_DeltaTime);
}

void AreaTitle::AreaTitleAppearStart(const StateInfo& _Info)
{
}

void AreaTitle::AreaTitleAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	AlphaTimer_ += _DeltaTime;

	if (AlphaTimer_ > 0.2f)
	{
		Alpha_ += 0.1f;
		AlphaTimer_ = 0.0f;
		GameTitleFont_->SetColor({ 1.0f, 1.0f, 1.0f, Alpha_ });
		GameTitleBottomFont_->SetColor({ 1.0f, 1.0f, 1.0f, Alpha_ });
	}

	if (Alpha_ >= 1.0f)
	{
		AreaTitleStateManager_.ChangeState("IDLE");
		return;
	}
}

void AreaTitle::AreaTitleAppearEnd(const StateInfo& _Info)
{
	KnightSoundManager::GetInst()->BgmOn("Dirtmouth 1.ogg", 400);
	AlphaTimer_ = 0.f;
}

void AreaTitle::AreaTitleIdleStart(const StateInfo& _Info)
{
	ReSetAccTime();
}

void AreaTitle::AreaTitleIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 2.0f)
	{
		AreaTitleStateManager_.ChangeState("BYE");
	}
}

void AreaTitle::AreaTitleIdleEnd(const StateInfo& _Info)
{
}

void AreaTitle::AreaTitleByeStart(const StateInfo& _Info)
{

}

void AreaTitle::AreaTitleByeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	AlphaTimer_ += _DeltaTime;

	if (AlphaTimer_ > 0.2f)
	{
		Alpha_ -= 0.1f;
		AlphaTimer_ = 0.0f;
		GameTitleFont_->SetColor({ 1.0f, 1.0f, 1.0f, Alpha_ });
		GameTitleBottomFont_->SetColor({ 1.0f, 1.0f, 1.0f, Alpha_ });
		AreaTitleTop_->GetRenderer()->GetPixelData().MulColor.a = Alpha_;
		AreaTitleBottom_->GetRenderer()->GetPixelData().MulColor.a = Alpha_;

	}

	if (Alpha_ <= 0.0f)
	{
		GameTitleFont_->Death();
		GameTitleBottomFont_->Death();
		AreaTitleTop_->Death();
		AreaTitleBottom_->Death();
		this->Death();
	}
}

void AreaTitle::AreaTitleByeEnd(const StateInfo& _Info)
{
}

