#pragma once

#include "TextButton.h"

class MultipleToggleOption
{
	public:
	Callback<int> OptionSelected;
	MultipleToggleOption(Float2 pos, Float2 size, const std::vector<std::string>& options, const std::vector<int> &initialSelected);
	void Draw(Color primary, Color alt) const;
	private:
	std::vector<int> callbacks;
	std::vector<TextButton*> buttons;
	void OnButtonClick(int button);

	std::vector<int> selected;
};