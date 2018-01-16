/*
 * Gene.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Russell Flaum
 */

#include "Gene.h"
//used for memcpy
#include <cstring>
#include <algorithm>

float** Gene::distances;
int Gene::numCities = 0;

int* Gene::rotateMaker()
{
	int *baseArr = new int[numCities];
//	int newBeginning = rander(0, numCities - 1);
//	int sizeFirst = newBeginning*sizeof(int);
//	int sizeSecond = (numCities - newBeginning)*sizeof(int);
//	memcpy(baseArr, cityOrder + newBeginning, sizeSecond);
//	memcpy(baseArr + numCities - newBeginning, cityOrder, sizeFirst);
	std::rotate_copy(cityOrder, cityOrder + rander(0,numCities - 1), cityOrder + numCities, baseArr);
	return baseArr;
}

/* This creates a "child" gene, which is the same as this one except that a
 * section has been randomly shuffled. I'm not using std::shuffle because the
 * rng used is not guaranteed to be a fast one.
 */
Gene* Gene::shuffleChild()
{
	int * baseArr = rotateMaker();

	int first = rander(0, numCities - 2);
	int second = rander(first + 1, numCities - 1);
	for (int i = first, holder; i <= second; i++)
	{
		int dest = rander(first, second);
		holder = baseArr[dest];
		baseArr[dest] = baseArr[i];
		baseArr[i] = holder;
	}

	return new Gene(baseArr);
}

/* Often a locally optimum solution will emerge for a small group of cities;
 * we want to move these groups around as a single unit; trying to just
 * randomly shuffle will almost always result in a longer time, so if we only
 * had shuffleChild() we'd gettrapped in a local optimum with no way to the
 * global optimum.
 */
Gene* Gene::moveChild(bool flip)
{
	int * baseArr = rotateMaker();
	int first = rander(0, numCities - 3);
	int last = rander(first + 1, numCities - 2);
	int * cookedArray = new int[numCities];

	memcpy(cookedArray, baseArr, first*sizeof(int));
	memcpy(cookedArray + first, baseArr + last + 1, (numCities - last - 1)*sizeof(int));
	if (flip)
		std::reverse_copy(baseArr + first,
				baseArr + last + 1,
				cookedArray + numCities + first - last - 1);
	else
		memcpy(cookedArray + numCities + first - last - 1,
				baseArr + first,
				(last - first + 1)*sizeof(int));
	delete baseArr;

	return new Gene(cookedArray);
}

Gene::Gene(int* cityOrderIn):score(0), extTime(score), cityOrder(cityOrderIn)
{
	for (int i = 0; i < numCities - 1; i++)
		score += distances[cityOrder[i]][cityOrder[i+1]];
	score += distances[cityOrder[numCities - 1]][cityOrder[0]];
}

Gene::~Gene()
{
	delete cityOrder;
}

