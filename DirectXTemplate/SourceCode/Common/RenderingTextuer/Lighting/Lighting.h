#ifndef LIGHTING_RENDER_H
#define LIGHTING_RENDER_H

#include "..\RenderingTextuer.h"

/***********************************************
*	���C�e�B���O�`��N���X.
**/
class CLightingRender : public CRenderTexture
{
	// "Lighting_PS.hlsl"�̃��C�g�ő�l�ƒl�����킹�邱�Ƃ��K�v.
	static constexpr int LIGHT_MAX_COUNT = 2;	// ���C�g�̍ő吔.

	// �R���X�^���g�o�b�t�@.
	struct LIGHT_CBUFFER
	{
		D3DXVECTOR4 CameraPos;
		D3DXVECTOR4 LightPos[LIGHT_MAX_COUNT];
		D3DXVECTOR4 LightVec[LIGHT_MAX_COUNT];
		D3DXVECTOR4 LightColor[LIGHT_MAX_COUNT];
		D3DXVECTOR4 LightConeAngle[LIGHT_MAX_COUNT];
		D3DXVECTOR4 LightType[LIGHT_MAX_COUNT];
		LIGHT_CBUFFER()
			: CameraPos			( 0.0f, 0.0f, 0.0f, 0.0f )
			, LightPos			()
			, LightVec			()
			, LightColor		()
			, LightConeAngle	()
			, LightType			()
		{
			for( int i = 0; i < LIGHT_MAX_COUNT; i++ ){
				LightPos[i]			= { 0.0f, 0.0f, 0.0f, 0.0f };
				LightVec[i]			= { 0.0f, 0.0f, 0.0f, 0.0f };
				LightColor[i]		= { 0.0f, 0.0f, 0.0f, 0.0f };
				LightConeAngle[i]	= { 0.0f, 0.0f, 0.0f, 0.0f };
				LightType[i]		= { 0.0f, 0.0f, 0.0f, 0.0f };
			}
		};
	};

public:
	CLightingRender();
	virtual ~CLightingRender();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �`��.
	void Render( const int& srvCount, const std::vector<ID3D11ShaderResourceView*>& srvList );

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override { return 1; }

protected:
	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;

private:
	ID3D11Buffer*	m_pConstantBufferFrame;	// �R���X�^���g�o�b�t�@.
};

#endif	// #ifndef LIGHTING_RENDER_H.