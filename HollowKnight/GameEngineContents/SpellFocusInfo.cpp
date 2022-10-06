#include "PreCompile.h"
#include "SpellFocusInfo.h"

SpellFocusInfo::SpellFocusInfo() 
	:
	KeyTexture(nullptr),
	SpellTexture(nullptr),

	FocusInfo1_(nullptr),
	FocusInfo2_(nullptr),
	FocusInfo3_(nullptr)
{
}

SpellFocusInfo::~SpellFocusInfo() 
{
}

void SpellFocusInfo::Start()
{

	FocusInfo1_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	FocusInfo1_->CreateFontRenderer(
		"적을 공격하여 영혼을 모으십시오.\n충분한 영혼이 모이면"
		, 30
		, { GameEngineWindow::GetInst()->GetScale().hx() , GameEngineWindow::GetInst()->GetScale().hy() + 160.f },
		false,
		false
	);

	//DialogueList_.back()->Ge SetParent(this);
	FocusInfo1_->Off();
	FocusInfo1_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);


	FocusInfo2_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	FocusInfo2_->CreateFontRenderer(
		"길게 누르기"
		, 37
		, { GameEngineWindow::GetInst()->GetScale().hx() - 80.f , GameEngineWindow::GetInst()->GetScale().hy() + 250.f },
		false,
		false
	);

	//DialogueList_.back()->Ge SetParent(this);
	FocusInfo2_->Off();
	FocusInfo2_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);

	FocusInfo3_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	FocusInfo3_->CreateFontRenderer(
		"영혼을 집중해 치유할 수 있습니다."
		, 30
		, { GameEngineWindow::GetInst()->GetScale().hx() , GameEngineWindow::GetInst()->GetScale().hy() + 310.f },
		false,
		false
	);

	//DialogueList_.back()->Ge SetParent(this);
	FocusInfo3_->Off();
	FocusInfo3_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);

	SpellTexture = CreateComponent<GameEngineUIRenderer>();
	SpellTexture->SetTexture("Focus_prompt_temp.png");
	SpellTexture->GetTransform().SetLocalScale(SpellTexture->GetCurTexture()->GetScale());
	SpellTexture->GetTransform().SetLocalPosition({0, -40});
	SpellTexture->Off();


	KeyTexture = CreateComponent<GameEngineUIRenderer>();
	KeyTexture->SetTexture("button_skin_0004_square_arrow_u.png");
	KeyTexture->GetTransform().SetLocalScale(KeyTexture->GetCurTexture()->GetScale() * 0.6f);
	KeyTexture->GetTransform().SetLocalPosition({80.f, -280.f });
	KeyTexture->Off();


	SpellFocusInfoManager_.CreateStateMember("IDLE"
		, std::bind(&SpellFocusInfo::SpellFocusInfoIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SpellFocusInfo::SpellFocusInfoIdleStart, this, std::placeholders::_1)
		, std::bind(&SpellFocusInfo::SpellFocusInfoIdleEnd, this, std::placeholders::_1));

	SpellFocusInfoManager_.CreateStateMember("ON"
		, std::bind(&SpellFocusInfo::SpellFocusInfoOnDialougueUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SpellFocusInfo::SpellFocusInfoOnDialougueStart, this, std::placeholders::_1)
		, std::bind(&SpellFocusInfo::SpellFocusInfoOnDialougueEnd, this, std::placeholders::_1));

	SpellFocusInfoManager_.CreateStateMember("OFF"
		, std::bind(&SpellFocusInfo::SpellFocusInfoOffDialougueUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SpellFocusInfo::SpellFocusInfoOffDialougueStart, this, std::placeholders::_1)
		, std::bind(&SpellFocusInfo::SpellFocusInfoOffDialougueEnd, this, std::placeholders::_1));

	SpellFocusInfoManager_.ChangeState("IDLE");

}

void SpellFocusInfo::Update(float _DeltaTime)
{
	SpellFocusInfoManager_.Update(_DeltaTime);
}

void SpellFocusInfo::SetSpellFocusInfoOn()
{
	SpellTexture->On();

	FocusInfo1_->On();
	FocusInfo2_->On();
	FocusInfo3_->On();
	KeyTexture->On();
	
}

void SpellFocusInfo::SetSpellFocusInfoOff()
{
	SpellTexture->Off();

	FocusInfo1_->Off();
	FocusInfo2_->Off();
	FocusInfo3_->Off();
	KeyTexture->Off();

}

void SpellFocusInfo::SpellFocusInfoIdleStart(const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoIdleEnd(const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOnDialougueStart(const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOnDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOnDialougueEnd(const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOffDialougueStart(const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOffDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SpellFocusInfo::SpellFocusInfoOffDialougueEnd(const StateInfo& _Info)
{
}
