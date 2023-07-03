#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int minimoDeLigasNecessarias(int NumTiposLigasMetalicas, vector<int>& ligas, int DemandaCliente) 
{
    vector<int> solucoesIntermediarias(DemandaCliente + 1, INF);
    solucoesIntermediarias[0] = 0;

    for (int i = 1; i <= DemandaCliente; i++) // itera sobre os valores de 1 a DemandaCliente, representando cada subdemanda a ser atendida
    {
        for (int j = 0; j < NumTiposLigasMetalicas; j++) // itera sobre os tipos de ligas disponíveis. Cada iteração representa a tentativa de usar uma liga de determinado tamanho para atender a uma subdemanda
        {
            if (ligas[j] <= i) // se o tamanho da liga for menor ou igual à subdemanda atual, então é possível usar essa liga para atender parte da demanda
            {
                int subproblem = solucoesIntermediarias[i - ligas[j]]; // subproblem = soluções intermediárias para a subdemanda atual menos o tamanho da liga atual

                if(subproblem != INF) // se a solução intermediária obtida for diferente de INF (ou seja, se for uma solução válida)
                {
                    if(subproblem + 1 < solucoesIntermediarias[i]) // se a solução intermediária obtida + 1 for menor que a solução intermediária atual
                    {
                        solucoesIntermediarias[i] = subproblem + 1; // atualiza a solução intermediária atual
                    }
                }
            }
        }
    }

    return solucoesIntermediarias[DemandaCliente];
}

int main(int argc, char const *argv[]) 
{
    // A primeira linha de um cenário de teste  é composta por um inteiro T, que representa o número de casos de teste no arquivo.
    int NumCasosTeste; // T
    std::cin >> NumCasosTeste;

    // para processar cada caso de teste
    for (int i = 0; i < NumCasosTeste; i++) 
    {
        // Cada caso de teste possui duas linhas de informações. 
        // A primeira linha é composta por dois número inteiros N e W, representando respectivamente o número de tipos de ligas 
        // metálicas disponível (1 ≤ N ≤ 1000) e a demanda do cliente, em metros (1 ≤ W ≤ 1000000).
        int NumTiposLigasMetalicas; // N
        int DemandaCliente; // W
        cin >> NumTiposLigasMetalicas >> DemandaCliente;

        if (NumTiposLigasMetalicas < 1 || NumTiposLigasMetalicas > 1000)
        {
            cout << "Numero de tipos de ligas metalicas disponiveis invalido." << endl;
            return 0;
        }

        if (DemandaCliente < 1 || DemandaCliente > 1000000)
        {
            cout << "Demanda do cliente invalida." << endl;
            return 0;
        }

        // vetor para armazenar os tamanhos das ligas metálicas disponíveis
        vector<int> ligas(NumTiposLigasMetalicas);

        // A segunda linha de um caso de teste contém N inteiros representando o tamanho li de cada liga metálica disponível (1 ≤ li ≤ 1000). 
        for (int j = 0; j < NumTiposLigasMetalicas; j++) 
        {
            cin >> ligas[j];

            if (ligas[j] < 1 || ligas[j] > 1000)
            {
                cout << "Tamanho de liga metalica disponivel invalido." << endl;
                return 0;
            }
        }

        // para calcular o número mínimo de ligas metálicas para suprir uma demanda de tamanho W
        int result = minimoDeLigasNecessarias(NumTiposLigasMetalicas, ligas, DemandaCliente);
        cout << result << endl;
    }

    return 0;
}