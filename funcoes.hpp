#ifndef FUNCOES_P_H
#define FUNCOES_P_H
#include <iostream>
#include <fstream>

#define MAXTAM 12
#define MAX_E 7

using namespace std;

typedef struct PedidoLista{
    int codigo;
    int produto[MAXTAM];
    double total;
    float distancia; 
    struct PedidoLista *prox;
}pedido;

typedef struct Lista{
    pedido *inicio;
    pedido *fim;
}TLista;

//Armazenamento dos valores do Codigo e Distancia.
struct PILHA{
    int Codigo[10];
    float Distancia[10];
}Pilha;

//Struct da Pilha para entrega.
typedef struct tipoElemento{
    int Codigo;
    int Distancia;
    struct tipoElemento *prox;
}TElemento;

typedef struct PPilha{
    TElemento *topo;
    int tamanho;
}TPilha;

//Cardapio IFMG DELIVERY'S.
void cardapio(){
    system("cls");
    cout<<"|---------------------------------|"<<endl;
    cout<<"|             CARDAPIO            |"<<endl;
    cout<<"|---------------------------------|"<<endl;
    cout<<"| 1.Batata Frita............ 12.5 |"<<endl;
    cout<<"| 2.Hamburguer ............. 30.4 |"<<endl;
    cout<<"| 3.Coca-Cola ............... 7.8 |"<<endl;
    cout<<"| 4.Nugets ................. 16.6 |"<<endl;
    cout<<"| 5.Suco Natural ............ 5.0 |"<<endl;
    cout<<"| 6.Sushi .................. 49.9 |"<<endl;
    cout<<"| 7.Costela no Bafo......... 26.6 |"<<endl;
    cout<<"|---------------------------------|"<<endl;
}

//Tabela de Valores.
double pagamento(int codigo){
    int i;
    double tabela[]={12.5, 30.4, 7.8, 16.6, 5.0, 49.9, 43.1};
    string produto[]={"Batata Frita","Hamburguer","Coca-Cola","Nugets","Suco Natural","Sushi","Costela no Bafo"};
    
    for(i=0; i<(MAXTAM+1); i++){
        if((codigo-1)==i){
            cout<<tabela[i]<<"    "<<produto[i]<<endl;
            return tabela[i];
            break;
        }
    }
}

//Função para inicializar a Pilha.
void inicializarpilha(TPilha *pi){
    pi->topo=NULL;
    pi->tamanho=0;
}
//Função para inicializar a Lista.
void inicializarlista(TLista *lista){
    lista->inicio=NULL;
    lista->fim=NULL;
}

//Função para preencher um novo pedido do cliente.
void PreenchePedido(TLista *lista, int *cod){
    pedido *novo;
    novo = new pedido;
    int i;
    system("cls");
    //Lista o cardapio e da as opções de adicionar os lanches.
    cardapio();
    cout<<"|PEDIDO NOVO|";
    novo->codigo=*cod;
    *cod=*cod + 1;
    cout<<"\t\nDigite distância do seu local até o estabelecimento em metros: ";
    cin>>novo->distancia;
    cout<<"\nAdicione 10 produtos ou digite (-1) para finalizar a compra!"<<endl;
    cout<<"Digite o código do lanche que você deseja adicionar:  "<<endl;
    novo->total=0;
    for(i=0; i<MAXTAM; i++){
        cin>>novo->produto[i];
        if(novo->produto[i]==-1){
            break;
        }
        cout<<"|---------------------------------------------------------|"<<endl;
        cout<<"|-----------------Produto Adicionado!---------------------|"<<endl;
        cout<<"|Digite o código do próximo produto ou -1 para finalizar: |"<<endl;
        cout<<"|---------------------------------------------------------|"<<endl;
    }
    novo->prox = NULL;
    if (lista->inicio == NULL){
        lista->inicio = novo;  
        lista->fim = novo;
    }else{
        lista->fim->prox=novo;
        lista->fim=novo;
     }
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|-----------------Pedido Finalizado!-----------------|"<<endl;
        cout<<"|Aguarde que em breve seu pedido estará na suas mãos!|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
       
    }
    
    //Lista Dos Pedidos Realizados.
    void PedidoLista(TLista *lista){
    pedido *aux;
    aux = lista->inicio;
    float preco;
    int i=0, a;

    system("cls");
    
    if(aux==NULL){
        cout<<"|---------------------------------------------------------|"<<endl;
        cout<<"|-----------Nenhum Pedido Cadastrado No Momento-----------|"<<endl;
        cout<<"|---------------------------------------------------------|"<<endl;
    }else{
        while(aux!= NULL){
            a=0;
            cout<<"\n\nNúmero do Pedido:  "<<aux->codigo;
            cout<<"\nDistância do local até o estabelecimento:    "<<aux->distancia;
            cout<<"\nProdutos do Pedido:\n";
            
            for(i=0; i<MAXTAM; i++){
                if(aux->produto[i]==-1){
                    break;
                }
                preco=pagamento(aux->produto[i]);
                if(aux->total==0){
                    a=1;
                }
                if(a==1){
                    aux->total+=preco;
                }
            }
            cout<<"\nTotal:  "<<aux->total<<endl;
            aux = aux->prox;
         }
    }
}


