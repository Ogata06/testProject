#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <string>

#include "..\Global.h"

class CFrameRate;
class CSceneManager;
class CSprite;
class CFont;
class CLoadManager;

/**************************************************
*	���C���N���X.
**/
class CMain
{
public:
	CMain();
	~CMain();
	// �E�B���h�E�������֐�.
	HRESULT InitWindow( HINSTANCE hInstance );

	// ���b�Z�[�W���[�v.
	void Loop();

	// �������֐�.
	HRESULT Init();
	// ����֐�.
	void Release();

private:
	// �X�V����.
	void Update();

	// �ǂݍ��݊֐�.
	HRESULT Load();

	// FPS�̕`��.
	void FPSRender();

private:
	HWND m_hWnd;
	std::unique_ptr<CLoadManager>	m_pLoadManager;		// ���[�h�}�l�[�W���[.
	std::unique_ptr<CFrameRate>		m_pFrameRate;		// �t���[�����[�g.
	std::unique_ptr<CSceneManager>	m_pSceneManager;	// �V�[���}�l�[�W���[.
	std::unique_ptr<CFont>			m_FPSRender;		// FPS�̕`��.

	bool	m_IsFPSRender;	// FPS��`�悷�邩.
};

#endif	// #ifndef MAIN_H.
