#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class DropGeo : public GameEngineActor
{
public:
	// constrcuter destructer
	DropGeo();
	~DropGeo();

	// delete Function
	DropGeo(const DropGeo& _Other) = delete;
	DropGeo(DropGeo&& _Other) noexcept = delete;
	DropGeo& operator=(const DropGeo& _Other) = delete;
	DropGeo& operator=(DropGeo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float Speed_;

	float4 Dir_;

	GameEngineTextureRenderer* MainRenderer_;

	GameEngineCollision* MainCollision_;

	GameEngineStateManager DropGeoManager_;

private:
	void isPixelCheck(float _DeltaTime);
	void isPixelDownCheck(float _DeltaTime);

private:
	//================================
	//    Bind State
	//================================
	void DropGeoAirStart(const StateInfo& _Info);
	void DropGeoAirUpdate(float _DeltaTime, const StateInfo& _Info);
	void DropGeoAirEnd(const StateInfo& _Info);

	void DropGeoFallDownStart(const StateInfo& _Info);
	void DropGeoFallDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void DropGeoFallDownEnd(const StateInfo& _Info);

	void DropDeoOnGroundStart(const StateInfo& _Info);
	void DropDeoOnGroundUpdate(float _DeltaTime, const StateInfo& _Info);
	void DropDeoOnGroundEnd(const StateInfo& _Info);



	bool ThisVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//Ί®
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

public:
	void SetDir(float4 _Dir);
};

