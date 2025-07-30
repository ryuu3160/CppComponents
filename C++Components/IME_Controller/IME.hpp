/*+===================================================================
	File: IME.hpp
	Summary: IME����N���X
	Author: ryuu3160
	Date: 2025/01/29 16:38 ����쐬
				 /30 12:30 ���͗p�̊֐��Ȃǒǉ�
			  /02/06 06:30 ���{����͑Ή�,�E�B���h�E�v���V�[�W���ōs���������܂Ƃ߂��֐���ǉ�,Init�֐���ǉ�

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../Singleton/Singleton.hpp"
#include <Windows.h>
#include <memory>
#include <imm.h>
#pragma comment(lib, "imm32.lib")

/// <summary>
/// IME�N���X
/// </summary>
class IME final : public Singleton<IME>
{
	friend class Singleton<IME>;
public:

	// 2D���W�̍\����
	struct SF2Position
	{
		float x; // x���W
		float y; // y���W
	};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="[In_hWnd]">�E�B���h�E�n���h��</param>
	void Init(HWND hWnd) noexcept;

	/// <summary>
	/// �f�t�H���g�̃E�B���h�E�v���V�[�W���ōs������
	/// </summary>
	/// <param name="[In_nMessage]">���b�Z�[�W</param>
	/// <param name="[wParam]">wParam</param>
	/// <param name="[lParam]">lParam</param>
	void DefaultProssesInWinProc(UINT In_nMessage, WPARAM wParam, LPARAM lParam) noexcept;

	/// <summary>
	/// <para>IME�̗L����</para>
	/// <para>�����Ō���IME�̗L�����́A���{����̗͂L�������w��</para>
	/// </summary>
	void EnableIME() noexcept;

	/// <summary>
	/// <para>IME�̖�����</para>
	/// <para>�����Ō���IME�̖������́A���{����̖͂��������w��</para>
	/// </summary>
	void DisableIME() noexcept;

	/// <summary>
	/// �������̗͂L����
	/// </summary>
	inline void EnableType() noexcept { m_bTypeEnabled = true; }

	/// <summary>
	/// �������̖͂�����
	/// </summary>
	inline void DisableType() noexcept { m_bTypeEnabled = false; }

	/// <summary>
	/// <para>���͏����擾����</para>
	/// <para>���{����͐�p</para>
	/// </summary>
	/// <param name="[In_wParam]">�����R�[�h</param>
	void InputJp(WPARAM In_wParam) noexcept;

	/// <summary>
	/// <para>���͏����擾����</para>
	/// <para>���[�}�����͐�p</para>
	/// </summary>
	/// <param name="[In_wParam]">JIS�R�[�h</param>
	void InputEng(WPARAM In_wParam) noexcept;

	/// <summary>
	/// �ۑ�����Ă�����͏����N���A����
	/// </summary>
	inline void Clear() { m_strInput.clear(); }

	// ==============================
	//  Getter
	// ==============================

	/// <summary>
	/// ���͏����擾����
	/// </summary>
	/// <returns>���͏��</returns>
	inline const std::string& GetInput() const noexcept
	{ return m_strInput; }

	/// <summary>
	/// ���͏����擾���A�ۑ�����Ă�����͏����N���A����
	/// </summary>
	/// <returns>���͏��</returns>
	std::string PopInput();

	/// <summary>
	/// IME���L�����ǂ������擾����
	/// </summary>
	/// <returns>IME���L�����ǂ���</returns>
	inline const bool& IsIME_Enabled() const noexcept
	{ return m_bIME_Enabled; }

	/// <summary>
	/// �������͂��L�����ǂ������擾����
	/// </summary>
	/// <returns>�������͂��L�����ǂ���</returns>
	inline const bool& IsTypeEnabled() const noexcept
	{ return m_bTypeEnabled; }

	// ==============================
	//  Setter
	// ==============================

	/// <summary>
	/// ���̓E�B���h�E�̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="[In_f3Pos]">�ʒu</param>
	void SetCompositionWindowPos(const SF2Position& In_f2Pos) noexcept;

	/// <summary>
	/// ���̓E�B���h�E�̃t�H���g����ݒ肷��
	/// </summary>
	/// <param name="[In_nFontSizeHeight]">�t�H���g�̍���</param>
	/// <param name="[In_nFontSizeWidth]">�t�H���g�̕�</param>
	/// <param name="[In_lfWeight]">�t�H���g�̑���</param>
	/// <param name="[In_lfItalic]">�Α̂��ǂ���</param>
	/// <param name="[In_lfUnderline]">�����t�����ǂ���</param>
	/// <param name="[In_lfStrikeOut]">���������t�����ǂ���</param>
	/// <param name="[In_lfCharSet]">�����Z�b�g</param>
	void SetCompositionFont(int In_nFontSizeHeight, int In_nFontSizeWidth = 0, LONG In_lfWeight = FW_NORMAL,
		BYTE In_lfItalic = false, BYTE In_lfUnderline = false, BYTE In_lfStrikeOut = false, BYTE In_lfCharSet = DEFAULT_CHARSET);

	/// <summary>
	/// ���ɐݒ肳��Ă�������g�p�������̓E�B���h�E�̏��X�̐ݒ�
	/// </summary>
	void SetCompositionWindow() const noexcept;

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	IME() noexcept;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~IME();

private:
	HIMC m_hIMC; // IME�̃R���e�L�X�g
	HWND m_hWnd; // �E�B���h�E�n���h��

	std::string m_strInput;		// ���͏��
	std::string m_strOldInput;	// 1�t���[���O�̓��͏��
	bool m_bIME_Enabled;		// IME���L�����ǂ���
	bool m_bTypeEnabled;		// �������͂��L�����ǂ���

	LPLOGFONTA m_pLogFont;		// �t�H���g���
	int m_nFontSize;			// �t�H���g�T�C�Y

	SF2Position m_f2CompositionWindowPos; // ���̓E�B���h�E�̈ʒu
};
