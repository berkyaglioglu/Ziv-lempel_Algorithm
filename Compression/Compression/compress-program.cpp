#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int Hash(const string & key, int tableSize)//hash function for a key that is string object
{
	int hashVal = 0;

	for(int i = 0; i < key.length(); i++) {
		hashVal = 20*hashVal + int(key[i]);
	}
	hashVal = hashVal % tableSize;
	
	if(hashVal < 0) {
		hashVal = hashVal + tableSize;
	}

	return hashVal;
}

int Hash(const int & key, int tableSize)//hash function for a key that is int object
{
	int hashVal = key % tableSize;

	return 0;
}

template <class KeyObj>
class HashTable
{
private:
	struct HashEntry// hash entry that is kept in the table which is array
	{
		KeyObj key;
		int value;

		HashEntry(const KeyObj & key = KeyObj(), int val = -1): key(key), value(val) { }//default values of hash entry object
	};

	vector<HashEntry> arr;//represent table
	int currentEltNum;
	int arrSize;
	
	int findPos(const KeyObj & key) const
	{
		int pos = Hash(key, arrSize);// index of array to be inserted returns from hash

		while(arr[pos].key != key && arr[pos].value != -1) { // In every collision, increment pos
			pos++;
			if(pos == arrSize) {// when equals array size, make position 0 to search from beginning
				pos = 0;
			}
		}

		return pos;
	}

public:
	HashTable(int tableSize): arr(tableSize), arrSize(tableSize), currentEltNum(0) { } // table size is the parameter
	
	int FindCode(const KeyObj & key) const
	{
		int pos = findPos(key);//returns the position of key
		return arr[pos].value;
	}

	void Insert(const KeyObj & key)
	{
		if(currentEltNum != arrSize) {
			int pos = findPos(key);//returns the position that key can be inserted

			if(arr[pos].value != -1) { // if it is already inserted
				return;
			}

			int value = currentEltNum;
			arr[pos] = HashEntry(key, value);// add new object with a key to spesific position
			currentEltNum++;
		}
	}
};


int main()
{
	ifstream in;
	in.open("compin.txt");
	ofstream out;
	out.open("compout.txt");

	HashTable<string> table(4096);
	
	string key = "0";
	for(int i=0; i <= 255; i++) {// put first 256 default characters to the table
		key[0] = char(i);			
		table.Insert(key);
	}

	char c;
	string longestPrefix, newText;
	int code;
	bool check = false;
	
	if(in.get(c)) { //when compin is not empty
		key[0] = c;
		check = true;
	}

	while(check) {
		longestPrefix = key;// make longest prefix equal to last char

		if(in.get(c)) {//when compin is not ended
			key[0] = c;
			newText = longestPrefix + key;
			code = table.FindCode(newText);// look at the code of the prefix that is followed by a char

			while(code != -1 && in.get(c)) {// continue to look prefixes until it is not on table
				key[0] = c;
				longestPrefix = newText;
				newText = longestPrefix + key;
				code = table.FindCode(newText);
			}
			
			if(code == -1) { // write to compout the code of the longest prefix
				code = table.FindCode(longestPrefix);
				out << code << " ";
				table.Insert(newText);
				key[0] = newText.at(newText.length()-1);
			}
			else { // when compin is ended
				out << code << " ";
				check = false;
			}
		}
		else { // when compin is ended
			code = table.FindCode(longestPrefix);
			out << code << " ";
			check = false;
		}
	}

	in.close();
	out.close();

	return 0;
}