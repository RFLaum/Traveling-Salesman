/*
 * Gene.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Russell Flaum
 */

#ifndef GENE_H_
#define GENE_H_

#include <cstdlib>

class Gene
{
	float score;
	/* using the c++ <algorithm> random generators gives better randomization,
	 * but also takes longer; speed is more important here, so I use
	 * c-style randomization instead.
	 */
	static int rander(int min, int max)
	{
		return (rand() % (max - min) + min);
	}
public:
	//distances between cities
	static float** distances;
	static int numCities;
	//externally visible reference to the time score for this gene
	const float & extTime;

	//probably shouldn't make this public, but this app is small enough that
	//it doesn't really matter, and this simplifies some code elsewhere
	int* cityOrder;

	//makes a child Gene by shuffling a random subsection of this Gene
	Gene* shuffleChild();
	//makes a child Gene by moving a subsection of this Gene to a different
	//place, and optionally reversing its order
	Gene* moveChild(bool reverse);
	//generates a rotated copy of cityOrder
	int* rotateMaker();

	Gene(int* cityOrderIn);
	virtual ~Gene();
};

#endif /* GENE_H_ */
