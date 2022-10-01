#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MapWhiteParticleWindMaker : public GameEngineActor
{
public:
	// constrcuter destructer
	MapWhiteParticleWindMaker();
	~MapWhiteParticleWindMaker();

	// delete Function
	MapWhiteParticleWindMaker(const MapWhiteParticleWindMaker& _Other) = delete;
	MapWhiteParticleWindMaker(MapWhiteParticleWindMaker&& _Other) noexcept = delete;
	MapWhiteParticleWindMaker& operator=(const MapWhiteParticleWindMaker& _Other) = delete;
	MapWhiteParticleWindMaker& operator=(MapWhiteParticleWindMaker&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

