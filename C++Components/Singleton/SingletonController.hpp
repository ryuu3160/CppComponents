/*+===================================================================
    File: SingletonController.hpp
    Summary: 自作シングルトン
    Author: AT12C192 01 青木雄一郎
    Date: 2024/08/16   初回作成

    (C) 2024 Yuichiro Aoki. All Rights Reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <mutex>
#include <vector>
#include <algorithm>

class SingletonController final
{
public:
    using ControllerFunc = void(*)();   // 関数ポインタ

    /// <summary>
    /// シングルトンクラスの解放処理を追加
    /// </summary>
    /// <param name="[func]">destroy関数のポインタ</param>
    static void addController(ControllerFunc func);

    /// <summary>
    /// 全てのシングルトンクラスの解放処理を呼び出す
    /// </summary>
    static void release();
};