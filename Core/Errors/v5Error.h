//DONE
#ifndef __v5Error_H__
#define __v5Error_H__

#include "Base_Includes.h"
#include "Global_Variables.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct v5Error
			{
				int	_ErrorID	;
				char* 	_ErrorCode	;
				char* 	_ErrorMessage	;

			////////////////////////////////////////////////////////////

					v5Error	()					;
					v5Error	(char* errorCode)			;
					v5Error	(char* errorCode, char* errorMessage)	;
					~v5Error	()					;
	
				char*	GetErrorCode	()					;
				char*	GetErrorMessage	()					;
				int	GetErrorID	()					;
				void	SetErrorCode	(char* errorCode)			;
				void	SetErrorMessage	(char* errorMessage)			;
	
				//Prints the error to an error log file.
				void 	Print		()					;
				//Prints the error to an error log file, and tells the engine to exit.
				void 	Print		(bool fatal)				;
			};

#define ErrorFunctions(name, code)  static inline void name(){v5Error e(code);e.Print();}; \
									static inline void name(char* message){v5Error e(code, message);e.Print();}; \
									static inline void name(bool fatal){v5Error e(code);e.Print(fatal);}; \
									static inline void name(char* message, bool fatal){v5Error e(code, message);e.Print(fatal);}
		};
	};
};

#endif