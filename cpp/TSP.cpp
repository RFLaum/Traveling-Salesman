//============================================================================
// Name        : TSP.cpp
// Author      : Russell Flaum
// Version     :
// Copyright   :
// Description : Traveling Salesman Problem solver
//				 This uses a genetic algorithm with two different kinds of
//				 mutation; I ran some test problems to see what kind of local
//				 minima it got trapped in, and designed the second kind of
//				 mutation to get it out of those.
//============================================================================

#include <cstdlib>
#include <ctime>
#include "GenePool.h"
#include "rice/Class.hpp"
#include "rice/Array.hpp"

using namespace std;
using namespace Rice;

Array solver(Array coords)
{
	//rand() is used for the mutations, so we need to initialize it here.
	srand(time(NULL));
	/* Ruby passes the input parameter as a flat array instead of a
	 * multidimensional one because it makes the code to translate it into a
	 * c array somewhat simpler.
	 */
	int numCoords = coords.size() / 2;
	int ** cooked = new int * [numCoords];

	for (int i = 0; i < numCoords; i++)
	{
		cooked[i] = new int[2];
		cooked[i][0] = from_ruby<int>(coords[2*i]);
		cooked[i][1] = from_ruby<int>(coords[2*i+1]);
	}

	GenePool pool(cooked, numCoords, 500);
	for (int i = 0; i < 100; i++)
		pool.oneGeneration();
	/* Important note: once we exit this function, this pointer is no longer
	 * guaranteed to be useful. This is because pool will be destroyed, which
	 * in turn destroys all its Genes. bestOrder() just returns a pointer to
	 * a Gene's internal array, and once the Gene is destroyed, it releases
	 * its claim on that memory.
	 */
	int * cAnswer = pool.bestOrder();
	Array rubyAnswer;
	for (int i = 0; i < numCoords; i++)
		rubyAnswer.push(to_ruby(cAnswer[i]));
	return rubyAnswer;
}

extern "C"

void Init_cruncher ()
{
	Class rb_cCruncher = define_class("Cruncher").define_method("solver", &solver);
}
