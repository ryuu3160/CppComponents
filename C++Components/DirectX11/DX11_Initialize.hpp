/*+===================================================================
	File: DX11_Initialize.hpp
	Summary: DirectX11�̏������N���X
	Author: AT12C192 01 �ؗY��Y
	Date: 10/19/2024 Sat AM 12:32:59 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
===================================================================+*/
#pragma once
// ==============================
//	include
// ==============================
#include <dxgidebug.h>
#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <DirectXMath.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "../WindowGenerator/Window.hpp"
#include "../Singleton/Singleton.hpp"

// COM
#include <wrl/client.h>
#include <initguid.h>
using Microsoft::WRL::ComPtr;

// ==============================
//  �}�N��
// ==============================
#define SAFE_RELEASE(ptr) { if(ptr){ptr->Release(); ptr = nullptr;}}

// ==============================
//	�O���錾
// ==============================
class RenderTarget;
class DepthStencil;

// ==============================
//	�񋓌^��`
// ==============================

/// <summary>
/// �u�����h���[�h
/// </summary>
enum BlendMode
{
	BLEND_NONE,
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_ADDALPHA,
	BLEND_SUB,
	BLEND_SCREEN,
	BLEND_MAX
};

/// <summary>
/// �T���v���[�X�e�[�g
/// </summary>
enum SamplerState
{
	SAMPLER_LINEAR,
	SAMPLER_POINT,
	SAMPLER_MAX
};

/// <summary>
/// DirectX�������N���X
/// </summary>
class DX11_Initialize : public Singleton<DX11_Initialize>
{
	friend class Singleton;
public:
	/// <summary>
	/// DirectX����������
	/// </summary>
	/// <returns>FAILED�}�N���Ŕ���</returns>
	HRESULT Init();
	/// <summary>
	/// DirectX�I������
	/// </summary>
	void Uninit();
	/// <summary>
	/// �`��J�n����
	/// </summary>
	void BeginDraw();
	/// <summary>
	/// �`��I������
	/// </summary>
	void EndDraw();

	/// <summary>
	/// ID3D11Device���擾����
	/// </summary>
	/// <returns>ID3D11Device�ւ̃|�C���^�[</returns>
	ID3D11Device* GetDevice();
	/// <summary>
	/// ID3D11DeviceContext���擾����
	/// </summary>
	/// <returns>ID3D11DeviceContext�ւ̃|�C���^�[</returns>
	ID3D11DeviceContext* GetDeviceContext();
	/// <summary>
	/// IDXGISwapChain���擾����
	/// </summary>
	/// <returns>IDXGISwapChain�ւ̃|�C���^�[</returns>
	IDXGISwapChain *GetSwapChain();
	/// <summary>
	/// �f�t�H���g��RenderTarget���擾����
	/// </summary>
	/// <returns>RanderTarget�ւ̃|�C���^</returns>
	RenderTarget *GetDefaultRTV();
	/// <summary>
	/// �f�t�H���g��DepthStencil���擾����
	/// </summary>
	/// <returns>DepthStencil�ւ̃|�C���^</returns>
	DepthStencil *GetDefaultDSV();
	/// <summary>
	/// �����擾����
	/// </summary>
	/// <returns>UINT�^</returns>
	UINT GetWidth() const;
	/// <summary>
	/// �������擾����
	/// </summary>
	/// <returns>UINT�^</returns>
	UINT GetHeight() const;

	/// <summary>
	/// WindowColor���Z�b�g����
	/// </summary>
	/// <param name="[In_fR]">���b�h</param>
	/// <param name="[In_fG]">�O���[��</param>
	/// <param name="[In_fB]">�u���[</param>
	/// <param name="[In_fA]">���ߓx</param>
	void SetWindowColor(float In_fR, float In_fG, float In_fB, float In_fA);

	/// <summary>
	/// WindowColor���Z�b�g����
	/// </summary>
	/// <param name="[In_vecRgba]">vector�^�̔z�񁦗v�f����4����</param>
	void SetWindowColor(const std::vector<float>&In_vecRgba);
	/// <summary>
	/// WindowColor�̃��b�h�̒l���Z�b�g����
	/// </summary>
	/// <param name="[In_fR]">���b�h</param>
	void SetWindowColor_R(float In_fR);
	/// <summary>
	/// WindowColor�̃O���[���̒l���Z�b�g����
	/// </summary>
	/// <param nameIn_fGg]">�O���[��</param>
	void SetWindowColor_G(float In_fG);
	/// <summary>
	/// WindowColor�̃u���[�̒l���Z�b�g����
	/// </summary>
	/// <param name="[In_fB]">�u���[</param>
	void SetWindowColor_B(float In_fB);
	/// <summary>
	/// WindowColor�̓��ߓx�̒l���Z�b�g����
	/// </summary>
	/// <param name="[In_fA]">���ߓx</param>
	void SetWindowColor_A(float In_fA);

