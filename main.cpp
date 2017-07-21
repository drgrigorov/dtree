
#include <iostream>
#include <string>



class Node
{
private:
	int Index( char cFrom ) const throw()
	{
		if (cFrom >= 'a')
			return (cFrom - 'a' + ('Z' - 'A' + 1));
		return cFrom - 'A';
	}
public:
	void printIndexTable() const throw()
	{
		for (char c = 'A'; c <= 'Z'; c++)
		{
			std::cout << c << " : " << int(c) << " -> " << Index(c) << std::endl;
		}
		for (char c = 'a'; c <= 'z'; c++)
		{
			std::cout << c << " : " << int(c) << " -> " << Index(c) << std::endl;
		}
	}

	bool insert( const std::string& sWord ) throw() { return false; }
	bool remove( const std::string& sWord ) throw() { return false; }
	bool isWord( const std::string& sWord ) const throw() { return false; }
	int getHeight() const throw() { return 0;}
};


int main()
{
	Node dictionary;

	//dictionary.printIndexTable();

	dictionary.insert("ada");
	dictionary.insert("adaa");
	dictionary.insert("adab");
	dictionary.insert("aday");
	dictionary.insert("adadada");
	dictionary.remove("ada");

	std::cout << "adaa : " << (dictionary.isWord("adaa")?"is word":"is not word") << std::endl;
	std::cout << "adaa : " << (dictionary.isWord("adab")?"is word":"is not word") << std::endl;
	std::cout << "adaa : " << (dictionary.isWord("ada")?"is word":"is not word") << std::endl;
	std::cout << "Three height: " << dictionary.getHeight() << std::endl;

	return 0;
}


