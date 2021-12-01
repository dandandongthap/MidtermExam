#include <iostream>
#include <vector>

long long countCouples(const std::vector<int>& a, const std::vector<int>& b, int n);

void fillVector(std::vector<int>& vec);

std::vector<int> subtractVectors(const std::vector<int>& vec0, const std::vector<int>& vec1);

void heapSort(std::vector<int>& vec);

void heapify(std::vector<int>& vec, int num, int index);

int findPositiveSum(const std::vector<int>& vec, int left, int right, int data);

//int test0(const std::vector<int>& a, const std::vector<int>& b, int n);

//int test1(const std::vector<int>& vec, int data);

int main()
{
	int n = 0;

	std::cin >> n;

	std::vector<int>a(n);
	std::vector<int>b(n);

	fillVector(a);
	fillVector(b);

	//std::cout << test0(a, b, n) << std::endl;
	std::cout << countCouples(a, b, n);

	return 0;
}

long long countCouples(const std::vector<int>& a, const std::vector<int>& b, int n)
{
	long long count = 0;
	auto c = subtractVectors(a, b);

	heapSort(c);

	for (int i = n - 1; i >= 0; i--)
	{
		if (c.at(i) > 0)
		{
			count += static_cast<long long>(n - 1 - i);
		}
		else
		{
			int index = findPositiveSum(c, i + 1, n - 1, c.at(i));

			if (index != -1)
			{
				count += static_cast<long long>(n - index);
			}
		}
	}

	return count;
}

void fillVector(std::vector<int>& vec)
{
	for (auto& input : vec)
	{
		std::cin >> input;
	}
}

std::vector<int> subtractVectors(const std::vector<int>& vec0, const std::vector<int>& vec1)
{
	std::vector<int> vec2(vec0.size());

	for (int i = 0; i < vec2.size(); i++)
	{
		vec2.at(i) = vec0.at(i) - vec1.at(i);
	}
	return vec2;
}

void heapSort(std::vector<int>& vec)
{
	int size = static_cast<int>(vec.size());

	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapify(vec, size, i);
	}

	for (int i = size - 1; i > 0; i--)
	{
		std::swap(vec.at(0), vec.at(i));
		heapify(vec, i, 0);
	}
}

void heapify(std::vector<int>& vec, int num, int index)
{
	int largest = index;
	int left = 2 * index + 1;
	int right = left + 1;

	if (left < num && vec.at(left) > vec.at(largest))
	{
		largest = left;
	}
	if (right < num && vec.at(right) > vec.at(largest))
	{
		largest = right;
	}
	if (largest != index)
	{
		std::swap(vec.at(largest), vec.at(index));
		heapify(vec, num, largest);
	}
}

int findPositiveSum(const std::vector<int>& vec, int left, int right, int data)
{
	if (left < vec.size() && right < left) return left;

	if (right < left) return -1;

	int mid = left + (right - left) / 2;

	if (vec.at(mid) + data > 0) return findPositiveSum(vec, left, mid - 1, data);

	return findPositiveSum(vec, mid + 1, right, data);
}
/*
int test0(const std::vector<int>& a, const std::vector<int>& b, int n)
{
	int count = 0;
	auto c = subtractVectors(a, b);

	heapSort(c);

	for (int i = n - 1; i >= 0; i--)
	{
		if (c.at(i) > 0)
		{
			count += n - 1 - i;
		}
		else
		{
			int index = test1(c, c.at(i));
			if (index != -1)
			{
				count += n - index;
			}
		}
	}

	return count;
}

int test1(const std::vector<int>& vec, int data)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] + data > 0) return i;
	}

	return -1;
}
*/