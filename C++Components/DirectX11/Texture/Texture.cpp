#include "Texture.hpp"
#include "../DirectXTex/TextureLoad.h"

/// <summary>
/// テクスチャ
/// </summary>
Texture::Texture()
	: m_unWidth(0), m_unHeight(0)
	, m_cpTex(nullptr)
	, m_cpSRV(nullptr)
{
}
Texture::~Texture()
{
	/*SAFE_RELEASE(m_cpSRV);
	SAFE_RELEASE(m_cpTex);*/
}
HRESULT Texture::Create(const char* fileName)
{
	HRESULT hr = S_OK;

	// 文字変換
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;
	MultiByteToWideChar(0, 0, fileName, -1, wPath, MAX_PATH);

	// ファイル別読み込み
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	if (strstr(fileName, ".tga"))
		hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	else
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, &mdata, image);
	if (FAILED(hr)) {
		return E_FAIL;
	}

	// シェーダリソース生成
	hr = CreateShaderResourceView(GraphicsDevice::GetInstance().GetDevice(), image.GetImages(), image.GetImageCount(), mdata, &m_cpSRV);
	if (SUCCEEDED(hr))
	{
		m_unWidth = (UINT)mdata.width;
		m_unHeight = (UINT)mdata.height;
	}
	return hr;
}
HRESULT Texture::Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData)
{
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);
	return CreateResource(desc, pData);
}

UINT Texture::GetWidth() const
{
	return m_unWidth;
}
UINT Texture::GetHeight() const
{
	return m_unHeight;
}
ID3D11ShaderResourceView* Texture::GetResource() const
{
	return m_cpSRV.Get();
}

D3D11_TEXTURE2D_DESC Texture::MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}
HRESULT Texture::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	HRESULT hr = E_FAIL;

	// テクスチャ作成
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = pData;
	data.SysMemPitch = desc.Width * 4;
	hr = GraphicsDevice::GetInstance().GetDevice()->CreateTexture2D(&desc, pData ? &data : nullptr, &m_cpTex);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	switch (desc.Format)
	{
	default:						srvDesc.Format = desc.Format;			break;
	case DXGI_FORMAT_R32_TYPELESS: 	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;	break;
	}
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// 生成
	hr = GraphicsDevice::GetInstance().GetDevice()->CreateShaderResourceView(m_cpTex.Get(), &srvDesc, &m_cpSRV);
	if (SUCCEEDED(hr))
	{
		m_unWidth = desc.Width;
		m_unHeight = desc.Height;
	}
	return hr;
}