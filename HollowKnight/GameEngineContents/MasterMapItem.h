#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineUIRenderer;
class MasterMapItem : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterMapItem();
	~MasterMapItem();

	// delete Function
	MasterMapItem(const MasterMapItem& _Other) = delete;
	MasterMapItem(MasterMapItem&& _Other) noexcept = delete;
	MasterMapItem& operator=(const MasterMapItem& _Other) = delete;
	MasterMapItem& operator=(MasterMapItem&& _Other) noexcept = delete;

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
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateCollisionComponent(float4 _LocalScale, int _Order);


};

