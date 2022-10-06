#include "PreCompile.h"
#include "TutorialBreakDoor.h"
#include "DoorStoneParticle.h"
#include "HollowKnightLevel.h"

TutorialBreakDoor::TutorialBreakDoor() 
{
}

TutorialBreakDoor::~TutorialBreakDoor() 
{
}

void TutorialBreakDoor::Start()
{
	CreateRendererComponent({ 95, 252, 1 }, "tut_door_02.png");
	CreateCollisionComponent({ 95, 252, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	CreateWallCollisionComponent({ 95, 252 });

	GetWallCollision()->GetTransform().SetLocalPosition({0,252/2 });
	GetCollision()->GetTransform().SetLocalPosition({ 0,252 / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,252 / 2 });
	
}

void TutorialBreakDoor::Update(float _DeltaTime)
{

}

void TutorialBreakDoor::SetHitCollision()
{
	DoorStoneParticle* DoorStoneParticle_ = GetLevel()->CreateActor<DoorStoneParticle>();
	DoorStoneParticle_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y + 100.f });
	DoorStoneParticle_->SetDir(GetLevel<HollowKnightLevel>()->GetKnight()->GetKnightSlashEffect()->GetDir());
	GameEngineSound::SoundPlayOneShot("breakable_wall_death.ogg");

	this->Death();

}

bool TutorialBreakDoor::ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{  

	return true;
}

