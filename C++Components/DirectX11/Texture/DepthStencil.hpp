/*+===================================================================
	File: DepthStencil.hpp
	Summary: 深度テクスチャクラスのヘッダーファイル
	Author: AT12C192 01 青木雄一郎
	Date: 10/19/2024 Sat AM 03:57:52 初回作成
	（これ以降下に更新日時と更新内容を書く）
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Texture.hpp"

/// <summary>
/// DepthStencilクラス
/// </summary>
class DepthStencil : public Texture
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DepthStencil();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DepthStencil() override;

	/// <summary>
	/// DPSVをクリア
	/// </summary>
	void Clear();

	/// <summary>
	/// DPSVを作成
	/// </summary>
	/// <param name="[In_Width]">幅</param>
	/// <param name="[In_Height]">高さ</param>
	/// <param name="[In_bUseStencil]">ステンシルバッファを使用するならtrue</param>
	/// <returns>成功していたらture</returns>
	HRESULT Create(UINT In_Width, UINT In_Height, bool In_bUseStencil);

	/// <summary>
	/// DPSVを取得
	/// </summary>
	/// <returns>DPSVのアドレス</returns>
	ID3D11DepthStencilView *GetView() const;

protected:
	/// <summary>
	/// リソース作成及びDPSVの作成
	/// </summary>
	/// <param name="[In_Desc]">テクスチャ情報</param>
	/// <param name="[In_pData]">テクスチャデータのポインタ</param>
	/// <returns>成功していたらS_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData = nullptr);

private:
	ComPtr<ID3D11DepthStencilView> m_cpDSV; // 深度ステンシルビュー
};
