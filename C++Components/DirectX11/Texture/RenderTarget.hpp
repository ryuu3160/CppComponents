/*+===================================================================
	File: RenderTarget.hpp
	Summary: RenderTargetクラスのヘッダーファイル
	Author: AT12C192 01 青木雄一郎
	Date: 10/19/2024 Sat AM 03:16:11 初回作成
	（これ以降下に更新日時と更新内容を書く）
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Texture.hpp"

/// <summary>
/// RenderTargetクラス
/// </summary>
class RenderTarget : public Texture
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RenderTarget();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RenderTarget() override;

	/// <summary>
	/// RTVのクリア
	/// </summary>
	void Clear();
	/// <summary>
	/// RTVのクリア
	/// </summary>
	/// <param name="[In_fColor]">カラー配列のポインタ</param>
	void Clear(const float *In_fColor);

	/// <summary>
	/// RTVの作成
	/// </summary>
	/// <param name="[In_Format]">フォーマット</param>
	/// <param name="[In_Width]">幅</param>
	/// <param name="[In_Height]">高さ</param>
	/// <returns>成功していたらS_OK</returns>
	HRESULT Create(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height);

	/// <summary>
	/// バックバッファーからRTVを作成
	/// </summary>
	/// <returns>成功していたらS_OK</returns>
	HRESULT CreateFromScreen();

	/// <summary>
	/// RTVの取得
	/// </summary>
	/// <returns>RTVのアドレス</returns>
	ID3D11RenderTargetView *GetView() const;

protected:
	/// <summary>
	/// リソース作成及びRTVの作成
	/// </summary>
	/// <param name="[In_Desc]">テクスチャ情報</param>
	/// <param name="[In_pData]">テクスチャデータのポインタ</param>
	/// <returns>成功していたらS_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData = nullptr);

private:
	ComPtr<ID3D11RenderTargetView> m_cpRTV; // レンダーターゲットビュー
};