//Remove da Lista o Pedido Já Entregue ao Cliente.
void remove(TLista *lista, int cod){
    pedido *primeiro, *novo;
    
    if(lista->inicio == NULL){
        cout<<"|---------------------------------------------------------|"<<endl;
        cout<<"|-----------Nenhum Pedido Cadastrado No Momento-----------|"<<endl;
        cout<<"|---------------------------------------------------------|"<<endl;
    }else{
        primeiro = lista->inicio;
        novo = lista->inicio;
        while(novo!=NULL){
            if(novo->codigo==cod){
                if(novo == lista->inicio){
                    lista->inicio = lista->inicio->prox;
                    free(novo);
                    break;
                }else{
                    if(novo==lista->fim){
                        lista->fim =primeiro;
                    }
                    primeiro->prox = novo->prox;
                    free(novo);
                    break;
                }
            }else{
                primeiro=novo;
                novo = novo->prox;
            }
        }   
    }
}

void listaentrega(PILHA *vetor, TLista *lista, int tam){
    pedido *aux;
    aux = lista->inicio;
    int i;

    system("cls");
    if(aux==NULL){
        cout<<"|---------------------------------------------------------|"<<endl;
        cout<<"|-----------Nenhum Pedido Cadastrado No Momento-----------|"<<endl;
        cout<<"|---------------------------------------------------------|"<<endl;
    }else{
        for(i=0; i<tam; i++){
            if(aux!= NULL){
                vetor->Distancia[i]=aux->distancia;
                vetor->Codigo[i]=aux->codigo;
                aux = aux->prox;
            }else{
                break;
            }
        }
    }
}

void organiza(PILHA *vetor, int tam){
    int i, j, aux, troca;
    for(i=0 ; i<tam-1 ; i++){
        for(j=i+1 ; j<tam ; j++){
            aux=vetor->Distancia[i];
            troca=vetor->Codigo[i];

            if(vetor->Distancia[j]>vetor->Distancia[i]){
                vetor->Distancia[i]=vetor->Distancia[j];
                vetor->Distancia[j] = aux;

                vetor->Codigo[i]=vetor->Codigo[j];
                vetor->Codigo[j] = troca;
            }
        }
    }
}

void adiciona(PILHA *vetor, TPilha *pi, int tam){
    int i;

    for(i=0; i<tam; i++){
        TElemento *novo;
        novo = new TElemento;
        novo->Codigo=vetor->Codigo[i];
        novo->Distancia=vetor->Distancia[i];

        novo->prox=NULL;
        if(pi->topo = NULL){
            pi->topo =novo;
        }else{
            novo->prox= pi->topo;
            pi->topo = novo;
        }
    }
}

void P_Final(PILHA *vetor, int tam){
    int i;

    if(tam>0){
        cout<<"Sequencia de codigo dos produtos a se entregue:\n";
        for(i=(tam-1) ; i>=0 ; i--){
            cout<<vetor->Codigo[i]<<"  Distancia: "<<vetor->Distancia[i]<<endl;
        }
    }
}

