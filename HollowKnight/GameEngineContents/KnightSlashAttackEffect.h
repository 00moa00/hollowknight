#pragma once

// 설명 : 공격 성공했을때 빠칭 하는거
class KnightSlashAttackEffect
{
public:
	// constrcuter destructer
	KnightSlashAttackEffect();
	~KnightSlashAttackEffect();

	// delete Function
	KnightSlashAttackEffect(const KnightSlashAttackEffect& _Other) = delete;
	KnightSlashAttackEffect(KnightSlashAttackEffect&& _Other) noexcept = delete;
	KnightSlashAttackEffect& operator=(const KnightSlashAttackEffect& _Other) = delete;
	KnightSlashAttackEffect& operator=(KnightSlashAttackEffect&& _Other) noexcept = delete;

protected:

private:

};

