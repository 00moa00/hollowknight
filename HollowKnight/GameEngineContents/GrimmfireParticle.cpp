#include "PreCompile.h"
#include "GrimmFireBallSpectrum.h"
#include "GrimmfireParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmfireParticle::GrimmfireParticle() 
{
}

GrimmfireParticle::~GrimmfireParticle() 
{
}

void GrimmfireParticle::Start()
{
	{

	}


}

void GrimmfireParticle::Update(float _DeltaTime)
{

	if (GetAccTime() > 0.5f)
	{

		ReSetAccTime();
		GrimmFireBallSpectrum* GrimmFireBallSpectrum_ = GetLevel()->CreateActor<GrimmFireBallSpectrum>();
		//GrimmFireBallSpectrum_->SetParent(this);

		GrimmFireBallSpectrum_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
		GrimmFireBallSpectrum_->GetTransform().SetWorldMove({ GameEngineRandom::MainRandom.RandomFloat(-10,10) , GameEngineRandom::MainRandom.RandomFloat(-10,10) });
	}
	
}

