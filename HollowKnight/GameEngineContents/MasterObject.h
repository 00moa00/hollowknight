#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class MasterObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterObject();
	~MasterObject();

	// delete Function
	MasterObject(const MasterObject& _Other) = delete;
	MasterObject(MasterObject&& _Other) noexcept = delete;
	MasterObject& operator=(const MasterObject& _Other) = delete;
	MasterObject& operator=(MasterObject&& _Other) noexcept = delete;

public:
	virtual void SetHitCollision(){};

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* WallCollision_;

	int HitCount_;



protected:
	//================================
	//     Getter
	//================================
	GameEngineTextureRenderer* GetRenderer() const
	{
		return Renderer_;
	}

	GameEngineCollision* GetCollision() const
	{
		return Collision_;
	}


	GameEngineCollision* GetWallCollision() const
	{
		return WallCollision_;
	}

	int GetHitCount()
	{
		return HitCount_;
	}

	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);
	void CreateRendererComponent(std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);
	void CreateWallCollisionComponent(float4 _LocalScale);

	void SetHitCount(int _i)
	{
		HitCount_ = _i;
	}

	void SubHitCount()
	{
		--HitCount_;
		if (HitCount_ <= 0)
		{
			HitCount_ = 0;
		}
	}

};

