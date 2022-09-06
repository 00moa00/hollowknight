#include "PreCompile.h"

#include "VignettePostEffect.h"
#include <GameEngineBase/GameEngineWindow.h>

VignettePostEffect::VignettePostEffect() 
{
}

VignettePostEffect::~VignettePostEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void VignettePostEffect::EffectInit()
{
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetPipeLine("Vignette");
}

void VignettePostEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));

	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

