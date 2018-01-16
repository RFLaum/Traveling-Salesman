/*
 * GenePool.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Russell Flaum
 */

#ifndef GENEPOOL_H_
#define GENEPOOL_H_

#include <vector>
#include "Gene.h"

class GenePool
{
public:
	//contains the distances between any two cities
	//e.g. dists[7][12] is the distance between city 7 and city 12
	float** dists;
	int numCities;

	void oneGeneration();
	float bestTime();
	int * bestOrder();

	GenePool(int** cityLocations, int numberOfCities, int maximumGenes);
	virtual ~GenePool();
private:
	//maximum number of genes we want to survive any given generation
	int maxSize;
	std::vector<Gene*> genes;
	//used for sorting
	static bool geneCompare(Gene * a, Gene * b) {return (a->extTime < b->extTime);}
};

#endif /* GENEPOOL_H_ */
