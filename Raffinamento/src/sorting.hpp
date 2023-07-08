#ifndef SORTING_HPP
#define SORTING_HPP


#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"


using namespace std;
using namespace Eigen;

namespace Sorting
{

template <typename T>
void MakeHeap(vector<T>& vecttSuppS, unsigned int n, unsigned int i) { 



    unsigned int max = i;
    unsigned int l = 2 * i + 1;
    unsigned int r = 2 * i + 2;

    if (l < n && vecttSuppS[l] < vecttSuppS[max])
        {
            max = l;
        }

        if (r < n && vecttSuppS[r] < vecttSuppS[max])
        {
            max = r;
        }

        if (max != i)
        {
            swap(vecttSuppS[i], vecttSuppS[max]);
            MakeHeap(vecttSuppS, n, max); 
        }
    }


template<typename T>
void HeapSort(vector<T>& vecttSuppS, vector<T>& vecttS){  

    vecttSuppS.clear();
    for (unsigned int k = 0; k < vecttS.size(); k++){
        vecttSuppS.push_back(vecttS[k]);
    }

    for (int i = vecttSuppS.size() / 2 - 1; i >= 0; i--)
    {
        MakeHeap(vecttSuppS, vecttSuppS.size(), i); 
    }
    for (int i = vecttSuppS.size() - 1; i >= 0; i--)
    {
        swap(vecttSuppS[0], vecttSuppS[i]);
        MakeHeap(vecttSuppS, i, 0); 
    }
}

}



#endif // SORTING_HPP
