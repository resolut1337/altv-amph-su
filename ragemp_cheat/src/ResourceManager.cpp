#include "ResourceManager.h"
std::shared_ptr<cTextureManager> m_pTexture;


#define STB_IMAGE_IMPLEMENTATION



cTextureManager::cTextureManager(ID3D11Device* pDevice) :
	m_pDevice(pDevice)
{
	mData.clear();
}
cTextureManager::~cTextureManager()
{
	if (this->m_pDevice) {
		this->m_pDevice->Release();
		this->m_pDevice = nullptr;
	}

	mData.clear();
}


ID3D11ShaderResourceView* cTextureManager::get(std::string Key)
{
	return  mData.count(Key) != 0 ? mData.at(Key) : nullptr;
}
ID3D11ShaderResourceView* cTextureManager::add(std::string Key, LPCVOID  pSrcData, UINT SrcDataSize)
{
	if (mData.count(Key))
		return mData.at(Key);

	ID3D11ShaderResourceView* texture = nullptr;



	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load_from_memory((stbi_uc const*)pSrcData, SrcDataSize, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return nullptr;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	m_pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	m_pDevice->CreateShaderResourceView(pTexture, &srvDesc, &texture);
	pTexture->Release();


	stbi_image_free(image_data);


	mData.emplace(Key, std::move(texture));
	return mData.at(Key);
}
ID3D11ShaderResourceView* cTextureManager::add(std::string Key, int IdResource, LPCSTR lpType)
{
	if (mData.count(Key))
		return mData.at(Key);


	auto _LocResource = [](int  a1, LPCSTR a2)->std::pair<std::unique_ptr<uint8_t[]>, uint32_t>
	{
		HRSRC resInfo = FindResourceA(NULL, MAKEINTRESOURCEA(a1), a2);
		if (resInfo) {
			HGLOBAL hRes = LoadResource(NULL, resInfo);

			auto   pData = LockResource(hRes);
			auto   size = SizeofResource(NULL, resInfo);

			auto buf = std::make_unique<uint8_t[]>(size);

			memcpy(buf.get(), pData, size);
			return std::make_pair(std::move(buf), size);

		}
		return std::pair<std::unique_ptr<uint8_t[]>, uint32_t>();
	};

	auto [buff, size] = _LocResource(IdResource, lpType);
	ID3D11ShaderResourceView* texture = add(Key, buff.get(), size);

	mData.emplace(Key, std::move(texture));
	return mData.at(Key);
}



