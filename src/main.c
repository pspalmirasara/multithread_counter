#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define N_THREADS 3

int n_primos; //variavel global que guardara a quantidade de numeros primos encontrados

void verifica_primo(long int n){
	int aux;
	int eh_primo = 1; //0 caso nao seja primo
			  //1 caso seja primo

	if (n==1 || n==0){
		eh_primo = 0;
		return;
	}

	for (int i = 2; i<n; i++){
		aux = n % i;
		if (aux == 0){
			eh_primo = 0;
			break;
		}
	}
	if (eh_primo == 1){
		n_primos++;
	}

	return;
}

void* funcao_thread(void *arg) {

	long int* N = (long int*)arg;
	long int M = (*N);

	verifica_primo(M);
	return NULL;
}


int main(int argc, char **argv) {

	pthread_t threads[N_THREADS]; //vetor de threads
	long int entrada[500]; //as entradas ficarao nesse vetor
	char entrada_char;    //variavel auxiliar para receber a entrada
	int i_entrada; 	      //indice do vetor da entrada
	int i_thread;         //indice do vetor das threads

	/*Recebendo a entrada*/
	int N_entradas = 0; //tamanho total do vetor de entradas
	while (1){
		scanf("%li", &entrada[N_entradas]);
		N_entradas++;
		scanf("%c", &entrada_char);
		if (entrada_char != ' '){
			break;
		}
	}

	/*Multithread*/
	i_thread = 0;
	for (i_entrada = 0; i_entrada < N_entradas; i_entrada++) {
		pthread_create(&(threads[i_thread]), NULL, funcao_thread, &(entrada[i_entrada])); //criando a thread
		if ( (i_thread==0) ||  (i_thread==1) || (i_thread==2) ){
			i_thread++;		
		}else{
			/*Esperando todas as threads terminarem os processos, caso ainda estejam ocupadas*/
			for (int k=0; k<N_THREADS; k++) {
				pthread_join(threads[k], NULL);
			}
			i_thread = 0; //volta a ocupar a primeira thread

		}
	}

	
	/*Esperando todas as threads terminarem*/
	for (int i = 0; i < N_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	/*Printando a quantidade de numeros primos encontrados*/
	printf ("%d\n", n_primos);

	return 0;
}
