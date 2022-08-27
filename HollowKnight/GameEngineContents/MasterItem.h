#pragma once

// Ό³Έν :
class MasterItem
{
public:
	// constrcuter destructer
	MasterItem();
	~MasterItem();

	// delete Function
	MasterItem(const MasterItem& _Other) = delete;
	MasterItem(MasterItem&& _Other) noexcept = delete;
	MasterItem& operator=(const MasterItem& _Other) = delete;
	MasterItem& operator=(MasterItem&& _Other) noexcept = delete;

protected:

private:

};

