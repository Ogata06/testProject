/**
* @file CollisionManager.h.
* @brief �����蔻��N���X.
* @author ���c���.
*/
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

// �x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

#include <D3DX11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

// ���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx10.lib" )	//�uD3DX�`�v�̒�`�g�p���ɕK�v.

class CSphere;
class CCapsule;
class CBox;
class CRay;

namespace coll
{

	// ���̓��m�̓����蔻��.
	bool IsSphereToSphere( CSphere* pMySphere, CSphere* pOppSphere );

	// �J�v�Z�����m�̓����蔻��.
	bool IsCapsuleToCapsule( CCapsule* pMyCapsule, CCapsule* pOppCapsule );

	// �{�b�N�X���m�̓����蔻��.
	bool IsOBBToOBB( CBox* pMyBox, CBox* pOppBox );

	// ���C�Ƌ��̂̓����蔻��.
	bool IsRayToSphere( CRay* pRay, CSphere* pSphere, D3DXVECTOR3* pOutStartPos, D3DXVECTOR3* pOutEndPos );

};

#endif	// #ifndef COLLISION_MANAGER_H.