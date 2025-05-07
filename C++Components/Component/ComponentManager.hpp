/*+===================================================================
	File: ComponentManager.hpp
	Summary: コンポーネントの管理クラス(追加先)
	Author: ryuu3160
	Date: 2025/5/8 Thu AM 01:15:12 初回作成

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Component.hpp"
#include <list>

/// <summary>
/// ComponentManagerクラス
/// </summary>
class ComponentManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentManager() = default;

	/// <summary>
	/// コンポーネントの追加
	/// </summary>
	/// <param name="[T]">追加するコンポーネントの型</param>
	template<typename T = Component>
	T *AddComponent()
	{
		T *pComponent = new T();
		m_lsComponents.push_back(pComponent);
		// アップキャストでComponentに変換後、初期化処理
		static_cast<Component *>(pComponent)->Init();
		return pComponent;
	}

	template<typename T = Component>
	T *GetComponent()
	{
		for (auto &component : m_lsComponents)
		{
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T *>(component); // ダウンキャストによる型変換
			}
		}
		return nullptr;
	}

protected:
	std::list<Component *> m_lsComponents; // コンポーネントのリスト
};
