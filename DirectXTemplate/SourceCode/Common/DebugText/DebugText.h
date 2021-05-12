/**
* @file DebugText.h.
* @brief �f�o�b�O�e�L�X�g�`��N���X.
* @author ���c���.
*/
#ifndef DEBUG_TEXT_H
#define DEBUG_TEXT_H

#include <queue>
#include <string>
#include <sstream>

#include "..\Common.h"

class CDebugTextShader;
class CFont;
class CSpriteRender;

/*********************************
*	�f�o�b�O�e�L�X�g�`��N���X.
**/
class CDebugText : public CCommon
{
private:
	static constexpr size_t	MAX_TEXT_LENGH	= 70;	// �ő啶����.

public:
	CDebugText();	// �R���X�g���N�^
	virtual ~CDebugText();	// �f�X�g���N�^.

	// �C���X�^���X�̎擾.
	static CDebugText* GetInstance();

	// �������֐�.
	static HRESULT Init( ID3D11DeviceContext* pContext11 );

	// �`��֐�(�ψ���).
	template<class... T1>
	static void PushText( const T1&... t1 )
	{
		if( GetInstance()->m_IsRender			== false ) return;
		std::string Text = GetInstance()->initstring(t1...);
		if( Text.length() >= GetInstance()->MAX_TEXT_LENGH ) return;
		GetInstance()->m_TextQueue.push( Text );
	}
	// �`��֐�.
	static void Render();

private:
	// �X�V�֐�.
	void Update();
	// �e�N�X�`���̓ǂݍ���.
	void TextureLoad();

	template <class T>
	std::string to_std_string(const T& x)
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
	template<class T1, class... T2>
	std::string initstring( const T1& t1, const T2&... t2 )
	{
		std::string s = to_std_string(t1);
		return s + initstring(t2...);
	}
	template<class T1>
	std::string initstring( const T1& t1 )
	{
		std::string s = to_std_string(t1);
		return s;
	}

private:
	std::queue<std::string>			m_TextQueue;		// �e�L�X�g�L���[.
	std::unique_ptr<CFont>			m_pFont;			// �t�H���g.
	std::unique_ptr<CSpriteRender>	m_pSpriteRender;	// �摜�`��N���X.
	CSprite*						m_pBackSprite;		// �w�i�摜.
	D3DXVECTOR2						m_BackTextureSize;	// �w�i�̉摜�T�C�Y.
	int								m_TextIndex;		// �e�L�X�g�C���f�b�N�X.
	bool							m_IsRender;			// �`��ł��邩.
	bool							m_IsMoveing;		// �ړ��ł��邩.

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CDebugText( const CDebugText & )				= delete;
	CDebugText& operator = ( const CDebugText & )	= delete;
	CDebugText( CDebugText && )						= delete;
	CDebugText& operator = ( CDebugText && )		= delete;
};

#endif // #ifndef DEBUG_TEXT_H.