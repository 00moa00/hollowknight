#include "PreCompile.h"
#include "SpellScreamInfo.h"

SpellScreamInfo::SpellScreamInfo() 
	:
	SpellTexture(nullptr),
	DividerTexture(nullptr),
	SpellName_(nullptr),
	SpellInfo_(nullptr),
	BackTexture(nullptr),
	FadeOut_(nullptr),

	SpellAlpha_(0.f),
	DividerAlpha_(0.f),
	NameAlpha_(0.f),
	InfoAlpha_(0.f)
{
}

SpellScreamInfo::~SpellScreamInfo() 
{
}

void SpellScreamInfo::Start()
{
	BackTexture = CreateComponent<GameEngineUIRenderer>();
	BackTexture->SetTexture("Black.png");
	BackTexture->GetTransform().SetLocalScale(BackTexture->GetCurTexture()->GetScale());
	BackTexture->GetTransform().SetLocalPosition({ 0, 0 });

	SpellName_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	SpellName_->CreateFontRenderer(
		"울부짖는 원혼들"
		, 55
		, { GameEngineWindow::GetInst()->GetScale().hx() , GameEngineWindow::GetInst()->GetScale().hy() + 50.f },
		false,
		false
	);

	//SpellName_->Off();
	SpellName_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	SpellName_->GetFontRenderer()->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });





	SpellInfo_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	SpellInfo_->CreateFontRenderer(
		"위 방향과 함께 누르면 원혼들을 풀어줍니다.\n\n주문은 영혼을 고갈시킵니다.\n적을 공격하여 영혼을 보충하십시오."
		, 30
		, { GameEngineWindow::GetInst()->GetScale().hx() , GameEngineWindow::GetInst()->GetScale().hy() + 150.f },
		false,
		false
	);

	//SpellInfo_->Off();
	SpellInfo_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	SpellInfo_->GetFontRenderer()->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });



	SpellTexture = CreateComponent<GameEngineUIRenderer>();
	SpellTexture->SetTexture("_0006_scream_spell.png");
	SpellTexture->GetTransform().SetLocalScale(SpellTexture->GetCurTexture()->GetScale());
	SpellTexture->GetTransform().SetLocalPosition({ 0, 280 });
	SpellTexture->GetPixelData().MulColor.a = 0.f;

	//SpellTexture->Off();

	DividerTexture = CreateComponent<GameEngineUIRenderer>();
	DividerTexture->SetTexture("prompt_divider.png");
	DividerTexture->GetTransform().SetLocalScale(DividerTexture->GetCurTexture()->GetScale());
	DividerTexture->GetTransform().SetLocalPosition({ 0, 10 });
	DividerTexture->GetPixelData().MulColor.a = 0.f;
}

void SpellScreamInfo::Update(float _DeltaTime)
{
	SpellAlpha_ += 0.7f * _DeltaTime;
	if (SpellAlpha_ >= 1.0f)
	{
		SpellAlpha_ = 1.f;
	}

	SpellTexture->GetPixelData().MulColor.a = SpellAlpha_;

	if (GetAccTime() > 1.f)
	{
		NameAlpha_ += 0.7f * _DeltaTime;
		if (NameAlpha_ >= 1.0f)
		{
			NameAlpha_ = 1.f;
		}

		SpellName_->GetFontRenderer()->SetColor({ 1.0f, 1.0f, 1.0f, NameAlpha_ });
	}

	if (GetAccTime() > 1.5f)
	{
		DividerAlpha_ += 0.7f * _DeltaTime;
		if (DividerAlpha_ >= 1.0f)
		{
			DividerAlpha_ = 1.f;
		}

		DividerTexture->GetPixelData().MulColor.a = DividerAlpha_;
	}

	if (GetAccTime() > 2.f)
	{
		InfoAlpha_ += 0.7f * _DeltaTime;
		if (InfoAlpha_ >= 1.0f)
		{
			InfoAlpha_ = 1.f;
		}

		SpellInfo_->GetFontRenderer()->SetColor({ 1.0f, 1.0f, 1.0f, InfoAlpha_ });
	}

	if (GetAccTime() > 3.8f)
	{
		if (FadeOut_ == nullptr)
		{
			FadeOut_ = GetLevel()->CreateActor<FadeOut>();
		}

		if (FadeOut_ != nullptr)
		{
			if (FadeOut_->GetDeathflag() == true)
			{
				GEngine::ChangeLevel("DirtmouthLevel1");

			}
		}

	}
}

void SpellScreamInfo::End()
{
}

void SpellScreamInfo::LevelStartEvent()
{
}

void SpellScreamInfo::LevelEndEvent()
{
	if (FadeOut_ != nullptr)
	{
		if (FadeOut_->GetDeathflag() == true)
		{
			FadeOut_->Death();
			FadeOut_ = nullptr;
		}
	}
}
