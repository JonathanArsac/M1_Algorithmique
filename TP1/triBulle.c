#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/**
 * Reading and writing data
 */
void read_data( FILE *datain, int **dataout, int *n, int *k ) {
	int *data;

	fscanf(datain, "%d", n);
	fscanf(datain, "%d", k);
	*dataout = (int *)malloc( (*n) * sizeof(int) );
	data=*dataout;

	for ( int i=0; i< *n; ++i, ++data )
		fscanf( datain, "%d", data );
}

void print_data(int *tableau, int taille) {
	for( int i=0; i<taille; ++i)
		printf( "%d ", tableau[i] );
	printf("\n");
}

/**
 * Exchange values between two memory space
 */
void permut(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Write your functions there*/
void triBulle(int* t, int taille,int k){
	double duree_ms;
	clock_t duree = clock();
  for(int i=0;i<k;i++){
    for(int j=1;j<taille-i;j++){
      if(t[j-1]>t[j])
        permut(&t[j-1],&t[j]);
    }
  }
	for(int i=1;i<=k;i++){
		printf(" %d ",t[taille-i]);
	}
	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("TRI A BULLE fait en %.7fms  \n",duree_ms);


	printf("\n");


}
void testTriBulle(int* t, int tailleTableauDonnees, int k){

	printf("\n -------- TEST BUBULLE ------------ \n");
	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees) * sizeof(int) );
	for(int i=0;i<tailleTableauDonnees;i++){
		tasBinaireMax[i]=t[i];
	}
	triBulle(tasBinaireMax,tailleTableauDonnees,k);
	free(tasBinaireMax);

}

void percolateD(int* t,int taille, int i,int *compteur){

  int prioritaire=i;
  int l = 2*i +1;
  int r = 2*i +2;
  if(l<taille && t[l] > t[prioritaire]){
    prioritaire=l;
  }
  if(r<taille && t[r] > t[prioritaire]){
    prioritaire=r;
  }

  if(prioritaire!=i){
		++(*compteur);
    permut(&t[i],&t[prioritaire]);
    percolateD(t,taille,prioritaire,compteur);
  }
}


void buildheap(int* t, int taille){
	double duree_ms;
	clock_t duree = clock();
	int compteur=0;
  for(int i =(taille/2)-1;i>=0;i--){
    percolateD(t,taille,i,&compteur);
  }
	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("BUILDHEAP fait en %.7fms avec %d echanges  \n",duree_ms,compteur);

}

void testBuildheap(int* t,int tailleTableauDonnees){
	printf("\n -------- TEST BUILDHEAP ------------ \n");
	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees) * sizeof(int) );
	for(int i=0;i<tailleTableauDonnees;i++){
		tasBinaireMax[i]=t[i];
	}
	buildheap(tasBinaireMax,tailleTableauDonnees);
	print_data(tasBinaireMax,9);
	free(tasBinaireMax);

}

void percolateU(int* t, int fils,int* compteur) {
  int parent = (fils-1)/2;

	while (parent>=0 && t[parent] < t[fils]){
		++(*compteur);
		permut(&t[fils],&t[parent]);
		fils = parent;
		parent = (fils-1)/2;

	}
}

void add(int* tasBinaireMax, int *tailleActuelleTasBinaireMax, int tailleMaxTasBinaireMax, int elementAAjouter,int *compteurPermut){

	if(*tailleActuelleTasBinaireMax < tailleMaxTasBinaireMax){

		tasBinaireMax[*tailleActuelleTasBinaireMax]= elementAAjouter;
		percolateU(tasBinaireMax,*tailleActuelleTasBinaireMax,compteurPermut);
		++(*tailleActuelleTasBinaireMax);
	}
}

void testAdd(int* tableauDonnees,int tailleTableauDonnees){
printf("\n -------- TEST ADD ------------ \n");
	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees+5) * sizeof(int) );
	int tailleActuelleTasBinaireMax=0;
	int compteurPermut=0;
	double duree_ms;
	clock_t duree = clock();
	for (int i=0;i<tailleTableauDonnees;i++){
		add(tasBinaireMax,&tailleActuelleTasBinaireMax,tailleTableauDonnees+5,tableauDonnees[i],&compteurPermut);
	}
	print_data(tasBinaireMax,9);
	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("ADD fait en %.7fms avec  %d echanges \n",duree_ms,compteurPermut);
