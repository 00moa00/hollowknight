#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineTextureRenderer;

class PixelPOINT
{
public:
	float RightBottom_;
	float LeftBottom_;
	float RightTop_;
	float LeftTop_;



};


class MasterActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterActor();
	~MasterActor();

	// delete Function
	MasterActor(const MasterActor& _Other) = delete;
	MasterActor(MasterActor&& _Other) noexcept = delete;
	MasterActor& operator=(const MasterActor& _Other) = delete;
	MasterActor& operator=(MasterActor&& _Other) noexcept = delete;

protected:
	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* CollisionMap_;
	GameEngineCollision* MainCollision_;

	float4 MoveDirection_;

	float Speed_;

	bool isMove_;
	bool isOnGround_;
	bool isWall_;

	float GravityY;
	float JumpSpeed_;
	float FallSpeed_;


	float4 JumpPower_;
	float4 FallDownDirection_;
	float4 CollisionSize_;

protected:
protected:

	PixelPOINT Point_;

protected:

	//================================
	//     Getter
	//================================

	//bgr
	bool GetPixelRed(float4 _NextDir);
	bool GetPixelBlue(float4 _NextDir);

	//픽셀 충돌 체크
	void isOnGroundCheck(float _DeltaTime);
	void isWallCheck(float _DeltaTime);
	float4 GetNextPos(float4 _DeltaTime);

	GameEngineTextureRenderer* GetRenderer() const
	{
		return MainRenderer_;
	}

	GameEngineTextureRenderer* GetCollisionMap() const
	{
		return CollisionMap_;
	}

	GameEngineCollision* GetCollision() const
	{
		return MainCollision_;
	}



	float GetRightBottom()
	{
		return Point_.RightBottom_;
	}

	float GetLeftBottom()
	{
		return Point_.LeftBottom_;
	}

	float GetRightTop()
	{
		return Point_.RightTop_;
	}

	float GetLeftTop()
	{
		return Point_.LeftTop_;
	}

	void SetRightBottom(float _f)
	{
		Point_.RightBottom_ = _f;
	}

	void SetLeftBottom(float _f)
	{
		Point_.LeftBottom_ = _f;
	}

	void SetRightTop(float _f)
	{
		Point_.RightTop_ = _f;
	}

	void SetLeftTop(float _f)
	{
		Point_.LeftTop_ = _f;
	}


	float4 GetJumpPower() const
	{
		return JumpPower_;
	}

	PixelPOINT dfdf()
	{
		return Point_;
	}


	float GetGravity() const
	{
		return GravityY;
	}

	float GetJumpSpeed() const
	{
		return JumpSpeed_;
	}


	float4 GetFallDownDirection() const
	{
		return FallDownDirection_;
	}

	float4 GetCollisionSize() const
	{
		return CollisionSize_;
	}

	float GetFallSpeed() const
	{
		return FallSpeed_;
	}

	float4 GetMoveDirection() const
	{
		return MoveDirection_;
	}

	float GetSpeed() const
	{
		return Speed_;
	}

	bool GetisMove() const
	{
		return isMove_;
	}

	bool GetisOnGround() const
	{
		return isOnGround_;
	}

	bool GetisWall() const
	{
		return isWall_;
	}


	//================================
	//    Setter
	//================================

	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateCollisionComponent(float4 _LocalScale, int _Order);

	void SetJumpSpeed(float _JumpSpeed)
	{
		JumpSpeed_ = _JumpSpeed;
	}

	void SetGravity(float _GravityY)
	{
		GravityY = _GravityY;
	}

	void SetJumpPower(float4 _JumpPower)
	{
		JumpPower_ = _JumpPower;
	}

	void SubJumpPower(float4 _JumpPower)
	{
		JumpPower_ -= _JumpPower;
	}

	void SetallDownDirection(float4 _FallDownDirection)
	{
		FallDownDirection_ = _FallDownDirection;
	}

	void SetCollisionSize(float4 _CollisionSize)
	{
		CollisionSize_ = _CollisionSize;
	}

	void SetFallSpeed(float _FallSpeed)
	{
		FallSpeed_ = _FallSpeed;
	}

	void SetMoveDirectionNormalize()
	{
		MoveDirection_.Normalize();
	}

	void SetMoveDirection(float4 _Dir)
	{
		MoveDirection_ = _Dir;
	}

	void AddMoveDirection(float4 _Dir)
	{
		MoveDirection_ += _Dir;
	}

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	void SetisMove(bool _b)
	{
		isMove_ = _b;
	}

	void SetisGround(bool _b)
	{
		isOnGround_ = _b;
	}

	void SetisWall(bool _b)
	{
		isWall_ = _b;
	}

public:

	void SetCollisionMap(GameEngineTextureRenderer* _MapColl)
	{
		CollisionMap_ = _MapColl;
	}

};

