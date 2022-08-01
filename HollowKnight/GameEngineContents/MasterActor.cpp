#include "PreCompile.h"
#include "MasterActor.h"

MasterActor::MasterActor() 
	:
	MainRenderer_(nullptr),
	CollisionMap_(nullptr),

	GravityY(),
	JumpPower_(),
	FallDownDirection_(),
	CollisionSize_(),
	FallSpeed_(),
	Speed_ (),

	MoveDirection_(float4::ZERO),

	isMove_(true),
	isOnGround_(false),
	isWall_(false)
{
}

MasterActor::~MasterActor() 
{
}

void MasterActor::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1});
	MainRenderer_->GetTransform().SetWorldPosition({ 0, _LocalScale.y/2 });

	//MainRenderer_->GetTransform().SetWorldScale({ _LocalScale.x, _LocalScale.y });
	//MainRenderer_->SetOrder(_Order);
	//MainRenderer_->SetPivot(PIVOTMODE::BOT);
	//MainRenderer_->GetTransform().SetLocalPosition({ MainRenderer_->GetTransform().GetLocalPosition().x, MainRenderer_->GetTransform().GetLocalPosition().y, 0.1 });
	
}
