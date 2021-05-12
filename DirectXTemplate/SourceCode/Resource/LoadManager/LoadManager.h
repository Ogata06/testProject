/**
* @file LoadManager.h.
* @brief �e���\�[�X�ǂݍ��݃N���X.
* @author ���c���.
*/
#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include "..\..\Global.h"
#include <thread>
#include <mutex>

#include <memory>
#include <vector>

/*********************************
*	�e���\�[�X�ނ̓ǂݍ��݂��܂Ƃ߂�N���X.
*		Load�摜�Ȃǂ̕\���������ɓ���Ă���������.
*/
class CLoadManager
{
public:
	CLoadManager();
	~CLoadManager();

	// �ǂݍ���.
	void LoadResource( 
		HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9  );
	// �X���b�h�̉��.
	bool ThreadRelease();

	// ���[�h���s.
	inline bool IsLoadFailed() const { return m_isLoadFailed; }
	// ���[�h���I��������.
	inline bool	IsLoadEnd() const { return m_isThreadJoined; }

private:
	std::thread m_Thread;		// �X���b�h.
	std::mutex	m_Mutex;
	bool m_isLoadEnd;			// ���[�h���I��������.
	bool m_isThreadJoined;		// �X���b�h��������ꂽ��.
	bool m_isLoadFailed;		// ���[�h���s.
};

#endif	// #ifndef LOAD_MANAGER_H.