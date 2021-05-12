#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "..\CameraBase.h"

class CFreeCamera;	// �t���[�J����.

/**************************************
*	�J�����Ǘ��N���X.
**/
class CCameraManager
{
public:
	CCameraManager();
	~CCameraManager();

	// �C���X�^���X�̎擾.
	static CCameraManager* GetInstance();

	// �X�V�֐�.
	static void Update( const float& deltaTime );

	// �J������ύX.
	static void ChangeCamera( CCameraBase* pCamera, const bool& isMove = 0, const float& sec = 1.0f );

	// ���W�̎擾.
	static D3DXVECTOR3 GetPosition(){ return GetInstance()->m_pCamera->GetPosition(); }
	// ���_���W�̎擾.
	static D3DXVECTOR3 GetLookPosition(){ return GetInstance()->m_pCamera->GetLookPosition(); }
	// �r���[�s��擾�֐�.
	static D3DXMATRIX GetViewMatrix(){ return GetInstance()->m_pCamera->GetViewMatrix(); }
	// �v���W�F�N�V�����s��擾�֐�.
	static D3DXMATRIX GetProjMatrix(){ return GetInstance()->m_pCamera->GetProjMatrix(); }
	// �r���[�E�v���W�F�N�V�����̍����s��擾�֐�.
	static D3DXMATRIX GetViewProjMatrix(){ return GetInstance()->m_pCamera->GetViewProjMatrix(); }

	// �t���[�J������L����.
	static void SetActiveFreeCamera();
	// �t���[�J�����𖳌���.
	static void SetPassiveFreeCamera();

	// �J������null����������.
	static void SetNullCamera();

private:
	// �؂�ւ��ړ��̍X�V.
	void ChangeMoveUpdate( const float& deltaTime );

private:
	CCameraBase*					m_pCamera;
	CCameraBase*					m_pTmpCamera;
	std::unique_ptr<CFreeCamera>	m_pFreeCamera;
	CCameraBase::SCameraState		m_NewState;
	CCameraBase::SCameraState		m_OldState;
	float							m_MoveSeconds;
	float							m_MoveSecondsSpeed;
	bool							m_IsMoveCamera;
	bool							m_IsActiveFreeCamera;

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CCameraManager( const CCameraManager & )				= delete;
	CCameraManager& operator = ( const CCameraManager & )	= delete;
	CCameraManager( CCameraManager && )						= delete;
	CCameraManager& operator = ( CCameraManager && )		= delete;
};

#endif	// #ifndef CAMERA_MANAGER_H.