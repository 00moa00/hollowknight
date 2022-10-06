#include "PreCompile.h"

#include "EffectGUIActor.h"

EffectGUIActor::EffectGUIActor() 
	:
	EffectGUI_(nullptr)
{
}

EffectGUIActor::~EffectGUIActor() 
{
}

void EffectGUIActor::Start()
{
}

void EffectGUIActor::Update(float _DeltaTime)
{
	//KnightData::GetInst()->SetOverlayflag(EffectGUI_->GetOverlayFlag());

	//KnightData::GetInst()->SetNoiseFlag(EffectGUI_->GetNoiseFlag());
	//KnightData::GetInst()->SetBloomFlag(EffectGUI_->GetBloomFlag());

}

void EffectGUIActor::LevelStartEvent()
{
	EffectGUI_ = GameEngineGUI::CreateGUIWindow<EffectGUI>("Effect", GetLevel());

	if (GetLevel()->GetNameConstRef() == "GRIMMLEVEL"  )
	{
		EffectGUI_->SetisMainLightOnOff(false);
		EffectGUI_->SetisDonutLightOnOff(false);
		EffectGUI_->SetOverlayColor({ 0.737f, 0.0564f, 0.655f, 1.0f });

		EffectGUI_->SetSlibingLightColor({ 0.653f, 0.348f, 0.553f, 1.0f });

	}

	if (GetLevel()->GetNameConstRef() == "GRIMMDIRTMOUTHLEVEL2")
	{
		EffectGUI_->SetOverlayColor({ 0.602f, 0.407f, 0.509f, 1.0f });

	}
}

void EffectGUIActor::LevelEndEvent()
{
	KnightData::GetInst()->SetOverlayflag(EffectGUI_->GetOverlayFlag());
	KnightData::GetInst()->SetNoiseFlag(EffectGUI_->GetNoiseFlag());
	KnightData::GetInst()->SetBloomFlag(EffectGUI_->GetBloomFlag());


	KnightData::GetInst()->SetOverlayColor(EffectGUI_->GetoverlayColor());

	KnightData::GetInst()->SetKnihgtMainLightMulColor(EffectGUI_->GetMainLightMulColor());
	KnightData::GetInst()->SetKnihgtMainLightPlusColor(EffectGUI_->GetMainLightPlusColor());

	KnightData::GetInst()->SetKnihgtSlibingLightMulColor(EffectGUI_->GetSlibingLightMulColor());
	KnightData::GetInst()->SetKnihgtSlibingLightPlusColor(EffectGUI_->GetSlibingLightPlusColor());

	KnightData::GetInst()->SetKnihgtDounutLightMulColor(EffectGUI_->GetDounutLightMulColor());
	KnightData::GetInst()->SetKnihgtDounutLightPlusColor(EffectGUI_->GetDounutLightPlusColor());

	EffectGUI_->EffectGUIDeath();
}
