#ifndef __V5OBJECT_H__
#define __V5OBJECT_H__

#include "Global_Variables.h"
#include "Array.h"
#include "ID_Manager.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct v5ObjectDestroyEventData
			{
				uint _I;
			};

			struct v5Object
			{
				EventHandlerList(_OnObjectDestroyEventHandlers);
				uint _ID;

				v5Object(v5Object& o){
					_ID = o._ID;
					_OnObjectDestroyEventHandlers = o._OnObjectDestroyEventHandlers;
				};
				v5Object()
				{
					_OnObjectDestroyEventHandlers.SetResizeAmount(1);
				};

				v5Object(void* data, uint type)
				{
					_ID = __GLOBAL_ID_MANAGER__.RegisterID(data, type);
					_OnObjectDestroyEventHandlers.SetResizeAmount(1);
				};

				v5Object(void* data)
				{
					_ID = __GLOBAL_ID_MANAGER__.RegisterID(data, 0);
					//_OnObjectDestroyEventHandlers.SetResizeAmount(1);
				};

				~v5Object()
				{
					__GLOBAL_ID_MANAGER__.RecycleID(_ID);
					_ID = null;
					CallOnObjectDestroyEventHandlers();
				};

				uint GetID()
				{
					return _ID;
				};

				//functionToRun parameter = (void*)v5ObjectDestroyEventData
				void OnObjectDestroy(EventHandler(functionToRun))
				{
					_OnObjectDestroyEventHandlers.Add((uint)functionToRun);
				};

				void CallOnObjectDestroyEventHandlers()
				{
					v5ObjectDestroyEventData data = {_ID};
					CallEventHandlers(_OnObjectDestroyEventHandlers, &data);
				};

				void operator =(v5Object& o){
					_ID = o._ID;
					_OnObjectDestroyEventHandlers = o._OnObjectDestroyEventHandlers;
				};
			};
		};
	};
};
			
#endif