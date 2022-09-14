#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "PerlinNoise.h"
#include "CameraGUI.h"

enum class CameraMode
{
	TargetMove,
	Shaking,
	ReturnTargetMove,
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

	float max_skew;		// unit is degrees angle.
	float max_sway;	// unit is pixels in screen space.
	float seed ;
	float seed_shifting_factor ;

public:
	void MainCameraMoveLimitWindow(float4 _TargetPos, float4 _MapSize);
	void ChangeCameraMove(CameraMode _Mode);

private:
	//================================
	//    Bind State
	//================================
	void MoveToTargetStart(const StateInfo& _Info);
	void MoveToTargetUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveToTargetEnd(const StateInfo& _Info);

	void ShakingStart(const StateInfo& _Info);
	void ShakingUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShakingEnd(const StateInfo& _Info);



};

