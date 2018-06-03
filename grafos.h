typedef struct adjacencias Adja;
struct adjacencias{
    int peso;
    int v2;
    Adja* prox;
};
typedef struct vertice{
    int rotulo;
    int grau;
    Adja* adjacentes;
}Vert;

typedef struct grafo {
    Vert *vertices;
    int n;
}Grafo;

//inicia grafo
Grafo iniciaGrafo(int vertices);
//adiciona itens no grafo
void addVert(Grafo* grafo,int i);
void addAres(Grafo* grafo, int peso,int v1, int v2);
int custo(Grafo* grafo,int v1,int v2);
// Grafo* destroiGrafo();

void imprime(Grafo* a);