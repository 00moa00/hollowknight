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
	CreateCollisionComponent(float4{ 150, 50, 1 }, static_cast<int>(OBJECTORDER::Potal));

	PromptSet_->SetParent(this);
}

void RoomPotal::Update(float _DeltaTime)
{
}

void RoomPotal::CreatePotal(POTAL_TYPE _Type)
{
	POTAL_TYPE_ = _Type;
}

