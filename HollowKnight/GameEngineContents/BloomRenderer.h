#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>

struct BlurData
{
	float4 TextureSize;

};


// Ό³Έν :
class BloomRenderer : public GameEngineTextureRenderer
{
public:
	// constrcuter destructer
	BloomRenderer();
	~BloomRenderer();

	// delete Function
	BloomRenderer(const BloomRenderer& _Other) = delete;
	BloomRenderer(BloomRenderer&& _Other) noexcept = delete;
	BloomRenderer& operator=(const BloomRenderer& _Other) = delete;
	BloomRenderer& operator=(BloomRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

	void SetTextureRendererSetting();

	void Update(float _Delta) override;

private:
	BlurData BlurData_;
};

