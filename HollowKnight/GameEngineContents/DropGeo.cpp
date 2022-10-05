#include "PreCompile.h"
#include "DropGeo.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "HollowKnightLevel.h"

DropGeo::DropGeo() 
	:
	Speed_(0.f),
	Dir_(),
	MainRenderer_(nullptr),
	MainCollision_(nullptr)
{
}

DropGeo::~DropGeo() 
{
}

void DropGeo::Start()
{
	//CreateRendererComponent(float4{ 62, 62, 1 }, "HUD Cln_HUD_coin_v020000-Sheet.png", 4, static_cast<int>(RENDERORDER::UI));
	
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture("HUD Cln_HUD_coin_v020000-Sheet.png", 0);
	MainRenderer_->GetTransform().SetLocalScale({ 30.f * 1.3f ,30.f * 1.3f, 1 });
	MainRenderer_->SetPivot(PIVOTMODE::BOT);

	MainCollision_ = CreateComponent<GameEngineCollision>();
	MainCollision_->GetTransform().SetLocalScale({ 30.f * 1.3 ,30.f * 1.3, 1 });
	MainCollision_->ChangeOrder(COLLISION_ORDER::Geo);
	MainCollision_->GetTransform().SetLocalPosition({0,(30.f )/2 });

	//================================
	//    Create Animation
	//================================
	MainRenderer_->CreateFrameAnimationCutTexture("AIR_ANIMATION", FrameAnimation_DESC("Geo_coin_air000-Sheet.png", 0, 8, 0.050f));
	MainRenderer_->CreateFrameAnimationCutTexture("GROUND_ANIMATION", FrameAnimation_DESC("Geo_coin0000-Sheet.png", 0, 7, 0.050f));
	
	//MainRenderer_->SetScaleModeImage();

	MainRenderer_->ChangeFrameAnimation("AIR_ANIMATION");
	//GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);

	//================================
	//    Create Bind Animation
	//================================

	//================================
	//    Create State
	//================================
	DropGeoManager_.CreateStateMember("AIR",
		std::bind(&DropGeo::DropGeoAirUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&DropGeo::DropGeoAirStart, this, std::placeholders::_1),
		std::bind(&DropGeo::DropGeoAirEnd, this, std::placeholders::_1));

	DropGeoManager_.CreateStateMember("FALL_DOWN",
		std::bind(&DropGeo::DropDeoOnGroundUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&DropGeo::DropDeoOnGroundStart, this, std::placeholders::_1),
		std::bind(&DropGeo::DropDeoOnGroundEnd, this, std::placeholders::_1));

	DropGeoManager_.CreateStateMember("DROP",
		std::bind(&DropGeo::DropDeoOnGroundUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&DropGeo::DropDeoOnGroundStart, this, std::placeholders::_1),
		std::bind(&DropGeo::DropDeoOnGroundEnd, this, std::placeholders::_1));

	DropGeoManager_.ChangeState("AIR");


	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-0.2f, 0.2f);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(0.2f, 2.5f);
	//Dir_.Normalize();

	Speed_ = 500.f;

}

void DropGeo::Update(float _DeltaTime)
{
	if (MainCollision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&DropGeo::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		if (GetLevel<HollowKnightLevel>()->GetHUD()->GetGeoCountFont()->SetPossibleCounting() == true)
		{
			GetLevel<HollowKnightLevel>()->GetHUD()->GetGeoCountFont()->SetCountingFont(1);
			this->Death();
		}

	}



	DropGeoManager_.Update(_DeltaTime);
}

void DropGeo::isPixelCheck(float _DeltaTime)
{
	float4 DowmPos = { GetTransform().GetWorldPosition().x ,
			-(GetTransform().GetWorldPosition().y - ((MainRenderer_-> GetTransform().GetWorldScale().y / 3))) };

	float4 DownColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(DowmPos.ix(), DowmPos.iy());
	
	if (DownColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
	{
		DropGeoManager_.ChangeState("DROP");

	}
	else
	{
	}

	while (true)
	{

		float4 CheckPos = { GetTransform().GetLocalPosition().x ,
		-(GetTransform().GetLocalPosition().y + 1.f) };

		float4 CheckColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(CheckPos.ix(), CheckPos.iy());

		if (CheckColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}
		else
		{
			break;
		}

	}

	if (Dir_.x > 0.f)
	{
		float4 RightPos = { GetTransform().GetWorldPosition().x + (MainRenderer_->GetTransform().GetWorldScale().x / 3),
			-(GetTransform().GetWorldPosition().y) };

		float4 RightColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(RightPos.ix(), RightPos.iy());

		if (RightColor.CompareInt4D(float4(0, 0, 1, 1)) == true)
		{
			Dir_.x = 0.0f;
			//DropGeoManager_.ChangeState("DROP");
		}
	}

	else
	{
		float4 LeftPos = { GetTransform().GetWorldPosition().x - (MainRenderer_->GetTransform().GetWorldScale().x / 3),
			-(GetTransform().GetWorldPosition().y) };

		float4 LeftColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(LeftPos.ix(), LeftPos.iy());

		if (LeftColor.CompareInt4D(float4(0, 0, 1, 1)) == true)
		{
			Dir_.x = 0.0f;
			//DropGeoManager_.ChangeState("DROP");
		}
	}

}

void DropGeo::isPixelDownCheck(float _DeltaTime)
{
	float4 DowmPos = { GetTransform().GetWorldPosition().x ,
		-(GetTransform().GetWorldPosition().y - ((MainRenderer_->GetTransform().GetWorldScale().y / 3))) };

	float4 DownColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(DowmPos.ix(), DowmPos.iy());

	while (true)
	{

		float4 CheckPos = { GetTransform().GetLocalPosition().x ,
		-(GetTransform().GetLocalPosition().y + 1.f) };

		float4 CheckColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(CheckPos.ix(), CheckPos.iy());

		if (CheckColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}
		else
		{
			break;
		}

	}

	if (DownColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
	{
		DropGeoManager_.ChangeState("DROP");

	}
	else
	{
	}
}

void DropGeo::DropGeoAirStart(const StateInfo& _Info)
{
}

void DropGeo::DropGeoAirUpdate(float _DeltaTime, const StateInfo& _Info)
{
	isPixelCheck(_DeltaTime);

	if (Dir_.x >= 0.f)
	{
		Dir_.x += 0.01f;
	}

	else
	{
		Dir_.x -= 0.01f;
	}

	Dir_.y -= 0.1f;
	GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);

}

void DropGeo::DropGeoAirEnd(const StateInfo& _Info)
{
}

void DropGeo::DropGeoFallDownStart(const StateInfo& _Info)
{
}

void DropGeo::DropGeoFallDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	isPixelDownCheck(_DeltaTime);

	GetTransform().SetWorldMove(float4::DOWN * Speed_ * _DeltaTime);


}

void DropGeo::DropGeoFallDownEnd(const StateInfo& _Info)
{
}

void DropGeo::DropDeoOnGroundStart(const StateInfo& _Info)
{
	MainRenderer_->ChangeFrameAnimation("GROUND_ANIMATION");

}

void DropGeo::DropDeoOnGroundUpdate(float _DeltaTime, const StateInfo& _Info)
{
	while (true)
	{

		float4 CheckPos = { GetTransform().GetLocalPosition().x ,
		-(GetTransform().GetLocalPosition().y + 1.f) };

		float4 CheckColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(CheckPos.ix(), CheckPos.iy());

		if (CheckColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}
		else
		{
			break;
		}

	}
}

void DropGeo::DropDeoOnGroundEnd(const StateInfo& _Info)
{
}

bool DropGeo::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

