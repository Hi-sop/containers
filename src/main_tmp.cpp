#include <iostream>
#include <string>
#include <deque>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#include <stdlib.h>


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T>
class MutantStack : public ft::stack<T>
{
	public:
		MutantStack() {}
		MutantStack(const MutantStack<T>& src) {*this = src;}
		MutantStack<T>& operator=(const MutantStack<T>& rhs)
		{
			this->c = rhs.c;
			return *this;
		}
		~MutantStack() {}

		typedef typename ft::stack<T>::container_type::iterator iterator;

		iterator begin() { return this->c.begin(); }
		iterator end() { return this->c.end(); }
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "You should insert seed!! ./container [seed]" << std::endl;
		return 1;
	}
	//rand seed 값
	const int seed = atoi(argv[1]);
	srand(seed);

	//변수 선언 체크
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;
	ft::set<int> set_int;

	//vector 생성 및 삽입 체크
	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try {
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Vector check end." << std::endl;
	}

	//map 생성 및 탐색 체크
	for (int i = 0; i < 1000; ++i)
	{
		map_int.insert(ft::make_pair(rand() % 1000, rand() % 1000));
	}

	int sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		int access = rand() % 100;
		sum += map_int[access];
	}
	std::cout << "seed: " << seed << "\nsum: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}

	//set 생성 및 삽입 체크
	for (int i = 0; i < COUNT; ++i)
	{
		set_int.insert(rand());
	}

	{ ft::set<int> copy = set_int; }

	//stack 체크
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin();
			it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
