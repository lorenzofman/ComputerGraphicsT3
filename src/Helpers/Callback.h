#pragma once
#include <algorithm>
#include <functional>
#include <vector>

/* Generic class to handle multiple callback register/deregister */
template <typename ... _Args>
class Callback
{
	public:

	int Register(std::function<void(_Args ...)> func)
	{
		listeners.push_back(func);
        deleted.push_back(false);
		return index++;
	}

	void Deregister(int id)
	{
	    if (id >= 0 && id <= deleted.size())
	    {
	        deleted[id] = true;
	    }
	}

	void Invoke(_Args ... args)
	{
		for (int i = listeners.size() - 1; i >= 0; i--)
		{
            if (!deleted[i])
            {
			    listeners[i](args ...);
		    }
		}
	}
	private:

	std::vector<std::function<void(_Args ...)>> listeners;
	std::vector<bool> deleted;
	int index = 0;
};
