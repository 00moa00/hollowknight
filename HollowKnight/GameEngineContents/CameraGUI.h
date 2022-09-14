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
	
	float max_skew;		// unit is degrees angle.
	float max_sway;	// unit is pixels in screen space.
	float seed_shifting_factor;

public:

	void CameraGUIDeath()
	{
		KnightData::GetInst()->SetMaxSway(max_sway);
		KnightData::GetInst()->SetMaxSkew(max_skew);
		KnightData::GetInst()->SetSeedshiftingFactor(seed_shifting_factor);

		this->Death();
	}

	float GetMaxSkew() const
	{
		return max_skew;
	}

	float GetMaxSway() const
	{
		return max_sway;
	}

	float GetSeedshiftingFactor() const
	{
		return seed_shifting_factor;
	}
};

