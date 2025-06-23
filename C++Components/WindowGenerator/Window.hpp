/*+===================================================================
	File: Window.hpp
	Summary: Window�쐬�N���X
	Author: ryuu3160
	Date: 2024/10/16 18:34 ����쐬
		  2025/04/17 15:11 �p�����[�^�[�̐ݒ�֐��̒ǉ��A�擾�֐��̒ǉ��A�R�����g�̒ǉ�

	(C) 2024 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <Windows.h>
#include "../Singleton/Singleton.hpp"

// �����o�֐���GetClassName�����邽�߁A�}�N���𖳌���
#undef GetClassName

/// <summary>
/// �E�B���h�E�쐬�N���X
/// </summary>
class Window : public Singleton<Window>
{
	friend class Singleton<Window>;
public:
	/// <summary>
	/// �E�B���h�E�v���V�[�W���[
	/// </summary>
	/// <param name="[In_hWnd]">�E�B���h�E�̃n���h��</param>
	/// <param name="[In_unMessage]">���b�Z�[�W</param>
	/// <param name="[In_wParam]">�ǉ��̃��b�Z�[�W</param>
	/// <param name="[In_lParam]">�ǉ��̃��b�Z�[�W</param>
	/// <returns>����</returns>
	static LRESULT CALLBACK m_WndProc(_In_ HWND In_hWnd, _In_ UINT In_unMessage, _In_ WPARAM In_wParam, _In_ LPARAM In_lParam);

	/// <summary>
	/// �E�B���h�E�̍쐬
	/// </summary>
	/// <param name="[In_lpcTitleName]">�^�C�g���o�[�̕\����</param>
	/// <param name="[In_nWidth]">�E�B���h�E�̉���</param>
	/// <param name="[In_nHeight]">�E�B���h�E�̏c��</param>
	/// <param name="[In_hInstance]">WinMain�̈����ɂ���C���X�^���X�n���h��</param>
	/// <param name="[In_nCmdShow]">�E�B���h�E�̕\�����@</param>
	void Create(_In_ LPCTSTR In_lpcTitleName, _In_ UINT In_unWidth, UINT In_unHeight, _In_ HINSTANCE In_hInstance, _In_ int In_nCmdShow = SW_SHOWDEFAULT);

	/// <summary>
	/// �E�B���h�E����ʒ����Ɉړ�
	/// </summary>
	void SetWindowPosCenter();

	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	/// <returns>�E�B���h�E�n���h��</returns>
	inline HWND& GetHwnd() noexcept;
	/// <summary>
	/// �E�B���h�E�̉������擾
	/// </summary>
	/// <returns>����(UINT�^)</returns>
	inline UINT GetWidth() const noexcept;
	/// <summary>
	/// �E�B���h�E�̏c�����擾
	/// </summary>
	/// <returns>�c��(UINT�^)</returns>
	inline UINT GetHeight() const noexcept;

	/// <summary>
	/// �^�C�g���o�[�̕\�������擾
	/// </summary>
	/// <returns>�^�C�g���o�[�̕\����</returns>
	inline LPCSTR GetTitleName() const noexcept;

	/// <summary>
	/// �E�B���h�E�N���X���̎擾
	/// </summary>
	/// <returns>�E�B���h�E�N���X��</returns>
	inline LPCSTR GetClassName() const noexcept;

	/// <summary>
	/// �e�E�B���h�E�̃n���h�����擾
	/// </summary>
	/// <returns>�e�E�B���h�E�̃n���h��</returns>
	inline HWND &GetParentHwnd() noexcept;

	/// <summary>
	/// �N���X�l�[���̐ݒ�
	/// </summary>
	/// <param name="[In_alpcName]">�N���X��</param>
	void SetClassName(_In_ const LPCSTR& In_alpcName);

	/// <summary>
	/// �e�E�B���h�E�̐ݒ�
	/// </summary>
	/// <param name="[In_hWndParent]">�e�E�B���h�E�ւ̃n���h��</param>
	void SetParent(_In_ HWND In_hWndParent = HWND_DESKTOP);

	/// <summary>
	/// �E�B���h�E�J���[�̐ݒ�
	/// </summary>
	/// <param name="[In_nColor]">�F�p�����[�^</param>
	void SetColor(_In_ const int &In_nColor = WHITE_BRUSH);
	/// <summary>
	/// �A�C�R���̐ݒ�
	/// </summary>
	/// <param name="[In_ahIns]">HINSTANCE�ւ̎Q��</param>
	/// <param name="[In_alpcName]">LPCTSTR�ւ̎Q��</param>
	void SetIcon(_In_ HINSTANCE& In_ahIns, _In_ LPCTSTR& In_alpcName);
	/// <summary>
	/// �J�[�\���A�C�R���̐ݒ�
	/// </summary>
	/// <param name="[In_ahIns]">HINSTANCE�ւ̎Q��</param>
	/// <param name="[In_alpcName]">LPCTSTR�ւ̎Q��</param>
	void SetCursorIcon(_In_ HINSTANCE& In_ahIns, _In_ LPCTSTR& In_alpcName);
	/// <summary>
	/// �E�B���h�E�����̐ݒ�
	/// </summary>
	/// <param name="[In_unStyle]">UINT�^</param>
	void SetStyle(_In_ UINT In_unStyle);

	/// <summary>
	/// �E�B���h�E�X�^�C���̐ݒ�
	/// </summary>
	/// <param name="[In_dwStyle]">�E�B���h�E�X�^�C���l�ƃR���g���[���X�^�C���̑g�ݍ��킹</param>
	void SetWindowStyle(_In_ DWORD In_dwStyle = WS_CAPTION | WS_SYSMENU);

	/// <summary>
	/// �g���E�B���h�E�X�^�C���̐ݒ�
	/// </summary>
	/// <param name="[In_dwExStyle]">�g���E�B���h�E�X�^�C��</param>
	void SetWindowExStyle(_In_ DWORD In_dwExStyle = WS_EX_OVERLAPPEDWINDOW);

	/// <summary>
	/// ���j���[�̃n���h�����͎q�E�B���h�E���ʎq�̐ݒ�
	/// </summary>
	/// <param name="[In_hMenu]">HMENU</param>
	void SetMenu(_In_ HMENU In_hMenu = NULL);

	/// <summary>
	/// MDI�N���C�A���g�E�B���h�E���쐬����Ƃ��Ɏg�p
	/// </summary>
	/// <param name="[lpParam]">CLIENTCREATESTRUCT�ւ̃|�C���^</param>
	void SetCreateStructParam(_In_ LPCLIENTCREATESTRUCT In_lpParam);

	/// <summary>
	/// MDI�q�E�B���h�E���쐬����Ƃ��Ɏg�p
	/// </summary>
	/// <param name="[lpParam]">MDICREATESTRUCT�ւ̃|�C���^</param>
	void SetCreateStructParam(_In_ LPMDICREATESTRUCT In_lpParam);

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Window();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Window() override;

private:
	WNDCLASSEX m_wcex;		//�E�B���h�E�N���X���
	HWND m_hWnd;			//�E�B���h�E�n���h��
	UINT m_unWidth;			//�E�B���h�E�̉���
	UINT m_unHeight;			//�E�B���h�E�̏c��
	RECT m_rcWindowRect;	//�E�B���h�E�̋�`

	LPCSTR m_lpcTitleName;	// �^�C�g���o�[�̕\����

	// �A�C�R��
	HINSTANCE m_hIconInstance;
	LPCTSTR m_lpcIconName;

	// �J�[�\���A�C�R��
	HINSTANCE m_hCursorInstance;
	LPCTSTR m_lpcCursorName;
	
	UINT m_unStyle;			// �E�B���h�E����
	LPCSTR m_lpcClassName;	// �E�B���h�E�����ʂ��邽�߂̃N���X��

	// �E�B���h�E�̃X�^�C��
	DWORD m_dwStyle;
	DWORD m_dwExStyle;
	// �E�B���h�E�̈ʒu
	int m_nX;
	int m_nY;

	int m_Color;	// �E�B���h�E�J���[

	HWND m_hWndParent; // �e�E�B���h�E�ւ̃n���h��

	// ���j���[�̃n���h���A���́A�E�B���h�E�̃X�^�C���ɉ����Ďq�E�B���h�E���ʎq���w�肷��
	// �d�Ȃ����E�B���h�E���̓|�b�v�A�b�v�E�B���h�E�̏ꍇ�A�E�B���h�E�Ŏg�p���郁�j���[�����ʂ���
	// �N���X���j���[���g�p����ꍇ�́ANULL���w��ł���
	// �q�E�B���h�E�̏ꍇ�A�q�E�B���h�E���ʎq�����w��
	// �A�v���P�[�V�����́A�q�E�B���h�E���ʎq�����肷��
	// �����e�E�B���h�E�������ׂĂ̎q�E�B���h�E�ň�ӂł���K�v������
	// ��:�C�x���g�ɂ��Đe�ɒʒm���邽�߂Ƀ_�C�A���O �{�b�N�X �R���g���[���ɂ���Ďg�p����鐮���l
	HMENU m_hMenu;

	// MDI�N���C�A���g�E�B���h�E�A����MDI�q�E�B���h�E���쐬����Ƃ��Ɏg�p
	// ������w�肵�Ȃ��ꍇ��NULL���w�肷��
	// ���̃��b�Z�[�W�́A�߂�O�ɁA���̊֐��ɂ���č쐬���ꂽ�E�B���h�E�ɑ��M�����
	LPVOID m_lpParam;
};