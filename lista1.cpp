#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

struct Pessoa {
	char nome[101];
	char telefone[11];
	char endereco[300];
	unsigned int cep;
	char nascimento[11];
	struct Pessoa *proximo;
	struct Pessoa *anterior;
};	

typedef struct Pessoa contato;
vector<string> nomes;
vector<pair<string, contato *>> indice;

contato *lista_contatos_vazia();
contato *leitura_inicial();
void salvar_arquivo(contato *contatos); 
contato * insertion_sort(contato *contatos); 
void libera_contatos(contato *contatos); 
contato *novo_contato(contato *contatos, contato *novo);
void imprimi_contatos(contato *contatos);
void busca_contato(contato *contatos, char *busca);
void remove_contato(contato *contatos, char *busca);
int verificador_telefone(contato *novo, char *t);
int verificador_nascimento(contato *novo, char *t);
contato * busca_sequencial(contato *contatos, string chave);
vector<string> recorte(int elementos);

void indexar_lista(contato *contatos_ordenados, int n){

	contato *atual;
	int intervalo = nomes.size() / n;
	pair<string,contato *> aux;

	aux.first = *contatos_ordenados->nome;
	aux.second = contatos_ordenados;

	indice.push_back(aux);

	atual = contatos_ordenados->proximo;

	for(int k=1; k<nomes.size(); k ++, atual = atual->proximo){
		
		//cout << k << endl;
		
		if(k%intervalo == 0){
			aux.first = atual->nome;
			aux.second = atual;
			indice.push_back(aux);
		}

		if(atual->proximo == NULL){
			return;
		} 
	}
}

contato * busca_index(string chave){

	contato *aux;

	for(int j=1; j<indice.size(); j++){
		if(chave < indice[j].first){
			aux = busca_sequencial(indice[j-1].second, chave);
			return aux;
		}
	}

	return NULL;

}

