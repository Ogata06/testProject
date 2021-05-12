/**
* @file CollisionRender.h.
* @brief �����蔻��`��p�N���X.
* @author ���c���.
*/
#ifndef COLLISION_RENDER_H
#define COLLISION_RENDER_H

#include <queue>
#include <memory>

class CDX9StaticMesh;
class CSphere;
class CCapsule;
class CBox;
class CRay;
class CRayMesh;

/*************************************
*	�����蔻��̕`��p�N���X.
**/
class CCollisionRender
{
public:
	CCollisionRender();
	~CCollisionRender();

	// �C���X�^���X�̎擾.
	static CCollisionRender* GetInstance();

	// �`��.
	static void Render();

	// ���̂̒ǉ�.
	static void PushSphere( CSphere* pSphere );
	// �J�v�Z���̒ǉ�.
	static void PushCapsule( CCapsule* pCapsule );
	// �{�b�N�X�̒ǉ�.
	static void PushBox( CBox* pBox );
	// ���C�̒ǉ�.
	static void PushRay( CRay* pBox );

private:
	// ���̂̕`��.
	void SphereRender();
	// �J�v�Z���̕`��.
	void CapsuleRender();
	// �{�b�N�X�̕`��.
	void BoxRender();
	// ���C�̕`��.
	void RayRender();

private:
	std::queue<CSphere*>		m_pSphereQueue;	// ���̂̃L���[.
	std::queue<CCapsule*>		m_pCapsuleQueue;// �J�v�Z���̃L���[.
	std::queue<CBox*>			m_pBoxQueue;	// �{�b�N�X�̃L���[.
	std::queue<CRay*>			m_pRayQueue;	// ���C�̃L���[.
	CDX9StaticMesh*				m_pSphere;		// ���̃��b�V��.
	CDX9StaticMesh*				m_pCapsule;		// �J�v�Z�����b�V��.
	CDX9StaticMesh*				m_pBox;			// �{�b�N�X���b�V��.
	std::unique_ptr<CRayMesh>	m_pRay;			// ���C���b�V��.

	bool					m_IsSphreRender;	// ���̂�`�悷�邩.
	bool					m_IsCapsuleRender;	// �J�v�Z����`�悷�邩.
	bool					m_IsBoxRender;		// �{�b�N�X��`�悷�邩.
	bool					m_IsRayRender;		// ���C��`�悷�邩.

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CCollisionRender( const CCollisionRender & )				= delete;
	CCollisionRender& operator = ( const CCollisionRender & )	= delete;
	CCollisionRender( CCollisionRender && )						= delete;
	CCollisionRender& operator = ( CCollisionRender && )		= delete;
};

#endif	// #ifndef COLLISION_RENDER_H.