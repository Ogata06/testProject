/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
**/
#ifndef DX9_SKIN_MESH_H
#define DX9_SKIN_MESH_H

#include "Parser/CDX9SkinMeshParser.h"
#include "..\..\Common.h"
#include "..\MeshStruct.h"

struct stAnimationController
{
	LPD3DXANIMATIONCONTROLLER	pAC;
	double						AnimTime;
	bool						IsAnimChangeBlend;

	stAnimationController()
		: pAC				( nullptr )
		, AnimTime			( 0.0 )
		, IsAnimChangeBlend	( false )
	{}

	void BlendAnimUpdate( const double& speed )
	{
		// �A�j���[�V�����؂�ւ��t���O������Ă���I��.
		if( IsAnimChangeBlend == false ) return;
		AnimTime += speed;

		float weight = static_cast<float>(AnimTime) / 1.0f;	// �E�F�C�g�̌v�Z.
		pAC->SetTrackWeight( 0, weight );	// �g���b�N0 �ɃE�F�C�g��ݒ�.
		pAC->SetTrackWeight( 1, 1.0f - weight );// �g���b�N1 �ɃE�F�C�g��ݒ�.

		if( AnimTime < 1.0 ) return;
		// �A�j���[�V�����^�C�������l�ɒB������.
		IsAnimChangeBlend = false;	// �t���O������.
		pAC->SetTrackWeight( 0, 1.0f );		// �E�F�C�g��1�ɌŒ肷��.
		pAC->SetTrackEnable( 1, false );	// �g���b�N1�𖳌��ɂ���.
	}

	HRESULT SetAnimController( LPD3DXANIMATIONCONTROLLER pAc )
	{
		if( FAILED( pAc->CloneAnimationController(
			pAc->GetMaxNumAnimationOutputs(),
			pAc->GetMaxNumAnimationSets(),
			pAc->GetMaxNumTracks(),
			pAc->GetMaxNumEvents(),
			&pAC ))){
			return E_FAIL;
		}
		return S_OK;
	}

} typedef SAnimationController;

//==================================================================================================
//
//	�X�L�����b�V���N���X.
//
//==================================================================================================
class CDX9SkinMesh : public CCommon
{
public:
	//�{�[���P��.
	struct CBUFFER_PER_BONES
	{
		D3DXMATRIX mBone[D3DXPARSER::MAX_BONES];
		CBUFFER_PER_BONES()
		{
			for (int i = 0; i < D3DXPARSER::MAX_BONES; i++)
			{
				D3DXMatrixIdentity(&mBone[i]);
			}
		}
	};


	//���_�\����.
	struct MY_SKINVERTEX
	{
		D3DXVECTOR3	vPos;		//���_�ʒu.
		D3DXVECTOR3	vNorm;		//���_�@��.
		D3DXVECTOR2	vTex;		//UV���W.
		D3DXVECTOR3	Tangent;	// .
		D3DXVECTOR3	Binormal;	// �@��(�A�e�v�Z�ɕK�{).
		UINT bBoneIndex[4];		//�{�[�� �ԍ�.
		float bBoneWeight[4];	//�{�[�� �d��.
		MY_SKINVERTEX()
			: vPos()
			, vNorm()
			, vTex()
			, bBoneIndex()
			, bBoneWeight()
		{}
	};

	//�p�[�T�[�N���X����A�j���[�V�����R���g���[���[���擾����.
	LPD3DXANIMATIONCONTROLLER GetAnimController()
	{
		return m_pD3dxMesh->m_pAnimController;
	}

	//���\�b�h.
	CDX9SkinMesh( 
		HWND hWnd, 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9,
		const char* fileName )
		: CDX9SkinMesh()
	{
		Init( hWnd, pDevice11, pContext11, pDevice9, fileName );
	}
	CDX9SkinMesh();
	~CDX9SkinMesh();

	HRESULT Init(
		HWND hWnd, 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		LPDIRECT3DDEVICE9 pDevice9,
		const char* fileName );

	//X�t�@�C������X�L�����b�V�����쐬����.
	HRESULT LoadXMesh( const char* fileName );
	//�`��֐�.
	void Render( SAnimationController* pAC=NULL );
	//����֐�.
	HRESULT Release();

	double GetAnimSpeed()				{ return m_dAnimSpeed;		}
	void SetAnimSpeed( double dSpeed )	{ m_dAnimSpeed = dSpeed;	}

	double GetAnimTime()				{ return m_dAnimTime;		}
	void SetAnimTime( double dTime )	{ m_dAnimTime = dTime;		}

	//�A�j���[�V�����R���g���[�����擾.
	LPD3DXANIMATIONCONTROLLER GetAnimationController() { return m_pD3dxMesh->m_pAnimController; }

	//�A�j���[�V�����Z�b�g�̐؂�ւ�.
	void ChangeAnimSet( int index, SAnimationController* pAC=nullptr );
	//�A�j���[�V�����Z�b�g�̐؂�ւ�(�J�n�t���[���w��\��).
	void ChangeAnimSet_StartPos( int index, double dStartFramePos, SAnimationController* pAC=nullptr );
	// �A�j���[�V�������u�����h���Đ؂�ւ�.
	void ChangeAnimBlend( int index, int oldIndex, SAnimationController* pAC = nullptr );

