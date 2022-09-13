#include "PreCompile.h"
#include "MainCameraManager.h"
#include "HollowKnightLevel.h"

MainCameraManager::MainCameraManager() 
	:
	max_skew(5.00f),
	max_sway(16.00f),
	seed(0),
	seed_shifting_factor(3.00f)
{
}

MainCameraManager::~MainCameraManager() 
{
}

void MainCameraManager::Start()
{
	CameraStateManager_.CreateStateMember("MOVE_TO_TARGET"
		, std::bind(&MainCameraManager::MoveToTargetUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::MoveToTargetStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::MoveToTargetEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("SHAKING"
		, std::bind(&MainCameraManager::ShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::ShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::ShakingEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("RETURN_TO_TARGET"
		, std::bind(&MainCameraManager::ShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::ShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::ShakingEnd, this, std::placeholders::_1));


	CameraStateManager_.ChangeState("MOVE_TO_TARGET");
}

void MainCameraManager::Update(float _DeltaTime)
{
	CameraStateManager_.Update(_DeltaTime);
}


void MainCameraManager::MainCameraMoveLimitWindow(float4 _TargetPos, float4 _MapSize)
{

}

void MainCameraManager::ChangeCameraMove(CameraMode _Mode)
{
	switch (_Mode)
	{
	case CameraMode::TargetMove:
		CameraStateManager_.ChangeState("MOVE_TO_TARGET");



		break;
	case CameraMode::Shaking:

		CameraStateManager_.ChangeState("SHAKING");

		break;
	default:
		break;
	}
}

void MainCameraManager::MoveToTargetStart(const StateInfo& _Info)
{
}

void MainCameraManager::MoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//카메라가 없다면
	if (GetLevel()->GetMainCameraActor() == nullptr)
	{
		return;
	}

	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();
	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 10.f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ MoveCamera.x,MoveCamera.y,  -1800.0f });
	float4 MainCameraPosition = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	//카메라의 위치 - 윈도우 사이즈의 x가 0이라면
	if (0 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (MapSize.x < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = MapSize.x - GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (0 < MainCameraPosition.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (-MapSize.y > MainCameraPosition.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = -(MapSize.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}
}

void MainCameraManager::MoveToTargetEnd(const StateInfo& _Info)
{
}

void MainCameraManager::ShakingStart(const StateInfo& _Info)
{
}

void MainCameraManager::ShakingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	seed += _DeltaTime;
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * seed_shifting_factor, seed * seed_shifting_factor, 0)) - 1.0f;

	float4 ShakePosition = { shake * max_sway/GameEngineWindow::GetInst()->GetScale().x , shake * max_sway/ GameEngineWindow::GetInst()->GetScale().y};

	GetLevel()->GetMainCameraActorTransform().SetWorldMove(ShakePosition);

}

void MainCameraManager::ShakingEnd(const StateInfo& _Info)
{
}

void MainCameraManager::ReturnToTargetStart(const StateInfo& _Info)
{
}

void MainCameraManager::ReturnToTargetUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MainCameraManager::ReturnToTargetEnd(const StateInfo& _Info)
{
}

