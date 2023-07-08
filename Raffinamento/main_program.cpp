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


    Project::TriangularMesh mesh = Project::TriangularMesh(vectp, vects, vectt);
    vector<vector<unsigned int>> Matr = MatrAdiac(mesh.vecttMesh, mesh.vectsMesh);

    for (int iter = 0; iter < 20; iter++) {
        Sorting::HeapSort(vectSupp, mesh.vecttMesh);
        for (int i = 0; i < 20; i++) {
            Project::Cell2D* trisupp = &mesh.vecttMesh[vectSupp[i].Id2D];
            Project::Bisect(trisupp, mesh.vectpMesh, mesh.vectsMesh, mesh.vecttMesh, Matr);
        }
    }

    Project::ExportVertices(mesh.vectpMesh);
    Project::ExportEdges(mesh.vectpMesh, mesh.vectsMesh);
    Project::ExportTriangles(mesh.vectpMesh, mesh.vectsMesh, mesh.vecttMesh);

    return 0;
}