int R_P(TPilha *pi){
    TElemento *aux;
    int x=-1;
    if(pi->topo==NULL){
        cout<<"\nVazio!\n";
    }else{
        x = pi->topo->Codigo;
        aux = pi->topo;
        pi->topo = pi->topo->prox;
        pi->tamanho--;
        free(aux);
    }
    return x;
}
//Busca de Pedido.
void BuscaPedido(TLista *lista){
    pedido *aux;
    aux = lista->inicio;
    float preco;
    int x=0, i=0, opcao, a=0;
    system("cls");
    if(aux==NULL){
        cout<<"|---------------------------------------------------------|"<<endl;
        cout<<"|-----------Nenhum Pedido Cadastrado No Momento-----------|"<<endl;
        cout<<"|---------------------------------------------------------|"<<endl;
    }else{
        cout<<"Digite o número do pedido: ";
        cin>>opcao;
        while(aux!= NULL){
            if(aux->codigo==opcao){
                cout<<"\n\nNúmero do Pedido:  "<<aux->codigo;
                cout<<"\nDistância do local até o estabelecimento:      "<<aux->distancia;
                cout<<"\nProdutos do Pedido:\n";
                for(i=0; i<MAXTAM; i++){
                    if(aux->produto[i]==-1){
                        break;
                    }
                    preco=pagamento(aux->produto[i]);
                    if(aux->total==0){
                        a=1;
                    }
                    if(a==1){
                        aux->total+=preco;
                    }
                }
                cout<<"\nValor Total do Pedido:  "<<aux->total<<endl;
                x=0;
            }
            aux = aux->prox;
        }
    }
}
    
    int tamanho;
    int codigo=1;
    TLista L1;
    PILHA P1;
    TPilha TP1;
    pedido pedidos;
    PPilha P2;

void menu(){
    int op=7, TM=0, cd;
    

    FILE *file = fopen("lanchonete.bin", "r");
    if (file != NULL)
    {
        while (fread(&pedidos, sizeof(pedido), 1, file))
        {
            if (pedidos.codigo > codigo)
            {
                codigo = pedidos.codigo;
            }
            adiciona(&P1,&TP1,TM);
        }
    }

    for(;;){
    cout<<"  |---------------------|"<<endl;
    cout<<"  |   IFMG DELIVERY'S   |"<<endl;
    cout<<"  |---------------------|"<<endl;
    cout<<"  |1->Novo Pedido.      |"<<endl;
    cout<<"  |2->Lista De Pedidos. |"<<endl;
    cout<<"  |3->Cardápio.         |"<<endl;
    cout<<"  |4->Buscar Pedido.    |"<<endl;
    cout<<"  |5->Lista de Entrega. |"<<endl;
    cout<<"  |6->Pedidos Entregues.|"<<endl;
    cout<<"  |7->Sair.             |"<<endl;
    cout<<"  |---------------------|"<<endl;
    cout<<" Selecione a opção desejada: ";
    cin>> op;
        switch(op){
            case 1:
                PreenchePedido(&L1, &codigo);
                TM++;
                system("pause");
                system("cls");
                break;
            case 2:
                PedidoLista(&L1);
                system("pause");
                system("cls");
                break;
            case 3:
                cardapio();
                system("pause");
                system("cls");
                break; 
            case 4:
                BuscaPedido(&L1);
                system("pause");
                system("cls");
                break;
                case 5:
                listaentrega(&P1, &L1, TM);
                organiza(&P1, TM);
                adiciona(&P1, &TP1, TM);
                P_Final(&P1, TM);
                system("pause");
                system("cls");
            break;  
            case 6:
                listaentrega(&P1, &L1, TM);
                organiza(&P1, TM);
                adiciona(&P1, &TP1, TM);
                system("cls");
                cd=R_P(&TP1);
                remove(&L1,cd);
                system("cls");
                if(cd!=-1){
                    cout<<"|---------------------------------------------------------|"<<endl;
                    cout<<"|-----------Pedido Entregue Com Sucesso-------------------|"<<endl;
                    cout<<"|---------------------------------------------------------|"<<endl;
                    TM--;
                    system("pause");
                    system("cls");
                }else{
                    cout<<"|---------------------------------------------------------|"<<endl;
                    cout<<"|-----------Nenhum Pedido Cadastrado No Momento-----------|"<<endl;
                    cout<<"|---------------------------------------------------------|"<<endl;
                    system("pause");
                    system("cls");
                }
                
            break;
            case 7:
             file = fopen("lanchonete.bin", "w"); 
             for(int i=0; i<TP1.tamanho; i++){
                    R_P(&TP1);
                    fwrite(&pedidos, sizeof(pedido), 1, file);
             }
            exit(0);
            break;
        }
    }
 }
    
    
    



#endif 
