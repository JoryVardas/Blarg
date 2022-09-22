#include "Texture.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			Texture::Texture() : v5Object(this)
			{
				_FileLocation = null;
				_Width = 0;
				_Height = 0;
				_Texture = null;
				//_ID = __ID_MANAGER__->RegisterID(this, 0);
			};

			Texture::Texture(char* a, ID3D11Device** b) : v5Object(this)
			{
			//	_Device = b;
			//	_FileLocation = a;
//				File file (__STRING_ADD__(2, a, ".info"));
			//	char* buffer = new char[file.Size()];
			//	file.Read(buffer);
			//	Array<char*> settings = __STRING_SPLIT__(buffer, ';');
			//	_Width = __STRING_TO_INT__(*settings[0]);
			//	_Height = __STRING_TO_INT__(*settings[1]);
			//	_Type = __STRING_TO_INT__(*settings[2]);
			//	delete[] buffer;
			//	D3DX11CreateShaderResourceViewFromFile(b, a, null, null, &_Texture, null);
			};

			Texture::~Texture()
			{
				Release();
			};

			ID3D11ShaderResourceView* Texture::GetTexture()
			{
				return _Texture;
			};

			int Texture::GetWidth()
			{
				return _Width;
			};

			int Texture::GetHeight()
			{
				return _Height;
			};

			char* Texture::GetFileLocation()
			{
				return _FileLocation;
			};

			void Texture::Open(char* a)
			{
			//	if(_Texture != null) _Texture->Release();
			//	
			//	_FileLocation = a;
			//	File file (__STRING_ADD__(2, a, ".info"));
			//	char* buffer = new char[file.Size()];
			//	file.Read(buffer);
			//	Array<char*> settings = __STRING_SPLIT__(buffer, ';');
			//	_Width = __STRING_TO_INT__(*settings[0]);
			//	_Height = __STRING_TO_INT__(*settings[1]);
			//	_Type = __STRING_TO_INT__(*settings[2]);
			//	delete[] buffer;
			//	D3DX11CreateShaderResourceViewFromFile(_Device, a, null, null, &_Texture, null);
			};

			void Texture::Release()
			{
				try
				{
					delete[] _FileLocation;
				}
				catch(...)
				{
					try
					{
						delete[] _FileLocation;
					}
					catch(...)
					{
					};
				};

				_Width = _Height = _Type = 0;
//				_ID = 0;
				_Texture->Release();
				_Texture = null;
				_Device = null;
			};

			void Texture::operator =(Texture& a)
			{
				Release();
				_Device = a._Device;
				Open(a._FileLocation);
			};
		};
	};
};