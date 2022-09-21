#include "PreCompile.h"
#include "GrimmFireBallSpectrumActor.h"
#include "GrimmFireBallSpectrum.h"


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
	UpdateTimer_ += _DeltaTime;
	CreateTimer_ += _DeltaTime;
	if (CreateTimer_ > 0.1f)
	{
		CreateTimer_ = 0.0f;
		GrimmFireBallSpectrum* GrimmFireBallSpectrum_ = GetLevel()->CreateActor<GrimmFireBallSpectrum>();
		GrimmFireBallSpectrum_->SetParent(this);

		GrimmFireBallSpectrum_->GetTransform().SetLocalPosition(this->GetTransform().GetWorldPosition());
		GrimmFireBallSpectrum_->GetTransform().SetLocalMove({ GameEngineRandom::MainRandom.RandomFloat(-10,10) +50.f, GameEngineRandom::MainRandom.RandomFloat(-10,10) });
	
	
	
}

	if (UpdateTimer_ > 5.0f)
	{
		Death();
	}

}