int main () {

	contato *contatos;
	contato *novo;
	clock_t Ticks[2];
	double tempo;

	//cout << "Teste" << endl;


	contatos = leitura_inicial(); //realizando a leitura do banco de dados

	cout << "" << endl;


	// lista de contatos ordenados
	Ticks[0] = clock(); // medindo o tempo de ordenacao

	contato *contatos_ordenados;
	contatos_ordenados = insertion_sort(contatos);
	indexar_lista(contatos_ordenados, 100);

	Ticks[1] = clock(); // finalizando o calculo de ordenacao e indexacao

	double temp_ordena = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC; //tempo para realizar a ordenacao e indexacao
	printf ("Tempo de ordenacao %lf\n", temp_ordena);
	
	for(int j=1; j<=3; j++){

		Ticks[0] = clock();

		for(int i=0; i<pow(10, j); i++){
			auto busca_in = busca_index(nomes[i]);

		}

		Ticks[1] = clock();
		tempo = ((Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC) + temp_ordena; // tempo de busca + ordenacao
		cout << "Busca indexada, " << pow(10, j) << " valores: " << tempo << " ms." << endl;


		Ticks[0] = clock();
		for(int i=0; i<pow(10, j); i++){
			auto busca_seq = busca_sequencial(contatos, nomes[i]);		
		}

			Ticks[1] = clock();
		tempo = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC;
		cout << "Busca sequencial, " << pow(10, j) << " valores: " << tempo << " ms." << endl;

		cout << endl;

	}	

	for(int j=2; j<=40; j++){

		Ticks[0] = clock();

		for(int i=0; i<1000*j; i++){
			auto busca_in = busca_index(nomes[i]);

		}

		Ticks[1] = clock();
		tempo = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC+ temp_ordena;
		cout << "Busca indexada, " << 1000*j << " valores: " << tempo << " ms." << endl;


		Ticks[0] = clock();
		for(int i=0; i<1000*j; i++){
			auto busca_seq = busca_sequencial(contatos, nomes[i]);		
		}

			Ticks[1] = clock();
		tempo = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC;
		cout << "Busca sequencial, " << 1000*j << " valores: " << tempo << " ms." << endl;

		cout << endl;

	}

	// char busca[101];
	// string nome_busca;

	// char *ponto;
	// printf("********** Seja bem-vindo a sua lista de contatos **********\n\n");
	
	// int opcao;
	// do{
	// 	printf("1. Inserir novo contato\n");
	// 	printf("2. Remover contatos\n");
	// 	printf("3. Realizar busca de usuários\n");
	// 	printf("4. Visualizar todos os contatos\n");
	// 	printf("5. Fechar a lista de contatos\n");
	// 	printf("Indique o número de uma das opções acima: ");
	// 	scanf ("%d", &opcao);

	// 	switch (opcao){
	// 		case 1:
	// 			novo = lista_contatos_vazia();

	// 			novo = (contato *) malloc(sizeof(contato));
	// 			if (novo == NULL)
	// 				exit (1);

	// 			printf("Insira o nome do contato: ");
	// 			scanf(" %[^\n]", novo->nome);

	// 			//verificador do telefone
	// 			while (1){
	// 				char t[11];
	// 				printf("Insira o Telefone: ");
	// 				scanf(" %[^\n]", t);
	// 				ponto = t;

	// 				int certo = verificador_telefone(novo, ponto);

	// 				if(certo)
	// 					break;

	// 				printf("\n*** Telefone inválido, utilize o formato xxxxx-xxxx ***\n\n");

	// 			}

	// 			printf("Insira o endereço: ");
	// 			scanf(" %[^\n]", novo->endereco);


	// 			//verificador do CEP
	// 			while (1){
 	// 				printf("Insira o CEP (padrão EUA): ");
	// 				scanf(" %u", &novo->cep);
					
	// 				if(novo->cep > 9999 && novo->cep < 100000000)
	// 					break;

	// 				printf("\n*** CEP invalido, utilize o formato xxxxx ***\n\n");
	// 			}


	// 			//verificador data de nascimento
	// 			while (1){
	// 				char t[11];

	// 				printf("Insira a data de nascimento: ");
	// 				scanf(" %[^\n]", t);

	// 				ponto = t;

	// 				int certo = verificador_nascimento(novo, ponto);

	// 				if(certo)
	// 					break;

	// 				printf("\n*** Data inválida, utilize o formato dd/mm/aaaa ***\n\n");
	// 			}

	// 			// printf("Nome: %s\n", novo->nome);
	// 			// printf("Telefone: %s\n", novo->telefone);
	// 			// printf("Endereço: %s\n", novo->endereco);
	// 			// printf("CEP: %u\n", novo->cep);
	// 			// printf("Data de Nascimento: %s\n", novo->nascimento);

	// 			contatos = novo_contato(contatos, novo);

	// 			printf("\n\n");
	// 			// free (novo);
	// 		break;
	// 		case 2:
	// 			printf("Insira o nome do cotato(s) que você deseja remover: ");
	// 			scanf(" %[^\n]", busca);

	// 			ponto = busca;

	// 			remove_contato(contatos, busca);
	// 		break;
	// 		case 3:
	// 			printf("Insira o nome do cotato(s) que você deseja buscar: ");
	// 			scanf(" %[^\n]", busca);

	// 			ponto = busca;

	// 			busca_contato(contatos, busca);
	// 		break;
	// 		case 4:
	// 			printf("\nLista dos contatos inseridos\n");
	// 			contatos = insertion_sort(contatos);
	// 			imprimi_contatos(contatos);

	// 		break;
	// 		case 5:
	// 			printf("\nFinalizando a aplicacao\n");
	// 		break;
	// 	}

	// } while (opcao != 5);
	// contatos = insertion_sort(contatos);
	// salvar_arquivo(contatos);

	// libera_contatos(contatos);
	// libera_contatos(contatos_ordenados);

	return 0;
}


contato *lista_contatos_vazia(){
	return NULL;
}


void libera_contatos(contato *contatos){
	contato *atual;
	for (atual = contatos; atual != NULL; contatos = atual){
		//printf("liberando: %s\n", contatos->nome);
		atual=atual->proximo;
		free(contatos);
		contatos = NULL;
	}
	//if(contatos == NULL)
		//printf("LIBERADO\n");
}
contato * insertion_sort(contato *contatos){
	contato *escolhido;
	contato *temp;
	//temp = (contato *) malloc(sizeof(contato));
	if(temp==NULL) exit(-1);
	int i=1;
	for (;;i++){
		//imprimi_contatos(contatos);
		int need_swap=0; //determina se é necessário ou nao trocar elementos
		int j = i - 1;
		int k=i;
		for(escolhido=contatos; k ; k--, escolhido = escolhido->proximo){
			if(escolhido->proximo == NULL){
				return contatos;
			}
		};	
		temp=escolhido->anterior;
		if(escolhido->proximo!=NULL){
			escolhido->proximo->anterior=temp;
			temp->proximo=escolhido->proximo;
		}
		else{
			temp->proximo=NULL;
		}
		//imprimi_contatos(contatos);
		while ((j >= 0) && (strcmp(temp->nome, escolhido->nome))>=0){
			temp=temp->anterior;
			j--;
		}
		if(temp==NULL){
			escolhido->proximo=contatos;
			escolhido->anterior=NULL;
			contatos->anterior=escolhido;
			contatos=escolhido;
			
		}
		else if(temp->proximo==NULL){
			escolhido->proximo=NULL;
			escolhido->anterior=temp;
			temp->proximo=escolhido;
		}
		else{
			escolhido->proximo=temp->proximo;
			escolhido->anterior=temp;
			escolhido->proximo->anterior=escolhido;
			temp->proximo=escolhido;
			
		}
		//imprimi_contatos(contatos);
		//getchar();
	}
}
void salvar_arquivo(contato *contatos){
	FILE *arquivo;
	arquivo = fopen("contatos.txt", "w");
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(-1);
	}
	contato *atual;
	for (atual = contatos; atual != NULL; atual = atual->proximo){
		fprintf(arquivo, "%s\n", atual->nome);
		fprintf(arquivo, "%s\n", atual->telefone);
		fprintf(arquivo, "%s\n", atual->endereco);
		fprintf(arquivo, "%u\n", atual->cep);
		fprintf(arquivo, "%s\n", atual->nascimento);
		fprintf(arquivo, "$\n");
	}	
}
contato * leitura_inicial(){
	FILE *arquivo;
	arquivo = fopen("contatos.txt", "r");
	if (arquivo == NULL){
		return NULL;
	}
	char linha[500];
	int i=0;
	contato *contatos;
	contatos = lista_contatos_vazia();
	contato *novo;
	novo = (contato *) malloc(sizeof(contato));
	if(novo==NULL) exit(-1);

	while(fscanf(arquivo,"%[^\n]s", linha)!=EOF){
		fscanf(arquivo,"%*c");
		if (novo == NULL)
			exit (1);
		if(linha[0]=='$'){
			i=0;
			contatos = novo_contato(contatos, novo);
			novo = (contato *) malloc( sizeof(contato));
			if(novo==NULL) exit(-1);
			continue;
		}
		if(i==0 && linha[0]==' ')
			break;

		switch(i){
			case 0:
				printf ("");
				strcpy(novo->nome,linha);
				nomes.push_back(novo->nome);
			break;

			case 1:
				printf ("");
				strcpy(novo->telefone,linha);
			break;

			case 2:
				printf ("");
				strcpy(novo->endereco,linha);
			break;

			case 3:
				printf ("");
				sscanf(linha, "%u", &novo->cep);
			break;

			case 4:
				printf ("");
				strcpy(novo->nascimento,linha);
			break;
		}
		i++;
	}
	fclose(arquivo);
	return contatos;
}


