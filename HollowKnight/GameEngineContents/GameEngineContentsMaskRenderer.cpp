#include "PreCompile.h"
#include "GameEngineContentsMaskRenderer.h"

GameEngineContentsMaskRenderer::GameEngineContentsMaskRenderer() 
{
}

GameEngineContentsMaskRenderer::~GameEngineContentsMaskRenderer() 
{
}

void GameEngineContentsMaskRenderer::Start()
{

	GameEngineDefaultRenderer::Start();

	PushRendererToUICamera();


	SetTextureRendererSetting();
}

void GameEngineContentsMaskRenderer::SetTextureRendererSetting()
{
	SetPipeLine("TextureAtlasMask");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;

	ShaderResources.SetConstantBufferLink("AtlasData", AtlasDataInst);
	ShaderResources.SetConstantBufferLink("ColorData", ColorData);

	UVData_.OffsetX = 0.f;
	UVData_.OffsetY = 0.f;

	ShaderResources.SetConstantBufferLink("UVData", UVData_);
}


void GameEngineContentsMaskRenderer::Update(float _Delta)
{
	if (nullptr != CurAni)
	{
		CurAni->Update(_Delta);
	}

}
