#include "PreCompile.h"
#include "OverlayPostEffect.h"
#include <GameEngineBase/GameEngineWindow.h>

OverlayPostEffect::OverlayPostEffect() 
{
}

OverlayPostEffect::~OverlayPostEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void OverlayPostEffect::EffectInit()
{

	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	Overlay_ = GameEngineTexture::Find("PostEffectOverlay.png");

	EffectSet.SetPipeLine("Overlay");

	//EffectSet.GetPipeLine()->SetOutputMergerBlend("TransparentBlend");


}

void OverlayPostEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex1", CopyTarget->GetRenderTargetTexture(0));
	EffectSet.ShaderResources.SetTexture("Tex2", Overlay_);	

	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);

}

void OverlayPostEffect::Update(float _DeltaTime)
{
}

