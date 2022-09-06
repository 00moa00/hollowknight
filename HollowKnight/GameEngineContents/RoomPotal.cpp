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

}

void RoomPotal::Update(float _DeltaTime)
{
}

void RoomPotal::CreatePotal(POTAL_TYPE _Type, bool isPromt)
{
	if (isPromt == true)
	{
		PromptSet_ = GetLevel()->CreateActor<PromptSet>();
		PromptSet_->SetParent(this);

		PromptSet_->GetCollision()->GetTransform().SetLocalScale(float4{ 400, 200, 1 });
		PromptSet_->CreatePrompSet(PromptSetType::INTER);
	}


	CreateCollisionComponent(float4{ 400, 200, 1 }, static_cast<int>(OBJECTORDER::Potal));
	PotalType_ = _Type;
}

