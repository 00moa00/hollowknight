#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineUIRenderer;

// Ό³Έν :
class SettingUIMaster : public GameEngineActor
{
	
public:
	// constrcuter destructer
	SettingUIMaster();
	~SettingUIMaster();

	// delete Function
	SettingUIMaster(const SettingUIMaster& _Other) = delete;
	SettingUIMaster(SettingUIMaster&& _Other) noexcept = delete;
	SettingUIMaster& operator=(const SettingUIMaster& _Other) = delete;
	SettingUIMaster& operator=(SettingUIMaster&& _Other) noexcept = delete;

protected:
	float4 PointerSize_;
	
	GameEngineUIRenderer* Renderer_;

public:

	virtual void SelectSettingPointer();

	//================================
	//     Getter
	//================================
	GameEngineUIRenderer* GetRenderer() const
	{
		return Renderer_;
	}

	float4 GetPointerSize() const
	{
		return PointerSize_;
	}


	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);

	void CreateCollisionComponent(float4 _LocalScale, int _Order);

	void PixLocalNegativeY();
	void PixLocalPositiveY();

	void ChangeAnimation(std::string _Name);


	void SetPointerSize(float4 _Size)
	{
		PointerSize_ = _Size;
	}
	
};

