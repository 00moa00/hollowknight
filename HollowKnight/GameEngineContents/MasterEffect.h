#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineTextureRenderer;
class MasterEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterEffect();
	~MasterEffect();

	// delete Function
	MasterEffect(const MasterEffect& _Other) = delete;
	MasterEffect(MasterEffect&& _Other) noexcept = delete;
	MasterEffect& operator=(const MasterEffect& _Other) = delete;
	MasterEffect& operator=(MasterEffect&& _Other) noexcept = delete;

protected:

private:
	GameEngineTextureRenderer* MainRenderer_;
	GameEngineCollision* MainCollision_;

	float4 Direction_;
	float4 CollisionSize_;

public:

	//================================
	//     Getter
	//================================

	GameEngineTextureRenderer* GetRenderer() const
	{
		return MainRenderer_;
	}

	GameEngineCollision* GetCollision() const
	{
		return MainCollision_;
	}


	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateRendererComponent(float4 _LocalScale, std::string _FileNameint);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);
};

