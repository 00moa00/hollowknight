#include "PreCompile.h"
#include "TutorialGate.h"
#include "HollowKnightLevel.h"

TutorialGate::TutorialGate() 
{
}

TutorialGate::~TutorialGate() 
{
}

void TutorialGate::Start()
{
	CreateRendererComponent({ 964.f, 1061.f, 1 }, "tut_door_02.png");
	//GetR

	CreateCollisionComponent({ 964.f, 1061.f, 1 }, static_cast<int>(COLLISION_ORDER::Object));

	CreateWallCollisionComponent({ 964.f, 1061.f});

	GetWallCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetCollision()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });
	GetRenderer()->GetTransform().SetLocalPosition({ 0,  1061.f / 2 });

}

void TutorialGate::Update(float _DeltaTime)
{
	if ((GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight_Slash, CollisionType::CT_OBB2D,
		std::bind(&TutorialGate::ObjectVSEffectCollision, this, std::placeholders::_1, std::placeholders::_2)) == true))
	{

		//DoorStoneParticle* DoorStoneParticle_ = GetLevel()->CreateActor<DoorStoneParticle>();
		//DoorStoneParticle_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y + 100.f });
		//DoorStoneParticle_->SetDir(GetLevel<HollowKnightLevel>()->GetKnight()->GetKnightSlashEffect()->GetDir());
		//this->Death();
	}
}

bool TutorialGate::ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    return true;
}
