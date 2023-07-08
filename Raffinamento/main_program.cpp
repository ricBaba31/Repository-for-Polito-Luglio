#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"

#include "empty_class.hpp"
#include "sorting.hpp"

using namespace std;
using namespace Eigen;
using namespace Project;
using namespace Sorting;


int main()
{
    vector<Project::Cell2D> vectSupp;

   
    vector<Project::Cell0D> vectp;
    Project::ImportCell0Ds(vectp, "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell0Ds.csv");

    vector<Project::Cell1D> vects;
    Project::ImportCell1Ds(vects,  "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell1Ds.csv");

    std::vector<vector<unsigned int>> LenghtMax;
    vector<Project::Cell2D> vectt;
    vector<Project::Cell0D> vectp2D;
    Project::ImportCell2Ds(vectt,  vectp,  "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell2Ds.csv");

    vector<vector<unsigned int>> Matr = MatrAdiac(vectt, vects);
    
    int Iter = 20;
    int Theta = 20;

    for (int i = 0; i < Iter; i++) {
        Sorting::HeapSort(vectSupp, vectt);
        for (int j = 0; j < Theta; j++) {
            Project::Cell2D* trisupp = &vectt[vectSupp[j].Id2D];
            Project::Bisect(trisupp, vectp, vects, vectt, Matr);
        }
    }

    Project::ExportVertices(vectp);
    Project::ExportEdges(vectp, vects);



    return 0;
}
