#include "PreCompile.h"
#include "MapSmokeMaker.h"

#include "MapSmoke.h"

MapSmokeMaker::MapSmokeMaker() 
{
}

MapSmokeMaker::~MapSmokeMaker() 
{
}

void MapSmokeMaker::Start()
{
	for (int i = 0; i < 20; ++i)
	{
		/*MapSmoke* MapSmoke_ = */GetLevel()->CreateActor<MapSmoke>();
	}

}

void MapSmokeMaker::Update(float _DeltaTime)
{

	if (GetAccTime() > 1.0f)
	{
		ReSetAccTime();
		/*MapSmoke* MapSmoke_ = */GetLevel()->CreateActor<MapSmoke>();
	}
}

