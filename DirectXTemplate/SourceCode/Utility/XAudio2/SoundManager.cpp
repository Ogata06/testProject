#include "SoundManager.h"
#include <crtdbg.h>
#include <filesystem>	// C++17 �K�{.

namespace fs = std::filesystem;
//=============================
// �萔�錾.
//=============================
namespace {
	constexpr char FILE_PATH[128] = "Data\\Sound";					// Sound�f�[�^�������Ă���f�B���N�g���p�X.
	constexpr char BINARY_FILE_PATH[128] = "Data\\Sound\\Data.bin";	// �o�C�i���f�[�^�������Ă�p�X.
	constexpr CSoundManager::SoundVolume INIT_VOLUME = { 0.5f,0.5f,0.5f };	// �o�C�i���f�[�^�����݂��Ȃ��ۂɐݒ肷�鏉������.
}

CSoundManager::CSoundManager()
	: m_bEndGame					( false )
	, m_bEndCreate					( false )
	, m_bMoveSoundVolumeThread		( true )
	, m_isCreateThread				( false )
	, m_bResumeSoundVolumeThread	( true )
{
	//---------------------------
	// Map�R���e�i�̃N���A.
	pBgmSource.clear();
	pBGMThread.clear();
	m_bisEndThread.clear();
	m_bisThreadRelease.clear();
	InThreadID.clear();
	m_vsBGMNameList.clear();
	m_vsSENameList.clear();
	pSeSource.clear();
}

CSoundManager::~CSoundManager()
{
}
//=============================
// �C���X�^���X�̍쐬.
//=============================
CSoundManager* CSoundManager::GetInstance()
{
	static std::unique_ptr<CSoundManager> pInstance =
		std::make_unique<CSoundManager>();	// �C���X�^���X�̍쐬.
	return pInstance.get();
}
//=============================
// �T�E���h�f�[�^�쐬.
//=============================
void CSoundManager::CreateSoundData()
{
	std::mutex	m_Mutex;
	m_Mutex.lock();
	if (GetInstance()->m_bEndCreate == true) return;
	auto eachLoad = [&](const fs::directory_entry& entry)
	{
		const std::string extension = entry.path().extension().string();	// �g���q.
		const std::string filePath = entry.path().string();					// �t�@�C���p�X.
		const std::string fileName = entry.path().stem().string();			// �t�@�C����.
		// �g���q��Ogg�łȂ���ΏI��.
		if (extension != ".ogg" && extension != ".OGG") return;

		//�t�@�C���p�X����BGM���Ȃ����SE�̍쐬������.
		if (filePath.find("BGM") == std::string::npos) {
			// WavLoad�N���X�쐬.
			GetInstance()->m_pOggWavData[fileName] = std::make_shared<COggLoad>();
			// Wav�t�H�[�}�b�g�擾.
			GetInstance()->m_pOggWavData[fileName]->CreateOggData(fileName.c_str(), true);
			// PlaySound�N���X�쐬.
			GetInstance()->pSeSource[fileName] = std::make_shared<CXAudio2PlaySE>();
			// SE��SoundSource�쐬.
			GetInstance()->pSeSource[fileName]->CreateOggSound(GetInstance()->m_pOggWavData[fileName], GetInstance()->m_pOggWavData[fileName]->GetFileName());
			// �t�H���_�̖��O��SE���O���X�g�ɓ����.
			GetInstance()->m_vsSENameList.emplace_back(fileName);
		}
		else {
			// WavLoad�N���X�쐬.
			GetInstance()->m_pOggWavData[fileName] = std::make_shared<COggLoad>();
			// Wav�t�H�[�}�b�g�擾.
			GetInstance()->m_pOggWavData[fileName]->CreateOggData(fileName.c_str());
			// PlaySound�N���X�쐬.
			GetInstance()->pBgmSource[fileName] = std::make_shared<CXAudio2PlayBGM>();
			// SE��SoundSource�쐬.
			GetInstance()->pBgmSource[fileName]->CreateOggSound(GetInstance()->m_pOggWavData[fileName], GetInstance()->m_pOggWavData[fileName]->GetFileName());
			// �t�H���_�̖��O��SE���O���X�g�ɓ����.
			GetInstance()->m_vsBGMNameList.emplace_back(fileName);
		}
	};

	try {
		//�w��p�X(FILE_PATH)�f�B���N�g�������ċA�I�ɑ���
		fs::recursive_directory_iterator dir_itr(FILE_PATH), end_itr;
		// eachLoad�֐����s��.
		std::for_each(dir_itr, end_itr, eachLoad);
	}
	// �G���[�L���b�`.
	catch (const fs::filesystem_error& e) {
		const char* errorMessage = e.path1().string().c_str();
		_ASSERT_EXPR(false, L"�T�E���h�f�[�^�쐬���s");
		MessageBox(nullptr, errorMessage, "�T�E���h�f�[�^�쐬���s", MB_OK);
	}
	// ���ʐݒ�.
	VolumeInit();
	// �T�E���h�쐬�I��.
	GetInstance()->m_bEndCreate = true;
	m_Mutex.unlock();
}
//================================================
// BGM.
//=============================

