#ifndef XAUDIO2_PLAYSE_H
#define XAUDIO2_PLAYSE_H


#include <vector>
#include <mutex>
#include "..\XAudio2.h"
#include "..\XAudio2Master\XAudio2MasterVoice.h"
#include "..\OggLoad\OggLoad.h"
#include "..\XAudio2CallBack\VoiceCallBack.h"

struct IXAudio2SourceVoice;

/**
 * @file XAudio2PlaySE.h
 * @brief XAudio2�ł�SE�Đ���ړI�Ƃ����N���X.
 * @author OTakotiri.
 */

class CXAudio2PlaySE
{
private:
	static const int SE_VOICE_SIZE = 10;	// SE�̗\���̐�.
public:
	// �R���X�g���N�^.
	CXAudio2PlaySE();
	// �f�X�g���N�^.
	virtual ~CXAudio2PlaySE();
	// SE���Đ�������Ԃ�.
	const bool IsPlayingSE(const size_t ArrayNum);
	// ���d�Đ��\�ȃT�E���h�Đ�.
	virtual bool Play( std::shared_ptr<COggLoad> pWavData);
	// ���d�Đ����Ȃ��T�E���h�Đ�.
	bool NoMultiplePlay(std::shared_ptr<COggLoad> pWavData);
	// SE�T�E���h��~.
	bool SeStop(const size_t ArrayNum);
	// �쐬���Ă�\������SE����~.
	bool AllSeStop();

	HRESULT CreateOggSound(std::shared_ptr<COggLoad> pOggData, const char* filename);
	//=======================================================================
	// ��{���ʑ���n.
	//====

	// SE��Voice�\�[�X���ő剹�ʂ�ݒ�.
	void SetMaxSEVolume(const float& fMaxVolume) { m_fSEVolume = fMaxVolume; }
	// SE��Voice�\�[�X���ő剹�ʂ��擾.
	const float GetMaxSEVolume() { return m_fSEVolume; }
	// SE�̉��ʂ��擾���܂�.
	const float GetSEVolume(size_t Array);
	// SE�̉��ʂ�ݒ肵�܂�.
	bool SetSEVolume(float value, size_t Array);
	// SoundSource��j�󂷂�֐�.
	void DestoroySource();
	// �S��SE���ʂƂ͕ʂ̃\�[�X���̉��ʂ��Z�b�g.
	void SetAnotherSEVolume(const float& fVolume) { m_fAnotherVolume = fVolume; }
	// �\�[�X���Őݒ肳��Ă��鉹�ʂ�K�p���邩�ǂ���.
	void SetUseAnotherSEVolume(const float& bFlag) { m_bisAnotherVolume = bFlag; }
protected:
	int		CheckPlaySeBuffer();
protected:
	COggLoad*				m_pOggData; // Ogg�f�[�^���[�h�N���X.

	IXAudio2SourceVoice*	m_pSourceVoice[SE_VOICE_SIZE];		// ����SE�𓯎��ɂȂ点��悤�ɔz��ɂ���.
	bool				m_bisAnotherVolume;
	float				m_fAnotherVolume;
	int					m_CheckNonePlaySeVoice;					// �Đ����Ă��Ȃ�SE��􂢏o���p.
	int					m_RepeatPlaySe;							// �S�����Đ����̎��Ɏ��Ɋ����߂��čĐ�����z��ԍ���Ԃ�.		

	float m_fSEVolume;		// SE����.
};

#endif // #ifndef XAUDIO2_PLAYSE_H