//	print_data(tasBinaireMax,tailleActuelleTasBinaireMax);
	free(tasBinaireMax);
}


void removeLE(int *tasBinaireMax,int* tailleActuelleTasBinaireMax){
	printf("%d ",tasBinaireMax[0]);
	tasBinaireMax[0]=tasBinaireMax[(*tailleActuelleTasBinaireMax)-1];
	--*tailleActuelleTasBinaireMax;
	int compteur=0;
	percolateD(tasBinaireMax,*tailleActuelleTasBinaireMax,0,&compteur);
}

void testRemove(int *t,int tailleTableauDonnees,int k){
	printf("\n -------- TEST REMOVE ------------ \n");
	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees) * sizeof(int) );
	int taille = tailleTableauDonnees;
	for(int i=0;i<tailleTableauDonnees;i++){
		tasBinaireMax[i]=t[i];
	}
	double duree_ms;
	clock_t duree = clock();
	buildheap(tasBinaireMax,taille);
	//print_data(tasBinaireMax,taille);

	for(int i=0;i<k;i++)
		removeLE(tasBinaireMax,&taille);
	printf("\n");

	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("REMOVE fait en %.7fms  \n",duree_ms);
	free(tasBinaireMax);
}

void removebis(int *tableauDonnees,int* tailleActuelleTasBinaireMax){
	permut(&tableauDonnees[0],&tableauDonnees[(*tailleActuelleTasBinaireMax)-1]);
	--*tailleActuelleTasBinaireMax;
	int compteur=0;
	percolateD(tableauDonnees,*tailleActuelleTasBinaireMax,0,&compteur);
}

void heapsort(int *tableauDonnees, int tailleTableauDonnees,int k){
	printf("\n -------- TEST HEAPSORT ------------ \n");

	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees) * sizeof(int) );
	int taille = tailleTableauDonnees;
	for(int i=0;i<tailleTableauDonnees;i++){
		tasBinaireMax[i]=tableauDonnees[i];
	}

	double duree_ms;
	clock_t duree = clock();
	buildheap(tasBinaireMax,taille);
	for (int i=0;i<k;i++)
	removebis(tasBinaireMax,&taille);

print_data(tasBinaireMax,9);
	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("HEAPSORT fait en %.7fms  \n",duree_ms);
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            permut(&arr[i], &arr[j]);
        }
    }
    permut(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{

    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }

}

void testQuickSort(int* tableauDonnees,int tailleTableauDonnees){
	printf("\n -------- TEST QUICKSORT ------------ \n");

	int* tasBinaireMax = (int *)malloc( (tailleTableauDonnees) * sizeof(int) );
	int taille = tailleTableauDonnees;
	for(int i=0;i<tailleTableauDonnees;i++){
		tasBinaireMax[i]=tableauDonnees[i];
	}
	double duree_ms;
	clock_t duree = clock();
	quickSort(tasBinaireMax,0,taille-1);
	duree = clock()-duree;
	duree_ms=duree/(double)CLOCKS_PER_SEC*1000;
	printf("QUICKSORT fait en %.7fms  \n",duree_ms);

	free(tasBinaireMax);

}
/* Main Program*/
int main( int argc, char **argv ) {
	int *tableauDonnees;
	int tailleTableauDonnees, k;
	FILE *f_in;

	if ( argc > 1 )
		f_in = fopen(argv[1], "r");
	else
		f_in = stdin;

	/* read the data from the file given in arg or from stdin */
	read_data( f_in, &tableauDonnees, &tailleTableauDonnees, &k );
	fclose(f_in);


	/* print the array */
	//print_data(data,n);


	/* use your functions there*/
	//testAdd(tableauDonnees,tailleTableauDonnees);
  //testBuildheap(tableauDonnees,tailleTableauDonnees);
	testRemove(tableauDonnees,tailleTableauDonnees,9);
//	testTriBulle(tableauDonnees,tailleTableauDonnees,k);
	//heapsort(tableauDonnees,tailleTableauDonnees,k);
//	testQuickSort(tableauDonnees,tailleTableauDonnees);
	/* output result */
  //print_data(data,n);
	/* end of the program*/
	free(tableauDonnees);
	return 0;
}
