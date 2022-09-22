#include "PreCompile.h"
#include "GrimmFireBallSpectrumActor.h"


#include <GameEngineBase/GameEngineRandom.h>
GrimmFireBallSpectrumActor::GrimmFireBallSpectrumActor() 
{
}

GrimmFireBallSpectrumActor::~GrimmFireBallSpectrumActor() 
{
}

void GrimmFireBallSpectrumActor::Start()
{

	//GrimmFireBallSpectrum* GrimmFireBallSpectrum_ = GetLevel()->CreateActor<GrimmFireBallSpectrum>();
	//GrimmFireBallSpectrum_->SetParent(this);

	////GrimmFireBallSpectrum_->GetTransform().SetLocalPosition(this->GetTransform().GetWorldPosition());
	//GrimmFireBallSpectrum_->GetTransform().SetLocalMove({ GameEngineRandom::MainRandom.RandomFloat(-15,15), GameEngineRandom::MainRandom.RandomFloat(-15,15) });
	//GrimmFireBallSpectrum_->GetTransform().SetWorldRotation({ 0,0,  GameEngineRandom::MainRandom.RandomFloat(-30,30) });

	//AllFireSpectrum_.push_back(GrimmFireBallSpectrum_);
	//++Count_;
}

void GrimmFireBallSpectrumActor::Update(float _DeltaTime)
{
	CreateTimer_ += _DeltaTime;
	if (CreateTimer_ > 0.01f && Count_ < 10)
	{
		CreateTimer_ = 0.0f;

		if (Count_ == 10)
		{
			ReSetAccTime();
		}
		else
		{
			GrimmFireBallSpectrum* GrimmFireBallSpectrum_ = GetLevel()->CreateActor<GrimmFireBallSpectrum>();
			GrimmFireBallSpectrum_->SetParent(this);

			GrimmFireBallSpectrum_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
			GrimmFireBallSpectrum_->GetRenderer()->GetTransform().SetLocalMove({ GameEngineRandom::MainRandom.RandomFloat(-15,15), GameEngineRandom::MainRandom.RandomFloat(-25,25)});
			GrimmFireBallSpectrum_->GetRenderer()->GetTransform().SetWorldRotation({ 0,0,  GameEngineRandom::MainRandom.RandomFloat(-30,30) });

			AllFireSpectrum_.push_back(GrimmFireBallSpectrum_);
			++Count_;
		}


	
}

	if (GetAccTime() > 0.7f && Count_ >= 10)
	{
		for (int i = 0; i < AllFireSpectrum_.size(); ++i)
		{
			if (AllFireSpectrum_[i] != nullptr)
			{
				AllFireSpectrum_[i]->Death(0);

			}
		}


		Death();
		return;
	}

}

