//////////////////////////////////////////////////////////////////
//                 Copyright (c) 2011-2013 by                   //
//                          Simon Pratt                         //
//                          Bruce Kuo                           //
//                     (All rights reserved)                    //
//////////////////////////////////////////////////////////////////
//                                                              //
//FILE:    test_pst_serialize.cpp                               //
//                                                              //
//MODULE:  Priority Search Tree                                 //
//                                                              //
//NOTES:   None.                                                //
//                                                              //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <assert.h>

#include "PSTPoint.h"
#include "InPlacePST.h"
#include "array_utilities.h"
#include "control_utilities.h"

using namespace std;
using namespace PrioritySearchTree;

void printUsage() {
  cout << "Usage: test_pst_serialize [number of points] [query iterations] [enumerate iterations]" << endl;
}

int main(int argv, char **argc) {

  time_t before, after;
  int n, qi, ei;

  // Set the random seed
  srand(time(0));

  if(argv < 3) {
    printUsage();
    return 1;
  }

  n = atoi(argc[1]);
  qi = atoi(argc[2]);
  ei = atoi(argc[3]);

  // Create Points
  cout << "Creating " << n << " points..." << endl << flush;
  before = time(0);
  PSTPoint *points = new PSTPoint[n];
  for(int i=1;i<n;++i)
    points[i] = PSTPoint(i, i);
  after = time(0);
  cout << "time elapsed: " << (after - before) << endl;
  if(n <= 20) {
    cout << "Points: ";
    PSTArray::print(points, n);
    cout << endl << flush;
  }

  // Build tree
  cout << "Building tree..." << endl << flush;
  before = time(0);
  InPlacePST ippst(points, n);
  after = time(0);
  cout << "time elapsed: " << (after - before) << endl << flush;
  delete points;

  vector<unsigned char> test = ippst.serialize();
  FILE *fp = fopen("test.idx", "w");
  fwrite((const unsigned char *)&test[0], 1, test.size(), fp);
  cout << test.size() << endl;
  cout << "Original..." << endl;
  ippst.printArray();
  fclose(fp);

  fp = fopen("test.idx", "r");
  InPlacePST rebuild("test.idx");
  cout << "Rebuild..." << endl;
  rebuild.printArray();

  

  return 0;
}
