#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MapRenderer.h"


// Ό³Έν :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:

private:
	MapRenderer* MapRenderer_;

public:
	//================================
	//     Getter
	//================================
	MapRenderer* GetRenderer() const
	{
		return MapRenderer_;
	}

	//================================
	//    Setter
	//================================
	void CreateRendererComponent(float4 _LocalScale, std::string _FileName);



};

