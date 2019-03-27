#include<bits/stdc++.h>

using namespace std;

#define quant_contatos 1000;

struct Contato{

    string nome;
    string telefone;
    string indereco;
    string cep;
    string nascimento;

};

int main(){

    int j;
    vector<Contato> contatos;
    vector<string> nomes;
    vector<pair<string, string>> ceps;
    vector<string> numeros;
    string linha;
    string linha2;
    pair<string,string> aux;
    Contato aux2;
    string buffer{""};

    ifstream arquivo("nomes_aleat.txt");
    ifstream arquivo2("lista_ceps.txt");
    ifstream arquivo_num("numeros.txt");

    //arquivo = fopen("nomes_aleat.txt", "r");

    while(getline(arquivo ,linha)){
        nomes.push_back(linha);
    }

    while(getline(arquivo2 ,linha2)){
        
        buffer = "";

        for(j=0; linha2[j] != '\t'; j++){
            
            buffer += linha2[j];
        }

        aux.first = buffer;

        buffer = "";

        for(j+=1; linha2[j] != '\0'; j++){
            buffer += linha2[j];
        }

        aux.second = buffer;

        ceps.push_back(aux);
    }

    while(getline(arquivo_num ,linha)){
        numeros.push_back(linha);
    }

    arquivo.close();
    arquivo2.close();
    arquivo_num.close();

    for(int k=0; k < 20000; k++){

        srand(clock());

        int a = rand() % nomes.size();
        int b = rand() % ceps.size();
        int c = rand() % numeros.size();

        //cout << a << " " << b << " " << c << endl;

        /*aux2.nome = nomes[a];
        aux2.cep = ceps[b].first;
        aux2.indereco = ceps[b].second;
        aux2.telefone = numeros[c];

        contatos.push_back(aux2);
        */

        cout << nomes[a] << endl;
        cout << numeros[c] << endl;
        cout << ceps[b].second << endl;
        cout << ceps[b].first << endl;
        cout << rand()%29 + 1 << "/" << rand()%11 + 1 << "/" << (rand()%100) + 1918 << endl;
        cout << "$" << endl;

    }

    


    return 0;
}