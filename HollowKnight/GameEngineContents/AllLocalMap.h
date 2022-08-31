#pragma once

// Ό³Έν :
class AllLocalMap
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

private:

};

