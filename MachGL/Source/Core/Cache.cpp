/*

Mach::GL (Alpha)

*/

#include "../../Headers/Core/Cache.h"

namespace MachGL {

	std::vector<CachedInstance> Cache::s_cache = std::vector<CachedInstance>();

	void Cache::eraseFromCache(const uint32_t& address) {

		for (size_t i = 0; i < getSize(); i++) {

			if (s_cache[i].cacheAddress == address) s_cache.erase(s_cache.begin() + i);
		}
	}

	bool Cache::checkInCache(const uint32_t& address) {

		if (s_cache.size() > 0) {

			for (size_t i = 0; i < getSize(); i++) {

				if (s_cache[i].cacheAddress == address) return true;
				return false;
			}
		}

		return false;
	}
}
