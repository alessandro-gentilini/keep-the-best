#include <libgen.h>

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

std::string help(const char* myself)
{
    std::ostringstream oss;
    oss << "\nNAME\n";
    oss << "   " << myself << " - prints on stdout a bash script for removing duplicate files.\n";
    oss << "\nSYNOPSIS\n";
    oss << "   " << myself << " < hashes.txt folder\n";
    oss << "\nDESCRIPTION\n";
    oss << "   hashes.txt is the output of an md5deep command\n";
    oss << "   folder     is the folder where to move the duplicate files\n";
    oss << "\nEXAMPLE\n";
    oss << "   The bash script dedup.sh moves all the duplicates found in /home/alex/pdf\n";
    oss << "   (and all its subdir) to /home/alex/dup/\n\n";
    oss << "   md5deep /home/alex/pdf -r | " << myself << " /home/alex/dup/ > dedup.sh\n";
    oss << "\nAUTHOR\n";
    oss << "   Alessandro Gentilini, January 2014.\n";
    oss << "   https://github.com/alessandro-gentilini/keep-the-best\n";
    oss << "\n\n";
    return oss.str();
}

size_t number_of_distinct_chars(std::string s)
{
    return std::distance(s.begin(), std::unique(s.begin(), s.end()));
}

bool entropy(const std::string &a, const std::string &b)
{
    std::string base_a( basename( const_cast<char *>(a.c_str()) ) );
    std::string base_b( basename( const_cast<char *>(b.c_str()) ) );
    bool r = base_a.length() < base_b.length();
    if ( base_a.length() == base_b.length() )
    {
        r = number_of_distinct_chars(base_a) < number_of_distinct_chars(base_b);
    }
    return r;
}

int main(int argc, char **argv)
{
    if ( argc < 2 )
    {
    	std::cout << help(argv[0]);
        return 0;
    }

    typedef std::string hash_t;
    std::multimap< hash_t, std::string > files;
    hash_t hash;
    std::set< hash_t > hashes;
    std::string line, name;
    while ( std::getline(std::cin, line) )
    {
        size_t w = line.find(' ');
        if ( w == std::string::npos ) continue;
        hash = line.substr(0, w);
        name = line.substr(w + 2);
        files.insert(std::make_pair(hash, name));
        hashes.insert(hash);
    }

    std::cout << "#!/bin/bash\n";
    for ( auto h : hashes )
    {
        if ( files.count(h) > 1 )
        {
            auto bounds = files.equal_range(h);
            std::vector<std::string> names;
            for ( auto it = bounds.first; it != bounds.second; ++it )
            {
                names.push_back(it->second);
            }
            auto it = std::max_element(names.begin(), names.end(), entropy);
            std::string the_best = *it;
            names.erase(it);
            std::cout << "#keep\t" << the_best << "\n";
            for ( auto n : names )
            {
                std::cout << "mv \"" << n << "\"" << " ~/pdf-doppioni/\n";
            }
            std::cout << "\n";
        }
    }

    return 0;
}