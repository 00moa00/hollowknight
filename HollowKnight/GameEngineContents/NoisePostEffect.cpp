#include "PreCompile.h"

#include "NoisePostEffect.h"
#include <GameEngineBase/GameEngineWindow.h>
NoisePostEffect::NoisePostEffect() 
{
}

NoisePostEffect::~NoisePostEffect() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void NoisePostEffect::EffectInit()
{
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	//CopyTarget->SetName("Noise");
	EffectSet.SetPipeLine("Noise");
	//CopyTarget->GetNameConstRef
	//NoiseData_.Time = GameEngineTime::GetInst()->GetDeltaTime();

	//NoiseData_.Time = 1000000.f;

	EffectSet.ShaderResources.SetConstantBufferLink("NoiseData", NoiseData_);
}

void NoisePostEffect::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));


	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
	_Target->SetName("Noise");

}

void NoisePostEffect::Update(float _DeltaTime)
{
	NoiseData_.Time = _DeltaTime;
}

