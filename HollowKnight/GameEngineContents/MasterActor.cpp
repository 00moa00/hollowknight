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
	isWall_(false)
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

bool MasterActor::GetPixelRed(float4 _NextDir)
{
	float DirSize = 0;
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		DirSize = 50.f;
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		DirSize = -50.f;
	}
	float4 Color = GetCollisionMap()->GetCurTexture()->GetPixel(GetTransform().GetLocalPosition().ix() + _NextDir.x + GetCollisionSize().x,
		-(GetTransform().GetLocalPosition().iy() + _NextDir.y - GetCollisionSize().y));

	if (Color.CompareInt4D(float4(0, 0, 1, 1)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MasterActor::GetPixelBlue(float4 _NextDir)
{

	float DirSize = 0;
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		DirSize = 50.f;
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		DirSize = -50.f;
	}





	float4 Color = GetCollisionMap()->GetCurTexture()->GetPixel(GetTransform().GetLocalPosition().ix() + _NextDir.x + DirSize,
		-(GetTransform().GetLocalPosition().iy() + _NextDir.y - GetCollisionSize().y));

	if (Color.CompareInt4D(float4(1, 0, 0, 1)) == true)
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

float4 MasterActor::GetNextPos(float4 _DeltaTime)
{
	this->SetMoveDirectionNormalize();
	return (GetMoveDirection() * _DeltaTime * GetSpeed());
}
