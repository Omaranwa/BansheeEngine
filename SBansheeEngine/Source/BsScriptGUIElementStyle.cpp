#include "BsScriptGUIElementStyle.h"
#include "BsScriptMeta.h"
#include "BsMonoField.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsScriptFont.h"
#include "BsException.h"
#include "BsGUIElementStyle.h"
#include "BsScriptGUIElementStateStyle.h"
#include "BsMonoUtil.h"

namespace BansheeEngine
{
	ScriptGUIElementStyle::ScriptGUIElementStyle(MonoObject* instance, const String& name)
		:ScriptObject(instance), mName(name), mElementStyle(bs_new<GUIElementStyle>()), mFont(nullptr), mOwnsStyle(true), mNormal(nullptr), mHover(nullptr),
		mActive(nullptr), mFocused(nullptr), mNormalOn(nullptr), mHoverOn(nullptr), mActiveOn(nullptr), mFocusedOn(nullptr)
	{

	}

	ScriptGUIElementStyle::ScriptGUIElementStyle(MonoObject* instance, const String& name, GUIElementStyle* externalStyle)
		:ScriptObject(instance), mName(name), mElementStyle(externalStyle), mFont(nullptr), mOwnsStyle(false), mNormal(nullptr), mHover(nullptr),
		mActive(nullptr), mFocused(nullptr), mNormalOn(nullptr), mHoverOn(nullptr), mActiveOn(nullptr), mFocusedOn(nullptr)
	{

	}

	ScriptGUIElementStyle::~ScriptGUIElementStyle()
	{
		if(mOwnsStyle)
			bs_delete(mElementStyle);
	}

