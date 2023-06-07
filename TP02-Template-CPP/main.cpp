#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#define INF 0x3f3f3f3f

using namespace std;

// funcao que verifica se é possível encontrar um caminho de usuário para vaga
bool podeRealizarMatch(const string& usuario, const unordered_map<string, unordered_set<string>>& qualificacoes, unordered_map<string, string>& matchUsuario, unordered_map<string, string>& matchVaga, unordered_set<string>& visitados)
{
    for (const string& vaga : qualificacoes.at(usuario))  // percorre as vagas que o usuário está qualificado
    {
        if (!visitados.count(vaga))  // se a vaga ainda não foi visitada
        {
            visitados.insert(vaga);  // adiciona a vaga ao conjunto de visitados

            if (!matchVaga.count(vaga) || podeRealizarMatch(matchVaga[vaga], qualificacoes, matchUsuario, matchVaga, visitados))  // se a vaga não foi combinada ou se é possível realizar o match
            {
                matchUsuario[usuario] = vaga;  // combina o usuário com a vaga
                matchVaga[vaga] = usuario;  // combina a vaga com o usuário
                return true;
            }
        }
    }

    return false;
}

int AlgoritmoExato(const vector<pair<string, string>>& qualificacoes)
{
    // Cria um mapa de usuários para vagas, onde cada usuário tem um conjunto de vagas que ele está qualificado
    unordered_map<string, unordered_set<string>> qualificacoesUsuario; // cada qualificacao de um usuário com uma vaga representa uma aresta entre o nó usuário e o nó vaga

    for (const auto& qualificacao : qualificacoes) // percorre o vetor de qualificações
    {
        const string& usuario = qualificacao.first;  // armazena o nome do usuário
        const string& vaga = qualificacao.second;  // armazena o nome da vaga

        qualificacoesUsuario[usuario].insert(vaga);  // adiciona a vaga ao conjunto de vagas qualificadas do usuário
    }

    unordered_map<string, string> matchUsuario;  // cria um mapa de usuários para vagas, onde cada usuário tem uma vaga que ele está qualificado
    unordered_map<string, string> matchVaga;  // cria um mapa de vagas para usuários, onde cada vaga tem um usuário que ele está qualificado

    int tamanhoDoMatch = 0; // para armazenar quantos matches foram realizados

    for (const auto& entrada : qualificacoesUsuario)  // percorre o mapa de qualificações de usuários para vagas
    {
        const string& usuario = entrada.first;  // armazena o nome do usuário
        unordered_set<string> visitados;  // cria um conjunto de strings para armazenar as vagas que já foram visitadas

        if (podeRealizarMatch(usuario, qualificacoesUsuario, matchUsuario, matchVaga, visitados))  // se é possível realizar o match
        {
            tamanhoDoMatch++;
        }
    }

    return tamanhoDoMatch;
}

int main(int argc, char const *argv[]) 
{
    // Ler a entrada
    int numUsuarios;  // U
    int numVagas;  // J
    int numQualificacoes;  // E

    cin >> numUsuarios >> numVagas >> numQualificacoes;

    // Validar as restrições de entrada
    if(numUsuarios < 2 || numUsuarios > 10000)
    {
        cout << "Número inválido de usuários" << endl;
        return 0;
    }
    if(numVagas < 1 || numVagas > 10000)
    {
        cout << "Número inválido de vagas de emprego" << endl;
        return 0;
    }
    if(numQualificacoes < 1 || numQualificacoes > (numUsuarios * numVagas))
    {
        cout << "Número inválido de qualificações usuário-vaga" << endl;
        return 0;
    }

    // Cada uma das próximas E linhas descreve uma qualificação usuário-vaga, representadas pelo nome do usuário seguido 
    // pelo nome da vaga, obrigatoriamente nessa ordem. Os dois identificadores são representados por strings, separados por 
    // um espaço simples.

    vector<pair<string, string>> qualificacoes;  // cria o vetor de pares de strings para armazenar as qualificações

    for(int i = 0; i < numQualificacoes; i++)  // Le as qualificações e armazena no vetor de qualificações
    {
        string NomeDoUsuario;
        string NomeDaVaga;

        cin >> NomeDoUsuario >> NomeDaVaga;

        qualificacoes.emplace_back(NomeDoUsuario, NomeDaVaga);
    }

    int ResultadoExato = AlgoritmoExato(qualificacoes);  // para calcular o algoritmo exato

    // para calcular o algoritmo guloso
    vector<string> matchUsuario;  // vetor de strings para armazenar os usuários que já foram combinados
    vector<string> matchVaga;  // vetor de strings para armazenar as vagas que já foram combinadas

    int ResultadoGuloso = 0;  // armazena o resultado do algoritmo guloso

    for (auto& qualificacaoIndividual : qualificacoes) // percorre o vetor de qualificações
    {
        const string& usuario = qualificacaoIndividual.first;  // armazena o nome do usuário
        const string& vaga = qualificacaoIndividual.second;  // armazena o nome da vaga
        
        auto itUsuario = find(matchUsuario.begin(), matchUsuario.end(), usuario);  // Verifica se o usuário já foi combinado
        auto itVaga = find(matchVaga.begin(), matchVaga.end(), vaga);  // Verifica se a vaga já foi combinada

        if (itUsuario == matchUsuario.end() && itVaga == matchVaga.end())  // se o usuário e a vaga não foram combinados
        {
            matchUsuario.push_back(usuario);  // adiciona o usuário ao vetor de usuários combinados
            matchVaga.push_back(vaga);  // adiciona a vaga ao vetor de vagas combinadas
            ResultadoGuloso++;  // incrementa o resultado do algoritmo guloso
        }
    }

    cout << "Guloso: " << ResultadoGuloso << endl;  // imprime o resultado do algoritmo guloso
    cout << "Exato: " << ResultadoExato << endl;  // imprime o resultado do algoritmo exato

    return 0;
}