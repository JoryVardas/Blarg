//DONE
#ifndef __ID_H__
#define __ID_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct ID
			{
			public:
				unsigned int _ID;
				uint _Address;
				unsigned int _Type;

				ID()
				{
					_ID = 0;
					_Address = null;
					_Type = 0;
				};
				ID(ID& id){
					_ID = id._ID;
					_Address = id._Address;
					_Type = id._Type;
				};
				ID(uint id, void* address, uint type){
					_ID = id;
					_Address = (uint)address;
					_Type = type;
				};
				void operator =(ID id){
					_ID = id._ID;
					_Address = id._Address;
					_Type = id._Type;
				};
			};

		};
	};
};
#endif