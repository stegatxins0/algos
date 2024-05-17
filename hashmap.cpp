// {{{ hashmap
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const uint64_t c = (long long)(4e18 * acos(0)) | 71;
	const uint32_t random =
	    chrono::steady_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ random) * c);
	}
};
// }}}

gp_hash_table<char, int, chash> mp;



// for pair
struct phash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
