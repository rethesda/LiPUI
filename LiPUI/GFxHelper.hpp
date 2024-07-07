#pragma once
#include "ColorCoding.h"
#include "f4se/ScaleformValue.h"

namespace GFxHelper
{
	// delimiter is '.' (dot)
	bool GetNestedMember(GFxValue* root, const std::string& path, GFxValue& out)
	{
		if (!root)
			return false;
		size_t start = 0;
		GFxValue* current = root;
		GFxValue m;
		do
		{
			const size_t pos = path.find('.', start);
			//_MESSAGE("pos = %d when start = %d", pos, start);
			if (pos == std::string::npos)
			{
				if (!current)
					return false;
				const std::string member = path.substr(start);
				//_MESSAGE("get last member %s", member.c_str());
				return current->GetMember(member.c_str(), &out);
			}
			const std::string member = path.substr(start, pos-start);
			//_MESSAGE("get value of member %s", member.c_str());
			const bool res = current->GetMember(member.c_str(), &m);
			if (!res)
			{
				_MESSAGE("Failed");
				return false;
			}
			current = &m;
			start = pos + 1;
		}
		while(true);
	}

#include "f4se/GameSettings.h"
	UInt32 GetTextColor()
	{
		UInt32 red;
		UInt32 green;
		UInt32 blue;
		Setting* colorR = GetINISetting("iHUDColorR:Interface");
		Setting* colorG = GetINISetting("iHUDColorG:Interface");
		Setting* colorB = GetINISetting("iHUDColorB:Interface");
		if (colorR)
			red = colorR->data.u32;
		else
		{
			_MESSAGE("R: None");
			return ColorCoding::DefaultColor;
		}

		if (colorG)
			green = colorG->data.u32;
		else
		{
			_MESSAGE("G: None");
			return ColorCoding::DefaultColor;
		}

		if (colorB)
			blue = colorB->data.u32;
		else
		{
			_MESSAGE("B: None");
			return ColorCoding::DefaultColor;
		}

		return red << 16 | green << 8 | blue;
	}
	
}
