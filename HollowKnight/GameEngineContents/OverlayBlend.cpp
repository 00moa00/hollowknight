#include "PreCompile.h"
#include "OverlayBlend.h"

OverlayBlend::OverlayBlend() 
{
}

OverlayBlend::~OverlayBlend() 
{
}

void OverlayBlend::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("PostEffectOverlay.png");
	Renderer_->GetTransform().SetLocalScale(GameEngineWindow::GetInst()->GetScale());
	Renderer_->GetClonePipeLine()->SetOutputMergerBlend("TransparentBlend");

}

void OverlayBlend::Update(float _DeltaTime)
{
}

