#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineUIRenderer;
class MasterUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterUI();
	~MasterUI();

	// delete Function
	MasterUI(const MasterUI& _Other) = delete;
	MasterUI(MasterUI&& _Other) noexcept = delete;
	MasterUI& operator=(const MasterUI& _Other) = delete;
	MasterUI& operator=(MasterUI&& _Other) noexcept = delete;

protected:
	GameEngineUIRenderer* Renderer_;
	GameEngineCollision* Collision_;

public:
	//================================
	//     Getter
	//================================
	GameEngineUIRenderer* GetRenderer() const
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
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);
	void CreateRendererComponent(std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);

	void PixLocalNegativeY();
	void PixLocalPositiveY();

	void ChangeAnimation(std::string _Name);
	



};

