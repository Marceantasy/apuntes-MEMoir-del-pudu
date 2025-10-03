using key = tuple<int, int, int>; // define a key type

using bits = bitset<sizeof(key) * 8>;
unordered_map<bits, int> hashmap;

// hashmap[*((long long *)&hash)] = value;