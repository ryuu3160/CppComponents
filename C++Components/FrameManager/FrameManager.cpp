/*+===================================================================
	File: FrameManager.cpp
	Summary: フレームレート管理クラスのソースファイル
	Author: ryuu3160
	Date: 2024/08/17	   初回作成

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "FrameManager.hpp"

void FrameManager::Init(float In_fFps)
{
	timeBeginPeriod(1);	// 分解能の設定

	// ------------------------------
	// メインフレームデータの設定
	// ------------------------------
	m_dwTime = timeGetTime();			// 現在時間の取得
	m_dwOldTime = m_dwTime;
	m_fMainFps = In_fFps;				// フレームレートの設定
	m_bMainExists = true;				// メインデータの存在フラグを立てる
}

bool FrameManager::UpdateMain()
{
	// エラー処理
	if (!m_bMainExists)
		return false;

	// 現在時間の更新
	m_dwTime = timeGetTime();

	// フレームレートの制限
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
	if (In_fFps > m_fMainFps)	// メインのfpsよりも大きい値を設定できない
	{
		MessageBoxA(nullptr,"Cannot set a value greater than the \"Main fps\"", "FrameManager Error",MB_OK);
		return;
	}

	FrameData data{};
	data.m_nFrameCount = 0;			// フレームのカウント
	data.m_nLapTime = In_nLapTime;	// 1サイクルにかける時間
	data.m_nSwitchCount = 0;		// 切替回数の初期化

	data.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// 何メインフレームごとに1フレームを進めるかの計算

	// こっちのAppendでは使わないデータ
	data.m_bIsInterval = false;
	data.m_bReturn = false;
	data.m_fIntervalFrame = 0.0f;

	m_mapFrameData[In_strName] = data;	// フレームデータの追加
}

void FrameManager::AppendInterval(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	FrameData data{};
	data.m_nFrameCount = 0;		// フレームのカウント
	data.m_nLapTime = 1;		// 1サイクルにかける時間
	data.m_nSwitchCount = 0;	// 切替回数の初期化

	data.m_fAdvanceFrame = In_fTrueFrame;	// trueのフレーム数
	data.m_fIntervalFrame = In_fIntervalFrame;	// falseのフレーム数

	data.m_bReturn = false;		// 間隔をあけたサイクルに使う

	data.m_bIsInterval = true;	// 間隔をあけるバージョン

	m_mapFrameData[In_strName] = data;	// フレームデータの追加
}

bool FrameManager::Update(std::string In_strName)
{
	// エラー処理
	auto itr = m_mapFrameData.find(In_strName);
	if (itr == m_mapFrameData.end())
	{
		return false;
	}
	
	if (itr->second.m_bIsInterval)	// 間隔をあけるバージョン
	{
		return UpdateInterval(itr);
	}

	// 現在時間の更新
	itr->second.m_nFrameCount++; // フレームのカウントを進める

	// フレームレートの制限
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
		itr->second.m_nFrameCount = 0;	// フレームのカウントをリセット
}

void FrameManager::SwitchCountReset(std::string In_strName)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
		itr->second.m_nSwitchCount = 0;	// 切替回数のリセット
}

void FrameManager::ChangeFps(std::string In_strName, float In_fFps, unsigned int In_nLapTime)
{
	auto itr = m_mapFrameData.find(In_strName);
	if (itr != m_mapFrameData.end())
	{
		if(!itr->second.m_bIsInterval)
			itr->second.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// 何メインフレームごとに1フレームを進めるかの計算
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
	
	// すぐに計測を始めるかどうか
	if (In_bIsStartNow)
		data.m_bIsStart = true;
	else
		data.m_bIsStart = false;

	m_mapTimeCounter[In_strName] = data; // データ追加
}

void FrameManager::StartTimeCounter(std::string In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr != m_mapTimeCounter.end())
		itr->second.m_bIsStart = true;	// 計測開始
}

void FrameManager::UpdateAllTimeCounter()
{
	for (auto &data : m_mapTimeCounter)
	{
		if (data.second.m_bIsStart)
			data.second.m_dwCount++;	// カウントを進める
	}
}

void FrameManager::UpdateTimeCounter(std::string In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if (itr == m_mapTimeCounter.end())
		return;

	if (itr->second.m_bIsStart)
		itr->second.m_dwCount++;	// カウントを進める
}

void FrameManager::StopAllTimeCounter()
{
	for (auto &data : m_mapTimeCounter)
	{
		data.second.m_bIsStart = false;	// 計測を止める
	}
}

void FrameManager::StopTimeCounter(std::string In_strName)
{
	auto itr = m_mapTimeCounter.find(In_strName);
	if(itr != m_mapTimeCounter.end())
		itr->second.m_bIsStart = false;	// 計測を止める
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
		itr->second.m_dwCount = 0;	// カウントをリセット
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
	if (itr != m_mapFrameData.end()) m_mapFrameData.erase(itr);	// フレームデータの削除
}

FrameManager::FrameManager() : m_dwTime(0), m_dwOldTime(0), m_fMainFps(0.0f), m_bMainExists(false)
{
}

FrameManager::~FrameManager()
{
	m_mapFrameData.clear();	// フレームデータのクリア
	m_mapTimeCounter.clear();	// タイムカウンターのクリア
	m_bMainExists = false;
	timeEndPeriod(1);	// 分解能の解除
}

bool FrameManager::UpdateInterval(std::unordered_map<std::string, FrameData>::iterator In_itr)
{
	//現在フレームの更新
	In_itr->second.m_nFrameCount++;

	if (In_itr->second.m_bReturn)
	{
		if (In_itr->second.m_nFrameCount >= In_itr->second.m_fAdvanceFrame)
		{
			In_itr->second.m_nFrameCount = 0;// フレームのカウントをリセット
			In_itr->second.m_nSwitchCount++; // 切替回数のカウント
			In_itr->second.m_bReturn = false;
		}
	}
	else
	{
		if (In_itr->second.m_nFrameCount >= In_itr->second.m_fIntervalFrame)
		{
			In_itr->second.m_nFrameCount = 0;// フレームのカウントをリセット
			In_itr->second.m_nSwitchCount++; // 切替回数のカウント
			In_itr->second.m_bReturn = true;
		}
	}

	return In_itr->second.m_bReturn;
}
