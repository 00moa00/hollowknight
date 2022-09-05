#include "PreCompile.h"
#include "RoomPotal.h"
#include "GlobalContentsValue.h"

RoomPotal::RoomPotal() 
	:
	PromptSet_(nullptr)
{
}

RoomPotal::~RoomPotal() 
{
}

void RoomPotal::Start()
{
	PromptSet_ = GetLevel()->CreateActor<PromptSet>();
	PromptSet_->SetParent(this);

	CreateCollisionComponent(float4{ 400, 200, 1 }, static_cast<int>(OBJECTORDER::Potal));
	PromptSet_->GetCollision()->GetTransform().SetLocalScale(float4{ 400, 200, 1 });
	PromptSet_->CreatePrompSet(PromptSetType::INTER);
}

void RoomPotal::Update(float _DeltaTime)
{
}

void RoomPotal::CreatePotal(POTAL_TYPE _Type)
{
	POTAL_TYPE_ = _Type;
}

