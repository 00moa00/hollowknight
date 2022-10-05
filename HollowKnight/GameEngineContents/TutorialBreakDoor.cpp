#include "PreCompile.h"
#include "TutorialBreakDoor.h"
#include "DoorStoneParticle.h"
#include "HollowKnightLevel.h""

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
	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight_Slash, CollisionType::CT_OBB2D,
		std::bind(&TutorialBreakDoor::ObjectVSEffectCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{
		
		DoorStoneParticle* DoorStoneParticle_ = GetLevel()->CreateActor<DoorStoneParticle>();
		DoorStoneParticle_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition(). x, this->GetTransform().GetWorldPosition().y + 100.f});
		DoorStoneParticle_->SetDir(GetLevel<HollowKnightLevel>()->GetKnight()->GetKnightSlashEffect()->GetDir());
		this->Death();
	}
}

bool TutorialBreakDoor::ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	return true;
}

