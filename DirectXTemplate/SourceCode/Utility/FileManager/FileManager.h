/**
* @file FileManager.h.
* @brief �t�@�C���ǂݍ��݊Ǘ��w�b�_�[.
* @author ���c���.
*/
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace fileManager
{
	//----------------------------------------------.
	// �o�C�i���f�[�^�ł̏�������.
	//----------------------------------------------.
	template<class outDATA>
	bool BinaryWriting( const char* fileName, const outDATA& outData )
	{
		std::fstream fout;
		fout.open( fileName, std::ios::out | std::ios::binary | std::ios::trunc );

		if( !fout ) return false;

		fout.write( reinterpret_cast<const char*>(std::addressof(outData)), sizeof(outDATA) );

		fout.close();  //�t�@�C�������

		return true;
	}

	//----------------------------------------------.
	// �o�C�i���f�[�^�ł̓ǂݍ���.
	//----------------------------------------------.
	template<class inDATA>
	bool BinaryReading( const char* fileName, inDATA& inData, const int& seekPoint = 0 )
	{
		std::fstream fin;
		fin.open( fileName, std::ios::in | std::ios::binary );

		if( !fin ) return false;

		fin.seekg( seekPoint * sizeof(inDATA) );
		fin.read( reinterpret_cast<char*>(std::addressof(inData)), sizeof(inDATA) );

		fin.close();  //�t�@�C�������

		return true;
	}

	//----------------------------------------------.
	// �o�C�i���f�[�^��vector�ŏ�������.
	//----------------------------------------------.
	template<class outDATA>
	bool BinaryVectorWriting( const char* fileName, const std::vector<outDATA>& outDataList )
	{
		std::ofstream fout( fileName, std::ios::out | std::ios::binary);

		if( !fout ) return false;

		int vecSize = outDataList.size();
		fout.write( reinterpret_cast<const char*>(&vecSize), sizeof(vecSize) );
		fout.write( reinterpret_cast<const char*>(&outDataList[0]), vecSize*sizeof(outDATA) );
		fout.close();

		return true;
	}

	//----------------------------------------------.
	// �o�C�i���f�[�^��vector�œǂݍ���.
	//----------------------------------------------.
	template<class inDATA>
	bool BinaryVectorReading( const char* fileName, std::vector<inDATA>& inDataList )
	{
		std::ifstream fin( fileName, std::ios::in | std::ios::binary );

		if ( !fin ) return false;

		inDataList.clear();
		int size = 0;

		fin.read( reinterpret_cast<char*>(&size), sizeof(size) );
		inDataList.resize( size );
		fin.read( reinterpret_cast<char*>(&inDataList[0]), size*sizeof(inDATA) );
		fin.close();

		return true;
	}

	//----------------------------------------------.
	// �t�@�C���̓ǂݍ���.
	//----------------------------------------------.
	std::vector<std::string> TextLoading( const std::string& fileName, const bool& isCommentOut = true, char delimiter = ',' );
};

#endif	// #ifndef FILE_MANAGER_H.