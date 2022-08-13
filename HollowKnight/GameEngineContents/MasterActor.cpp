#include "PreCompile.h"
#include "MasterActor.h"

MasterActor::MasterActor() 
	:
	MainRenderer_(nullptr),
	CollisionMap_(nullptr),
	MainCollision_(nullptr),
	GravityY(),
	JumpPower_(),
	CollisionSize_(),
	FallSpeed_(),
	Speed_ (),

	FallDownDirection_(float4::DOWN),
	MoveDirection_(float4::ZERO),

	isMove_(true),
	isOnGround_(false),
	isWall_(false),
	isUpBlock_(false)
{
}

MasterActor::~MasterActor() 
{
}

void MasterActor::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1});
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
	//MainRenderer_->GetTransform().SetLocalPosition({ MainRenderer_->GetTransform().GetLocalPosition().x, MainRenderer_->GetTransform().GetLocalPosition().y, 0.1 });
	
}

void MasterActor::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	MainCollision_ = CreateComponent<GameEngineCollision>();
	MainCollision_->GetTransform().SetLocalScale(_LocalScale);
	MainCollision_->ChangeOrder(_Order);
}

bool MasterActor::GetPixelRed(float4 _NextPos)
{
	//float4 GetDirPos = { GetTransform().GetLocalPosition().ix() + _NextPos.x ,
	//	-(GetTransform().GetLocalPosition().iy() + _NextPos.y) };


	//if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	//{
	//	//GetPixelPos += GetRightBottom();
	//	GetDirPos += GetLeftBottom();
	//}

	//else if (GetMoveDirection().CompareInt2D(float4::LEFT))
	//{
	//	//GetPixelPos += GetLeftBottom();
	//	GetDirPos += GetRightBottom();

	//}

	//float4 DirColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GetDirPos.ix(), GetDirPos.iy());


	float4 GetBottomPos = { GetTransform().GetLocalPosition().ix() + _NextPos.x ,
	-(GetTransform().GetLocalPosition().iy() + _NextPos.y) };


	float4 BottomColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GetBottomPos.ix(), GetBottomPos.iy());




	if (BottomColor.CompareInt4D(float4(1.f, 0, 0, 1.f)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MasterActor::GetPixelBlue(float4 _NextPos)
{
	float4 GetCenterPos = { GetTransform().GetLocalPosition().ix() + _NextPos.x ,
		-(GetTransform().GetLocalPosition().iy() + _NextPos.y )};


	GetCenterPos += GetCenter();

	float4 CenterColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GetCenterPos.ix(), GetCenterPos.iy());


	float4 GetBottomPos = { GetTransform().GetLocalPosition().ix() + _NextPos.x ,
	-(GetTransform().GetLocalPosition().iy() + _NextPos.y) };


	GetMoveDirection().Normalize();
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		//GetPixelPos += GetRightBottom();
		GetBottomPos += GetRightCenter();
	}

	else if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		//GetPixelPos += GetLeftBottom();
		GetBottomPos += GetLeftCenter();

	}

	float4 BottomColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GetBottomPos.ix(), GetBottomPos.iy());




	if (CenterColor.CompareInt4D(float4(0, 0, 1, 1)) == true && BottomColor.CompareInt4D(float4(0, 0, 1, 1)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MasterActor::isOnGroundCheck(float _DeltaTime)
{
	if (GetPixelRed(GetNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
	}

	else
	{
		this->SetisGround(false);
	}

}

void MasterActor::isWallCheck(float _DeltaTime)
{
	//GetRenderer()->GetCurTexture()->
	if (GetPixelBlue(GetNextPos(_DeltaTime)) == true)
	{
		this->SetisWall(true);
	}

	else
	{
		this->SetisWall(false);
	}
}

void MasterActor::isDownGroundCheck(float _DeltaTime)
{
	if (GetPixelRed(GetNextPos(_DeltaTime, float4::DOWN)) == true)
	{
		this->SetisGround(true);
	}

	else
	{
		this->SetisGround(false);
	}
}

void MasterActor::isUpBlockCheck(float _DeltaTime)
{
	float4 NextPos = GetNextPos(_DeltaTime);
	NextPos += GetCenterTop();


	if (GetPixelBlue(NextPos) == true)
	{
		this->SetisUpBlock(true);
	}

	else
	{
		this->SetisUpBlock(false);
	}
}

float4 MasterActor::GetNextPos(float4 _DeltaTime)
{
	//this->SetMoveDirectionNormalize();

	GetMoveDirection().Normalize();

	return (GetMoveDirection() * _DeltaTime * GetSpeed());
}

float4 MasterActor::GetNextPos(float4 _DeltaTime, float4 Dir)
{
	return (Dir * _DeltaTime * GetSpeed());
}
