#include "OptionToggle.h"

OptionToggle::OptionToggle(Float2 pos, Float2 size, const std::vector<std::string>& options, int initial)
{
	int i = 0;
	lastSelected = initial;
	for (auto& option : options)
	{
		buttons.push_back(new TextButton(option, pos - size * 0.5f, pos + size * 0.5f));
		int idx = i++;
		callbacks.push_back(buttons[buttons.size() - 1]->ClickCallback.Register([this, idx](Int2 unused)
		{
			this->OnButtonClick(idx);
		}));
		pos.x += size.x;
	}
}

void OptionToggle::OnButtonClick(int button)
{
	if (button == lastSelected)
	{
		return;
	}
	OptionSelected.Invoke(button);
	lastSelected = button;
}

void OptionToggle::Draw(Color primary, Color alt) const
{
	int i = 0;
	for (auto& button : buttons)
	{
		if (i++ == lastSelected)
		{
			button->Draw(alt, primary);
		}
		else
		{
			button->Draw(primary, alt);
		}
	}
}
