/*+===================================================================
	File: FrameManager.cpp
	Summary: �t���[�����[�g�Ǘ��N���X�̃\�[�X�t�@�C��
	Author: ryuu3160
	Date: 2024/08/17	   ����쐬

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "FrameManager.hpp"

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
	// �G���[����
	if (!m_bMainExists)
		return false;

	// ���ݎ��Ԃ̍X�V
	m_dwTime = timeGetTime();

	// �t���[�����[�g�̐���
	if (m_dwTime - m_dwOldTime >= 1000 / m_fMainFps)
	{
		m_dwOldTime = m_dwTime;
		return true;
	}
	return false;
}

DWORD FrameManager::GetMainTime()
{
	return m_dwTime;
}

void FrameManager::Append(std::string In_strName, float In_fFps, unsigned int In_nLapTime)
{
	if (In_fFps > m_fMainFps)	// ���C����fps�����傫���l��ݒ�ł��Ȃ�
	{
		MessageBoxA(nullptr,"Cannot set a value greater than the \"Main fps\"", "FrameManager Error",MB_OK);
		return;
	}

	FrameData data{};
	data.m_nFrameCount = 0;			// �t���[���̃J�E���g
	data.m_nLapTime = In_nLapTime;	// 1�T�C�N���ɂ����鎞��
	data.m_nSwitchCount = 0;		// �ؑ։񐔂̏�����

	data.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// �����C���t���[�����Ƃ�1�t���[����i�߂邩�̌v�Z

	// ��������Append�ł͎g��Ȃ��f�[�^
	data.m_bIsInterval = false;
	data.m_bReturn = false;
	data.m_fIntervalFrame = 0.0f;

	m_mapFrameData[In_strName] = data;	// �t���[���f�[�^�̒ǉ�
}

void FrameManager::AppendInterval(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	FrameData data{};
	data.m_nFrameCount = 0;		// �t���[���̃J�E���g
	data.m_nLapTime = 1;		// 1�T�C�N���ɂ����鎞��
	data.m_nSwitchCount = 0;	// �ؑ։񐔂̏�����

	data.m_fAdvanceFrame = In_fTrueFrame;	// true�̃t���[����
	data.m_fIntervalFrame = In_fIntervalFrame;	// false�̃t���[����

	data.m_bReturn = false;		// �Ԋu���������T�C�N���Ɏg��

	data.m_bIsInterval = true;	// �Ԋu��������o�[�W����

	m_mapFrameData[In_strName] = data;	// �t���[���f�[�^�̒ǉ�
}

bool FrameManager::Update(std::string In_strName)
{
	// �G���[����
	auto itr = m_mapFrameData.find(In_strName);
	if (itr == m_mapFrameData.end())
	{
		return false;
	}
	
	if (itr->second.m_bIsInterval)	// �Ԋu��������o�[�W����
	{
		return UpdateInterval(itr);
	}

	// ���ݎ��Ԃ̍X�V
	itr->second.m_nFrameCount++; // �t���[���̃J�E���g��i�߂�

	// �t���[�����[�g�̐���
	if (itr->second.m_nFrameCount >= itr->second.m_fAdvanceFrame)
	{
		itr->second.m_nFrameCount = 0;
		itr->second.m_nSwitchCount++;
		return true;
	}
	return false;
}

void FrameManager::FrameCountReset(std::string In_strName)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
		itr->second.m_nFrameCount = 0;	// �t���[���̃J�E���g�����Z�b�g
}

void FrameManager::SwitchCountReset(std::string In_strName)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
		itr->second.m_nSwitchCount = 0;	// �ؑ։񐔂̃��Z�b�g
}

void FrameManager::ChangeFps(std::string In_strName, float In_fFps, unsigned int In_nLapTime)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
	{
		if(!itr->second.m_bIsInterval)
			itr->second.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// �����C���t���[�����Ƃ�1�t���[����i�߂邩�̌v�Z
	}
}

void FrameManager::ChangeIntervalFrame(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
	{
		if (itr->second.m_bIsInterval)
		{
			if (In_fTrueFrame > 0)
				itr->second.m_fAdvanceFrame = In_fTrueFrame;
			if(In_fIntervalFrame > 0)
				itr->second.m_fIntervalFrame = In_fIntervalFrame;
		}
	}
}

int FrameManager::GetSwitchCount(std::string In_strName)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
		return itr->second.m_nSwitchCount;
	else
		return -1;
}

void FrameManager::AppendTimeCounter(std::string In_strName, bool In_bIsStartNow)
{
	if (m_mapTimeCounter.find(In_strName) != m_mapTimeCounter.end())
		return;

	TimeCountData data;
	data.m_dwCount = 0;
	
	// �����Ɍv�����n�߂邩�ǂ���
	if (In_bIsStartNow)
		data.m_bIsStart = true;
	else
		data.m_bIsStart = false;

	m_mapTimeCounter[In_strName] = data; // �f�[�^�ǉ�
}

void FrameManager::StartTimeCounter(std::string In_strName)
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

void FrameManager::UpdateTimeCounter(std::string In_strName)
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

void FrameManager::StopTimeCounter(std::string In_strName)
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

void FrameManager::ResetTimeCounter(std::string In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr != m_mapTimeCounter.end())
		itr->second.m_dwCount = 0;	// �J�E���g�����Z�b�g
}

float FrameManager::GetTimeCountSecond(std::string In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr == m_mapTimeCounter.end())
		return -1.0f;

	return static_cast<float>(itr->second.m_dwCount) / m_fMainFps;
}

void FrameManager::Delete(std::string In_strName)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end()) m_mapFrameData.erase(itr);	// �t���[���f�[�^�̍폜
}

FrameManager::FrameManager() : m_dwTime(0), m_dwOldTime(0), m_fMainFps(0.0f), m_bMainExists(false)
{
}

FrameManager::~FrameManager()
{
	m_mapFrameData.clear();	// �t���[���f�[�^�̃N���A
	m_mapTimeCounter.clear();	// �^�C���J�E���^�[�̃N���A
	m_bMainExists = false;
	timeEndPeriod(1);	// ����\�̉���
}

bool FrameManager::UpdateInterval(std::unordered_map<std::string, FrameData>::iterator In_itr)
{
	//���݃t���[���̍X�V
	In_itr->second.m_nFrameCount++;

	if (In_itr->second.m_bReturn)
	{
		if (In_itr->second.m_nFrameCount >= In_itr->second.m_fAdvanceFrame)
		{
			In_itr->second.m_nFrameCount = 0;// �t���[���̃J�E���g�����Z�b�g
			In_itr->second.m_nSwitchCount++; // �ؑ։񐔂̃J�E���g
			In_itr->second.m_bReturn = false;
		}
	}
	else
	{
		if (In_itr->second.m_nFrameCount >= In_itr->second.m_fIntervalFrame)
		{
			In_itr->second.m_nFrameCount = 0;// �t���[���̃J�E���g�����Z�b�g
			In_itr->second.m_nSwitchCount++; // �ؑ։񐔂̃J�E���g
			In_itr->second.m_bReturn = true;
		}
	}

	return In_itr->second.m_bReturn;
}
