#pragma once
#include <GameEngineCore/CoreMinimal.h>

class GameEngineTextureRenderer;
class MasterActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterActor();
	~MasterActor();

	// delete Function
	MasterActor(const MasterActor& _Other) = delete;
	MasterActor(MasterActor&& _Other) noexcept = delete;
	MasterActor& operator=(const MasterActor& _Other) = delete;
	MasterActor& operator=(MasterActor&& _Other) noexcept = delete;

private:
	GameEngineTextureRenderer* Renderer_;

protected:
	GameEngineTextureRenderer* GetRenderer() const
	{
		return Renderer_;
	}

	void CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order);


};

