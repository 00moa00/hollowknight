#include "PreCompile.h"
#include "MasterMapItem.h"

MasterMapItem::MasterMapItem() 
{
}

MasterMapItem::~MasterMapItem() 
{
}

void MasterMapItem::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(_FileName, _Index);
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
}

void MasterMapItem::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_LocalScale);
	Collision_->ChangeOrder(_Order);
}

