#include "PreCompile.h"
#include "GrimmFire.h"

#include <GameEngineBase/GameEngineRandom.h>



GrimmFire::GrimmFire()
	:
	CreateTimer_(0.f)
{
}

GrimmFire::~GrimmFire() 
{
}

void GrimmFire::Start()
{
	{
		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", 0, 7, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		MainRenderer_->SetScaleModeImage();
	}

	
	{

		std::vector<unsigned int>CustomAni;

		CustomAni.push_back(1);
		CustomAni.push_back(2);
		CustomAni.push_back(3);
		CustomAni.push_back(4);
		CustomAni.push_back(5);
		CustomAni.push_back(6);
		CustomAni.push_back(7);
		CustomAni.push_back(0);

		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		MainRenderer_->SetScaleModeImage();
	}

	{
		std::vector<unsigned int>CustomAni;
		CustomAni.push_back(7);
		CustomAni.push_back(0);

		CustomAni.push_back(1);
		CustomAni.push_back(2);
		CustomAni.push_back(3);
		CustomAni.push_back(4);
		CustomAni.push_back(5);
		CustomAni.push_back(6);




		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		MainRenderer_->ScaleToCutTexture(0);
		//MainRenderer_->SetScaleModeImage();
	}

	GrimmFireBallSpectrumActor* GrimmFireBallSpectrumActor_ = GetLevel()->CreateActor< GrimmFireBallSpectrumActor>();
	//GrimmFireBallSpectrumActor_->SetParent(this);
	GrimmFireBallSpectrumActor_->GetTransform().SetLocalPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	AllSpecturumActor_.push_back(GrimmFireBallSpectrumActor_);

	CreateTimer_ = 0.0f;
}

void GrimmFire::Update(float _DeltaTime)
{
	CreateTimer_ += _DeltaTime;
	GetTransform().SetWorldMove(MovePos_ * _DeltaTime * 400.f);

	if (CreateTimer_ > 0.1f /*&& Count_ < 7*/)
	{
		GrimmFireBallSpectrumActor* GrimmFireBallSpectrumActor_ = GetLevel()->CreateActor< GrimmFireBallSpectrumActor>();
		//GrimmFireBallSpectrumActor_->SetParent(this);
		GrimmFireBallSpectrumActor_->GetTransform().SetLocalPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y  });
		AllSpecturumActor_.push_back(GrimmFireBallSpectrumActor_);
		++Count_;
		CreateTimer_ = 0.0f;
	}

	if (GetAccTime() > 5.0f)
	{
		for (int i = 0; i < AllSpecturumActor_.size(); ++i)
		{
			if (AllSpecturumActor_[i] != nullptr)
			{
				AllSpecturumActor_[i]->Death();

			}
			//
		}
		this->Death();
	}

}
void GrimmFire::SetMoveDir(float4 _Dir)
{
	MovePos_ = _Dir;
}


