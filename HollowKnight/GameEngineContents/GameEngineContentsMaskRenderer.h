#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>




class GameEngineContentsMaskRenderer : public GameEngineTextureRenderer
{
public:
	// constrcuter destructer
	GameEngineContentsMaskRenderer();
	~GameEngineContentsMaskRenderer();

	// delete Function
	GameEngineContentsMaskRenderer(const GameEngineContentsMaskRenderer& _Other) = delete;
	GameEngineContentsMaskRenderer(GameEngineContentsMaskRenderer&& _Other) noexcept = delete;
	GameEngineContentsMaskRenderer& operator=(const GameEngineContentsMaskRenderer& _Other) = delete;
	GameEngineContentsMaskRenderer& operator=(GameEngineContentsMaskRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

private:

};

