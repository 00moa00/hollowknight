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


}

void GrimmFireBallSpectrumActor::Update(float _DeltaTime)
{
	CreateTimer_ += _DeltaTime;
	if (CreateTimer_ > 0.1f && Count_ < 4)
	{
		CreateTimer_ = 0.0f;

		if (Count_ == 4)
		{
			ReSetAccTime();
		}
		else
		{
			GrimmFireBallSpectrum* GrimmFireBallSpectrum_ = GetLevel()->CreateActor<GrimmFireBallSpectrum>();
			GrimmFireBallSpectrum_->SetParent(this);

			//GrimmFireBallSpectrum_->GetTransform().SetLocalPosition(this->GetTransform().GetWorldPosition());
			GrimmFireBallSpectrum_->GetTransform().SetLocalMove({ GameEngineRandom::MainRandom.RandomFloat(-15,15) + 50.f, GameEngineRandom::MainRandom.RandomFloat(-15,15) });
			GrimmFireBallSpectrum_->GetTransform().SetWorldRotation({ 0,0,  GameEngineRandom::MainRandom.RandomFloat(-30,30) });

			AllFireSpectrum_.push_back(GrimmFireBallSpectrum_);
			++Count_;
		}


	
}

	if (GetAccTime() > 6.0f && Count_ >= 4)
	{
		for (int i = 0; i < AllFireSpectrum_.size(); ++i)
		{
			AllFireSpectrum_[i]->Death(0);
		}


		Death();
		return;
	}

}

