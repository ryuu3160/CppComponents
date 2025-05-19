/*+===================================================================
	File: UnorderedAccessView.hpp
	Summary: wasssk�l�̂��̂��Q�l�ɂ��č쐬
	Author: ryuu3160
	Date: 2025/05/19 Mon PM 04:47:15 ����쐬
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../DX11_Initialize.hpp"

class UnorderedAccessView
{
public:
	UnorderedAccessView();
	~UnorderedAccessView();
	HRESULT Create(UINT stride, UINT num, void *pData = nullptr);

	void Copy();

	ID3D11UnorderedAccessView *GetUAV();
	ID3D11ShaderResourceView *GetSRV();

private:
	ID3D11Buffer *m_pBuffer;
	ID3D11UnorderedAccessView *m_pUAV;
	ID3D11ShaderResourceView *m_pSRV;
};
