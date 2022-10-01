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

	CameraPivot_(),
	ReturnLenth_()
{

}

MainCameraManager::~MainCameraManager() 
{
}

void MainCameraManager::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}

	GetLevel()->GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({
		GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
		,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
		, -1800});
	

	CameraStateManager_.CreateStateMember("MOVE_TO_TARGET"
		, std::bind(&MainCameraManager::MoveToTargetUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::MoveToTargetStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::MoveToTargetEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("MOVE_TO_TARGET_INROOM"
		, std::bind(&MainCameraManager::MoveToTargetInRoomUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::MoveToTargetInRoomStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::MoveToTargetInRoomEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("SHAKING"
		, std::bind(&MainCameraManager::ShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::ShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::ShakingEnd, this, std::placeholders::_1));
	
	CameraStateManager_.CreateStateMember("BATTLE_SHAKING"
		, std::bind(&MainCameraManager::BattleShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::BattleShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::BattleShakingEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("BOSS_SHAKING"
		, std::bind(&MainCameraManager::BossShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::BossShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::BossShakingEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("BOSS_ACTTING_SHAKING"
		, std::bind(&MainCameraManager::BossActtingShakingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::BossActtingShakingStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::BossActtingShakingEnd, this, std::placeholders::_1));

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

	CameraStateManager_.CreateStateMember("CHANGE_PIVOT"
		, std::bind(&MainCameraManager::ChangePivotUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::ChangePivotStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::ChangePivotEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("PIVOT_MOVE_TO_TARGET"
		, std::bind(&MainCameraManager::PivotMoveToTargetUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::PivotMoveToTargetStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::PivotMoveToTargetEnd, this, std::placeholders::_1));

	CameraStateManager_.CreateStateMember("FREE_CAMERA"
		, std::bind(&MainCameraManager::FreeCameraUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&MainCameraManager::FreeCameraStart, this, std::placeholders::_1)
		, std::bind(&MainCameraManager::FreeCameraEnd, this, std::placeholders::_1));



	CameraStateManager_.ChangeState("MOVE_TO_TARGET");
}

void MainCameraManager::Update(float _DeltaTime)
{
	CameraStateManager_.Update(_DeltaTime);

}

void MainCameraManager::LevelStartEvent()
{
	CameraGUI_ = GameEngineGUI::CreateGUIWindow<CameraGUI>("Camera", GetLevel());
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({
	GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x
	,GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y
	, -1800 });

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

	case CameraMode::TargetInRoomMove:
		CameraStateManager_.ChangeState("MOVE_TO_TARGET_INROOM");

		break;
	case CameraMode::Shaking:
		CameraStateManager_.ChangeState("SHAKING");
		break;

	case CameraMode::Battle_Shaking:
		CameraStateManager_.ChangeState("BATTLE_SHAKING");
		break;
	case CameraMode::BossShaking:
		CameraStateManager_.ChangeState("BOSS_SHAKING");

		break;

	case CameraMode::BossActtingShaking:
		CameraStateManager_.ChangeState("BOSS_ACTTING_SHAKING");

		break;

	case CameraMode::PivotTargetMove:
		CameraStateManager_.ChangeState("CHANGE_PIVOT");

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

	case CameraMode::FreeCamera:
		CameraStateManager_.ChangeState("FREE_CAMERA");

		break;

	default:
		break;
	}
}

void MainCameraManager::SetRoomCamera(float4 _RoomSize, float4 _RoomPos)
{
	RoomSize_ = _RoomSize;
	RoomPos_ = _RoomPos;
}

void MainCameraManager::SetCameraPivot(float4 _Pivot)
{
	CameraPivot_ = _Pivot;
}

void MainCameraManager::MoveToTargetStart(const StateInfo& _Info)
{

}

void MainCameraManager::MoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info)
{

	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();
	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 5.f);

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


	if (KnightData::GetInst()->GetCurrentLevel() == "KINGSPASSLEVEL4")
	{
		if (DestPos.x > 3230.f && DestPos.y > -1200)
		{
			CameraStateManager_.ChangeState("CHANGE_PIVOT");
			CameraPivot_ = { 0, 200 };
		}
	}

}

void MainCameraManager::MoveToTargetEnd(const StateInfo& _Info)
{
}

void MainCameraManager::MoveToTargetInRoomStart(const StateInfo& _Info)
{
}

void MainCameraManager::MoveToTargetInRoomUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();
	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 5.f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ MoveCamera.x,MoveCamera.y,  -1800.0f });
	float4 MainCameraPosition = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

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

	//왼쪽
	if (RoomPos_.x  - RoomSize_.x/2 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x - RoomSize_.x / 2 + GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (0 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/

	}

	//오른쪽

	if (RoomPos_.x + RoomSize_.x / 2 < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x + RoomSize_.x / 2 - GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (MapSize.x < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = MapSize.x - GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/
	}

	//위

	if (0 < MainCameraPosition.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	//아래
	if (-MapSize.y > MainCameraPosition.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = -(MapSize.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}
}

void MainCameraManager::MoveToTargetInRoomEnd(const StateInfo& _Info)
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

	float4 Knihgt = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ Knihgt.x, Knihgt .y , -1800});
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

void MainCameraManager::BattleShakingStart(const StateInfo& _Info)
{
}

void MainCameraManager::BattleShakingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	seed += (_DeltaTime);
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * CameraGUI_->GetSeedshiftingFactor(), seed * CameraGUI_->GetSeedshiftingFactor(), 0)) - 1.0f;
	float4 ShakePosition = { shake * CameraGUI_->GetMaxSway(), shake * CameraGUI_->GetMaxSway() };
	float4 ShakeRotation = { 0,0, shake * CameraGUI_->GetMaxSkew() };

	float4 Knihgt = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ Knihgt.x, Knihgt.y , -1800 });
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


	//왼쪽
	if (RoomPos_.x - RoomSize_.x / 2 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x - RoomSize_.x / 2 + GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (0 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/

	}

	//오른쪽

	if (RoomPos_.x + RoomSize_.x / 2 < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x + RoomSize_.x / 2 - GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (MapSize.x < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = MapSize.x - GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/
	}

	//위

	if (0 < MainCameraPosition.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	//아래
	if (-MapSize.y > MainCameraPosition.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = -(MapSize.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

}

void MainCameraManager::BattleShakingEnd(const StateInfo& _Info)
{
}

void MainCameraManager::BossShakingStart(const StateInfo& _Info)
{
}

void MainCameraManager::BossShakingUpdate(float _DeltaTime, const StateInfo& _Info)
{

	seed += (_DeltaTime);
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * 15.f, seed * 15.f, 0)) - 1.0f;
	float4 ShakePosition = { shake * 15.f, shake * 15.f };
	//float4 ShakeRotation = { 0,0, shake * CameraGUI_->GetMaxSkew() };

	GetLevel()->GetMainCameraActorTransform().SetWorldMove(ShakePosition);
	//GetLevel()->GetMainCameraActorTransform().SetWorldRotation(ShakeRotation);


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

void MainCameraManager::BossShakingEnd(const StateInfo& _Info)
{
}

void MainCameraManager::BossActtingShakingStart(const StateInfo& _Info)
{
}

void MainCameraManager::BossActtingShakingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	seed += (_DeltaTime);
	const float shake = 2.0f * static_cast<float>(Pn_.noise(seed * 12.f, seed * 12.f, 0)) - 1.0f;
	float4 ShakePosition = { shake * 19.f, shake * 19.f };
	float4 ShakeRotation = { 0,0, shake * 0.5f };

	float4 Knihgt = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ Knihgt.x, Knihgt.y , -1800 });
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


	//왼쪽
	if (RoomPos_.x - RoomSize_.x / 2 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x - RoomSize_.x / 2 + GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (0 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/

	}

	//오른쪽

	if (RoomPos_.x + RoomSize_.x / 2 < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = RoomPos_.x + RoomSize_.x / 2 - GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);

		/*if (MapSize.x < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
		{
			MainCameraPosition.x = MapSize.x - GameEngineWindow::GetInst()->GetScale().hix();
			GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
		}*/
	}

	//위

	if (0 < MainCameraPosition.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	//아래
	if (-MapSize.y > MainCameraPosition.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = -(MapSize.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

}

void MainCameraManager::BossActtingShakingEnd(const StateInfo& _Info)
{
}

void MainCameraManager::ChangePivotStart(const StateInfo& _Info)
{
}

void MainCameraManager::ChangePivotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();
	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition() + CameraPivot_;
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 0.01f);

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

	if (_Info.PrevState == "PIVOT_MOVE_TO_TARGET")
	{
		CameraStateManager_.ChangeState("MOVE_TO_TARGET");

	}
	else
	{
		CameraStateManager_.ChangeState("PIVOT_MOVE_TO_TARGET");

	}
}

void MainCameraManager::ChangePivotEnd(const StateInfo& _Info)
{
}

void MainCameraManager::PivotMoveToTargetStart(const StateInfo& _Info)
{
}

void MainCameraManager::PivotMoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MapSize = GetLevel<HollowKnightLevel>()->GetMapSize();
	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition() + CameraPivot_;
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 5.f);

	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ MoveCamera.x, MoveCamera.y,  -1800.0f });
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


	if (DestPos.x < 3150.f && DestPos.y > -1200)
	{
		CameraStateManager_.ChangeState("CHANGE_PIVOT");
		CameraPivot_ = { 0, 0 };
	}
}

void MainCameraManager::PivotMoveToTargetEnd(const StateInfo& _Info)
{
}

void MainCameraManager::FocusStart(const StateInfo& _Info)
{
	
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

void MainCameraManager::FreeCameraStart(const StateInfo& _Info)
{
}

void MainCameraManager::FreeCameraUpdate(float _DeltaTime, const StateInfo& _Info)
{



	float MoveSpeed = 700.f;

	if (GameEngineInput::GetInst()->IsPress("CamMoveBoost"))
	{
		MoveSpeed *= 3.0f;
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveForward"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldForwardMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveBack"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldBackMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveUp"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldUpMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveDown"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldDownMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveLeft"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldLeftMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveRight"))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldRightMove(MoveSpeed, _DeltaTime);
	}

}

void MainCameraManager::FreeCameraEnd(const StateInfo& _Info)
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
