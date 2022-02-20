/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "DataStructures.h"

namespace MachGL {

	class Cache {

		private:
			static std::vector<CachedInstance> s_cache;

		public:
			inline static std::vector<CachedInstance>& getCache() { return s_cache; }
			inline static void pushToCache(const CachedInstance& instance) { s_cache.push_back(instance); }
			static void eraseFromCache(const uint32_t& address);
			static bool checkInCache(const uint32_t& address);
			inline static size_t getSize() { return s_cache.size(); }
	};
}
