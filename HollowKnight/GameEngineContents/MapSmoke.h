#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MapSmoke : public GameEngineActor
{
public:
	// constrcuter destructer
	MapSmoke();
	~MapSmoke();

	// delete Function
	MapSmoke(const MapSmoke& _Other) = delete;
	MapSmoke(MapSmoke&& _Other) noexcept = delete;
	MapSmoke& operator=(const MapSmoke& _Other) = delete;
	MapSmoke& operator=(MapSmoke&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Speed_;
	float RotatinSpeed_;

	float MapMaxX_;

	GameEngineTextureRenderer* ParticleRenderer_;

private:
};

