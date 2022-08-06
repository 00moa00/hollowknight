#include "PreCompile.h"
#include "MasterEffect.h"

MasterEffect::MasterEffect() 
	:
	MainRenderer_(nullptr),
	MainCollision_(nullptr),

	Direction_(),
	CollisionSize_()
{
}

MasterEffect::~MasterEffect() 
{
}

void MasterEffect::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
	MainRenderer_->GetTransform().SetWorldPosition({ 0, _LocalScale.y / 2 });
}

void MasterEffect::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	MainCollision_ = CreateComponent<GameEngineCollision>();
	//MainCollision_ ->Push
	MainCollision_->GetTransform().SetLocalScale(_LocalScale);
	MainCollision_->ChangeOrder(_Order);
}
