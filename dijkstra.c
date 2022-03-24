#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct lista {
   int custo, indiceCidade;
   struct lista *next;
}Lista;

typedef struct grafo {
   int nCidades;
   int kRotas;
   Lista **adj;
}Grafo;

//adiciona uma nova cidade na lista de cidades, no inicio da lista.
Lista* adicionarCidadeCaminhoInicio(int custo, int nomeCidade, Lista *next) {
   Lista *ptr = malloc( sizeof (Lista));

   ptr->custo = custo;
   ptr->indiceCidade = nomeCidade;
   ptr->next = next;
   return ptr;
}

Grafo* criarGrafo(int N, int K) {
   Grafo *gr = (Grafo*) malloc(sizeof(Grafo));
   gr->nCidades = N;
   gr->kRotas = K;
   gr->adj = (Lista**) malloc(N*sizeof(Lista));

   for (int i = 0; i < N; i++)
      gr->adj[i] = NULL;

   return gr;
}

void imprimeGrafo(Grafo *grafo) {
    if(grafo != NULL){
        //printando pra ver se ta salvando direito
        for(int i = 0; i < grafo->nCidades; i++){
            printf("%d ", i);
            for(Lista *J = grafo->adj[i]; J != NULL; J = J->next){
                // printf("%d vai ate %d com custo %d\n", i, J->indiceCidade, J->custo);
                printf("-> (%d | %d) ", J->indiceCidade, J->custo);
            }
            printf("\n");
        }
    }
}

void liberaLista(Lista *lista)
{
    Lista *aux;
    while(lista != NULL){
        aux = lista->next;
        free(lista);
        lista = aux;
    }
}


void liberaGrafo(Grafo *grafo) {
    if(grafo != NULL){
        for(int i = 0; i < grafo->nCidades; i++)
            liberaLista(grafo->adj[i]);
    }
    free(grafo);
}


int pegarMenorDistancia(int N, Lista *distancias, Lista *remanescentes)
{
    //nao sabemos quantos elementos tem em remanescentes, mas é pra percorrer todas cidades em remanescentes e retornar a que tiver a menor distancia associada no vetor distancia
    //retorna a cidade que tem menor distancia

    int minIndice = 0, montanteMin = INT_MAX;

    for(int i = 0; i < N; i++)
        if(remanescentes[i].custo == 0 && distancias[remanescentes[i].indiceCidade].custo < montanteMin)
        {
            minIndice = remanescentes[i].indiceCidade;
            montanteMin = distancias[minIndice].custo;
        }
    return minIndice;
}


int contarCidades(int origem, int destino, Lista* predecessores)//origem é o fim
{//contra quantos elementos tem no caminho entre origem e destino(ta de tras pra frente na orientação normal da rota)
    int i = 1;
    if(destino == origem)
        return 0;
    for(Lista ptr = predecessores[origem]; ptr.custo != destino; ptr = predecessores[ptr.custo])
        i++;
    return i;
}

int isEmpty(int N, Lista *remanescentes)
{
    for(int i = 0; i < N; i++)
        if(remanescentes[i].custo == 0)
            return 0;
    return 1;
}

void dijkstra()
{
    //N é o numero de cidades
    // K é o numero de ligações
    Lista *predecessores, *distancias, *remanescentes;
    int N, K, origem, destino, custo, indice, aux;

    scanf("%d %d", &N, &K);

    Grafo *grafo = criarGrafo(N, K);

    for(int i = 0; i < K; i++)
    {
        scanf("%d %d %d", &origem, &destino, &custo);
        grafo->adj[origem-1] = adicionarCidadeCaminhoInicio(custo, destino-1, grafo->adj[origem-1]);
        grafo->adj[destino-1] = adicionarCidadeCaminhoInicio(custo, origem-1, grafo->adj[destino-1]);
    }


    //armazena cidade de origem e cidade destino
    scanf("%d %d", &origem, &destino);

    //imprimeGrafo(grafo);


    origem--;
    destino--;

    //criando as listas auxiliares
    distancias = (Lista*) malloc(N*sizeof(Lista));
    predecessores = (Lista*) malloc(N*sizeof(Lista));
    remanescentes = (Lista*) malloc(N*sizeof(Lista));

    for(int i = 0; i < N; i++)
    {
        distancias[i].custo = INT_MAX; //valor mt grande
        predecessores[i].custo = -1;// -1 indica vazio
        remanescentes[i].custo = 0;//se ainda nao foi lido, fica zero, se tiver 1 é pq ja foi lido
        remanescentes[i].indiceCidade = i;
    }
    //setando o inicio
    distancias[origem].custo = 0;
    //insere origem em remanescentes, só ele
    while(!isEmpty(N, remanescentes))//enquanto remanescentes nao tiver vazio;
    {

        indice = pegarMenorDistancia(N, distancias, remanescentes);//pega o menor elemento em distancais e tira de remanescentes
        for(Lista *i = grafo->adj[indice]; i != NULL; i = i->next)
        {

            aux = distancias[indice].custo + i->custo;
            if((aux < distancias[i->indiceCidade].custo) || (aux == distancias[i->indiceCidade].custo && contarCidades(indice, origem, predecessores) + 1 > contarCidades(i->indiceCidade, origem, predecessores)))//atualiza distancias pra toda cidade adjacente a S que tiverem um custo menor que o curso de S somado com o custo de S pra tal cidade e também colocar em predecessores o caminho atualizado pra tal cidade.
            {//caso o custo do atual + o proximo passo for menor do que o custo ja calculado pra proxima cidade OU se for igual mas tiver mais cidades na rota nova, insere a nova rota como a predecessora.
                predecessores[i->indiceCidade].custo = indice;//armazena o nó predecessor
                distancias[i->indiceCidade].custo = aux; //armazena a distancia encontrada
            }
            //insiro em A os vertices

        }
        remanescentes[indice].custo = 1;
    }

    printf("%d %d\n", distancias[destino].custo, contarCidades(destino, origem, predecessores));

    free(distancias);
    free(predecessores);
    free(remanescentes);

    liberaGrafo(grafo);
}

int main()
{
    //loop de repetição dos testes
    int nTestes;
    scanf("%d", &nTestes);

    while(nTestes-- > 0)
        dijkstra();

    return 0;
}