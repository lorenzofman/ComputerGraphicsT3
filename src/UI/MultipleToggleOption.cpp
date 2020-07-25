#include "MultipleToggleOption.h"

MultipleToggleOption::MultipleToggleOption(Float2 pos, Float2 size, const std::vector<std::string> &options, const std::vector<int> &initialSelected)
{
	int i = 0;
	for (auto& option : options)
	{
		buttons.push_back(new TextButton(option, pos - size * 0.5f, pos + size * 0.5f));
		int idx = i++;
		callbacks.push_back(buttons[buttons.size() - 1]->ClickCallback.Register([this, idx](Int2 unused)
		{
			this->OnButtonClick(idx);
		}));
		selected.push_back(false);
		pos.x += size.x;
	}

	for (auto idx : initialSelected)
	{
		selected[idx] = true;
	}
}

void MultipleToggleOption::Draw(Color primary, Color alt) const
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (selected[i])
		{
			buttons[i]->Draw(alt, primary);
		}
		else
		{
			buttons[i]->Draw(primary, alt);
		}
	}
}

void MultipleToggleOption::OnButtonClick(int button)
{
	OptionSelected.Invoke(button);
	selected[button] = !selected[button];
}
