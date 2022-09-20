#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "PerlinNoise.h"
#include "CameraGUI.h"

enum class CameraMode
{
	TargetMove,
	TargetInRoomMove,
	Shaking,
	BossShaking,
	PivotTargetMove,
	Focus,
	CancleFocus,
	ReturnFocus
};

// Ό³Έν :
class MainCameraManager : public GameEngineActor
{
public:
	// constrcuter destructer
	MainCameraManager();
	~MainCameraManager();

	// delete Function
	MainCameraManager(const MainCameraManager& _Other) = delete;
	MainCameraManager(MainCameraManager&& _Other) noexcept = delete;
	MainCameraManager& operator=(const MainCameraManager& _Other) = delete;
	MainCameraManager& operator=(MainCameraManager&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime)override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	GameEngineStateManager CameraStateManager_;
	CameraGUI* CameraGUI_;

	PerlinNoise Pn_;

	float MaxSkew;		// unit is degrees angle.
	float MaxSway;	// unit is pixels in screen space.
	float seed ;
	float SeedShiftingFactor ;

	float ReturnLenth_;

	float4 RoomSize_;
	float4 RoomPos_;

public:
	void MainCameraMoveLimitWindow(float4 _TargetPos, float4 _MapSize);
	void ChangeCameraMove(CameraMode _Mode);

	void SetRoomCamera(float4 _RoomSize, float4 _RoomPos);

private:
	//================================
	//    Bind State
	//================================
	void MoveToTargetStart(const StateInfo& _Info);
	void MoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveToTargetEnd(const StateInfo& _Info);

	void MoveToTargetInRoomStart(const StateInfo& _Info);
	void MoveToTargetInRoomUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveToTargetInRoomEnd(const StateInfo& _Info);

	void ShakingStart(const StateInfo& _Info);
	void ShakingUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShakingEnd(const StateInfo& _Info);

	void BossShakingStart(const StateInfo& _Info);
	void BossShakingUpdate(float _DeltaTime, const StateInfo& _Info);
	void BossShakingEnd(const StateInfo& _Info);

	void ChangePivotStart(const StateInfo& _Info);
	void ChangePivotUpdate(float _DeltaTime, const StateInfo& _Info);
	void ChangePivotEnd(const StateInfo& _Info);

	void PivotMoveToTargetStart(const StateInfo& _Info);
	void PivotMoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info);
	void PivotMoveToTargetEnd(const StateInfo& _Info);

	void FocusStart(const StateInfo& _Info);
	void FocusUpdate(float _DeltaTime, const StateInfo& _Info);
	void FocusEnd(const StateInfo& _Info);

	void FocusCancleStart(const StateInfo& _Info);
	void FocusCancleUpdate(float _DeltaTime, const StateInfo& _Info);
	void FocusCancleEnd(const StateInfo& _Info);

	void FocusReturnStart(const StateInfo& _Info);
	void FocusReturnUpdate(float _DeltaTime, const StateInfo& _Info);
	void FocusReturnEnd(const StateInfo& _Info);


};