//=============================
// �X���b�h�������BGM���Đ�����֐�(�O���ďo).
//=============================
void CSoundManager::ThreadPlayBGM(const std::string& Name, const bool& LoopFlag)
{
	if (Name.size() == 0) return;
	// �f�[�^�`�F�b�N.
	if (CheckBGMDataIsTrue(Name) == false) return;
	GetInstance()->m_bisEndThread[Name] = false;
	// �X���b�h�ɓ���郉���_�֐�.
	auto BGM = [&]()
	{
		CSoundManager::PlayBGM(Name, GetInstance()->m_bisEndThread[Name]);	// �Đ��֐�.
	};

	DWORD ThreadExitCode = -1;
	// �w�肵��BGM�̖��O�̃X���b�h����n���h��ID�擾.
	GetExitCodeThread(GetInstance()->pBGMThread[Name].native_handle(), &ThreadExitCode);
	// 0xFFFFFFFF���A���Ă�����X���b�h�������Ă��Ȃ��̂œ�����.
	if (ThreadExitCode == 0xFFFFFFFF) GetInstance()->pBGMThread[Name] = std::thread(BGM);
	// �X���b�h�̃n���h��ID��ێ�.
	GetInstance()->InThreadID[Name] = GetInstance()->pBGMThread[Name].get_id();
	// �炵��BGM�̃X���b�h�̉���t���O������.
	GetInstance()->m_bisThreadRelease[Name] = false;
}
//=============================
// BGM�Đ��֐�(�����g�p).
//=============================
void CSoundManager::PlayBGM(const std::string Name, bool& isEnd)
{
	// �f�[�^�`�F�b�N.
	if (CheckBGMDataIsTrue(Name) == false) return;
	// �Đ�.
	GetInstance()->pBgmSource[Name]->Play(GetInstance()->m_pOggWavData[Name],
		GetInstance()->m_pOggWavData[Name]->GetFileName(), isEnd);
}
//=============================
// BGM�ꎞ��~.
//=============================
void CSoundManager::PauseBGM(const std::string Name)
{
	// map�R���e�i�ɃL�[�����݂��ĂȂ���΃��^�[��.
	if (GetInstance()->pBgmSource.find(Name) == GetInstance()->pBgmSource.end()) {
		return;
	}

	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pBgmSource[Name] == nullptr) return;
	// �Q�[���I���t���O�������Ă���΃��^�[��.
	if (GetInstance()->m_bEndGame == true) return;
	// �w�肵��BGM��~.
	GetInstance()->pBgmSource[Name]->Pause();
}
//=============================
// BGM�ĊJ�֐�.
//=============================
void CSoundManager::AgainPlayBGM(const std::string Name)
{
	// map�R���e�i�ɃL�[�����݂��ĂȂ���΃��^�[��.
	if (GetInstance()->pBgmSource.find(Name) == GetInstance()->pBgmSource.end()) {
		return;
	}

	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pBgmSource[Name] == nullptr) return;
	// �Q�[���I���t���O�������Ă���΃��^�[��.
	if (GetInstance()->m_bEndGame == true) return;
	// �w�肵��BGM��~.
	GetInstance()->pBgmSource[Name]->PlayStart();
}

