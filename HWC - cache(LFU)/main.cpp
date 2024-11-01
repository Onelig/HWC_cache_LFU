#include <iostream>
#include "cache.h"

int main()
{
	size_t s_cache, n_elements;
	std::cin >> s_cache >> n_elements;
	caches::cache_t<int> cache_obj(n_elements);

	for (size_t i = 0; i < s_cache; ++i)
	{
		int value;
		std::cin >> value;
		cache_obj.emplace(value);
	}

	std::cout << cache_obj.GetHits();

	return 0;
}