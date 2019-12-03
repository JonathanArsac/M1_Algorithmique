
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <limits>
#include <algorithm>


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

std::vector<int> meilleur_voisin(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &p){
  std::vector<int> bitsAChanger(0);
  int meilleurValeur=std::numeric_limits<int>::max();
  int sommeBit=0;
  // variante avec p
  for(unsigned int i=0;i<matrice.size();i++){
    sommeBit+=x[i];
  }
  if(sommeBit>=p-1){

    for(unsigned int i=0;i<matrice.size();i++){
      sommeBit=0;
      x[i]= !x[i];
      for(unsigned int j=0;j<matrice.size();j++){
        sommeBit+=x[j];
        //std::cout<<"sommeBit "<<sommeBit<<std::endl;

      }
      if(sommeBit>=p){

        int resultatUBPQ = UBPQ(matrice,x);
        //std::cout<<" res "<<resultatUBPQ<<" val : "<<meilleurValeur<<std::endl;
        if(resultatUBPQ<=meilleurValeur){
          if(resultatUBPQ<meilleurValeur){
            bitsAChanger.clear();
          }

          bitsAChanger.push_back(i);
          meilleurValeur=resultatUBPQ;
        }
      }

      x[i]= !x[i];
    }
    // random
    srand(time(NULL));
    int positionBit = bitsAChanger[(rand()%bitsAChanger.size())];
    x[positionBit]=!x[positionBit];
  }
  return x;
}

