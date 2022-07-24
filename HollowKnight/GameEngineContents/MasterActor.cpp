#include "PreCompile.h"
#include "MasterActor.h"

MasterActor::MasterActor() 
	:
	Renderer_(nullptr)
{
}

MasterActor::~MasterActor() 
{
}

void MasterActor::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, _LocalScale.z });
	Renderer_->SetTexture(_FileName, _Index);
	Renderer_->SetOrder(_Order);


}

