#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

bool cmp(const std::string &a, const std::string &b)
{
	return a.size() < b.size();
}

int main(int, char**)
{
	typedef std::string hash_t;
	std::multimap< hash_t, std::string > files;
	hash_t hash;
	std::set< hash_t > hashes;
	std::string line, name;
	while ( std::getline(std::cin, line) ) {
		size_t w = line.find(' ');
		if ( w == std::string::npos ) continue;
		hash = line.substr(0,w);
		name = line.substr(w+1);
		files.insert(std::make_pair(hash,name));
		hashes.insert(hash);
	}

	for ( auto h : hashes ) {
		if ( files.count(h) > 1 ) {
			auto bounds = files.equal_range(h);
			std::vector<std::string> names;
			for ( auto it = bounds.first; it != bounds.second; ++it ) {
				names.push_back(it->second);
			}
			names.erase(std::max_element(names.begin(),names.end(),cmp));
			for ( auto n : names ) {
				std::cout << "rm " << n << "\n";
			}
		}
	}

	return 0;
}