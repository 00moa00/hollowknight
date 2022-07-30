#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "UIPoint.h"
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
	void Update(float _DeltaTime);

private:
	UIPoint* UIPointGameStart_;
	UIPoint* UIPointMapEditor_;
	UIPoint* UIPointGameExit_;

	GameEngineStateManager TitleStateManager_;

private:

	void EventOffGameStart();
	void EventOffMapEditor();
	void EventOffGameExit();

	//void GameStartAnimationEnd(const FrameAnimation_DESC& _Info);

	void GameStartUpdate(float _DeltaTime, const StateInfo& _Info);
	void MapEditorUpdate(float _DeltaTime, const StateInfo& _Info);
	void GameExitUpdate(float _DeltaTime, const StateInfo& _Info);

};

