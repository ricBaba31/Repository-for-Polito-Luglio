#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"
#include <gtest/gtest.h>


#include "empty_class.hpp"
#include "sorting.hpp"

using namespace testing;
using namespace Sorting;
using namespace Project;

// constr x3

// import x3

// metodi x3

// sorting

// bisect
// propagazione

TEST(TestCostruttori, TestCell0D)
{
  unsigned int marker0DT = 0;
  unsigned int id0DT = 1;
  Vector2d CoordT = {2.9, 3.1415};
  Cell0D puntoT = Cell0D(id0DT, marker0DT, CoordT);
  EXPECT_EQ(puntoT.marker0D, marker0DT);
  EXPECT_EQ(puntoT.Id0D, id0DT);
  EXPECT_EQ(puntoT.Coord, CoordT);

}

TEST(TestCostruttori, TestCell1D)
{
  unsigned int marker1DT = 1;
  unsigned int id1DT = 7;
  vector<unsigned int> Vertices1DT = {2, 9};
  Cell1D latoT = Cell1D(id1DT, marker1DT, Vertices1DT);
  EXPECT_EQ(latoT.marker1D, marker1DT);
  EXPECT_EQ(latoT.Id1D, id1DT);
  EXPECT_EQ(latoT.Vertices1D, Vertices1DT);
}


TEST(TestCostruttori, TestCell2D)
{
    unsigned int v1m = 0;
    unsigned int v2m = 0;
    unsigned int v3m = 0;
    unsigned int v1id = 0;
    unsigned int v2id = 1;
    unsigned int v3id = 2;
    Vector2d v1d = {1.0, 1.0};
    Vector2d v2d = {2.0, 2.0};
    Vector2d v3d = {3.0, 3.0};
    Project::Cell0D v1 = Project::Cell0D(v1m, v1id, v1d);
    Project::Cell0D v2 = Project::Cell0D(v2m, v2id, v2d);
    Project::Cell0D v3 = Project::Cell0D(v3m, v3id, v3d);
    unsigned int id2DT = 7;
    array<unsigned int, 3> Vertices2DT = {2, 5, 9};
    array<unsigned int, 3> Edges2DT = {3, 6, 10};
    vector<Project::Cell0D> vectp2D = {v1, v2, v3};
    Cell2D triangoloT = Cell2D(id2DT, Vertices2DT, Edges2DT, vectp2D);
    EXPECT_EQ(triangoloT.Id2D, id2DT);
    EXPECT_EQ(triangoloT.Vertices2D, Vertices2DT);
    EXPECT_EQ(triangoloT.Edges, Edges2DT);
}

// ----------------------------------------------------------------------------------

TEST(TestImport, TestCell0D)
{
    unsigned int numbercell0DT = 0;
    vector<Project::Cell0D> vectpT;

    Vector2d coord3T = {0.0000000000000000e+00, 0.655};

    if(ImportCell0Ds(vectpT, numbercell0DT, "../Dataset/Test1/Cell0Ds.csv")){
        EXPECT_EQ(vectpT[0].marker0D, 1);
        EXPECT_EQ(vectpT[2].Id0D, 2);
        EXPECT_EQ(vectpT[3].Coord, coord3T);
    }

}


TEST(TestImport, TestCell1D)
{

    unsigned int numbercell1DT = 0;
    //vector<double> LengthEdgesT; // = {0.0, 0.0};
    vector<Project::Cell1D> vectsT;
    vector<Project::Cell0D> vectpT;

    if(ImportCell1Ds(vectsT, numbercell1DT, vectpT, "../Dataset/Test1/Cell1Ds.csv")){
        EXPECT_EQ(vectsT[0].marker1D, 0);
        EXPECT_EQ(vectsT[2].Id1D, 2);
        EXPECT_EQ(vectsT[3].Vertices1D[0], 23);
        EXPECT_EQ(vectsT[7].Vertices1D[1], 50);
    }

}


TEST(TestImport, TestCell2D)
{

    vector<Project::Cell0D> vectpT;
    vector<Project::Cell0D> vectpT2D;
    unsigned int numbercell2DT = 0;
    vector<Project::Cell2D> vecttT;

    if(ImportCell2Ds(vecttT, numbercell2DT, vectpT, vectpT2D, "../Dataset/Test1/Cell2Ds.csv")){
        EXPECT_EQ(vecttT[0].Id2D, 41);
        EXPECT_EQ(vecttT[1].Vertices2D[0] , 23);
        EXPECT_EQ(vecttT[2].Vertices2D[1], 51);
        EXPECT_EQ(vecttT[3].Vertices2D[2], 61);
        EXPECT_EQ(vecttT[4].Edges[0], 6);
        EXPECT_EQ(vecttT[5].Edges[1], 9);
        EXPECT_EQ(vecttT[6].Edges[2], 12);
    }

}

