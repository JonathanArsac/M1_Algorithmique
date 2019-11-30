
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;


int UBPQ(vector<vector<int>> t,vector<int> vecteur){

    int resultat=0;
    for(int i=0;i<t.size();i++){
      for(int j=0;j<t.size();j++){
        resultat+=t[i][j]*vecteur[i]*vecteur[j];
      }

    }
    return resultat;
}

int meilleur_voisin(vector<int> x){
/*  vector<int> bitAAChanger;
  int meilleurValeur=INFINY;
  for(int i=0;i<X.size();i++){
    X[i]= !X[i];
    if(UBQP(X)<=meilleurValeur){
      bitAAChanger.push_back(i);
    }
  }*/
  // random
}
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
  vector<int> vecteur={1,1,0,1,0,0};
  srand(time(0));
  cout << " Vecteur : ";
  for(int i=0;i<tailleMatrice;i++){
    //vecteur[i]=(rand()%2);
    cout << vecteur[i]<<" ";
  }
  cout<<endl;



  cout << "Resultat = "<<UBPQ(t,vecteur)<<endl;
  return 0;
}
