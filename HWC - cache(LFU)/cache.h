#pragma once

#include <unordered_map>
#include <list>
#include <algorithm>


namespace caches
{

	template<typename KeyT, typename T = size_t>
	class cache_t
	{
	private:
		std::unordered_map<KeyT, T> cache_; // value , repetition
		std::list<std::pair<KeyT, T>> objlist_;

		size_t size_;
		size_t hits_ = 0;

	public:
		cache_t(size_t size) : size_(size)
		{
			objlist_.resize(size);
			std::for_each(objlist_.begin(), objlist_.end(), [](std::pair<KeyT, T>& obj)
				{
					obj.first = std::numeric_limits<KeyT>::min();
				});
		}
		void emplace(KeyT element);
		size_t GetHits() { return hits_; }

	};

}

