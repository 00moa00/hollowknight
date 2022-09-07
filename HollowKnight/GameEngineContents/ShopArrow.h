#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineUIRenderer;
class ShopArrow : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopArrow();
	~ShopArrow();

	// delete Function
	ShopArrow(const ShopArrow& _Other) = delete;
	ShopArrow(ShopArrow&& _Other) noexcept = delete;
	ShopArrow& operator=(const ShopArrow& _Other) = delete;
	ShopArrow& operator=(ShopArrow&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

private:
	int CurrentPointItemIndex_;

	GameEngineUIRenderer* TopArrowRenderer_;
	GameEngineUIRenderer* BottomArrowRenderer_;

private:
	void PixLocalNegativeY(GameEngineUIRenderer* _Renderer);
	void PixLocalPositiveY(GameEngineUIRenderer* _Renderer);

public:
	int GetCurrentPointItemIndex()
	{
		return CurrentPointItemIndex_;
	}

	void SetCurrentPointItemIndex(int _i)
	{
		CurrentPointItemIndex_ = _i;
	}

};

