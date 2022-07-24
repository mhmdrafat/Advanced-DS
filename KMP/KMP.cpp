#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
    int failureLink;
};
Node* preProcessing(char* pattern)//function to return the maxLength of a failure link and use it at findKMP array
{
    int n = strlen(pattern);
    Node* nodes = new Node[n]; //create array of nodes
    nodes[0].failureLink=0;//set first failure link of the array into 0 as there is no match
    int maxLen=0;//to get maximum length of the failure link array
    for(int i=1; i<n;)
    {
        if(pattern[i]==pattern[maxLen])//compare between characters of pattern and text if they are match then update maxLength and i value to check next character
        {
            maxLen++;
            nodes[i].failureLink=maxLen;//then update the value of failure link of this node into maxLen of it
            i++;
        }
        else//it means they are not match
        {
            if(maxLen==0)
            {
                nodes[i].failureLink=0;//as they don't match then update node's failure link value into 0
                i++; //update i value to check next character
            }
            else
            {
                maxLen=nodes[maxLen-1].failureLink;//back and update maxLen value to recheck the characters
            }
        }
    }
    return nodes;//then return nodes array
    delete[] nodes;// and delete it
}
void findKMP(char* pattern, char* txt)
{
    int patternSize = strlen(pattern);
    int txtSize = strlen(txt);
    int founds[txtSize]; //array to store indexes which are found
    Node* node;
    node = preProcessing(pattern); // Preprocess the pattern (calculate failureLink array for each node)
    int i=0,j=0,k=0; // indexes for txt, pattern and founds arrays
    while (i < txtSize)
    {
        if (pattern[j] == txt[i]) //they matches each other
        {
            // then update the indexes values to check next characters
            j++;
            i++;
        }
        if (j == patternSize)
        {
            //once j reaches patter's size then the pattern totally found
            founds[k]=i-j; //then return its index by substracting i (the biggest) from j (the smallest)
            k++;
            j = node[j - 1].failureLink; //back and update pattern's index value to recheck the characters
        }
        else if (i < txtSize && pattern[j] != txt[i])//it means ther is no match so update j or i value according to j value
        {
            if (j != 0)//then update it back to the old value
                j = node[j - 1].failureLink;
            else // then update i value to check the next character
                i = i + 1;
        }
    }
    for(int i=0; i<k; i++) //printing indexes values
    {
        if(i==0 && k>1)
            cout<<"Pattern found at indixes: ";
        else if(i==0 && k==1)
            cout<<"Pattern found at indix: ";
        cout<<founds[i]<<" ";
    }

}
int main()
{
    char txt[] = "AAACAAAA";
    findKMP("AAC",txt);
    return 0;
}
