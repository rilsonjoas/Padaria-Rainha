#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char nome[20], codigo[20];
  int quantidade_disponivel, n_vendas, n_compras, preco, status;
} Produto;


int buscar(Produto *produtos, int tamanho, char *codigo) {
  for (int i = 0; i < tamanho; i++) {
    if (strcmp(produtos[i].codigo, codigo) == 0) {
      return i;
    }
  }
  return -1;
}

int inserir_produto(Produto *produtos, int tamanho, int posicao, int preco, Produto novo) {
    strcpy(produtos[posicao].nome, novo.nome);
    produtos[posicao].status = 1;
    produtos[posicao].quantidade_disponivel = 0;
    produtos[posicao].n_compras = 0;
    produtos[posicao].n_vendas = 0;
    produtos[posicao].preco = preco;

    printf("\nProduto registrado!\n\n%s\nCódigo de cadastro: %s\nO preço desse produto é %i\nHá %i produtos desse tipo disponíveis\nForam realizadas %i compras deste produto. \nForam realizadas %i vendas deste produto.\n\n", produtos[posicao].nome, produtos[posicao].codigo, produtos[posicao].preco,produtos[posicao].quantidade_disponivel, produtos[posicao].n_compras, produtos[posicao].n_vendas);
    return 1;
}

int remover_produto(Produto *produtos, int tamanho, char *codigo) {
  buscar(produtos, tamanho, codigo);
  if (buscar(produtos, tamanho, codigo) == -1) {
    printf("\nO produto não existe!\n\n");
    return 0;
  } else {
    produtos[buscar(produtos, tamanho, codigo)].status = 0;
    produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel = 0;
    printf("\nProduto removido!\n\n");
    return 1;
  }
}

int comprar(Produto *produtos, int tamanho, char *codigo, int quantidade) {
  if (buscar(produtos, tamanho, codigo) == -1) {
    printf("\nO produto não existe!\n\n");
    return 0;
  } else if (produtos[buscar(produtos, tamanho, codigo)].status == 0) {
    printf("\nProduto indisponível\n\n");
    return 0;
  } else {
    produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel += quantidade;
    produtos[buscar(produtos, tamanho, codigo)].n_compras+=quantidade;

    printf("\nCompra realizada!\nAgora você possui %i produtos desse tipo disponíveis\n\n", produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel);
    
    return 1;
  }
}

int vender(Produto *produtos, int tamanho, char *codigo, int quantidade) {
  if (buscar(produtos, tamanho, codigo) == -1) {
    printf("\nO produto não existe!\n\n");
    return 0;
  } else {
    if (produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel - quantidade > 0) {
      produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel -= quantidade;
      produtos[buscar(produtos, tamanho, codigo)].n_vendas+=quantidade;
      
      printf("\nVenda realizada!\nAgora você possui %i produtos desse tipo disponíveis\n\n", produtos[buscar(produtos, tamanho, codigo)].quantidade_disponivel);
      
    } else {
      printf("\nQuantidade insuficiente para vendas!\n\n");
    }
  }
  return 1;
}

