#pragma once

// 설명 : 포 날릴때 플레이어 이펙트 
class KnightCastEffect
{
public:
	// constrcuter destructer
	KnightCastEffect();
	~KnightCastEffect();

	// delete Function
	KnightCastEffect(const KnightCastEffect& _Other) = delete;
	KnightCastEffect(KnightCastEffect&& _Other) noexcept = delete;
	KnightCastEffect& operator=(const KnightCastEffect& _Other) = delete;
	KnightCastEffect& operator=(KnightCastEffect&& _Other) noexcept = delete;

protected:

private:

};

