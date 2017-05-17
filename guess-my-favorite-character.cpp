#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class CharacterTree
{
    vector<string> myCharacterTree;
    int nCount;

public:
    CharacterTree( void );
    void insert( string, int );
    void pinorder( void );
    void pinorder_helper( int );

    string retrieve( int );
    void print_tree( void );
};

CharacterTree::CharacterTree( void ) // constructor
{
    int i;

    myCharacterTree.clear();
    myCharacterTree.push_back("Captain America");
    for (i = 0; i < 5; i++)
        myCharacterTree.push_back(" ");
    nCount = 0;
}

string CharacterTree::retrieve( int index )
{
    return myCharacterTree.at(index);
}

void CharacterTree::insert( string s, int index )
{
    ++nCount;
    int resizeTo = nCount + (3*index);

    if (((unsigned)(2*index)) >= (myCharacterTree.size())) // comparing 2*index because 2*index is the largest number that will be accessed at all times
    {
        for (int i=0; i < resizeTo; i++)
            myCharacterTree.push_back(" ");
    }

    myCharacterTree.at(index) = s;
}

void CharacterTree::pinorder( void )
{
    pinorder_helper( 1 );
    cout << endl;
}

void CharacterTree::pinorder_helper( int index )
{
    cout << "Printing tree inorder:" << endl;
    if ((myCharacterTree.at(2*index).compare(" ") != 0) && (myCharacterTree.at(2*index+1).compare(" ") != 0)) // continue recursive call... base case... then we want to print it out
    {
        pinorder_helper( (2*index) ); // go left
        cout << myCharacterTree[index-1] << " ";
        pinorder_helper( (2*index)+1 ); // go right
    }
}

void CharacterTree::print_tree( void )
{
    cout << "Printing tree:" << endl;
    for (vector<string>::const_iterator i = myCharacterTree.begin(); i != myCharacterTree.end(); ++i)
    {
        cout << *i << " ";
    }
}

int main(int argc, char **argv, char **envp)
{
    string answer = "y";
    string treeAnswer;
    string treeGuess;
    string treeCharName;
    string treeQuestionDistinguish;
    CharacterTree t = CharacterTree();

    int index;

    while ( answer.compare("y") == 0 ) // While the user is thinking of a character
    {
        cout << endl << "Are you thinking of your favorite character? (y/n) ";
        getline( cin, answer );
        if ( answer.compare("y") == 0 ); // if the answer is "y"
        else return 0;

        index = 1; // Start at the root

        while ( ((t.retrieve((2*index)-1)).compare(" ") != 0) && ((t.retrieve(2*index)).compare(" ") != 0) ) // While left child is not a leaf node...
        {
            cout << t.retrieve(index-1) << "? (y/n) "; // Ask an identifying question
            getline( cin, treeAnswer );

            if (treeAnswer.compare("n") == 0) // If user responds no to question in current node
            {
                index = ( 2 * index ); // follow left child
            }
            else
            {
                index = ( 2 * index ) + 1; // follow right child
            }
        }

        // We are now at a leaf node
        // Make a guess
        cout << "Is it " << t.retrieve(index-1) << "? (y/n) ";
        treeGuess = t.retrieve(index-1);
        getline( cin, treeAnswer );
        if ( treeAnswer.compare("n") == 0 )
        {
            cout << "What is the character's name? ";
            getline( cin, treeCharName );
            cout << "What question would distinguish " << treeCharName << " from " << t.retrieve(index-1) << "? ";
            getline( cin, treeQuestionDistinguish );
            cout << "If the character were " << treeCharName << ", what would the answer be? {y/n) ";
            getline ( cin, treeAnswer );

            if ( treeAnswer.compare("y") == 0 )
            {
                t.insert( treeGuess, ((2*index)-1) ); // add previous (incorrect) character name of leaf node to LEFT
                t.insert( treeQuestionDistinguish, index-1 ); // insert question into CURRENT node
                t.insert( treeCharName, ((2*index)) ); // insert NEW (correct) character name to the RIGHT
            }
            else
            {
                t.insert( treeGuess, ((2*index)) ); // add previous (incorrect) character name of leaf node to RIGHT
                t.insert( treeQuestionDistinguish, index-1 ); // insert question into CURRENT node
                t.insert( treeCharName, ((2*index)-1) ); // insert NEW (correct) character name to the LEFT
            }
        }
        else if ( treeAnswer.compare("y") == 0 )
        {
            cout << "I rule!" << endl;
        }
        else
        {
            cout << "You didn't enter 'n' or 'y'. Try again." << endl;
            return 0;
        }
    }
}
