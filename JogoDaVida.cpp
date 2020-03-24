// PDS 2 - Lista de Exercicios 01: Programa Jogo da Vida
// Aluno: Ruy Braga Filho



#include <iostream>
#include <fstream>
#include <string>

using namespace std;



// ########################## Inicio da definicao da classe Vida ##########################



// Definicao da Classe Vida, que representa uma colonia de organismos do jogo Vida
// de John Horton Conway. 
class Vida {


    private:

        // Matriz de char que representa o mapa contendo a colonia de organismos do jogo.
        // Esse mapa tera numLinhas linhas e numColunas colunas.  

        long numLinhas;
        long numColunas;
        
        char** mapaGeracaoAtual;
        char** mapaGeracaoAnterior;


        // Metodo privado que conta o numero de organismos na vizinhanca da
        // celula da posicao (linha, coluna) do mapa passado como parametro
        long numVizinhos( char** mapa, long linha, long coluna );

        // Metodo privado que verifica se a celula (linha,coluna) do mapa passado como parametro tem
        // um organismo vivo
        bool temOrganismo( char** mapa, long linha, long coluna );

        // Metodo que cria um novo organismo na posicao (linha, coluna) do mapa passado como parametro
        void nasce( char** mapa, long linha, long coluna );

        // Metodo que elimina um organismo na posicao (linha, coluna) do mapa passado como parametro
        void morre( char** mapa, long linha, long coluna );



    public:

        // Construtor da classe Vida. Esse construtor cria um mapa
        // vazio, ou seja, contendo caracteres ' ', com dimensao
        // (numLinhas, NumColunas).
        Vida( long numLinhas, long numColunas );

        // Destrutor da classe Vida. Esse destrutor desaloca a memoria 
        // dinamica alocada pelo objeto da classe Vida
        ~Vida();    


        // Metodo que cria um novo organismo na posicao (linha, coluna) do mapa da geracao atual
        void nasce( long linha, long coluna );

        // Metodo que elimina um organismo na posicao (linha, coluna) do mapa da geracao atual
        void morre( long linha, long coluna );

        // Metodo que gera a proxima geracao de organismos, com base na geracao atual e 
        // nas regras do Jogo da Vida de John Horton Conway
        void proximaGeracao();

        // Metodo que imprime a colonia de organismos no console, onde:
        //    *  significa presenca de organismo 
        //   ' ' significa ausencia de organismo 
        void imprime();

}; // Fim da definicao da classe vida




// ************************** Definicoes dos metodos privados da classe Vida **************************



// Definicao do metodo privado que conta o numero de organismos na vizinhanca
// da celula da posicao (linha, coluna) do mapa passado como parametro
long Vida::numVizinhos( char** mapa, long linha, long coluna )  {

    long count{0};
    
    // Conta o numeto de organismos na linha de cima
    if( this->temOrganismo( mapa, linha-1, coluna-1 ) ) ++count;
    if( this->temOrganismo( mapa, linha-1, coluna )   ) ++count;
    if( this->temOrganismo( mapa, linha-1, coluna+1 ) ) ++count;

    // Conta o numeto de organismos na linha da celula
    if( this->temOrganismo( mapa, linha, coluna-1 ) ) ++count;
    if( this->temOrganismo( mapa, linha, coluna+1 ) ) ++count;

    // Conta o numeto de organismos na linha de baixo
    if( this->temOrganismo( mapa, linha+1, coluna-1 ) ) ++count;
    if( this->temOrganismo( mapa, linha+1, coluna )   ) ++count;
    if( this->temOrganismo( mapa, linha+1, coluna+1 ) ) ++count;

    return( count );

} // Fim da definicao do metodo numVizinhos



// Definicao do metodo privado que verifica se a celula (linha,coluna) do mapa passado como parametro tem
// um organismo vivo
bool Vida::temOrganismo( char** mapa, long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->numLinhas  &&
         coluna >= 0   &&   coluna < this->numColunas  )   {

        return(  mapa[linha][coluna] == '*' );
    }

    return( false );  
    
} // Fim da definicao do metodo temOrganismo



