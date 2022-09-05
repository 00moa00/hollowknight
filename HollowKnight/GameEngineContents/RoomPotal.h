#pragma once
#include "MasterObject.h"
#include "PromptSet.h"

enum class POTAL_TYPE
{
	Sly_Shop,
	 Map_Shop
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

private:
	PromptSet* PromptSet_;

	POTAL_TYPE POTAL_TYPE_;

public:
	void CreatePotal(POTAL_TYPE _Type);
	
	POTAL_TYPE GetPotalType()
	{
		return POTAL_TYPE_;
	}

};

