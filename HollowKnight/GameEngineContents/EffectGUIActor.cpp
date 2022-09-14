#include "PreCompile.h"

#include "EffectGUIActor.h"

EffectGUIActor::EffectGUIActor() 
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
}

void EffectGUIActor::LevelStartEvent()
{
	EffectGUI_ = GameEngineGUI::CreateGUIWindow<EffectGUI>("Effect", GetLevel());
}

void EffectGUIActor::LevelEndEvent()
{
	EffectGUI_->EffectGUIDeath();
}
