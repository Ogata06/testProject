/**
* @file GameParamResource.h.
* @brief �Q�[���p�����[�^�[�Ǘ��\�[�X�N���X.
* @author ���c���.
*/
#ifndef GAME_PARAM_RESOURCE_H
#define GAME_PARAM_RESOURCE_H

#include "..\..\Common\RenderingTextuer\OutLine\OutLine.h"
#include "..\..\Common\RenderingTextuer\DownSampling\DownSampling.h"
#include "..\..\Utility\FileManager\FileManager.h"

#include <variant>
#include <vector>
#include <unordered_map>
#include <string>

enum class enParamNo : unsigned int
{
	None,
	OutLine	= 0,
	DownSamle,

	Max,
} typedef EParamNo;

class CGameParamResource
{
	using paramTypeList = 
		std::variant<
			COutLineRender::OUTLINE_CBUFFER,
			CDownSamplingRender::SDownSamplePrame>;

	const std::unordered_map<EParamNo, std::string> PARAM_FILE_PATH_LIST
	{
		{ EParamNo::OutLine, "Data\\Parameter\\Outline.bin" },
		{ EParamNo::DownSamle, "Data\\Parameter\\DownSamle.bin" },
	};
public:
	CGameParamResource();
	~CGameParamResource();

	// �C���X�^���X�̎擾.
	static CGameParamResource* GetInstance();

	// �S�p�����[�^�̓ǂݍ���.
	static void ReadAllParam();

	// �p�����[�^�̎擾.
	template<class T>
	static T GetParam()
	{
		T tmp;
		for( auto& l : GetInstance()->m_ParamList ){
			if( std::holds_alternative<T>(l) == false ) continue;
			tmp = std::get<T>(l); break;
		}
		return tmp;
	}

	// �p�����[�^�̓ǂݍ���.
	template<class T>
	static T ReadParam( const EParamNo& no )
	{
		T tmp;
		fileManager::BinaryReading( GetInstance()->PARAM_FILE_PATH_LIST.at(no).c_str(), tmp );
		return tmp;
	}
	
	// �p�����[�^�̏�������.
	template<class T>
	static bool WritingParam( const EParamNo& no, const T& param, const bool& isListSave = false )
	{
		if( isListSave == true ){
			for( auto& l : GetInstance()->m_ParamList ){
				if( std::holds_alternative<T>(l) == false ) continue;
				l = param; break;
			}
		}
		return fileManager::BinaryWriting( GetInstance()->PARAM_FILE_PATH_LIST.at(no).c_str(), param );
	}

private:
	std::vector<paramTypeList> m_ParamList;

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CGameParamResource( const CGameParamResource & )				= delete;
	CGameParamResource& operator = ( const CGameParamResource & )	= delete;
	CGameParamResource( CGameParamResource && )					= delete;
	CGameParamResource& operator = ( CGameParamResource && )		= delete;
};

#endif	// #ifndef GAME_PARAM_RESOURCE_H.