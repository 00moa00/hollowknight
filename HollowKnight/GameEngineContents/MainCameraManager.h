#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>


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

public:
	void MainCameraMoveLimitWindow(float4 _TargetPos, float4 _MapSize);

};

