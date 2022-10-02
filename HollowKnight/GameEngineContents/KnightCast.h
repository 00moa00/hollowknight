#pragma once

// 설명 : 포 날릴때 영혼
// 콜리전 만들어서 몬스터와 닿으면 터질때 이펙트
// 벽과 닿아도 그러나?
class KnightCast
{
public:
	// constrcuter destructer
	KnightCast();
	~KnightCast();

	// delete Function
	KnightCast(const KnightCast& _Other) = delete;
	KnightCast(KnightCast&& _Other) noexcept = delete;
	KnightCast& operator=(const KnightCast& _Other) = delete;
	KnightCast& operator=(KnightCast&& _Other) noexcept = delete;

protected:

private:

};