//=============================
// ���ʂ�ύX�ł���X���b�h�̃X�e�[�g�ύX.
//=============================
void CSoundManager::StateChangeVolumeThread(const bool& bFlag)
{
	GetInstance()->m_bResumeSoundVolumeThread = bFlag;
	// ���ꂽ�t���O��true�̎��A����false�̏ꍇ�A�X���b�h���T�X�y���h���Ă��邽��.
	// ���ʂ�ύX����X���b�h���N��������.
	if (bFlag == true) GetInstance()->m_SoundVolumeCv.notify_one();
}
//=============================
// BGM��~�֐�.
//=============================
void CSoundManager::StopBGM(const std::string Name)
{
	// �f�[�^�`�F�b�N.
	if (CheckBGMDataIsTrue(Name) == false) return;
	// �w�肵��BGM��~.
	GetInstance()->pBgmSource[Name]->Stop();
}
//=============================
// BGM�t�F�[�h�A�E�g�֐�.
//=============================
void CSoundManager::FadeOutBGM(const std::string Name)
{
	if (CheckBGMDataIsTrue(Name) == false) return;			// �f�[�^�`�F�b�N.
	GetInstance()->pBgmSource[Name]->SetFadeInFlag(false);	// �t�F�[�h�C�����������ꍇ�A������~�߃t�F�[�h�A�E�g���n�߂�.
	// �t�F�[�h�A�E�g�t���O�𗧂Ă�.
	if (GetInstance()->pBgmSource[Name]->GetFadeOutFlag() == false) GetInstance()->pBgmSource[Name]->SetFadeOutFlag(true);
}
//=============================
// �w��BGM�̉��ʂ̃t�F�[�h�A�E�g���s������Ԃ�.
//=============================
const bool CSoundManager::GetFadeOutBGM(const std::string Name)
{
	if (CheckBGMDataIsTrue(Name) == false) return false; // �f�[�^�`�F�b�N.
	return GetInstance()->pBgmSource[Name]->GetFadeOutFlag();
}
//=============================
// BGM�t�F�[�h�C���֐�.
//=============================
void CSoundManager::FadeInBGM(const std::string Name)
{
	if (CheckBGMDataIsTrue(Name) == false) return;			// �f�[�^�`�F�b�N.	
	GetInstance()->pBgmSource[Name]->SetFadeOutFlag(false); // �t�F�[�h�A�E�g���������ꍇ�A������~�߃t�F�[�h�C�����n�߂�.
	// �t�F�[�h�C���t���O�𗧂Ă�.
	if (GetInstance()->pBgmSource[Name]->GetFadeInFlag() == false ) GetInstance()->pBgmSource[Name]->SetFadeInFlag(true);
}
//=============================
// �w��BGM�̉��ʂ̃t�F�[�h�C�����s������Ԃ�.
//=============================
const bool CSoundManager::GetFadeInBGM(const std::string Name)
{
	if (CheckBGMDataIsTrue(Name) == false) return false; // �f�[�^�`�F�b�N.
	return GetInstance()->pBgmSource[Name]->GetFadeInFlag();
}
//=============================
// �w�肵��BGM�̉��ʂ��擾����֐�.
//=============================
const float CSoundManager::GetBGMVolume(const std::string Name)
{
	// �f�[�^�`�F�b�N.
	if (CheckBGMDataIsTrue(Name) == false) return 0.0f;
	// �Đ����Ă��Ȃ�.
	if (GetInstance()->pBgmSource[Name]->IsPlaying() == false) return 0.0f;
	return GetInstance()->pBgmSource[Name]->GetVolume();
}
//=============================
// �w�肵��BGM�̉��ʂ��Z�b�g����֐�.
//=============================
void CSoundManager::SetBGMVolume(const std::string Name, float Volme)
{
	// �Q�[���I���t���O�������Ă���΃��^�[��.
	if (GetInstance()->m_bEndGame == true) return;

	GetInstance()->pBgmSource[Name]->SetBGMVolume(Volme);
}
//=============================
// BGM���~���A����BGM���Đ����Ă����X���b�h���������.
//=============================
const bool CSoundManager::StopBGMThread(const std::string BGMName)
{
	// �X���b�h���������Ă���΃��^�[��.
	if (GetInstance()->m_bisThreadRelease[BGMName] == true) return true;
	// �Đ����ɐݒ肵���t���O��true�ɂ��āABGM���~�Ɍ����킹��.
	GetInstance()->m_bisEndThread[BGMName] = true;
	DWORD ThreadExitCode = -1;
	// �X���b�h����~�������ǂ�����ID�擾�Ŏ擾.
	GetExitCodeThread(GetInstance()->pBGMThread[BGMName].native_handle(), &ThreadExitCode);
	// �Ԃ��ė���l��4294967295�̏ꍇ�A���������X���b�h�������オ���Ă��Ȃ�(�Đ����Ă��Ȃ�)�̂Ń��^�[��.
	if (ThreadExitCode == 0xFFFFFFFF) return true;
	// ��~���Ă�����0���Ԃ��ė���.
	if (ThreadExitCode == 0) {
		// �X���b�h����A���Ă���ID���A�Đ����ɕێ�����ID�Ɠ��������`�F�b�N.
		if (GetInstance()->InThreadID[BGMName] == GetInstance()->pBGMThread[BGMName].get_id()) {
			GetInstance()->pBGMThread[BGMName].detach();
			GetInstance()->m_bisThreadRelease[BGMName] = true;
			return true;
		}
		return false;
	}
	return false;
}
//=============================
// �w�肵�����O��BGM�X���b�h���Đ������ǂ���.
//=============================
const bool CSoundManager::GetIsPlayBGM(const std::string BGMName)
{
	DWORD ThreadExitCode = -1;
	// �X���b�h����~�������ǂ�����ID�擾�Ŏ擾.
	GetExitCodeThread(GetInstance()->pBGMThread[BGMName].native_handle(), &ThreadExitCode);
	// �Ԃ��ė���l��4294967295�̏ꍇ�A�Đ����Ă��Ȃ�.
	if (ThreadExitCode == 0xFFFFFFFF) return false;
	// 0�Ȃ�X���b�h��~�ς�.
	else if (ThreadExitCode == 0) return false;
	return true;
}
//=============================
// BGM�̃s�b�`�ݒ�.
//=============================
void CSoundManager::SetBGMPitch(const std::string Name, const float Value)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pBgmSource[Name] == nullptr) return;
	GetInstance()->pBgmSource[Name]->SetPitch(Value);
}

