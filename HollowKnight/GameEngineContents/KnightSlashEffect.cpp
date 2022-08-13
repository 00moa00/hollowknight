#include "PreCompile.h"
#include "KnightSlashEffect.h"

KnightSlashEffect::KnightSlashEffect() 
{
}

KnightSlashEffect::~KnightSlashEffect() 
{
}

void KnightSlashEffect::Start()
{
	SetName("KnightSlashEffect");

	CreateCollisionComponent(float4{ 200, 186, 10000 }, static_cast<int>(OBJECTORDER::Knight_Slash));

	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_double_slashes_effect-Sheet.png", 2, static_cast<int>(RENDERORDER::Knight));
	
	//GetCollision()->GetTransform().SetLocalPosition({-100,0,1});
	GetRenderer()->SetScaleModeImage();
	GetRenderer()->CreateFrameAnimationCutTexture("STILL", FrameAnimation_DESC("Knight_double_slashes_effect-Sheet.png", 2, 2, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("SLASH", FrameAnimation_DESC("Knight_slashes_effect0001-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_SLASH", FrameAnimation_DESC("Knight_double_slashes_effect-Sheet.png", 0, 1, 0.100f, false));


	GetRenderer()->CreateFrameAnimationCutTexture("UP_SLASH", FrameAnimation_DESC("Knight_up_slash_effect0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOWN_SLASH", FrameAnimation_DESC("Knight_down_slash_effect0001-Sheet.png", 0, 1, 0.100f, false));

	GetRenderer()->ChangeFrameAnimation("STILL");

	GetRenderer()->AnimationBindEnd("SLASH"
		, std::bind(&KnightSlashEffect::AnimationEndSlash, this, std::placeholders::_1));

	GetRenderer()->AnimationBindEnd("DOUBLE_SLASH"
		, std::bind(&KnightSlashEffect::AnimationEndDoubleSlash, this, std::placeholders::_1));

	GetRenderer()->AnimationBindEnd("UP_SLASH"
		, std::bind(&KnightSlashEffect::AnimationEndDoubleSlash, this, std::placeholders::_1));

	GetRenderer()->AnimationBindEnd("DOWN_SLASH"
		, std::bind(&KnightSlashEffect::AnimationEndDoubleSlash, this, std::placeholders::_1));
}

void KnightSlashEffect::Update(float _DeltaTime)
{

	GetCollision()->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&KnightSlashEffect::thisVSMonsterCollision, this, std::placeholders::_1, std::placeholders::_2));


}

void KnightSlashEffect::SetAnimationSlash()
{
	GetRenderer()->ChangeFrameAnimation("SLASH");
}

void KnightSlashEffect::SetAnimationDoubleSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOUBLE_SLASH");
}

void KnightSlashEffect::SetAnimationUpSlash()
{
	GetRenderer()->ChangeFrameAnimation("UP_SLASH");
}

void KnightSlashEffect::SetAnimationDownSlash()
{
	GetRenderer()->ChangeFrameAnimation("DOWN_SLASH");
}

void KnightSlashEffect::SetAnimationStill()
{
	GetRenderer()->ChangeFrameAnimation("STILL");
}

bool KnightSlashEffect::thisVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{



	if (_Other != nullptr)
	{
		//_Other->
		//_Other->Death();
		_Other->GetActor()->Death();
		return true;

	}

	return false;
}

void KnightSlashEffect::AnimationEndSlash(const FrameAnimation_DESC& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL");
}

void KnightSlashEffect::AnimationEndDoubleSlash(const FrameAnimation_DESC& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL");
}

void KnightSlashEffect::AnimationEndUpSlash(const FrameAnimation_DESC& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL");
}

void KnightSlashEffect::AnimationEndDownSlash(const FrameAnimation_DESC& _Info)
{
	GetRenderer()->ChangeFrameAnimation("STILL");
}

