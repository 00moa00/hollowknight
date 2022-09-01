#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class AllLocalMap : public GameEngineActor
{
public:
	// constrcuter destructer
	AllLocalMap();
	~AllLocalMap();

	// delete Function
	AllLocalMap(const AllLocalMap& _Other) = delete;
	AllLocalMap(AllLocalMap&& _Other) noexcept = delete;
	AllLocalMap& operator=(const AllLocalMap& _Other) = delete;
	AllLocalMap& operator=(AllLocalMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
public:
	void OpenAllLocalMap();
	void CloseAllLocalMap();
};

