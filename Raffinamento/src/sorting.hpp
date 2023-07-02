#ifndef SORTING_HPP
#define SORTING_HPP


#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"
#include "empty_class.hpp"


using namespace std;
using namespace Eigen;

namespace Sorting
{

template <typename T>
void MakeHeap(vector<T>& vecttSuppS, int i) { //, vector<T>& vectpS){



    int max = i;
    unsigned int l = 2 * i + 1;
    unsigned int r = 2 * i + 2;

    if (l < vecttSuppS.size() && vecttSuppS[l] < vecttSuppS[max])
        {
            max = l;
        }

        if (r < vecttSuppS.size() && vecttSuppS[r] < vecttSuppS[max])
        {
            max = r;
        }

        if (max != i)
        {
            swap(vecttSuppS[i], vecttSuppS[l]);
            MakeHeap(vecttSuppS, i); //, vectpS);
        }
    }


template<typename T>
void HeapSort(vector<T>& vecttSuppS, vector<T>& vecttS){  //, vector<T>& vectpS){

    vecttSuppS.clear();
    for (unsigned int k = 0; k < vecttS.size(); k++){
        vecttSuppS.push_back(vecttS[k]);
    }

    for (int i = vecttSuppS.size() / 2 - 1; i >= 0; i--)
    {
        MakeHeap(vecttSuppS, i); //, vectpS);
    }
    for (int i = vecttSuppS.size() - 1; i >= 0; i--)
    {
        swap(vecttSuppS[0], vecttSuppS[i]);
        MakeHeap(vecttSuppS, 0); //, vectpS);
    }
}

}



#endif // SORTING_HPP
