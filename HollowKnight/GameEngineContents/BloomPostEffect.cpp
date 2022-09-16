#include "PreCompile.h"
#include "BloomPostEffect.h"
#include <GameEngineBase/GameEngineWindow.h>
BloomPostEffect::BloomPostEffect() 
{
}

BloomPostEffect::~BloomPostEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void BloomPostEffect::EffectInit()
{
	
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	//BloomData_.iMouse.x = 1.0f;
	//BloomData_.iMouse.y = 1.0f;
	//BloomData_.iResolution. x = 1.0f;
	//BloomData_.iResolution.y = 1.0f;


	//EffectSet.ShaderResources.SetConstantBufferLink("BloomData", BloomData_);

	EffectSet.SetPipeLine("Bloom");
}

void BloomPostEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));

	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

