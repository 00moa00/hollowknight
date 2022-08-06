#pragma once

// Ό³Έν :
class Crawlid
{
public:
	// constrcuter destructer
	Crawlid();
	~Crawlid();

	// delete Function
	Crawlid(const Crawlid& _Other) = delete;
	Crawlid(Crawlid&& _Other) noexcept = delete;
	Crawlid& operator=(const Crawlid& _Other) = delete;
	Crawlid& operator=(Crawlid&& _Other) noexcept = delete;

protected:

private:

};

