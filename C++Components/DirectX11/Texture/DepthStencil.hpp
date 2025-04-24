/*+===================================================================
	File: DepthStencil.hpp
	Summary: �[�x�e�N�X�`���N���X�̃w�b�_�[�t�@�C��
	Author: AT12C192 01 �ؗY��Y
	Date: 10/19/2024 Sat AM 03:57:52 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Texture.hpp"

/// <summary>
/// DepthStencil�N���X
/// </summary>
class DepthStencil : public Texture
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DepthStencil();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DepthStencil() override;

	/// <summary>
	/// DPSV���N���A
	/// </summary>
	void Clear();

	/// <summary>
	/// DPSV���쐬
	/// </summary>
	/// <param name="[In_Width]">��</param>
	/// <param name="[In_Height]">����</param>
	/// <param name="[In_bUseStencil]">�X�e���V���o�b�t�@���g�p����Ȃ�true</param>
	/// <returns>�������Ă�����ture</returns>
	HRESULT Create(UINT In_Width, UINT In_Height, bool In_bUseStencil);

	/// <summary>
	/// DPSV���擾
	/// </summary>
	/// <returns>DPSV�̃A�h���X</returns>
	ID3D11DepthStencilView *GetView() const;

protected:
	/// <summary>
	/// ���\�[�X�쐬�y��DPSV�̍쐬
	/// </summary>
	/// <param name="[In_Desc]">�e�N�X�`�����</param>
	/// <param name="[In_pData]">�e�N�X�`���f�[�^�̃|�C���^</param>
	/// <returns>�������Ă�����S_OK</returns>
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &In_Desc, const void *In_pData = nullptr);

private:
	ComPtr<ID3D11DepthStencilView> m_cpDSV; // �[�x�X�e���V���r���[
};
