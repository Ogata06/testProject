#ifndef XAUDIO2_PLAYBGM_H
#define XAUDIO2_PLAYBGM_H


#include <vector>
#include <mutex>
#include "..\XAudio2.h"
#include "..\XAudio2Master\XAudio2MasterVoice.h"
#include "..\OggLoad\OggLoad.h"
#include "..\XAudio2CallBack\VoiceCallBack.h"

struct IXAudio2SourceVoice;

/**
 * @file XAudio2PlayBGM.h
 * @brief XAudio2�ł�BGM�X�g���[�~���O�Đ���ړI�Ƃ����N���X.
 * @author OTakotiri.
 */

class CXAudio2PlayBGM
{
public: //---------------- �֐� -----------------
	CXAudio2PlayBGM();
	~CXAudio2PlayBGM();
	// �Đ����Ă邩�ǂ����擾�֐�.
	const bool IsPlaying();
	// �T�E���h�Đ��A�O�Ɉꎞ��~����Ă����ꍇ�͋L���ʒu����ĊJ.
	bool Play(std::shared_ptr< COggLoad> pWavData, const char* filename, bool& isEnd);
	// BGM�T�E���h�����S��~.(�ʒu��ێ����Ȃ�).
	bool Stop();
	// �T�E���h�ꎞ��~.
	bool Pause();
	// �T�E���h�Đ����ĊJ.
	bool PlayStart();
	// �s�b�`�ݒ�֐�.
	bool SetPitch(float value);
	// �s�b�`���擾�֐�.
	const float GetPitch();
	// �ő�s�b�`��ݒ肵�܂�.
	void  SetMaxPitch(float value);
	// �s�b�`��ݒ�.
	void SetPitchValue(const float value) { m_fPitch = value; }
	// Ogg����\�[�X�{�C�X���쐬����.
	HRESULT CreateOggSound(std::shared_ptr<COggLoad> pOggData, const char* filename);
	//=======================================================================
	// ��{���ʑ���n.
	//====
	// BGM�̉��ʂ��擾���܂�.
	const float GetVolume();
	// BGM�̉��ʂ�ݒ肵�܂�.
	bool SetBGMVolume(float value);
	// ���݂̉��ʂ�����Z�܂��͌��Z.
	bool  AdjustVolume(float value);
	// SoundSource��j�󂷂�֐�.
	void DestoroySource();
	// �t�F�[�h�A�E�g�t���O�̃Z�b�^�[.
	void SetFadeOutFlag(bool BGMFadeOutFlag) { m_bFadeOutStart = BGMFadeOutFlag; }
	// �t�F�[�h�A�E�g�t���O�̃Q�b�^�[.
	bool GetFadeOutFlag() { return m_bFadeOutStart; }
	// �t�F�[�h�C���t���O�̃Z�b�^�[.
	void SetFadeInFlag(bool BGMFadeInFlag) { m_bFadeInStart = BGMFadeInFlag; }
	// �t�F�[�h�C���t���O�̃Q�b�^�[.
	bool GetFadeInFlag() { return m_bFadeInStart; }
protected:
	// BGM���t�F�[�h�A�E�g����֐�.
	bool FadeOutBGM(float value, const bool& isGameEnd);
	// BGM���t�F�[�h�C������֐�.
	bool FadeInBGM(float value, const bool& isGameEnd);
	// �����f�[�^���X�g���[���ɗ�������.
	HRESULT OggSubmit(std::shared_ptr<COggLoad> pOggData, const char* filename);
private:
	// �t�F�[�h�A�E�g�p�̃X���b�h���N������.
	void CallFadeOutBGM(bool& isEnd);
	// �t�F�[�h�C���p�̃X���b�h���N������.
	void CallFadeInBGM(bool& isEnd);
protected: //--------------- �ϐ� ---------------.
	std::mutex			m_mtx;
	COggLoad*			m_pOggData;		// Ogg�f�[�^���[�h�N���X.
	VoiceCallback		m_Callback;		// �R�[���o�b�N.
	XAUDIO2_BUFFER		m_Buffer;		// �I�[�f�B�I�o�b�t�@�[
	int					m_Buff_len;		// �o�b�t�@�����W.
	BYTE**				m_Buff;			// �o�b�t�@�T�C�Y.
	int					m_Len;			// �����W.
	int					m_Buff_cnt;		// �o�b�t�@�J�E���g.
	int					m_Size;
	IXAudio2SourceVoice*   m_pSourceVoice; //  �T�E���h���Đ�����X�g���[��.
	std::thread	m_FadeInThread;			// �{�����[���t�F�[�h�C���p�X���b�h.
	std::thread	m_FadeOutThread;		// �{�����[���t�F�[�h�A�E�g�p�X���b�h.
	bool	m_isMoveFadeInThread;		// �t�F�[�h�C���X���b�h�������Ă��邩.
	bool	m_isMoveFadeOutThread;		// �t�F�[�h�A�E�g�X���b�h�������Ă��邩.
	float	m_fMaxPitch;				// �ő�s�b�`.
	float	m_fPitch;					// �s�b�`.
	bool	m_bFadeOutStart;			// �t�F�[�h�A�E�g�J�n�t���O.
	bool	m_bFadeInStart;				// �t�F�[�h�C���J�n�t���O.
	float	m_fFadeInValue;				// �t�F�[�h�C���̒l.
	float	m_fFadeOutValue;			// �t�F�[�h�A�E�g�̒l.
	bool	m_bFirstPlay;				// ����Đ����ǂ���.
};

#endif // !C_XAUDIO2_PLAYSOUND_H