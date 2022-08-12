#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "UIPoint.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

//#pragma comment(lib, "DirectXTex.lib")

class GameEngineUIRenderer;

// Ό³Έν :
class AllTitleUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AllTitleUI();
	~AllTitleUI();

	// delete Function
	AllTitleUI(const AllTitleUI& _Other) = delete;
	AllTitleUI(AllTitleUI&& _Other) noexcept = delete;
	AllTitleUI& operator=(const AllTitleUI& _Other) = delete;
	AllTitleUI& operator=(AllTitleUI&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

private:
	UIPoint* UIPointGameStart_;
	UIPoint* UIPointMapEditor_;
	UIPoint* UIPointGameExit_;

	GameEngineFontRenderer* GameStartFont_;
	GameEngineFontRenderer* MapEditorFont_;
	GameEngineFontRenderer* GameExitFont_;


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

