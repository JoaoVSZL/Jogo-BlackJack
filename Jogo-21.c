#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define AlocaMemoria()    ( (Tmonte) malloc(sizeof(Tbaralho)) )
#define LiberaMemoria(p)  ( free(p) )

typedef struct _carta_ //estrutura do baralho que vai ter o naipe o,c,e,p e valor da carta de 1 a 13
{
   char naipe;
   int valor;
} Tcarta;//carta

typedef struct _baralho_ //estrutura do baralho, que vai conter um tipo carta e o apontador para o proximo valor
{
   Tcarta x;
   struct _baralho_ *prox;
} Tbaralho; //baralho

typedef Tbaralho *Tmonte; //definindo o monte do tipo baralho

/*================*
 *  Inicia Fila
 *================*/
Tmonte criaFila (void){
   //aloca uma nova celula
   Tmonte pcabeca = AlocaMemoria();
   //o valor desta celula recebe -1 para se diferenciar
   pcabeca->x.valor = -1;
   //ela aponta para ela mesma
   pcabeca->prox  = pcabeca;
   //retornando esta celula para fazer ligação com a variavel que pediu ela
   return pcabeca;
}

/*================*
 *  cria Baralho
 *================*/

void criaBaralho(Tmonte *monte){
   //montando o baralho
   int i,j;
   for(i=1;i<14;i++)
   for(j=1;j<5;j++){
    Tmonte novo = AlocaMemoria();
    novo->prox = (*monte)->prox;
    (*monte)->prox = novo;
    if (j == 1)
    novo->x.naipe = 'o';
    if (j == 2)
    novo->x.naipe = 'c';
    if (j == 3)
    novo->x.naipe = 'e';
    if (j == 4)
    novo->x.naipe = 'p';
    novo->x.valor = i;
    (*monte)->prox=novo;
   }
}
/*===================*
 * Exibe o Baralho
 *===================*/
void mostraBaralho(Tmonte *monte){
   //exibe o baralho
    Tbaralho *aux;
   aux = (*monte)->prox;
   while (aux->x.valor != -1){   //comparaçao de início da fila
     printf("\nValor %d Naipe %c\n",aux->x.valor,aux->x.naipe);
     aux = aux->prox;
   }

}

/*===========================*
 *    Pega uma carta
 *===========================*/
Tcarta pegaCarta(Tmonte *monte)
{
   Tbaralho *aux; Tcarta x;
   aux = (*monte)->prox;
   (*monte)->prox = aux->prox;
   x = aux->x;
   LiberaMemoria(aux);
   return(x);
}

/*==========================*
 *   Devolve uma carta
 *==========================*/

void devolveCarta(Tmonte *monte, Tcarta carta){
   Tbaralho *aux = AlocaMemoria();
   aux->x = carta;
   aux->prox  = (*monte)->prox;
   (*monte)->prox = aux;
}

/*=======================*
 *   Embaralha o Baralho
 *=======================*/
void embaralha(Tmonte *monte){
   //Embaralhar o Baralho
   //para usar o random
   srand(time(NULL));
   Tbaralho *aux, *aux0;
   Tmonte aux1 = criaFila(),aux2 = criaFila();
   Tcarta x;
   int p;
   //aux está recebendo o monte->prox
   aux = (*monte)->prox;
   //enquanto aux->x.valor for diferente do flag
   while (aux->x.valor != -1){
      //pegando uma carta do endereço do ponteiro para monte
      x = pegaCarta(&(*monte));
      //p vai receber um valor aleatório
      p = rand() % 100;
      //se o valor de p for par
      if (p % 2 == 0)
         //jogo ele na fila aux1
         devolveCarta(&aux1,x);
      //caso contrario jogo na fila aux2
      else devolveCarta(&aux2,x);
      //aux vai receber monte->prox
      aux = (*monte)->prox;
   }
   //monte que está vazio vai receber a fila aux1->prox
   (*monte)->prox = aux1->prox;
   aux = (*monte);
   aux0 = (*monte)->prox;
   while(aux0->x.valor != -1){
      aux= aux->prox;
       aux0= aux0->prox;
   }
   aux->prox= aux2->prox;

}


/*========================*
 *   destroi Baralho
 *========================*/

void destroiBaralho (Tmonte *monte)
{
   Tbaralho *aux;
   Tcarta x;
    //aux está recebendo o monte->prox
   aux = (*monte)->prox;
   //enquanto aux->x.valor for diferente do flag
   while (aux->x.valor != -1){
      //pegando uma carta do endereço do ponteiro para monte
      x = pegaCarta(&(*monte));
      aux = (*monte)->prox;
   }
}
/*===================*
 *        Jogar
 *===================*/
