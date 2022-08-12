#include "PreCompile.h"
#include "MasterUI.h"

MasterUI::MasterUI() 
	:
	Renderer_(nullptr),
	Collision_(nullptr)
{
}

MasterUI::~MasterUI() 
{
}

void MasterUI::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture(_FileName, _Index);
	Renderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1 });
	//Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
}

void MasterUI::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_LocalScale);
	Collision_->ChangeOrder(_Order);
}

