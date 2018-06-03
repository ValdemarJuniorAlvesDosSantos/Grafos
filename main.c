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
                grafo=iniciaGrafo(a);
                
            }

        }
    }
    fclose(arquivo);
    return grafo;
}

int main(int argc, char** argv) {
    FILE* arquivo();
    Grafo g = ReadData("USA-road-d.NY.gr");
    //imprime(&g);
    printf("%d\n",g.n);
    int **a=(int**)malloc(sizeof(int*)*g.n);
    for (int i=0;i<g.n+1;i++){
        a[i]=(int*)malloc(sizeof(int)*g.n);
    }
    printf("true da true");
    for (int i=1;i<g.n+1;i++){
        for (int k=1;k<g.n+1;k++){          
            a[i][k] = custo(&g,i,k);
             if (a[i][k] != 200000){
                printf("%d %d custo :%d",i,k,a[i][k]);
             }
        }       
        printf("\n \t");
   }
    
    for (int i=1;i<g.n+1;i++){
        free(a[i]);
    }
    free(a);
    return (EXIT_SUCCESS);
}

