#pragma once
#include <GameEngineCore/CoreMinimal.h>

class GameEngineUIRenderer;
// Ό³Έν :
class UIPoint : public GameEngineActor
{
public:
	// constrcuter destructer
	UIPoint();
	~UIPoint();

	// delete Function
	UIPoint(const UIPoint& _Other) = delete;
	UIPoint(UIPoint&& _Other) noexcept = delete;
	UIPoint& operator=(const UIPoint& _Other) = delete;
	UIPoint& operator=(UIPoint&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

private:
	GameEngineUIRenderer* LeftPoint_;
	GameEngineUIRenderer* RightPoint_;

	float4 PointScale_;

public:
	void SetPointChangeUpdateAnimation();
	void SetPointChangeIdleAnimation();
	
	void SetLeffPointLocalPosition(float4 _LocalPosition);
	void SetRightPointLocalPosition(float4 _LocalPosition);

private:
	void PointAnimationLeftEnd(const FrameAnimation_DESC& _Info);
	void PointAnimationRightEnd(const FrameAnimation_DESC& _Info);


};

