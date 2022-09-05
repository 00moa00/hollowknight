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

protected:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

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

	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);
	void CreateRendererComponent(std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);


};