	/// <summary>
	/// fps�l��ύX
	/// </summary>
	/// <param name="[In_unNum]">fps�l</param>
	void _SetRefreshRate_Numerator(UINT In_unNum);
	/// <summary>
	/// fps�̕���l��ύX
	/// </summary>
	/// <param name="[In_unNum]">fps�̕���l</param>
	void _SetRefreshRate_Denominator(UINT In_unNum);
	/// <summary>
	/// �}���`�T���v������ύX
	/// </summary>
	/// <param name="[In_unCount]">�T���v����</param>
	void _SetSampleDesc_Count(UINT In_unCount);
	/// <summary>
	/// �t���[���o�b�t�@�̐F���(�e8bit)��ύX
	/// </summary>
	/// <param name="[In_dxgiFormat]">�F���</param>
	void _SetFormat(DXGI_FORMAT In_dxgiFormat);
	/// <summary>
	/// �o�b�t�@�̎g�p���@��ύX
	/// </summary>
	/// <param name="[In_dxgiBufferUsage]">�g�p���@</param>
	void _SetBufferUsage(DXGI_USAGE In_dxgiBufferUsage);
	/// <summary>
	/// �o�b�N�o�b�t�@���̕ύX
	/// </summary>
	/// <param name="[In_unBufferCount]">�J�E���g</param>
	void _SetBufferCount(UINT In_unBufferCount);
	/// <summary>
	/// �t���X�N���[���̉ۂ�ύX
	/// </summary>
	/// <param name="[In_bFullScreen]">true or false</param>
	void _SetFullScreen(bool In_bFullScreen);
	/// <summary>
	/// �t���O�̐ݒ�
	/// </summary>
	/// <param name="[In_unFlags]">�t���O</param>
	void _SetFlags(UINT In_unFlags);

	/// <summary>
	/// LiveDeviceObjects�̃f�o�b�O�o��
	/// </summary>
	void DebugOutput_LiveDeviceObjects();
	/// <summary>
	/// LiveObjects�̃f�o�b�O�o��
	/// </summary>
	void DebugOutput_LiveObjects();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̐ݒ�
	/// </summary>
	/// <param name="[In_unNum]">�ݒ萔</param>
	/// <param name="[In_rtppViews]">RenderTarget�N���X�ւ̃|�C���^�[</param>
	/// <param name="[In_dspView]">DepthStencil�N���X�ւ̃|�C���^�[</param>
	void SetRenderTargets(UINT In_unNum, RenderTarget **In_rtppViews, DepthStencil *In_dspView);
	/// <summary>
	/// CullingMode�̐ݒ�
	/// </summary>
	/// <param name="[In_cull]">���[�h</param>
	void SetCullingMode(D3D11_CULL_MODE In_cull);
	/// <summary>
	/// DepthTest�̐ݒ�
	/// </summary>
	/// <param name="[In_Enable]">�L���ɂ��邩�ۂ�</param>
	void SetDepthTest(bool In_Enable);
	/// <summary>
	/// BlendMode�̐ݒ�
	/// </summary>
	/// <param name="[In_Blend]">���[�h</param>
	void SetBlendMode(BlendMode In_Blend);
	/// <summary>
	/// SamplerState�̐ݒ�
	/// </summary>
	/// <param name="[In_State]">SamplerState</param>
	void SetSamplerState(SamplerState In_State);

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DX11_Initialize();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DX11_Initialize() override;

private:
	ComPtr<IDXGIFactory> m_cpFactory;							//�t�@�N�g���[
	ComPtr<ID3D11Device> m_cpDevice;							//DirectX�ŃA�Z�b�g�̍쐬���s���@�\
	ID3D11Debug *m_pDebug1;										//�f�o�b�O�@�\(LiveDeviceObjects�p)
	IDXGIDebug *m_pDebug2;										//�f�o�b�O�@�\(LiveObjects�p)
	ComPtr<ID3D11DeviceContext> m_cpContext;					//DirectX�ŕ`�施�߂𔭍s����@�\
	ComPtr<IDXGISwapChain> m_cpSwapChain;						//�t���[���o�b�t�@�ƃf�B�X�v���C�̋��n��
	ComPtr<ID3D11RasterizerState> m_cpRasterizerState[3];		//���X�^���C�U�X�e�[�g
	ComPtr<ID3D11BlendState> m_cpBlendState[BLEND_MAX];			// �u�����h�X�e�[�g
	ComPtr<ID3D11SamplerState> m_cpSamplerState[SAMPLER_MAX];	//�e�N�X�`���̃T���v�����O���@��ݒ肷��

	RenderTarget *m_pRT; //�����_�[�^�[�Q�b�g�N���X�̃|�C���^
	DepthStencil *m_pDS; //�f�v�X�X�e���V���N���X�̃|�C���^

	HRESULT m_hr;	// �G���[�`�F�b�N�p

	//�p�����[�^�[
	UINT m_Width;						// �t���[���o�b�t�@�̕�
	UINT m_Height;						// �t���[���o�b�t�@�̍���
	UINT m_RefreshRate_Numerator;		// fps(���q)
	UINT m_RefreshRate_Denominator;		// fps(����)
	UINT m_SampleDesc_Count;			// �}���`�T���v�����O�̐�
	UINT m_SampleDesc_Quality;			// �}���`�T���v�����O�̕i��
	UINT m_BufferCount;					// �o�b�N�o�b�t�@�̐�
	UINT m_Flags;
	DXGI_FORMAT m_Format;				// �t���[���o�b�t�@�̐F���(�e8bit)
	DXGI_USAGE m_BufferUsage;
	bool m_FullScreen;					// �t���X�N���[���ɂ��邩�̔���

	//�h���C�o�̎��
	D3D_DRIVER_TYPE m_DriverType;
	D3D_DRIVER_TYPE m_DriverTypes[3];	// �����l�͎g�p�ґ��Ŏw�肵�Ȃ�
	UINT m_nuDriverTypes;
	//�@�\���x��
	D3D_FEATURE_LEVEL m_FeatureLevel;
	D3D_FEATURE_LEVEL m_FeatureLevels[7];	// �����l�͎g�p�ґ��Ŏw�肵�Ȃ�
	UINT m_nuFeatureLevels;
	UINT m_nuCreateDeviceFlags;

	//�E�B���h�E�̐F���
	float m_WindowColor[4];	// �w�i�F
	float m_BlendFactor[4];
};