
#include <iostream>
#include <string>
#include <vector>
#include <list>



//The class usses a "cache" of rows for each three level.
//This will make it a lot more effective in terms of add/remove/isWord, but will consume more memory
class Node
{
private:
	//Did not know that those were introduced in c++11
	static const uint8_t MAXSIZE = (('Z' - 'A') + ('z' - 'a') + 1);

	typedef std::vector< Node* > Nodes;

	//Holds an "array" of children
	Nodes m_Children;

	//Saves information if the node is an end of a word.
	bool m_bIsTerminal;


	//This is simple indexer function which returns consecutive numbers from 0 to N so we can
	//access the "array".
	const uint8_t Index( char cFrom ) const throw()
	{
		if (cFrom >= 'a')
			return (cFrom - 'a' + ('Z' - 'A' + 1));
		return cFrom - 'A';
	}

	//Check if the node has any children
	bool HasChildren() const throw()
	{
		for ( int i = 0; i < MAXSIZE; i++ )
		{
			if ( m_Children[i] )
			{
				return true;
			}
		}
		return false;
	}

public:
	//We initialize the children with 0 (not existing at the moment)
	//and each node starts as non-terminal
	Node() throw()
	:
		m_Children( MAXSIZE, 0 ),
		m_bIsTerminal( false )
	{
	}

	//Helper funciton to print the index function.
	//it is a dumb way to verify the index integrity
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

	/** inserts a word in the tree (or subtree)
	 * @sWord - word to be inserted
	 * 
	 * returns true if string is exhausted
	 */
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

	/** removes a word in the tree (or subtree) and
	 * takes care for memory deletion
	 *
	 * @sWord - word to be removed
	 * 
	 * returns true if string is exhausted
	 */
	bool remove( const std::string& sWord ) throw()
	{
		//String exhausted, we need to set this node as non-terminal
		//Deletion should be handled from outside the node.
		if ( sWord.size() == 0 )
		{
			m_bIsTerminal = false;
			return true; //return end of processing
		}

		Node* nextChild = m_Children[ Index(sWord[0]) ];
		if ( nextChild )
		{
			if ( nextChild->remove( sWord.substr(1) ) )
			{
				if ( ! nextChild->HasChildren() )
				{
					m_Children[ Index(sWord[0]) ] = 0;
					delete nextChild;
				}
			}
			
		}
	}

	/** Checks if word is present in dictionary
	 *
	 * @sWord - word to be checked
	 * 
	 * returns true the word is present in the three (and terminated)
	 */
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

	///Returns the height of the tree including root node (will be max word +1)
	int getHeight() const throw()
	{
		//This method prints the height including root node.
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

	dictionary.remove("adadada");

	std::cout << "Three height (after deletion): " << dictionary.getHeight() << std::endl;

	return 0;
}


