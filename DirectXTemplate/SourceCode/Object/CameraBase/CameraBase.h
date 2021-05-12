/**
* @file CameraBase.h.
* @brief �J�������N���X.
* @author ���c���.
*/
#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include "..\Object.h"

/****************************************
*	�J�����x�[�X�N���X.
**/
class CCameraBase : public CObject
{
public:
	// �J�������.
	struct stCameraState
	{
		D3DXVECTOR3 Position;		// ���W.
		D3DXVECTOR3 LookPosition;	// ���_���W.
	} typedef SCameraState;

public:
	CCameraBase();
	virtual ~CCameraBase();

	// �X�V�֐�.
	virtual void Update( const float& deltaTime ) = 0;

	// �w��b�ŁA�w����W�Ɉړ�����J��������.
	void AnySecondsMove( const SCameraState& newState, const SCameraState& oldState, const float& sec );
	// �w��b�ŁA�w����W�Ɉړ�����J��������.
	void AnySecondsMovePosition( const D3DXVECTOR3& newPos, const D3DXVECTOR3& oldPos, const float& sec );
	// �w��b�ŁA�w����W�Ɉړ�����J��������.
	void AnySecondsMoveLookPosition( const D3DXVECTOR3& newPos, const D3DXVECTOR3& oldPos, const float& sec );

	// �r���[�E�v���W�F�N�V�����̍X�V.
	void UpdateViewProj();

	// �������W�̐ݒ�.
	inline void SetLookPosition( const D3DXVECTOR3& p ) { m_LookPosition = p; }
	// �������W�̎擾.
	inline D3DXVECTOR3 GetLookPosition() const { return m_LookPosition; }

	// �r���[�s��擾�֐�.
	inline D3DXMATRIX GetViewMatrix() const { return m_ViewMatrix; }
	// �v���W�F�N�V�����s��擾�֐�.
	inline D3DXMATRIX GetProjMatrix() const { return m_ProjMatrix; }
	// �r���[�E�v���W�F�N�V�����̍����s��擾�֐�.
	inline D3DXMATRIX GetViewProjMatrix() const { return m_ViewMatrix * m_ProjMatrix; }

	// �����Ԃ�.
	inline bool IsActive() const { return m_IsActive; }

protected:
	D3DXMATRIX	m_ViewMatrix;			// �r���[�s��.
	D3DXMATRIX	m_ProjMatrix;			// �v���W�F�N�V�����s��.
	D3DXVECTOR3	m_LookPosition;			// �J�����������W.
	D3DXVECTOR3	m_ViewVector;			// �r���[�x�N�g��.
	float		m_ViewAngle;			// ����p.
	float		m_Aspect;				// �A�X�y�N�g��.
	float		m_MaxClippingDistance;	// �ő�N���b�s���O����.
	float		m_MinClippingDistance;	// �ŏ��N���b�s���O����.
	bool		m_IsActive;				// ���삵�Ă��邩.
};

#endif	// #ifndef CAMERA_BASE_H.