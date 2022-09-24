#include "PreCompile.h"
#include "GrimmBird.h"

GrimmBird::GrimmBird()
	:
	MoveDir_(float4::ZERO),
	Speed_(0.f),

	BirdDeathEffect_(nullptr)
{
}

GrimmBird::~GrimmBird() 
{
}

void GrimmBird::Start()
{
	Speed_ = 1300.f;

	CreateCollisionComponent({ 60,60 }, static_cast<int>(COLLISION_ORDER::Monster_Attack));
	
	CreateRendererComponent("Grimm Cln_Flame_bat0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimm Cln_Flame_bat0000-Sheet.png", 0, 4, 0.040f, true));
	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);


	BirdDeathEffect_ = CreateComponent<GameEngineTextureRenderer>();
	BirdDeathEffect_->SetTexture("Grimmkin Cln_grimm_fireball_explode0000-Sheet.png");
	BirdDeathEffect_->GetTransform().SetLocalScale(BirdDeathEffect_->GetCurTexture()->GetScale());
	BirdDeathEffect_->GetTransform().SetWorldPosition({ 0, BirdDeathEffect_->GetCurTexture()->GetScale().y / 2 });

	BirdDeathEffect_->CreateFrameAnimationCutTexture("DEATH_EFFECT", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball_explode0000-Sheet.png", 0, 3, 0.040f, false));
	BirdDeathEffect_->ChangeFrameAnimation("DEATH_EFFECT");
	BirdDeathEffect_->ScaleToCutTexture(0);
	BirdDeathEffect_->Off();

	BirdDeathEffect_->AnimationBindEnd("DEATH_EFFECT", [=](const FrameAnimation_DESC& _Info)
		{
			BirdDeathEffect_->Death();
			this->Death();

		});



	GrimmBirdStateManager.CreateStateMember("MOVE"
		, std::bind(&GrimmBird::BirdMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmBird::BirdMoveStart, this, std::placeholders::_1)
		, std::bind(&GrimmBird::BirdMoveEnd, this, std::placeholders::_1));


	GrimmBirdStateManager.CreateStateMember("DEATH"
		, std::bind(&GrimmBird::BirdDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmBird::BirdDeathStart, this, std::placeholders::_1)
		, std::bind(&GrimmBird::BirdDeathEnd, this, std::placeholders::_1));

	GrimmBirdStateManager.ChangeState("MOVE");

}

void GrimmBird::Update(float _DeltaTime)
{

	GrimmBirdStateManager.Update(_DeltaTime);

}

void GrimmBird::SetMoveDir(float4 _Dir)
{
	MoveDir_ = _Dir;
	if (MoveDir_.x > 0.0f)
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		//	GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });

	}

	if (MoveDir_.x < 0.0f)
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		//GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });

	}
}

void GrimmBird::BirdMoveStart(const StateInfo& _Info)
{
}

void GrimmBird::BirdMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Move = MoveDir_ * Speed_ * _DeltaTime;
	GetTransform().SetWorldMove(Move);

	if (GetTransform().GetWorldPosition().x < 3700.f
		|| GetTransform().GetWorldPosition().x > 5900.f

		)
	{
		GrimmBirdStateManager.ChangeState("DEATH");
		return;

	}
}

void GrimmBird::BirdMoveEnd(const StateInfo& _Info)
{
}

void GrimmBird::BirdDeathStart(const StateInfo& _Info)
{
	GetRenderer()->Off();
	BirdDeathEffect_->On();

	if (MoveDir_.x > 0.0f)
	{
		BirdDeathEffect_->GetTransform().SetLocalRotation({0,0,90});
	}

	else

	{
		BirdDeathEffect_->GetTransform().SetLocalRotation({ 0,0,-90 });

	}
}

void GrimmBird::BirdDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GrimmBird::BirdDeathEnd(const StateInfo& _Info)
{
}
