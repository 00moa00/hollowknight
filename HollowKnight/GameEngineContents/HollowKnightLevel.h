#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Knight.h"
#include "MasterMap.h"
// Ό³Έν :
class HollowKnightLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HollowKnightLevel();
	~HollowKnightLevel();

	// delete Function
	HollowKnightLevel(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel(HollowKnightLevel&& _Other) noexcept = delete;
	HollowKnightLevel& operator=(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel& operator=(HollowKnightLevel&& _Other) noexcept = delete;

protected:

private:
	MasterMap* MasterMap_;
	Knight* Knight_;

protected:
	void CraateMasterMapActor();
	void CreateKnightActor();

	MasterMap* GetMasterMap() const
	{
		return MasterMap_;
	}

	Knight* GetKnight() const
	{
		return Knight_;
	}

};

