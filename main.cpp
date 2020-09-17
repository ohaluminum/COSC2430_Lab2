#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"

using namespace std;

struct word
{
    string info = "";
    word* next = nullptr;
};

class sentence
{
private:
    word* head;
    word* curr;

public:
    //Constructor
    sentence()
    {
        head = nullptr;
        curr = nullptr;
    }

    //Getter function
    word* getCurr()
    {
        return curr;
    }

    word* getHead()
    {
        return head;
    }

    //Setter function
    void setCurr(word* ptr)
    {
        curr = ptr;
        return;
    }

    void setHead(word* ptr)
    {
        head = ptr;
        return;
    }

    //Add new word at the end of the linked list
    void addWord(string newWord)
    {
        //1.Create a temperary word
        word* temp = new word;

        //2.Fill the data
        temp->info = newWord;

        //3.Update the pointer
        temp->next = nullptr;

        if (head == nullptr)
        {
            head = temp;
        }
        else
        {
            //3.1.Create a previous word
            word* prev = new word;
            prev = head;

            //3.2.Move to the previous position
            while (prev->next != nullptr)
            {
                prev = prev->next;
            }

            //3.3.Link together
            prev->next = temp;
        }

        return;
    }

    //Print the linked list
    void printReverse(word* curr, ofstream &outFS)
    {
        if (curr == nullptr)
        {
            return;
        }
        else
        {
            printReverse(curr->next, outFS);
            outFS << curr->info << " ";
        }
    }
};

//Create a function to count number of space in a string
int countSpace(string str)
{
    int counter = 0;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
        {
            counter++;
        }
    }

    return counter;
}


int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input3.txt";
    string output = "output3.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    //Open the input file and output file
    inFS.open(input);
    outFS.open(output);

    try
    {
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        string line;
        string subLine;
        int numOfSpace;
        sentence wholeSentence;

        //Read input file
        while (getline(inFS, line))
        {
            //Check if the line is empty (if so continue to read next line)
            if (line.empty())
            {
                continue;
            }

            numOfSpace = countSpace(line);

            //If there is no space in one line, there is only one word in this line
            if (numOfSpace == 0)
            {
                wholeSentence.addWord(line);
            }
            else
            {
                //Clear input string stream
                inSS.clear();

                //Using input string stream to read problem line
                inSS.str(line);

                for (int i = 0; i < numOfSpace; i++)
                {
                    getline(inSS, subLine, ' ');
                    wholeSentence.addWord(subLine);
                }

                getline(inSS, subLine);
                wholeSentence.addWord(subLine);
            }
        }

        wholeSentence.setCurr(wholeSentence.getHead());

        wholeSentence.printReverse(wholeSentence.getCurr(), outFS);

    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    //Close all files
    inFS.close();
    outFS.close();
    
    return 0;
}