#include "PreCompile.h"
#include "BloomPostEffect.h"
#include <GameEngineBase/GameEngineWindow.h>
BloomPostEffect::BloomPostEffect() 
{
}

BloomPostEffect::~BloomPostEffect() 
{
	if (nullptr != CopyTargetWhiteCut)
	{
		delete CopyTargetWhiteCut;
		CopyTargetWhiteCut = nullptr;
	}

	if (nullptr != CopyTargetWhiteCutBlur)
	{
		delete CopyTargetWhiteCutBlur;
		CopyTargetWhiteCutBlur = nullptr;
	}


	if (nullptr != CopyTargetBloom)
	{
		delete CopyTargetBloom;
		CopyTargetBloom = nullptr;
	}


	if (nullptr != OriTex)
	{
		delete OriTex;
		OriTex = nullptr;
	}
}

void BloomPostEffect::EffectInit()
{
	
	CopyTargetWhiteCut = new GameEngineRenderTarget();
	CopyTargetWhiteCut->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSetWhiteCut.SetPipeLine("WhiteCutPostEffect");

	CopyTargetWhiteCutBlur = new GameEngineRenderTarget();
	CopyTargetWhiteCutBlur->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSetWhiteCutBlur.SetPipeLine("Blur");


	CopyTargetBloom = new GameEngineRenderTarget();
	CopyTargetBloom->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSetBloom.SetPipeLine("Bloom");



	//EffectSetBloom.ShaderResources.SetTexture("BloomOriTex", CopyTargetWhiteCut->GetRenderTargetTexture(0));
	//EffectSetBloom.ShaderResources.SetTexture("BloomTex", CopyTargetWhiteCutBlur->GetRenderTargetTexture(0));
	//EffectSetBloom.ShaderResources.SetTexture("OriTexture", CopyTargetWhiteCut->GetRenderTargetTexture(0));

}

void BloomPostEffect::Effect(GameEngineRenderTarget* _Target)
{
	// Èò»ö Àß¶ó³¿
	CopyTargetBloom->Copy(_Target);

	//OriTex -> Copy(_Target);

	CopyTargetWhiteCut->Copy(_Target);
	EffectSetWhiteCut.ShaderResources.SetTexture("Tex", CopyTargetWhiteCut->GetRenderTargetTexture(0));

	// Àß¶ó³½ Èò»ö¿¡ ºí·¯ Àû¿ë
	CopyTargetWhiteCutBlur->Clear();
	CopyTargetWhiteCutBlur->Setting();
	CopyTargetWhiteCutBlur->Effect(EffectSetWhiteCut);

	EffectSetWhiteCutBlur.ShaderResources.SetTexture("Tex", CopyTargetWhiteCutBlur->GetRenderTargetTexture(0));


	//CopyTargetBloom->Clear();
	//CopyTargetBloom->Setting();
	//CopyTargetBloom->Effect(EffectSetWhiteCutBlur);



	EffectSetBloom.ShaderResources.SetTexture("OriTexture", CopyTargetBloom->GetRenderTargetTexture(0));
	EffectSetBloom.ShaderResources.SetTexture("BloomTex", CopyTargetWhiteCutBlur->GetRenderTargetTexture(0));
	EffectSetBloom.ShaderResources.SetTexture("BloomOriTex", CopyTargetWhiteCut->GetRenderTargetTexture(0));


	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSetBloom);
}

