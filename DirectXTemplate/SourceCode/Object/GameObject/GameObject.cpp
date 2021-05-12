#include "GameObject.h"
#include "..\CameraBase\CameraManager\CameraManager.h"

CGameObject::CGameObject()
	: m_DeltaTime	( FOR_INIT_ZERO_FLOAT )
	, m_ObjectTag	( EObjectTag::None )
{
}

CGameObject::~CGameObject()
{
}

//--------------------------------.
// ��ʂ̊O�ɏo�Ă��邩.
//--------------------------------.
bool CGameObject::IsDisplayOut( const float& adjSize )
{
	const float wnd_w = static_cast<float>(CDirectX11::GetWndWidth());
	const float wnd_h = static_cast<float>(CDirectX11::GetWndHeight());
	// �r���[�|�[�g�s��.
	D3DXMATRIX mViewport;
	D3DXMatrixIdentity( &mViewport );	// �P�ʍs��쐬.
	mViewport._11 = wnd_w *  0.5f;
	mViewport._22 = wnd_h * -0.5f;
	mViewport._41 = wnd_w *  0.5f;
	mViewport._42 = wnd_h *  0.5f;

	// ���[���h, �r���[, �v���W�F, �r���[�|�[�g�̌v�Z.
	D3DXMATRIX m = CCameraManager::GetViewMatrix() * CCameraManager::GetProjMatrix() * mViewport;
	D3DXVECTOR3 screenPos = { 0.0f, 0.0f, 0.0f };	// �X�N���[�����W.
	// D3DXVECTOR3�Ɗ|�����킹.
	D3DXVec3TransformCoord( &screenPos, &m_Tranceform.Position, &m );

	if( -adjSize < screenPos.x && screenPos.x < wnd_w + adjSize &&
		-adjSize < screenPos.y && screenPos.y < wnd_h + adjSize ) return false;	// ��ʓ�.
	
	return true;	// ��ʊO.
}