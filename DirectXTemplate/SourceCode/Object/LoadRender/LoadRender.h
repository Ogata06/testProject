/**
* @file LoadRender.h.
* @brief ���[�h���ɕ`�悳����N���X.
* @author ���c���.
*/
#ifndef LOAD_RENDER_H
#define LOAD_RENDER_H

#include "..\Object.h"

/****************************************
*	���[�h�摜�`��N���X.
**/
class CLoadRender : public CObject
{
public:
	CLoadRender();
	virtual ~CLoadRender();

	// �ǂݍ��݃N���X.
	bool Init();

	// �X�V�֐�.
	void Update( const float& deltaTime );
	// �`��N���X.
	void Render();

private:
	// �X�v���C�g�̓ǂݍ���.
	bool LoadSprite();

private:
	std::vector<std::unique_ptr<CSprite>>	m_pSprites;			// �摜�N���X.
	float									m_DeltaTime;		// �f���^�^�C��.
	bool									m_IsLoadEnd;		// �ǂݍ��݂��I��������.
};

#endif	// #ifndef LOAD_RENDER_H.