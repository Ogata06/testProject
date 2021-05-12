#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <iostream>
#include <thread>
#include "XAudio2Play\XAudio2PlayBGM.h"
#include "XAudio2Play\XAudio2PlaySE.h"
#include "OggLoad/OggLoad.h"

/**
 * @file SoundManager.h
 * @brief XAudio2�̃T�E���h�Đ��@�\���܂Ƃ߂��V���O���g���N���X.
 * @author OTakotiri.
 */

class CSoundManager
{
public:
//=============================
// �\���̐錾.
//=============================
	struct SoundVolume
	{
		float MasterVolume = 1.0f;
		float BGMVolume = 1.0f;
		float SEVolume = 1.0f;
	};
public:
	CSoundManager();
	~CSoundManager();
	// �C���X�^���X�̎擾.
	static CSoundManager* GetInstance();
	// �T�E���h�f�[�^�쐬.
	static void CreateSoundData();
	// �Q�[���S�̂�BGM�̍ő剹�ʂ��擾.
	inline static const float GetGameBGMVolume()	{ return GetInstance()->m_stSound.BGMVolume * GetInstance()->m_stSound.MasterVolume; }
	// �ő�}�X�^�[���ʎ擾
	inline static const float GetMasterVolume()		{ return GetInstance()->m_stSound.MasterVolume; }
	// �ő�BGM���ʎ擾
	inline static const float GetBGMVolume()		{ return GetInstance()->m_stSound.BGMVolume; }
	// �Q�[���S�̂�SE�̍ő剹�ʂ��擾.
	inline static const float GetGameSEVolume()		{ return GetInstance()->m_stSound.SEVolume * GetInstance()->m_stSound.MasterVolume; }
	//========================================================================================
	//	BGM
	//====
	// �X���b�h�������BGM���Đ�����֐�(�O���ďo).
	static void ThreadPlayBGM(const std::string& Name, const bool& LoopFlag = true);
	// BGM��~�֐�.
	static void StopBGM(const std::string Name);
	// BGM�ꎞ��~�֐�.
	static void PauseBGM(const std::string Name);
	// BGM�čĐ��֐�
	static void AgainPlayBGM(const std::string Name);
	// BGM�t�F�[�h�A�E�g�֐�.
	static void FadeOutBGM(const std::string Name);
	// �w��BGM�̉��ʂ̃t�F�[�h�A�E�g���s������Ԃ�.
	static const bool GetFadeOutBGM(const std::string Name);
	// BGM�t�F�[�h�C���֐�.
	static void FadeInBGM(const std::string Name);
	// �w��BGM�̉��ʂ̃t�F�[�h�C�����s������Ԃ�.
	static const bool GetFadeInBGM(const std::string Name);
	// BGM�̉��ʎ擾�֐�.
	static const float GetBGMVolume(const std::string Name);
	// BGM�̉��ʃZ�b�g�֐�.
	static void SetBGMVolume(const std::string Name, const float Volume);
	// BGM���~�߂āA�X���b�h���������֐�.
	static const bool StopBGMThread(const std::string BGMName);
	// �w�肵�����O��BGM�X���b�h���Đ������ǂ�����Ԃ� : �Đ����Ȃ�true.
	static const bool GetIsPlayBGM(const std::string BGMName);
	// BGM�̃s�b�`�ݒ�.
	static void SetBGMPitch(const std::string Name, const float Value);
	//========================================================================================
	//	SE
	//====
	// SE�Đ��֐�.
	static void PlaySE(const std::string& Name);
	// ���d�Đ����Ȃ�SE�Đ��֐�.
	static void NoMultipleSEPlay(const std::string& Name);
	// SE��~�֐�.
	static void StopSE(const std::string Name, const size_t ArrayNum);
	// ���������̑S�Ă�SE�\�[�X��~�֐�.
	static void StopAllSE(const std::string Name);
	// SE��Voice�\�[�X���ő剹�ʂ�ݒ�.
	static void SetSEVolume(const std::string Name, const float Volume);
	// �w�肵�����O��SE���Đ������ǂ�����Ԃ� : �Đ����Ȃ�true.
	static bool GetIsPlaySE(const std::string Name, const size_t ArrayNum);
	// �S��SE���ʂƂ͕ʂ̃\�[�X���̉��ʂ��Z�b�g.
	static void SetAnotherSEVolume(const std::string Name, const float& Volume);
	// �\�[�X���Őݒ肳��Ă��鉹�ʂ�K�p���邩�ǂ���.
	static void SetUseAnotherSEVolumeFlag(const std::string Name, const bool& bFlag);
	// ��������֐�.
	static void Release();
	//========================================================================================
	// �I�v�V������ʗp�S�\�[�X�̃T�E���h����.
	// �}�X�^�[���ʃZ�b�g.
	static void SetMasterVolume(float& MasterVolume);
	// BGM,SE�̉��ʂ�ύX���邽�߂̃X���b�h�𗧂��グ��.
	static void CreateChangeSoundVolumeThread();
	// BGM,SE�̉��ʂ�ύX���邽�߂̃X���b�h���������.
	static bool ReleaseChangeSoundVolumeThread();
	//===========================================================
	// �I�v�V�����p�֐�.
	// ���ʂ�ύX�ł���X���b�h�̃X�e�[�g�ύX.
	static void StateChangeVolumeThread(const bool& bFlag);
	// �I�v�V�����p�X���b�h����ς݂��ǂ����̃t���O�擾�֐�.
	inline static const bool GetCreateOptionThread() { return GetInstance()->m_isCreateThread; }
public:
	SoundVolume m_stSound;
private:
	// BGM�Đ��֐�.
	static void PlayBGM(const std::string Name, bool& isEnd);
	// ���ʂ�ύX����X���b�h�𗧂Ă�.
	static void SetChangeVolumeThread();
	// ���ʏ����ݒ�֐�.
	static void VolumeInit();
	// ���݂Ȃǂ̃`�F�b�N.
	static bool CheckBGMDataIsTrue(const std::string Name);
private:
	// Ogg�f�[�^�N���X�̔�
	std::unordered_map <std::string, std::shared_ptr<COggLoad>>	m_pOggWavData;
	// BGM�pPlaySound�N���X�̔�.
	std::unordered_map <std::string, std::shared_ptr<CXAudio2PlayBGM>> pBgmSource;
	// BGM�X�g���[�~���O�Đ��p�X���b�h.
	std::unordered_map <std::string, std::thread> pBGMThread;
	// �X���b�h���ōĐ����Ă���BGM���~���邽�߂̃t���O.
	std::unordered_map <std::string, bool> m_bisEndThread;
	// �X���b�h�����[�X�p�֐�.
	std::unordered_map <std::string, bool> m_bisThreadRelease;
	// �e�X���b�hID�ێ�.
	std::unordered_map <std::string, std::thread::id> InThreadID;
	// BGM�̖��O���X�g.
	// ������ɕK�v.
	std::vector<std::string>	m_vsBGMNameList;
	// SE�̖��O���X�g.
	// ������ɕK�v.
	std::vector<std::string>	m_vsSENameList;
	// SE�pPlaySound�N���X�̔�.
	std::unordered_map <std::string, std::shared_ptr<CXAudio2PlaySE>> pSeSource;
	// �I���p�t���O.
	bool	m_bEndGame;
	// BGM,SE�̍쐬���I������ォ�ǂ���.
	bool	m_bEndCreate;
//=================================================
// �ȉ��I�v�V������ʗp.
	// �ȉ���̓X���b�h�ŉ񂳂Ȃ��ƃX�g���[�~���O�̓��ꍞ�݂�҂��Ă���̕ύX�ɂȂ邽��
	// �X���b�h�ɉ�.
	std::thread m_SoundSourceVolume;	// �I�v�V������ʂŁA���ʂ�ύX���邽�߂̃X���b�h.
	bool	m_bMoveSoundVolumeThread;	// �I�v�V������ʂŁABGM��ݒ�Ɠ����ɕύX���邽�߂̃X���b�h�p�ϐ�.
	bool	m_isCreateThread;	// ���ʕύX�̃X���b�h�������Ă��邩�ǂ���.
//------------------------------------------
// �X���b�h���b�N�p.
	bool	m_bResumeSoundVolumeThread;	// �����ϐ�.
	std::mutex m_SoundVolumemtx;
	std::condition_variable m_SoundVolumeCv;
private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CSoundManager(const CSoundManager &) = delete;
	CSoundManager& operator = (const CSoundManager &) = delete;
	CSoundManager(CSoundManager &&) = delete;
	CSoundManager& operator = (CSoundManager &&) = delete;
};

#endif // #ifndef SOUNDMANAGER_H.
