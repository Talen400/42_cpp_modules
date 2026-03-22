#include <iostream>
#include <fstream>
#include <string>

std::string	replace(const std::string& content, const std::string& s1, const std::string& s2)
{
	std::string result;
	size_t		pos;
	size_t		found;

	pos = 0;
	while ((found = content.find(s1, pos)) != std::string::npos)
	{
		result += content.substr(pos, found - pos);
		result += s2;
		pos = found + s1.size();
	}
	result +=  content.substr(pos);
	return result;
}

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
		istrm.close();
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

	std::string content((std::istreambuf_iterator<char>(istrm)), std::istreambuf_iterator<char>());

	ostrm << replace(content, s1, s2);
	ostrm.close();
	istrm.close();
	return (0);
}

