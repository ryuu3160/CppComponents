/*+===================================================================
	File: Easing.hpp
	Summary: Easing�̃w�b�_�[�t�@�C��
	Author: ryuu3160
	Date: 2025/1/23 23:04 ����쐬
				/24 02:06 Ease InOut�֐��ǉ�

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <cmath>

/// <summary>
/// Easing NameSpace
/// </summary>
namespace Ease
{
	// ==============================
	//  �񋓌^
	// ==============================
	enum EasingType : unsigned int
	{
		LERP,		// ���`���
		IN_SINE,	// Ease-In Sine
		IN_QUAD,	// Ease-In Quad
		IN_CUBIC,	// Ease-In Cubic
		IN_QUART,	// Ease-In Quart
		IN_QUINT,	// Ease-In Quint
		IN_EXPO,	// Ease-In Expo
		IN_CIRC,	// Ease-In Circ
		IN_BACK,	// Ease-In Back
		IN_ELASTIC,	// Ease-In Elastic
		IN_BOUNCE,	// Ease-In Bounce
		OUT_SINE,	// Ease-Out Sine
		OUT_QUAD,	// Ease-Out Quad
		OUT_CUBIC,	// Ease-Out Cubic
		OUT_QUART,	// Ease-Out Quart
		OUT_QUINT,	// Ease-Out Quint
		OUT_EXPO,	// Ease-Out Expo
		OUT_CIRC,	// Ease-Out Circ
		OUT_BACK,	// Ease-Out Back
		OUT_ELASTIC,// Ease-Out Elastic
		OUT_BOUNCE,// Ease-Out Bounce
		IN_OUT_SINE,   // Ease-InOut Sine
		IN_OUT_QUAD,   // Ease-InOut Quad
		IN_OUT_CUBIC,  // Ease-InOut Cubic
		IN_OUT_QUART,  // Ease-InOut Quart
		IN_OUT_QUINT,  // Ease-InOut Quint
		IN_OUT_EXPO,   // Ease-InOut Expo
		IN_OUT_CIRC,   // Ease-InOut Circ
		IN_OUT_BACK,   // Ease-InOut Back
		IN_OUT_ELASTIC,// Ease-InOut Elastic
		IN_OUT_BOUNCE  // Ease-InOut Bounce
	};

	// ==============================
	//  �\����
	// ==============================
	struct Float2
	{
		float x;
		float y;
	};

	struct Float3
	{
		float x;
		float y;
		float z;
	};

	struct DataRate
	{
		float fRate;	// �}��ϐ�
		float fStart;	// �J�n���̒l
		float fEnd;		// �I�����̒l
	};

	struct DataDuration
	{
		float fNowTime;	// ���݂̎���
		float fDuration;// ������
		float fStart;	// �J�n���̒l
		float fEnd;		// �I�����̒l
	};

	struct DataRate2
	{
		float fRate;	// �}��ϐ�
		Float2 fStart;	// �J�n���̒l
		Float2 fEnd;		// �I�����̒l
	};

	struct DataDuration2
	{
		float fNowTime;	// ���݂̎���
		float fDuration;// ������
		Float2 fStart;	// �J�n���̒l
		Float2 fEnd;		// �I�����̒l
	};

	struct DataRate3
	{
		float fRate;	// �}��ϐ�
		Float3 fStart;	// �J�n���̒l
		Float3 fEnd;		// �I�����̒l
	};

	struct DataDuration3
	{
		float fNowTime;	// ���݂̎���
		float fDuration;// ������
		Float3 fStart;	// �J�n���̒l
		Float3 fEnd;		// �I�����̒l
	};

	// ==============================
	//  ���`���
	// ==============================

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_fRate]">�}��ϐ�</param>
	/// <param name="[In_fStart]">�J�n���̒l</param>
	/// <param name="[In_fEnd]">�I�����̒l</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr float Lerp(const float &In_fRate, const float &In_fStart, const float &In_fEnd)
	{
		return (In_fEnd - In_fStart) * In_fRate + In_fStart;
	}

	constexpr Float2 Lerp(const float &In_fRate, const Float2 &In_fStart, const Float2 &In_fEnd)
	{
		return { (In_fEnd.x - In_fStart.x) * In_fRate + In_fStart.x,
				 (In_fEnd.y - In_fStart.y) * In_fRate + In_fStart.y };
	}

	constexpr Float3 Lerp(const float &In_fRate, const Float3 &In_fStart, const Float3 &In_fEnd)
	{
		return { (In_fEnd.x - In_fStart.x) * In_fRate + In_fStart.x,
				 (In_fEnd.y - In_fStart.y) * In_fRate + In_fStart.y,
				 (In_fEnd.z - In_fStart.z) * In_fRate + In_fStart.z };
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr float Lerp(DataRate &In_sData)
	{
		return (In_sData.fEnd - In_sData.fStart) * In_sData.fRate + In_sData.fStart;
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr float Lerp(DataDuration &In_sData)
	{
		return (In_sData.fEnd - In_sData.fStart) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart;
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr Float2 Lerp(DataRate2 &In_sData)
	{
		return { (In_sData.fEnd.x - In_sData.fStart.x) * In_sData.fRate + In_sData.fStart.x,
				 (In_sData.fEnd.y - In_sData.fStart.y) * In_sData.fRate + In_sData.fStart.y };
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr Float2 Lerp(DataDuration2 &In_sData)
	{
		return { (In_sData.fEnd.x - In_sData.fStart.x) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart.x,
				 (In_sData.fEnd.y - In_sData.fStart.y) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart.y };
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr Float3 Lerp(DataRate3 &In_sData)
	{
		return { (In_sData.fEnd.x - In_sData.fStart.x) * In_sData.fRate + In_sData.fStart.x,
				 (In_sData.fEnd.y - In_sData.fStart.y) * In_sData.fRate + In_sData.fStart.y,
				 (In_sData.fEnd.z - In_sData.fStart.z) * In_sData.fRate + In_sData.fStart.z };
	}

	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	constexpr Float3 Lerp(DataDuration3 &In_sData)
	{
		return { (In_sData.fEnd.x - In_sData.fStart.x) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart.x,
				 (In_sData.fEnd.y - In_sData.fStart.y) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart.y,
				 (In_sData.fEnd.z - In_sData.fStart.z) * (In_sData.fNowTime / In_sData.fDuration) + In_sData.fStart.z };
	}

	// ==============================
	//  Eas-In
	// ==============================

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InSine(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InSine(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InSine(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InSine(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InSine(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Sine</para>
	/// <para>https://easings.net/ja#easeInSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InSine(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuad(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuad(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuad(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuad(DataDuration &In_sData);
	
	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuad(DataDuration2 &In_sData);
	
	/// <summary>
	/// <para>Ease-In Quad</para>
	/// <para>https://easings.net/ja#easeInQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuad(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InCubic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InCubic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InCubic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InCubic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InCubic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Cubic</para>
	/// <para>https://easings.net/ja#easeInCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InCubic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuart(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuart(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuart(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuart(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuart(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Quart</para>
	/// <para>https://easings.net/ja#easeInQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuart(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuint(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuint(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuint(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InQuint(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InQuint(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Quint</para>
	/// <para>https://easings.net/ja#easeInQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InQuint(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InExpo(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InExpo(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InExpo(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InExpo(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InExpo(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Expo</para>
	/// <para>https://easings.net/ja#easeInExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InExpo(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InCirc(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InCirc(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InCirc(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InCirc(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InCirc(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Circ</para>
	/// <para>https://easings.net/ja#easeInCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InCirc(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InBack(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InBack(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InBack(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InBack(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InBack(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Back</para>
	/// <para>https://easings.net/ja#easeInBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InBack(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InElastic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InElastic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InElastic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InElastic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InElastic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Elastic</para>
	/// <para>https://easings.net/ja#easeInElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InElastic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	///	<para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InBounce(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	///	<para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InBounce(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	///	<para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InBounce(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	/// <para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InBounce(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	/// <para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InBounce(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-In Bounce</para>
	/// <para>https://easings.net/ja#easeInBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InBounce(DataDuration3 &In_sData);

	// ==============================
	//  Eas-Out
	// ==============================

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutSine(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutSine(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutSine(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutSine(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutSine(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Sine</para>
	/// <para>https://easings.net/ja#easeOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutSine(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuad(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuad(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuad(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuad(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuad(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quad</para>
	/// <para>https://easings.net/ja#easeOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuad(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutCubic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutCubic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutCubic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutCubic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutCubic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Cubic</para>
	/// <para>https://easings.net/ja#easeOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutCubic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuart(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuart(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuart(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuart(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuart(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quart</para>
	/// <para>https://easings.net/ja#easeOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuart(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuint(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuint(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuint(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutQuint(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutQuint(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Quint</para>
	/// <para>https://easings.net/ja#easeOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutQuint(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutExpo(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutExpo(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutExpo(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutExpo(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutExpo(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Expo</para>
	/// <para>https://easings.net/ja#easeOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutExpo(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutCirc(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutCirc(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutCirc(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutCirc(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutCirc(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Circ</para>
	/// <para>https://easings.net/ja#easeOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutCirc(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutBack(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutBack(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutBack(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutBack(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutBack(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Back</para>
	/// <para>https://easings.net/ja#easeOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutBack(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutElastic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutElastic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutElastic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutElastic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutElastic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Elastic</para>
	/// <para>https://easings.net/ja#easeOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutElastic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutBounce(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutBounce(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutBounce(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float OutBounce(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 OutBounce(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-Out Bounce</para>
	/// <para>https://easings.net/ja#easeOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 OutBounce(DataDuration3 &In_sData);

	// ==============================
	//  Eas-InOut
	// ==============================

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutSine(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutSine(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutSine(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutSine(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutSine(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Sine</para>
	/// <para>https://easings.net/ja#easeInOutSine</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutSine(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuad(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuad(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuad(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuad(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuad(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quad</para>
	/// <para>https://easings.net/ja#easeInOutQuad</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuad(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutCubic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutCubic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutCubic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutCubic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutCubic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Cubic</para>
	/// <para>https://easings.net/ja#easeInOutCubic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutCubic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuart(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuart(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuart(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuart(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuart(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quart</para>
	/// <para>https://easings.net/ja#easeInOutQuart</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuart(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuint(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuint(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuint(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutQuint(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutQuint(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Quint</para>
	/// <para>https://easings.net/ja#easeInOutQuint</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutQuint(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutExpo(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutExpo(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutExpo(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutExpo(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutExpo(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Expo</para>
	/// <para>https://easings.net/ja#easeInOutExpo</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutExpo(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutCirc(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutCirc(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutCirc(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutCirc(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutCirc(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Circ</para>
	/// <para>https://easings.net/ja#easeInOutCirc</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutCirc(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutBack(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutBack(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutBack(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutBack(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutBack(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Back</para>
	/// <para>https://easings.net/ja#easeInOutBack</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutBack(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutElastic(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutElastic(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutElastic(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutElastic(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutElastic(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Elastic</para>
	/// <para>https://easings.net/ja#easeInOutElastic</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutElastic(DataDuration3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutBounce(DataRate &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutBounce(DataRate2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutBounce(DataRate3 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float InOutBounce(DataDuration &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 InOutBounce(DataDuration2 &In_sData);

	/// <summary>
	/// <para>Ease-InOut Bounce</para>
	/// <para>https://easings.net/ja#easeInOutBounce</para>
	/// </summary>
	/// <param name="[In_sData]">sDataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 InOutBounce(DataDuration3 &In_sData);


	// ==============================
	//  �����Ŏw��ł������
	// ==============================

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ƃf�[�^�Ɋ�Â��ăC�[�W���O�������s���܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">sDataRate�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float Easing(EasingType In_EasingType, DataRate &In_sData);

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ƃf�[�^�Ɋ�Â��āA�C�[�W���O�������s���A���ʂ�Ԃ��܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">DataRate2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 Easing(EasingType In_EasingType, DataRate2 &In_sData);

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ɏ]���āA3�����f�[�^�̃C�[�W���O�������s���܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">DataRate3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 Easing(EasingType In_EasingType, DataRate3 &In_sData);

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ƃf�[�^�Ɋ�Â��āA�C�[�W���O�l���v�Z���܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">DataDuration�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float Easing(EasingType In_EasingType, DataDuration &In_sData);

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ƃf�[�^�Ɋ�Â��āA�C�[�W���O�������s���A���ʂ�2�������������_�l��Ԃ��܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">DataDuration2�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float2 Easing(EasingType In_EasingType, DataDuration2 &In_sData);

	/// <summary>
	/// �w�肳�ꂽ�C�[�W���O�^�C�v�ƃf�[�^�Ɋ�Â��āA3�����̃C�[�W���O�l���v�Z���܂��B
	/// </summary>
	/// <param name="[In_EasingType]">�C�[�W���O�^�C�v</param>
	/// <param name="[In_sData]">DataDuration3�ւ̎Q��</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Float3 Easing(EasingType In_EasingType, DataDuration3 &In_sData);

}
