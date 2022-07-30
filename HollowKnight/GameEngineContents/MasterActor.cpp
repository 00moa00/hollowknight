#include "PreCompile.h"
#include "MasterActor.h"

MasterActor::MasterActor() 
	:
	MainRenderer_(nullptr),
	CollisionMap_(nullptr),

	MoveDirection_(float4::ZERO),
	Speed_ (0),
	isMove_(true),
	isOnGround_(false)
{
}

MasterActor::~MasterActor() 
{
}

void MasterActor::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, _LocalScale.z });
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->SetOrder(_Order);
	//MainRenderer_->SetPivot(PIVOTMODE");

}

