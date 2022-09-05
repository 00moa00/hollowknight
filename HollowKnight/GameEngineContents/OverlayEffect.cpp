#include "PreCompile.h"
#include "OverlayEffect.h"
#include <GameEngineBase/GameEngineWindow.h>

OverlayEffect::OverlayEffect() 
{
}

OverlayEffect::~OverlayEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void OverlayEffect::EffectInit()
{
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetPipeLine("TextureAtlas");
}

void OverlayEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);


	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

