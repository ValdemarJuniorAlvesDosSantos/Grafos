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

    FILE* arquivo();
    Grafo g = ReadData("rome99.gr"); 


    int **a=(int**)malloc(sizeof(int*) * g.n+1);
    
    for (int i=0;i<g.n+1;i++){
        a[i]=(int*)malloc(sizeof(int) * g.n+1);
    }
    
    int **pred=(int**)malloc(sizeof(int*) * g.n+1);
    
    for (int i=0;i<g.n+1;i++){
        pred[i]=(int*)malloc(sizeof(int) * g.n+1);
    }
    
    for (int i=1;i<g.n+1;i++){
        
        for (int k=1;k<g.n+1;k++){          
            a[i][k] = custo(&g,i,k);
            //printf ("de %d para %d custo %d \n" ,i,k,a[i][k]);
        }       
       // printf("\n");
    }
    
    for (int i=1;i<g.n+1;i++){
        
        for (int k=1;k<g.n+1;k++){
            if (k==i){
                pred[i][k] = i;
            }else{
                pred[i][k] = 0;
            }
        }       
     
    }
    
    
    
    FloydCanonica(a,g.n+1,pred);
    
    printf("Depois do algoritmo\n");
    for (int i=1;i<g.n+1;i++){
        
        for (int k=1;k<g.n+1;k++){                   
            printf ("de %d para %d custo %d \n" ,i,k,a[i][k]);
        }       
        printf("\n");
    }
    
    //printf("Caminho 1 para 6");
    for (int i=1;i<g.n+1;i++){
        for (int j=1;j<g.n+1;j++){
            printf(" -> %d",pred[i][j]);
        }
        printf("\n");
    }
    
    for (int i=1;i<g.n+1;i++){
         free(a[i]);
    }
    free(a);
    imprimeCaminho(pred,1,5,9);
    
    for (int i=1;i<g.n+1;i++){
         free(pred[i]);
    }
    free(pred);
    
    return (EXIT_SUCCESS);
}


