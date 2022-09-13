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



};

