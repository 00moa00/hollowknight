#include "PreCompile.h"
#include "GrimmFire.h"

#include <GameEngineBase/GameEngineRandom.h>



GrimmFire::GrimmFire()
	:
	CreateTimer_(0.f),
	Speed_(0.0f),
	CurvPower_(0.0f),
	Count_(0),
	SubScale_(0),
	MoveType_(MoveType::Down),
	GrimmFireStateManager(),

	FireBallRenderer1(nullptr),
	FireBallRenderer2(nullptr),
	FireBallRenderer3(nullptr)
{
}

GrimmFire::~GrimmFire() 
{
}

void GrimmFire::Start()
{

	CreateCollisionComponent({60,60}, static_cast<int>(COLLISION_ORDER::Monster_Attack));
	SubScale_ = 1.0f;
	Speed_ = 600.f;
	CurvPower_ = 1.2f;

	{

		FireBallRenderer1 = CreateComponent<GameEngineTextureRenderer>();
		FireBallRenderer1->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		//FireBallRenderer1->ScaleToCutTexture(0);

		FireBallRenderer1->GetTransform().SetLocalScale({151, 164});
		FireBallRenderer1->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		FireBallRenderer1->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", 0, 7, 0.040f, true));
		FireBallRenderer1->ChangeFrameAnimation("ANIMATION");
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


		FireBallRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		FireBallRenderer2->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");
		FireBallRenderer2->GetTransform().SetLocalScale({ 151, 164 });

		//FireBallRenderer2->GetTransform().SetLocalScale(FireBallRenderer2->GetCurTexture()->GetScale());
		FireBallRenderer2->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		FireBallRenderer2->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		FireBallRenderer2->ChangeFrameAnimation("ANIMATION");
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





		FireBallRenderer3 = CreateComponent<GameEngineTextureRenderer>();
		FireBallRenderer3->SetTexture("Grimmkin Cln_grimm_fireball0000-Sheet.png");

		//FireBallRenderer3->GetTransform().SetLocalScale(FireBallRenderer3->GetCurTexture()->GetScale());
		FireBallRenderer3->GetPipeLine()->SetOutputMergerBlend("AddBlend");
		FireBallRenderer3->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Grimmkin Cln_grimm_fireball0000-Sheet.png", CustomAni, 0.040f, true));
		FireBallRenderer3->ChangeFrameAnimation("ANIMATION");
		FireBallRenderer3->GetTransform().SetLocalScale({ 151, 164 });
		//MainRenderer_->ScaleToCutTexture(0);
	}

	//GrimmFireBallSpectrumActor* GrimmFireBallSpectrumActor_ = GetLevel()->CreateActor< GrimmFireBallSpectrumActor>();
	////GrimmFireBallSpectrumActor_->SetParent(this);
	//GrimmFireBallSpectrumActor_->GetTransform().SetLocalPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	////AllSpecturumActor_.push_back(GrimmFireBallSpectrumActor_);

	CreateTimer_ = 0.0f;


	GrimmFireStateManager.CreateStateMember("MOVE"
		, std::bind(&GrimmFire::FireMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmFire::FireMoveStart, this, std::placeholders::_1)
		, std::bind(&GrimmFire::FireMoveEnd, this, std::placeholders::_1));

	GrimmFireStateManager.CreateStateMember("DEATH"
		, std::bind(&GrimmFire::FireDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmFire::FireDeathStart, this, std::placeholders::_1)
		, std::bind(&GrimmFire::FireDeathEnd, this, std::placeholders::_1));

	GrimmFireStateManager.ChangeState("MOVE");
}

void GrimmFire::Update(float _DeltaTime)
{
	GrimmFireStateManager.Update(_DeltaTime);
	

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

void GrimmFire::FireMoveStart(const StateInfo& _Info)
{
}

void GrimmFire::FireMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	switch (MoveType_)
	{
	case MoveType::RightDown:
		StartMoveDir_.y += CurvPower_ * _DeltaTime;
		if (StartMoveDir_.y > 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::RightUp:
		StartMoveDir_.y -= CurvPower_ * _DeltaTime;

		if (StartMoveDir_.y < 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::Right:

		StartMoveDir_ = float4::ZERO;

		break;
	case MoveType::LeftDown:
		StartMoveDir_.y += CurvPower_ * _DeltaTime;

		if (StartMoveDir_.y > 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::LeftUp:
		StartMoveDir_.y -= CurvPower_ * _DeltaTime;

		if (StartMoveDir_.y < 0.0f)
		{
			MoveType_ = MoveType::Right;
			break;
		}

		break;
	case MoveType::Left:
		StartMoveDir_ = float4::ZERO;
		break;
	case MoveType::DownRight:
		StartMoveDir_.x -= CurvPower_ * _DeltaTime;

		if (StartMoveDir_.x < 0.0f)
		{
			MoveType_ = MoveType::Down;
			break;
		}
		break;
	case MoveType::DownLeft:
		StartMoveDir_.x += CurvPower_ * _DeltaTime;

		if (StartMoveDir_.x > 0.0f)
		{
			MoveType_ = MoveType::Down;
			break;
		}
		break;
	case MoveType::Down:
		StartMoveDir_ = float4::ZERO;
		break;
	default:
		break;
	}

	CreateTimer_ += _DeltaTime;
	GetTransform().SetWorldMove((MovePos_ + (StartMoveDir_)) * _DeltaTime * Speed_);

	//if (GetAccTime() > 2.0f)
	//{
	//	this->Death();
	//}

	if (GetTransform().GetWorldPosition().x < 3700.f
		|| GetTransform().GetWorldPosition().x > 5900.f
		|| GetTransform().GetWorldPosition().y < -950.f
		
		)
	{
		GrimmFireStateManager.ChangeState("DEATH");
		return;

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

void GrimmFire::FireMoveEnd(const StateInfo& _Info)
{
}

void GrimmFire::FireDeathStart(const StateInfo& _Info)
{
	SubScale_ = 1.0f;

}

void GrimmFire::FireDeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SubScale_ -= 0.1 * _DeltaTime;

	FireBallRenderer1->GetTransform().SetLocalScale(FireBallRenderer1->GetTransform().GetLocalScale() * SubScale_);
	FireBallRenderer2->GetTransform().SetLocalScale(FireBallRenderer1->GetTransform().GetLocalScale() * SubScale_);
	FireBallRenderer3->GetTransform().SetLocalScale(FireBallRenderer1->GetTransform().GetLocalScale() * SubScale_);


	if (SubScale_ <= 0.f)
	{
		Death();
	}
}

void GrimmFire::FireDeathEnd(const StateInfo& _Info)
{
}