// Definicao do metodo que cria um novo organismo na posicao (linha, coluna) do mapa passado como parametro
void Vida::nasce( char** mapa, long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->numLinhas  &&
         coluna >= 0   &&   coluna < this->numColunas  )   {

        mapa[linha][coluna] = '*';
    }  

} // Fim da definicao do metodo nasce



// Definicao do metodo que elimina um organismo na posicao (linha, coluna) do mapa passado como parametro
void Vida::morre( char** mapa, long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->numLinhas  &&
         coluna >= 0   &&   coluna < this->numColunas  )   {

        mapa[linha][coluna] = ' ';
    }  

} // Fim da definicao do metodo morre




// ************************** Definicoes do construtor e destrutor da classe Vida **************************


// Definicao do construtor da classe Vida. Esse construtor cria um 
// mapa vazio, ou seja, contendo caracteres ' ', com dimensao
// (numLinhas, NumColunas).
Vida::Vida( long numLinhas, long numColunas )  {

    long i, j;

    char** mapaGeracaoAtual;
    char** mapaGeracaoAnterior;
  

    // Alocacao dinamica de memoria para os mapas

    mapaGeracaoAtual     = new char*[numLinhas];
    mapaGeracaoAnterior  = new char*[numLinhas];

    for( i=0; i<numLinhas; ++i )  {

        mapaGeracaoAtual[i]     = new char[numColunas];
        mapaGeracaoAnterior[i]  = new char[numColunas];
    }


    // Inicializacao das celulas do mapa

    for( i=0; i<numLinhas; ++i )  {

        for( j=0; j<numColunas; ++j )  {

            mapaGeracaoAtual[i][j] = mapaGeracaoAnterior[i][j] = ' ';             
        }
    }


    // Inicializacao dos atributos do objeto
    this->numLinhas   =  numLinhas;
    this->numColunas  =  numColunas;

    this->mapaGeracaoAtual     =  mapaGeracaoAtual;
    this->mapaGeracaoAnterior  =  mapaGeracaoAnterior;

} // Fim da definicao do construtor da classe Vida



// Definicao do destrutor da classe Vida. Esse destrutor desaloca 
// a memoria dinamica alocada pelo objeto da classe Vida
Vida::~Vida()  {

    long i;

    // Variaveis auxiliares para os atributos do objeto
    long numLinhas   =  this->numLinhas;
    char** mapaGeracaoAtual     =  this->mapaGeracaoAtual;
    char** mapaGeracaoAnterior  =  this->mapaGeracaoAnterior;    
  

    // Desalocacao dinamica da memoria dos mapas

    for( i=0; i<numLinhas; ++i )  {

        delete[] mapaGeracaoAtual[i];
        delete[] mapaGeracaoAnterior[i];       
    }

    delete[] mapaGeracaoAtual;
    delete[] mapaGeracaoAnterior;    

} // Fim da definicao do destrutor da classe Vida  





// ************************** Definicoes dos metodos publicos da classe Vida **************************



// Definicao do metodo que cria um novo organismo na posicao (linha, coluna) do mapa da geracao atual
void Vida::nasce( long linha, long coluna )  {

    this->nasce( this->mapaGeracaoAtual, linha, coluna );

} // Fim da definicao do metodo nasce



// Definicao do metodo que elimina um organismo na posicao (linha, coluna) do mapa da geracao atual
void Vida::morre( long linha, long coluna )  {

    this->morre( this->mapaGeracaoAtual, linha, coluna );

} // Fim da definicao do metodo morre



