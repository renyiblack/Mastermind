#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Menu(int,char[],char[],int,int);
int Jogo(char[],int);
void Instrucoes();
void Configuracoes(int&,int&,int&);
void Identificacao(int,char[],char[]);
void random(char[]);
void tabuleir(char[][12],int,int);
int main()
{
    int jogadores=1,dificuldade=1,repeticao=2;
    char jogador1[20]="Jogador 1",jogador2[20]="Jogador 2";
    Menu(jogadores,jogador1,jogador2,dificuldade,repeticao);
}
void Menu(int jogadores,char jogador1[20], char jogador2[20], int dificuldade, int repeticao)
{
    int partidas,pontosjog1=0,pontosjog2=0,pinos;
    system("cls");//para não colocar um system cls em cada função achei melhor deixar 2 no menu
    int escolha;
    char senha[6];
    cout<<"\n                     ___  ___             _                           _             _ \n";
    cout<<"                     |  \\/  |            | |                         (_)           | |\n";
    cout<<"                     |      |  __ _  ___ | |_   ___  _ __  _ __ ___   _  _ __    __| |\n";
    cout<<"                     | |\\/| | / _` |/ __|| __| / _ \\| '__|| '_ ` _ \\ | || '_ \\  / _` |\n";
    cout<<"                     | |  | || (_| |\\__ \\| |_ |  __/| |   | | | | | || || | | || (_| |\n";
    cout<<"                     \\_|  |_/ \\__,_||___/ \\__| \\___||_|   |_| |_| |_||_||_| |_| \\__,_|\n";
    cout<<"\nDesenvolvedores: Victor Angelo, Marcos Paulo, Erickson.\n";
    cout<<"\n1-Jogar\n";
    cout<<"2-Instrucoes\n";
    cout<<"3-Configuracoes\n";
    cout<<"4-Identificacao\n";
    cin>>escolha;
    while(escolha<1 || escolha>4)
        cin>>escolha;
    system("cls");
    cin.ignore();
    switch(escolha)
    {
    case 1:
        if(dificuldade==1)
            pinos=4;
        else if(dificuldade==2)
            pinos=5;
        else
            pinos=6;
        while(escolha==1)
        {
            if(jogadores==1)
                partidas=1;
            else
            {
                cout<<"Quantas partidas deseja jogar? ";
                cin>>partidas;
                while(partidas%2!=0 || partidas<0)
                {
                    cout<<"Numero de partidas precisa ser par e maior que 0.\n";
                    cin>>partidas;
                }
            }
            system("cls");
            for(int jogada=0,pontosjog1=0,pontosjog2=0; jogada<partidas; jogada++)
            {
                cout<<"Partida "<<jogada+1<<endl;
                if(jogadores==1)
                {
                    if(jogada%2==0)
                        cout<<jogador1<<" sua vez.\n";
                    else
                        cout<<jogador2<<" sua vez.\n";
                    jogador2="jogador 2";
                    random(senha);
                    pontosjog1+=Jogo(senha,dificuldade);
                    cout<<"Parabens "<<jogador1<<" Voce ganhou!\n";
                }
                else
                {
                    if(jogada%2==0)
                    {
                        cout<<jogador1<<"\nDigite a senha: ";
                        for(int i=0; i<pinos; i++)
                        {
                            cin>>senha[i];
                            while(senha[i]<48 || senha[i]>54)
                                cin>>senha[i];
                        }
                        cin.ignore();
                        system("cls");
                        cout<<jogador2<<" sua vez.\n";
                        pontosjog1+=Jogo(senha,dificuldade);
                    }
                    else
                    {
                        cout<<jogador2<<"\nDigite a senha: ";
                        for(int i=0; i<pinos; i++)
                        {
                            cin>>senha[i];
                            while(senha[i]<48 || senha[i]>54)
                                cin>>senha[i];
                        }
                        cin.ignore();
                        system("cls");
                        cout<<jogador1<<" sua vez.\n";
                        pontosjog2+=Jogo(senha,dificuldade);
                    }
                    cout<<jogador1<<": "<<pontosjog1<<"\t"<<jogador2<<": "<<pontosjog2<<endl;

                    if(pontosjog1>pontosjog2)
                        cout<<"Parabens "<<jogador1<<" Voce ganhou!\n";
                    else
                        cout<<"Parabens "<<jogador2<<" Voce ganhou!\n";
                }
            }
            cout<<"Deseja jogar novamente?(1-sim, 2-nao)\n";
            cin>>escolha;
            while(escolha<1 || escolha>2)
            {
                cout<<"Numero invalido.\n";
                cin>>escolha;
            }
        }
        return;
    case 2:
        Instrucoes();
        break;
    case 3:
        Configuracoes(jogadores,dificuldade,repeticao);
        break;
    case 4:
        Identificacao(jogadores,jogador1,jogador2);
        break;
    }
    Menu(jogadores,jogador1,jogador2,dificuldade,repeticao);
}
int Jogo(char senha[6],int dificuldade)
{
    int l=0,cont=0,pinos,cores,limjogadas;
    char tabuleiro[14][12], corespossiveis[9]= {"12345678"};
    if(dificuldade==1)
    {
        pinos=4;
        cores=6;
        limjogadas=10;
    }
    else if(dificuldade==2)
    {
        pinos=5;
        cores=7;
        limjogadas=12;
    }
    else
    {
        pinos=6;
        cores=8;
        limjogadas=14;
    }
    for(int i=0; i<limjogadas; i++)
        for(int j=0; j<pinos*2; j++)
            tabuleiro[i][j]='*';
    tabuleir(tabuleiro,limjogadas,pinos);
    cout<<"As opcoes de cores sao: ";
    for(int i=0; i<cores; i++)
        cout<<corespossiveis[i]<<" ";
    cout<<endl;
    while(l<limjogadas and cont!=pinos)
    {
        cout<<"Digite a senha: ";
        cont=0;
        for(int i=0; i<pinos; i++)
        {
            cin>>tabuleiro[l][i];
            while((tabuleiro[l][i]<48 || tabuleiro[l][i]>54))
            {
                cout<<"Digite novamente. ";
                cin>>tabuleiro[l][i];
            }
        }
        for(int i=0; i<pinos; i++)
            if(tabuleiro[l][i]==senha[i])
            {
                tabuleiro[l][i+pinos]='P';
                cont++;
            }
        if(cont!=pinos)
            for(int a=0; a<pinos; a++)
                for(int j=0; j<pinos; j++)
                {
                    if(senha[a]==tabuleiro[l][j] and tabuleiro[l][j+pinos]=='*')
                    {
                        tabuleiro[l][j+pinos]='B';
                        break;
                    }
                }
        tabuleir(tabuleiro,limjogadas,pinos);
        l++;
    }
    if(cont==pinos)
        return 10-l;
    else
        return 0;
}
void Instrucoes()
{
    ifstream instrucao("instrução.txt");
    char ch;
    while(instrucao.get(ch))
        cout.put(ch);
    instrucao.close();
    cout<<endl;
    system("pause");
}
void Configuracoes(int& jogadores, int& dificuldade, int& repeticao)
{
    cout<<"Digite a quantidade de jogadores: ";
    cin>>jogadores;
    while(jogadores>2 || jogadores<1)
        cin>>jogadores;
    cout<<"Escolha a dificulade do jogo(nivel 1, nivel 2, nivel 3): ";
    cin>>dificuldade;
    while(dificuldade>3 || dificuldade<1)
        cin>>dificuldade;
    cout<<"Podera repetir cores na senha?(1-sim, 2-nao): ";
    cin>>repeticao;
    while(repeticao>3 || repeticao<1)
        cin>>repeticao;
}
void Identificacao(int jogadores,char jogador1[20], char jogador2[20])
{
    cout<<"Digite o nome do jogador 1: ";
    cin.getline(jogador1,20);
    if(jogadores==2)
    {
        cout<<"Digite o nome do jogador2: ";
        cin.getline(jogador2,20);
    }
}
void random(char senha[6])
{
    srand(time(0));
    for (int i=0; i<6; i++)
    {
        do
        {
            senha[i]=rand()%54;
        }
        while(senha[i]<48 || senha[i]>54);
        cout<<senha[i]<<endl;
    }
}
void tabuleir(char tabuleiro[][12],int limjogadas,int pinos)
{
    for(int i=0; i<limjogadas; i++)
    {
        cout<<"             ";
        for(int j=0; j<pinos*2; j++)
        {
            cout<<"  "<<tabuleiro[i][j];
            if(j==pinos-1)
                cout<<"\t";
        }
        cout<<endl;
    }
}
