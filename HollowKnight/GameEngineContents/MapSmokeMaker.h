#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MapSmokeMaker : public GameEngineActor
{
public:
	// constrcuter destructer
	MapSmokeMaker();
	~MapSmokeMaker();

	// delete Function
	MapSmokeMaker(const MapSmokeMaker& _Other) = delete;
	MapSmokeMaker(MapSmokeMaker&& _Other) noexcept = delete;
	MapSmokeMaker& operator=(const MapSmokeMaker& _Other) = delete;
	MapSmokeMaker& operator=(MapSmokeMaker&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

