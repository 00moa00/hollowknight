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

	MapPosition_.push_back({ -218, 200,0 });
	MapPosition_.push_back({ -72, 200,0 });
	MapPosition_.push_back({ 96, 34, -10 });
	MapPosition_.push_back({ 267, -116, -10 });
	MapPosition_.push_back({ -233, 127 , -10 });
	MapPosition_.push_back({ -258, 49 , -10 });
	MapPosition_.push_back({ -328, 123, -10 });
	MapPosition_.push_back({ -252, -38, -10 });
	MapPosition_.push_back({ -419, 20 , -10 });
	MapPosition_.push_back({ -165, 49 , -10 });
	MapPosition_.push_back({ -479, 111 , -10 });
	MapPosition_.push_back({ -422, -30 , -10 });
	MapPosition_.push_back({ -143, -55 , -10 });
	MapPosition_.push_back({ 156, 157 , -10 });
	MapPosition_.push_back({ 174, 29, -10 });
	MapPosition_.push_back({ 56, 131 , -10 });
	MapPosition_.push_back({ 206, 72, -10 });
	MapPosition_.push_back({ -327, -76, -10 });
	MapPosition_.push_back({ 101, -75, -10 });
	MapPosition_.push_back({ 270, -127 , -10 });
	MapPosition_.push_back({ -20, 26 , -10 });
	MapPosition_.push_back({ -31, 75 , -10 });
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
	MapPosition_.push_back({ 60, 191 , -10 });
	MapPosition_.push_back({ -92, 129 , -10 });
	MapPosition_.push_back({ -12, -52 , -10 });
	MapPosition_.push_back({ -11, -90 , -10 });
	MapPosition_.push_back({ 240, 134 , -10 });
	MapPosition_.push_back({ 367, -42, -10 });
	MapPosition_.push_back({ 636, -173 , -10 });
	MapPosition_.push_back({ 40, -15, -10 });
	MapPosition_.push_back({ 226, 192 , -10 });
	MapPosition_.push_back({ -103, -166 , -10 });
	//MapPosition_.push_back({ 630, -286 , -1000 });

		//================================
	//    CreateKey
	//================================

	if (false == GameEngineInput::GetInst()->IsKey("MapMoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MapMoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MapMoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MapMoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MapMoveDown", VK_DOWN);
	}

	for (int i = 1; i < 45; ++i)
	{
		ForgottenCrossroadMap_.insert({ i, GetLevel()->CreateActor<Map>() });
		std::stringstream ssInt;
		ssInt << i;

		ForgottenCrossroadMap_[i]->CreateRendererComponent("Crossroads_" + ssInt.str() + ".png");
		ForgottenCrossroadMap_[i]->GetTransform().SetWorldPosition(MapPosition_[i-1]);
		ForgottenCrossroadMap_[i]->SetParent(this);
	}

	this->Off();
}

void ForgottenCrossroadMap::Update(float _DeltaTime)
{
	//GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalPosition({0, 0, -2000.f});
	if (GameEngineInput::GetInst()->IsPress("MapMoveLeft") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveLeft();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveRight") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveRight();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveUp") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveTop();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveDown") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveDown();

	}

}

void ForgottenCrossroadMap::MapOn()
{
	On();
	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraWide();
}

void ForgottenCrossroadMap::MapOff()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraNarrow();
}

