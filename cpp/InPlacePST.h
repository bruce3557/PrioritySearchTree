//-*- mode: c++ -*-////////////////////////////////////////////////////////////
//                       Copyright (c) 2011 - 2012 by                        //
//                                Simon Pratt                                //
//                           (All rights reserved)                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// FILE:    InPlacePST.h                                                     //
//                                                                           //
// MODULE:  Priority Search Tree                                             //
//                                                                           //
// PURPOSE: Implements the data structure presented in "In-place             //
//          Priority Search Tree and its applications" by De,                //
//          Maheshwari, Nandy, Smid in 2011.                                 //
//                                                                           //
// NOTES:   None.                                                            //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                             Public Methods:                               //
///////////////////////////////////////////////////////////////////////////////
#ifndef INPLACEPST_H
#define INPLACEPST_H

#include <vector>
#include "PSTPoint.h"

using namespace std;

namespace PrioritySearchTree {
  class InPlacePST {
    PSTPoint* tree;
    int npoints;
    void buildLevel(int i, int n);
    void swap(int a, int b);
    void inPlaceSort(int begin, int end, const PSTPoint& s);
    int numberOfChildren(int index);
    bool isLeaf(int index);
    void explore(int indexP, coord_t ymin, vector<PSTPoint>* points);
    PSTPoint getPoint(int n); // index base 1
    void printTree(int index, int spaces);
  public:
    coord_t POSITIVE_INFINITY;
    coord_t NEGATIVE_INFINITY;
    InPlacePST(){}
    InPlacePST(char *filename);
    InPlacePST(FILE *fp);
    InPlacePST(PSTPoint* points, int n);
    PSTPoint leftMostNE(coord_t xmin, coord_t ymin);
    PSTPoint highestNE(coord_t xmin, coord_t ymin);
    PSTPoint highest3Sided(coord_t xmin, coord_t xmax, coord_t ymin);
    vector<PSTPoint>* enumerate3Sided(coord_t xmin, coord_t xmax, coord_t ymin);
    void printTree();

    vector< unsigned char > serialize();
    int load(FILE* fp);
    void load(char *filename);

    void printArray() {
      cout << "RESULT: " << endl;
      for(int i=0;i<npoints;i++)
        cout << tree[i] << " ";
      cout << endl << "OVER" << endl;
    }
  };
}

#endif
