#include "PreCompile.h"
#include "ForgottenCrossroadMap.h"

#include <sstream>

ForgottenCrossroadMap::ForgottenCrossroadMap() 
{
}

ForgottenCrossroadMap::~ForgottenCrossroadMap() 
{
}

void ForgottenCrossroadMap::Start()
{

	MapPosition_.push_back({ -218, 200, -1000 });
	MapPosition_.push_back({ -72, 200, -1000 });
	MapPosition_.push_back({ 96, 34, -1000 });
	MapPosition_.push_back({ 267, -116, -1000 });
	MapPosition_.push_back({ -233, 127 , -1000 });
	MapPosition_.push_back({ -258, 49 , -1000 });
	MapPosition_.push_back({ -328, 123, -1000 });
	MapPosition_.push_back({ -252, -38, -1000 });
	MapPosition_.push_back({ -149, 20 , -1000 });
	MapPosition_.push_back({ -165, 49 , -1000 });
	MapPosition_.push_back({ -479, 111 , -1000 });
	MapPosition_.push_back({ -422, -30 , -1000 });
	MapPosition_.push_back({ -143, -55 , -1000 });
	MapPosition_.push_back({ 156, 157 , -1000 });
	MapPosition_.push_back({ 174, 29, -1000 });
	MapPosition_.push_back({ 56, 131 , -1000 });
	MapPosition_.push_back({ 206, 72, -1000 });
	MapPosition_.push_back({ -327, -76, -1000 });
	MapPosition_.push_back({ 101, -75, -1000 });
	MapPosition_.push_back({ 270, -127 , -1000 });
	MapPosition_.push_back({ -20, 26 , -1000 });
	MapPosition_.push_back({ -31, 75 , -1000 });
	MapPosition_.push_back({ -326, -111, -1000 });
	MapPosition_.push_back({ -53, 36 , -1000 });
	MapPosition_.push_back({ -420, 70 , -1000 });
	MapPosition_.push_back({ -273, -109, -1000 });
	MapPosition_.push_back({ 248, -26 , -1000 });
	MapPosition_.push_back({ -171, -17 , -1000 });
	MapPosition_.push_back({ 177, -17, -1000 });
	MapPosition_.push_back({ -330, 3 , -1000 });
	MapPosition_.push_back({ -541, -45, -1000 });
	MapPosition_.push_back({ -507, 35 , -1000 });
	MapPosition_.push_back({ -182, -91 , -1000 });
	MapPosition_.push_back({ -417, 188 , -1000 });
	MapPosition_.push_back({ 60, 191 , -1000 });
	MapPosition_.push_back({ -92, 129 , -1000 });
	MapPosition_.push_back({ -12, -52 , -1000 });
	MapPosition_.push_back({ -11, -90 , -1000 });
	MapPosition_.push_back({ 240, 134 , -1000 });
	MapPosition_.push_back({ 367, -42, -1000 });
	MapPosition_.push_back({ 636, -173 , -1000 });
	MapPosition_.push_back({ 40, -15, -1000 });
	MapPosition_.push_back({ 226, 192 , -1000 });
	MapPosition_.push_back({ -103, -166 , -1000 });
	MapPosition_.push_back({ 630, -286 , -1000 });



	for (int i = 1; i < 46; ++i)
	{
		ForgottenCrossroadMap_.insert({ i, GetLevel()->CreateActor<Map>() });
		std::stringstream ssInt;
		ssInt << i;

		ForgottenCrossroadMap_[i]->CreateRendererComponent("Crossroads_" + ssInt.str() + ".png");
		ForgottenCrossroadMap_[i]->GetTransform().SetWorldPosition(MapPosition_[i-1]);
	}
}

void ForgottenCrossroadMap::Update(float _DeltaTime)
{
}

