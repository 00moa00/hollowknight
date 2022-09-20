#pragma once
#include "MasterObject.h"

// Ό³Έν :
class BossRoomGate : public  MasterObject
{
public:
	// constrcuter destructer
	BossRoomGate();
	~BossRoomGate();

	// delete Function
	BossRoomGate(const BossRoomGate& _Other) = delete;
	BossRoomGate(BossRoomGate&& _Other) noexcept = delete;
	BossRoomGate& operator=(const BossRoomGate& _Other) = delete;
	BossRoomGate& operator=(BossRoomGate&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

