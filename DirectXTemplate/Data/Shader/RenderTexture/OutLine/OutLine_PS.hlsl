#include "..\RenderTexture.hlsli"
/*
*	���Q�l�T�C�g.
*	https://qiita.com/kanurapoison/items/1b36fdaa0a33f0d278d5
*/

#define GBUFFER_BACK		(0)	// �F�e�N�X�`��.
#define GBUFFER_COLOR		(1)	// �F�e�N�X�`��.
#define GBUFFER_NORMAL		(2)	// �@���e�N�X�`��
#define GBUFFER_WORLD_POS	(3)	// ���[���h���W�e�N�X�`��.
#define GBUFFER_Z_DEPTH		(4)	// �[�x�l�e�N�X�`��.
#define GBUFFER_DIFFUSE		(5)	// �f�B�t�[�Y�e�N�X�`��.
#define GBUFFER_MAX			(6)	// �e�N�X�`���z��̍ő�l.

//-----------------------------------------------.
// �e�N�X�`��.
//-----------------------------------------------.
Texture2D g_GBufferColor[GBUFFER_MAX] : register(t0); // �F���.

//-----------------------------------------------.
// �T���v��.
//-----------------------------------------------.
SamplerState g_SamLinear : register(s0);

//-----------------------------------------------.
// �R���X�^���g�o�b�t�@.
//-----------------------------------------------.
// �s�N�Z���V�F�[�_�[�o��.
struct PS_OUTPUT
{
	float4 Default	: SV_Target0;
	float4 LineOnly	: SV_Target1;
};

// �T���v��.
struct OUTLINE_SAMPLE
{
	float NormalPower;		// �@���̃T���v���̋���.
	float NormalCompare;	// �@���̔�r�l.
	float DepthPower;		// �[�x�l�̃T���v���̋���.
	float DepthCompare;		// �[�x�l�̔�r�l.
};

//-----------------------------------------------.
// �R���X�^���g�o�b�t�@.
//-----------------------------------------------.
cbuffer per_frame : register(b1)
{
	float4			Color;	// �A�E�g���C���̐F.
	OUTLINE_SAMPLE	Sample;	// �T���v��.
};


PS_OUTPUT PS_Main(VS_OUTPUT input)
{
	float4 modelColor		= g_GBufferColor[GBUFFER_COLOR].Sample(g_SamLinear, input.Tex);
	float4 worldPosColor	= g_GBufferColor[GBUFFER_WORLD_POS].Sample(g_SamLinear, input.Tex);
	float4 diffuseColor		= g_GBufferColor[GBUFFER_DIFFUSE].Sample(g_SamLinear, input.Tex);
	
	//----------------------------------------------------------------.
	// �֊s��.
	//----------------------------------------------------------------.
	float s = Sample.NormalPower; // �T���v�����O���鋭��.
	float px = s * g_vPixelSize.x, py = s * g_vPixelSize.y;
	
	
	float3 normColor = float3( 0.0f, 0.0f, 0.0f );
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(	 -px,	 -py), 0.0f, 1.0 )).xyz; // ����.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2( 0 * px,	 -py), 0.0f, 1.0 )).xyz; // ��.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(	  px,	 -py), 0.0f, 1.0 )).xyz; // �E��.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(	 -px, 0 * py), 0.0f, 1.0 )).xyz; // ��.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2( 0 * px, 0 * py), 0.0f, 1.0 )).xyz * -8.0; // ����.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(	  px, 0 * py), 0.0f, 1.0 )).xyz; // �E.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(	 -px,	  py), 0.0f, 1.0 )).xyz; // ����.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2( 0 * px,	  py), 0.0f, 1.0 )).xyz; // ��.
	normColor += g_GBufferColor[GBUFFER_NORMAL].Sample(g_SamLinear, input.Tex + clamp(float2(     px,	  py), 0.0f, 1.0 )).xyz; // �E��.
	
	s = Sample.DepthPower; // �T���v�����O���鋭��.
	px = s * g_vPixelSize.x, py = s * g_vPixelSize.y;
	float zDepth			= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex).x;
	float depthColor11		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		 px,	  py), 0.0f, 1.0f)).x; // ����.
	float depthColor10		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		 px, 0 *  py), 0.0f, 1.0f)).x; // ��.
	float depthColor1_1		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		 px,	 -py), 0.0f, 1.0f)).x; // �E��.
	float depthColor01		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2( 0 *  px,	  py), 0.0f, 1.0f)).x; // ��.
	float depthColor0_1		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2( 0 *  px,	 -py), 0.0f, 1.0f)).x; // �E.
	float depthColor_11		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		-px,	  py), 0.0f, 1.0f)).x; // ����.
	float depthColor_10		= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		-px, 0 *  py), 0.0f, 1.0f)).x; // ��.
	float depthColor_1_1	= g_GBufferColor[GBUFFER_Z_DEPTH].Sample(g_SamLinear, input.Tex + clamp(float2(		-px,	 -py), 0.0f, 1.0f)).x; // �E��.
	
	// Horizontal.
	float h = (depthColor11	 *  1.0f + depthColor10	  *  2.0f)
			+ (depthColor1_1 *  1.0f + depthColor_11  * -1.0f)
			+ (depthColor_10 * -2.0f + depthColor_1_1 * -1.0f);
	// vertical.
	float v = (depthColor11	 *  1.0f + depthColor01	  *  2.0f)
			+ (depthColor_11 *  1.0f + depthColor1_1  * -1.0f)
			+ (depthColor0_1 * -2.0f + depthColor_1_1 * -1.0f);
	float depth = 1.0f - clamp(abs(h + v), 0.0f, 1.0f);
	
	PS_OUTPUT output = (PS_OUTPUT)0;
	
	// �@�����ƁA�[�x�l�̏�񂪈��ȏ�Ȃ�֊s����\��.
	if( length(normColor) >= Sample.NormalCompare || abs(depth) < Sample.DepthCompare )
	{
		output.Default = float4(Color.rgb, 1.0f);
		output.LineOnly = float4( 0.0f, 0.0f, 0.0f, 1.0f );
	}
	else
	{
		output.Default	= modelColor;
		output.LineOnly = float4( 1.0f, 1.0f, 1.0f, 1.0f );;
	}
	
	return output;
}