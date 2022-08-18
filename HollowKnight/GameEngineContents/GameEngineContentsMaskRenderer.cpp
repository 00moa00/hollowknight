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

	PushRendererToMainCamera();

	SetPipeLine("TextureAtlas");

	FrameData.PosX = 0.0f;
	FrameData.PosY = 0.0f;
	FrameData.SizeX = 1.0f;
	FrameData.SizeY = 1.0f;

	ShaderResources.SetConstantBufferLink("AtlasData", FrameData);
	ShaderResources.SetConstantBufferLink("ColorData", ColorData);
}

void GameEngineContentsMaskRenderer::SetTextureRendererSetting()
{
}

void GameEngineContentsMaskRenderer::Update(float _Delta)
{
}
