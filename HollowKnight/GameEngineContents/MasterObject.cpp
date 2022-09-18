#include "PreCompile.h"
#include "MasterObject.h"

MasterObject::MasterObject() 
	:
	Renderer_(nullptr),
	Collision_(nullptr),
	WallCollision_(nullptr)
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

void MasterObject::CreateRendererComponent(std::string _FileName)
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(_FileName);
	Renderer_->GetTransform().SetLocalScale(Renderer_->GetCurTexture()->GetScale());
}

void MasterObject::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_LocalScale);
	Collision_->ChangeOrder(_Order);
}

void MasterObject::CreateWallCollisionComponent(float4 _LocalScale)
{
	WallCollision_ = CreateComponent<GameEngineCollision>();
	WallCollision_->GetTransform().SetLocalScale(_LocalScale);
	WallCollision_->ChangeOrder(COLLISION_ORDER::Wall);
}

