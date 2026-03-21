#include <iostream>
#include <fstream>
#include <string>

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (1);
	
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	std::ifstream istrm(filename.c_str());
	
	if (!istrm.is_open())
	{
		std::cerr << "Error infile \n";
		return (1);
	}

	std::string outFile = filename + ".replace";
	std::ofstream ostrm(outFile.c_str());
	
	if (!ostrm.is_open())
	{
		std::cerr << "Error Outfile \n";
		return (1);
	}
	/* range (7)
	 *
	 * template <class InputIterator>  
	 * 			string  (InputIterator first, InputIterator last);
	 *
	 * Iterator intern in ifstream:
	 * cplusplus.com/reference/iterator/istreambuf_iterator/
	 *
	 * std::istreambuf_iterator<char>(infile) => begin of string
	 * std::istreambuf_iterator<char>() => end of string
	 */

	std::string content(); 
	return (0);
}



/*
 * argv[2] => filename
 * filename => argv[3]
 *
 */
