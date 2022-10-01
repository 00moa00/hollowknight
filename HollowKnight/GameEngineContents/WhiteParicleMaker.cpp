#include "PreCompile.h"

#include "WhiteParicleMaker.h"
#include "MapWhitParticle.h"

WhiteParicleMaker::WhiteParicleMaker() 
{
}

WhiteParicleMaker::~WhiteParicleMaker() 
{
}

void WhiteParicleMaker::Start()
{
	for (int i = 0; i < 150; ++i)
	{
		GetLevel()->CreateActor<MapWhitParticle>();

	}

}

void WhiteParicleMaker::Update(float _DeltaTime)
{
	if (GetAccTime() > 6.0f)
	{
		ReSetAccTime();
		for (int i = 0; i < 30; ++i)
		{
			GetLevel()->CreateActor<MapWhitParticle>();

		}
	}
}