// ----------------------------------------------------------------------------------


TEST(TestMetodi, TestLengthEdge)
{
    unsigned int idVerT1 = 0, idVerT2 = 1;
    unsigned int idEdgT = 2;
    unsigned int markerVerT1 = 0, markerVerT2 = 0;
    unsigned int markerEdgT = 0;

    Vector2d CoordT1 = {0.0, 0.0};
    Vector2d CoordT2 = {4.0, 3.0};

    Cell0D vertT1 = Cell0D(idVerT1, markerVerT1, CoordT1), vertT2 = Cell0D(idVerT2, markerVerT2, CoordT2);
    vector<Project::Cell0D> vectpT = {vertT1, vertT2};

    vector<unsigned int> verEdg = {vertT2.Id0D, vertT1.Id0D};
    Cell1D edgT = Cell1D(idEdgT, markerEdgT, verEdg);





    double len = edgT.LengthEdge(vectpT);

    EXPECT_EQ(len, 5);


}

TEST(TestMetodi, TestMaxEdge)
{
    unsigned int idVerT1 = 0, idVerT2 = 1, idVerT3 = 2;
    unsigned int idEdgT1 = 0, idEdgT2 = 1, idEdgT3 = 2;
    unsigned int idtri = 0;
    unsigned int markerVerT1 = 0, markerVerT2 = 0, markerVerT3 = 0;
    unsigned int markerEdgT1 = 0, markerEdgT2 = 0, markerEdgT3 = 0;
    Vector2d CoordT1 = {0, 0};
    Vector2d CoordT2 = {4, 0};
    Vector2d CoordT3 = {4, 3};

    Cell0D vertT1 = Cell0D(idVerT1, markerVerT1, CoordT1), vertT2 = Cell0D(idVerT2, markerVerT2, CoordT2), vertT3 = Cell0D(idVerT3, markerVerT3, CoordT3);
    vector<Project::Cell0D> vectpT = {vertT1, vertT2, vertT3};

    vector<unsigned int> verEdg1 = {vertT1.Id0D, vertT2.Id0D}, verEdg2 = {vertT2.Id0D, vertT3.Id0D}, verEdg3 = {vertT3.Id0D, vertT1.Id0D};
    Cell1D edgT1 = Cell1D(idEdgT1, markerEdgT1, verEdg1), edgT2 = Cell1D(idEdgT2, markerEdgT2, verEdg2), edgT3 = Cell1D(idEdgT3, markerEdgT3, verEdg3);
    vector<Project::Cell1D> vectsT = {edgT1, edgT2, edgT3};

    array<unsigned int, 3> verTri = {vertT1.Id0D, vertT2.Id0D, vertT3.Id0D};
    array<unsigned int, 3> edgTri = {edgT1.Id1D, edgT2.Id1D, edgT3.Id1D};
    Cell2D triT = Cell2D(idtri, verTri, edgTri, vectpT);

    double len = triT.maxedge(vectsT, vectpT);

    EXPECT_EQ(len, 2);


}

TEST(TestMetodi, TestArea)
{
    unsigned int idVerT1 = 0, idVerT2 = 1, idVerT3 = 2;
    unsigned int idEdgT1 = 0, idEdgT2 = 1, idEdgT3 = 2;
    unsigned int idtri = 0;
    unsigned int markerVerT1 = 1, markerVerT2 = 1, markerVerT3 = 1;
    unsigned int markerEdgT1 = 1, markerEdgT2 = 1, markerEdgT3 = 1;
    Vector2d CoordT1 = {0, 0};
    Vector2d CoordT2 = {4, 0};
    Vector2d CoordT3 = {4, 3};

    Cell0D vertT1 = Cell0D(idVerT1, markerVerT1, CoordT1), vertT2 = Cell0D(idVerT2, markerVerT2, CoordT2), vertT3 = Cell0D(idVerT3, markerVerT3, CoordT3);
    vector<Project::Cell0D> vectpT = {vertT1, vertT2, vertT3};

    vector<unsigned int> verEdg1 = {vertT1.Id0D, vertT2.Id0D}, verEdg2 = {vertT2.Id0D, vertT3.Id0D}, verEdg3 = {vertT3.Id0D, vertT1.Id0D};
    Cell1D edgT1 = Cell1D(idEdgT1, markerEdgT1, verEdg1), edgT2 = Cell1D(idEdgT2, markerEdgT2, verEdg2), edgT3 = Cell1D(idEdgT3, markerEdgT3, verEdg3);
    vector<Project::Cell1D> vectsT = {edgT1, edgT2, edgT3};

    array<unsigned int, 3> verTri = {vertT1.Id0D, vertT2.Id0D, vertT3.Id0D};
    array<unsigned int, 3> edgTri = {edgT1.Id1D, edgT2.Id1D, edgT3.Id1D};
    Cell2D triT = Cell2D(idtri, verTri, edgTri, vectpT);

    double len = triT.Area();

    EXPECT_EQ(len, 6);


}


