#include "PreCompile.h"
#include "MasterObject.h"

MasterObject::MasterObject() 
{
}

MasterObject::~MasterObject() 
{
}

void MasterObject::CreateRendererComponent(float4 _LocalScale, std::string _FileName)
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(_FileName);
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
}

void MasterObject::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_LocalScale);
	Collision_->ChangeOrder(_Order);
}