void jogar(Tmonte *monte,char nome1[], char nome2[], int *placar1, int *placar2){
   srand(time(NULL));
   int soma1=0, soma2=0;
   Tcarta x1,x2;
   char ch, aux1;
   int op2;
   int n=0;
    
      x1.valor=x2.valor=0;
      x1.naipe=x2.naipe='a';
      (system("cls"));
        printf("\n******** Menu do Jogo ************ v0.14\n\n");
        printf("\n1- Pegar Carta\n");
        printf("\n2- Nao Pegar uma Carta\n");
        printf("\n3- Sair \n");
        printf("\nEntre com a sua Opcao: \n");
        scanf("%d", &op2);
   do{
      switch (op2){
          case 1:{
           (system("cls"));
           x1 = pegaCarta(&(*monte));
           printf("Voce pegou a carta %d %c   ", x1.valor, x1.naipe);
           if (soma2==0 && soma2<=18){
            x2 = pegaCarta(&(*monte));
            printf("Computador pegou a carta %d %c\n\n", x2.valor, x2.naipe);
            soma2 += x2.valor;
           }
           else{
              int r=rand()%2;
            if (r==1 && soma2<=18){
              x2 = pegaCarta(&(*monte));
              soma2 += x2.valor;
              printf("Computador pegou a carta %d %c\n\n", x2.valor, x2.naipe);
            }
            else printf("Computador nao pegou uma carta\n\n");
           }
           soma1 += x1.valor;
           scanf("%c", &ch);
           break;
        }
        case 2:{
           (system("cls"));
           printf("Voce nao pegou uma carta   ");
           if (soma2==0 && soma2<=18){
            x2 = pegaCarta(&(*monte));
            printf("Computador pegou a carta %d %c\n\n", x2.valor, x2.naipe);
            soma2 += x2.valor;
           }
           else{
              int r=rand()%2;
            if (r==1 && soma2<=18){
              x2 = pegaCarta(&(*monte));
              soma2 += x2.valor;
              printf("Computador pegou a carta %d %c\n\n", x2.valor, x2.naipe);
            }
            else printf("Computador nao pegou uma carta\n\n");
           }
           
           scanf("%c", &ch);
           break;
        }
        case 3:{
           (system("cls"));
           printf("\nSaindo do Jogo\n");
           scanf("%c", &ch);
           break;
        }
        default:{
           printf("\nEntre com um valor valido!\n");
           scanf("%c", &ch);
        }
     }
     printf("Soma do Jogador 1 %d      ", soma1);
     printf("Soma do Computador %d\n\n", soma2);
     printf("Deseja pegar outra carta? Y/N\n");
     scanf("%c", &aux1);
     if(aux1 == 'N' || aux1 == 'n'){
        n++;  
        op2 = 2;
        }
     else if(aux1 == 'Y' || aux1 == 'y'){   
        n=0;
        op2 = 1;
        
         
        }
   }while ((soma1 < 21) && (soma2 < 21) && (op2!=3) && n!=2);
   if ((soma1>21) && (soma2>21))
      printf("\nO jogo ficou empatado\n");
   else if (soma1 > 21){
      printf("\nVoce perdeu esta rodada\n");
      (*placar2)++;
   }
   else if(soma2 > 21){
      printf("\nVoce ganhou esta rodada\n");
      (*placar1)++;
   }
   else if(soma1 == 21){
      printf("\nVoce ganhou esta rodada\n");
      (*placar1)++;
   }
   else if(soma2 == 21){
      printf("\nVoce perdeu esta rodada\n");
      (*placar2)++;
   }
   else if ((soma1==21) && (soma2==21))
      printf("\nO jogo ficou empatado\n");
   else if (soma1>soma2){
      printf("\nVoce ganhou esta rodada\n");
      (*placar1)++;
   }
   else if (soma1<soma2){
      printf("\nVoce perdeu esta rodada\n");
      (*placar2)++;
   }
   else printf("\nO jogo ficou empatado\n");
   destroiBaralho(&(*monte));
}

int main(void){
   char ch;
   int op;
   char nome1[10],nome2[20];
   (system("cls"));
   printf("Jogador 1 entre com o seu nome : ");
   fflush(stdin);
   fgets(nome1,10,stdin);
   (system("cls"));
   printf("Bem Vindo %sPressione Enter para continuar...", nome1);
   scanf("%c",&ch);
   strcpy(nome2,"Computador");
   (system("cls"));
   /*Criando a Fila*/
   Tmonte monte = criaFila();
   /*Criando o Baralho */
   criaBaralho(&monte);
   int i;
   /*Embaralhando o Baralho*/
   for (i=0;i<10;i++)
   embaralha(&monte);
   int placar1 = 0, placar2= 0;
   do{
     (system("cls"));
     printf("\n*************** Menu ***************\n\n");
     printf("\n1- Mostrar o Baralho\n");
     printf("\n2- Jogar\n");
     printf("\n3- Ver Placar\n");
     printf("\n4- Zerar Placar\n");
     printf("\n5- Sair \n");
     printf("\nEntre com a sua Opcao: \n");
     scanf("%d", &op);
     switch(op){
        case 1:{
           (system("cls"));
           printf("Mostrando o Baralho\n");
           mostraBaralho(&monte);
           scanf("%c", &ch);
           break;
        }
        case 2:{
           (system("cls"));
           jogar(&monte, nome1, nome2, &placar1, &placar2);
           scanf("%c", &ch);
           /*Criando o Baralho */
           criaBaralho(&monte);
           int i;
           /*Embaralhando o Baralho*/
           for (i=0;i<10;i++)
            embaralha(&monte);
           break;
        }
        case 3:{
           (system("cls"));
           printf("Placar de %s : %d \n", nome1, placar1);
           printf("Placar do %s : %d \n", nome2, placar2);
           scanf("%c", &ch);
           break;
        }
        case 4:{
           (system("cls"));
           placar1 = placar2 = 0;
           printf("Placar Zerado\n");
           scanf("%c", &ch);
           break;
        }
        case 5:{
           (system("cls"));
           printf("\nSaindo do Programa\n");
           scanf("%c", &ch);
           exit (0);
           break;
        }
        default:{
           printf("\nEntre com um valor valido!\n");
           scanf("%c", &ch);
        }
     }
     scanf("%c", &ch);
   }while (op != 5);

   return 0;
}