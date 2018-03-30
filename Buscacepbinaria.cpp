#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
//#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};
    FILE *f;
	Endereco e;
	char *cep;
	int qt;
	int qtleitura =0;
	long posicao, primeiro, ultimo, meio;
    int impcep(char cep[]);
    int buscarcep();

int main(int argc, char**argv)
{   system( "cls" );
    cep =argv[1];
	if(argc != 2)
	{   fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr, "USO: %s [CEP] ", argv[0]);
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");
	if(!f)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", "cep_ordenado.dat");
		return 1;
	}
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	rewind(f);

	printf("Tamanho do Arquivo: %ld\n", posicao);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n\n", posicao/sizeof(Endereco));
	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;
	meio = (primeiro+ultimo)/2;
	buscarcep();
	cout << "Quantidade de leitura  "<< qtleitura<<"\n";
	fclose(f);
	system("pause");
}
int impcep(char cep[])
{
    if(strncmp(cep,e.cep,8)==0)
    {   cout <<"Cep localizado......\n";
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
        return 1;
    }
    return 0;
}
int buscarcep()
{   fseek(f, meio * sizeof(Endereco), SEEK_SET);
	fread(&e,sizeof(Endereco),1,f);
    qtleitura++;
    if( impcep(cep)==1)
    {
        return 1;
    }
    else
    {   if ((atol(cep) < atol(e.cep)) && !(primeiro==meio && ultimo==primeiro+1) )
        {   ultimo = meio;
            meio = (primeiro+ultimo)/2;
            buscarcep();
        }
        else
        {   if ((atol(cep) > atol(e.cep))&& !(primeiro==meio && ultimo==primeiro+1))
            {   primeiro=meio;
                meio = (primeiro+ultimo)/2;
                buscarcep();
            }
            else
            {
                    cout <<"\n" << "Cep nao localizado...."<<"\n";
            }

        }

    }

}