// ----------------------------------------------------------------------------------

TEST(TestSorting, TestHeapSort)
{
    vector<unsigned int> vecttT = {31, 45, 23, 3, 99, 7, 10, 25, 66, 69, 77, 88};
    vector<unsigned int> vecttSuppT = {};
    //vector<unsigned int> vectpT = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 1, 1, 2 ,3, 45, 67, 78, 56};
    Sorting::HeapSort(vecttSuppT, vecttT); //, vectpT);
    vector<unsigned int> OrderedT = {99, 88, 77, 69, 66, 45, 31, 25, 23, 10, 7, 3};
    EXPECT_EQ(vecttSuppT, OrderedT);
}


// ----------------------------------------------------------------------------------


TEST(TestBis, TestBisect)
{
    unsigned int idVerT1 = 0, idVerT2 = 1, idVerT3 = 2, idVerT4 = 3, idVerT5 = 4;
    unsigned int idEdgT1 = 0, idEdgT2 = 1, idEdgT3 = 2, idEdgT4 = 3, idEdgT5 = 4, idEdgT6 = 5, idEdgT7 = 6, idEdgT8 = 7;
    unsigned int idTriT1 = 0, idTriT2 = 1, idTriT3 = 2, idTriT4 = 3;
    unsigned int markerVerT1 = 1, markerVerT2 = 2, markerVerT3 = 3, markerVerT4 = 4, markerVerT5 = 0;
    unsigned int markerEdgT1 = 5, markerEdgT2 = 6, markerEdgT3 = 7, markerEdgT4 = 8, markerEdgT5 = 0, markerEdgT6 = 0, markerEdgT7 = 0, markerEdgT8 = 0;
    Vector2d CoordT1 = {0, 0};
    Vector2d CoordT2 = {6, 0};
    Vector2d CoordT3 = {6, 4};
    Vector2d CoordT4 = {1, 3};
    Vector2d CoordT5 = {1, 1};

    Cell0D vertT1 = Cell0D(idVerT1, markerVerT1, CoordT1), vertT2 = Cell0D(idVerT2, markerVerT2, CoordT2), vertT3 = Cell0D(idVerT3, markerVerT3, CoordT3), vertT4 = Cell0D(idVerT4, markerVerT4, CoordT4), vertT5 = Cell0D(idVerT5, markerVerT5, CoordT5);
    vector<Project::Cell0D> vectpT = {vertT1, vertT2, vertT3, vertT4, vertT5};
    vector<Project::Cell0D> vectpT1 = {vertT1, vertT2, vertT5};
    vector<Project::Cell0D> vectpT2 = {vertT2, vertT3, vertT5};
    vector<Project::Cell0D> vectpT3 = {vertT3, vertT4, vertT5};
    vector<Project::Cell0D> vectpT4 = {vertT4, vertT1, vertT5};

    vector<unsigned int> verEdg1 = {vertT1.Id0D, vertT2.Id0D}, verEdg2 = {vertT2.Id0D, vertT3.Id0D}, verEdg3 = {vertT3.Id0D, vertT4.Id0D}, verEdg4 = {vertT4.Id0D, vertT1.Id0D}, verEdg5 = {vertT1.Id0D, vertT5.Id0D}, verEdg6 = {vertT2.Id0D, vertT5.Id0D}, verEdg7 = {vertT3.Id0D, vertT5.Id0D}, verEdg8 = {vertT4.Id0D, vertT5.Id0D};
    Cell1D edgT1 = Cell1D(idEdgT1, markerEdgT1, verEdg1), edgT2 = Cell1D(idEdgT2, markerEdgT2, verEdg2), edgT3 = Cell1D(idEdgT3, markerEdgT3, verEdg3), edgT4 = Cell1D(idEdgT4, markerEdgT4, verEdg4), edgT5 = Cell1D(idEdgT5, markerEdgT5, verEdg5), edgT6 = Cell1D(idEdgT6, markerEdgT6, verEdg6), edgT7 = Cell1D(idEdgT7, markerEdgT7, verEdg7), edgT8 = Cell1D(idEdgT8, markerEdgT8, verEdg8);
    vector<Project::Cell1D> vectsT = {edgT1, edgT2, edgT3, edgT4, edgT5, edgT6, edgT7, edgT8};

    array<unsigned int, 3> verTri1 = {vertT1.Id0D, vertT2.Id0D, vertT5.Id0D}, verTri2 = {vertT2.Id0D, vertT3.Id0D, vertT5.Id0D}, verTri3 = {vertT3.Id0D, vertT4.Id0D, vertT5.Id0D}, verTri4 = {vertT4.Id0D, vertT1.Id0D, vertT5.Id0D};
    array<unsigned int, 3> edgTri1 = {edgT1.Id1D, edgT6.Id1D, edgT5.Id1D}, edgTri2 = {edgT2.Id1D, edgT7.Id1D, edgT6.Id1D}, edgTri3 = {edgT3.Id1D, edgT8.Id1D, edgT7.Id1D}, edgTri4 = {edgT4.Id1D, edgT5.Id1D, edgT8.Id1D};
    Cell2D triT1 = Cell2D(idTriT1, verTri1, edgTri1, vectpT1), triT2 = Cell2D(idTriT2, verTri2, edgTri2, vectpT2), triT3 = Cell2D(idTriT3, verTri3, edgTri3, vectpT3), triT4 = Cell2D(idTriT4, verTri4, edgTri4, vectpT4);
    vector<Project::Cell2D> vecttT = {triT1, triT2, triT3, triT4};

    //vector<vector<unsigned int>> MatrAd = MatrAdiac(vecttT, vectsT).Matr;
    vector<vector<unsigned int>> MatrAd = MatrAdiac(vecttT, vectsT);


    Project::Cell2D* trisuppT = &vecttT[0];
    Bisect(trisuppT, vectpT, vectsT, vecttT, MatrAd); // lato lungo esterno -> non parte propagazione

    //area tri 1 = 5
    //area tri 6 = 4.5
    //len edge 0 = 3
    //len edge 9 = rad 5

    //cout << vecttT[0].Area()<<endl;




    EXPECT_EQ(vecttT[0].Area(), 1.5); //0
    EXPECT_EQ(vecttT[4].Area(), 1.5); //7.97095e+303 CAMBIA -> PROB GUARDA LOC MEMORIA
    EXPECT_EQ(vectsT[0].LengthEdge(vectpT), 3);
    EXPECT_EQ(vectsT[8].LengthEdge(vectpT), sqrt(5));
    EXPECT_EQ(MatrAd[5][0], 4);
    EXPECT_EQ(MatrAd[5][1], 1);
    EXPECT_EQ(MatrAd[8][0], 0);
    EXPECT_EQ(MatrAd[8][1], 4);

    // PROBLEMI SOLO CON L'AREA

}


