#include <string>
#include <vector>
#include <cmath>

using namespace std;

string RTrim(const string& s, const string& delimiters = " \f\n\r\t\v") {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

string LTrim(const string& s, const string& delimiters = " \f\n\r\t\v") {
	return s.substr(s.find_first_not_of(delimiters));
}

string Trim(const string& s, const string& delimiters = " \f\n\r\t\v") {
	return LTrim(RTrim(s, delimiters), delimiters);
}

void eraseAllSubStr(string & mainStr, const string & toErase)
{
	uint64_t pos = string::npos;
 
	// Search for the substring in string in a loop until nothing is found
	while ((pos  = mainStr.find(toErase) )!= string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length()+1);
	}
}

int WordsToNumbers(string words) {
	if (words.empty()) return 0;
	eraseAllSubStr(words,"de");
	eraseAllSubStr(words,"si");
	words = Trim(words);
	words += ' ';
	
	int number = 0;
	vector<string> singles = {"zero", "zero", "zero","un","unu", "o", "doi", "doua", "doua","trei", "trei", "trei","patru", "patru","patru","cinci", "cinci", "cinci","sase", "sase","sase", "sapte","sapte","sapte","opt","opt","opt", "noua","noua","noua" };
	vector<string> teens = { "zece", "unsprezece", "doisprezece", "treisprezece", "paisprezece", "cincisprezece", "saisprezece", "saptesprezece", "optsprezece", "nouasprezece" };
	vector<string> tens = { "", "", "douazeci", "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci" };
	vector<string> powers = { "","", "mie", "mii", "milion", "milioane" };
	int singlesLength = singles.size();
	int teensLength = teens.size();
	int tensLength = tens.size();
	int powersLength = powers.size();

	for (int i = powersLength - 1; i >= 0; i--)
	{
		if (!(powers[i].empty()))
		{
			int index = words.find(powers[i], 0);
			if (index >= 0 && words[index + powers[i].length()] == ' ')
			{
				uint64_t count = WordsToNumbers(words.substr(0, index));
				number += count * (uint64_t)pow(1000, i/2);
				words = words.erase(0, index+powers[i].length()+1);
			}
		}
	}

	{
		int index = words.find("suta", 0);
		int index2= words.find("sute",0);

		if ((index >= 0) && words[index + string("suta").length()] == ' ')
		{
			uint64_t count = WordsToNumbers(words.substr(0, index));
			number += (count * 100);
			words = words.erase(0, index+4+1);
		}else{
			if ((index2 >= 0) && words[index2 + string("sute").length()] == ' ')
		{
			uint64_t count = WordsToNumbers(words.substr(0, index2));
			number += (count * 100);
			words = words.erase(0, index+4+1);
		}
		}
	}

	for (int i = tensLength - 1; i >= 0; i--)
	{
		if (!(tens[i].empty()))
		{
			int index = words.find(tens[i], 0);

			if (index >= 0 && words[index + tens[i].length()] == ' ')
			{
				number += (unsigned int)(i * 10);
				words = words.erase(index, tens[i].length());
			}
		}
	}

	for (int i = teensLength - 1; i >= 0; i--)
	{

		if (!(teens[i].empty()))
		{
			int index = words.find(teens[i], 0);

			if (index >= 0 && words[index + teens[i].length()] == ' ')
			{
				number += (unsigned int)(i + 10);
				words = words.erase(index,teens[i].length());
			}
		}
	}

	for (int i = singlesLength - 1; i >= 0; i--)
	{
		if (!(singles[i].empty()))
		{
			int index = words.find(singles[i], 0);
			if (index >= 0 && words[index + singles[i].size()] == ' ')
			{
				number += (unsigned int)(i/3);
				words = words.erase(index,singles[i].length()+1);
				break;
			}
		}
	}

	return number;
}
