#include "PreCompile.h"
#include "MapRenderer.h"

MapRenderer::MapRenderer()
{
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	PushRendererToUICamera();
	ChangeCamera(CAMERAORDER::MAPCAMERA);

	SetPipeLine("TextureAtlas");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;

	ShaderResources.SetConstantBufferLink("AtlasData", AtlasDataInst);
	ShaderResources.SetConstantBufferLink("PixelData", PixelDataInst);
}

void MapRenderer::SetTextureRendererSetting()
{
}

void MapRenderer::Update(float _Delta)
{
	if (nullptr != CurAni)
	{
		CurAni->Update(_Delta);
	}
}