std::vector<int> steepestHillClimbing(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &maxDeplacement,const int &p){
  int nbDeplacement{0};
  bool aucunmeilleurVoisintrouve = false;

  while(nbDeplacement<maxDeplacement && aucunmeilleurVoisintrouve==false){
    std::vector<int> xprime= meilleur_voisin(matrice,x,p);

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

std::vector<int> varianteSteepestHillClimbing(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &maxDeplacement,const int &maxEssai,const int &p){
  int nbEssai{0};
  int meilleurValeur=std::numeric_limits<int>::max();
  std::vector<int> resultat=x;
  while(nbEssai<=maxEssai){
    //  std::cout<<" Essai "<<nbEssai<<" "<<std::endl;
    /*  std::cout<<"Vecteur : "<<std::endl;
    for(unsigned int i=0;i<x.size();i++){

      std::cout << x[i]<<" ";
    }
    std::cout<<std::endl;*/
    std::vector<int> xprime=steepestHillClimbing(matrice,x,maxDeplacement,p);
    int sommeBit=0;
    // variante avec p
    for(unsigned int i=0;i<matrice.size();i++){
      sommeBit+=xprime[i];
    }
    if(sommeBit>=p){
      int resultatUBPQ=UBPQ(matrice,xprime);
      if (resultatUBPQ<meilleurValeur){
        meilleurValeur=resultatUBPQ;
        resultat=xprime;
      }
    }


    srand(time(NULL)*nbEssai);

    for(unsigned int i=0;i<x.size();i++){
      x[i]=(rand()%2);
    }
    nbEssai++;
  }
  return resultat;
}

std::vector<std::vector<int>> voisinsNonTabous( std::vector<int> &x,const std::vector<std::vector<int>> &tabou){
  std::vector<std::vector<int>> listeNonTabou(0);
  for(unsigned int i=0;i<x.size();i++){
    x[i]= !x[i];

    if( std::find(tabou.begin(), tabou.end(), x) != tabou.end()) {
      /* v contains x
      std::cout<<"Vecteur reconnu : ";
      for(unsigned int i=0;i<x.size();i++){

      std::cout << x[i]<<" ";
    }
    std::cout<<std::endl;*/
  } else {
    /*std::cout<<"Vecteur pas reconnu : ";
    for(unsigned int i=0;i<x.size();i++){

    std::cout << x[i]<<" ";
  }
  std::cout<<std::endl;*/
  listeNonTabou.push_back(x);
}
x[i]= !x[i];
}
return listeNonTabou;
}

std::vector<int> meilleur_voisin_non_Tabou(const std::vector<std::vector<int>> &matrice,const std::vector<std::vector<int>> &listeNonTabou){
  std::vector<int> meilleursVoisinsNonTabous;
  int meilleurValeur=std::numeric_limits<int>::max();
  //std::cout<<"----------------"<<std::endl;
  for(unsigned int i=0;i<listeNonTabou.size();i++){

    int resultatUBPQ = UBPQ(matrice,listeNonTabou[i]);
    /*std::cout<<"Vecteur calculé : ";
    for(unsigned int j=0;j<listeNonTabou[i].size();j++){

    std::cout << listeNonTabou[i][j]<<" ";
  }
  std::cout<<std::endl;
  std::cout<<" Resultat UBPQ : "<<resultatUBPQ<<" v = "<<meilleurValeur<<std::endl;*/
  if(resultatUBPQ<=meilleurValeur){
    if(resultatUBPQ<meilleurValeur){
      meilleursVoisinsNonTabous.clear();
    }

    meilleursVoisinsNonTabous.push_back(i);
    meilleurValeur=resultatUBPQ;
  }
}
//std::cout<<"----------------"<<std::endl;
//srand(time(NULL));
return listeNonTabou[meilleursVoisinsNonTabous[rand()%meilleursVoisinsNonTabous.size()]];

}

std::vector<int> tabou(const std::vector<std::vector<int>> &matrice,std::vector<int> x,const int &maxDeplacement,const unsigned int &k){
  std::vector<std::vector<int>> tabou;
  int nbDeplacement=0;
  bool plusVoisinTabou = false;
  std::vector<std::vector<int>> listeNonTabou(0);
  std::vector<int> xprime;
  std::vector<int> msol=x;
  do{
    /*std::cout<<" ---- Vecteur base : ";
    for(unsigned int i=0;i<x.size();i++){

    std::cout << x[i]<<" ";
  }
  std::cout<<std::endl;*/
  listeNonTabou = voisinsNonTabous(x,tabou);

  //std::cout<<" Liste t : "<<listeNonTabou.size()<<" nbD : "<<nbDeplacement<<" tabou : "<<tabou.size()<<std::endl;
  if(listeNonTabou.size()!=0){
    xprime=meilleur_voisin_non_Tabou(matrice,listeNonTabou);
  }else{
    plusVoisinTabou=true;
  }
  if(tabou.size()<k){
    tabou.push_back(x);
  }
  //  std::cout<<"Xp : "<<UBPQ(matrice,xprime)<<" Msol : "<<UBPQ(matrice,msol)<<std::endl;
  if(UBPQ(matrice,xprime)<UBPQ(matrice,msol)){
    msol=xprime;
    nbDeplacement++;
  }
  x=xprime;

  listeNonTabou.clear();
}while(nbDeplacement<maxDeplacement && plusVoisinTabou==false);

/*std::cout << " Tabou = "<<std::endl;
for(unsigned int i=0;i<tabou.size();i++){
for(unsigned int j=0;j<x.size();j++){
std::cout << tabou[i][j] << " ";
}
std::cout<<std::endl;
}*/
return msol;
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
std::cout << " -- Vecteur : -- ";
for(int i=0;i<tailleMatrice;i++){
  vecteur[i]=(rand()%2);
  std::cout << vecteur[i]<<" ";
}
std::cout<<std::endl;


std::vector<int> vecteurMeilleurVoisin =varianteSteepestHillClimbing(matrice,vecteur,50,4,p) ;
std::cout << "Meilleur voisin = ";
for(int i=0;i<tailleMatrice;i++){
  std::cout << vecteurMeilleurVoisin[i]<<" ";
}
std::cout  << std::endl;

std::cout << "UBPQ : " <<UBPQ(matrice,vecteurMeilleurVoisin)<<std::endl;


return 0;
}
