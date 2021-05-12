/**
* @file Command.h.
* @brief ���̓R�}���h���Ǘ�����N���X.
* @author ���c���.
*/
#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <vector>

/****************************************
*	���̓R�}���h�����Ǘ�����N���X.
*		Cpp�t�@�C���̕��ŔC�ӂ̃R�}���h��ݒ�ł���.
**/
class CCommand
{
public:
	// �L�[(button)�̃��X�g.
	enum enKey : unsigned char
	{
		EKey_Up,	// ��.
		EKey_Down,	// ��.
		EKey_Right,	// �E.
		EKey_Left,	// ��.
		EKey_A,		// A.
		EKey_B,		// B.
		EKey_X,		// X.
		EKey_Y,		// Y.
		EKey_RB,	// RB.
		EKey_LB,	// LB.
	} typedef EKey;
	
	using command_list = std::vector<CCommand::EKey>;

public:
	CCommand();
	CCommand( const command_list& );
	~CCommand();

	void Update();

	// ����������.
	inline bool IsSuccess() { return m_isSuccessCommand; }

private:
	// �L�[(button�̓���).
	void InputKey();
	// �L�[�̒ǉ�.
	void PushKey( const EKey& key );
	// �L���[�̊m�F.
	void Check();

private:
	const command_list	COMMAND_LIST;		// �R�}���h�̃��X�g.
	std::queue<EKey>	m_KeyQueue;			// ���͂��ꂽ�L�[�̃L���[.
	int					m_TimeCount;		// ���͂���Ă���̃^�C���J�E���g.
	bool				m_isSuccessCommand;	// �R�}���h������������.
};

#endif	// #ifndef COMMAND_H.