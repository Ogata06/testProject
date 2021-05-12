/**
* @file Fade.h.
* @brief �V�[�����؂�ւ��^�C�~���O�Ńt�F�[�h��`�悳����N���X.
* @author ���c���.
*/
#ifndef FADE_H
#define FADE_H

#include "..\Object.h"
#include "..\..\Common\Sprite\SpriteStruct.h"

/**********************************
*	�t�F�[�h�N���X.
**/
class CFade : public CObject
{
	enum class enFadeState
	{
		None,

		In,		// �t�F�[�h�C��.
		Out,	// �t�F�[�h�A�E�g.
		End,	// �t�F�[�h�I��.
	} typedef EFadeState;
public:
	CFade();
	virtual ~CFade();

	// �C���X�^���X�̐���.
	static CFade* GetInstance();

	// ������.
	static bool Init();

	// �X�V.
	static void Update( const float& deltaTime );
	// �`��.
	static void Render();

	// ���݂̏�Ԃ��擾.
	static EFadeState GetNowState(){ return GetInstance()->m_NowState; }

	// �t�F�[�h�C���ݒ�֐�.
	static bool IsFadeIn(){ return GetInstance()->m_NowState == EFadeState::In; }
	// �t�F�[�h�A�E�g�ݒ�֐�.
	static bool IsFadeOut(){ return GetInstance()->m_NowState == EFadeState::Out; }
	// �t�F�[�h�A�E�g�ݒ�֐�.
	static bool IsFadeEnd(){ return GetInstance()->m_NowState == EFadeState::End; }

	// �t�F�[�h�C���ݒ�֐�.
	static void SetFadeIn( const bool& isNextFade = false );
	// �t�F�[�h�A�E�g�ݒ�֐�.
	static void SetFadeOut( const bool& isNextFade = false );

	// �����ĕ`�悷��.
	static void KeepRender( const bool& isKeep = true );

private:
	// �摜�̓ǂݍ���.
	bool LoadSprite();

private:
	std::unique_ptr<CSprite>	m_MainSprite;		// ���C���̉摜.
	std::unique_ptr<CSprite>	m_MaskSprite;		// �}�X�N�摜.
	SSpriteRenderState			m_MainSpriteState;	// ���C���摜�̏��.
	EFadeState					m_NowState;			// ���݂̏��.
	bool						m_IsNextFade;		// �����ăt�F�[�h�������邩.
	bool						m_IsKeepRender;		// �����ĕ`�悷�邩.

private:
	//�R�s�[�E���[�u�R���X�g���N�^�A������Z�q�̍폜.
	CFade(const CFade &)				= delete;
	CFade(CFade &&)						= delete;
	CFade& operator = (const CFade &)	= delete;
	CFade& operator =(CFade &&)			= delete;
};

#endif	// #ifndef FADE_H.