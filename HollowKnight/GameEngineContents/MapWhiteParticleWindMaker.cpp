#include "PreCompile.h"
#include "MapWhiteParticleWindMaker.h"
#include "MapWhitParticle.h"
MapWhiteParticleWindMaker::MapWhiteParticleWindMaker() 
{
}

MapWhiteParticleWindMaker::~MapWhiteParticleWindMaker() 
{
}

void MapWhiteParticleWindMaker::Start()
{
	for (int i = 0; i < 100; ++i)
	{
		MapWhitParticle* MapWhitParticle_ = GetLevel()->CreateActor<MapWhitParticle>();
		MapWhitParticle_->SetWindMove();
	}
}

void MapWhiteParticleWindMaker::Update(float _DeltaTime)
{
	if (GetAccTime() > 5.0f)
	{
		ReSetAccTime();
		for (int i = 0; i < 30; ++i)
		{
			MapWhitParticle* MapWhitParticle_ = GetLevel()->CreateActor<MapWhitParticle>();
			MapWhitParticle_->SetWindMove();
		}
	}
}