TEST(TestProp, TestPropagation)
{
    unsigned int idVerT1 = 0, idVerT2 = 1, idVerT3 = 2, idVerT4 = 3, idVerT5 = 4;
    unsigned int idEdgT1 = 0, idEdgT2 = 1, idEdgT3 = 2, idEdgT4 = 3, idEdgT5 = 4, idEdgT6 = 5, idEdgT7 = 6, idEdgT8 = 7;
    unsigned int idTriT1 = 0, idTriT2 = 1, idTriT3 = 2, idTriT4 = 3;
    unsigned int markerVerT1 = 1, markerVerT2 = 2, markerVerT3 = 3, markerVerT4 = 4, markerVerT5 = 0;
    unsigned int markerEdgT1 = 5, markerEdgT2 = 6, markerEdgT3 = 7, markerEdgT4 = 8, markerEdgT5 = 0, markerEdgT6 = 0, markerEdgT7 = 0, markerEdgT8 = 0;
    Vector2d CoordT1 = {0, 0};
    Vector2d CoordT2 = {6, 0};
    Vector2d CoordT3 = {6, 4};
    Vector2d CoordT4 = {1, 3};
    Vector2d CoordT5 = {1, 1};

    Cell0D vertT1 = Cell0D(idVerT1, markerVerT1, CoordT1), vertT2 = Cell0D(idVerT2, markerVerT2, CoordT2), vertT3 = Cell0D(idVerT3, markerVerT3, CoordT3), vertT4 = Cell0D(idVerT4, markerVerT4, CoordT4), vertT5 = Cell0D(idVerT5, markerVerT5, CoordT5);
    vector<Project::Cell0D> vectpT = {vertT1, vertT2, vertT3, vertT4, vertT5};
    vector<Project::Cell0D> vectpT1 = {vertT1, vertT2, vertT5};
    vector<Project::Cell0D> vectpT2 = {vertT2, vertT3, vertT5};
    vector<Project::Cell0D> vectpT3 = {vertT3, vertT4, vertT5};
    vector<Project::Cell0D> vectpT4 = {vertT4, vertT1, vertT5};

    vector<unsigned int> verEdg1 = {vertT1.Id0D, vertT2.Id0D}, verEdg2 = {vertT2.Id0D, vertT3.Id0D}, verEdg3 = {vertT3.Id0D, vertT4.Id0D}, verEdg4 = {vertT4.Id0D, vertT1.Id0D}, verEdg5 = {vertT1.Id0D, vertT5.Id0D}, verEdg6 = {vertT2.Id0D, vertT5.Id0D}, verEdg7 = {vertT3.Id0D, vertT5.Id0D}, verEdg8 = {vertT4.Id0D, vertT5.Id0D};
    Cell1D edgT1 = Cell1D(idEdgT1, markerEdgT1, verEdg1), edgT2 = Cell1D(idEdgT2, markerEdgT2, verEdg2), edgT3 = Cell1D(idEdgT3, markerEdgT3, verEdg3), edgT4 = Cell1D(idEdgT4, markerEdgT4, verEdg4), edgT5 = Cell1D(idEdgT5, markerEdgT5, verEdg5), edgT6 = Cell1D(idEdgT6, markerEdgT6, verEdg6), edgT7 = Cell1D(idEdgT7, markerEdgT7, verEdg7), edgT8 = Cell1D(idEdgT8, markerEdgT8, verEdg8);
    vector<Project::Cell1D> vectsT = {edgT1, edgT2, edgT3, edgT4, edgT5, edgT6, edgT7, edgT8};

    array<unsigned int, 3> verTri1 = {vertT1.Id0D, vertT2.Id0D, vertT5.Id0D}, verTri2 = {vertT2.Id0D, vertT3.Id0D, vertT5.Id0D}, verTri3 = {vertT3.Id0D, vertT4.Id0D, vertT5.Id0D}, verTri4 = {vertT4.Id0D, vertT1.Id0D, vertT5.Id0D};
    array<unsigned int, 3> edgTri1 = {edgT1.Id1D, edgT6.Id1D, edgT5.Id1D}, edgTri2 = {edgT2.Id1D, edgT7.Id1D, edgT6.Id1D}, edgTri3 = {edgT3.Id1D, edgT8.Id1D, edgT7.Id1D}, edgTri4 = {edgT4.Id1D, edgT5.Id1D, edgT8.Id1D};
    Cell2D triT1 = Cell2D(idTriT1, verTri1, edgTri1, vectpT1), triT2 = Cell2D(idTriT2, verTri2, edgTri2, vectpT2), triT3 = Cell2D(idTriT3, verTri3, edgTri3, vectpT3), triT4 = Cell2D(idTriT4, verTri4, edgTri4, vectpT4);
    vector<Project::Cell2D> vecttT = {triT1, triT2, triT3, triT4};

    //vector<vector<unsigned int>> MatrAd = MatrAdiac(vecttT, vectsT).Matr;
    vector<vector<unsigned int>> MatrAd = MatrAdiac(vecttT, vectsT);


    Project::Cell2D* trisuppT = &vecttT[1];
    Bisect(trisuppT, vectpT, vectsT, vecttT, MatrAd); // lato lungo interno -> parte propagazione

    //area tri 1 = 5
    //area tri 6 = 4.5
    //len edge 0 = 3
    //len edge 9 = rad 5

    EXPECT_EQ(vecttT[1].Area(), 5);
    EXPECT_EQ(vecttT[5].Area(), 2.5);
    EXPECT_EQ(vectsT[6].LengthEdge(vectpT), sqrt(8.5));
    EXPECT_EQ(vectsT[8].LengthEdge(vectpT), sqrt(12.5));
    EXPECT_EQ(MatrAd[5][0], 0);
    EXPECT_EQ(MatrAd[5][1], 4);
    EXPECT_EQ(MatrAd[8][0], 1);
    EXPECT_EQ(MatrAd[8][1], 4);
    


}




//TEST(TestEmpty, TestEmpty)
//{
//  Project::Empty empty;
//  ASSERT_NO_THROW(empty.Show());
//}



#endif // __TEST_EMPTY_H


// constr x3


// sorting
// import x3
// bisect
// propagazione