void ordem_numeros(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] < arr[j + 1]) { 
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int gerar_relatorio(Produto *produtos, int tamanho, int posicao) {
  printf("\nRelatório de vendas:\n\n");
    if (atoi(produtos[posicao].codigo) >= 0 && atoi(produtos[posicao].codigo) < 20) {


      printf("Venda de produtos de maior a menor:\n");
      
      int n = 3;
      if (produtos[posicao].status == 1 && produtos[posicao].n_vendas > 0) {
      
      for (int i = 0; i < n; i++) {
          for (int j = i + 1; j < n; j++) {
              if (produtos[i].n_vendas < produtos[j].n_vendas) {
                int temp;
                  temp = produtos[i].n_vendas;
                  produtos[i].n_vendas = produtos[j].n_vendas;
                  produtos[j].n_vendas = temp;
                printf("Produto: %s\nNúmero de vendas: %d\n\n", produtos[posicao].nome, produtos[posicao].n_vendas);
              }
          }
      }
      }

      printf("\nCompra de produtos de maior a menor:\n");

      int m = 3;
      if (produtos[posicao].status == 1) {
      for (int i = 0; i < m; i++) {
          for (int j = i + 1; j < m; j++) {
              if (produtos[i].n_compras < produtos[j].n_compras) {
                int temp;
                  temp = produtos[i].n_compras;
                  produtos[i].n_compras = produtos[j].n_compras;
                  produtos[j].n_compras = temp;
                printf("Produto: %s\nNúmero de compras: %d\n\n", produtos[posicao].nome, produtos[posicao].n_compras);
              }
          }
      }
      }
      
      printf("Extrato de conta da padaria:\n\n");
      for(posicao = 0; posicao < 20; posicao++) {
        if (produtos[posicao].status == 1 && produtos[posicao].n_compras > 0) {
            printf("Código: %s\nProduto: %s\nQuantidade de compras: %d\nQuantidade de vendas: %d\nSaldo: %d\n\n",
             produtos[posicao].codigo, produtos[posicao].nome,
             produtos[posicao].n_compras, produtos[posicao].n_vendas, (produtos[posicao].preco * produtos[posicao].n_vendas) - (produtos[posicao].preco * produtos[posicao].n_compras));
          }
        }

      printf("Produtos em estoque: \n");
      for(posicao = 0; posicao < 20; posicao++){
        if (produtos[posicao].quantidade_disponivel > 0 && produtos[posicao].status == 1) {
          printf("%s\n", produtos[posicao].nome);
        }
      }
  
  }
  return 0;
}

//FUNÇÃO PRINCIPAL

int main(void) {

  char codigo[20];
  int opcao, posicao;
  Produto produtos[20];

  do {
    printf("Opções da Padaria Rainha\n\n1 - Inserir produto no sistema\n2 - Remover "
           "produto do sistema\n3 - Buscar produto no sistema\n4 - Comprar "
           "produto\n5 - Vender produto\n6 - Gerar relatório completo\n7 - "
           "Sair\n\nDigite a opção desejada: ");
    scanf("%i", &opcao);
    getchar();

    switch (opcao) {
    case 1:
      printf("Digite o código do produto: ");
      scanf("%s", codigo);
      getchar();

      if (buscar(produtos, 20, codigo) != -1 && produtos[buscar(produtos, 20, codigo)].status == 1) {
        printf("\nCódigo já cadastrado! Tente outra vez.\n\n");
      } else {
        printf("Qual a posição do produto no catálogo: ");
        scanf("%i", &posicao);
        getchar();

        if (posicao < 0 || posicao >= 20) {
          printf("\nPosição indisponível. Digite uma entre 0 e 19.\n\n");

        } else {
          printf("Qual o nome do produto?: ");
          scanf("%s", produtos[posicao].nome);
          getchar();

          printf("Qual o preço do produto?: ");
          scanf("%i", &produtos[posicao].preco);
          getchar();

          strcpy(produtos[posicao].codigo, codigo);
          inserir_produto(produtos, 20, posicao, produtos[posicao].preco, produtos[posicao]);
        }
      };

      break;

    case 2:
      printf("Digite o código do produto: ");
      scanf("%s", codigo);
      getchar();

      remover_produto(produtos, 20, codigo);
      break;

    case 3:
      printf("Digite o código do produto: ");
      scanf("%s", codigo);
      getchar();
      if (buscar(produtos, 20, codigo) == -1) {
        printf("\nProduto não encontrado na Padaria.\n\n");
      } else {
        printf("\n%s\nCódigo de cadastro: %s\nO preço desse produto é %i\nHá %i produtos desse tipo disponíveis\nForam realizadas %i compras deste produto. \nForam realizadas %i vendas deste produto.\n\n",
            produtos[posicao].nome, produtos[posicao].codigo, produtos[posicao].preco,
            produtos[posicao].quantidade_disponivel, produtos[posicao].n_compras,
            produtos[posicao].n_vendas);
      }

      break;
      
    case 4:
      printf("Digite o código do produto que deseja comprar: ");
      scanf("%c", codigo);
      getchar();

      int quantidade;
      
      printf("Qual a quantidade de produtos que deseja comprar?: ");
      scanf("%i", &quantidade);
      getchar();

      comprar(produtos, 20, codigo, quantidade);

      break;

    case 5:
      printf("Digite o código do produto que deseja vender: ");
      scanf("%c", codigo);
      getchar();
      
      printf("Qual a quantidade de produtos que deseja vender?: ");
      scanf("%i", &quantidade);
      getchar();

      vender(produtos, 20, codigo, quantidade);
      break;

    case 6:
      gerar_relatorio(produtos, 20, posicao);
      break;
    }
  } while (opcao != 7);

  printf("\nAté breve! :)");

  return 0;
}