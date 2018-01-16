/*
 * GenePool.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Russell Flaum
 */

#include "GenePool.h"
#include <algorithm>
#include <cmath>
/* Number of children of each type to create for each parent gene.
 * Since there are three types, the total number of children per parent
 * is 3 * EACH_TYPE.
 */
#define EACH_TYPE 10

float GenePool::bestTime()
{
	return genes[0]->extTime;
}

int* GenePool::bestOrder()
{
	return genes[0]->cityOrder;
}

void GenePool::oneGeneration()
{
	int numParents = genes.size();
//	genes.reserve((3*EACH_TYPE + 1)*numParents);

	for (int i = 0; i < numParents; i++)
	{
		Gene * papa = genes[i];
		for (int j = 0; j < EACH_TYPE; j++)
		{
			genes.push_back(papa -> shuffleChild());
			genes.push_back(papa -> moveChild(true));
			genes.push_back(papa -> moveChild(false));
		}
	}

	std::sort(genes.begin(), genes.end(), geneCompare);
	int sz = genes.size();
	if (sz > maxSize)
	{
		for (int i = maxSize; i < sz; i++)
			delete genes[i];
		genes.resize(maxSize);
	}
}

GenePool::GenePool(int** cityLocs, int numCitiesIn, int cull): numCities(numCitiesIn), maxSize(cull)
{
	dists = new float*[numCities];
	for (int i = 0; i < numCities; i++)
		dists[i] = new float[numCities];

	for (int i = 0; i < numCities; i++)
		for (int j = 0, xDist, yDist; j < numCities; j++)
		{
			xDist = cityLocs[i][0] - cityLocs[j][0];
			yDist = cityLocs[i][1] - cityLocs[j][1];
			dists[i][j] = std::pow(xDist*xDist + yDist*yDist, 0.5);
		}

	//if there were ever going to be more than one GenePool object this would
	//cause problems, but there never will be.
	Gene::distances = dists;
	Gene::numCities = numCities;

	int * startArray = new int[numCities];
	for (int i = 0; i < numCities; i++)
		startArray[i] = i;
	Gene * adam = new Gene(startArray);
	//after creating children but before culling, will need at most this many
	genes.reserve((3*EACH_TYPE + 1)*maxSize);
	genes.push_back(adam);
}

GenePool::~GenePool()
{
	/* This isn't strictly necessary, because this will all be cleaned up
	 * anyway when the app closes, and the GenePool will only ever be
	 * destroyed when the app closes. This is mostly just here for
	 * aesthetic reasons.
	 */
	for (auto gene : genes)
		delete gene;
	for (int i = 0; i < numCities; i++)
		delete dists[i];
	delete dists;
}

