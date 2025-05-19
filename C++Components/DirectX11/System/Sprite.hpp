/*+===================================================================
	File: Sprite.hpp
	Summary: wasssk�l�̂��̂��Q�l�ɂ��č쐬
	Author: ryuu3160
	Date: 2025/05/19 Mon PM 05:27:48 ����쐬
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <memory>
#include "../Texture/MeshBuffer.hpp"
#include "../Texture/Shader.hpp"
#include "../Texture/Texture.hpp"

class Sprite : Singleton<Sprite>
{
	friend class Singleton<Sprite>;
public:
	void Init();
	void Uninit();
	void Draw();

	void SetOffset(DirectX::XMFLOAT2 offset);
	void SetSize(DirectX::XMFLOAT2 size);
	void SetUVPos(DirectX::XMFLOAT2 pos);
	void SetUVScale(DirectX::XMFLOAT2 scale);
	void SetColor(DirectX::XMFLOAT4 color);
	void SetTexture(Texture *tex);

	void SetWorld(DirectX::XMFLOAT4X4 world);
	void SetView(DirectX::XMFLOAT4X4 view);
	void SetProjection(DirectX::XMFLOAT4X4 proj);

	void SetVertexShader(Shader *vs);
	void SetPixelShader(Shader *ps);

private:

	Sprite();
	~Sprite();

	struct Data
	{
		std::shared_ptr<MeshBuffer> mesh;
		DirectX::XMFLOAT4X4 matrix[3];
		DirectX::XMFLOAT4 param[3];
		Texture *texture;
		Shader *vs;
		Shader *ps;
	};
	Data m_data;
	std::shared_ptr<VertexShader> m_defVS;
	std::shared_ptr<PixelShader> m_defPS;
	std::shared_ptr<Texture> m_whiteTex;
};
