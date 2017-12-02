#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>

bool rev (int i,int j) { return (j<i); }

int main(int argc, char* argv[])
{
	std::string row;
	int num = 0;
	int check = 0;
	std::vector<int> arr;
	while (std::getline(std::cin,row) && row.length()>0) {
		std::stringstream str(row);
		arr.erase(arr.begin(),arr.end());
		while (str >> num)
			arr.push_back(num);
		for (auto it = arr.begin(); it<arr.end(); ++it) {
			for (auto it2 = arr.begin(); it2<arr.end(); ++it2) {
				int di = *it;
				int dv = *it2;
				if (di>dv && di%dv==0) {
					check += (di/dv);
				}
			}
		}

/*		std::sort(arr.begin(),arr.end());
		do {
			std::cout << ".";
			if (arr[0]%arr[1]==0) {
				check += arr[0]/arr[1];
				break;
			}
		} while (std::next_permutation(arr.begin(),arr.end()));*/
	}

	std::cout << "Checksum is " << check << std::endl;
	return 0;
}
