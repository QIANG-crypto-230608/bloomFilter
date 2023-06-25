#include<iostream>
#include<bitset>
#include<functional>
#include<string>
#include<cmath>
#include<vector>
using namespace std;

constexpr int FILTER_SIZE = 1000000;
//constexpr int NUM_HASHER = 3;

class BloomFilter
{
private:
	//bitset<1000000> filter;
	vector<bool> filter;
	hash<string> hashFunc;
	int numHashes;
	int filterSize;

public:
	BloomFilter(int expectedNumItems, double falsePositiveRate) {
		filterSize = calculateFilterSize(expectedNumItems, falsePositiveRate);
		numHashes = calculateNumHasher(filterSize, expectedNumItems);
		filter.resize(filterSize);
	}

	void insert(const string& item)
	{
		for (int i = 0; i < numHashes; ++i)
		{
			int index = hashFunc(item + to_string(i)) % filter.size();
			//filter.set(index, true);
			filter[index] = true;
		}
	}

	bool contains(const string& item)
	{
		for (int i = 0; i < numHashes; ++i)
		{
			int index = hashFunc(item + to_string(i)) % filter.size();
			if (!filter[index])//(!filter.test(index))
				return false;
		}
		return true;
	}

	void clear()
	{
		//filter.reset();
		filter.clear();
	}

private:
	int calculateFilterSize(int expectedNumItems, double falsePositiveRate)
	{
		int size = -(expectedNumItems * log(falsePositiveRate)) / (log(2) * log(2));
		return size;
	}

	int calculateNumHasher(int filterSize, int expectedNumItems)
	{
		int numHashes = (filterSize / expectedNumItems) * log(2);
		return numHashes;
	}
};

int main(void)
{
	BloomFilter filter(1000, 0.01);

	filter.insert("apple");
	filter.insert("banana");
	filter.insert("orange");

	cout << "Contains 'appla': " << filter.contains("apple") << endl;
	cout << "Contains 'banana': " << filter.contains("banana") << endl;
	cout << "Contains 'orange': " << filter.contains("orange") << endl;
	cout << "Contains 'grape': " << filter.contains("grape") << endl;

	/*filter.clear();
	cout << "After clearing the filter: " << endl;
	cout << "Contains 'appla': " << filter.contains("apple") << endl;
	cout << "Contains 'banana': " << filter.contains("banana") << endl;
	cout << "Contains 'orange': " << filter.contains("orange") << endl;*/

	return 0;
}