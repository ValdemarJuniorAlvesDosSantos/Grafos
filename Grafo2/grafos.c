#include <string.h>
#include "grafos.h"
#include <stdlib.h>
#include <stdio.h>

Grafo iniciaGrafo(int vertices) {
    int i=1;
    Grafo novo;
    novo.vertices = (Vert*) malloc (sizeof(Vert) * (vertices+1));
    for (int i=0;i < vertices+1 ; i++){
        addVert(&novo,i);
    }
    novo.n = vertices;
    return novo;
}
void addVert(Grafo* grafo,int rotulo){
    Vert novo;
    novo.grau=0;
    novo.rotulo=rotulo;
    novo.adjacentes = NULL;    
    grafo->vertices [rotulo] = novo;

}
void imprime(Grafo* a){
    for(int i=1; i< a->n+1;i++){
        printf("%d\t",a->vertices[i].rotulo);
        Adja* aux= a->vertices[i].adjacentes;
        while(aux!=NULL){
            printf("-> %d",aux->v2);
            aux=aux->prox;
        }
        printf("\t%d", a->vertices[i].grau);
        printf("\n");
    }
}
Adja* addAdja(Adja* adjacen,int peso,int v2){
    Adja* novo = (Adja*) malloc(sizeof(Adja));
    
    novo->peso=peso;  
    novo->v2 = v2;   
    novo->prox=adjacen;
    
    return novo;
}
void addAres(Grafo* grafo, int peso,int v1, int v2){
            grafo->vertices[v1].adjacentes=addAdja(grafo->vertices[v1].adjacentes,peso,v2);
            grafo->vertices[v1].grau++;
            //grafo->vertices[v2].adjacentes=addAdja(grafo->vertices[v2].adjacentes,peso,v1);  
}

int custo(Grafo* grafo,int v1,int v2){
    if (v1==v2){
        return 0;
    }
    Adja* aux=grafo->vertices[v1].adjacentes;
    
    while(aux!=NULL){
        if (aux->v2==v2){
            return aux->peso;
        }
        aux=aux->prox;
    }
    return 200000;
}
Adja* liberaUltimo(Adja* lista){
     Adja* aux=lista;
     if (aux==NULL){
         return NULL;
     }
    while(aux->prox!=NULL){
        aux=aux->prox;
    }
    free (aux);
}
void libera(Adja* lista){
    while (lista!=NULL){
        liberaUltimo(lista);
    }
}

void destroiGrafo(Grafo* grafo){
    for (int i=0; i < grafo->n+1;i++){
        //libera(grafo->vertices[i].adjacentes);
    }
    //free(grafo);
}