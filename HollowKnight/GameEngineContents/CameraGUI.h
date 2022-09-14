#pragma once
#include <GameEngineCore/GameEngineGUI.h>
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

