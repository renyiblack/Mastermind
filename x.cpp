#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Menu(int,char[],char[],int,int);
int Jogo(char[]);
void Instrucoes();
void Configuracoes(int&,int&,int&);
void Identificacao(int,char[],char[]);
void random(char[]);
void tabuleir(char[][8]);
int main()
{
    int jogadores=1,dificuldade=1,repeticao=2;
    char jogador1[20]="Jogador 1",jogador2[20]="Jogador 2";
    Menu(jogadores,jogador1,jogador2,dificuldade,repeticao);
}
void Menu(int jogadores,char jogador1[20], char jogador2[20], int dificuldade, int repeticao)
{
    int partidas;
    system("cls");//para não colocar um system cls em cada função achei melhor deixar 2 no menu
    int escolha;
    char senha[5];
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
                    Jogo(senha);
                }
                else
                {
                    if(jogada%2==0)
                    {
                        cout<<jogador1<<"\nDigite a senha: ";
                        cin.ignore();
                        cin.getline(senha,5);
                        system("cls");
                        cout<<jogador2<<" sua vez.\n";
                        pontosjog1+=Jogo(senha);
                    }
                    else
                    {
                        cout<<jogador2<<"\nDigite a senha: ";
                        cin.ignore();
                        cin.getline(senha,5);
                        system("cls");
                        cout<<jogador1<<" sua vez.\n";
                        pontosjog2+=Jogo(senha);
                    }
                    cout<<jogador1<<": "<<pontosjog1<<"\t"<<jogador2<<": "<<pontosjog2<<endl;
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
int Jogo(char senha[4])
{

    int l=0,cont=0;
    char tabuleiro[10][8], cores[7]= {"123456"};
    for(int i=0; i<10; i++)
        for(int j=0; j<8; j++)
            tabuleiro[i][j]='*';
    tabuleir(tabuleiro);
    cout<<"As opcoes de cores sao: ";
    for(int i=0; i<6; i++)
        cout<<cores[i]<<" ";
    cout<<endl;
    cout<<"Digite a senha: ";
    while(l<10 and cont!=4)
    {
        cont=0;
        for(int i=0; i<4; i++)
        {
            cin>>tabuleiro[l][i];
            while(tabuleiro[l][i]<48 || tabuleiro[l][i]>54)
            {
                cin.ignore();
                cout<<"Digite novamente. ";
                cin>>tabuleiro[l][i];
            }
        }
        for(int i=0; i<4; i++)
            if(tabuleiro[l][i]==senha[i])
            {
                tabuleiro[l][i+4]='P';
                cont++;
            }
        if(cont!=4)
            for(int a=0; a<4; a++)
                for(int j=0; j<4; j++)
                    if(senha[a]==tabuleiro[l][j] and tabuleiro[l][a+4]=='*')
                    {
                        tabuleiro[l][a+4]='B';
                        break;
                    }
        tabuleir(tabuleiro);
        l++;
    }
    if(cont==4)
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
void random(char senha[4])
{
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        do
        {
            senha[i]=rand()%60;
        }
        while(senha[i]<48 || senha[i]>54);
        cout<<senha[i]<<endl;
    }
}
void tabuleir(char tabuleiro[10][8])
{
    for(int i=0; i<10; i++)
    {
        cout<<"             ";
        for(int j=0; j<8; j++)
        {
            cout<<"  "<<tabuleiro[i][j];
            if(j==3)
                cout<<"\t";
        }
        cout<<endl;
    }
}
