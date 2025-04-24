/*+===================================================================
	File: RenderTarget.cpp
	Summary: RenderTarget�N���X�̎����t�@�C��
	Author: AT12C192 01 �ؗY��Y
	Date: 10/19/2024 Sat AM 03:16:28 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/

// ==============================
//	include
// ==============================
#include "RenderTarget.hpp"

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
	m_cpRTV = nullptr;
}

void RenderTarget::Clear()
{
	static float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	Clear(color);
}

void RenderTarget::Clear(const float *In_fColor)
{
	GraphicsDevice::GetInstance().GetDeviceContext()->ClearRenderTargetView(m_cpRTV.Get(), In_fColor);
}

HRESULT RenderTarget::Create(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height)
{
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(In_Format, In_Width, In_Height);
	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	return CreateResource(desc);
}

HRESULT RenderTarget::CreateFromScreen()
{
	HRESULT hr;

	//�o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D *pBackBuffer = nullptr;
	hr = GraphicsDevice::GetInstance().GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&m_cpTex);
	if (FAILED(hr)) { return hr; }

	//�o�b�N�o�b�t�@�ւ̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
	CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.Texture2D.MipSlice = 0;
	hr = GraphicsDevice::GetInstance().GetDevice()->CreateRenderTargetView(m_cpTex.Get(), &rtvDesc, &m_cpRTV);
	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC desc;
		m_cpTex->GetDesc(&desc);
		m_unWidth = desc.Width;
		m_unHeight = desc.Height;
	}
	return hr;
}

ID3D11RenderTargetView *RenderTarget::GetView() const
{
	return m_cpRTV.Get();
}

HRESULT RenderTarget::CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData)
{
	//�e�N�X�`�����\�[�X�쐬
	HRESULT hr = Texture::CreateResource(In_Desc, nullptr);
	if (FAILED(hr)) { return hr; }

	//�ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = In_Desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	
	//����
	return GraphicsDevice::GetInstance().GetDevice()->CreateRenderTargetView(m_cpTex.Get(), &rtvDesc, &m_cpRTV);
}
