//-----------------------------------------------.
// �\����.
//-----------------------------------------------.
// ���_�o�͗p.
struct VS_OUTPUT
{
	float4 Pos			: SV_Position;
	float2 Tex			: TEXCOORD0;
};

//-----------------------------------------------.
// �R���X�^���g�o�b�t�@.
//-----------------------------------------------.
// �ŏ������n���p.
cbuffer PerInit	: register(b0)
{
	matrix g_mW			: packoffset(c0); // ���[���h�s��.
	float2 g_vViewPort	: packoffset(c4); // �E�B���h�E�T�C�Y.
	float2 g_vPixelSize	: packoffset(c5); // �s�N�Z���̃T�C�Y.
	float2 g_vWndRatio	: packoffset(c6); // �E�B���h�E�̉����̔䗦.
};