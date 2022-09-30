#include "PreCompile.h"
#include "TitleLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "TitleCircleParticle.h"

TitleLevel::TitleLevel()
	:
	Background_(nullptr),
	LogoRenderer_(nullptr),
	MasterTitleUI_(nullptr)
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	Background_ = CreateActor<RendererActor>();
	Background_->CreateRenderer("Title.png");
	Background_->GetTransform().SetWorldPosition({0,0,50});

	LogoRenderer_ = CreateActor<RendererActor>();
	LogoRenderer_->CreateRenderer("TitleLogo.png");
	//LogoRenderer_->GetTransform().SetLocalPosition({0, 0 });
	LogoRenderer_->GetRenderer()->GetTransform().SetLocalPosition({0, 200, 0});


	MasterTitleUI_ = CreateActor<AllTitleUI>();
	//MasterTitleUI_->GetTransform().SetLocalPosition({ 0, 200, 0 });

	
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GetAccTime() > 0.5f)
	{
		TitleCircleParticle* TitleCircleParticle_ = CreateActor<TitleCircleParticle>();
		TitleCircleParticle_->GetTransform().SetWorldPosition({ GameEngineRandom::MainRandom.RandomFloat(-GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hx())
			, -GameEngineWindow::GetInst()->GetScale().hy(),10});

		ReSetAccTime();
	}
}

void TitleLevel::End()
{
}