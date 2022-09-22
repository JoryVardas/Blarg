#include "SettingsFile.h"

#ifndef __KEY_BINDING_MAP_FILE_H__
#define __KEY_BINDING_MAP_FILE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			namespace IO
			{
				struct KeyBinding
				{
					uint Key;
					bool Shift;
					bool Control;
					bool Alt;
					bool MultiKey;
					uint Key2;
					uint Key3;
				};

				class KeyBindingMapFile
				{
				private:
					SettingsFile _Source;
				public:
					KeyBindingMapFile(){};
					KeyBindingMapFile(v5String path){
						_Source = SettingsFile(path);
					};
					~KeyBindingMapFile(){};

					KeyBinding GetKeyBinding(v5String name)
					{
						int index = _Source.ElementExists(name);
						if(index != -1){
							v5String key = _Source.GetChildElementValue(index, 1);
							v5String shift = _Source.GetChildElementValue(index, 2);
							v5String control = _Source.GetChildElementValue(index, 3);
							v5String alt = _Source.GetChildElementValue(index, 4);
							v5String multiKey = _Source.GetChildElementValue(index, 5);
							v5String key2 = _Source.GetChildElementValue(index, 6);
							v5String key3 = _Source.GetChildElementValue(index, 7);

							KeyBinding keyBinding = {key.ToUINT(), shift.ToBool(), control.ToBool(), alt.ToBool(), multiKey.ToBool(), key2.ToUINT(), key3.ToUINT()};
							return keyBinding;
						};
					};
					void SetKeyBinding(v5String name, uint key, bool shift, bool control, bool alt, bool multikey, uint key2, uint key3)
					{
						int index = _Source.ElementExists(name);
						if(index != -1)
						{
							_Source.SetChildElementValue(index, 1, v5String().ToString(key));
							_Source.SetChildElementValue(index, 2, v5String().ToString(shift));
							_Source.SetChildElementValue(index, 3, v5String().ToString(control));
							_Source.SetChildElementValue(index, 4, v5String().ToString(alt));
							_Source.SetChildElementValue(index, 5, v5String().ToString(multikey));
							_Source.SetChildElementValue(index, 6, v5String().ToString(key2));
							_Source.SetChildElementValue(index, 7, v5String().ToString(key3));
						}
						else
						{
							_Source.AppendNewElement(name, "");
							_Source.AppendNewChildElement(v5String().ToString(key));
							_Source.AppendNewChildElement(v5String().ToString(shift));
							_Source.AppendNewChildElement(v5String().ToString(control));
							_Source.AppendNewChildElement(v5String().ToString(alt));
							_Source.AppendNewChildElement(v5String().ToString(multikey));
							_Source.AppendNewChildElement(v5String().ToString(key2));
							_Source.AppendNewChildElement(v5String().ToString(key3));
						};
					};
				};
			};
		};
	};
};

#endif