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

	template<typename KeyT, typename T>
	inline void cache_t<KeyT, T>::emplace(KeyT element)
	{
		T repetition = ++cache_[element];

		// seek element in list
		typename std::list<std::pair<KeyT, T>>::iterator iter_elem = std::find_if(objlist_.begin(), objlist_.end(), [&element](const std::pair<KeyT, T>& temp_p) { return element == temp_p.first; });

		// seek repetition of an element 
		typename std::list<std::pair<KeyT, T>>::iterator iter_num = std::find_if(objlist_.begin(), objlist_.end(), [&repetition](const std::pair<KeyT, T>& temp_p) { return repetition >= temp_p.second; });

		if (iter_elem == objlist_.end())
		{
			if (iter_num != objlist_.end())
			{
				objlist_.emplace(iter_num, std::pair<KeyT, T>(element, cache_[element]));
				objlist_.pop_back();
			}
		}
		else // have found element
		{
			++iter_elem->second;
			++hits_;

			if (iter_num != objlist_.end())
			{
				objlist_.emplace(iter_num, std::pair<KeyT, T>(element, cache_[element]));
				objlist_.erase(iter_elem);
			}
		}
	}

}