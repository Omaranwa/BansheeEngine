#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptGUIElement.h"

namespace BansheeEngine
{
	/**
	 * @brief	Interop class between C++ & CLR for GUIProgressBar. 
	 */
	class BS_SCR_BE_EXPORT ScriptGUIProgressBar : public TScriptGUIElement <ScriptGUIProgressBar>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "GUIProgressBar")

	private:
		ScriptGUIProgressBar(MonoObject* instance, GUIProgressBar* progressBar);

		/************************************************************************/
		/* 								CLR HOOKS						   		*/
		/************************************************************************/
		static void internal_createInstance(MonoObject* instance, MonoString* style, MonoArray* guiOptions);
		static void internal_setPercent(ScriptGUIProgressBar* nativeInstance, float percent);
		static float internal_getPercent(ScriptGUIProgressBar* nativeInstance);
		static void internal_setTint(ScriptGUIProgressBar* nativeInstance, Color color);
	};
}