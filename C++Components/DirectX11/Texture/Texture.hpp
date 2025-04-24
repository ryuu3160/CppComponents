/*+===================================================================
	File: Texture.hpp
	Summary: �i���̃t�@�C���ŉ������邩�L�ڂ���j
	Author: AT12X999 99 ����
	Date: 10/19/2024 Sat AM 01:20:06 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../DX11_Initialize.hpp"

/// <summary>
/// Texture�N���X
/// </summary>
class Texture
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Texture();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Texture();

	/// <summary>
	/// �e�N�X�`���̓ǂݍ���
	/// </summary>
	/// <param name="[In_FilePath]">�p�X��</param>
	/// <returns>�������Ă�����S_OK</returns>
	HRESULT Create(const char *In_FilePath);

	/// <summary>
	/// �e�N�X�`���̍쐬
	/// </summary>
	/// <param name="[In_Format]">�t�H�[�}�b�g</param>
	/// <param name="[In_Width]">��</param>
	/// <param name="[In_Height]">����</param>
	/// <param name="[In_pData]">�e�N�X�`���f�[�^�̃|�C���^</param>
	/// <returns></returns>
	HRESULT Create(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height, const void *In_pData = nullptr);

	/// <summary>
	/// �e�N�X�`���̕��擾
	/// </summary>
	/// <returns>��</returns>
	UINT GetWidth() const;
	/// <summary>
	/// �e�N�X�`���̍����擾
	/// </summary>
	/// <returns>����</returns>
	UINT GetHeight() const;
	/// <summary>
	/// �V�F�[�_�[���\�[�X�r���[�擾
	/// </summary>
	/// <returns>SRV</returns>
	ID3D11ShaderResourceView *GetResource() const;

protected:
	/// <summary>
	/// �e�N�X�`���̏��ݒ�
	/// </summary>
	/// <param name="[In_Format]">�t�H�[�}�b�g</param>
	/// <param name="[In_Width]">��</param>
	/// <param name="[In_Height]">����</param>
	/// <returns>�e�N�X�`�����̍\����</returns>
	D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT In_Format, UINT In_Width, UINT In_Height);
	/// <summary>
	/// ���\�[�X�쐬
	/// </summary>
	/// <param name="[In_Desc]">�e�N�X�`�����</param>
	/// <param name="[In_pData]">�e�N�X�`���f�[�^�̃|�C���^</param>
	/// <returns>�������Ă�����S_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData);

protected:
	UINT m_unWidth; // ����
	UINT m_unHeight; // �c��
	ComPtr<ID3D11ShaderResourceView> m_cpSRV; // �V�F�[�_���\�[�X�r���[
	ComPtr<ID3D11Texture2D> m_cpTex; // �e�N�X�`��
};
