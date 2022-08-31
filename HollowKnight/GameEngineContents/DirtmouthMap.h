#pragma once

// Ό³Έν :
class DirtmouthMap
{
public:
	// constrcuter destructer
	DirtmouthMap();
	~DirtmouthMap();

	// delete Function
	DirtmouthMap(const DirtmouthMap& _Other) = delete;
	DirtmouthMap(DirtmouthMap&& _Other) noexcept = delete;
	DirtmouthMap& operator=(const DirtmouthMap& _Other) = delete;
	DirtmouthMap& operator=(DirtmouthMap&& _Other) noexcept = delete;

protected:

private:

};

