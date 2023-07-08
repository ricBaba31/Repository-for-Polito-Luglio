#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include <algorithm>
#include "cmath"
#include "empty_class.hpp"


using namespace std;
using namespace Eigen;
//using namespace Project;





namespace Project{

//void Propagazione(unsigned int idLatoTagliatoVecchio, unsigned int idLatoTagliatoNuovo, Project::Cell2D Triangolo, unsigned int latoMax);


Project::Cell0D::Cell0D(unsigned int& id, unsigned int& marker, Vector2d& coord)
    {
    Id0D = id;
    marker0D = marker;
    Coord = coord;
    };



Project::Cell1D::Cell1D(unsigned int& id,unsigned int& marker,vector<unsigned int>& vertices)
    {
    Id1D = id;
    marker1D = marker;
    //Vertices1D = vertices;

    if (vertices.size() >= 2)
        {
            Vertices1D = vertices;
        }
        else
        {
            cerr << "Invalid number of vertices for Cell1D with id: " << id << endl;

        }
    };

Project::Cell2D::Cell2D(unsigned int& id, array<unsigned int, 3>& Edges2D, vector<Project::Cell0D>& vectp2d)
    {
    Id2D = id;
    Edges = Edges2D;
    vectp2D = vectp2d;
    };






//unsigned int numbercell0D123;
//vector<Project::Cell0D> vectp;
//unsigned int numbercell1D123;
//vector<Project::Cell1D> vects;
//vector<double> LengthEdges123;
//unsigned int numbercell2D123;
//std::vector<vector<unsigned int>> LenghtMax123;
//vector<Project::Cell2D> vectt;






double Project::Cell1D::LengthEdge(vector<Project::Cell0D>& vectp){
    unsigned int A = Vertices1D[0];
    unsigned int B = Vertices1D[1];
    Vector2d coordOrigin = vectp[A].Coord;
    //double coordOriginx = vectp[A].Coord[0];
    //cout << coordOrigin[0] << endl;
    //double coordOriginy = vectp[A].Coord[1];
    Vector2d coordEnd = vectp[B].Coord;
    //double coordEndx = vectp[B].Coord[0];
    //double coordEndy = vectp[B].Coord[1];

    double len = (coordEnd-coordOrigin).norm();
    //double len = sqrt(pow(coordOriginx - coordEndx, 2)+pow(coordOriginy - coordEndy, 2));
    //cout << len << endl;
    return len;
    }

//PROBLEMA TOLLERANZA
unsigned int Project::Cell2D::maxedge(vector<Project::Cell1D>& vects, vector<Project::Cell0D>& vectp){
    unsigned int indmax = 0;
    double max = vects[Edges[0]].LengthEdge(vectp);
    for (unsigned int i = 1; i<3; i++){
        if(vects[Edges[i]].LengthEdge(vectp)  > max - tol1D){  // check
            max = vects[Edges[i]].LengthEdge(vectp);
            indmax = i;
        }
    }
    return Edges[indmax];

}

double Project::Cell2D::Area(){
             //Formula dell'area di Gauss
             double A_12 = (vectp2D[0].Coord[0]*vectp2D[1].Coord[1]) - (vectp2D[0].Coord[1]*vectp2D[1].Coord[0]);
             double A_23 = (vectp2D[1].Coord[0]*vectp2D[2].Coord[1]) - (vectp2D[1].Coord[1]*vectp2D[2].Coord[0]);
             double A_31 = (vectp2D[2].Coord[0]*vectp2D[0].Coord[1]) - (vectp2D[2].Coord[1]*vectp2D[0].Coord[0]);
             return (abs((A_12+A_23+A_31))/2);
  }

//double Project::Cell2D::Area(){
//    double A = this->AreaProvv(vectp);
//    return A;
//}



//METODI LENEDGE, MAXEDGE, (AREA vince)

// !! se nella parte iterativa il lato non viene tolto ma aggiornato con nuova end, non c'è riscalamento id nei vettori -> non serve ciclo for !!

//metterei double anziché void




//IMPORTAZIONE






bool ImportCell0Ds(vector<Project::Cell0D>& vettorePunti, string file0)
{

ifstream file;
file.open(file0);

if(file.fail()){
return false;
}

list<string> listLines;
string line;
while (getline(file, line))
    listLines.push_back(line);

file.close();

listLines.pop_front();

unsigned int numbercell0D123 = listLines.size();

if (numbercell0D123 == 0)
{
    cerr << "There is no cell 0D" << endl;
    return false;
}



for (const string& line : listLines)
{
istringstream converter(line);

unsigned int id;
unsigned int marker;
Vector2d coord;

converter >>  id >> marker >> coord[0] >> coord[1];


Project::Cell0D point = Project::Cell0D(id,marker,coord);
vettorePunti.push_back(point);
//cout << point.Coord << endl;

//    if( marker != 0)
//    {
//      if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
//        mesh.Cell0DMarkers.insert({marker, {id}});
//      else
//        mesh.Cell0DMarkers[marker].push_back(id);
//    }

  }
  file.close();
  return true;
}



bool ImportCell1Ds(vector<Project::Cell1D>& vettoreLati, string file1)
{

  ifstream file;
  file.open(file1);

  if(file.fail())
    return false;

  list<string> listLines;
  string line;
  while (getline(file, line))
    listLines.push_back(line);

  listLines.pop_front();

  unsigned int numbercell1D123 = listLines.size();

  if (numbercell1D123 == 0)
  {
    cerr << "There is no cell 1D" << endl;
    return false;
  }



  for (const string& line : listLines)
  {
    istringstream converter(line);

    unsigned int id;
    unsigned int marker;
    vector<unsigned int> vertices(2);

    converter >>  id >> marker >> vertices[0] >> vertices[1];
    Project::Cell1D segment = Project::Cell1D(id,marker,vertices);
    vettoreLati.push_back(segment);
    //cout << segment.LengthEdge(vettorePunti) << endl;
    //LengthEdges123.push_back(segment.LengthEdge(vettorePunti));


  }

  file.close();

  return true;
}



bool ImportCell2Ds(vector<Project::Cell2D>& vettoreTriangoli, vector<Project::Cell0D>& vettorePunti, string file2)
{

  ifstream file;
  file.open(file2);

  if(file.fail())
    return false;

  list<string> listLines;
  string line;
  while (getline(file, line))
    listLines.push_back(line);

  listLines.pop_front();


  unsigned int numbercell2D123 = listLines.size();

  if (numbercell2D123 == 0)
  {
    cerr << "There is no cell 2D" << endl;
    return false;
  }



  for (const string& line : listLines)
  {
    istringstream converter(line);

    unsigned int id;
    array<unsigned int, 3> vertices;
    array<unsigned int, 3> edges;

    converter >>  id;
    for(unsigned int i = 0; i < 3; i++)
      converter >> vertices[i];

    for(unsigned int i = 0; i < 3; i++)
      converter >> edges[i];


    vector<Project::Cell0D> vectp2DF = {vettorePunti[vertices[0]], vettorePunti[vertices[1]], vettorePunti[vertices[2]]};
    Project::Cell2D triangle = Project::Cell2D(id,edges, vectp2DF);
    vettoreTriangoli.push_back(triangle);

  }
  file.close();
  return true;
}

//Project::TriangularMesh mesh = Project::TriangularMesh(numbercell0D123, vectp, numbercell1D123, vects, LengthEdges123, numbercell2D123, LenghtMax123, vectt);





//----------------------------------------------------------------------

// RAFFINAMENTO:

// MATRICE DI ADIACENZA [OK]
// ORDINAMENTO PER AREA [Riccardo]
// PUNTO MEDIO LATO LUNGO (CHE SI AGGIORNA CON STESSA ORIGIN E NUOVA END, LEN = LEN/2) (NEW LATO, LEN = LEN/2)
// TAGLIO LATO LUNGO


//MatrAdiac::MatrAdiac(vector<Project::Cell2D>& vectt, vector<Project::Cell1D>& vects) {
vector<vector<unsigned int>> MatrAdiac(vector<Project::Cell2D>& vectt, vector<Project::Cell1D>& vects){
    vector<vector<unsigned int>> MatrAdiac1(vects.size(), vector<unsigned int>());
    for (unsigned int i = 0; i < vectt.size(); i++) {
        for (unsigned int j = 0; j < 3; j++) {
            MatrAdiac1[vectt[i].Edges[j]].push_back(vectt[i].Id2D);
        }
    }
    return MatrAdiac1;
    //Matr = MatrAdiac;
}





void Bisect(Project::Cell2D* triangleToBisect, vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects, vector<Project::Cell2D>& vectt, vector<vector<unsigned int>>& Matr){

    unsigned int idTTBmemo = triangleToBisect->Id2D;
    unsigned int longest = triangleToBisect->maxedge(vects, vectp);
    vector<Project::Cell0D> vectp2Dnew = triangleToBisect->vectp2D;
    //vector<Project::Cell0D> vectp2Dupd;
    //serve subito controllo: 1) marker lato lungo 2) lato lungo dell'eventuale altro triangolo
    unsigned int markerMaxEdge = vects[longest].marker1D;
    unsigned int idAltroMaxEdge = 0;
    unsigned int idAltroTri = 0;
    if (markerMaxEdge == 0) {
        for (unsigned int i = 0; i<2; i++) {
            if (Matr[longest][i] != triangleToBisect->Id2D) {
                idAltroTri = Matr[longest][i];
                idAltroMaxEdge = vectt[idAltroTri].maxedge(vects, vectp);
            }
        }
    }


    // salvo vertici e lati che poi dovrò aggiornare
    array<unsigned int, 3> latiTriNuovo = triangleToBisect->Edges;

    // inizio bisezione
    Vector2d midCoord;
    midCoord[0] = (vectp[vects[longest].Vertices1D[0]].Coord[0] + vectp[vects[longest].Vertices1D[1]].Coord[0]) *0.5;
    midCoord[1] = (vectp[vects[longest].Vertices1D[0]].Coord[1] + vectp[vects[longest].Vertices1D[1]].Coord[1]) *0.5;

    unsigned int markerP = vects[longest].marker1D;

    unsigned int newIndexpoint = vectp.size();
    Project::Cell0D newVertex = Cell0D(newIndexpoint, markerP, midCoord);
    vectp.push_back(newVertex);
    //vectp2D.push_back(newVertex);
    //vectp2D1.push_back(newVertex);

    unsigned int opposite = 0;
    for(unsigned int i = 0; i < 3; i++)
    {
        if(!(vects[longest].Vertices1D[0] == triangleToBisect->vectp2D[i].Id0D || vects[longest].Vertices1D[1] == triangleToBisect->vectp2D[i].Id0D))
            {
            opposite = triangleToBisect->vectp2D[i].Id0D;
            //vectp2D.push_back(vectp[opposite]);
            //vectp2D1.push_back(vectp[opposite]);
            break;
            }
    }

    vector<unsigned int> MedianaVert = {opposite, newVertex.Id0D};

    unsigned int idMediana = vects.size();
    unsigned int idNewEdge2 = idMediana + 1;

    unsigned int markerMediana = 0; // NON PUO' ESSERE ALTRIMENTI



    //Creo segm mediana
    Cell1D Mediana = Cell1D(idMediana, markerMediana, MedianaVert);
    vects.push_back(Mediana);

    vector<unsigned int> NewSegVert = {newVertex.Id0D, vects[longest].Vertices1D[1]};



    //Creo segm pto medio -> end vecchia
    Cell1D newSegment = Cell1D(idNewEdge2, vects[longest].marker1D, NewSegVert);
    vects.push_back(newSegment);


    //aggiorno segm origin vecchia -> pto medio
    vects[longest].Vertices1D[1] = newVertex.Id0D;  // GUARDATO FINO A QUA



    //vertici effettivi del triangolo nuovo
    for (unsigned int i = 0;i<3;i++) {
        if (vectp2Dnew[i].Id0D == vects[longest].Vertices1D[0]) {
            vectp2Dnew[i] = newVertex;
            //vectp2D.push_back(vectp[vertTriNuovo[i]]);
            break;
        };
    }

    // vertici effettivi del triangolo aggiornato
    for (unsigned int i = 0;i<3;i++) {
        if (triangleToBisect->vectp2D[i].Id0D != opposite && triangleToBisect->vectp2D[i].Id0D != vects[longest].Vertices1D[0]) {

            triangleToBisect->vectp2D[i] = newVertex;
            //vectp2D1.push_back(vectp[triangleToBisect.Vertices2D[i]]);
            //triangleToBisect.vectp2D = vectp2D1;
            break;
        };
    }


    // lati effettivi del triangolo aggiornato
    for (unsigned int i=0; i < 3; i++) {
        if ((vects[triangleToBisect->Edges[i]].Vertices1D[0] == opposite && vects[triangleToBisect->Edges[i]].Vertices1D[1] == newSegment.Vertices1D[1]) || (vects[triangleToBisect->Edges[i]].Vertices1D[1] == opposite && vects[triangleToBisect->Edges[i]].Vertices1D[0] == newSegment.Vertices1D[1])) {
            triangleToBisect->Edges[i] = Mediana.Id1D;
            break;
        }
    }

    // lati effettivi del triangolo nuovo


    for (unsigned int i=0; i < 3; i++) {
        if (latiTriNuovo[i] == longest) {
            latiTriNuovo[i] = newSegment.Id1D;
        }
        if ((vects[latiTriNuovo[i]].Vertices1D[0] == opposite && vects[latiTriNuovo[i]].Vertices1D[1] == vects[longest].Vertices1D[0]) || (vects[latiTriNuovo[i]].Vertices1D[1] == opposite && vects[latiTriNuovo[i]].Vertices1D[0] == vects[longest].Vertices1D[0])) {
            latiTriNuovo[i] = Mediana.Id1D;
        }
    }



    // creazione triangolo nuovo
    unsigned int idnewTri = vectt.size();
    Cell2D newTri = Cell2D(idnewTri, latiTriNuovo, vectp2Dnew);
    vectt.push_back(newTri);
    triangleToBisect = &vectt[idTTBmemo];


    // aggiorno matrice di adiacenza

    // aggiungo mediana
    vector<unsigned int> MatrMediana = {triangleToBisect->Id2D, newTri.Id2D};
    Matr.push_back(MatrMediana);

    // aggiungo newSegment
    if (vects[longest].marker1D == 0){
        vector<unsigned int> MatrNewSegment = {newTri.Id2D, idAltroTri};
        Matr.push_back(MatrNewSegment);
    }
    else {
        vector<unsigned int> MatrNewSegment = {newTri.Id2D};
        Matr.push_back(MatrNewSegment);
    }


    // aggiorno terzo lato
    for (unsigned int i=0; i<3; i++) {
        if(newTri.Edges[i] != Mediana.Id1D && newTri.Edges[i] != newSegment.Id1D){
            if(vects[newTri.Edges[i]].marker1D == 0){
                for (unsigned int j = 0; j < 2; j++) {
                    if(Matr[newTri.Edges[i]][j] == triangleToBisect->Id2D){
                        Matr[newTri.Edges[i]][j] = newTri.Id2D;
                        break;
                    }
                }
            }

            else{
                Matr[newTri.Edges[i]][0] = newTri.Id2D;
            }

        }
    }

    if (markerMaxEdge == 0) {
        Cell2D* AltroTri = &vectt[idAltroTri];
        //unsigned int recursionDepth = 0;
        unsigned int newSegmentId = newSegment.Id1D;
        Propagazione(longest, newSegmentId, AltroTri, idAltroMaxEdge, vectp, vects, vectt, Matr); // recursionDepth);
    }


} // fine Bisect



void Propagazione(unsigned int& idLatoTagliatoVecchio, unsigned int& idLatoTagliatoNuovo, Cell2D* Triangolo, unsigned int& latoMax, vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects, vector<Project::Cell2D>& vectt, vector<vector<unsigned int>>& Matr)
{
    unsigned int idTTBmemoPropa = Triangolo->Id2D;

    if (idLatoTagliatoVecchio == latoMax){

        vector<Project::Cell0D> vectpUlti = Triangolo->vectp2D;

        // collega pto medio e vertice opposto

        array<unsigned int, 3> latiUltimoTri = Triangolo->Edges;


        unsigned int newopposite = 0;
        for(unsigned int i = 0; i < 3; i++)
        {
            if(vects[idLatoTagliatoVecchio].Vertices1D[0] != Triangolo->vectp2D[i].Id0D && vects[idLatoTagliatoNuovo].Vertices1D[1] != Triangolo->vectp2D[i].Id0D)
                {
                newopposite = Triangolo->vectp2D[i].Id0D;
                //vectpUlti.push_back(vectp[newopposite]);
                break;
                }
        }

        unsigned int marker0 = 0;
        unsigned int size = vects.size();
        vector<unsigned int> vettore = {vects[idLatoTagliatoNuovo].Vertices1D[0], newopposite};
        //creo ultimo lato
        Cell1D Unione = Cell1D(size, marker0, vettore);
        vects.push_back(Unione);

        // creo Ultimo triangolo
        for (unsigned int i = 0; i<3; i++) {
            if (vectpUlti[i].Id0D == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
                vectpUlti[i] =vectp[vects[idLatoTagliatoVecchio].Vertices1D[1]];
                break;
            }
        }

        for (unsigned int i=0; i < 3; i++) {
            if (latiUltimoTri[i] == latoMax) {
                latiUltimoTri[i] = idLatoTagliatoNuovo;
            }
            if ((vects[latiUltimoTri[i]].Vertices1D[0] == newopposite && vects[latiUltimoTri[i]].Vertices1D[1] == vects[latoMax].Vertices1D[0]) || (vects[latiUltimoTri[i]].Vertices1D[1] == newopposite && vects[latiUltimoTri[i]].Vertices1D[0] == vects[latoMax].Vertices1D[0])) {
                latiUltimoTri[i] = Unione.Id1D;
            }
        }

        unsigned int sizeT = vectt.size();



        Cell2D UltimoTriangolo = Cell2D(sizeT, latiUltimoTri, vectpUlti);
        vectt.push_back(UltimoTriangolo);
        Triangolo = &vectt[idTTBmemoPropa];

        // aggiorno vertici
        for (unsigned int i = 0; i<3; i++) {
            if (Triangolo->vectp2D[i].Id0D == vects[idLatoTagliatoNuovo].Vertices1D[1]) {

                Triangolo->vectp2D[i] = vectp[vects[idLatoTagliatoNuovo].Vertices1D[0]];
                break;
            }
        }

        // aggiorno lati
        for (unsigned int i=0; i < 3; i++) {
            if ((vects[Triangolo->Edges[i]].Vertices1D[0] == newopposite && vects[Triangolo->Edges[i]].Vertices1D[1] == vects[idLatoTagliatoNuovo].Vertices1D[1]) || (vects[Triangolo->Edges[i]].Vertices1D[1] == newopposite && vects[Triangolo->Edges[i]].Vertices1D[0] == vects[idLatoTagliatoNuovo].Vertices1D[1])) {
                Triangolo->Edges[i] = Unione.Id1D;
                break;
            }
        }


        //aggiorno matrice di adiacenza
        vector<unsigned int> MatrUnione = {Triangolo->Id2D, UltimoTriangolo.Id2D};
        Matr.push_back(MatrUnione);


        for (unsigned int i=0; i<3; i++) {
            if(UltimoTriangolo.Edges[i] != Unione.Id1D && UltimoTriangolo.Edges[i] != idLatoTagliatoNuovo){
                if (vects[UltimoTriangolo.Edges[i]].marker1D == 0) {
                    for (unsigned int j = 0; j < 2; j++) {
                        if(Matr[UltimoTriangolo.Edges[i]][j] == Triangolo->Id2D){
                            Matr[UltimoTriangolo.Edges[i]][j] = UltimoTriangolo.Id2D;
                            break;
                        }
                    }
                }
                else {
                    Matr[UltimoTriangolo.Edges[i]][0] = UltimoTriangolo.Id2D;
                }
            break;
            }

        }
        //for (unsigned int i=0; i<2; i++) {
        //    if (Matr[idLatoTagliatoNuovo][i] == Triangolo->Id2D) {
        //        Matr[idLatoTagliatoNuovo][i] = UltimoTriangolo.Id2D;
        //    }
        //}


        for (unsigned int i = 0; i<2; i++) {
            if (Matr[idLatoTagliatoNuovo][i] == Triangolo->Id2D) {
            Matr[idLatoTagliatoNuovo][i] = UltimoTriangolo.Id2D;
            }
        }




    } //fine if (stesso lato max)
    else {

        vector<Project::Cell0D> vectpPenu = Triangolo->vectp2D;


        // va fatto un if che mette l'end di latoMax = end latotagliatonuovo (caso 1)
        //                            origin latoMax = origin latotagliatovecchio (caso 2)

        //for (unsigned int i = 0; i <2 ; i++) {
        //    if (vects[latoMax].Vertices1D[i] == vects[idLatoTagliatoVecchio].Vertices1D[0] && i==1){
        //        unsigned int supporto = vects[latoMax].Vertices1D[i];
        //        vects[latoMax].Vertices1D[i] = vects[latoMax].Vertices1D[1-i];
        //        vects[latoMax].Vertices1D[1-i] = supporto;

        //    }
        //    else if (vects[latoMax].Vertices1D[i] == vects[idLatoTagliatoVecchio].Vertices1D[1] && 1==0) {
        //        unsigned int supporto = vects[latoMax].Vertices1D[i];
        //        vects[latoMax].Vertices1D[i] = vects[latoMax].Vertices1D[i+1];
        //        vects[latoMax].Vertices1D[i+1] = supporto;
        //    }
        //}

        if (vects[latoMax].Vertices1D[1] == vects[idLatoTagliatoVecchio].Vertices1D[0] || vects[latoMax].Vertices1D[0] == vects[idLatoTagliatoNuovo].Vertices1D[1])    {
            unsigned int supporto = vects[latoMax].Vertices1D[0];
            vects[latoMax].Vertices1D[0] = vects[latoMax].Vertices1D[1];
            vects[latoMax].Vertices1D[1] = supporto;
        }



        unsigned int markerLatoMax = vects[latoMax].marker1D;
        unsigned int idMaxEdgePropa;
        unsigned int idAltroTriPropa;
        if (markerLatoMax == 0) {
            for (unsigned int i = 0; i<2; i++) {
                if (Matr[latoMax][i] != Triangolo->Id2D) {
                    idAltroTriPropa = Matr[latoMax][i];
                    idMaxEdgePropa = vectt[Matr[latoMax][i]].maxedge(vects, vectp);
                }
            }
        }



        array<unsigned int, 3> latiTriNuovoPropa = Triangolo->Edges;


        Vector2d midCoordPropa;
        midCoordPropa[0] = (vectp[vects[latoMax].Vertices1D[0]].Coord[0] + vectp[vects[latoMax].Vertices1D[1]].Coord[0]) *0.5;
        midCoordPropa[1] = (vectp[vects[latoMax].Vertices1D[0]].Coord[1] + vectp[vects[latoMax].Vertices1D[1]].Coord[1]) *0.5;

        unsigned int markerPPropa = vects[latoMax].marker1D ;

        unsigned int newIndexpointPropa = vectp.size();
        Project::Cell0D newVertexPropa = Cell0D(newIndexpointPropa, markerPPropa, midCoordPropa);
        vectp.push_back(newVertexPropa);

        unsigned int oppositePropa = 0;
        for(unsigned int i = 0; i < 3; i++)
        {
            if(!(vects[latoMax].Vertices1D[0] == Triangolo->vectp2D[i].Id0D || vects[latoMax].Vertices1D[1] == Triangolo->vectp2D[i].Id0D))
                {
                oppositePropa = Triangolo->vectp2D[i].Id0D;
                break;
                }
        }

        vector<unsigned int> MedianaVertPropa = {oppositePropa, newVertexPropa.Id0D};

        unsigned int idNewEdgePropa = vects.size();

        unsigned int markerMedianaPropa = 0; // NON PUO' ESSERE ALTRIMENTI

        Cell1D MedianaPropa = Cell1D(idNewEdgePropa, markerMedianaPropa, MedianaVertPropa);
        vects.push_back(MedianaPropa);

        vector<unsigned int> NewSegVertPropa = {newVertexPropa.Id0D, vects[latoMax].Vertices1D[1]};


        unsigned int idNewEdgeTemp = idNewEdgePropa + 1;

        Cell1D newSegmentPropa = Cell1D(idNewEdgeTemp, vects[latoMax].marker1D, NewSegVertPropa);
        vects.push_back(newSegmentPropa);

        // aggiorno end pto medio propa
        vects[latoMax].Vertices1D[1] = newVertexPropa.Id0D;



        unsigned int lontano = 0;
        for (unsigned int i = 0;i<3;i++) {
            if (Triangolo->vectp2D[i].Id0D != vects[idLatoTagliatoNuovo].Vertices1D[1] && Triangolo->vectp2D[i].Id0D != vects[idLatoTagliatoVecchio].Vertices1D[0]) {
                lontano = Triangolo->vectp2D[i].Id0D;
            }
        }

        // vertici effettivi nuovo propa
        for (unsigned int i = 0;i<3;i++) {
            if (vectpPenu[i].Id0D == lontano) {
                vectpPenu[i] = newVertexPropa; // AGGIUNTO
                break;
            }
        }

        // vertici aggiornati
        for (unsigned int i = 0;i<3;i++) {
            if (Triangolo->vectp2D[i].Id0D != oppositePropa && Triangolo->vectp2D[i].Id0D != lontano) {
                Triangolo->vectp2D[i] = newVertexPropa; //AGGIUNTO
                break;
            };
        }

        // lati aggiornati
        if (vects[latoMax].Vertices1D[0] == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
            for (unsigned int i=0; i < 3; i++) {
                if (Triangolo->Edges[i] == latoMax){
                    Triangolo->Edges[i] = newSegmentPropa.Id1D;
                }
                if (Triangolo->Edges[i] == idLatoTagliatoVecchio){
                    Triangolo->Edges[i] = MedianaPropa.Id1D;
                }
            }

        }
        else { // if (vects[latoMax].Vertices1D[1] == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
            for (unsigned int i=0; i < 3; i++) {
                if (Triangolo->Edges[i] == idLatoTagliatoVecchio) {
                    Triangolo->Edges[i] = MedianaPropa.Id1D;
                }
            }
        }

        // lati effettivi nuovo propa
        if (vects[latoMax].Vertices1D[0] == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
            for (unsigned int i=0; i < 3; i++) {
                if (latiTriNuovoPropa[i] != latoMax && latiTriNuovoPropa[i] != idLatoTagliatoVecchio){
                    latiTriNuovoPropa[i] = MedianaPropa.Id1D;
                }
            }
        }
        else { // if (vects[latoMax].Vertices1D[1] == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
            for (unsigned int i=0; i < 3; i++) {
                if (latiTriNuovoPropa[i] == latoMax){
                    latiTriNuovoPropa[i] = newSegmentPropa.Id1D;
                }
                if ((vects[latiTriNuovoPropa[i]].Vertices1D[0] == oppositePropa && vects[latiTriNuovoPropa[i]].Vertices1D[1] == lontano) || (vects[latiTriNuovoPropa[i]].Vertices1D[1] == oppositePropa && vects[latiTriNuovoPropa[i]].Vertices1D[0] == lontano)) {
                    latiTriNuovoPropa[i] = MedianaPropa.Id1D;
                }
            }
        }

        unsigned int idPenultimo = vectt.size();

        //for (unsigned int i = 0; i<3; i++) {
        //    vectpPenu[i] = vectp[vertTriNuovoPropa[i]];
        //}

        Cell2D Penultimo = Cell2D(idPenultimo, latiTriNuovoPropa, vectpPenu);
        vectt.push_back(Penultimo);
        unsigned int idTTPenultimo = Penultimo.Id2D;
        Cell2D* PenultimoP = &vectt[idTTPenultimo];
        Triangolo = &vectt[idTTBmemoPropa];


        vector<Project::Cell0D> vectpResi = PenultimoP->vectp2D;

        //aggiorno PARZIALMENTE matrice di adiac

        if (vects[latoMax].Vertices1D[0] == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
            vector<unsigned int> SuppMediana = {Triangolo->Id2D, PenultimoP->Id2D};
            Matr.push_back(SuppMediana);

            if (vects[latoMax].marker1D == 0){
                vector<unsigned int> SuppNewSegmentPropa = {Triangolo->Id2D, idAltroTriPropa};
                Matr.push_back(SuppNewSegmentPropa);
            }
            else {
                vector<unsigned int> SuppNewSegmentPropa = {Triangolo->Id2D};
                Matr.push_back(SuppNewSegmentPropa);
            }

            for (unsigned int i = 0; i<2; i++) {
                if (Matr[idLatoTagliatoNuovo][i] == Triangolo->Id2D) {
                    Matr[idLatoTagliatoNuovo][i] = PenultimoP->Id2D;
                }
            }
        }
        else { // if (vects[latoMax].Vertices1D[1] == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
            vector<unsigned int> SuppMediana = {Triangolo->Id2D, PenultimoP->Id2D};
            Matr.push_back(SuppMediana);
            for (unsigned int i = 0; i<2; i++) {
                if (Matr[idLatoTagliatoVecchio][i] == Triangolo->Id2D) {
                    Matr[idLatoTagliatoVecchio][i] = PenultimoP->Id2D;
                }

            }
        }



        // collego i due punti medi

        array<unsigned int, 3> latiTriResiduoPropa = PenultimoP->Edges;
        //array<unsigned int, 3> vertTriResiduoPropa = PenultimoP->Vertices2D;


        unsigned int idUnione = vects.size();
        unsigned int markerUnione = 0;
        vector<unsigned int> vettoreUnione = {vects[idLatoTagliatoVecchio].Vertices1D[1], newVertexPropa.Id0D};

        Cell1D Unione = Cell1D(idUnione, markerUnione, vettoreUnione);
        vects.push_back(Unione);

        if (vects[latoMax].Vertices1D[0] == vects[idLatoTagliatoVecchio].Vertices1D[0]) {

            for (unsigned int i = 0; i<3; i++) {
                // aggiorno vertici
                if (PenultimoP->vectp2D[i].Id0D == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
                    PenultimoP->vectp2D[i] = vectp[vects[idLatoTagliatoVecchio].Vertices1D[1]]; //AGGIUNTO
                }
                // vert effettivi residuo
                if (vectpResi[i].Id0D == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
                    vectpResi[i] =vectp[vects[idLatoTagliatoNuovo].Vertices1D[0]]; //AGGIUNTO
                }
                // aggiorno lati
                if (PenultimoP->Edges[i] == idLatoTagliatoVecchio) {
                    PenultimoP->Edges[i] = idLatoTagliatoNuovo;
                }
                if (PenultimoP->Edges[i] == latoMax) {
                    PenultimoP->Edges[i] = Unione.Id1D;
                }
                // lati effettivi residuo
                if (latiTriResiduoPropa[i] == MedianaPropa.Id1D) {
                    latiTriResiduoPropa[i] = Unione.Id1D;
                }

            }

            unsigned int idResiduoT = vectt.size();

            //for (unsigned int i = 0; i<3; i++) {
            //    Penultimo.vectp2D[i] = vectp[Penultimo.Vertices2D[i]];
            //}

            //for (unsigned int i = 0; i<3; i++) {
            //    vectpResi[i] = vectp[vertTriResiduoPropa[i]];
            //}

            Cell2D Residuo = Cell2D(idResiduoT,  latiTriResiduoPropa, vectpResi);
            vectt.push_back(Residuo);
            //Triangolo = &vectt[idTTBmemoPropa];
            PenultimoP = &vectt[idTTPenultimo];

            // aggiorno matrice adiacenza
            vector <unsigned int> SuppUnione = {PenultimoP->Id2D, Residuo.Id2D};
            Matr.push_back(SuppUnione);
            for (unsigned int i = 0; i<2; i++) {

                if (Matr[idLatoTagliatoVecchio][i] == Triangolo->Id2D) {
                    Matr[idLatoTagliatoVecchio][i] = Residuo.Id2D;
                }
            }

            if(markerLatoMax == 0){
                for (unsigned int i = 0; i<2; i++) {
                    if (Matr[latoMax][i] == Triangolo->Id2D) {
                    Matr[latoMax][i] = Residuo.Id2D;
                    }
                }
            }
            else{
                Matr[latoMax][0] = Residuo.Id2D;
            }
        }
        else { // if (vects[latoMax].Vertices1D[1] == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
            for (unsigned int i = 0; i<3; i++) {
                // aggiorno vert penultimo
                if (PenultimoP->vectp2D[i].Id0D == vects[idLatoTagliatoNuovo].Vertices1D[1]) {
                    PenultimoP->vectp2D[i] = vectp[vects[idLatoTagliatoNuovo].Vertices1D[0]]; //AGGIUNTO
                }
                // vert effettivi res
                if (vectpResi[i].Id0D == vects[idLatoTagliatoVecchio].Vertices1D[0]) {
                    vectpResi[i] =vectp[vects[idLatoTagliatoNuovo].Vertices1D[0]]; //AGGIUNTO
                }
                // aggiorno lati
                if (PenultimoP->Edges[i] == newSegmentPropa.Id1D) {
                    PenultimoP->Edges[i] = Unione.Id1D;
                }
                // lati effettivi residuo
                if (latiTriResiduoPropa[i] == MedianaPropa.Id1D) {
                    latiTriResiduoPropa[i] = Unione.Id1D;
                }
                if (latiTriResiduoPropa[i] == idLatoTagliatoVecchio) {
                    latiTriResiduoPropa[i] = idLatoTagliatoNuovo;
                }
            }

            unsigned int idResiduo = vectt.size();

            //for (unsigned int i = 0; i<3; i++) {
            //    Penultimo.vectp2D[i] = vectp[Penultimo.Vertices2D[i]]; // CONTROLLAAAAAAAAAAAAAAA E AGGIORNAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            //}

            //for (unsigned int i = 0; i<3; i++) {
            //    vectpResi[i] = vectp[vertTriResiduoPropa[i]];
            //}

            Cell2D Residuo = Cell2D(idResiduo, latiTriResiduoPropa, vectpResi);
            vectt.push_back(Residuo);
            Triangolo = &vectt[idTTBmemoPropa];
            PenultimoP = &vectt[idTTPenultimo];

            // aggiorno matrice adiacenza

            vector<unsigned int> SuppNewSegmentPropa;
            if(markerLatoMax == 0){
                SuppNewSegmentPropa = {Residuo.Id2D, idAltroTriPropa};
            }
            else{
                SuppNewSegmentPropa = {Residuo.Id2D};
            }
            vector<unsigned int> SuppUnione = {PenultimoP->Id2D, Residuo.Id2D};

            Matr.push_back(SuppNewSegmentPropa);
            Matr.push_back(SuppUnione);
            for (unsigned int i = 0; i<2; i++) {
                if (Matr[idLatoTagliatoNuovo][i] == Triangolo->Id2D) {
                    Matr[idLatoTagliatoNuovo][i] = Residuo.Id2D;
                }
            }
        }

        // void Propagazione(unsigned int idLatoTagliatoVecchio, unsigned int idLatoTagliatoNuovo, Cell2D Triangolo, unsigned int latoMax){
        // in questo caso è ricorsiva
        if (markerLatoMax == 0) {
            Cell2D* AltroTriPropa = &vectt[idAltroTriPropa];
            Project::Propagazione(latoMax, newSegmentPropa.Id1D, AltroTriPropa, idMaxEdgePropa, vectp, vects, vectt, Matr);
        }
    } // fine else (lato lungo diverso dal precedente)
} // fine Propagazione

//void PropagazioneRicorsiva(unsigned int& idLatoTagliatoVecchio, unsigned int& idLatoTagliatoNuovo, Cell2D& Triangolo, unsigned int& latoMax, vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects, vector<Project::Cell2D>& vectt, vector<vector<unsigned int>>& Matr, unsigned int& numberRecurs){
//    Propagazione(idLatoTagliatoVecchio, idLatoTagliatoNuovo, Triangolo, latoMax, vectp, vects, vectt, Matr, numberRecurs);


bool ExportVertices(vector<Project::Cell0D>& vectp){
         ofstream file;
         string outputFile = "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Output-40-Cell0Ds.csv";
         file.open(outputFile);

         if(file.fail())
         {
           return false;
         }

         file<<"Id marker X Y"<<endl;

         for(unsigned int i = 0; i < vectp.size();i++)
         {
           file<<vectp[i].Id0D<<" "<<vectp[i].marker0D<<" "<<vectp[i].Coord[0]<<" "<<vectp[i].Coord[1]<<endl;
         }

         file.close();
         return true;

}
bool ExportEdges(vector<Project::Cell0D>& vectp, vector<Project::Cell1D>& vects){

        ofstream file;
        string outputFile = "C:/Users/utente/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Output-40-Cell1Ds.csv";
        file.open(outputFile);

        if(file.fail())
        {
          return false;
        }

        file<<"Id marker V1X V1Y V2X V2Y"<<endl;

        for(unsigned int i = 0; i < vects.size(); i++)
        {
            file<<vects[i].Id1D<<' ';
            file<<vects[i].marker1D<<' ';

            for(unsigned int j = 0; j < 2; j++){
            file<<vectp[vects[i].Vertices1D[j]].Coord[0]<<' ';
            file<<vectp[vects[i].Vertices1D[j]].Coord[1]<<' ';
            }

        file<<endl;
        }

        file.close();

        return true;

}






}   // fine namespace Cells


//-----------------------------------------------------------------------
