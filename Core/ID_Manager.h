#ifndef __ID_MANAGER_H__
#define __ID_MANAGER_H__

#include "Global_Variables.h"
#include "v5Error.h"
#include "Array.h"
#include "ID.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct ID_Manager{
				Array<ID> _Identification;
				Array<uint> _UnusedIdentification;
				uint _NextIdentity;

				ID_Manager(ID_Manager& m){
					_Identification.SetResizeAmount(5);
					_NextIdentity = 0;
				};
				ID_Manager(){
					_Identification.SetResizeAmount(5);
					_NextIdentity = 0;
				};
				~ID_Manager(){
					_Identification.Clear();
				};

				ID GetIdentification(uint id){
					for(int i = 0; i < _Identification.GetSize(); i++){
						if(_Identification[i]->_ID == id) return _Identification[i].GetData();
					};
				};
				//returns the registered ID
				uint RegisterID(void* data, uint type){
					if(_UnusedIdentification.GetSize() != 0){
						ID ident (_UnusedIdentification[0].GetData(), data, type);
						_UnusedIdentification.Remove(0);
						_Identification.Add(ident);
						return ident._ID;
					}
					else{
						ID ident(_NextIdentity, data, type);
						_Identification.Add(ident);
						_NextIdentity++;
						return ident._ID;
					};
					return null;
				};
				void RecycleID(uint id){
					int idPos = -1;
					for(int i = 0; i < _Identification.GetSize(); i++){
						if(_Identification[i]->_ID == id)
						{
							idPos = i;
							break;
						};
					};
					if(idPos != -1){
						_UnusedIdentification.Add(_Identification[idPos]->_ID);
						_Identification.Remove(idPos);
					};
				};
			};

			static ID_Manager __GLOBAL_ID_MANAGER__;
		};
	};
};
#endif