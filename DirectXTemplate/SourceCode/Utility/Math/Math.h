#ifndef MTAH_H
#define MTAH_H

// �x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

#include <D3DX11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

// ���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3dx10.lib" )	//�uD3DX�`�v�̒�`�g�p���ɕK�v.

namespace Math
{
	const D3DXVECTOR3 X_AXIS{ 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 Y_AXIS{ 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 Z_AXIS{ 0.0f, 0.0f, 1.0f };

	// v�̃x�N�g���ɑ΂��Ē����̃x�N�g����Ԃ�.
	extern D3DXVECTOR3 Orthogonal( const D3DXVECTOR3& v );

	// u�̕�����v�̕����Ɠ����ɂ��邽�߂�D3DXQUATERNION��Ԃ�.
	extern D3DXQUATERNION GetRotationBetween( const D3DXVECTOR3& _u, const D3DXVECTOR3& _v );
};

#endif	// #ifndef MTAH_H.