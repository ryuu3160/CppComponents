/*+===================================================================
	File: FrameManager.cpp
	Summary: フレームレート管理クラスのソースファイル
	Author: ryuu3160
	Date: 2024/08/17	   初回作成
			  /11/19 10:14 クラス全体の改良
		  2025/04/08 11:40 クラス全体のリファクタリング

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "FrameManager.hpp"
#include <future>

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
	// メインのフレームデータが存在しない場合はfalseを返す
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

void FrameManager::AppendLimitation(std::string In_strName, float In_fFps, unsigned int In_nLapTime)
{
	if (In_fFps > m_fMainFps) // メインのfpsよりも大きい値を設定できない
	{
		OutputDebugStringA("error : FrameManager Error : Cannot set a value greater than the \"Main fps\"\n");
		return;
	}

	// フレームデータ名がLimitation,Intervalのどちらかに既に存在する場合はエラーメッセージを出力して、スキップ
	if (m_mapFrameLimitData.find(In_strName) != m_mapFrameLimitData.end())
	{
		OutputDebugStringA("error : FrameManager Error : This name already exists in \"Limitation\"\n");
		return;
	}
	else if (m_mapIntervalData.find(In_strName) != m_mapIntervalData.end())
	{
		OutputDebugStringA("error : FrameManager Error : This name already exists in \"Interval\"\n");
		return;
	}

	FrameLimitData data{};
	data.m_nFrameCount = 0;			// フレームのカウント
	data.m_nLapTime = In_nLapTime;	// 1サイクルにかける時間
	data.m_nSwitchCount = 0;		// 切替回数の初期化

	data.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// 何メインフレームごとに1フレームを進めるかの計算

	m_mapFrameLimitData[In_strName] = data;	// フレームデータの追加
}

void FrameManager::AppendInterval(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame)
{
	// フレームデータ名がLimitation,Intervalのどちらかに既に存在する場合はエラーメッセージを出力して、スキップ
	if (m_mapFrameLimitData.find(In_strName) != m_mapFrameLimitData.end())
	{
		OutputDebugStringA("error : FrameManager Error : This name already exists in \"Limitation\"\n");
		return;
	}
	else if (m_mapIntervalData.find(In_strName) != m_mapIntervalData.end())
	{
		OutputDebugStringA("error : FrameManager Error : This name already exists in \"Interval\"\n");
		return;
	}

	IntervalData data{};
	data.FrameData.m_nFrameCount = 0;		// フレームのカウント
	data.FrameData.m_nLapTime = 1;		// 1サイクルにかける時間
	data.FrameData.m_nSwitchCount = 0;	// 切替回数の初期化

	data.FrameData.m_fAdvanceFrame = In_fTrueFrame;	// trueのフレーム数
	data.fIntervalFrame = In_fIntervalFrame;	// falseのフレーム数

	data.bReturn = false;		// 間隔をあけたサイクルに使う

	m_mapIntervalData[In_strName] = data;	// フレームデータの追加
}

bool FrameManager::Update(std::string In_strName)
{
	// マルチスレッドで2つのmapを同時探索
	// Update関数では速度を優先するため、マルチスレッドを採用
	std::future<std::unordered_map<std::string, FrameLimitData>::iterator> FrameLimit
		= std::async(std::launch::async,&FrameManager::FindFrameLimit,this, In_strName);
	std::future<std::unordered_map<std::string, IntervalData>::iterator> Interval
		= std::async(std::launch::async, &FrameManager::FindInterval, this, In_strName);

	auto LimitItr = FrameLimit.get();
	auto IntervalItr = Interval.get();
	if (LimitItr != m_mapFrameLimitData.end())
	{
		return UpdateLimitation(LimitItr);	// フレームデータの更新
	}
	else if(IntervalItr != m_mapIntervalData.end())
	{
		return UpdateInterval(IntervalItr);	// 間隔をあけるバージョン
	}

	// フレームデータが存在しない場合はfalseを返す
	return false;
}

void FrameManager::FrameCountReset(std::string In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
		itr->second.m_nFrameCount = 0;	// フレームのカウントをリセット
}

void FrameManager::SwitchCountReset(std::string In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
		itr->second.m_nSwitchCount = 0;	// 切替回数のリセット
}

void FrameManager::ChangeFps(std::string In_strName, float In_fFps, unsigned int In_nLapTime)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
	{
		itr->second.m_fAdvanceFrame = (m_fMainFps * In_nLapTime) / In_fFps;	// 何メインフレームごとに1フレームを進めるかの計算
	}
}

void FrameManager::ChangeIntervalFrame(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame)
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

int FrameManager::GetSwitchCount(std::string In_strName)
{
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end())
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
	auto itr = m_mapFrameLimitData.find(In_strName);
	if (itr != m_mapFrameLimitData.end()) m_mapFrameLimitData.erase(itr);	// フレームデータの削除
}

FrameManager::FrameManager() : m_dwTime(0), m_dwOldTime(0), m_fMainFps(0.0f), m_bMainExists(false)
{
}

FrameManager::~FrameManager()
{
	m_mapFrameLimitData.clear();	// フレームデータのクリア
	m_mapTimeCounter.clear();	// タイムカウンターのクリア
	m_bMainExists = false;
	timeEndPeriod(1);	// 分解能の解除
}

bool FrameManager::UpdateLimitation(std::unordered_map<std::string, FrameLimitData>::iterator In_itr)
{
	// 現在時間の更新
	In_itr->second.m_nFrameCount++; // フレームのカウントを進める

	// フレームレートの制限
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
	//現在フレームの更新
	In_itr->second.FrameData.m_nFrameCount++;

	if (In_itr->second.bReturn)
	{
		if (In_itr->second.FrameData.m_nFrameCount >= In_itr->second.FrameData.m_fAdvanceFrame)
		{
			In_itr->second.FrameData.m_nFrameCount = 0;// フレームのカウントをリセット
			In_itr->second.FrameData.m_nSwitchCount++; // 切替回数のカウント
			In_itr->second.bReturn = false;
		}
	}
	else
	{
		if (In_itr->second.FrameData.m_nFrameCount >= In_itr->second.fIntervalFrame)
		{
			In_itr->second.FrameData.m_nFrameCount = 0;// フレームのカウントをリセット
			In_itr->second.FrameData.m_nSwitchCount++; // 切替回数のカウント
			In_itr->second.bReturn = true;
		}
	}

	return In_itr->second.bReturn;
}

std::unordered_map<std::string, FrameManager::FrameLimitData>::iterator FrameManager::FindFrameLimit(std::string In_strName)
{
	return m_mapFrameLimitData.find(In_strName);
}

std::unordered_map<std::string, FrameManager::IntervalData>::iterator FrameManager::FindInterval(std::string In_strName)
{
	return m_mapIntervalData.find(In_strName);
}
