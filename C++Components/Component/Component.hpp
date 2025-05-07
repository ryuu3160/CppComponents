/*+===================================================================
	File: Component.hpp
	Summary: コンポーネントの基底クラス
	Author: ryuu3160
	Date: 2025/5/8 Thu AM 01:15:39 初回作成

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================


/// <summary>
/// Componentクラス
/// </summary>
class Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Component() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Component();

	virtual void Init();
	virtual void Uninit();

private:

};
