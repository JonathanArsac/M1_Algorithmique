#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <limits>
#include <algorithm>
#include <math.h>


void lectureDonnees(const char *fichier,std::vector<std::vector<int>> &matrice,int &tailleMatrice){
  std::ifstream monFlux {fichier};
  int nombre;
  if(monFlux){

    monFlux>>tailleMatrice;
    tailleMatrice++; // ajout du point 0,0
    matrice.push_back(std::vector<int>(tailleMatrice));
    matrice[0][0]=0;
    matrice[0][1]=0;
    for(int i=1;i<tailleMatrice;i++){
      matrice.push_back(std::vector<int>(tailleMatrice));
      monFlux>>nombre;
      for (int j=0; j < 2; j++){
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


double voyageur(const std::vector<std::vector<double>> &matriceDistance,const std::vector<int> tournee ){
  double resultat=0.0;
  resultat+= matriceDistance[0][tournee[0]];
  if(tournee.size()>1){
    for(unsigned int i=0;i<tournee.size()-1;i++){
      resultat+= matriceDistance[tournee[i]][tournee[i+1]];
    }
  }
  resultat+= matriceDistance[0][tournee[tournee.size()-1]];
  return resultat;
}


std::vector<int> meilleur_voisin(const std::vector<std::vector<double>> &matriceDistance,std::vector<int> tournee){

  double meilleurValeur=std::numeric_limits<double>::max();
  std::vector<std::vector<int>> resultats;
  resultats.push_back(tournee);
  for(unsigned int i=0;i<matriceDistance.size();i++){
    for(unsigned int j=i+1;j<matriceDistance.size()-1;j++){
      int tempo=tournee[i];
      tournee[i]=tournee[j];
      tournee[j]=tempo;
      double resultatVoyageur = voyageur(matriceDistance,tournee);
      std::cout<<" res "<<resultatVoyageur<<" val : "<<meilleurValeur<<std::endl;
      if(resultatVoyageur<=meilleurValeur){
        if(resultatVoyageur<meilleurValeur){
          resultats.clear();
        }
        resultats.push_back(tournee);

        meilleurValeur=resultatVoyageur;
      }
      tournee[j]=tournee[i];
      tournee[i]=tempo;

    }


  }
  // random
  srand(time(NULL));

  return resultats[rand()%resultats.size()];
}



std::vector<int> steepestHillClimbing(const std::vector<std::vector<double>> &matrice,std::vector<int> x,const int &maxDeplacement){
  int nbDeplacement{0};
  bool aucunmeilleurVoisintrouve = false;

  while(nbDeplacement<maxDeplacement && aucunmeilleurVoisintrouve==false){
    std::vector<int> xprime= meilleur_voisin(matrice,x);

    //std::cout << " 1 : "<<UBPQ(matrice,xprime) << " 2 : "<< UBPQ(matrice,x)<<std::endl;
    if(voyageur(matrice,xprime)<voyageur(matrice,x)){
      x=xprime;
    }else{
      aucunmeilleurVoisintrouve=true;
    }
    nbDeplacement++;
  }
  return x;
}


std::vector<int> varianteSteepestHillClimbing(const std::vector<std::vector<double>> &matrice,std::vector<int> x,const int &maxDeplacement,const int &maxEssai){
  int nbEssai{0};
  double meilleurValeur=std::numeric_limits<double>::max();
  std::vector<int> resultat=x;
  while(nbEssai<=maxEssai){
    //  std::cout<<" Essai "<<nbEssai<<" "<<std::endl;
    /*  std::cout<<"Vecteur : "<<std::endl;
    for(unsigned int i=0;i<x.size();i++){

    std::cout << x[i]<<" ";
  }
  std::cout<<std::endl;*/
  std::vector<int> xprime=steepestHillClimbing(matrice,x,maxDeplacement);

  double resultatVoyageur=voyageur(matrice,xprime);
  if (resultatVoyageur<meilleurValeur){
    meilleurValeur=resultatVoyageur;
    resultat=xprime;
  }



  srand(time(NULL)*nbEssai);


  for(unsigned int i=0;i<x.size()-1;i++){
    int n=rand()%(x.size()-1);
    int tempo=x[i];

    x[i]=x[n];

    x[n]=tempo;
  }

  nbEssai++;
}
return resultat;
}


std::vector<std::vector<int>> voisinsNonTabous( std::vector<int> &x,const std::vector<std::vector<int>> &tabou){
  std::vector<std::vector<int>> listeNonTabou(0);
  for(unsigned int i=0;i<x.size();i++){
    for(unsigned int j=i+1;j<x.size()-1;j++){
      int tempo=x[i];
      x[i]=x[j];
      x[j]=tempo;


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
  x[j]=x[i];
  x[i]=tempo;
}
}
return listeNonTabou;
}

std::vector<int> meilleur_voisin_non_Tabou(const std::vector<std::vector<double>> &matrice,const std::vector<std::vector<int>> &listeNonTabou){
  std::vector<int> meilleursVoisinsNonTabous;
  double meilleurValeur=std::numeric_limits<double>::max();
  //std::cout<<"----------------"<<std::endl;
  for(unsigned int i=0;i<listeNonTabou.size();i++){

    double resultatVoyageur = voyageur(matrice,listeNonTabou[i]);
    /*std::cout<<"Vecteur calculé : ";
    for(unsigned int j=0;j<listeNonTabou[i].size();j++){

    std::cout << listeNonTabou[i][j]<<" ";
  }
  std::cout<<std::endl;
  std::cout<<" Resultat UBPQ : "<<resultatUBPQ<<" v = "<<meilleurValeur<<std::endl;*/
  if(resultatVoyageur<=meilleurValeur){
    if(resultatVoyageur<meilleurValeur){
      meilleursVoisinsNonTabous.clear();
    }

    meilleursVoisinsNonTabous.push_back(i);
    meilleurValeur=resultatVoyageur;
  }
}
//std::cout<<"----------------"<<std::endl;
//srand(time(NULL));
return listeNonTabou[meilleursVoisinsNonTabous[rand()%meilleursVoisinsNonTabous.size()]];

}

std::vector<int> tabou(const std::vector<std::vector<double>> &matrice,std::vector<int> x,const int &maxDeplacement,const unsigned int &k){
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
  if(voyageur(matrice,xprime)<voyageur(matrice,msol)){
    msol=xprime;
  }
  x=xprime;
  nbDeplacement++;
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

int main(int argc, char** argv){
  int tailleMatrice;

  std::vector<std::vector<int>> matrice;

  lectureDonnees(argv[1],matrice,tailleMatrice);
  /*
  std::cout <<"tailleMatrice = "<<tailleMatrice<<std::endl;

  std::cout << " Matrice = "<<std::endl;
  for( int i=0;i<tailleMatrice;i++){
  for( int j=0;j<2;j++){
  std::cout << matrice[i][j] << " ";
}
std::cout<<std::endl;
}
*/
std::vector<std::vector<double>> matriceDistance(tailleMatrice,std::vector<double>(tailleMatrice));

for(int i=0;i<tailleMatrice;i++){
  for(int j=i;j<tailleMatrice;j++){
    matriceDistance[i][j]=sqrt(pow((matrice[i][0]-matrice[j][0]),2)+pow((matrice[i][1]-matrice[j][1]),2));
    matriceDistance[j][i]=matriceDistance[i][j];
  }
}

/*std::cout << " MatriceDistance  = "<<std::endl;
for( int i=0;i<tailleMatrice;i++){
for( int j=0;j<tailleMatrice;j++){
std::cout << matriceDistance[i][j] << " ";
}
std::cout<<std::endl;
}*/


std::vector<int> tournee(tailleMatrice-1);
srand(time(NULL));
for(int i=0;i<tailleMatrice-1;i++){
  tournee[i]=i+1;
}


for(int i=0;i<tailleMatrice-1;i++){
  int n=rand()%(tailleMatrice-1);
  int tempo=tournee[i];

  tournee[i]=tournee[n];

  tournee[n]=tempo;
}

std::cout << " -- Vecteur :  " ;
for(int i=0;i<tailleMatrice-1;i++){
  std::cout <<tournee[i]<<"  ";
}
std::cout<<std::endl;
std::cout << " Resultat = "<< voyageur(matriceDistance,tournee)<<std::endl;

std::vector<int> resultatVoisin = meilleur_voisin(matriceDistance,tournee);

std::cout << " -- Vecteur Voisin :  " ;
for(int i=0;i<tailleMatrice-1;i++){
  std::cout <<resultatVoisin[i]<<"  ";
}
std::cout<<std::endl;
std::cout << " Resultat Voisin = "<< voyageur(matriceDistance,resultatVoisin)<<std::endl;

std::vector<int> resultatVoisin2 = tabou(matriceDistance,tournee,50,10);
std::cout << " Resultat Voisin 2 = "<< voyageur(matriceDistance,resultatVoisin2)<<std::endl;


return 0;
}
