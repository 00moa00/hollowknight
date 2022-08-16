#include "PreCompile.h"
#include "TitleLevel.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

TitleLevel::TitleLevel()
	:
	Background_(nullptr),
	LogoRenderer_(nullptr)
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

	LogoRenderer_ = CreateActor<RendererActor>();
	LogoRenderer_->CreateRenderer("TitleLogo.png");
	//LogoRenderer_->GetTransform().SetLocalPosition({0, 0 });
	LogoRenderer_->GetRenderer()->GetTransform().SetLocalPosition({0, 200, 0});


	MasterTitleUI_ = CreateActor<AllTitleUI>();
	//MasterTitleUI_->GetTransform().SetLocalPosition({ 0, 200, 0 });

	
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("KingsPassLevel1");
	}
}

void TitleLevel::End()
{
}