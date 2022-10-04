#include "PreCompile.h"
#include "KnightScreamCastEffect.h"
#include "KnightData.h"
#include "Monster.h"
KnightScreamCastEffect::KnightScreamCastEffect() 
	:
	NeutralRenderer_(nullptr),
	ScreamRenderer_(nullptr),
	MainCollision_(nullptr)

{
}

KnightScreamCastEffect::~KnightScreamCastEffect() 
{
}

void KnightScreamCastEffect::Start()
{
	GetTransform().SetLocalPosition({0, 500});

	ScreamRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ScreamRenderer_->SetTexture("Spell Effects 2_scream_effect0000-Sheet.png");
	ScreamRenderer_->GetTransform().SetLocalScale({ 357.f * 3.0f, 292.f * 3.0f });
	ScreamRenderer_->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

	ScreamRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects 2_scream_effect0000-Sheet.png", 0, 12, 0.060f, false));
	ScreamRenderer_->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects 2_scream_effect0000-Sheet.png", 12, 12, 0.010f, false));

	ScreamRenderer_->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ScreamRenderer_->ChangeFrameAnimation("IDLE");
			//Off();
		});

	ScreamRenderer_->ChangeFrameAnimation("ANIMATION");



	NeutralRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	NeutralRenderer_->SetTexture("Spell Effects Neutral_scream_blast_level_020000-Sheet.png");
	NeutralRenderer_->GetTransform().SetLocalScale({357.f * 3.0f, 292.f * 3.0f });


	NeutralRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects Neutral_scream_blast_level_020000-Sheet.png", 0, 12, 0.060f, false));
	NeutralRenderer_->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects Neutral_scream_blast_level_020000-Sheet.png", 12, 12, 0.010f, false));

	NeutralRenderer_->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			NeutralRenderer_->ChangeFrameAnimation("IDLE");
			Off();
		});

	NeutralRenderer_->ChangeFrameAnimation("ANIMATION");

	MainCollision_ = CreateComponent<GameEngineCollision>();
	MainCollision_->GetTransform().SetLocalScale({ 357.f * 3.0f, 292.f * 3.0f });
	MainCollision_->ChangeOrder(COLLISION_ORDER::Knight_Slash);


	this->Off();
}

void KnightScreamCastEffect::Update(float _DeltaTime)
{

	MainCollision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightScreamCastEffect::EffectVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));

}

void KnightScreamCastEffect::EffectOn()
{
	On();
	ScreamRenderer_->On();
	NeutralRenderer_->On();
	MainCollision_->On();

	ScreamRenderer_->ChangeFrameAnimation("ANIMATION");
	NeutralRenderer_->ChangeFrameAnimation("ANIMATION");

}

bool KnightScreamCastEffect::EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		Monster* Monster_ = dynamic_cast<Monster*>(_Other->GetActor());
		Monster_->SetMonsterHit(KnightData::GetInst()->GetHitDamage() * 2, float4::ZERO, float4::ZERO);

		MainCollision_->Off();

		return true;
	}
	else
	{
		return false;
	}
}
