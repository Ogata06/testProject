#include "FileManager.h"

namespace fileManager
{
	//----------------------------------------------.
	// �t�@�C���̓ǂݍ���.
	//----------------------------------------------.
	std::vector<std::string> TextLoading( const std::string& fileName, const bool& isCommentOut, char delimiter )
	{
		std::vector<std::string> readList;	// �ǂݍ��݃��X�g.

		// �t�@�C�����J��.
		std::fstream fileStream( fileName );
		// �t�@�C�����J���Ȃ��ꍇ.
		if( !fileStream.is_open() ){
			return readList;
		}

		std::string line;	// 1�s����ǂݍ��ނ��߂̕���.

		// ��s�Âǂݍ���.
		while( std::getline( fileStream, line ) ){
			if( isCommentOut == true ){
				// �擾���������� '//' ������΂�蒼��.
				if( line.find("//") != std::string::npos ) continue;
			}

			std::string buff = "";				// �������ꎞ�I�Ɋi�[����.
			std::istringstream stream( line );
			if( isCommentOut == false ){
				readList.emplace_back( line );
				continue;
			}

			// �f�t�H���g ',' ��؂�ŕ������擾.
			while( std::getline( stream, buff, delimiter ) ){
				if( isCommentOut == true ){
					// �擾���������� '#' ������΂�蒼��.
					if( buff.find('#') != std::string::npos ) continue;
				}

				// �ǂݍ��݃��X�g�ɒǉ�.
				readList.emplace_back( buff );
			}
		}

		fileStream.close();

		return readList;
	}
}
