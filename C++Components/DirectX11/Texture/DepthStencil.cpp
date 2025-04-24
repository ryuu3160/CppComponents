/*+===================================================================
	File: DepthStencil.cpp
	Summary: �[�x�e�N�X�`���N���X�̃\�[�X�t�@�C��
	Author: AT12C192 01 �ؗY��Y
	Date: 10/19/2024 Sat AM 03:58:41 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/

// ==============================
//	include
// ==============================
#include "DepthStencil.hpp"

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
	m_cpDSV = nullptr;
}

void DepthStencil::Clear()
{
	GraphicsDevice::GetInstance().GetDeviceContext()->ClearDepthStencilView(m_cpDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

HRESULT DepthStencil::Create(UINT In_Width, UINT In_Height, bool In_bUseStencil)
{
	// https://docs.microsoft.com/ja-jp/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil#compositing
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(In_bUseStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS, In_Width, In_Height);
	desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	return CreateResource(desc);
}

ID3D11DepthStencilView *DepthStencil::GetView() const
{
	return m_cpDSV.Get();
}

HRESULT DepthStencil::CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData)
{
	//�X�e���V���g�p����
	bool bUseStencil = (In_Desc.Format == DXGI_FORMAT_R24G8_TYPELESS);

	//���\�[�X����
	In_Desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	HRESULT hr = Texture::CreateResource(In_Desc, nullptr);
	if (FAILED(hr)) { return hr; }

	//�ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = bUseStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	//����
	return GraphicsDevice::GetInstance().GetDevice()->CreateDepthStencilView(m_cpTex.Get(), &dsvDesc, &m_cpDSV);
}
