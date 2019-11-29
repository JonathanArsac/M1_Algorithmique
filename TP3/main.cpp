
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

int main()
{
   ifstream monFlux {"./partition6.txt"  };

   int nombre;
   int tailleMatrice;
   int p;

   vector<vector<int>> t;

   if(monFlux){

   monFlux>>tailleMatrice;
   monFlux>>p;

  for(int i=0;i<tailleMatrice;i++){
    t.push_back(vector<int>(tailleMatrice));
    for (int j=0; j < tailleMatrice; j++){
    monFlux>>nombre;

      t[i][j]=nombre;
    }
  }
    //Tout est prêt pour la lecture.
}
else
{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
}

cout <<"tailleMatrice = "<<tailleMatrice<<endl;
cout <<"p = "<<p<<endl;

cout << " Matrice = "<<endl;
  for(int i=0;i<tailleMatrice;i++){
    for(int j=0;j<tailleMatrice;j++){
        cout << t[i][j] << " ";
    }
    cout<<endl;
  }
vector<int> vecteur(tailleMatrice);
 srand(time(0));
cout << " Vecteur : ";
for(int i=0;i<tailleMatrice;i++){
  vecteur[i]=(rand()%2);
  cout << vecteur[i]<<" ";
}
cout<<endl;
   return 0;
}
