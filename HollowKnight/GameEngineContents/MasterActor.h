#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineTextureRenderer;



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

private:
	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* CollisionMap_;
	GameEngineCollision* MainCollision_;
	GameEngineCollision* WallCollision_;

	float4 MoveDirection_;
	float4 PrevDirection_;

	float Speed_;

	bool isMove_;

	bool isOnGround_;
	bool isWall_;
	bool isCollWall_;
	bool isUpBlock_; // 위에 지형 지물이 있는지
	bool isDoubleJumpPossible_;

	float GravityY;
	float JumpSpeed_;
	float FallSpeed_;


	float4 JumpPower_;
	float4 CollisionSize_;

protected:
protected:


public:

	//================================
	//     Getter
	//================================

	//bgr

	//픽셀 충돌 체크
	void isPixelCheck(float _DeltaTime, float4 _CheckDir);
	void isPixelCheckUp(float _DeltaTime);
	void isDoubleCheckAreaCheck(float _DeltaTime);

	//_CheckDir : 현재 위치 


	float4 GetNextPos(float4 _DeltaTime);
	float4 GetNextPos(float4 _DeltaTime, float4 Dir);
	float4 GetNextPos(float4 _DeltaTime, float _Speed);

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

	GameEngineCollision* GetWallCollision() const
	{
		return WallCollision_;
	}

	float4 GetPrevDirection() const
	{
		return PrevDirection_;
	}

	float4 GetJumpPower() const
	{
		return JumpPower_;
	}

	float GetGravity() const
	{
		return GravityY;
	}

	float GetJumpSpeed() const
	{
		return JumpSpeed_;
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

	bool GetisCollWall() const
	{
		return isCollWall_;
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


	bool GetisUpBlock() const
	{
		return isUpBlock_;
	}

	bool GetisDoubleJumpPossible() const
	{
		return isDoubleJumpPossible_;
	}

	//================================
	//    Setter
	//================================

	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateRendererComponent(std::string _FileName, int _Index);
	void CreateRendererComponent( std::string _FileName);
	void CreateBloomRendererComponent(float4 _LocalScale, std::string _FileName);

	
	void CreateCollisionComponent(float4 _LocalScale, int _Order);
	void CreateWallCollisionComponent(float4 _LocalScale);

	void SetPrevDirection(float4 _Dir)
	{
		PrevDirection_ = _Dir;
	}

	void SetisCollWall(bool _b)
	{
		isCollWall_ = _b;
	}

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

	void SetisUpBlock(bool _b)
	{
		isUpBlock_ = _b;
	}

public:

	void SetCollisionMap(GameEngineTextureRenderer* _MapColl)
	{
		CollisionMap_ = _MapColl;
	}

};

