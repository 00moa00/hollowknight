#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>


class MapRenderer : public GameEngineTextureRenderer
{
public:
	// constrcuter destructer
	MapRenderer();
	~MapRenderer();

	// delete Function
	MapRenderer(const MapRenderer& _Other) = delete;
	MapRenderer(MapRenderer&& _Other) noexcept = delete;
	MapRenderer& operator=(const MapRenderer& _Other) = delete;
	MapRenderer& operator=(MapRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

	//PixelData PixelDataInst;
	AtlasData AtlasDataInst;
	FrameAnimation* CurAni;

};

