#ifndef TITLE_H
#define TITLE_H

#include "..\..\SceneBase\SceneBase.h"
#include "..\..\..\Common\Effect\EffectManager.h"
#include "..\..\..\Object\Collider\CollisionManager\CollisionManager.h"
#include "..\..\..\Object\CameraBase\RotLookAtCenter\RotLookAtCenter.h"
#include "..\..\..\Common\Mesh\RayMesh\RayMesh.h"

/**********************************
*	�^�C�g���V�[���N���X.
*/
class CTitle : public CSceneBase
{
public:
	CTitle( CSceneManager* pSceneManager );
	virtual ~CTitle();

	// �Ǎ��֐�.
	virtual bool Load() override;
	// �X�V�֐�.
	virtual void Update() override;
	// ���f���`��֐�.
	virtual void ModelRender() override;
	// �摜�`��֐�.
	virtual void SpriteRender() override;

private:
	float m_DeltaTime;
	CDX9SkinMesh*	m_pSkinMesh;
	CDX9StaticMesh*	m_pStaticMesh;
	CSprite*	m_Sprite;
	CEffectManager m_effect1;
	CEffectManager m_effect2;
};

#endif	// #ifndef TITLE_H.