	// �u�����h�A�j���[�V�����̍X�V.
	void BlendAnimUpdate();

	//�A�j���[�V������~���Ԃ��擾.
	double GetAnimPeriod( int index );
	//�A�j���[�V���������擾.
	int GetAnimMax( LPD3DXANIMATIONCONTROLLER pAC=NULL );

	//�w�肵���{�[�����(���W�E�s��)���擾����֐�.
	bool GetMatrixFromBone(const char* sBoneName, D3DXMATRIX* pOutMat );
	bool GetPosFromBone(const char* sBoneName, D3DXVECTOR3* pOutPos);
	bool SetMatrixFromBone(const char* sBoneName, D3DXMATRIX inMat );
	bool SetPosFromBone(const char* sBoneName, D3DXVECTOR3 inPos );
	bool GetDeviaPosFromBone(const char* sBoneName, D3DXVECTOR3* pOutPos, D3DXVECTOR3 vSpecifiedPos = { 0.0f, 0.0f, 0.0f });

	//ү�����擾.
	LPD3DXMESH GetMesh() const { return m_pMeshForRay; }

private:
	HWND m_hWnd;

	//Dx9.
	LPDIRECT3DDEVICE9		m_pDevice9;

	//Dx11.
	ID3D11SamplerState*		m_pSampleLinear;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11Buffer*			m_pCBufferPerMesh;		//�R���X�^���g�o�b�t�@(���b�V����).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//�R���X�^���g�o�b�t�@(�}�e���A����).
	ID3D11Buffer*			m_pCBufferPerFrame;		//�R���X�^���g�o�b�t�@(�t���[����).
	ID3D11Buffer*			m_pCBufferPerBone;		//�R���X�^���g�o�b�t�@(�{�[����).

	D3DXMATRIX		m_mWorld;
	D3DXMATRIX		m_mRotation;

	D3DXMATRIX		m_mView;
	D3DXMATRIX		m_mProj;

	D3DXVECTOR3		m_CameraPos;
	D3DXVECTOR3		m_CameraLookPos;

	//�A�j���[�V�������x.
	double m_dAnimSpeed;
	double m_dAnimTime;

	bool m_IsChangeAnim;

	//��������p��.
	SKIN_PARTS_MESH* m_pReleaseMaterial;

	//���b�V��.
	D3DXPARSER* m_pD3dxMesh;
	LPD3DXMESH	m_pMeshForRay;	//ڲ��ү���p.

	//XFile�̃p�X.
	CHAR	m_FilePath[256];

	//�A�j���[�V�����t���[��.
	int		m_iFrame;

	HRESULT InitShader();
	HRESULT CreateIndexBuffer( DWORD dwSize, int* pIndex, ID3D11Buffer** ppIndexBuffer );
	void RecursiveSetNewPoseMatrices( BONE* pBone,D3DXMATRIX* pmParent );

	//�S�Ẵ��b�V�����쐬����.
	void BuildAllMesh( D3DXFRAME* pFrame );
	
	//���b�V�����쐬����.
	HRESULT CreateAppMeshFromD3DXMesh( LPD3DXFRAME pFrame );

	//X�t�@�C������X�L���֘A�̏���ǂݏo���֐�.
	HRESULT ReadSkinInfo( MYMESHCONTAINER* pContainer, MY_SKINVERTEX* pvVB, SKIN_PARTS_MESH* pParts );

	//�{�[�������̃|�[�Y�ʒu�ɃZ�b�g����֐�.
	void SetNewPoseMatrices( SKIN_PARTS_MESH* pParts, int frame, MYMESHCONTAINER* pContainer );
	//����(���݂�)�|�[�Y�s���Ԃ��֐�.
	D3DXMATRIX GetCurrentPoseMatrix( SKIN_PARTS_MESH* pParts, int index );

	//�t���[���`��.
	void DrawFrame( LPD3DXFRAME pFrame );
	//�p�[�c�`��.
	void DrawPartsMesh( SKIN_PARTS_MESH* p, D3DXMATRIX World, MYMESHCONTAINER* pContainer );
	void DrawPartsMeshStatic( SKIN_PARTS_MESH* pMesh, D3DXMATRIX World, MYMESHCONTAINER* pContainer );

	//�S�Ẵ��b�V�����폜.
	void DestroyAllMesh( D3DXFRAME* pFrame );
	HRESULT DestroyAppMeshFromD3DXMesh( LPD3DXFRAME p );

	//�R���X�^���g�o�b�t�@�쐬�֐�.
	HRESULT CreateCBuffer(ID3D11Buffer** pConstantBuffer, UINT size);
	//�T���v���[�쐬�֐�.
	HRESULT CreateLinearSampler(ID3D11SamplerState** pSampler);
};

#endif//#ifndef DX9_SKIN_MESH_H.