#include "PreCompile.h"
#include "GrimmFire.h"

#include <GameEngineBase/GameEngineRandom.h>



GrimmFire::GrimmFire()
	:
	CreateTimer_(0.f),
	Speed_(0.0f),
	CurvPower_(0.0f)
{
}

GrimmFire::~GrimmFire() 
{
}

void GrimmFire::Start()
{

	CreateCollisionComponent({60,60}, static_cast<int>(COLLISION_ORDER::Monster_Attack));

	Speed_ = 600.f;
	CurvPower_ = 1.2f;

	{
		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", 0, 7, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		MainRenderer_->SetScaleModeImage();
	}

	
	{

		std::vector<unsigned int>CustomAni;

		CustomAni.push_back(1);
		CustomAni.push_back(2);
		CustomAni.push_back(3);
		CustomAni.push_back(4);
		CustomAni.push_back(5);
		CustomAni.push_back(6);
		CustomAni.push_back(7);
		CustomAni.push_back(0);

		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		MainRenderer_->SetScaleModeImage();
	}

	{
		std::vector<unsigned int>CustomAni;
		CustomAni.push_back(7);
		CustomAni.push_back(0);

		CustomAni.push_back(1);
		CustomAni.push_back(2);
		CustomAni.push_back(3);
		CustomAni.push_back(4);
		CustomAni.push_back(5);
		CustomAni.push_back(6);




		GameEngineTextureRenderer* MainRenderer_;

		MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer_->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
		MainRenderer_->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		MainRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		MainRenderer_->ChangeFrameAnimation("ANIMATION");
		//MainRenderer_->ScaleToCutTexture(0);
		MainRenderer_->SetScaleModeImage();
	}

	GrimmFireBallSpectrumActor* GrimmFireBallSpectrumActor_ = GetLevel()->CreateActor< GrimmFireBallSpectrumActor>();
	//GrimmFireBallSpectrumActor_->SetParent(this);
	GrimmFireBallSpectrumActor_->GetTransform().SetLocalPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	AllSpecturumActor_.push_back(GrimmFireBallSpectrumActor_);

	CreateTimer_ = 0.0f;
}

void GrimmFire::Update(float _DeltaTime)
{

	switch (MoveType_)
	{
	case MoveType::RightDown:
		StartMoveDir_.y += CurvPower_ * _DeltaTime;
	//	Speed_ += 10.f;
		if (StartMoveDir_.y > 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::RightUp:
		StartMoveDir_.y -= CurvPower_ * _DeltaTime;
		//Speed_ += 10.f;

		if (StartMoveDir_.y < 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}
		break;
	case MoveType::Right:

		StartMoveDir_ =float4::ZERO;
		//Speed_ = 400.f;

		break;
	case MoveType::LeftDown:
		StartMoveDir_.y += CurvPower_ * _DeltaTime;
		//Speed_ += 10.f;

		if (StartMoveDir_.y > 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::LeftUp:
		StartMoveDir_.y -= CurvPower_ * _DeltaTime;
		//Speed_ += 10.f;

		if (StartMoveDir_.y < 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}
		break;
	case MoveType::Left:
		StartMoveDir_ = float4::ZERO;
		//Speed_ = 400.f;

		break;
	case MoveType::DownRight:
		StartMoveDir_.x -= CurvPower_ * _DeltaTime;
		//Speed_ += 10.f;

		if (StartMoveDir_.x < 0.0f)
		{
			MoveType_ = MoveType::Down;
			break;
		}
		break;
	case MoveType::DownLeft:
		StartMoveDir_.x += CurvPower_ * _DeltaTime;
		//Speed_ += 10.f;

		if (StartMoveDir_.x > 0.0f)
		{
			MoveType_ = MoveType::Down;
			break;
		}
		break;
	case MoveType::Down:
		StartMoveDir_ = float4::ZERO;
		//Speed_ = 400.f;

		break;
	default:
		break;
	}


	CreateTimer_ += _DeltaTime;
	GetTransform().SetWorldMove((MovePos_ + (StartMoveDir_)) * _DeltaTime * Speed_);

	if (GetAccTime() > 2.0f)
	{

		this->Death();
	}

	if (CreateTimer_ > 0.1f /*&& Count_ < 7*/)
	{
		//GrimmFireBallSpectrumActor* GrimmFireBallSpectrumActor_ = GetLevel()->CreateActor< GrimmFireBallSpectrumActor>();
		////GrimmFireBallSpectrumActor_->SetParent(this);
		//GrimmFireBallSpectrumActor_->GetTransform().SetLocalPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });

		//++Count_;
		//CreateTimer_ = 0.0f;
	}

}
void GrimmFire::SetMoveDir(float4 _Dir, MoveType _Type)
{
	MovePos_ = _Dir;

	MoveType_ = _Type;

	switch (_Type)
	{
	case MoveType::RightDown:
		StartMoveDir_ = float4::DOWN;

		break;
	case MoveType::RightUp:
		StartMoveDir_ = float4::UP;

		break;
	case MoveType::Right:
		StartMoveDir_ = float4::ZERO;
		break;
	case MoveType::LeftDown:
		StartMoveDir_ = float4::DOWN;

		break;
	case MoveType::LeftUp:
		StartMoveDir_ = float4::UP;

		break;
	case MoveType::Left:
		break;
	case MoveType::DownRight:
		StartMoveDir_ = float4::RIGHT;

		break;
	case MoveType::DownLeft:
		StartMoveDir_ = float4::LEFT;

		break;
	case MoveType::Down:
		break;
	default:
		break;
	}


	CurvPower_ =  GameEngineRandom::MainRandom.RandomFloat(0.4f, 1.1f);
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(380.f, 550.f);


}




