#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MapCameraManager : public GameEngineActor
{
public:
	// constrcuter destructer
	MapCameraManager();
	~MapCameraManager();

	// delete Function
	MapCameraManager(const MapCameraManager& _Other) = delete;
	MapCameraManager(MapCameraManager&& _Other) noexcept = delete;
	MapCameraManager& operator=(const MapCameraManager& _Other) = delete;
	MapCameraManager& operator=(MapCameraManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	GameEngineStateManager CameraStateManager_;

	float WideSpeed_;

	float4 WidePivot_;

private:
	//================================
	//    Bind State
	//================================
	void WideStart(const StateInfo& _Info);
	void WideUpdate(float _DeltaTime, const StateInfo& _Info);
	void WideEnd(const StateInfo& _Info);

	void WideIdleStart(const StateInfo& _Info);
	void WideIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void WideIdleEnd(const StateInfo& _Info);

	void NarrowStart(const StateInfo& _Info);
	void NarrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void NarrowEnd(const StateInfo& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info);


public:
	void SetMapMoveRight();
	void SetMapMoveLeft();
	void SetMapMoveTop();
	void SetMapMoveDown();

	void SetMapCameraWide();
	void SetMapCameraNarrow();

	void SetWidePivot(float4 _pivot)
	{
		WidePivot_ = _pivot;
	}
};

