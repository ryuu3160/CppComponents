/*+===================================================================
	File: IME.hpp
	Summary: IME����p�N���X
	Author: ryuu3160
	Date: 2025/01/29 16:38 ����쐬
				 /30 12:30 ���͗p�̊֐��Ȃǒǉ�
			  /02/06 06:30 ���{����͑Ή�,�E�B���h�E�v���V�[�W���ōs���������܂Ƃ߂��֐���ǉ�,Init�֐���ǉ�

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "IME.hpp"

void IME::Init(HWND hWnd) noexcept
{
	m_bIME_Enabled = false;
	m_bTypeEnabled = false;
	m_nFontSize = 0;
	m_strInput.clear();
	m_strOldInput.clear();

	m_hWnd = hWnd;
	m_hIMC = ImmGetContext(hWnd);
}

void IME::DefaultProssesInWinProc(UINT In_nMessage, WPARAM In_wParam, LPARAM In_lParam) noexcept
{
	switch (In_nMessage)
	{
	case WM_CHAR: // �p�����͎��̏���
		// ���͂������̏ꍇ
		if (!IsTypeEnabled()) break;

		// ���{����͂�OFF�̏ꍇ
		if (!IsIME_Enabled())
		{
			InputEng(In_wParam);
		}
		break;

	case WM_IME_STARTCOMPOSITION:
		SetCompositionWindow();
		EnableIME();
		break;

	case WM_IME_CHAR:
		// ���͂������̏ꍇ
		if (!IsTypeEnabled()) break;
		// ���{����͂�ON�̏ꍇ
		if (IsIME_Enabled())
			InputJp(In_wParam);
		break;

	case WM_IME_ENDCOMPOSITION:
		DisableIME();
		break;
	}
}

void IME::EnableIME() noexcept
{
	m_bIME_Enabled = true;
	ImmSetConversionStatus(m_hIMC, IME_CMODE_NATIVE, IME_SMODE_NONE);
}

void IME::DisableIME() noexcept
{
	m_bIME_Enabled = false;
	ImmSetConversionStatus(m_hIMC, IME_CMODE_ALPHANUMERIC, IME_SMODE_NONE);
}

void IME::InputJp(WPARAM In_wParam) noexcept
{
	// 10�i��to16�i���Ŏg���ϐ�
	char work[5];
	std::string strWork1;
	std::string strWork2;
	std::string strWork3;
	// 16�i���ɕϊ�
	// �K��4���ŕԂ��Ă���(�����Ă����R�[�h�������R�[�h�ł����)
	sprintf_s(work, "%X", static_cast<int>(In_wParam));
	// 2�����ɕ�����
	strWork1 = work[0];
	strWork1 += work[1];
	strWork2 = work[2];
	strWork2 += work[3];
	// 2������16�i����10�i���ɕϊ����đ���(����ŕ����ɂȂ�)
	strWork3 = static_cast<char>(std::strtol(strWork1.c_str(), nullptr, 16));
	strWork3 += static_cast<char>(std::strtol(strWork2.c_str(), nullptr, 16));
	// ������ɒǉ�
	m_strInput += strWork3;
}

void IME::InputEng(WPARAM In_wParam) noexcept
{
	// �L��&�p����
	if (In_wParam >= 33 && In_wParam <= 126)
		m_strInput += static_cast<char>(In_wParam);
	else if (In_wParam == VK_BACK) // �o�b�N�X�y�[�X
		if(!m_strInput.empty()) // �������͂��Ȃ��ꍇ�͏������Ȃ�
			m_strInput.pop_back();
	else if (In_wParam == VK_SPACE) // �X�y�[�X
		m_strInput += " ";
}

std::string IME::PopInput()
{
	std::string strReturnVal = m_strInput;
	m_strInput.clear();
	return strReturnVal;
}

void IME::SetCompositionWindowPos(const SF2Position& In_f2Pos) noexcept
{
	m_f2CompositionWindowPos = In_f2Pos;

	// IME�p�̃n���h������������Ă��Ȃ��ꍇ�̓X���[
	if (m_hIMC == nullptr)
		return;

	LPCOMPOSITIONFORM lpCompForm = new COMPOSITIONFORM();
	ImmGetCompositionWindow(m_hIMC, lpCompForm); // ���݂̃R���|�W�V�����E�B���h�E�����擾
	lpCompForm->dwStyle = CFS_POINT; // �\�����W�Ŏg�p����f�[�^���|�C���g�Ɏw��
	lpCompForm->ptCurrentPos.x = static_cast<LONG>(m_f2CompositionWindowPos.x); // X���W�ݒ�
	lpCompForm->ptCurrentPos.y = static_cast<LONG>(m_f2CompositionWindowPos.y); // Y���W�ݒ�
	ImmSetCompositionWindow(m_hIMC, lpCompForm); // �R���|�W�V�����E�B���h�E�̏���ݒ�
	if (lpCompForm)
	{
		delete lpCompForm;
		lpCompForm = nullptr;
	}
}

void IME::SetCompositionFont(int In_nFontSizeHeight, int In_nFontSizeWidth, BYTE In_lfWeight,
	BYTE In_lfItalic, BYTE In_lfUnderline, BYTE In_lfStrikeOut, BYTE In_lfCharSet)
{
	LPLOGFONTA lpLogFont = new LOGFONTA(); // LOGFONTA�ŏ�����
	// ���݂�IME��font�����擾�A�o���Ȃ������ꍇ��return
	if (!ImmGetCompositionFontA(m_hIMC, lpLogFont))
	{
		delete lpLogFont;
		lpLogFont = nullptr;
		return;
	}
	
	// �t�H���g�̏���ݒ�
	lpLogFont->lfHeight = In_nFontSizeHeight; // �t�H���g�̍���
	lpLogFont->lfWidth = In_nFontSizeWidth; // �t�H���g�̕�
	lpLogFont->lfWeight = In_lfWeight; // �t�H���g�̑���
	lpLogFont->lfItalic = In_lfItalic; // �Α̂��ǂ���
	lpLogFont->lfUnderline = In_lfUnderline; // �����t�����ǂ���
	lpLogFont->lfStrikeOut = In_lfStrikeOut; // ���������t�����ǂ���
	lpLogFont->lfCharSet = In_lfCharSet; // �����Z�b�g

	*m_pLogFont = *lpLogFont; // �t�H���g����ۑ�

	// �t�H���g�̏���ݒ�
	if (!ImmSetCompositionFontA(m_hIMC, lpLogFont))
	{
		// font�̐ݒ�Ɏ��s�����ꍇ
		throw std::invalid_argument("�t�H���g���̐ݒ�Ɏ��s���܂����B");
	}

	// �g�p�����\���̂̊J��
	delete lpLogFont;
	lpLogFont = nullptr;
}

void IME::SetCompositionWindow() const noexcept
{
	// �ʒu���ݒ�
	LPCOMPOSITIONFORM lpCompForm = new COMPOSITIONFORM();
	ImmGetCompositionWindow(m_hIMC, lpCompForm); // ���݂̃R���|�W�V�����E�B���h�E�����擾
	lpCompForm->dwStyle = CFS_POINT; // �\�����W�Ŏg�p����f�[�^���|�C���g�Ɏw��
	lpCompForm->ptCurrentPos.x = static_cast<LONG>(m_f2CompositionWindowPos.x); // X���W�ݒ�
	lpCompForm->ptCurrentPos.y = static_cast<LONG>(m_f2CompositionWindowPos.y); // Y���W�ݒ�
	ImmSetCompositionWindow(m_hIMC, lpCompForm); // �R���|�W�V�����E�B���h�E�̏���ݒ�
	if (lpCompForm)
	{
		delete lpCompForm;
		lpCompForm = nullptr;
	}

	// �t�H���g�̏���ݒ�
	if(m_pLogFont != nullptr)
		ImmSetCompositionFontA(m_hIMC, m_pLogFont); // �t�H���g�̏���ݒ�
}

IME::IME() noexcept
	: m_bIME_Enabled(false), m_bTypeEnabled(false)
	, m_nFontSize(0), m_hIMC(nullptr), m_hWnd(nullptr)
	, m_strInput(""), m_strOldInput("")
	, m_pLogFont(nullptr)
	, m_f2CompositionWindowPos({ 0.0f, 0.0f })
{
}

IME::~IME()
{
	ImmReleaseContext(m_hWnd, m_hIMC);
}
