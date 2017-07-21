
#include <iostream>
#include <string>
#include <vector>
#include <list>



class Node
{
private:
	//Did not know that those were introduced in c++11
	static const uint8_t MAXSIZE = (('Z' - 'A') + ('z' - 'a') + 1);
	typedef std::vector< Node* > Nodes;

	Nodes m_Children;
	bool m_bIsTerminal;


	const uint8_t Index( char cFrom ) const throw()
	{
		if (cFrom >= 'a')
			return (cFrom - 'a' + ('Z' - 'A' + 1));
		return cFrom - 'A';
	}

public:
	Node() throw()
	:
		m_Children( MAXSIZE, 0 ),
		m_bIsTerminal( false )
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
		if ( sWord.size() == 0 )
		{
			m_bIsTerminal = true;
			return true;
		}

		//Check if we have the next letter as a child already
		Node* nextChild = m_Children[ Index(sWord[0]) ];
		if ( nextChild )
		{
			//if we have it proceed with rest of string
			return nextChild->insert( sWord.substr(1) );
		}
		else
		{
			//if we dont have it, add it and proceed with rest of string
			nextChild = new Node();
			m_Children[Index(sWord[0])] = nextChild;
			return nextChild->insert( sWord.substr(1) );
		}
	}

	bool remove( const std::string& sWord ) throw()
	{

	}

	bool isWord( const std::string& sWord ) const throw()
	{
		//emtpy word or end of word
		if ( sWord.size() == 0 )
		{
		   	return m_bIsTerminal;
		}

		Node* nextChild = m_Children[ Index(sWord[0]) ];
		if ( nextChild )
		{
			return nextChild->isWord( sWord.substr(1) );
		}
		else
		{
			return false;
		}
	}

	int getHeight() const throw()
	{
		//This method includes the height including root node.
		uint32_t nRes = 0;
		for ( int i = 0; i < MAXSIZE; i++ )
		{
			Node* nextNode = m_Children[i];

			if ( nextNode )
			{
				int subRes = nextNode->getHeight();
				if ( subRes > nRes ) nRes = subRes;
			}
		}
		return ++nRes;
	}
	
};


int main()
{
	Node dictionary;

	//dictionary.printIndexTable();
	std::list<std::string> testSet;
	std::list<std::string>::iterator It;

	testSet.push_back("ada");
	testSet.push_back("adaa");
	testSet.push_back("adab");
	testSet.push_back("aday");
	testSet.push_back("adadada");

	for ( It = testSet.begin(); It != testSet.end(); It++ )
	{
		dictionary.insert( *It );
	}

	dictionary.remove("ada");

	testSet.push_back("blah");
	testSet.push_back("adada");

	for ( It = testSet.begin(); It != testSet.end(); It++ )
	{
		std::cout << *It << " : " << (dictionary.isWord( *It )?"\033[1;32mis word\033[0m":"\033[1;31mis not word\033[0m") << std::endl;
	}


	std::cout << "Three height: " << dictionary.getHeight() << std::endl;

	return 0;
}


