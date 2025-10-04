/*+===================================================================
	File: Window.hpp
	Summary: Window�쐬�N���X
	Author: ryuu3160
	Date: 2024/10/16 18:34 ����쐬
		  2025/04/17 15:11 �p�����[�^�[�̐ݒ�֐��̒ǉ��A�擾�֐��̒ǉ��A�R�����g�̒ǉ�
			�@/06/23 11:24 ���t�@�N�^�����O

	(C) 2024 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "Window.hpp"
#include <Windows.h>

// ==============================
//  static�����o�ϐ��̏�����
// ==============================
std::deque<std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> Window::m_CustomProcQueue;

Window::Window()
{
	// ������
	ZeroMemory(&m_wcex, sizeof(m_wcex));
	m_hWnd = NULL;
	m_unWidth = 0;
	m_unHeight = 0;
	m_rcWindowRect = { 0, 0, 0, 0 };
	m_bIsCloseWindow = false;
	m_msgRoop = {};

	// ����̃A�C�R��
	m_hIconInstance = NULL;
	m_lpcIconName = IDI_APPLICATION;
	m_hCursorInstance = NULL;
	m_lpcCursorName = IDC_ARROW;

	// ����̃^�C�g����
	m_lpcTitleName = "DefaultWindowTitle";

	// ����̃N���X��
	m_lpcClassName = "MainWindow";

	// ����̃E�B���h�E����
	m_unStyle = CS_CLASSDC | CS_DBLCLKS;

	// �E�B���h�E�̈ʒu�ƃX�^�C��
	m_dwStyle = WS_CAPTION | WS_SYSMENU;
	m_dwExStyle = WS_EX_OVERLAPPEDWINDOW;
	m_nX = CW_USEDEFAULT;
	m_nY = CW_USEDEFAULT;
	m_Color = WHITE_BRUSH;

	// �e�E�B���h�E�ւ̃n���h��
	m_hWndParent = HWND_DESKTOP;
	// ���j���[�̃n���h��
	m_hMenu = NULL;
	// MDI�N���C�A���g�E�B���h�E�ȂǂŎg�p
	m_lpParam = NULL;
}

Window::~Window()
{
	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass(m_lpcClassName, m_wcex.hInstance);
}

LRESULT CALLBACK Window::m_WndProc(_In_ HWND In_hWnd, _In_ UINT In_unMessage, _In_ WPARAM In_wParam, _In_ LPARAM In_lParam)
{
	for (auto &func : m_CustomProcQueue)
	{
		// �o�^���ꂽ�J�X�^���v���V�[�W�����Ăяo��
		if (func(In_hWnd, In_unMessage, In_wParam, In_lParam))
			return true;
	}

	switch (In_unMessage)
	{
		// x�{�^���������ꂽ�Ƃ��̃��b�Z�[�W
	case WM_CLOSE:
		if (IDNO == MessageBoxA(In_hWnd, "�~�{�^����������܂����B\n�E�B���h�E����܂����H", "Window Close", MB_YESNO))
		{
			return 0;	// WM_CLOSE�̏����������ŏI���
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// ����̃E�B���h�E�v���V�[�W�����Ăяo��
	return DefWindowProc(In_hWnd, In_unMessage, In_wParam, In_lParam);
}

void Window::Create(_In_ LPCTSTR In_lpcTitleName, _In_ UINT In_unWidth, _In_ UINT In_unHeight, _In_ HINSTANCE In_hInstance, _In_ int In_nCmdShow)
{
	// ------------------------------
	//	�E�B���h�E�N���X���̍쐬
	// ------------------------------
	m_wcex.hInstance = In_hInstance;									// �C���X�^���X�n���h��
	m_wcex.lpszClassName = m_lpcClassName;								// �E�B���h�E�N���X��
	m_wcex.lpfnWndProc = m_WndProc;										// �E�B���h�E�v���V�[�W��//�E�B���h�E�v���V�[�W��
	m_wcex.style = m_unStyle;											// �E�B���h�E�̋���// �E�B���h�E�̋���
	m_wcex.cbSize = sizeof(WNDCLASSEX);									// �E�B���h�E�N���X���̃T�C�Y
	m_wcex.hIcon = LoadIcon(m_hIconInstance, m_lpcIconName);			// �A�v���̃A�C�R��// �A�v���̃A�C�R��
	m_wcex.hIconSm = m_wcex.hIcon;										// �^�X�N�o�[�̃A�C�R��
	m_wcex.hCursor = LoadCursor(m_hCursorInstance, m_lpcCursorName);	// �}�E�X�̃A�C�R��// �}�E�X�̃A�C�R��
	m_wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(m_Color));// �w�i�̐F// �w�i�̐F

	// ------------------------------
	//	�E�B���h�E�N���X���̓o�^
	// ------------------------------
	if (!RegisterClassEx(&m_wcex))
	{
		throw std::runtime_error("�E�B���h�E�N���X�̓o�^�Ɏ��s");
		return;
	}

	// ------------------------------
	//  ���̕ۑ�
	// ------------------------------

	m_unWidth = In_unWidth;							// �E�B���h�E�̉�����ۑ�
	m_unHeight = In_unHeight;						// �E�B���h�E�̏c����ۑ�
	m_rcWindowRect = { 0, 0, static_cast<long>(m_unWidth), static_cast<long>(m_unHeight) };	// �E�B���h�E�̋�`��ۑ�
	m_lpcTitleName = In_lpcTitleName;				// �^�C�g���o�[�̕\������ۑ�

	// ------------------------------
	//	�E�B���h�E�̍쐬�E�\��
	// ------------------------------

	// �E�B���h�E�̃T�C�Y�𒲐�
	AdjustWindowRectEx(&m_rcWindowRect, m_dwStyle, false, m_dwExStyle);

	// �E�B���h�E�̍쐬
	m_hWnd = CreateWindowExA(
		m_dwExStyle,								// �g���E�B���h�E�X�^�C��
		m_wcex.lpszClassName,						// �E�B���h�E�N���X��
		m_lpcTitleName,								// �E�B���h�E�̃^�C�g��
		m_dwStyle,									// �E�B���h�E�X�^�C��
		m_nX, m_nY,									// �E�B���h�E�̕\���ʒu
		m_rcWindowRect.right - m_rcWindowRect.left, // �E�B���h�E�̕�
		m_rcWindowRect.bottom - m_rcWindowRect.top,	// �E�B���h�E�̍���
		m_hWndParent,								// �e�E�B���h�E�̃n���h��
		m_hMenu,									// ���j���[�n���h��
		In_hInstance,								// �C���X�^���X�n���h��
		m_lpParam									// CREATESTRUCT�\���̂ւ̃|�C���^
	);

	// �G���[����
	if (m_hWnd == NULL)
	{
		throw std::runtime_error("�E�B���h�E�̍쐬�Ɏ��s");
		return;
	}

	// �E�B���h�E�̕\��
	ShowWindow(m_hWnd, In_nCmdShow);
	UpdateWindow(m_hWnd);
}

void Window::SetWindowPosCenter()
{
	// �E�B���h�E�̋�`���擾
	RECT rc;
	GetWindowRect(m_hWnd, &rc);

	// �E�B���h�E�̈ʒu����ʒ����ɐݒ�
	m_nX = (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2;
	m_nY = (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2;

	// �E�B���h�E�̈ʒu��ݒ�
	SetWindowPos(m_hWnd, NULL, m_nX, m_nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

bool Window::MessageLoop()
{
	if (PeekMessage(&m_msgRoop, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!GetMessage(&m_msgRoop, NULL, 0, 0))
		{
			m_bIsCloseWindow = true;	// �E�B���h�E�����t���O�𗧂Ă�
		}
		else
		{
			TranslateMessage(&m_msgRoop);
			DispatchMessage(&m_msgRoop);
		}

		return false;
	}

	// FPS�̌v��
#ifdef _DEBUG

	++FpsCount;// �����񐔂��J�E���g

	if (timeGetTime() - FpsTime >= 1000)	// 1000ms�o�߂�����
	{
		// �����^���當����֕ϊ�
		std::string mes = m_lpcTitleName;
		mes += " [fps]:" + std::to_string(FpsCount);

		SetWindowTextA(m_hWnd, mes.c_str());	// FPS�̕\��

		// ���̌v���̏���
		FpsCount = 0;
		FpsTime = timeGetTime();
	}
#endif // _DEBUG

	return true;
}

bool Window::IsLoop() const noexcept
{
	return !m_bIsCloseWindow;
}

void Window::SetClassName(_In_ const LPCSTR& In_alpcName)
{
	m_lpcClassName = In_alpcName;
}

void Window::SetParent(_In_ HWND In_hWndParent)
{
	m_hWndParent = In_hWndParent;
}

void Window::SetColor(_In_ const int &In_nColor)
{
	m_Color = In_nColor;
}

void Window::SetIcon(_In_ HINSTANCE& In_ahIns, _In_ LPCTSTR& In_alpcName)
{
	m_hIconInstance = In_ahIns;
	m_lpcIconName = In_alpcName;
}

void Window::SetCursorIcon(_In_ HINSTANCE& In_ahIns, _In_ LPCTSTR& In_alpcName)
{
	m_hCursorInstance = In_ahIns;
	m_lpcCursorName = In_alpcName;
}

void Window::SetStyle(_In_ UINT In_unStyle)
{
	m_unStyle = In_unStyle;
}

void Window::SetWindowStyle(_In_ DWORD In_dwStyle)
{
	m_dwStyle = In_dwStyle;
}

void Window::SetWindowExStyle(_In_ DWORD In_dwExStyle)
{
	m_dwExStyle = In_dwExStyle;
}

void Window::SetMenu(_In_ HMENU In_hMenu)
{
	m_hMenu = In_hMenu;
}

void Window::SetCreateStructParam(_In_ LPCLIENTCREATESTRUCT In_lpParam)
{
	m_lpParam = In_lpParam;
}

void Window::SetCreateStructParam(_In_ LPMDICREATESTRUCT In_lpParam)
{
	m_lpParam = In_lpParam;
}

void Window::AppendFunction(std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> In_Function)
{
	m_CustomProcQueue.push_back(In_Function);
}
