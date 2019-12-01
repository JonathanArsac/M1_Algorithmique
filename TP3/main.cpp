
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
  int meilleurValeur=std::numeric_limits<int>::max();
  for(unsigned int i=0;i<matrice.size();i++){
    x[i]= !x[i];
    int resultatUBPQ = UBPQ(matrice,x);
    //std::cout<<" res "<<resultatUBPQ<<" val : "<<meilleurValeur<<std::endl;
    if(resultatUBPQ<=meilleurValeur){
      if(resultatUBPQ<meilleurValeur){
        bitsAChanger.clear();
      }

      bitsAChanger.push_back(i);
      meilleurValeur=resultatUBPQ;
    }
    x[i]= !x[i];
  }
  // random
  srand(time(NULL));


  int positionBit = bitsAChanger[(rand()%bitsAChanger.size())];
  x[positionBit]=!x[positionBit];

  return x;
}

std::vector<int> steepestHillClimbing(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &maxDeplacement){
  int nbDeplacement{0};
  bool aucunmeilleurVoisintrouve = false;

  while(nbDeplacement<maxDeplacement && aucunmeilleurVoisintrouve==false){
    std::vector<int> xprime= meilleur_voisin(matrice,x);

    //std::cout << " 1 : "<<UBPQ(matrice,xprime) << " 2 : "<< UBPQ(matrice,x)<<std::endl;
    if(UBPQ(matrice,xprime)<UBPQ(matrice,x)){
      x=xprime;
    }else{
      aucunmeilleurVoisintrouve=true;
    }
    nbDeplacement++;
  }
  return x;
}

std::vector<int> varianteSteepestHillClimbing(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &maxDeplacement,const int &maxEssai){
  int nbEssai{0};
  int meilleurValeur=std::numeric_limits<int>::max();
  std::vector<int> resultat;
  while(nbEssai<=maxEssai){
    std::cout<<" Essai "<<nbEssai<<" "<<std::endl;
    std::cout<<"Vecteur : "<<std::endl;
    for(unsigned int i=0;i<x.size();i++){

      std::cout << x[i]<<" ";
    }
    std::cout<<std::endl;
    std::vector<int> xprime=steepestHillClimbing(matrice,x,maxDeplacement);

    srand(time(NULL)*nbEssai);

    for(unsigned int i=0;i<x.size();i++){
      x[i]=(rand()%2);
    }
    nbEssai++;
    int resultatUBPQ=UBPQ(matrice,xprime);
    if (resultatUBPQ<meilleurValeur){
      meilleurValeur=resultatUBPQ;
      resultat=xprime;
    }
  }
  return resultat;
}

int main(int argc, char** argv)
{
  int tailleMatrice;
  int p;

  std::vector<std::vector<int>> matrice;

  lectureDonnees(argv[1],matrice,tailleMatrice,p);
  /*
  std::cout <<"tailleMatrice = "<<tailleMatrice<<std::endl;
  std::cout <<"p = "<<p<<std::endl;

  std::cout << " Matrice = "<<std::endl;
  for( int i=0;i<tailleMatrice;i++){
  for( int j=0;j<tailleMatrice;j++){
  std::cout << matrice[i][j] << " ";
}
std::cout<<std::endl;
}
*/

std::vector<int> vecteur(tailleMatrice);
srand(time(NULL));
std::cout << " Vecteur : ";
for(int i=0;i<tailleMatrice;i++){
  vecteur[i]=(rand()%2);
  std::cout << vecteur[i]<<" ";
}
std::cout<<std::endl;


std::vector<int> vecteurMeilleurVoisin =varianteSteepestHillClimbing(matrice,vecteur,40,3) ;
std::cout << "Meilleur voisin = ";
for(int i=0;i<tailleMatrice;i++){
  std::cout << vecteurMeilleurVoisin[i]<<" ";
}
std::cout  << std::endl;



return 0;
}
