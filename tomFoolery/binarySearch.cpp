#include <iostream>

float binarySearch(float sortedList[], float item, int size);

int main()
{
	float someArray[] = { 1, 2, 4, 7, 125, 554, 667,668,669,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
	int size = sizeof(someArray) / sizeof(int);
	std::cout << "Found at: " << binarySearch(someArray, 900, size) << std::endl;

	return 0;
}

float binarySearch(float sortedList[], float item, int size)
{
	int low = 0, steps = 0;
	int high = size;
	int mid;
	float guess;
	while (low <= high)
	{
		steps++;
		mid = (low + high) / 2;
		guess = sortedList[mid];

		if (guess == item)
		{
			std::cout << "steps: " << steps << std::endl;
			return mid;
		}
		else if (guess > item) // too high
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return NULL;
}