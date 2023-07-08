#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"

using namespace std;
using namespace Eigen;

namespace Project {

    // classi
    class Cell0D {


        public:
            unsigned int marker0D;
            unsigned int Id0D;
            Vector2d Coord;
            Cell0D(unsigned int& id, unsigned int& marker, Vector2d& coord);
        };


    class Cell1D {

        public:
            unsigned int marker1D;
            unsigned int Id1D;
            vector<unsigned int> Vertices1D;
            Cell1D(unsigned int& id, unsigned int& marker, vector<unsigned int>& vertices);
            double LengthEdge(vector<Project::Cell0D>& vectp);
 };


    class Cell2D{
        public:
            unsigned int Id2D;
            array<unsigned int, 3> Edges;
            vector<Project::Cell0D> vectp2D;
            Cell2D(unsigned int& id, array<unsigned int, 3>& Edges, vector<Project::Cell0D>& vectp2D);
            unsigned int maxedge(vector<Project::Cell1D>& vects, vector<Project::Cell0D>& vectp);
            double Area(); //vector<Project::Cell0D>& vectp);
        };


    bool ImportCell0Ds(vector<Project::Cell0D>& vettorePunti, string path);
    bool ImportCell1Ds(vector<Project::Cell1D>& vettoreLati, string path);
    bool ImportCell2Ds(vector<Project::Cell2D>& vettoreTriangoli, vector<Project::Cell0D>& vettorePunti, string path);

    vector<vector<unsigned int>> MatrAdiac(vector<Project::Cell2D>& vectt, vector<Project::Cell1D>& vects);

    void Bisect(Project::Cell2D* triangleToBisect, vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects, vector<Project::Cell2D>& vectt, vector<vector<unsigned int>>& Matr);
    void Propagazione(unsigned int& idLatoTagliatoVecchio, unsigned int& idLatoTagliatoNuovo, Cell2D* Triangolo, unsigned int& latoMax, vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects, vector<Project::Cell2D>& vectt, vector<vector<unsigned int>>& Matr); 
   
    bool ExportVertices(vector<Project::Cell0D>& vectp);
    bool ExportEdges(vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects);



    // tolleranze
    constexpr double max_tol(const double& x, const double& y)
        {
        return x > y ? x : y;
        }

    static constexpr double tol1D = 1.0e-12;
    static constexpr double tol2D = max_tol(tol1D * tol1D, numeric_limits<double>::epsilon());


    inline bool operator<(Cell2D& t1,  Cell2D& t2) //, vector<Project::Cell0D>& vectp)
    {
      return t1.Area() < t2.Area() + tol2D * max(t1.Area(), t2.Area());
    }

    inline bool operator>=(Cell2D& t1,Cell2D& t2)
    {
      return !(t1 < t2);
    }



 }


#endif // __EMPTY_H
