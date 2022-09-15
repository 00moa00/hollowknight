#include "PreCompile.h"
#include "MainCameraManager.h"
#include "HollowKnightLevel.h"
#include "CameraGUI.h"
#include "KnightData.h"

MainCameraManager::MainCameraManager() 
	:
	MaxSkew(5.00f),
	MaxSway(1.5f),
	seed(0.2f),
	SeedShiftingFactor(10.00f),

	ReturnLenth_()
{

}

MainCameraManager::~MainCameraManager() 
{
}

void MainCameraManager::Start()
{
	GetLevel()->GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({
		GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
		, -1800});
	
	
	CameraStateManager_.CreateStateMember("MOVE_TO_TARGET"
		, std::bind(&MainCameraManager::MoveToTargetUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::MoveToTargetStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::MoveToTargetEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("SHAKING"
		, std::bind(&MainCameraManager::ShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::ShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::ShakingEnd, this, std::placeholders::_1));


	CameraStateManager_.CreateStateMember("FOCUS"
		, std::bind(&MainCameraManager::FocusUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::FocusStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::FocusEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("FOCUS_CANCLE"
		, std::bind(&MainCameraManager::FocusCancleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::FocusCancleStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::FocusCancleEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("FOCUS_RETURN"
		, std::bind(&MainCameraManager::FocusReturnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::FocusReturnStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::FocusReturnEnd, this, std::placeholders::_1));

	CameraStateManager_.ChangeState("MOVE_TO_TARGET");
}

void MainCameraManager::Update(float _DeltaTime)
{
	CameraStateManager_.Update(_DeltaTime);
}

void MainCameraManager::LevelStartEvent()
{
	CameraGUI_ = GameEngineGUI::CreateGUIWindow<CameraGUI>("Camera", GetLevel());

}

void MainCameraManager::LevelEndEvent()
{
	CameraGUI_->CameraGUIDeath();
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
	case CameraMode::Focus:
		CameraStateManager_.ChangeState("FOCUS");

		break;

	case CameraMode::CancleFocus:
		CameraStateManager_.ChangeState("FOCUS_CANCLE");

		break;
	case CameraMode::ReturnFocus:
		CameraStateManager_.ChangeState("FOCUS_RETURN");

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
	seed += (_DeltaTime);
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * CameraGUI_->GetSeedshiftingFactor(), seed * CameraGUI_->GetSeedshiftingFactor(), 0)) - 1.0f;
	float4 ShakePosition = { shake * CameraGUI_->GetMaxSway(), shake * CameraGUI_->GetMaxSway() };
	float4 ShakeRotation = { 0,0, shake * CameraGUI_->GetMaxSkew()};

	GetLevel()->GetMainCameraActorTransform().SetWorldMove(ShakePosition);
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation(ShakeRotation);


	float4 MainCameraPosition = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();

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

void MainCameraManager::ShakingEnd(const StateInfo& _Info)
{
}

void MainCameraManager::FocusStart(const StateInfo& _Info)
{
	;
}

void MainCameraManager::FocusUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();

	float4 CurrentPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
		, GetLevel()->GetMainCameraActorTransform().GetLocalPosition().z };

	float4 DestPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		, GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y 
		, -1700.f };

	
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 0.7f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MoveCamera);
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

void MainCameraManager::FocusEnd(const StateInfo& _Info)
{
}

void MainCameraManager::FocusReturnStart(const StateInfo& _Info)
{

	

}

void MainCameraManager::FocusReturnUpdate(float _DeltaTime, const StateInfo& _Info)
{


	seed += (_DeltaTime);
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * 5.0f, seed * 5.0f, 0)) - 1.0f;
	float4 ShakePosition = { shake * 5.f, shake * 5.f };
	float4 ShakeRotation = { 0,0, shake * 0.197f };

	GetLevel()->GetMainCameraActorTransform().SetWorldMove(ShakePosition);
	GetLevel()->GetMainCameraActorTransform().SetWorldRotation(ShakeRotation);




	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();

	float4 CurrentPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y 
		, GetLevel()->GetMainCameraActorTransform().GetLocalPosition().z };

	float4 DestPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y 
		, -1800.f };

	
	float4 Lenth = CurrentPos - DestPos;
	ReturnLenth_ = Lenth.Length();

	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.0f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MoveCamera);
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


	if (ReturnLenth_ <= 0)
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ GetLevel()->GetMainCameraActorTransform().GetWorldPosition().x, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().y , -1800.f });
		CameraStateManager_.ChangeState("MOVE_TO_TARGET");

	}
}

void MainCameraManager::FocusReturnEnd(const StateInfo& _Info)
{
}


void MainCameraManager::FocusCancleStart(const StateInfo& _Info)
{



}

void MainCameraManager::FocusCancleUpdate(float _DeltaTime, const StateInfo& _Info)
{


	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();

	float4 CurrentPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
		, GetLevel()->GetMainCameraActorTransform().GetLocalPosition().z };

	float4 DestPos = { GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
		, -1800.f };


	float4 Lenth = CurrentPos - DestPos;
	ReturnLenth_ = Lenth.Length();

	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.0f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MoveCamera);
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


	if (ReturnLenth_ <= 0)
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ GetLevel()->GetMainCameraActorTransform().GetWorldPosition().x, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().y , -1800.f });
		CameraStateManager_.ChangeState("MOVE_TO_TARGET");

	}
}

void MainCameraManager::FocusCancleEnd(const StateInfo& _Info)
{
}