//========================================================================================
//	SE.
//====

//=============================
// SE�Đ��֐�.
//=============================
void CSoundManager::PlaySE( const std::string& Name)
{
	// map�R���e�i�ɃL�[�����݂��ĂȂ���΃��^�[��.
	if (GetInstance()->pSeSource.find(Name) == GetInstance()->pSeSource.end()) return;
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	// �Đ�.
	GetInstance()->pSeSource[Name]->Play(GetInstance()->m_pOggWavData[Name]);
}
//=============================
// ���d�Đ����Ȃ�SE�Đ��֐�.
//=============================
void CSoundManager::NoMultipleSEPlay(const std::string & Name)
{
	// map�R���e�i�ɃL�[�����݂��ĂȂ���΃��^�[��.
	if (GetInstance()->pSeSource.find(Name) == GetInstance()->pSeSource.end()) return;
	if (GetInstance()->pSeSource[Name] == nullptr)  return;
	// �Đ�.
	GetInstance()->pSeSource[Name]->NoMultiplePlay(GetInstance()->m_pOggWavData[Name]);
}
//=============================
// SE��~�֐�.
//=============================
void CSoundManager::StopSE(const std::string Name, const size_t ArrayNum)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	GetInstance()->pSeSource[Name]->SeStop(ArrayNum);
}
//=============================
// ���������̑S�Ă�SE�\�[�X��~�֐�.
//=============================
void CSoundManager::StopAllSE(const std::string Name)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	GetInstance()->pSeSource[Name]->AllSeStop();
}
//=============================
// SE��Voice�\�[�X���ő剹�ʂ�ݒ�.
//=============================
void CSoundManager::SetSEVolume(const std::string Name, const float Volume)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	GetInstance()->pSeSource[Name]->SetMaxSEVolume(Volume);
}
//=============================
// �w�肵�����O��SE���Đ������ǂ�����Ԃ� : �Đ����Ȃ�true.
//=============================
bool CSoundManager::GetIsPlaySE(const std::string Name, const size_t ArrayNum)
{
	// ���݂��Ȃ���΃��^�[��false.
	if (GetInstance()->pSeSource[Name] == nullptr) return false;
	return GetInstance()->pSeSource[Name]->IsPlayingSE(ArrayNum);
}
//=============================
// �S��SE���ʂƂ͕ʂ̃T�E���h�\�[�X���̉��ʂ��Z�b�g.
//=============================
void CSoundManager::SetAnotherSEVolume(const std::string Name, const float & Volume)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	GetInstance()->pSeSource[Name]->SetAnotherSEVolume(Volume);
}
//=============================
// �\�[�X���Őݒ肳��Ă��鉹�ʂ�K�p���邩�ǂ���.
//=============================
void CSoundManager::SetUseAnotherSEVolumeFlag(const std::string Name, const bool & bFlag)
{
	// ���݂��Ȃ���΃��^�[��.
	if (GetInstance()->pSeSource[Name] == nullptr) return;
	GetInstance()->pSeSource[Name]->SetUseAnotherSEVolume(bFlag);
}
//=============================
// ����֐�.
//=============================
void CSoundManager::Release()
{
	// ���ʂ�ύX����X���b�h�̉���҂�.
	while (ReleaseChangeSoundVolumeThread() == false);
	// ���ʂ��o�C�i���f�[�^�ɃZ�[�u.
	XAudio2File::CreateBinary(BINARY_FILE_PATH, GetInstance()->m_stSound);

	// SE�̖��O���X�g�������[�v����.
	for (size_t i = 0; i < GetInstance()->m_vsSENameList.size(); i++) {
		StopAllSE(GetInstance()->m_vsSENameList[i]);
		GetInstance()->m_pOggWavData[GetInstance()->m_vsSENameList[i]]->Close();			//WavData�����.
		GetInstance()->pSeSource[GetInstance()->m_vsSENameList[i]]->DestoroySource();	// SoundSource�����.
	}
	// BGM�̖��O���X�g�������[�v����.
	for (size_t i = 0; i < GetInstance()->m_vsBGMNameList.size(); i++) {
		while (StopBGMThread(GetInstance()->m_vsBGMNameList[i]) == false);
		GetInstance()->m_pOggWavData[GetInstance()->m_vsBGMNameList[i]]->Close();		//WavData�����.
		GetInstance()->pBgmSource[GetInstance()->m_vsBGMNameList[i]]->DestoroySource();	// SoundSource�����.
	}
	// �Q�[���I���t���O�𗧂Ă�.
	GetInstance()->m_bEndGame = true;
}
//=============================
// �}�X�^�[���ʃZ�b�g.
//=============================
void CSoundManager::SetMasterVolume(float& MasterVolume)
{
	if (MasterVolume >= 1.0f) MasterVolume = 1.0f;
	if (MasterVolume <= 0.0f) MasterVolume = 0.0f;
	GetInstance()->m_stSound.MasterVolume = MasterVolume;
}
//=============================
// BGM,SE�̉��ʂ�ύX���邽�߂̃X���b�h�𗧂��グ��.
//=============================
void CSoundManager::CreateChangeSoundVolumeThread()
{
	// �X���b�h�쐬�̃t���O�������Ă���΃��^�[��.
	if (GetInstance()->m_isCreateThread == true) return;
	SetChangeVolumeThread();	// �X���b�h�쐬.
	GetInstance()->m_isCreateThread = true;
}
//=============================
// ���ʂ�ύX����X���b�h�𗧂Ă�.
//=============================
void CSoundManager::SetChangeVolumeThread()
{
	DWORD ThreadExitCode = -1;
	// �X���b�h��Ԃ��擾.
	GetExitCodeThread(GetInstance()->m_SoundSourceVolume.native_handle(), &ThreadExitCode);
	// �X���b�h�������Ă���΃��^�[��.
	if (ThreadExitCode != 0xFFFFFFFF && ThreadExitCode != 0) {
		return;
	}
	GetInstance()->m_bMoveSoundVolumeThread = true;
	auto SetBGMVolme = [&]()
	{
		while (GetInstance()->m_bMoveSoundVolumeThread)
		{
			std::unique_lock<std::mutex> lk(GetInstance()->m_SoundVolumemtx); // mutex.
			// �X���b�h��m_bMoveSoundVolumeThread��false�̊Ԃ����ŃT�X�y���h(��ؓ������Ȃ�)�Atrue�ōĊJ.
			GetInstance()->m_SoundVolumeCv.wait(lk, [&] { return GetInstance()->m_bResumeSoundVolumeThread; });
			// BGM�p���[�v.
			for (size_t i = 0; i < GetInstance()->m_vsBGMNameList.size(); i++) {
				GetInstance()->pBgmSource[GetInstance()->m_vsBGMNameList[i]]->SetBGMVolume(CSoundManager::GetInstance()->m_stSound.BGMVolume);	// ���ʂ��Z�b�g.
				if (GetInstance()->m_bMoveSoundVolumeThread == false) break;
			}
			// SE�p���[�v.
			for (size_t i = 0; i < GetInstance()->m_vsSENameList.size(); i++) {
				GetInstance()->pSeSource[GetInstance()->m_vsSENameList[i]]->SetMaxSEVolume(CSoundManager::GetInstance()->m_stSound.SEVolume);	// ���ʂ��Z�b�g.
				if (GetInstance()->m_bMoveSoundVolumeThread == false) break;
			}
		}
	};
	GetInstance()->m_SoundSourceVolume = std::thread(SetBGMVolme);
}
//=============================
// ���ʏ����ݒ�֐�.
//=============================
void CSoundManager::VolumeInit()
{
	HRESULT hr;
	// �o�C�i���f�[�^���特�ʂ�ǂݍ���.
	hr = XAudio2File::LoadBinary(BINARY_FILE_PATH, GetInstance()->m_stSound);
	// �o�C�i���f�[�^�����݂��Ȃ��ꍇ.
	if (hr == E_FAIL) {
		// �o�C�i���f�[�^�V�K�쐬.
		XAudio2File::CreateBinary(BINARY_FILE_PATH, INIT_VOLUME);
		GetInstance()->m_stSound = INIT_VOLUME;
	}
	// BGM�p���[�v.
	for (size_t i = 0; i < GetInstance()->m_vsBGMNameList.size(); i++) {
		GetInstance()->pBgmSource[GetInstance()->m_vsBGMNameList[i]]->SetBGMVolume(CSoundManager::GetInstance()->m_stSound.BGMVolume);	// ���ʂ��Z�b�g.
		if (GetInstance()->m_bMoveSoundVolumeThread == false) break;
	}
	// SE�p���[�v.
	for (size_t i = 0; i < GetInstance()->m_vsSENameList.size(); i++) {
		GetInstance()->pSeSource[GetInstance()->m_vsSENameList[i]]->SetMaxSEVolume(CSoundManager::GetInstance()->m_stSound.SEVolume);	// ���ʂ��Z�b�g.
		if (GetInstance()->m_bMoveSoundVolumeThread == false) break;
	}
	SetMasterVolume(GetInstance()->m_stSound.MasterVolume);
}
bool CSoundManager::CheckBGMDataIsTrue(const std::string Name)
{
	// map�R���e�i�ɃL�[�����݂��Ă��邩.
	if (GetInstance()->pBgmSource.find(Name) == GetInstance()->pBgmSource.end()) return false;
	// ���g�����邩.
	if (GetInstance()->pBgmSource[Name] == nullptr) return false;
	// �Q�[���I���t���O�������Ă��Ȃ���.
	if (GetInstance()->m_bEndGame == true) return false;
	return true;
}
//=============================
// BGM,SE�̉��ʂ�ύX���邽�߂̃X���b�h���������.
//=============================
bool CSoundManager::ReleaseChangeSoundVolumeThread()
{
	GetInstance()->m_bResumeSoundVolumeThread = true;
	// �X���b�h���N��������.
	GetInstance()->m_SoundVolumeCv.notify_one();
	// �X���b�h������ł�����(�X���b�h�������Ă���). 
	if (GetInstance()->m_SoundSourceVolume.joinable() == true) {
		GetInstance()->m_bMoveSoundVolumeThread = false;
		GetInstance()->m_SoundSourceVolume.join();
		while (1)
		{
			if (GetInstance()->m_SoundSourceVolume.joinable() != true) {
				break;
			}
		}
	}
	GetInstance()->m_isCreateThread = false;
	return true;
}
