//
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "v5Error.h"
#include "File.h"
#include "ID_Manager.h"
#include "v5Object.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{

			using namespace BrokenTechStudios::Nuke::Core;
			using namespace BrokenTechStudios::Nuke::Core::IO;

			struct Texture : public v5Object
			{
				char* _FileLocation;
				int _Width;
				int _Height;
				int _Type; //0 = color, 1 = greyscale
				ID3D11ShaderResourceView* _Texture;
				ID3D11Device** _Device;
	
				Texture(Texture& t){
					_FileLocation = t._FileLocation;
					Open(_FileLocation);
				};
				Texture();
				Texture(char* fileLocation, ID3D11Device** device);
				~Texture();
	
				ID3D11ShaderResourceView* GetTexture();
				ID3D11ShaderResourceView** GetTexturePtr(){
					return &_Texture;
				};
				int GetWidth();
				int GetHeight();
				char* GetFileLocation();
	
				void Open(char* fileLocation);
				void Release();
	
				void operator =(Texture&);
			};
		};
	};
};
#endif