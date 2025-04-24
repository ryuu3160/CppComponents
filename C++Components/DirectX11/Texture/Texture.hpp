/*+===================================================================
	File: Texture.hpp
	Summary: （このファイルで何をするか記載する）
	Author: AT12X999 99 氏名
	Date: 10/19/2024 Sat AM 01:20:06 初回作成
	（これ以降下に更新日時と更新内容を書く）
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../DX11_Initialize.hpp"

/// <summary>
/// Textureクラス
/// </summary>
class Texture
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Texture();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Texture();

	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="[In_FilePath]">パス名</param>
	/// <returns>成功していたらS_OK</returns>
	HRESULT Create(const char *In_FilePath);

	/// <summary>
	/// テクスチャの作成
	/// </summary>
	/// <param name="[In_Format]">フォーマット</param>
	/// <param name="[In_Width]">幅</param>
	/// <param name="[In_Height]">高さ</param>
	/// <param name="[In_pData]">テクスチャデータのポインタ</param>
	/// <returns></returns>
	HRESULT Create(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height, const void *In_pData = nullptr);

	/// <summary>
	/// テクスチャの幅取得
	/// </summary>
	/// <returns>幅</returns>
	UINT GetWidth() const;
	/// <summary>
	/// テクスチャの高さ取得
	/// </summary>
	/// <returns>高さ</returns>
	UINT GetHeight() const;
	/// <summary>
	/// シェーダーリソースビュー取得
	/// </summary>
	/// <returns>SRV</returns>
	ID3D11ShaderResourceView *GetResource() const;

protected:
	/// <summary>
	/// テクスチャの情報設定
	/// </summary>
	/// <param name="[In_Format]">フォーマット</param>
	/// <param name="[In_Width]">幅</param>
	/// <param name="[In_Height]">高さ</param>
	/// <returns>テクスチャ情報の構造体</returns>
	D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height);
	/// <summary>
	/// リソース作成
	/// </summary>
	/// <param name="[In_Desc]">テクスチャ情報</param>
	/// <param name="[In_pData]">テクスチャデータのポインタ</param>
	/// <returns>成功していたらS_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData);

protected:
	UINT m_unWidth; // 横幅
	UINT m_unHeight; // 縦幅
	ComPtr<ID3D11ShaderResourceView> m_cpSRV; // シェーダリソースビュー
	ComPtr<ID3D11Texture2D> m_cpTex; // テクスチャ
};
