#include "PreCompile.h"
#include "TitleLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "TitleCircleParticle.h"
#include "TitleSmokeParticle.h"
#include "VignettePostEffect.h"
#include "TitleWhitePartlcle.h"
#include "KnightSoundManager.h"

TitleLevel::TitleLevel()
	:
	CircleParticleCreateTimer_(0.f),
	SmokeParticleCreateTimer_(0.f),
	WhiteParticleCreateTimer_(0.f),

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
	LogoRenderer_->GetRenderer()->ChangeCamera(CAMERAORDER::UICAMERA);
	//LogoRenderer_->GetTransform().SetLocalPosition({0, 0 });
	LogoRenderer_->GetRenderer()->GetTransform().SetLocalPosition({0, 200, 0});


	MasterTitleUI_ = CreateActor<AllTitleUI>();
	//MasterTitleUI_->GetTransform().SetLocalPosition({ 0, 200, 0 });

	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();
	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}


	{
		TitleCircleParticle* TitleCircleParticle_ = CreateActor<TitleCircleParticle>();
		TitleCircleParticle_->GetTransform().SetWorldPosition({ GameEngineRandom::MainRandom.RandomFloat(-GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hx())
			, -GameEngineWindow::GetInst()->GetScale().hy(),10 });
	}

	{
		TitleSmokeParticle* TitleSmokeParticle_ = CreateActor<TitleSmokeParticle>();
		TitleSmokeParticle_->GetTransform().SetWorldPosition({ GameEngineRandom::MainRandom.RandomFloat(-GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hx())
			, -(GameEngineWindow::GetInst()->GetScale().hy() + 150),10 });

	}

	{
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}

	KnightSoundManager::GetInst()->BgmOn("Title.ogg", 5);

}

void TitleLevel::Update(float _DeltaTime)
{
	SmokeParticleCreateTimer_ += _DeltaTime;
	CircleParticleCreateTimer_ += _DeltaTime;
	WhiteParticleCreateTimer_ += _DeltaTime;

	if (CircleParticleCreateTimer_ >= 0.6f)
	{
		TitleCircleParticle* TitleCircleParticle_ = CreateActor<TitleCircleParticle>();
		TitleCircleParticle_->GetTransform().SetWorldPosition({ GameEngineRandom::MainRandom.RandomFloat(-GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hx())
			, -GameEngineWindow::GetInst()->GetScale().hy(),10});

		CircleParticleCreateTimer_ = 0.f;
	}

	if (SmokeParticleCreateTimer_ >= 0.8f)
	{
		TitleSmokeParticle* TitleSmokeParticle_ = CreateActor<TitleSmokeParticle>();
		TitleSmokeParticle_->GetTransform().SetWorldPosition({ GameEngineRandom::MainRandom.RandomFloat(-GameEngineWindow::GetInst()->GetScale().hx(), GameEngineWindow::GetInst()->GetScale().hx())
			, -(GameEngineWindow::GetInst()->GetScale().hy() + 150 ),10 });


		SmokeParticleCreateTimer_ = 0.f;
	}


	if (WhiteParticleCreateTimer_ >= 0.8f)
	{
		WhiteParticleCreateTimer_ = 0.f;

		
		TitleWhitePartlcle* TitleWhitePartlcle_ = CreateActor<TitleWhitePartlcle>();
		TitleWhitePartlcle_->GetTransform().SetWorldPosition({ LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().x + (GameEngineRandom::MainRandom.RandomFloat(-600.f, 600.f)),
			 LogoRenderer_->GetRenderer()->GetTransform().GetLocalPosition().y + (GameEngineRandom::MainRandom.RandomFloat(-150.f, 150.f)) });
	}


}

void TitleLevel::End()
{
}