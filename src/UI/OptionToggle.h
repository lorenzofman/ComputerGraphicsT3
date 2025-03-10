#pragma once

#include <string>
#include "../Helpers/Callback.h"
#include "../Primitives/Float2.h"
#include "TextButton.h"

class OptionToggle
{
	public:
	Callback<int> OptionSelected;
	OptionToggle(Float2 pos, Float2 size, const std::vector<std::string>& options, int initial = 0);
	void Draw(Color primary, Color alt) const;
	private:
	std::vector<int> callbacks;
	std::vector<TextButton*> buttons;
	void OnButtonClick(int button);

	int lastSelected;
};