	void ScriptGUIElementStyle::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", &ScriptGUIElementStyle::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_AddSubStyle", &ScriptGUIElementStyle::internal_addSubStyle);

		metaData.scriptClass->addInternalCall("Internal_GetFont", &ScriptGUIElementStyle::internal_GetFont);
		metaData.scriptClass->addInternalCall("Internal_SetFont", &ScriptGUIElementStyle::internal_SetFont);

		metaData.scriptClass->addInternalCall("Internal_GetFontSize", &ScriptGUIElementStyle::internal_GetFontSize);
		metaData.scriptClass->addInternalCall("Internal_SetFontSize", &ScriptGUIElementStyle::internal_SetFontSize);
		metaData.scriptClass->addInternalCall("Internal_GetTextHorzAlign", &ScriptGUIElementStyle::internal_GetTextHorzAlign);
		metaData.scriptClass->addInternalCall("Internal_SetTextHorzAlign", &ScriptGUIElementStyle::internal_SetTextHorzAlign);
		metaData.scriptClass->addInternalCall("Internal_GetTextVertAlign", &ScriptGUIElementStyle::internal_GetTextVertAlign);
		metaData.scriptClass->addInternalCall("Internal_SetTextVertAlign", &ScriptGUIElementStyle::internal_SetTextVertAlign);
		metaData.scriptClass->addInternalCall("Internal_GetImagePosition", &ScriptGUIElementStyle::internal_GetImagePosition);
		metaData.scriptClass->addInternalCall("Internal_SetImagePosition", &ScriptGUIElementStyle::internal_SetImagePosition);
		metaData.scriptClass->addInternalCall("Internal_GetWordWrap", &ScriptGUIElementStyle::internal_GetWordWrap);
		metaData.scriptClass->addInternalCall("Internal_SetWordWrap", &ScriptGUIElementStyle::internal_SetWordWrap);

		metaData.scriptClass->addInternalCall("Internal_GetNormal", &ScriptGUIElementStyle::internal_GetNormal);
		metaData.scriptClass->addInternalCall("Internal_SetNormal", &ScriptGUIElementStyle::internal_SetNormal);
		metaData.scriptClass->addInternalCall("Internal_GetHover", &ScriptGUIElementStyle::internal_GetHover);
		metaData.scriptClass->addInternalCall("Internal_SetHover", &ScriptGUIElementStyle::internal_SetHover);
		metaData.scriptClass->addInternalCall("Internal_GetActive", &ScriptGUIElementStyle::internal_GetActive);
		metaData.scriptClass->addInternalCall("Internal_SetActive", &ScriptGUIElementStyle::internal_SetActive);
		metaData.scriptClass->addInternalCall("Internal_GetFocused", &ScriptGUIElementStyle::internal_GetFocused);
		metaData.scriptClass->addInternalCall("Internal_SetFocused", &ScriptGUIElementStyle::internal_SetFocused);

		metaData.scriptClass->addInternalCall("Internal_GetNormalOn", &ScriptGUIElementStyle::internal_GetNormalOn);
		metaData.scriptClass->addInternalCall("Internal_SetNormalOn", &ScriptGUIElementStyle::internal_SetNormalOn);
		metaData.scriptClass->addInternalCall("Internal_GetHoverOn", &ScriptGUIElementStyle::internal_GetHoverOn);
		metaData.scriptClass->addInternalCall("Internal_SetHoverOn", &ScriptGUIElementStyle::internal_SetHoverOn);
		metaData.scriptClass->addInternalCall("Internal_GetActiveOn", &ScriptGUIElementStyle::internal_GetActiveOn);
		metaData.scriptClass->addInternalCall("Internal_SetActiveOn", &ScriptGUIElementStyle::internal_SetActiveOn);
		metaData.scriptClass->addInternalCall("Internal_GetFocusedOn", &ScriptGUIElementStyle::internal_GetFocusedOn);
		metaData.scriptClass->addInternalCall("Internal_SetFocusedOn", &ScriptGUIElementStyle::internal_SetFocusedOn);

		metaData.scriptClass->addInternalCall("Internal_GetBorder", &ScriptGUIElementStyle::internal_GetBorder);
		metaData.scriptClass->addInternalCall("Internal_SetBorder", &ScriptGUIElementStyle::internal_SetBorder);
		metaData.scriptClass->addInternalCall("Internal_GetMargins", &ScriptGUIElementStyle::internal_GetMargins);
		metaData.scriptClass->addInternalCall("Internal_SetMargins", &ScriptGUIElementStyle::internal_SetMargins);
		metaData.scriptClass->addInternalCall("Internal_GetContentOffset", &ScriptGUIElementStyle::internal_GetContentOffset);
		metaData.scriptClass->addInternalCall("Internal_SetContentOffset", &ScriptGUIElementStyle::internal_SetContentOffset);

		metaData.scriptClass->addInternalCall("Internal_GetWidth", &ScriptGUIElementStyle::internal_GetWidth);
		metaData.scriptClass->addInternalCall("Internal_SetWidth", &ScriptGUIElementStyle::internal_SetWidth);
		metaData.scriptClass->addInternalCall("Internal_GetHeight", &ScriptGUIElementStyle::internal_GetHeight);
		metaData.scriptClass->addInternalCall("Internal_SetHeight", &ScriptGUIElementStyle::internal_SetHeight);
		metaData.scriptClass->addInternalCall("Internal_GetMinWidth", &ScriptGUIElementStyle::internal_GetMinWidth);
		metaData.scriptClass->addInternalCall("Internal_SetMinWidth", &ScriptGUIElementStyle::internal_SetMinWidth);
		metaData.scriptClass->addInternalCall("Internal_GetMaxWidth", &ScriptGUIElementStyle::internal_GetMaxWidth);
		metaData.scriptClass->addInternalCall("Internal_SetMaxWidth", &ScriptGUIElementStyle::internal_SetMaxWidth);
		metaData.scriptClass->addInternalCall("Internal_GetMinHeight", &ScriptGUIElementStyle::internal_GetMinHeight);
		metaData.scriptClass->addInternalCall("Internal_SetMinHeight", &ScriptGUIElementStyle::internal_SetMinHeight);
		metaData.scriptClass->addInternalCall("Internal_GetMaxHeight", &ScriptGUIElementStyle::internal_GetMaxHeight);
		metaData.scriptClass->addInternalCall("Internal_SetMaxHeight", &ScriptGUIElementStyle::internal_SetMaxHeight);
		metaData.scriptClass->addInternalCall("Internal_GetFixedWidth", &ScriptGUIElementStyle::internal_GetFixedWidth);
		metaData.scriptClass->addInternalCall("Internal_SetFixedWidth", &ScriptGUIElementStyle::internal_SetFixedWidth);
		metaData.scriptClass->addInternalCall("Internal_GetFixedHeight", &ScriptGUIElementStyle::internal_GetFixedHeight);
		metaData.scriptClass->addInternalCall("Internal_SetFixedHeight", &ScriptGUIElementStyle::internal_SetFixedHeight);
	}

	void ScriptGUIElementStyle::internal_createInstance(MonoObject* instance, MonoString* name)
	{
		char* nativeName = mono_string_to_utf8(name);
		String styleName(nativeName);
		free(nativeName);

		ScriptGUIElementStyle* nativeInstance = new (bs_alloc<ScriptGUIElementStyle>()) ScriptGUIElementStyle(instance, styleName);
	}

	void ScriptGUIElementStyle::internal_createInstanceExternal(MonoObject* instance, MonoString* name, GUIElementStyle* externalStyle)
	{
		char* nativeName = mono_string_to_utf8(name);
		String styleName(nativeName);
		free(nativeName);

		ScriptGUIElementStyle* nativeInstance = new (bs_alloc<ScriptGUIElementStyle>()) ScriptGUIElementStyle(instance, styleName, externalStyle);
	}

	void ScriptGUIElementStyle::internal_addSubStyle(ScriptGUIElementStyle* nativeInstance, MonoString* guiType, MonoString* styleName)
	{
		String guiTypeStr = MonoUtil::monoToString(guiType);
		String styleNameStr = MonoUtil::monoToString(styleName);

		nativeInstance->getInternalValue()->subStyles[guiTypeStr] = styleNameStr;
	}

	void ScriptGUIElementStyle::internal_GetFont(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mFont != nullptr)
		{
			*value = nativeInstance->mFont->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetFont(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptFont* nativeValue = ScriptFont::toNative(value);
		nativeInstance->mElementStyle->font = static_resource_cast<Font>(nativeValue->getNativeHandle());
		nativeInstance->mFont = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetFontSize(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->fontSize;
	}

	void ScriptGUIElementStyle::internal_SetFontSize(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->fontSize = value;
	}

	void ScriptGUIElementStyle::internal_GetTextHorzAlign(ScriptGUIElementStyle* nativeInstance, TextHorzAlign*value)
	{
		*value = nativeInstance->mElementStyle->textHorzAlign;
	}

	void ScriptGUIElementStyle::internal_SetTextHorzAlign(ScriptGUIElementStyle* nativeInstance, TextHorzAlign value)
	{
		nativeInstance->mElementStyle->textHorzAlign = value;
	}

	void ScriptGUIElementStyle::internal_GetTextVertAlign(ScriptGUIElementStyle* nativeInstance, TextVertAlign* value)
	{
		*value = nativeInstance->mElementStyle->textVertAlign;
	}

	void ScriptGUIElementStyle::internal_SetTextVertAlign(ScriptGUIElementStyle* nativeInstance, TextVertAlign value)
	{
		nativeInstance->mElementStyle->textVertAlign = value;
	}

	void ScriptGUIElementStyle::internal_GetImagePosition(ScriptGUIElementStyle* nativeInstance, GUIImagePosition* value)
	{
		*value = nativeInstance->mElementStyle->imagePosition;
	}

	void ScriptGUIElementStyle::internal_SetImagePosition(ScriptGUIElementStyle* nativeInstance, GUIImagePosition value)
	{
		nativeInstance->mElementStyle->imagePosition = value;
	}

	void ScriptGUIElementStyle::internal_GetWordWrap(ScriptGUIElementStyle* nativeInstance, bool* value)
	{
		*value = nativeInstance->mElementStyle->wordWrap;
	}

	void ScriptGUIElementStyle::internal_SetWordWrap(ScriptGUIElementStyle* nativeInstance, bool value)
	{
		nativeInstance->mElementStyle->wordWrap = value;
	}

	void ScriptGUIElementStyle::internal_GetNormal(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mNormal != nullptr)
		{
			*value = nativeInstance->mNormal->getManagedInstance();
			return;	
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetNormal(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->normal = nativeValue->getInternalValue();
		nativeInstance->mNormal = nativeValue;
	}


	void ScriptGUIElementStyle::internal_GetHover(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mHover != nullptr)
		{
			*value = nativeInstance->mHover->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetHover(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->hover = nativeValue->getInternalValue();
		nativeInstance->mHover = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetActive(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mActive != nullptr)
		{
			*value = nativeInstance->mActive->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetActive(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->active = nativeValue->getInternalValue();
		nativeInstance->mActive = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetFocused(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mFocused != nullptr)
		{
			*value = nativeInstance->mFocused->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetFocused(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->focused = nativeValue->getInternalValue();
		nativeInstance->mFocused = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetNormalOn(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mNormalOn != nullptr)
		{
			*value = nativeInstance->mNormalOn->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetNormalOn(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->normalOn = nativeValue->getInternalValue();
		nativeInstance->mNormalOn = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetHoverOn(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mHoverOn != nullptr)
		{
			*value = nativeInstance->mHoverOn->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetHoverOn(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->hoverOn = nativeValue->getInternalValue();
		nativeInstance->mHoverOn = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetActiveOn(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mActiveOn != nullptr)
		{
			*value = nativeInstance->mActiveOn->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetActiveOn(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->activeOn = nativeValue->getInternalValue();
		nativeInstance->mActiveOn = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetFocusedOn(ScriptGUIElementStyle* nativeInstance, MonoObject** value)
	{
		if (nativeInstance->mFocusedOn != nullptr)
		{
			*value = nativeInstance->mFocusedOn->getManagedInstance();
			return;
		}

		*value = nullptr;
	}

	void ScriptGUIElementStyle::internal_SetFocusedOn(ScriptGUIElementStyle* nativeInstance, MonoObject* value)
	{
		ScriptGUIElementStateStyle* nativeValue = ScriptGUIElementStateStyle::toNative(value);
		nativeInstance->mElementStyle->focusedOn = nativeValue->getInternalValue();
		nativeInstance->mFocusedOn = nativeValue;
	}

	void ScriptGUIElementStyle::internal_GetBorder(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		*value = nativeInstance->mElementStyle->border;
	}

	void ScriptGUIElementStyle::internal_SetBorder(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		nativeInstance->mElementStyle->border = *value;
	}

	void ScriptGUIElementStyle::internal_GetMargins(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		*value = nativeInstance->mElementStyle->margins;
	}

	void ScriptGUIElementStyle::internal_SetMargins(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		nativeInstance->mElementStyle->margins = *value;
	}

	void ScriptGUIElementStyle::internal_GetContentOffset(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		*value = nativeInstance->mElementStyle->contentOffset;
	}

	void ScriptGUIElementStyle::internal_SetContentOffset(ScriptGUIElementStyle* nativeInstance, RectOffset* value)
	{
		nativeInstance->mElementStyle->contentOffset = *value;
	}

	void ScriptGUIElementStyle::internal_GetWidth(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->width;
	}

	void ScriptGUIElementStyle::internal_SetWidth(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->width = value;
	}

	void ScriptGUIElementStyle::internal_GetHeight(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->height;
	}

	void ScriptGUIElementStyle::internal_SetHeight(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->height = value;
	}

	void ScriptGUIElementStyle::internal_GetMinWidth(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->minWidth;
	}

	void ScriptGUIElementStyle::internal_SetMinWidth(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->minWidth = value;
	}

	void ScriptGUIElementStyle::internal_GetMaxWidth(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->maxWidth;
	}

	void ScriptGUIElementStyle::internal_SetMaxWidth(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->maxWidth = value;
	}

	void ScriptGUIElementStyle::internal_GetMinHeight(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->minHeight;
	}

	void ScriptGUIElementStyle::internal_SetMinHeight(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->minHeight = value;
	}

	void ScriptGUIElementStyle::internal_GetMaxHeight(ScriptGUIElementStyle* nativeInstance, UINT32* value)
	{
		*value = nativeInstance->mElementStyle->maxHeight;
	}

	void ScriptGUIElementStyle::internal_SetMaxHeight(ScriptGUIElementStyle* nativeInstance, UINT32 value)
	{
		nativeInstance->mElementStyle->maxHeight = value;
	}

	void ScriptGUIElementStyle::internal_GetFixedWidth(ScriptGUIElementStyle* nativeInstance, bool* value)
	{
		*value = nativeInstance->mElementStyle->fixedWidth;
	}

	void ScriptGUIElementStyle::internal_SetFixedWidth(ScriptGUIElementStyle* nativeInstance, bool value)
	{
		nativeInstance->mElementStyle->fixedWidth = value;
	}

	void ScriptGUIElementStyle::internal_GetFixedHeight(ScriptGUIElementStyle* nativeInstance, bool* value)
	{
		*value = nativeInstance->mElementStyle->fixedHeight;
	}

	void ScriptGUIElementStyle::internal_SetFixedHeight(ScriptGUIElementStyle* nativeInstance, bool value)
	{
		nativeInstance->mElementStyle->fixedHeight = value;
	}
}