#include "PreCompile.h"
#include "MapCameraManager.h"
#include "HollowKnightLevel.h"

MapCameraManager::MapCameraManager() 
	:
	WideSpeed_(0.f)
{
}

MapCameraManager::~MapCameraManager() 
{
}

void MapCameraManager::Start()
{
	//GetLevel<HollowKnightLevel>()->GetMapCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);




	CameraStateManager_.CreateStateMember("WIDE"
		, std::bind(&MapCameraManager::WideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MapCameraManager::WideStart, this, std::placeholders::_1)
		, std::bind(&MapCameraManager::WideEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("NARROW"
		, std::bind(&MapCameraManager::NarrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MapCameraManager::NarrowStart, this, std::placeholders::_1)
		, std::bind(&MapCameraManager::NarrowEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("IDLE"
		, std::bind(&MapCameraManager::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MapCameraManager::IdleStart, this, std::placeholders::_1)
		, std::bind(&MapCameraManager::IdleEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("WIDE_IDLE"
		, std::bind(&MapCameraManager::WideIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MapCameraManager::WideIdleStart, this, std::placeholders::_1)
		, std::bind(&MapCameraManager::WideIdleEnd, this, std::placeholders::_1));

	CameraStateManager_.ChangeState("IDLE");

	WideSpeed_ = 1600.f;
}

void MapCameraManager::Update(float _DeltaTime)
{
	CameraStateManager_.Update(_DeltaTime);
}

void MapCameraManager::LevelStartEvent()
{
}

void MapCameraManager::LevelEndEvent()
{
}

void MapCameraManager::WideStart(const StateInfo& _Info)
{
}

void MapCameraManager::WideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Move = float4::FORWARD * WideSpeed_ * _DeltaTime;

	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalMove({
	0
	,0
	, Move.z });

	float4 Dest = { 0,0,-1000 };

	if (GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().GetLocalPosition().z > Dest.z)
	{
		CameraStateManager_.ChangeState("WIDE_IDLE");

	}

}

void MapCameraManager::WideEnd(const StateInfo& _Info)
{
}
void MapCameraManager::WideIdleStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalPosition({
	0
	,0
	, -1000 });
}

void MapCameraManager::WideIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MapSize = {300, 200};
	float4 MapCameraPos = GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().GetWorldPosition();


	//카메라의 위치 - 윈도우 사이즈의 x가 0이라면
	if (-MapSize.x > MapCameraPos.x )
	{
		MapCameraPos.x = -MapSize.x;
		GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldPosition(MapCameraPos);
	}

	if (MapSize.x < MapCameraPos.x)
	{
		MapCameraPos.x = MapSize.x ;
		GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldPosition(MapCameraPos);
	}

	if (MapSize.y < MapCameraPos.y )
	{
		MapCameraPos.y = MapSize.y;
		GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldPosition(MapCameraPos);
	}

	if (-MapSize.y > MapCameraPos.y )
	{
		MapCameraPos.y = -(MapSize.y);
		GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldPosition(MapCameraPos);
	}
}

void MapCameraManager::WideIdleEnd(const StateInfo& _Info)
{
}
void MapCameraManager::NarrowStart(const StateInfo& _Info)
{
}

void MapCameraManager::NarrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Move = float4::BACK * WideSpeed_ * _DeltaTime;

	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalMove({
	0
	,0
	, Move.z });

	float4 Dest = { 0,0,-2000 };

	if (GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().GetLocalPosition().z < Dest.z)
	{
		CameraStateManager_.ChangeState("IDLE");

	}

}

void MapCameraManager::NarrowEnd(const StateInfo& _Info)
{
}

void MapCameraManager::IdleStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetLocalPosition({
	0
	,0
	, -2000 });

	GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->Off();

}

void MapCameraManager::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void MapCameraManager::IdleEnd(const StateInfo& _Info)
{
}




void MapCameraManager::SetMapMoveRight()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldRightMove(300.f, GameEngineTime::GetInst()->GetDeltaTime());
}
void MapCameraManager::SetMapMoveLeft()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldLeftMove(300.f, GameEngineTime::GetInst()->GetDeltaTime());

}
void MapCameraManager::SetMapMoveTop()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldUpMove(300.f, GameEngineTime::GetInst()->GetDeltaTime());

}
void MapCameraManager::SetMapMoveDown()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraActorTransform().SetWorldDownMove(300.f, GameEngineTime::GetInst()->GetDeltaTime());

}



void MapCameraManager::SetMapCameraWide()
{
	CameraStateManager_.ChangeState("WIDE");
}

void MapCameraManager::SetMapCameraNarrow()
{
	CameraStateManager_.ChangeState("NARROW");

}