#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// ���� :
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

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* WallCollision_;


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

	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);
	void CreateRendererComponent(std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);
	void CreateWallCollisionComponent(float4 _LocalScale);


};