contato *novo_contato(contato *contatos, contato *novo) {
	if (contatos == NULL){
		novo->anterior = NULL;
		novo->proximo = NULL;

		return novo;
	}
	else {
		contato *atual;

		for (atual = contatos; atual->proximo != NULL; atual = atual->proximo){}
		atual->proximo = novo;
		novo->anterior = contatos;
		novo->proximo = NULL;
		return contatos;
	}
}


void imprimi_contatos(contato *contatos){
	contato *atual;

	if (contatos != NULL){
		int i=1;
		for (atual = contatos; atual != NULL; atual = atual->proximo){
			printf("Nome: %s\n", atual->nome);
			printf("Telefone: %s\n", atual->telefone);
			printf("Endereço: %s\n", atual->endereco);
			printf("CEP: %u\n", atual->cep);
			printf("Data de Nascimento: %s\n", atual->nascimento);
			printf("\n");
			i++;
		}
	}
	else {
		printf("Agenda Vazia!!\n" );
	}
	
	printf("\n\n\n");
}


void busca_contato(contato *contatos, char *busca){
	contato *atual;

	int cont_loc = 0;
	for(atual = contatos; atual != NULL; atual = atual->proximo){
		int j = 0;
		for(int i=0; atual->nome[i] != '\0'; i++){
			if (*(busca+j)>= 97 && *(busca+j)<=122){
				*(busca+j) = *(busca+j)-32;
			}
			if (*(busca+j) == '\0'){
				if (cont_loc==0){
					printf("\nContato(s) localizados:\n\n");
				}
				printf("Nome: %s\n", atual->nome);
				printf("Telefone: %s\n", atual->telefone);
				printf("Endereço: %s\n", atual->endereco);
				printf("CEP: %u\n", atual->cep);
				printf("Data de Nascimento: %s\n", atual->nascimento);
				printf("\n");
				cont_loc++;
				break;
			}
			else {
				if(atual->nome[i] == *(busca+j) || atual->nome[i] == *(busca+j)+32){
					j++;
				}
				else {
					j=0;
				}
			}
		}
	}
	if (cont_loc==0){
		printf("\nNenhum contato localizado\n");
	}
}


