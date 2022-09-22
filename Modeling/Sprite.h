//
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Core\File.h"
#include "Core\v5Error.h"
#include "Point.h"
#include "Texture.h"
#include "Vector.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			using namespace BrokenTechStudios::Nuke::Core;

			class Sprite
			{
			private:
				Texture _Image;
				Vertex _UpperLeftCorner;
				float _Width;
				float _Height;
				bool _Visable;
			public:
				Sprite(Sprite& s){
					_Image = s._Image;
					_UpperLeftCorner = s._UpperLeftCorner;
					_Width = s._Width;
					_Height = s._Height;
					_Visable = s._Visable;
				};
				Sprite();
				Sprite(float x, float y, float width, float height, char* nameOfTexture);
				Sprite(Texture image, Point3D v1, Point3D v2, Point3D v3, Point3D v4);
				Sprite(Texture image, Point3D v1, float width, float height);
				Sprite(Texture image, float upperLeftCornerX, float upperLeftCornerY, float width, float height);
				~Sprite();
	
				Texture GetTexture();
				bool IsVisable();
				float GetWidth();
				float GetHeight();
				Point3D GetUpperLeftCorner();
				Vertex* GetVertexArray();
				WORD* GetIndexArray();
				void SetTexture(Texture texture);
				void SetWidth(float width);
				void SetHeight(float height);
				void SetVisable(bool visable);
				void SetUpperLeftCorner(Point3D upperLeftCorner);
				void Release();
	
				void operator =(Sprite&);
			};
		};
	};
};
#endif