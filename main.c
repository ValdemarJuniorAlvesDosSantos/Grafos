/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vj-estudos
 *
 * Created on 2 de Junho de 2018, 18:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
#include <time.h>
Grafo ReadData(char* arq)
{
    FILE * arquivo;
    char letter[50];
    char* aux;
    Grafo grafo;
    arquivo = fopen(arq,"r");

    if(arquivo == NULL)
        puts("Erro ao abrir o arquivo.");
    else
    {
        while( (fscanf(arquivo,"%s",letter))!= EOF )
        {
            if(strcmp(letter,"a")==0)
            {
                int v1,v2,peso;
                
               fscanf(arquivo,"%d %d %d",&v1,&v2,&peso);
               
               
               addAres(&grafo, peso, v1, v2);
               
            

            }
            else if(strcmp(letter,"p")==0)
            {
                int a=10;
                fscanf(arquivo,"%s %d",letter,&a);
                printf("%d\n",a);
                grafo=iniciaGrafo(a);
                
            }

        }
    }
    fclose(arquivo);
    return grafo;
}

void FloydCanonica(int** matriz, int n, int** pred){
	for(int k = 1; k < n; k++){
		for(int i = 1; i < n; i++){
                    
			for(int j = 1; j< n; j++){
				if( matriz[i][j] > (matriz[i][k] + matriz[k][j]) ){
					matriz[i][j] = matriz[i][k] + matriz[k][j];                                        
                                        pred[i][j] = k;
                                }
  			}
		}
	}
}

void imprimeCaminho(int** pred,int origem ,int destino,int n){
    //printf("%d->",&origem);
    int i=destino;
    int a=0;
    int cam[n];
    cam[0]=destino;
    
    while (i!=0){
        i = pred[origem][i];
        a++;
        cam[a]=i;
    }
    printf("Caminho: %d",origem);
    while (a != 0){
        a--;
        printf(" -> %d",cam[a]);
    }
}
int main(int argc, char** argv) {
    time_t comeco = time(&comeco);
    FILE* arquivo();
    Grafo g = ReadData("rome99.gr"); 
    int n=g.n;
    int **a=(int**)malloc(sizeof(int*) * n+1);
    for (int i=0;i<g.n+1;i++){
        a[i]=(int*)malloc(sizeof(int) * n+1);
    }      
    int **pred=(int**)malloc(sizeof(int*) * n+1);
    
    for (int i=0;i<n+1;i++){
        pred[i]=(int*)malloc(sizeof(int) * n+1);
    }
    
    for (int i=1;i<n+1;i++){       
        for (int k=1;k<n+1;k++){          
            a[i][k] = custo(&g,i,k);
        }       

    }
    destroiGrafo(&g);
    for (int i=1;i<n+1;i++){
        
        for (int k=1;k<n+1;k++){
            if (k==i){
                pred[i][k] = i;
            }else{
                pred[i][k] = 0;
            }
        }       
     
    }
    
    
    
    time_t tCanon;
    time(&tCanon);
    FloydCanonica(a,n+1,pred);
   
    //imprimeCaminho(pred,1,5,n);
    
    for (int i=1;i<n+1;i++){
         free(a[i]);
    }
    free(a);
    for (int i=1;i<n+1;i++){
         free(pred[i]);
    }
    free(pred);
    time_t fim = time(&fim);
    printf("tempo total: %f\n Tempo FroydCanonica: %f\n",difftime(fim,comeco),difftime(fim,tCanon));
    return (EXIT_SUCCESS);
}


