#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	vector<string> arr(4096, "");// array keeps the keys where codes are the indexes

	string key = "0";
	for(int i=0; i <= 255; i++) {// put first 256 key as default
		key[0] = char(i);
		arr[i] = key;
	}

	ifstream in;
	ofstream out;
	in.open("compout.txt");
	out.open("decompout.txt");

	int prevCode, code;//prev code is corresponding to index of the previous key added to list
	string text;
	
	in >> code;
	out << arr[code];
	prevCode = code;

	int index = 256;// putting keys starting from the first empty index that is 256
	while(in >> code) {
		if(arr[code] == "") {
			text = arr[prevCode] + arr[prevCode].substr(0,1);// if code is not in the array, add to corresponding key and write to decompout.txt
			arr[index] = text;
			out << arr[code];
			prevCode = code;
			index++;
		}
		else {
			text = arr[prevCode] + arr[code].substr(0,1);// if it is added before, add new key that is found and write the key corresponds to code
			arr[index] = text;
			out << arr[code];
			prevCode = code;
			index++;
		}
	}

	in.close();
	out.close();

	return 0;
}