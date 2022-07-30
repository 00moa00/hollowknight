#pragma once
#include <GameEngineCore/CoreMinimal.h>

//#pragma comment(lib, "DirectXTex.lib")

class GameEngineUIRenderer;

// Ό³Έν :
class MasterTitleUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterTitleUI();
	~MasterTitleUI();

	// delete Function
	MasterTitleUI(const MasterTitleUI& _Other) = delete;
	MasterTitleUI(MasterTitleUI&& _Other) noexcept = delete;
	MasterTitleUI& operator=(const MasterTitleUI& _Other) = delete;
	MasterTitleUI& operator=(MasterTitleUI&& _Other) noexcept = delete;

protected:
	void Start();
	void Update();

private:
	GameEngineUIRenderer* LeftPointGameStart_;
	GameEngineUIRenderer* RightPointGameStart_;

	GameEngineUIRenderer* LeftPointMapEditor_;
	GameEngineUIRenderer* RightPointMapEditor_;

	GameEngineUIRenderer* LeftPointGameExit_;
	GameEngineUIRenderer* RightPointGameExit_;


	float4 PointScale_;

private:

	void EventOffGameStart();
	void EventOffMapEditor();
	void EventOffGameExit();

	void GameStartAnimationEnd(const FrameAnimation_DESC& _Info);

};

