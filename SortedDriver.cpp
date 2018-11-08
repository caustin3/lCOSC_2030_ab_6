// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>       
using namespace std;
using std::cout;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double> getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string> getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double mostIsolated(vector<double> & number)
{
	if (number.size() == 1)
	{
		return number[1];
	}

	double number_i = 0, biggest_R = 0, biggest_L = 0, diff_R = 0, diff_L = 0, first = 0, second = 0, third = 0;
	int index_number = 0;
	for (int index = 1; index < number.size()-1; index++)
	{	
		first = number[index - 1];
		second = number[index ];
		third = number[index + 1];
		double new_L_biggest = second - first, new_R_biggest = third - second, newI = 0;
		if (index == 1)
		{
			newI = new_L_biggest;
		}
		else
		{
			newI = min(new_L_biggest, new_R_biggest);
		}

		if (newI > number_i && new_L_biggest > new_R_biggest)
		{
			index_number = index - 1;
			number_i = newI;
		}
		else if (newI > number_i && new_L_biggest == new_R_biggest)
		{
			index_number = index;
			number_i = newI;
		}
	}
	return number.at(index_number);
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int unmatched(list<string> & A, list<string> & B)
{
	A.begin();
	B.begin();
	int count = 0, index_top = 0;
	bool is_in_b = false, done = false;
	string temp_a,temp_b;
	
	index_top = A.size() + B.size();
	temp_b = B.front();
	temp_a = A.front();
	for (int index = 0; index < index_top; index++)
	{
		
		if (temp_a.compare(temp_b) ==0)
		{
			A.push_back(A.front());
			A.pop_front();			
			if (temp_a.compare(temp_b) ==0)
			{				
				B.push_back(B.front());
				B.pop_front();
				temp_b = B.front();
			}
			else
			{
				count++;
				A.push_back(A.front());
				A.pop_front();
				temp_a = A.front();
			}
		}
		else
		{
			B.push_back(B.front());
			B.pop_front();
			temp_b = B.front();
			if (temp_a.compare(temp_b) == 0)
			{
				B.push_back(B.front());
				B.pop_front();
				temp_b = B.front();
			}
			else
			{
				count++;
				A.push_back(A.front());
				A.pop_front();
				temp_a = A.front();
			}
		}
		
	}
	
	return count;
}

int main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
