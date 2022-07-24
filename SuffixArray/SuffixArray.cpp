#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

char* a=new char[10010]; //global array to store the chars with Naive mthod
void input(char arr[],int v) //function to enter values of (a) array from main
{
    for(int i=0;i<v;i++)
        a[i]=arr[i];
}
bool cmp(int i,int j) //compare function using strcmp to sort the suffixes
{
    return strcmp(a+i,a+j)<0;
}
int* function1(char* arr,int n) //Naive method
{
    input(arr,n);
    int* ind = new int[n]; // construct an indices array to store the indices of the chars
    for(int i=0;i<n;i++)
        ind[i]=i;
    sort(ind,ind+n,cmp); //sort the indices array by using cmp functions as we showed before
    return ind; // return the sorted indices  suffix array
    delete[] a;
    delete[] ind;
}
struct suffix // a struct to save data about the array such as indix and its rank
{
    int ind; // the current indix
    int ranks[2]; // // store ranks and next rank
};
bool comparison(suffix a,suffix b)// used to compare between two suffixes and returns 1 if the first one smaller than the second one
{
    if(a.ranks[0]==b.ranks[0])
    {
        if(a.ranks[1]<b.ranks[1])
            return 1;
        else return 0;
    }
    else if(a.ranks[0]<b.ranks[0])
        return 1;
    else return 0;
}
int* function2(char arr[],int siz)// prefix doubling function
{
    suffix suffixesArray[siz]; // stroe suffixes and their indecies with ranks
    for(int i=0;i<siz;i++)
    {
        suffixesArray[i].ind=i;
        suffixesArray[i].ranks[0]= arr[i]-'a'; //put rank of them by substract it from 'a' to make it easy
        if(i+1<siz)
            suffixesArray[i].ranks[1]=arr[i+1]-'a';
        else
            suffixesArray[i].ranks[1]= -1; // it means that we are outside of the size so put it -1
    }
    sort(suffixesArray,suffixesArray+siz,comparison);// now we sort the suffixes according to first 2 chars and we need to complete 4 then 8 and so on
    int indecies[siz]; // used to get the indices in suffixes from the original index and map it to get next suffix
    for(int i=4;i<2*siz;i*=2)
    {
        int rk=0; //assign the rank and index of first suffix
        int oldRank=suffixesArray[0].ranks[0];
        suffixesArray[0].ranks[0]=rk;
        indecies[suffixesArray[0].ind]=0;
        for(int j=1;j<siz;j++)
        {
            if(suffixesArray[j].ranks[0]==oldRank && suffixesArray[j].ranks[1]==suffixesArray[j-1].ranks[1]) // If first and next ranks are same as that of previous suffix in array then assign the same new rank to this suffix
            {
                oldRank=suffixesArray[j].ranks[0];
                suffixesArray[j].ranks[0]=rk;
            }
            else //otherwise increment the rank only
            {
                oldRank=suffixesArray[j].ranks[0];
                suffixesArray[j].ranks[0]=++rk;
            }
            indecies[suffixesArray[j].ind]=j;
        }
        for(int j=0;j<siz;j++) // now we need to assign the next ranks of every suffix
        {
            int nInd=suffixesArray[j].ind+(i/2); // put the start index of the next indexes array
            if(nInd<siz)
                suffixesArray[j].ranks[1]=suffixesArray[indecies[nInd]].ranks[0]; //put the index of original one in the indicies array into next rank
            else suffixesArray[j].ranks[1]= -1; // it means there is no next rank
        }
        sort(suffixesArray,suffixesArray+siz,comparison); // then sort suffixes according to first (i) chars
    }
    int* sortedSuffixArray=new int[siz]; // the sorted array
    for(int j=0;j<siz;j++)
        sortedSuffixArray[j]=suffixesArray[j].ind; //coping the suffix array indices into the sorted array then return it
    return sortedSuffixArray;
    delete[] sortedSuffixArray;
}
void write(int* arr,int n,char* path)
{
    FILE* file=fopen(path,"wb");
    for(int i=0;i<n;i++)
        fprintf(file,"%i\n",arr[i]);
    fprintf(file,"%s\n","--------------------------------");
    fclose(file);
}
int main()
{
    char* seq=new char[10010], *arr=new char[100]; // define two dynamic arrays one for the sequence and the other for line by line
    FILE* file=fopen("genome.txt","r"); //opening the file
    fscanf(file,"%[^\n\r]",seq);
    seq[0]=0;// ignore the first line (its id)
    while(strlen(seq)<10000)
    {

        fscanf(file,"%s",arr);
        strcat(seq,arr);
    }
    char* st ="basketball";
    int n = strlen(seq);
    int* F1=function1(seq,n); // call naive method (O(n^2logn)),time 5.875s
    int* F2= function2(seq,n); // call prefix method (O(nlogn)),time 5.78s
    delete[] seq;
    write(F1,n,"output1.txt");
    write(F2,n,"output2.txt");
    delete[] F1;
    delete[] F2;
    return 0;
}
