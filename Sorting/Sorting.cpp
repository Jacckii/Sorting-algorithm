/* Code by Jaccko */

#include "stdafx.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "gui.h"

std::mutex mutex;
std::vector<int32_t> array_to_sort;

void gui();

int main(void)
{
	/* run gui in another thread to make it simple */
	std::thread thread_gui(gui); 

	while(1)
	{
		char smth;

		/* size of the vector with numbers in random order */
		size_t desired_array_size = 132; 

		/* generate 0 - 132 in random order */
		std::cout << "Unsorted data:" << std::endl;
		mutex.lock();																							/* Locking Mutex to prevent reading vector from other thread while writing here */
		while (array_to_sort.size() < desired_array_size)
		{
			int val = rand() % desired_array_size;
			if (std::find(array_to_sort.begin(), array_to_sort.end(), val) == array_to_sort.end())
				array_to_sort.push_back(val);
		}
		mutex.unlock();																							/* Unlocking Mutex */

		/* print vector */
		for (int value : array_to_sort)
			std::cout << value << " ";
		std::cout << std::endl;

		/* Wait for user to start sorting alg. */
		while (true) {
			std::cout << "START Sorting![y/n]" << std::endl;
			std::cin >> smth;
			if ((smth == 'y') || (smth == 'n')) {
				break;
			}
		}

		size_t index = 0;										/* this is end index of the sorted vector */
		while (1)
		{
			int low = -1;										/* save the lowest number */
			size_t index_of_item = -1;							/* index of value that we want to sort */
			for (size_t x = 0; x < array_to_sort.size(); x++)
			{
				if (x != index && x < index)					/* we want to skip positions that we already have sorted */
					continue;

				int value = array_to_sort[x];					/* get currently selected value from the vector */
				if (value < low || low == -1)					/* if a currently selected value is smaller than lowest record change the lowest record to this value */
				{
					low = value;								/* saving the lowest value in the vector that wasn't sorted yet */
					index_of_item = x;							/* saving index of the lowest value in the vector that wasn't sorted yet */
				}
			}

			if (index_of_item != -1) 
			{
				mutex.lock();																							/* Locking Mutex to prevent reading vector from other thread while writing here */
				std::iter_swap(array_to_sort.begin() + index_of_item, array_to_sort.begin() + index);					/* Swap obj. position in vector  */
				mutex.unlock();																							/* Unlocking Mutex */
			}

			Sleep(30);											/* 30ms delay so you can see how this sort alg. works */

			if (index == array_to_sort.size())					/* if we sorted all out, then we want to exit this loop */
				break;

			index++;
		}

		std::cout << "Done!" << std::endl;

		/* print vector */
		std::cout << "Sorted data:" << std::endl;
		
		for (int value : array_to_sort)
			std::cout << value << " ";
		std::cout << std::endl;

		/* Wait for user action */
		while (true) {
			std::cout << "START Again?[y/n]" << std::endl;
			std::cin >> smth;
			if ((smth == 'y') || (smth == 'n')) {
				break;
			}
		}

		if (smth == 'y')
		{
			system("cls");		
			mutex.lock();																							/* Locking Mutex to prevent reading vector from other thread while writing here *//* Clear console */
			array_to_sort.clear();																					/* Clear sorted vector */
			mutex.unlock();																							/* Unlocking Mutex */
		}
		else
			break;

	}
	thread_gui.join();											/* we want to wait until thread gui finished */

	return 0;
}

void gui()
{
	GUI gui;
	gui.Draw();
}