void remove_contato(contato *contatos, char *busca){
	busca_contato(contatos, busca);

	char confirmar;
	printf("Deseja excluir os contatos acima? [s/n]: ");
	scanf(" %c", &confirmar);

	if (confirmar == 's' ||  confirmar == 'S') {
		contato *atual;

		atual = contatos;
		do{
			int j=0;
			for(int i=0; atual->nome[i] != '\0'; i++){
				if (*(busca+j)>= 97 && *(busca+j)<=122){
					*(busca+j) = *(busca+j)-32;
				}
				if (*(busca+j) == '\0'){
					contato *excluir;

					if (atual->anterior==NULL && atual->proximo == NULL){
						free(contatos);

						contatos = lista_contatos_vazia();

						goto finalizado;
					}
					else if (atual->anterior==NULL){
						contato *p;

						p = atual->proximo;
						p->anterior = NULL;

						excluir = atual;
						atual = atual->proximo;
					}
					else if(atual->proximo == NULL){
						contato *a;

						a = atual->anterior;
						a->proximo = NULL;

						excluir = atual;
						atual = atual->proximo;
					}
					else{
						contato *a;
						contato *p;

						a = atual->anterior;
						a->proximo = atual->proximo;

						p = atual->proximo;
						p->anterior = atual->anterior;

						excluir = atual;
						atual = atual->proximo;
					}
					j = 555;
					free(excluir);
					break;
				}
				else {
					if(atual->nome[i] == *(busca+j) || atual->nome[i] == *(busca+j)+32){
						j++;
					}
					else {
						j=0;
					}
				}
			}
			if (j != 555){
				atual = atual->proximo;
			}
		} while (atual != NULL);
		finalizado: printf("\nVocê não tem mais nennhum contato na sua agenda\n\n");
	}
}


int verificador_telefone(contato *novo, char *t) {
	int i;
	int j;
	for(i=0, j=0; i<10; i++, j++) {
		if(i != 5){
			if(*(t+j) >= 48 && *(t+j) <= 57);
			else
				return 0;
		}
		else{
			if(*(t+i) == '-');
			else if(*(t+j) >= 48 && *(t+j) <= 57){
				novo->telefone[i] = '-';
				i++;
			}
			else
				return 0;
		}
		novo->telefone[i] = *(t+j);
	}
	return 1;
}


int verificador_nascimento(contato *novo, char *t) {
	int i;
	int j;
	int cont;
	for(i=0, j=0, cont=0; i<10; i++, j++) {
		if(i == 2){
			if(*(t+j) == '/')
				cont++;
			else if(*(t+j) >= 48 && *(t+j) <= 57){
				novo->nascimento[i] = '/';
				i++;
			}
			else
				return 0;
		}
		else if(i == 5){
			if(*(t+j) == '/' && cont==1);
			else if (*(t+j) != '/' && cont==1)
				return 0;
			else if(*(t+j) >= 48 && *(t+j) <= 57){
				novo->nascimento[i] = '/';
				i++;
			}
			else
				return 0;
		}
		else{
			if(*(t+j) >= 48 && *(t+j) <= 57);
			else
				return 0;
		}
		novo->nascimento[i] = *(t+j);
	}
	return 1;
}


contato * busca_sequencial(contato *contatos, string chave){
    contato *atual;

    for(atual = contatos; atual->proximo != NULL; atual=atual->proximo){
        if(chave == atual->nome){
            return atual;
        }
    }

    return NULL;
}


vector<string> recorte(int elementos){
    vector<string> aux;
    int a=0;
    string aux2;

    srand(clock());

    for(int i=0; i<elementos; i++){
        
        a = rand()%nomes.size();

        aux.push_back(nomes[a]);

    }
    return aux;
}