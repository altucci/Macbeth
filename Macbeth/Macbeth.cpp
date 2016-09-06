// Macbeth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;



/*-----------------------------------------------------
	Custom sort function in order to display the
	unique words in order of their count. If the
	count is the same, the unique words will stay
	in alphabetical order.
-----------------------------------------------------*/
bool sort_by(const pair<string, int>& a, const pair<string, int>& b)
{
	if (a.second == b.second)
		return a.first < b.first;
	else
		return a.second < b.second;
}



/*-----------------------------------------------------
bool function specifying all involved delimeters
-----------------------------------------------------*/
bool IsDelimeter(char c)
{
	if (c == ' ' || 
		c == ',' || 
		c == '.' || 
		c == '?' || 
		c == ':' || 
		c == ';' || 
		c == '!' || 
		c == '&' || 
		c == '-' || 
		c == '[' || 
		c == ']' || 
		c == '\'')
		return true;
	else
		return false;
}



int main()
{
	//load in file
	ifstream in("macbeth.txt");

	//return will failure if file does not exist
	if (!in)
	{
		cerr << "Could not open macbeth.txt." << endl << endl;
		system("pause");
		return EXIT_FAILURE;
	}



	int i, j, nCount;
	string str, strLine, strWord;
	map<string, int> Words;
	vector<pair<string, int>> vecWords;



	//read in every line of the text and add it to the string 'str'
	str = "";
	while (getline(in, strLine))
	{
		str += strLine + " ";
	}

	//make every character lowercase
	transform(str.begin(), str.end(), str.begin(), tolower);



	//loop through every character
	i = 0;
	while (i < str.length())
	{
		j = i;

		//increment through all adjacent non-delimeters
		while (i < str.length() && !IsDelimeter(str[i]))
			i++;

		//save substring of all adjacent non-delimeters (i.e. this would represent one word)
		strWord = str.substr(j, i - j);

		//filter out all words not greater than 4 characters in length
		if (strWord.length() > 4)
		{
			if (Words.find(strWord) != Words.end())       //if word already exists, don't add it to the map, just increment its count.
			{
				nCount = Words.at(strWord);
				Words[strWord] = ++nCount;
			}
			else                                          //else, add it to the map and assign it a count of 1.
			{
				Words.insert(map<string, int>::value_type(strWord, 1));
			}
		}

		//increment through all adjacent delimeters
		while (i < str.length() && IsDelimeter(str[i]))
			i++;
	}



	//copy all map elements to a vector for easier sorting
	copy(Words.begin(), Words.end(), back_inserter(vecWords));
	
	//sort vector by count
	sort(vecWords.begin(), vecWords.end(), sort_by);



	//display all elements in vector
	for (i = 0; i < vecWords.size(); i++)
	{
		cout << vecWords[i].first << " - " << vecWords[i].second << endl;
	}

	//display the answer to the question
	cout << endl << "The second most common word longer than 4 characters in macbeth.txt is " << vecWords[vecWords.size() - 2].first << ". It appears " << vecWords[vecWords.size() - 2].second << " times." << endl << endl;



	system("pause");
    return 0;
}
