#include <stdio.h>
#include <stdlib.h>


/*definindo um tipo Palavra
Palavra é o dado guardado em memória*/
struct palavra{
	int dado;
};
/*use o nome palavra apenas para referenciar o tipo*/
typedef struct palavra palavra;

/*definindo um tipo Bloco
Bloco contem 5 palavras*/
struct bloco{
	palavra palavras[5];
	int tag;
};
/*use o nome bloco apenas para referenciar o tipo*/
typedef struct bloco bloco;

//memoria ram armazena palavras
palavra* ram[100] = {};
//memoria cache armazena blocos
bloco* cache[5];

//simula o envio do dado para a CPU
int enviaCPU(palavra p){
	printf("Dado enviado a CPU - %d\n", p.dado);	
}

//simulando o processo de preenchimendo da RAM inicialmente
void preencherRAM(){
	int i =0;
	for(i = 0; i < 100; i++){
		
		palavra *p = malloc(sizeof(palavra));
		p->dado = rand();
		printf("palavra %d = %d \n", i, p->dado);
		ram[i] = p;
	}
	
}

/*
	Para ler um dado, primeiro consulta-se na cache, caso não tenha, consuta-se na ram.
	Ao consultar na ram deve-se copiar o bloco (considere o bloco de 5 em 5 dados).
*/
int ler(int dado){	

	int i, j =0;
	//buscando na cache
	printf("\n\nBuscando dado (%d) na Cache...\n", dado);
	int achou = 0;
	for(i = 0; i < 5; i++){
		
		if(cache[i] == NULL)
			  continue;
			
		for(j = 0; j < 5; j++){
			
			if( cache[i]->palavras[j].dado == dado){
				achou = 1;
				enviaCPU( cache[i]->palavras[j] );
			}
		}
	}	
	
	//se achou na cache encerra o processo
	if(achou == 1){
	   printf("Dado encontrado na cache");
	   return;
	}
	//buscando na RAM
	
	printf("Buscando dado (%d) na RAM...\n", dado);

	for(i = 0; i < 100; i++){
		
		if( ram[i]->dado == dado){
			
			int nbloco = i/5;
			achou = 1;
			printf("Encontrado %d no bloco %d\n",ram[i]->dado, nbloco  );
			//criar o bloco
			bloco *b = malloc( sizeof(bloco) );
			printf("copiando bloco para a cache\n");
			printf("bloco: \n");
			for(j = 0 ; j < 5; j++){
				printf("\t palavra %d = %d\n", j, ram[nbloco*5 + j]->dado);
				b->palavras[j] = *(ram[nbloco*5 + j]);
			}	
			
			if(achou == 1){
				copiarBloco(b, nbloco);
				return;
			}
			
		}
		
	}	
	
	if(achou == 0){
		printf("\nErro ao acessar dado! (%d)", dado);
	}
	
}



/*aqui vc deve implementar um algortimos de substituição:
 - LRU
 - LFU
 - FIFO
 
O bloco deve ser armazenado na cache, observe que b é um ponteiro.
Ex: cache[indice] = b;

Esse código é referente ao modo direto, vocês devem apagar/modificar para
implementar o método de substituição escolhido
*/

int copiarBloco(bloco* b, int n){
	int pos;
	pos = n%5;
	
	printf("\nBloco copiado para a posicao %d na cache", pos);
	
	if(cache[pos] != NULL){
		printf("\nAtencao: Bloco %d substituido", pos);
	}
	cache[pos] = b;	
}


int main(){
	srand(1);
	
	preencherRAM();
	ler(16541);
	ler(22648);
	ler(2995);
	ler(19169);
	ler(13931);
	ler(18467);
	ler(7376);
	ler(13931);
	return 0; 
}



