#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>


struct UVData
{
	float OffsetX;
	float OffsetY;
	float Dummy0;
	float Dummy1;
};



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
	UVData UVData_;
public:
	UVData& GetUVData()
	{
		return UVData_;
	}

};

