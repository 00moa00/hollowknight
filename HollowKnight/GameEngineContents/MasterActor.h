#pragma once
#include <GameEngineCore/CoreMinimal.h>

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

	float4 MoveDirection_;

	float Speed_;

	bool isMove_;
	bool isOnGround_;


protected:

	//================================
	//     Getter
	//================================

	GameEngineTextureRenderer* GetRenderer() const
	{
		return MainRenderer_;
	}

	GameEngineTextureRenderer* GetCollisionMap() const
	{
		return CollisionMap_;
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


	//================================
	//    Setter
	//================================

	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);

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

public:

	void SetCollisionMap(GameEngineTextureRenderer* _MapColl)
	{
		CollisionMap_ = _MapColl;
	}

};

