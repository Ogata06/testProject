/**
* @file Font.h.
* @brief �t�H���g�`��N���X.
* @author ���c���.
*/
#ifndef FONT_H
#define FONT_H

#include "..\Common.h"

class CSpriteRender;

/********************************************
*	�t�H���g�`��N���X.
**/
class CFont : public CCommon
{
public:
	const float FONT_SIZE = 25.0f;	// �t�H���g�̑傫��.
	const D3DXVECTOR2 TEXTUR_UV_POS = { 1.0f, 1.0f };	// �e�N�X�`��UV���W.

public:
	CFont();
	virtual ~CFont();

	// ������.
	HRESULT Init( ID3D11DeviceContext* pContext11 );
	// ���.
	void Release();

	// UI�ŕ`��.
	void RenderUI( const std::string& text );
	// 3D�ŕ`��.
	void Render3D( const std::string& text, const bool& isBillboard = false );

private:
	// �e�N�X�`���̕`��.
	void RenderFontUI( const char* c );
	// �e�N�X�`���̕`��.
	void RenderFont3D( const char* c, const bool& isBillboard  );
	// �o�[�e�b�N�X�o�b�t�@�̍쐬.
	HRESULT CreateVerTexBuffer();

private:
	std::unique_ptr<CSpriteRender>	m_pSpriteRender;	// �摜�`��.
	ID3D11Buffer*					m_pVertexBuffer3D;	// �o�[�e�b�N�X�o�b�t�@.
	ID3D11Buffer*					m_pVertexBufferUI;	// ���_�o�b�t�@.
};

#endif	// #ifndef FONT_H.