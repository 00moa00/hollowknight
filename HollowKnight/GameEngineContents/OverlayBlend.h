#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineUIRenderer;
class OverlayBlend : public GameEngineActor
{
public:
	// constrcuter destructer
	OverlayBlend();
	~OverlayBlend();

	// delete Function
	OverlayBlend(const OverlayBlend& _Other) = delete;
	OverlayBlend(OverlayBlend&& _Other) noexcept = delete;
	OverlayBlend& operator=(const OverlayBlend& _Other) = delete;
	OverlayBlend& operator=(OverlayBlend&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	GameEngineTextureRenderer* Renderer_;

private:
public:
	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

};

