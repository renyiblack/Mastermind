#include <iostream>
#include <iomanip>
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
void Random(char[],int,int,int);
void Tabuleir(char[][12],int,int);
void Recorde(int,char[]);
int main()
{
    int jogadores=1,dificuldade=1,repeticao=2;
    char jogador1[20]="Jogador 1",jogador2[20]="Jogador 2";
    Menu(jogadores,jogador1,jogador2,dificuldade,repeticao);
}
void Menu(int jogadores,char jogador1[20], char jogador2[20], int dificuldade, int repeticao)
{
    int partidas,pontosjog1=0,pontosjog2=0,pinos,maior;
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
        {
            pinos=4;
            maior=55;
        }
        else if(dificuldade==2)
        {
            pinos=5;
            maior=56;
        }
        else
        {
            pinos=6;
            maior=57;
        }
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
                if(jogadores==1)
                {
                    jogador2="jogador 2";
                    Random(senha,repeticao,maior,pinos);
                    pontosjog1+=Jogo(senha,dificuldade);
                    if(pontosjog1>0)
                    {
                        cout<<"Parabens "<<jogador1<<" Voce ganhou!\n";
                        ifstream fin("recorde.txt");
                        char ch;
                        int pontos;
                        while(fin.get(ch))
                            pontos=ch-'0';
                        fin.close();
                        if(pontosjog1>pontos)
                            Recorde(pontosjog1,jogador1);
                    }
                }
                else
                {
                    cout<<"Partida "<<jogada+1<<endl;
                    if(jogada%2==0)
                    {
                        cout<<jogador1<<"\nDigite a senha: ";
                        for(int i=0; i<pinos; i++)
                        {
                            cin>>senha[i];
                            while(senha[i]<49 || senha[i]>maior)
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
                            while(senha[i]<49 || senha[i]>maior)
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
        break;
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
    char tabuleiro[14][12],c, corespossiveis[9]= {"12345678"};
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
    Tabuleir(tabuleiro,limjogadas,pinos);
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
            cin>>c;
            while(c<49 || c>56)
            {
                fflush(stdin);
                cout<<"Digite novamente. ";
                cin>>c;
            }
            tabuleiro[l][i]=c;
        }
        system("cls");
        fflush(stdin);
        for(int i=0; i<pinos; i++)
        {
            if(tabuleiro[l][i]==senha[i])
            {
                tabuleiro[l][i+pinos]='P';
                cont++;
            }
        }
        if(cont!=pinos)
            for(int a=0; a<pinos; a++)
                for(int j=0; j<pinos; j++)
                {
                    if(senha[a]==tabuleiro[l][j] and tabuleiro[l][a+pinos]=='*')
                    {
                        tabuleiro[l][a+pinos]='B';
                        break;
                    }
                }
        Tabuleir(tabuleiro,limjogadas,pinos);
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
    cout<<"Recorde: ";
    char ch;
    ifstream fin("recorde.txt");
    while(fin.get(ch))
        cout.put(ch);
    fin.close();
    cout<<" pontos.";
    cout<<"\nDigite o nome do jogador 1: ";
    cin.getline(jogador1,20);
    if(jogadores==2)
    {
        cout<<"Digite o nome do jogador2: ";
        cin.getline(jogador2,20);
    }
}
void Random(char senha[6],int repeticao, int maior, int pinos)
{
    srand(time(0));
    for (int i=0; i<pinos; i++)
    {
        do
        {
            senha[i]=rand()%maior;
        }
        while(senha[i]<49 || senha[i]>maior);
    }
    if(repeticao==2)
        for (int i=0; i<pinos; i++)
        {
            for(int j=0; j<pinos; j++)
            {
                if( i!=j and senha[i]==senha[j])
                {
                    do
                    {
                        senha[j]=rand()%maior;
                    }
                    while(senha[j]<49 || senha[j]>maior);
                    i=0;
                }
            }
        }
    for (int i=0; i<pinos; i++)
        cout<<senha[i]<<endl;
}
void Tabuleir(char tabuleiro[][12],int limjogadas,int pinos)
{
    if(pinos==4)
    {
        cout<<"             _________________________________________________";
        cout<<"\n            |                                                 |\n            |Senha:";
    }
    else if(pinos==5)
    {
        cout<<"             _____________________________________________________________";
        cout<<"\n            |                                                             |\n            |Senha:";
    }
    else
    {
        cout<<"             _________________________________________________________________________";
        cout<<"\n            |                                                                         |\n            |Senha:";
    }
    for(int i=0; i<pinos; i++)
    {
        cout<<"(x)";
    }
    if(pinos==4)
    {
        cout<<"                               |\n";
        cout<<"            |_________________________________________________|\n";
    }
    else if(pinos==5)
    {
        cout<<"                                        |\n";
        cout<<"            |_____________________________________________________________|\n";
    }
    else
    {
        cout<<"                                                 |\n";
        cout<<"            |_________________________________________________________________________|\n";
    }
    for(int i=0; i<limjogadas; i++)
    {
        cout<<"            |";
        for(int j=0; j<pinos*2; j++)
        {
            cout<<"(_"<<tabuleiro[i][j]<<"_)|";
            if(j==pinos-1)
                cout<<" |";
        }
        cout<<endl;
    }
    if(pinos==4)
    cout<<"             ------------------------ ------------------------\n";
    else if(pinos==5)
        cout<<"             ------------------------------ ------------------------------\n";
    else
        cout<<"             ------------------------------------ ------------------------------------\n";
}
void Recorde(int pontosjog1,char jogador[20])
{
    ofstream fout("recorde.txt");
    for(int i=0; jogador[i]!='\0'; i++)
        fout<<jogador[i];
    fout<<": "<<pontosjog1;
    fout.close();
}
