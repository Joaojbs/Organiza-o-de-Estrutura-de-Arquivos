#include <stdio.h>
#include <iostream>
#include <string.h>
#define TAMANHO 300
using namespace std;
FILE *f, *s;
int criararquivo (char uf[2]);
int fechararquivo ();
int main(int argc, char**argv)
{   cout << "Tamanho dos registros..:" << TAMANHO<<"\n\n";
    char registro [TAMANHO];
	int qt;
	int qtest=0;
	char uf[3];
	int r =0;
    uf[2]='\0';
	if(argc != 2)
	{   fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr, "USO: %s .....", argv[0]);
		return 1;
	}
	f = fopen(argv[1],"r");

	if(!f)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	qt = fread(registro,TAMANHO,1,f);
	strncpy(uf,registro+288,2);
 	criararquivo(uf);
	while(qt > 0)
	{	r++;
        if(strncmp(uf,registro+288,2)==0)
        {   fwrite(registro,1,TAMANHO,s);
            qt = fread(registro,TAMANHO,1,f);
            qtest++;

        }
        else
        {   cout << "CEPS Copiados do Estado: "<< uf<<" "<< qtest <<"\n";
            strncpy(uf,registro+288,2);
            r--;
            qtest=0;
            criararquivo(uf);
        }



	}
	cout << "Total de Registros Lido: "<< r <<"\n";
	fclose(f);
	fclose(s);
}
int criararquivo (char uf[2])
{   char nome[5]="";
    strcat( nome,uf);
    strcat( nome,".txt");
    s = fopen(nome,"w+" );
    if(!s)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", uf);
		return 0;
	}
    return 1 ;
}

/*int fechararquivo ()
{
    if(!fclose(s))
	{
		fprintf(stderr,"Arquivo %s não pode ser fechado\n");
		return 0;
	}
    return 1 ;
}
*/

