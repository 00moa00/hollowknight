#include "PreCompile.h"
#include "ForgottenCrossroadMap.h"
#include "HollowKnightLevel.h"

#include <sstream>

ForgottenCrossroadMap::ForgottenCrossroadMap() 
{
}

ForgottenCrossroadMap::~ForgottenCrossroadMap() 
{
}

void ForgottenCrossroadMap::Start()
{

	MapPosition_.push_back({ -219, 200, -10 });
	MapPosition_.push_back({ -73, 199, -10 });
	MapPosition_.push_back({ 96, 34, -10 });
	MapPosition_.push_back({ 267, -116, -10 });
	MapPosition_.push_back({ -233, 127 , -10 });
	MapPosition_.push_back({ -258, 49 , -10 });
	MapPosition_.push_back({ -329, 123, -10 });
	MapPosition_.push_back({ -252, -38, -10 });
	MapPosition_.push_back({ -417, 20 , -10 });
	MapPosition_.push_back({ -165, 49 , -10 });
	MapPosition_.push_back({ -479, 115 , -10 });
	MapPosition_.push_back({ -422, -30 , -10 });
	MapPosition_.push_back({ -143, -55 , -10 });
	MapPosition_.push_back({ 154, 159 , -10 });
	MapPosition_.push_back({ 174, 29, -10 });
	MapPosition_.push_back({ 56, 131 , -10 });
	MapPosition_.push_back({ 208, 66, -10 });
	MapPosition_.push_back({ -327, -76, -10 });
	MapPosition_.push_back({ 101, -75, -10 });
	MapPosition_.push_back({ 270, -127 , -10 });
	MapPosition_.push_back({ -20, 26 , -10 });
	MapPosition_.push_back({ -31, 77 , -10 });
	MapPosition_.push_back({ -326, -111, -10 });
	MapPosition_.push_back({ -53, 36 , -10 });
	MapPosition_.push_back({ -420, 70 , -10 });
	MapPosition_.push_back({ -273, -109, -10 });
	MapPosition_.push_back({ 248, -26 , -10 });
	MapPosition_.push_back({ -171, -17 , -10 });
	MapPosition_.push_back({ 177, -17, -10 });
	MapPosition_.push_back({ -330, 3 , -10 });
	MapPosition_.push_back({ -541, -45, -10 });
	MapPosition_.push_back({ -507, 35 , -10 });
	MapPosition_.push_back({ -182, -91 , -10 });
	MapPosition_.push_back({ -417, 188 , -10 });
	MapPosition_.push_back({ 58, 191 , -10 });
	MapPosition_.push_back({ -92, 129 , -10 });
	MapPosition_.push_back({ -12, -52 , -10 });
	MapPosition_.push_back({ -11, -90 , -10 });
	MapPosition_.push_back({ 239, 133 , -10 });
	MapPosition_.push_back({ 367, -42, -10 });
	MapPosition_.push_back({ 636, -173 , -10 });
	MapPosition_.push_back({ 40, -15, -10 });
	MapPosition_.push_back({ 226, 192 , -10 });
	MapPosition_.push_back({ -103, -166 , -10 });
	//MapPosition_.push_back({ 630, -286 , -1000 });

	for (int i = 1; i < 45; ++i)
	{
		ForgottenCrossroadMap_.insert({ i, GetLevel()->CreateActor<Map>() });
		std::stringstream ssInt;
		ssInt << i;

		ForgottenCrossroadMap_[i]->CreateRendererComponent("Crossroads_" + ssInt.str() + ".png");
		ForgottenCrossroadMap_[i]->GetTransform().SetWorldPosition(MapPosition_[i-1]);
		ForgottenCrossroadMap_[i]->SetParent(this);
		ForgottenCrossroadMap_[i]->GetRenderer()->GetPixelData().MulColor.r = 0.4f;
		ForgottenCrossroadMap_[i]->GetRenderer()->GetPixelData().MulColor.g = 0.5f;
		ForgottenCrossroadMap_[i]->GetRenderer()->GetPixelData().MulColor.b = 0.7f;
		//ForgottenCrossroadMap_[i]->GetRenderer()->GetPixelData().MulColor.a = 0.3f;

	}

	this->Off();
}

void ForgottenCrossroadMap::Update(float _DeltaTime)
{
	//GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalPosition({0, 0, -2000.f});
}

//void ForgottenCrossroadMap::MapOn()
//{
//	On();
//	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraWide();
//}
//
//void ForgottenCrossroadMap::MapOff()
//{
//	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraNarrow();
//}
//
