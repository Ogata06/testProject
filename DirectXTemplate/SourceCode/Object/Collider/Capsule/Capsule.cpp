#include "Capsule.h"

CCapsule::CCapsule()
	: m_Radius	( 1.0f )
	, m_Height	( 2.0f )
{
}

CCapsule::~CCapsule()
{
}

SSegment CCapsule::GetSegment()
{
	D3DXMATRIX mRot;
	D3DXMatrixRotationYawPitchRoll( &mRot, 
		m_Tranceform.Rotation.y,
		m_Tranceform.Rotation.x,
		m_Tranceform.Rotation.z );

	// ���x�N�g����p��.
	D3DXVECTOR3 vAxis = { 0.0, m_Height*0.5f, 0.0f };
	D3DXVECTOR3 vecAxisY;

	// Y�x�N�g�����̂��̂����݂̉�]���ɂ��ϊ�����.
	D3DXVec3TransformCoord( &vecAxisY, &vAxis, &mRot );

	D3DXVECTOR3 startPos	= m_Tranceform.Position - vecAxisY;	// �n�_.
	D3DXVECTOR3 endPos		= m_Tranceform.Position + vecAxisY;	// �I�_.
	D3DXVECTOR3 vec			= endPos - startPos;	// �x�N�g��.
					
	return SSegment( startPos, vec );
}