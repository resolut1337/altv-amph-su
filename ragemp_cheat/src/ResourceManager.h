#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <d3d11.h>
#include "../src/ImGui/imgui.h"
#include "stb_image.h"

class cTextureManager
{
	using TextureList = std::map<std::string, ID3D11ShaderResourceView*>;
public:
	cTextureManager(ID3D11Device* m_pDevice);
	~cTextureManager();

	ID3D11ShaderResourceView* add(std::string Key, LPCVOID  pSrcData, UINT SrcDataSize);
	ID3D11ShaderResourceView* add(std::string Key, int IdResource, LPCSTR lpType);
	ID3D11ShaderResourceView* get(std::string Key);

private:
	TextureList mData;
	ID3D11Device* m_pDevice;
};
extern std::shared_ptr<cTextureManager> m_pTexture;
