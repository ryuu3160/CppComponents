/*+===================================================================
	File: RenderTarget.hpp
	Summary: RenderTarget�N���X�̃w�b�_�[�t�@�C��
	Author: AT12C192 01 �ؗY��Y
	Date: 10/19/2024 Sat AM 03:16:11 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Texture.hpp"

/// <summary>
/// RenderTarget�N���X
/// </summary>
class RenderTarget : public Texture
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RenderTarget();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RenderTarget() override;

	/// <summary>
	/// RTV�̃N���A
	/// </summary>
	void Clear();
	/// <summary>
	/// RTV�̃N���A
	/// </summary>
	/// <param name="[In_fColor]">�J���[�z��̃|�C���^</param>
	void Clear(const float *In_fColor);

	/// <summary>
	/// RTV�̍쐬
	/// </summary>
	/// <param name="[In_Format]">�t�H�[�}�b�g</param>
	/// <param name="[In_Width]">��</param>
	/// <param name="[In_Height]">����</param>
	/// <returns>�������Ă�����S_OK</returns>
	HRESULT Create(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height);

	/// <summary>
	/// �o�b�N�o�b�t�@�[����RTV���쐬
	/// </summary>
	/// <returns>�������Ă�����S_OK</returns>
	HRESULT CreateFromScreen();

	/// <summary>
	/// RTV�̎擾
	/// </summary>
	/// <returns>RTV�̃A�h���X</returns>
	ID3D11RenderTargetView *GetView() const;

protected:
	/// <summary>
	/// ���\�[�X�쐬�y��RTV�̍쐬
	/// </summary>
	/// <param name="[In_Desc]">�e�N�X�`�����</param>
	/// <param name="[In_pData]">�e�N�X�`���f�[�^�̃|�C���^</param>
	/// <returns>�������Ă�����S_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData = nullptr);

private:
	ComPtr<ID3D11RenderTargetView> m_cpRTV; // �����_�[�^�[�Q�b�g�r���[
};
