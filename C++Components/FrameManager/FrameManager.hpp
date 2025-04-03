/*+===================================================================
	File: FrameManager.hpp
	Summary: フレームレート管理クラスのヘッダファイル
	Author: ryuu3160
	Date: 2024/08/17	   初回作成
			   11/19 10:14 クラス全体の改良

	(C) 2021 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../Singleton/Singleton.hpp"
#include <windows.h>
#include <unordered_map>

/// <summary>
/// フレームレート管理クラス
/// </summary>
class FrameManager : public Singleton<FrameManager>
{
	friend class Singleton<FrameManager>;
public:
	/// <summary>
	/// フレームレート初期化（main）
	/// </summary>
	/// <param name="[In_fFps]">更新するフレーム数</param>
	void Init(float In_fFps);

	/// <summary>
	/// フレームレートの制限（main）
	/// </summary>
	/// <returns>設定したフレーム数を超えていた場合trueを返す</returns>
	bool UpdateMain();

	/// <summary>
	/// 現在時間の取得（main）
	/// </summary>
	/// <returns>現在時間（ms）</returns>
	DWORD GetMainTime();

	/// <summary>
	/// <para>管理するフレームデータの追加</para>
	/// <para>フレームレートはメインのfpsよりも大きな値は設定できない</para>
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <param name="[In_fFps]">フレームレート(1サイクルで処理したいフレーム数)</param>
	/// <param name="[In_nLapTime]">1サイクルにかける時間(デフォルトは1秒)</param>
	void Append(std::string In_strName, float In_fFps, unsigned int In_nLapTime = 1);

	/// <summary>
	/// <para>間隔をあけるフレームデータの追加</para>
	/// <para>指定したフレーム数でtrueとfalseを切り替える</para>
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <param name="[In_fTrueFrame]">trueにするフレーム数</param>
	/// <param name="[In_fIntervalFrame]">falseにするフレーム数</param>
	void AppendInterval(std::string In_strName, float In_fTrueFrame, float In_fIntervalFrame);

	/// <summary>
	/// 指定したフレームデータの更新
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <returns>設定したフレーム数を超えていた場合trueを返す</returns>
	bool Update(std::string In_strName);

	/// <summary>
	/// 指定したフレームデータのカウントをリセット
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	void FrameCountReset(std::string In_strName);

	/// <summary>
	/// 指定したフレームデータの切替回数をリセット
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	void SwitchCountReset(std::string In_strName);

	/// <summary>
	/// 指定したフレームデータのフレームレートの変更
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <param name="[In_fFps]">フレームレート</param>
	/// <param name="[In_nLapTime]">1サイクルにかける時間(デフォルトは1秒)</param>
	void ChangeFps(std::string In_strName, float In_fFps,unsigned int In_nLapTime = 1);

	/// <summary>
	/// <para>指定したフレームデータのTrue-False切替フレーム数の変更</para>
	/// <para>指定するフレーム数に-1を入れた場合はその値は変更しない</para>
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <param name="[In_fTrueFrame]">trueにするフレーム数</param>
	/// <param name="[In_fIntervalFrame]">falseにするフレーム数</param>
	void ChangeIntervalFrame(std::string In_strName, float In_fTrueFrame = -1, float In_fIntervalFrame = -1);

	/// <summary>
	/// 指定したフレームデータが合計で何回TRUEとFALSEを切り替えたかを取得
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	/// <returns>切り替え回数 ※フレームデータが存在しない場合は-1を返す</returns>
	int GetSwitchCount(std::string In_strName);

	/// <summary>
	/// タイムカウンターを追加
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	/// <param name="[In_bIsStartNow]">すぐに計測を開始するか</param>
	void AppendTimeCounter(std::string In_strName, bool In_bIsStartNow = false);

	/// <summary>
	/// タイムカウンターの計測を開始
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	void StartTimeCounter(std::string In_strName);

	/// <summary>
	/// 全てのタイムカウンターの更新
	/// </summary>
	void UpdateAllTimeCounter();

	/// <summary>
	/// タイムカウンターの更新
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	void UpdateTimeCounter(std::string In_strName);

	/// <summary>
	/// 全てのタイムカウンターを止める
	/// </summary>
	void StopAllTimeCounter();

	/// <summary>
	/// タイムカウンターを止める
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	void StopTimeCounter(std::string In_strName);

	/// <summary>
	/// 全てのタイムカウンターをリセット
	/// </summary>
	void ResetAllTimeCounter();

	/// <summary>
	/// タイムカウンターをリセット
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	void ResetTimeCounter(std::string In_strName);

	/// <summary>
	/// タイムカウンターを秒に変換し取得
	/// </summary>
	/// <param name="[In_strName]">カウンター名</param>
	/// <returns>秒</returns>
	float GetTimeCountSecond(std::string In_strName);

	/// <summary>
	/// フレームデータの削除
	/// </summary>
	/// <param name="[In_strName]">フレームデータ名</param>
	void Delete(std::string In_strName);

private:
	FrameManager();
	~FrameManager();

private:
	// メインのフレームデータ
	DWORD m_dwTime;
	DWORD m_dwOldTime;
	float m_fMainFps;
	bool m_bMainExists;

	/// <summary>
	/// フレームデータ構造体
	/// </summary>
	struct FrameData
	{
		int m_nFrameCount;			// フレームのカウント
		int m_nSwitchCount;			// 何回切り替えたか
		unsigned int m_nLapTime;	// 1サイクルにかける時間
		float m_fAdvanceFrame;		// 何メインフレームごとにフレームを進めるか
		float m_fIntervalFrame;		// フレームの間隔
		bool m_bReturn;				// 間隔をあけたサイクルに使う
		bool m_bIsInterval;			// 間隔をあけるかどうか
	};

	struct TimeCountData
	{
		DWORD m_dwCount;			// カウント
		bool m_bIsStart;			// 計測中か

		float m_fTimeSecond; // 秒
		float m_fTimeMinute; // 分
		float m_fTimeHour; // 時
	};

	std::unordered_map<std::string, FrameData> m_mapFrameData;	// フレームデータ
	std::unordered_map<std::string, TimeCountData> m_mapTimeCounter;	// 時間計測用
private:

	/// <summary>
	/// フレームデータの更新(間隔をあけるバージョン)
	/// </summary>
	/// <param name="[In_itr]">更新するフレームデータ</param>
	bool UpdateInterval(std::unordered_map<std::string,FrameData>::iterator In_itr);
};
