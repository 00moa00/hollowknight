#pragma once
#include "MasterActor.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Knight : public MasterActor
{
public:
	// constrcuter destructer
	Knight();
	~Knight();

	// delete Function
	Knight(const Knight& _Other) = delete;
	Knight(Knight&& _Other) noexcept = delete;
	Knight& operator=(const Knight& _Other) = delete;
	Knight& operator=(Knight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End()  {}

private:
	float Speed_;
	float4 MoveDirection_;
	bool isMove_;

	std::vector<GameEngineTextureRenderer*> MapCollTexture_;
	std::vector<float4> MapCollisionColorList_;

private:
	//float4 
	//bool CheckMapCollision();

	void MapCollisionLoad();
	bool GetisPlayerMove();

public:
	void InsertMapCollisionTexture(std::vector<GameEngineTextureRenderer*> _VectorList);

}; 

