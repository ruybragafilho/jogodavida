// PDS 2 - Lista de Exercicios 01: Programa Jogo da Vida
// Aluno: Ruy Braga Filho



#include <iostream>
#include <fstream>
#include <string>

using namespace std;



// ########################## Inicio da definicao da classe Vida ##########################



// Definicao da Classe Vida, que representa uma colonia de organismos do jogo Vida
// de John Horton Conway. Essa colonia habita um mapa de 22 linhas por 80 colunas.
class Vida {

    private:

        // Matriz de char contendo a colonia de organismos do jogo 

        static const long NUM_LINHAS{22};
        static const long NUM_COLUNAS{80};
        
        char colonia[NUM_LINHAS][NUM_COLUNAS];
        

        // Metodo privado que conta o numero de organismos na vizinhanca
        // na celula da posicao (linha, coluna)
        long numVizinhos( long linha, long coluna );

        // Metodo privado que verifica se a celula (linha,coluna) tem
        // um organismo vivo
        bool temOrganismo( long linha, long coluna );



    public:

        // Construtor da classe Vida. Esse construtor cria um mapa
        // vazio, ou seja, contendo caracteres ' '.
        Vida();

        // Metodo que cria um novo organismo na posicao (linha, coluna)
        void nasce( long linha, long coluna );

        // Metodo que elimina um organismo na posicao (linha, coluna)
        void morre( long linha, long coluna );

        // Metodo que gera a proxima geracao de organismos, com base na geracao atual e 
        // nas regras do Jogo da Vida de John Horton Conway
        void proximaGeracao();

        // Metodo que imprime a colonia de organismos no console, onde:
        //    1 significa presenca de organismo 
        //    0 significa ausencia de organismo 
        void imprime();

}; // Fim da definicao da classe vida




// ************************** Definicao dos metodos privados da classe Vida **************************



// Definicao do metodo privado que conta o numero de organismos 
// na vizinhanca na celula da posicao (linha, coluna)
long Vida::numVizinhos( long linha, long coluna )  {

    long count{0};
    
    // Conta o numeto de organismos na linha de cima
    if( this->temOrganismo(linha-1, coluna-1) ) ++count;
    if( this->temOrganismo(linha-1, coluna)   ) ++count;
    if( this->temOrganismo(linha-1, coluna+1) ) ++count;

    // Conta o numeto de organismos na linha da celula
    if( this->temOrganismo(linha, coluna-1) ) ++count;
    if( this->temOrganismo(linha, coluna+1) ) ++count;

    // Conta o numeto de organismos na linha de baixo
    if( this->temOrganismo(linha+1, coluna-1) ) ++count;
    if( this->temOrganismo(linha+1, coluna)   ) ++count;
    if( this->temOrganismo(linha+1, coluna+1) ) ++count;

    return(count);

} // Fim da definicao do metodo numVizinhos



// Definicao do metodo privado que verifica se a celula (linha,coluna) tem
// um organismo vivo
bool Vida::temOrganismo( long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->NUM_LINHAS  &&
         coluna >= 0   &&   coluna < this->NUM_COLUNAS  )   {

        return(  this->colonia[linha][coluna] == '*' );
    }

    return( false );  
    
} // Fim da definicao do metodo bool Vida::temOrganismo( long linha, long coluna )  {





// ************************** Definicao do construtor da classe Vida **************************



// Definicao do construtor da classe Vida. Esse construtor cria um mapa
// vazio, ou seja, contendo caracteres ' '.
Vida::Vida()  {

    long i, j;

    for( i=0; i<this->NUM_LINHAS; ++i )  {

        for( j=0; j<this->NUM_COLUNAS; ++j )  {

            this->colonia[i][j] = ' ';
        }
    }

} // Fim da definicao do construtor da classe Vida




// ************************** Definicao dos metodos publicos da classe Vida **************************



// Definicao do metodo que cria um novo organismo na posicao (linha, coluna)
void Vida::nasce( long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->NUM_LINHAS  &&
         coluna >= 0   &&   coluna < this->NUM_COLUNAS  )   {

        this->colonia[linha][coluna] = '*';
    }  

} // Fim da definicao do metodo nasce



// Definicao do metodo que elimina um organismo na posicao (linha, coluna)
void Vida::morre( long linha, long coluna )  {

    if(  linha  >= 0   &&   linha  < this->NUM_LINHAS  &&
         coluna >= 0   &&   coluna < this->NUM_COLUNAS  )   {

        this->colonia[linha][coluna] = ' ';
    }  

} // Fim da definicao do metodo morre



// Metodo que gera a proxima geracao de organismos, com base na geracao atual e 
// nas regras do Jogo da Vida de John Horton Conway
void Vida::proximaGeracao()  {

    long i, j;
    long numVizinhos;

    char geracaoAnterior[this->NUM_LINHAS][this->NUM_COLUNAS];


    // Cria uma copia temporaria da geracao anterior
    for( i=0; i<this->NUM_LINHAS; ++i )  {

        for( j=0; j<this->NUM_COLUNAS; ++j )  {

            geracaoAnterior[i][j] = this->colonia[i][j];        

        } // for j
    } // for i



    for( i=0; i<this->NUM_LINHAS; ++i )  {

        for( j=0; j<this->NUM_COLUNAS; ++j )  {

            numVizinhos = this->numVizinhos( i, j );

            if( temOrganismo( i, j ) )  {

                if( numVizinhos <= 1 || numVizinhos >= 4 )   this->morre(i,j);                    

            } else {

                if( numVizinhos == 3 )   this->nasce(i,j); 

            }

        } // for j
    } // for i

} // Fim da definicao do metodo proximaGeracao



// Definicao do metodo que imprime a colonia de organismos no console, onde:
//    1 significa presenca de organismo 
//    0 significa ausencia de organismo 
void Vida::imprime()  {

    long i, j;

    for( i=0; i<this->NUM_LINHAS; ++i )  {

        for( j=0; j<this->NUM_COLUNAS; ++j )  {

            cout << this->colonia[i][j];
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

    Vida colonia;

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
