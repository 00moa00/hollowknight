#include "PreCompile.h"
#include "TutorialBreakDoor.h"

TutorialBreakDoor::TutorialBreakDoor() 
{
}

TutorialBreakDoor::~TutorialBreakDoor() 
{
}

void TutorialBreakDoor::Start()
{
	CreateRendererComponent({ 95, 252, 1 }, "tut_door_02.png");
	//GetR

	CreateCollisionComponent({ 95, 252, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	CreateWallCollisionComponent({ 95, 252 });

	GetWallCollision()->GetTransform().SetLocalPosition({0,252/2 });
	GetCollision()->GetTransform().SetLocalPosition({ 0,252 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,252 / 2 });
	
}

void TutorialBreakDoor::Update(float _DeltaTime)
{
}

