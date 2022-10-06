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
	BgmOff();
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

void KnightSoundManager::WindBgmOn(std::string _file, int _LoopCount)
{
	WindBgmOff();
	BgmWindPlayer = GameEngineSound::SoundPlayControl(_file, _LoopCount);
}

void KnightSoundManager::WindBgmOff()
{
	BgmWindPlayer.Stop();
}

void KnightSoundManager::WindBgmSound(float _Power)
{
	BgmWindPlayer.Volume(_Power);
}

void KnightSoundManager::KnightFallBgmOn(std::string _file, int _LoopCount)
{
	KnightFallBgmOff();
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
	KnightFootStepBgmOff();
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

void KnightSoundManager::KnightChargingBgmOn(std::string _file, int _LoopCount)
{
	KnightFootStepBgmOff();
	KnightChargingBgmPlayer = GameEngineSound::SoundPlayControl(_file, _LoopCount);
}

void KnightSoundManager::KnightChargingBgmOff()
{
	KnightChargingBgmPlayer.Stop();

}

void KnightSoundManager::KnightChargingBgmSound(float _Power)
{
	KnightChargingBgmPlayer.Volume(_Power);

}
