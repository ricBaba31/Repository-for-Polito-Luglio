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
//  int n = 5; // poi da cambiare: probabilmente è la size di vectsupp in heapsort

    //Project::TriangularMesh mesh;

    vector<Project::Cell2D> vectSupp;

    //unsigned int numbercell0D = 0;
    vector<Project::Cell0D> vectp;
    Project::ImportCell0Ds(vectp, "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell0Ds.csv");

    //unsigned int numbercell1D = 0;
    vector<Project::Cell1D> vects;
    //vector<double> LengthEdges;
    Project::ImportCell1Ds(vects,  "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell1Ds.csv");

    //unsigned int numbercell2D = 0;
    std::vector<vector<unsigned int>> LenghtMax;
    vector<Project::Cell2D> vectt;
    vector<Project::Cell0D> vectp2D;
    Project::ImportCell2Ds(vectt,  vectp,  "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell2Ds.csv");

    //Project::MatrAdiac MatriceAdiacenza = Project::MatrAdiac(mesh.vectt, mesh.vects);

    Project::TriangularMesh mesh = Project::TriangularMesh(vectp, vects, vectt);
    vector<vector<unsigned int>> Matr = MatrAdiac(mesh.vecttMesh, mesh.vectsMesh);
    //Project::MatrAdiac MatriceAdiacenza = Project::MatrAdiac(vectt, vects);

    for (int iter = 0; iter < 20; iter++) {
        Sorting::HeapSort(vectSupp, mesh.vecttMesh);
        for (int i = 0; i < 20; i++) {
            Project::Cell2D* trisupp = &mesh.vecttMesh[vectSupp[i].Id2D];
            Project::Bisect(trisupp, mesh.vectpMesh, mesh.vectsMesh, mesh.vecttMesh, Matr);
        }
    }


    return 0;
}
