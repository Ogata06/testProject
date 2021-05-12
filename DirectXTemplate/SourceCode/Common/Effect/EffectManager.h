/**
* @file EffectManager.h.
* @brief Effekseer�`��Ǘ��N���X.
* @author ���c���.
*/
#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "Effect.h"

/************************************:
*	�G�t�F�N�g�`��Ǘ��N���X.
**/
class CEffectManager
{
public:
	CEffectManager();
	~CEffectManager();

	// �G�t�F�N�g�̐ݒ�.
	bool SetEffect( const char* effectName );

	// �`��.
	void Render();

	// �Đ�.
	void Play( const D3DXVECTOR3& vPos );
	// ��~.
	void Stop();
	// �S�Ē�~.
	void StopAll();
	// �ꎞ��~�������͍ĊJ����.
	void Pause( const bool& bFlag );
	// ���ׂĂ��ꎞ��~�������͍ĊJ����.
	void AllPause( const bool& bFlag );
	// �ʒu���w�肷��.
	void SetLocation( const D3DXVECTOR3& vPos );
	// �T�C�Y���w�肷��.
	void SetScale( const D3DXVECTOR3& vScale );
	void SetScale( const float& scale );
	// ��]���w�肷��.
	void SetRotation( const D3DXVECTOR3& vRot );
	// �Đ����x��ݒ肷��.
	void SetSpeed( const float& fSpeed );
	// �`�悵�Ă��邩.
	bool IsShow();
	// �G�t�F�N�g�Ɏg�p����Ă���C���X�^���X�����擾.
	int GetTotalInstanceCount();

private:
	CEffect*		m_pEffect;	// �G�t�F�N�g�N���X.
	CEffect::Handle	m_Handle;	// �G�t�F�N�g�n���h��.
};

#endif	// #ifndef EFFECT_MANAGER_H.