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
	bool TopArrowMove_;
	bool BottomArrowMove_;

	int CurrentPointItemIndex_;

	float MoveTimer_;

	GameEngineUIRenderer* TopArrowRenderer_;
	GameEngineUIRenderer* BottomArrowRenderer_;

	GameEngineStateManager ArrowManager_;

private:
	void PixLocalNegativeY(GameEngineUIRenderer* _Renderer);
	void PixLocalPositiveY(GameEngineUIRenderer* _Renderer);

public:

	void MoveArrowUp()
	{
		ArrowManager_.ChangeState("MOVE");
		TopArrowMove_ = true;
	}

	void MoveArrowDown()
	{
		ArrowManager_.ChangeState("MOVE");
		BottomArrowMove_ = true;
	}

	int GetCurrentPointItemIndex()
	{
		return CurrentPointItemIndex_;
	}

	void SetCurrentPointItemIndex(int _i)
	{
		CurrentPointItemIndex_ = _i;
	}

private:
	//================================
	//    Bind State
	//================================

	void ArrowIdleStart(const StateInfo& _Info);
	void ArrowIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ArrowIdleEnd(const StateInfo& _Info);

	void ArrowMoveStart(const StateInfo& _Info);
	void ArrowMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void ArrowMoveEnd(const StateInfo& _Info);

	void ArrowMoveReturnStart(const StateInfo& _Info);
	void ArrowMoveReturnUpdate(float _DeltaTime, const StateInfo& _Info);
	void ArrowMoveReturnEnd(const StateInfo& _Info);


};


