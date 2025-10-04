/*+===================================================================
	File: FrameManager.cpp
	Summary: �t���[�����[�g�Ǘ��N���X�̃\�[�X�t�@�C��
	Author: ryuu3160
	Date: 2024/08/17	   ����쐬
			  /11/19 10:14 �N���X�S�̂̉���
		  2025/04/08 11:40 �N���X�S�̂̃��t�@�N�^�����O
				 /09 03:07 �啝�ȃ��t�@�N�^�����O

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "FrameManager.hpp"
#include <future>

void FrameManager::Init(float In_fFps)
{
	timeBeginPeriod(1);	// ����\�̐ݒ�

	// ------------------------------
	// ���C���t���[���f�[�^�̐ݒ�
	// ------------------------------
	m_dwTime = timeGetTime();			// ���ݎ��Ԃ̎擾
	m_dwOldTime = m_dwTime;
	m_fMainFps = In_fFps;				// �t���[�����[�g�̐ݒ�
	m_bMainExists = true;				// ���C���f�[�^�̑��݃t���O�𗧂Ă�
}

bool FrameManager::UpdateMain()
{
	// ���C���̃t���[���f�[�^�����݂��Ȃ��ꍇ��false��Ԃ�
	if (!m_bMainExists)
		return false;

	// ���ݎ��Ԃ̍X�V
	m_dwTime = timeGetTime();

	// �t���[�����[�g�̐���
	if (m_dwTime - m_dwOldTime >= 1000 / m_fMainFps)
	{
		m_dwOldTime = m_dwTime;

		// FPS�̌v��
#ifdef _DEBUG
		// Window�n���h�����擾�o���Ă���ꍇ�̂�
		if (m_hWnd != nullptr)
		{
			++FpsCount;// �����񐔂��J�E���g

			if (timeGetTime() - FpsTime >= 1000)	// 1000ms�o�߂�����
			{
				// �����^���當����֕ϊ�
				std::string mes = m_lpcTitleName;	// �E�B���h�E�^�C�g���̎擾
				mes += " [fps]:" + std::to_string(FpsCount);

				SetWindowTextA(m_hWnd, mes.c_str());	// FPS�̕\��

				// ���̌v���̏���
				FpsCount = 0;
				FpsTime = timeGetTime();
			}
		}
#endif // _DEBUG
		return true;
	}
	return false;
}

DWORD FrameManager::GetMainTime() const
{
	return m_dwTime;
}

void FrameManager::AppendLimitation(const std::string &In_strName, float In_fFps, unsigned int In_nLapTime)
{
	// �X���b�h�Z�[�t�ɂ��邽�߂̃��b�N
	std::lock_guard<std::mutex> lock(m_mutexFrameLimit);

	if (In_fFps > m_fMainFps) // ���C����fps�����傫���l��ݒ�ł��Ȃ�
	{
		throw std::invalid_argument("\"Main fps\"�����傫�Ȓl��ݒ肷�邱�Ƃ͂ł��܂���B");
	}

	// �d���`�F�b�N
	CheckExistsLimitAndInterval(In_strName);

	FrameLimitData data{};
	data.m_nFrameCount = 0;			// �t���[���̃J�E���g
	data.m_nLapTime = In_nLapTime;	// 1�T�C�N���ɂ����鎞��
	data.m_nSwitchCount = 0;		// �ؑ։񐔂̏�����

	data.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// �����C���t���[�����Ƃ�1�t���[����i�߂邩�̌v�Z

	m_mapFrameLimitData[In_strName] = data;	// �t���[���f�[�^�̒ǉ�
}

void FrameManager::AppendInterval(const std::string &In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	// �X���b�h�Z�[�t�ɂ��邽�߂̃��b�N
	std::lock_guard<std::mutex> lock(m_mutexInterval);

	// �d���`�F�b�N
	CheckExistsLimitAndInterval(In_strName);

	IntervalData data{};
	data.FrameData.m_nFrameCount = 0;		// �t���[���̃J�E���g
	data.FrameData.m_nLapTime = 1;		// 1�T�C�N���ɂ����鎞��
	data.FrameData.m_nSwitchCount = 0;	// �ؑ։񐔂̏�����

	data.FrameData.m_fAdvanceFrame = In_fTrueFrame;	// true�̃t���[����
	data.fIntervalFrame = In_fIntervalFrame;	// false�̃t���[����

	data.bReturn = false;		// �Ԋu���������T�C�N���Ɏg��

	m_mapIntervalData[In_strName] = data;	// �t���[���f�[�^�̒ǉ�
}

bool FrameManager::Update(const std::string &In_strName)
{
	auto LimitItr = m_mapFrameLimitData.find(In_strName);	// �t���[���f�[�^�̒T��
	std::unordered_map<std::string, IntervalData>::iterator IntervalItr; // �C���^�[�o���f�[�^�̃C�e���[�^

	// �t���[���f�[�^�̒T��
	if (LimitItr != m_mapFrameLimitData.end())
	{
		return UpdateLimitation(LimitItr);	// �t���[���f�[�^�̍X�V����
	}
	// �C���^�[�o���f�[�^�̒T��
	else if ((IntervalItr = m_mapIntervalData.find(In_strName)) != m_mapIntervalData.end())
	{
		return UpdateInterval(IntervalItr);	// �Ԋu��������o�[�W�����̍X�V����
	}

	// �t���[���f�[�^�����݂��Ȃ��ꍇ��false��Ԃ�
	return false;
}

void FrameManager::FrameCountReset(const std::string &In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
		itr->second.m_nFrameCount = 0;	// �t���[���̃J�E���g�����Z�b�g
}

void FrameManager::SwitchCountReset(const std::string &In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
		itr->second.m_nSwitchCount = 0;	// �ؑ։񐔂̃��Z�b�g
}

void FrameManager::ChangeFps(const std::string &In_strName, float In_fFps, unsigned int In_nLapTime)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
	{
		itr->second.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// �����C���t���[�����Ƃ�1�t���[����i�߂邩�̌v�Z
	}
}

void FrameManager::ChangeIntervalFrame(const std::string &In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	auto itr = m_mapIntervalData.find(In_strName);
	if (itr != m_mapIntervalData.end())
	{
		if (In_fTrueFrame > 0)
			itr->second.FrameData.m_fAdvanceFrame = In_fTrueFrame;
		if(In_fIntervalFrame > 0)
			itr->second.fIntervalFrame = In_fIntervalFrame;
	}
}

int FrameManager::GetSwitchCount(const std::string &In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
		return itr->second.m_nSwitchCount;
	else
		return -1;
}

void FrameManager::AppendTimeCounter(const std::string &In_strName, bool In_bIsStartNow)
{
	// �X���b�h�Z�[�t�ɂ��邽�߂̃��b�N
	std::lock_guard<std::mutex> lock(m_mutexTimeCounter);

	// ���O�̏d���`�F�b�N
	if (m_mapTimeCounter.find(In_strName) != m_mapTimeCounter.end())
		return;

	TimeCountData data{};
	data.m_dwCount = 0;

	// �����Ɍv�����n�߂邩�ǂ���
	if (In_bIsStartNow)
		data.m_bIsStart = true;
	else
		data.m_bIsStart = false;

	m_mapTimeCounter[In_strName] = data; // �f�[�^�ǉ�
}

void FrameManager::StartTimeCounter(const std::string &In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr != m_mapTimeCounter.end())
		itr->second.m_bIsStart = true;	// �v���J�n
}

void FrameManager::UpdateAllTimeCounter()
{
	for (auto &data : m_mapTimeCounter)
	{
		if (data.second.m_bIsStart)
			data.second.m_dwCount++;	// �J�E���g��i�߂�
	}
}

void FrameManager::UpdateTimeCounter(const std::string &In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr == m_mapTimeCounter.end())
		return;

	if (itr->second.m_bIsStart)
		itr->second.m_dwCount++;	// �J�E���g��i�߂�
}

void FrameManager::StopAllTimeCounter()
{
	for (auto &data : m_mapTimeCounter)
	{
		data.second.m_bIsStart = false;	// �v�����~�߂�
	}
}

void FrameManager::StopTimeCounter(const std::string &In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if(itr != m_mapTimeCounter.end())
		itr->second.m_bIsStart = false;	// �v�����~�߂�
}

void FrameManager::ResetAllTimeCounter()
{
	for (auto &data : m_mapTimeCounter)
		data.second.m_dwCount = 0;
}

void FrameManager::ResetTimeCounter(const std::string &In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr != m_mapTimeCounter.end())
		itr->second.m_dwCount = 0;	// �J�E���g�����Z�b�g
}

float FrameManager::GetTimeCountSecond(const std::string &In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr == m_mapTimeCounter.end())
		return -1.0f;

	return static_cast<float>(itr->second.m_dwCount) / m_fMainFps;
}

void FrameManager::Delete(const std::string &In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end()) m_mapFrameLimitData.erase(itr);	// �t���[���f�[�^�̍폜
}

FrameManager::FrameManager() : m_dwTime(0), m_dwOldTime(0), m_fMainFps(0.0f), m_bMainExists(false)
{
}

FrameManager::~FrameManager()
{
	m_mapFrameLimitData.clear();	// �t���[���f�[�^�̃N���A
	m_mapTimeCounter.clear();	// �^�C���J�E���^�[�̃N���A
	m_bMainExists = false;
	timeEndPeriod(1);	// ����\�̉���
}

bool FrameManager::UpdateLimitation(std::unordered_map<std::string, FrameLimitData>::iterator In_itr)
{
	// ���ݎ��Ԃ̍X�V
	In_itr->second.m_nFrameCount++; // �t���[���̃J�E���g��i�߂�

	// �t���[�����[�g�̐���
	if (In_itr->second.m_nFrameCount >= In_itr->second.m_fAdvanceFrame)
	{
		In_itr->second.m_nFrameCount = 0;
		In_itr->second.m_nSwitchCount++;
		return true;
	}
	return false;
}

bool FrameManager::UpdateInterval(std::unordered_map<std::string, IntervalData>::iterator In_itr)
{
	//���݃t���[���̍X�V
	In_itr->second.FrameData.m_nFrameCount++;

	// ���݂�Return�̏�Ԃɉ����āA�t���[�����̖ڕW�l���擾
	float fFrame;
	if(In_itr->second.bReturn)
		fFrame = In_itr->second.FrameData.m_fAdvanceFrame;
	else
		fFrame = In_itr->second.fIntervalFrame;

	// �t���[�����[�g�̐���
	if (In_itr->second.FrameData.m_nFrameCount >= fFrame)
	{
		In_itr->second.FrameData.m_nFrameCount = 0;// �t���[���̃J�E���g�����Z�b�g
		In_itr->second.FrameData.m_nSwitchCount++; // �ؑ։񐔂̃J�E���g
		In_itr->second.bReturn = !In_itr->second.bReturn; // Return�̏�Ԃ𔽓]
	}

	return In_itr->second.bReturn;
}

void FrameManager::CheckExistsLimitAndInterval(const std::string &In_strName)
{
	// �t���[���f�[�^����Limitation,Interval�̂ǂ��炩�Ɋ��ɑ��݂���ꍇ�̓G���[���b�Z�[�W���o�͂��āA�X�L�b�v
	if (m_mapFrameLimitData.find(In_strName) != m_mapFrameLimitData.end())
	{
		throw std::invalid_argument("���̖��O�͊���\"Limitation\"�Ŏg�p����Ă��܂��B");
	}
	else if (m_mapIntervalData.find(In_strName) != m_mapIntervalData.end())
	{
		throw std::invalid_argument("���̖��O�͊���\"Interval\"�Ŏg�p����Ă��܂��B");
	}
}
