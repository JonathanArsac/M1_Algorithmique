
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <limits>


void lectureDonnees(const char *fichier,std::vector<std::vector<int>> &matrice,int &tailleMatrice,int &p){
  std::ifstream monFlux {fichier};

  int nombre;

  if(monFlux){

    monFlux>>tailleMatrice;
    monFlux>>p;

    for(int i=0;i<tailleMatrice;i++){
      matrice.push_back(std::vector<int>(tailleMatrice));
      for (int j=0; j < tailleMatrice; j++){
        monFlux>>nombre;

        matrice[i][j]=nombre;
      }
    }
    //Tout est prêmatrice pour la lecture.
  }
  else
  {
    std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
  }

}

int UBPQ(const std::vector<std::vector<int>> &matrice,const std::vector<int> &vecteur){

  int resultat=0;
  for(unsigned int i=0;i<matrice.size();i++){
    for(unsigned int j=0;j<matrice.size();j++){
      resultat+=matrice[i][j]*vecteur[i]*vecteur[j];
    }
  }
  return resultat;
}

std::vector<int> meilleur_voisin(const std::vector<std::vector<int>> &matrice,std::vector<int> x){
  std::vector<int> bitsAChanger;
  int meilleurValeur=std::numeric_limits<int>::infinity();
  for(unsigned int i=0;i<matrice.size();i++){
    x[i]= !x[i];
    int resultatUBPQ = UBPQ(matrice,x);
    if(resultatUBPQ<=meilleurValeur){
      bitsAChanger.push_back(i);
      meilleurValeur=resultatUBPQ;
    }
    x[i]= !x[i];
  }
  // random
  srand(time(0));
  int positionBit = bitsAChanger[(rand()%bitsAChanger.size())];
  x[positionBit]=!x[positionBit];

  return x;
}

int main(int argc, char** argv)
{
  int tailleMatrice;
  int p;

  std::vector<std::vector<int>> matrice;

  lectureDonnees(argv[1],matrice,tailleMatrice,p);
  std::cout <<"tailleMatrice = "<<tailleMatrice<<std::endl;
  std::cout <<"p = "<<p<<std::endl;

  std::cout << " Matrice = "<<std::endl;
  for( int i=0;i<tailleMatrice;i++){
    for( int j=0;j<tailleMatrice;j++){
      std::cout << matrice[i][j] << " ";
    }
    std::cout<<std::endl;
  }
  std::vector<int> vecteur={1,1,0,1,0,0};
  srand(time(0));
  std::cout << " Vecteur : ";
  for(int i=0;i<tailleMatrice;i++){
    //vecteur[i]=(rand()%2);
    std::cout << vecteur[i]<<" ";
  }
  std::cout<<std::endl;


  std::vector<int> vecteurMeilleurVoisin =meilleur_voisin(matrice,vecteur) ;
  std::cout << "Resultat = ";
  for(int i=0;i<tailleMatrice;i++){
    //vecteur[i]=(rand()%2);
    std::cout << vecteurMeilleurVoisin[i]<<" ";
  }
  std::cout  << '\n';
  return 0;
}
