#pragma once
#include <GameEngineCore/GameEngineGUI.h>

#include "KnightData.h"

// Ό³Έν :
class CameraGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	CameraGUI();
	~CameraGUI();

	// delete Function
	CameraGUI(const CameraGUI& _Other) = delete;
	CameraGUI(CameraGUI&& _Other) noexcept = delete;
	CameraGUI& operator=(const CameraGUI& _Other) = delete;
	CameraGUI& operator=(CameraGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


private:
	
	float MaxSkew;		// unit is degrees angle.
	float MaxSway;	// unit is pixels in screen space.
	float SeedShiftingFactor;

public:

	void CameraGUIDeath()
	{
		KnightData::GetInst()->SetMaxSway(MaxSway);
		KnightData::GetInst()->SetMaxSkew(MaxSkew);
		KnightData::GetInst()->SetSeedshiftingFactor(SeedShiftingFactor);

		this->Death();
	}

	float GetMaxSkew() const
	{
		return MaxSkew;
	}

	float GetMaxSway() const
	{
		return MaxSway;
	}

	float GetSeedshiftingFactor() const
	{
		return SeedShiftingFactor;
	}
};

