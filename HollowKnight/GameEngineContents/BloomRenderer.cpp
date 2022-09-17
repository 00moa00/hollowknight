#include "PreCompile.h"
#include "BloomRenderer.h"

BloomRenderer::BloomRenderer() 
{
}

BloomRenderer::~BloomRenderer() 
{
}

void BloomRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	PushRendererToMainCamera();

	SetTextureRendererSetting();
}

void BloomRenderer::SetTextureRendererSetting()
{
	SetPipeLine("LightCut");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;
	BlurData_.TextureSize = {};

	ShaderResources.SetConstantBufferLink("AtlasData", AtlasDataInst);
	ShaderResources.SetConstantBufferLink("PixelData", PixelDataInst);

	ShaderResources.SetConstantBufferLink("BlurData", BlurData_);
}

void BloomRenderer::Update(float _Delta)
{
	if (nullptr != CurAni)
	{
		CurAni->Update(_Delta);
	}

	BlurData_.TextureSize = GetCurTexture()->GetScale();
}
