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

	float4 LightMulColor_;
	float4 LightPlusColor_;

	BlendMode BlendMode_;

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

	float4 GetLightMulColor() const
	{
		return LightMulColor_;
	}

	float4 GetLightPlusColor() const
	{
		return LightPlusColor_;
	}


	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateRendererComponent(float4 _LocalScale, std::string _FileNameint);
	void CreateRendererComponent(std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);

	void SetBlendMode(BlendMode _Mode);
	void SetMulColor(float4 _MulColor);
	void SetPlusColor(float4 _PlusColor);
};

