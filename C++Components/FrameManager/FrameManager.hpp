/*+===================================================================
	File: FrameManager.hpp
	Summary: �t���[�����[�g�Ǘ��N���X�̃w�b�_�t�@�C��
	Author: ryuu3160
	Date: 2024/08/17	   ����쐬
			  /11/19 10:14 �N���X�S�̂̉���
		  2025/04/08 11:40 �N���X�S�̂̃��t�@�N�^�����O
				 /09 03:07 �啝�ȃ��t�@�N�^�����O

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../Singleton/Singleton.hpp"
#include <windows.h>
#include <unordered_map>
// timeGetTime�Ȃǂ��g�����߂ɕK�v
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

/// <summary>
/// �t���[�����[�g�Ǘ��N���X
/// </summary>
class FrameManager : public Singleton<FrameManager>
{
	friend class Singleton<FrameManager>;
public:
	/// <summary>
	/// �t���[�����[�g�������imain�j
	/// </summary>
	/// <param name="[In_fFps]">�X�V����t���[����</param>
	void Init(float In_fFps);

	/// <summary>
	/// �t���[�����[�g�̐����imain�j
	/// </summary>
	/// <returns>�ݒ肵���t���[�����𒴂��Ă����ꍇtrue��Ԃ�</returns>
	bool UpdateMain();

	/// <summary>
	/// ���ݎ��Ԃ̎擾�imain�j
	/// </summary>
	/// <returns>���ݎ��ԁims�j</returns>
	DWORD GetMainTime();

	/// <summary>
	/// <para>�t���[�����[�g�����̒ǉ�</para>
	/// <para>�t���[�����[�g�̓��C����fps�����傫�Ȓl�͐ݒ�ł��Ȃ�</para>
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <param name="[In_fFps]">�t���[�����[�g(1�T�C�N���ŏ����������t���[����)</param>
	/// <param name="[In_nLapTime]">1�T�C�N���ɂ����鎞��(�f�t�H���g��1�b)</param>
	void AppendLimitation(const std::string &In_strName, float In_fFps, unsigned int In_nLapTime = 1);

	/// <summary>
	/// <para>�Ԋu��������t���[���f�[�^�̒ǉ�</para>
	/// <para>�w�肵���t���[������true��false��؂�ւ���</para>
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <param name="[In_fTrueFrame]">true�ɂ���t���[����</param>
	/// <param name="[In_fIntervalFrame]">false�ɂ���t���[����</param>
	void AppendInterval(const std::string &In_strName, float In_fTrueFrame, float In_fIntervalFrame);

	/// <summary>
	/// �w�肵���t���[���f�[�^�̍X�V
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <returns>�ݒ肵���t���[�����𒴂��Ă����ꍇtrue��Ԃ�</returns>
	bool Update(const std::string &In_strName);

	/// <summary>
	/// �w�肵���t���[���f�[�^�̃J�E���g�����Z�b�g
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	void FrameCountReset(const std::string &In_strName);

	/// <summary>
	/// �w�肵���t���[���f�[�^�̐ؑ։񐔂����Z�b�g
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	void SwitchCountReset(const std::string &In_strName);

	/// <summary>
	/// �w�肵���t���[���f�[�^�̃t���[�����[�g�̕ύX
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <param name="[In_fFps]">�t���[�����[�g</param>
	/// <param name="[In_nLapTime]">1�T�C�N���ɂ����鎞��(�f�t�H���g��1�b)</param>
	void ChangeFps(const std::string &In_strName, float In_fFps,unsigned int In_nLapTime = 1);

	/// <summary>
	/// <para>�w�肵���t���[���f�[�^��True-False�ؑփt���[�����̕ύX</para>
	/// <para>�w�肷��t���[������-1����ꂽ�ꍇ�͂��̒l�͕ύX���Ȃ�</para>
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <param name="[In_fTrueFrame]">true�ɂ���t���[����</param>
	/// <param name="[In_fIntervalFrame]">false�ɂ���t���[����</param>
	void ChangeIntervalFrame(const std::string &In_strName, float In_fTrueFrame = -1, float In_fIntervalFrame = -1);

	/// <summary>
	/// �w�肵���t���[���f�[�^�����v�ŉ���TRUE��FALSE��؂�ւ��������擾
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	/// <returns>�؂�ւ��� ���t���[���f�[�^�����݂��Ȃ��ꍇ��-1��Ԃ�</returns>
	int GetSwitchCount(const std::string &In_strName);

	/// <summary>
	/// �^�C���J�E���^�[��ǉ�
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	/// <param name="[In_bIsStartNow]">�����Ɍv�����J�n���邩</param>
	void AppendTimeCounter(const std::string &In_strName, bool In_bIsStartNow = false);

	/// <summary>
	/// �^�C���J�E���^�[�̌v�����J�n
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	void StartTimeCounter(const std::string &In_strName);

	/// <summary>
	/// �S�Ẵ^�C���J�E���^�[�̍X�V
	/// </summary>
	void UpdateAllTimeCounter();

	/// <summary>
	/// �^�C���J�E���^�[�̍X�V
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	void UpdateTimeCounter(const std::string &In_strName);

	/// <summary>
	/// �S�Ẵ^�C���J�E���^�[���~�߂�
	/// </summary>
	void StopAllTimeCounter();

	/// <summary>
	/// �^�C���J�E���^�[���~�߂�
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	void StopTimeCounter(const std::string &In_strName);

	/// <summary>
	/// �S�Ẵ^�C���J�E���^�[�����Z�b�g
	/// </summary>
	void ResetAllTimeCounter();

	/// <summary>
	/// �^�C���J�E���^�[�����Z�b�g
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	void ResetTimeCounter(const std::string &In_strName);

	/// <summary>
	/// �^�C���J�E���^�[��b�ɕϊ����擾
	/// </summary>
	/// <param name="[In_strName]">�J�E���^�[��</param>
	/// <returns>�b</returns>
	float GetTimeCountSecond(const std::string &In_strName);

	/// <summary>
	/// �t���[���f�[�^�̍폜
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	void Delete(const std::string &In_strName);

private:
	FrameManager();
	~FrameManager();

private:
	// ���C���̃t���[���f�[�^
	DWORD m_dwTime;
	DWORD m_dwOldTime;
	float m_fMainFps;
	bool m_bMainExists;

	// �X���b�h�Z�[�t�̂��߂̃~���[�e�b�N�X
	std::mutex m_mutexFrameLimit;
	std::mutex m_mutexInterval;
	std::mutex m_mutexTimeCounter;

	/// <summary>
	/// �t���[���f�[�^�\����
	/// </summary>
	struct FrameLimitData
	{
		int m_nFrameCount;			// �t���[���̃J�E���g
		int m_nSwitchCount;			// ����؂�ւ�����
		unsigned int m_nLapTime;	// 1�T�C�N���ɂ����鎞��
		float m_fAdvanceFrame;		// �����C���t���[�����ƂɃt���[����i�߂邩
	};

	/// <summary>
	/// �C���^�[�o���Ŏg�p����\����
	/// </summary>
	struct IntervalData
	{
		FrameLimitData FrameData;	// �t���[���f�[�^
		float fIntervalFrame;		// �t���[���̊Ԋu
		bool bReturn;				// �Ԋu���������T�C�N���Ɏg��
	};

	/// <summary>
	/// �J�E���g�p�̍\����
	/// </summary>
	struct TimeCountData
	{
		DWORD m_dwCount;	// �J�E���g
		bool m_bIsStart;	// �v������
	};

	std::unordered_map<std::string, FrameLimitData> m_mapFrameLimitData;	// �t���[���f�[�^
	std::unordered_map<std::string, IntervalData> m_mapIntervalData;		// �C���^�[�o���f�[�^
	std::unordered_map<std::string, TimeCountData> m_mapTimeCounter;		// ���Ԍv���p
private:

	/// <summary>
	/// �t���[���f�[�^�̍X�V
	/// </summary>
	/// <param name="[In_itr]">�X�V����t���[���f�[�^</param>
	bool UpdateLimitation(std::unordered_map<std::string, FrameLimitData>::iterator In_itr);

	/// <summary>
	/// �t���[���f�[�^�̍X�V(�Ԋu��������o�[�W����)
	/// </summary>
	/// <param name="[In_itr]">�X�V����t���[���f�[�^</param>
	bool UpdateInterval(std::unordered_map<std::string, IntervalData>::iterator In_itr);

	/// <summary>
	/// �t���[���f�[�^�����݂��邩
	/// </summary>
	/// <param name="[In_strName]">�t���[���f�[�^��</param>
	void CheckExistsLimitAndInterval(const std::string &In_strName);
};
