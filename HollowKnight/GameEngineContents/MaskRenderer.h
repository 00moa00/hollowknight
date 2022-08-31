#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>


struct UVData
{
	float OffsetX;
	float OffsetY;
	float Dummy0;
	float Dummy1;
};



class MaskRenderer : public GameEngineTextureRenderer
{
public:
	// constrcuter destructer
	MaskRenderer();
	~MaskRenderer();

	// delete Function
	MaskRenderer(const MaskRenderer& _Other) = delete;
	MaskRenderer(MaskRenderer&& _Other) noexcept = delete;
	MaskRenderer& operator=(const MaskRenderer& _Other) = delete;
	MaskRenderer& operator=(MaskRenderer&& _Other) noexcept = delete;

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

