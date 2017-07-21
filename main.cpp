
#include <iostream>
#include <string>
#include <vector>



class Node
{
private:
	//Did not know that those were introduced in c++11
	static const uint8_t MAXSIZE = (('Z' - 'A') + ('z' - 'a') + 1);
	typedef std::vector< Node* > Nodes;

	Nodes m_Children;


	const uint8_t Index( char cFrom ) const throw()
	{
		if (cFrom >= 'a')
			return (cFrom - 'a' + ('Z' - 'A' + 1));
		return cFrom - 'A';
	}

public:
	Node() throw()
	:
		m_Children( MAXSIZE, 0 )
	{
	}

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

	bool insert( const std::string& sWord ) throw()
	{
		//emtpy word or end of word
		if ( sWord.size() == 0 ) return false;

		Node* nextChild = m_Children[ Index(sWord[0]) ];
		if ( nextChild )
		{
			return nextChild->insert( sWord.substr(1) );
		}
		else
		{
			nextChild = new Node();
			m_Children[Index(sWord[0])] = nextChild;
			return nextChild->insert( sWord.substr(1) );
		}
	}

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


