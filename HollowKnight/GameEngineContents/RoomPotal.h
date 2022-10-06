#pragma once
#include "MasterObject.h"
#include "PromptSet.h"
#include "FadeOut.h"
#include "FadeIn.h"

enum class POTAL_TYPE
{
	Sly_Shop,
	Map_Shop,
	Dirt,
};

// Ό³Έν :
class RoomPotal : public  MasterObject
{
public:
	// constrcuter destructer
	RoomPotal();
	~RoomPotal();

	// delete Function
	RoomPotal(const RoomPotal& _Other) = delete;
	RoomPotal(RoomPotal&& _Other) noexcept = delete;
	RoomPotal& operator=(const RoomPotal& _Other) = delete;
	RoomPotal& operator=(RoomPotal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	PromptSet* PromptSet_;

	POTAL_TYPE PotalType_;

	FadeOut* FadeOut_;
	FadeIn* FadeIn_;

public:
	void CreatePotal(POTAL_TYPE _Type, bool isPromt);
	
	POTAL_TYPE GetPotalType()
	{
		return PotalType_;
	}

private:
	bool PotalVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

