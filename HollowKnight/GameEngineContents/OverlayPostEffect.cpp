#include "PreCompile.h"
#include "OverlayPostEffect.h"
#include "HollowKnightLevel.h"

#include <GameEngineBase/GameEngineWindow.h>

OverlayPostEffect::OverlayPostEffect() 
	:
	OverlayColorData_(),
	EffectSet(),

	CopyTarget(nullptr),
	Overlay_(nullptr),
	HollowKnightLevel_(nullptr)

{
	OverlayColorData_.OverlayColor = { 0.499, 0.592, 0.726, 1.0f };
	OverlayColorData_.isOverlay_ = 0;
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

	Overlay_ = GameEngineTexture::Find("PostEffectOverlayCustom.png");

	EffectSet.SetPipeLine("Overlay");

	OverlayColorData_.OverlayColor = { 0.499, 0.592, 0.726, 1.0f };
	OverlayColorData_.isOverlay_ = 0;
	EffectSet.ShaderResources.SetConstantBufferLink("OverlayColorData", OverlayColorData_);	
}

void OverlayPostEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex1", CopyTarget->GetRenderTargetTexture(0));

	OverlayColorData_.isOverlay_ = HollowKnightLevel_->GetEffectGUIActor()->GetOverlayFlag();
	float4 COlor= HollowKnightLevel_->GetEffectGUIActor()->GetOverlayColor();
	//EffectGUIActor* t = HollowKnightLevel_->GetEffectGUIActor();

	OverlayColorData_.OverlayColor = COlor;

	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);

}

