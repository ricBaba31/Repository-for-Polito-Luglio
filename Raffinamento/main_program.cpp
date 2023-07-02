#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"

#include "empty_class.hpp"
#include "sorting.hpp"

//using namespace std;
//using namespace Eigen;
using namespace Project;
using namespace Sorting;


int main()
{
//  int n = 5; // poi da cambiare: probabilmente è la size di vectsupp in heapsort

    //Project::TriangularMesh mesh;

    vector<Project::Cell2D> vectSupp;

    unsigned int numbercell0D = 0;
    vector<Project::Cell0D> vectp;
    Project::ImportCell0Ds(vectp, numbercell0D);

    unsigned int numbercell1D = 0;
    vector<Project::Cell1D> vects;
    vector<double> LengthEdges;
    Project::ImportCell1Ds(vects, numbercell1D, LengthEdges, vectp);

    unsigned int numbercell2D = 0;
    std::vector<vector<unsigned int>> LenghtMax;
    vector<Project::Cell2D> vectt;
    vector<Project::Cell0D> vectp2D;
    Project::ImportCell2Ds(vectt, numbercell2D, vectp, vectp2D);

    //Project::MatrAdiac MatriceAdiacenza = Project::MatrAdiac(mesh.vectt, mesh.vects);

    Project::TriangularMesh mesh = Project::TriangularMesh(numbercell0D, vectp, numbercell1D, vects, LengthEdges, numbercell2D, LenghtMax, vectt);
    vector<vector<unsigned int>> Matr = MatrAdiac(vectt, vects);
    //Project::MatrAdiac MatriceAdiacenza = Project::MatrAdiac(vectt, vects);

    for (int iter = 0; iter<20; iter++) {
        Sorting::HeapSort(vectSupp, vectt); //, vectp);
        for (int i = 0; i < 20; i++) {
            Project::Cell2D& trisupp = vectSupp[i];
            Project::Bisect(trisupp, vectp, vects, vectt, Matr);   //, MatriceAdiacenza.Matr);
        }
    }


//    empty.Show();

    return 0;
}
