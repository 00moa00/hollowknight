#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "GlobalContentsValue.h"

class GameEngineTextureRenderer;
class RendererActor : public GameEngineActor
{
public:
	// constrcuter destructer
	RendererActor();
	~RendererActor();

	// delete Function
	RendererActor(const RendererActor& _Other) = delete;
	RendererActor(RendererActor&& _Other) noexcept = delete;
	RendererActor& operator=(const RendererActor& _Other) = delete;
	RendererActor& operator=(RendererActor&& _Other) noexcept = delete;

protected:

private:
	GameEngineTextureRenderer* Renderer_;

public:

	void CreateRenderer(std::string _FileName);

	void SetRendererPivot(PIVOTMODE _Mode);

	GameEngineTextureRenderer* GetRenderer() const
	{
		return Renderer_;
	}

};

