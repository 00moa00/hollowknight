#include "PreCompile.h"
#include "KnightSoundManager.h"

KnightSoundManager* KnightSoundManager::Inst_ = new KnightSoundManager();

KnightSoundManager::KnightSoundManager() 
	:
	BgmPlayer()
{
}

KnightSoundManager::~KnightSoundManager() 
{
}

void KnightSoundManager::BgmOn(std::string _file, int _LoopCount)
{
	BgmPlayer = GameEngineSound::SoundPlayControl(_file, _LoopCount);
}

void KnightSoundManager::BgmOff()
{
	BgmPlayer.Stop();
}

void KnightSoundManager::BgmSound(float _Power)
{
	BgmPlayer.Volume(_Power);
}

void KnightSoundManager::KnightFallBgmOn(std::string _file, int _LoopCount)
{
	KnightFallBgmPlayer = GameEngineSound::SoundPlayControl(_file, _LoopCount);
}

void KnightSoundManager::KnightFallBgmOff()
{
	KnightFallBgmPlayer.Stop();
}

void KnightSoundManager::KnightFallBgmSound(float _Power)
{
	KnightFallBgmPlayer.Volume(_Power);
}

void KnightSoundManager::KnightFootStepBgmOn(std::string _file, int _LoopCount)
{
	KnightSoundManager::GetInst()->KnightFootStepBgmOff();
	KnightFootStepBgmPlayer = GameEngineSound::SoundPlayControl(_file, _LoopCount);
}

void KnightSoundManager::KnightFootStepBgmOff()
{
	KnightFootStepBgmPlayer.Stop();
}

void KnightSoundManager::KnightFootStepBgmSound(float _Power)
{
	KnightFootStepBgmPlayer.Volume(_Power);

}