// Definicao do metodo que gera a proxima geracao de organismos, com base na 
// geracao atual e nas regras do Jogo da Vida de John Horton Conway
void Vida::proximaGeracao()  {

    long i, j;
    long numVizinhos;

    // Variaveis auxiliares para os atributos do objeto
    long numLinhas   =  this->numLinhas;
    long numColunas  =  this->numColunas;    
    char** mapaGeracaoAnterior  =  this->mapaGeracaoAtual;  // Geracao atual vira geracao anterior
    char** mapaGeracaoFutura    =  this->mapaGeracaoAnterior;  // Proxima Geracao


    // Produz a proxima geracao de organismos
    for( i=0; i<numLinhas; ++i )  {

        for( j=0; j<numColunas; ++j )  {

            // Processa a celula atual

            // Inicializa a celula atual da proxima geracao com o 
            // conteudo da mesma celula, na geracao anterior
            mapaGeracaoFutura[i][j] = mapaGeracaoAnterior[i][j];
            
            // Conta o numero de celulas vizinhas ocupadas
            numVizinhos = this->numVizinhos( mapaGeracaoAnterior, i, j );

            // Aplica as regras do jogo da vida aa celula atual   
            if( temOrganismo( mapaGeracaoAnterior, i, j ) )  {
                
                if( numVizinhos <= 1 || numVizinhos >= 4 )   this->morre( mapaGeracaoFutura, i, j );                    

            } else {

                if( numVizinhos == 3 )   this->nasce( mapaGeracaoFutura, i, j ); 
            } 

        } // for j
    } // for i

    this->mapaGeracaoAtual    = mapaGeracaoFutura;
    this->mapaGeracaoAnterior = mapaGeracaoAnterior;

} // Fim da definicao do metodo proximaGeracao



// Definicao do metodo que imprime a colonia de organismos no console, onde:
//    *  significa presenca de organismo 
//   ' ' significa ausencia de organismo 
void Vida::imprime()  {

    long i, j;

    // Variaveis auxiliares para os atributos do objeto
    long numLinhas   =  this->numLinhas;
    long numColunas  =  this->numColunas;
    char** mapaGeracaoAtual     =  this->mapaGeracaoAtual;

    // Imprime o conteudo das celulas em console
    for( i=0; i<numLinhas; ++i )  {

        for( j=0; j<numColunas; ++j )  {

            cout << mapaGeracaoAtual[i][j];
        }
        cout << endl;
    }    

} // Fim da definicao do metodo imprime




// ########################## Fim da definicao da classe Vida ##########################





// prototipo da funcao que carrega uma colonia de organismos
// do arquivo cujo nome eh passado como parametro.
// O arquivo tem o seguinte formato:
// n
// x1 y1
// x2 y2
// ...
// xn yn
// onde n é um long contendo o numero de organismos vivos e
// as proximas n linhas contem as coordenadas x, y de cada
// um dos organismos vivos 
void carregarColoniaDoArquivo( Vida* colonia,
                               string nomeArquivo );


// Definicao da funcao main
int main()   {

    Vida colonia( 22, 80 );

    carregarColoniaDoArquivo( &colonia, "entrada.txt" ); 

    colonia.imprime();

    cout << endl << endl << endl;
    cout << "JOGO VIDA!";
    cout << endl << endl << endl;

    return( 0 );

} // Fim da funcao main


// Definicao da funcao que carrega uma colonia de organismos
// do arquivo cujo nome eh passado como parametro.
// O arquivo tem o seguinte formato:
// n
// x1 y1
// x2 y2
// ...
// xn  yn
// onde n é um long contendo o numero de organismos vivos e
// as proximas n linhas contem as coordenadas x, y de cada
// um dos organismos vivos 
void carregarColoniaDoArquivo( Vida* colonia,
                               string nomeArquivo )  {

    ifstream fin( nomeArquivo );
    long n;
    long x, y;

    fin >> n;
    cout << n << " \n";

    while( n > 0 )  {

        fin >> x;
        fin >> y;

        cout << x << " ";
        cout << y << " \n";


        colonia->nasce( x, y );

        --n;
    }

} // Fim da funcao carregarColoniaDoArquivo
