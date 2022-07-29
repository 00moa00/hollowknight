#include "PreCompile.h"
#include "RendererActor.h"

RendererActor::RendererActor() 
	:
	Renderer_(nullptr)
{
}

RendererActor::~RendererActor() 
{
}

void RendererActor::CreateRenderer(std::string _FileName)
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(_FileName);
	Renderer_->GetTransform().SetLocalScale(Renderer_->GetCurTexture()->GetScale());
	Renderer_->SetOrder(static_cast<int>(RENDERORDER::Background));
}

void RendererActor::SetRendererPivot(PIVOTMODE _Mode)
{
	Renderer_->SetPivot(_Mode);

}

