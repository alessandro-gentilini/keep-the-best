#include <libgen.h>

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

size_t number_of_distinct_chars(std::string s)
{
	return std::distance(s.begin(), std::unique(s.begin(),s.end()));
}

bool entropy(const std::string& a, const std::string& b)
{
	std::string base_a( basename( const_cast<char*>(a.c_str()) ) );
	std::string base_b( basename( const_cast<char*>(b.c_str()) ) );
	bool r = base_a.length() < base_b.length();
	if ( base_a.length() == base_b.length() ) {
		r = number_of_distinct_chars(base_a) < number_of_distinct_chars(base_b);
	} 
	return r;
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
			auto it = std::max_element(names.begin(),names.end(),entropy);
			std::string the_best = *it;
			names.erase(it);
			std::cout << "keep\t" << the_best << "\n";
			for ( auto n : names ) {
				std::cout << "\trm\t" << n << "\n";
			}
			std::cout << "\n";
		}
	}

	return 0;
}