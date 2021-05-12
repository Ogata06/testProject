#include "GameParamResource.h"


CGameParamResource::CGameParamResource()
	: m_ParamList	()
{
}

CGameParamResource::~CGameParamResource()
{
}

//-------------------------------.
// �C���X�^���X�̎擾.
//-------------------------------.
CGameParamResource* CGameParamResource::GetInstance()
{
	static std::unique_ptr<CGameParamResource> pInstance = std::make_unique<CGameParamResource>();
	return pInstance.get();
}

//-------------------------------.
// �S�p�����[�^�̓ǂݍ���.
//-------------------------------.
void CGameParamResource::ReadAllParam()
{
	GetInstance()->m_ParamList.emplace_back( ReadParam<COutLineRender::OUTLINE_CBUFFER>(EParamNo::OutLine) );
	GetInstance()->m_ParamList.emplace_back( ReadParam<CDownSamplingRender::SDownSamplePrame>(EParamNo::DownSamle) );
}