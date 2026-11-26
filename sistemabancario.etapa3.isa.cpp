#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// ---------------- Constantes ----------------
const int MAX_CONTAS = 100;
const int MAX_MOVIMENTACOES = 1000;
const string ARQ_CONTAS = "contas.txt";
const string ARQ_MOVIMENTACOES = "movimentacoes.txt";

// ---------------- Arrays das contas ----------------
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];      // 1 = Corrente, 2 = Poupanca
double saldo[MAX_CONTAS];
int contaAtiva[MAX_CONTAS];     // 1 = ativa, 0 = inativa
int quantidadeContas = 0;

// ---------------- Arrays das movimentacoes ----------------
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];   // 'D' = Deposito, 'S' = Saque
double valorMovimentacao[MAX_MOVIMENTACOES];
int quantidadeMovimentacoes = 0;

// ---------------- Prototipos ----------------
// Arquivos
void carregarContas();
void salvarContas();
void carregarMovimentacoes();
void salvarMovimentacoes();

// Auxiliares
void exibirMenu();
int buscarConta(int numero);
string nomeTipoConta(int tipo);
bool registrarMovimentacao(int numero, char tipo, double valor);
double lerValorPositivo(const string &mensagem);
void mostrarConta(int pos);

// Funcionalidades
void cadastrarConta();
void listarContas();
void consultarConta();
void depositar();
void sacar();
void transferir();
void exibirExtrato();
void alterarSituacaoConta();

// ============================================================
int main() {
    int opcao;

    // Ao iniciar, recupera os dados gravados nas execucoes anteriores
    carregarContas();
    carregarMovimentacoes();

    cout << "Dados carregados: " << quantidadeContas << " conta(s) e "
         << quantidadeMovimentacoes << " movimentacao(oes)." << endl;

    do {
        exibirMenu();
        cin >> opcao;

        // Evita loop infinito caso o usuario digite uma letra
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 8: alterarSituacaoConta(); break;
            case 0:
                // Garante que tudo esteja gravado antes de sair
                salvarContas();
                salvarMovimentacoes();
                cout << "Dados salvos. Encerrando o sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);

    return 0;
}

// ============================================================
//                   FUNCOES DE ARQUIVO
// ============================================================

// Le o arquivo contas.txt e preenche os arrays das contas.
// Formato de cada linha: numero;nome;cpf;tipo;saldo;ativa
void carregarContas() {
    ifstream arquivo(ARQ_CONTAS);

    // Primeira execucao: o arquivo ainda nao existe
    if (!arquivo.is_open()) {
        quantidadeContas = 0;
        return;
    }

    quantidadeContas = 0;
    int numero;

    // O >> le o numero e para no ';'. O ignore() descarta o ';'.
    while (quantidadeContas < MAX_CONTAS && arquivo >> numero) {
        arquivo.ignore();                                         // ;
        getline(arquivo, nomeCliente[quantidadeContas], ';');     // nome (pode ter espacos)
        getline(arquivo, cpf[quantidadeContas], ';');             // cpf
        arquivo >> tipoConta[quantidadeContas];
        arquivo.ignore();                                         // ;
        arquivo >> saldo[quantidadeContas];
        arquivo.ignore();                                         // ;
        arquivo >> contaAtiva[quantidadeContas];
        arquivo.ignore(10000, '\n');                              // fim da linha

        numeroConta[quantidadeContas] = numero;
        quantidadeContas++;
    }

    arquivo.close();
}

// Grava todas as contas (sobrescreve o arquivo com os dados atualizados)
void salvarContas() {
    ofstream arquivo(ARQ_CONTAS);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << ARQ_CONTAS << " para gravacao!" << endl;
        return;
    }

    arquivo << fixed << setprecision(2);
    for (int i = 0; i < quantidadeContas; i++) {
        arquivo << numeroConta[i] << ";"
                << nomeCliente[i] << ";"
                << cpf[i] << ";"
                << tipoConta[i] << ";"
                << saldo[i] << ";"
                << contaAtiva[i] << endl;
    }

    arquivo.close();
}

// Le o arquivo movimentacoes.txt e preenche os arrays de movimentacoes.
// Formato de cada linha: conta;tipo;valor
void carregarMovimentacoes() {
    ifstream arquivo(ARQ_MOVIMENTACOES);

    if (!arquivo.is_open()) {
        quantidadeMovimentacoes = 0;
        return;
    }

    quantidadeMovimentacoes = 0;
    int numero;

    while (quantidadeMovimentacoes < MAX_MOVIMENTACOES && arquivo >> numero) {
        arquivo.ignore();                                          // ;
        arquivo >> tipoMovimentacao[quantidadeMovimentacoes];      // D ou S
        arquivo.ignore();                                          // ;
        arquivo >> valorMovimentacao[quantidadeMovimentacoes];
        arquivo.ignore(10000, '\n');

        contaMovimentacao[quantidadeMovimentacoes] = numero;
        quantidadeMovimentacoes++;
    }

    arquivo.close();
}

// Grava todo o historico de movimentacoes
void salvarMovimentacoes() {
    ofstream arquivo(ARQ_MOVIMENTACOES);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir " << ARQ_MOVIMENTACOES << " para gravacao!" << endl;
        return;
    }

    arquivo << fixed << setprecision(2);
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        arquivo << contaMovimentacao[i] << ";"
                << tipoMovimentacao[i] << ";"
                << valorMovimentacao[i] << endl;
    }

    arquivo.close();
}

// ============================================================
//                   FUNCOES AUXILIARES
// ============================================================

void exibirMenu() {
    cout << "\n========== SISTEMA BANCARIO ==========" << endl;
    cout << "1 - Cadastrar conta" << endl;
    cout << "2 - Listar contas" << endl;
    cout << "3 - Consultar conta" << endl;
    cout << "4 - Depositar" << endl;
    cout << "5 - Sacar" << endl;
    cout << "6 - Transferir" << endl;
    cout << "7 - Extrato" << endl;
    cout << "8 - Ativar/Desativar conta" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha uma opcao: ";
}

// Retorna a posicao da conta nos arrays, ou -1 se nao existir
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

string nomeTipoConta(int tipo) {
    if (tipo == 1) return "Corrente";
    if (tipo == 2) return "Poupanca";
    return "Desconhecido";
}

// Guarda a movimentacao no array e acrescenta a linha no final do arquivo
// (ios::app preserva o historico das execucoes anteriores)
bool registrarMovimentacao(int numero, char tipo, double valor) {
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        cout << "Limite de movimentacoes atingido!" << endl;
        return false;
    }

    contaMovimentacao[quantidadeMovimentacoes] = numero;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;

    ofstream arquivo(ARQ_MOVIMENTACOES, ios::app);
    if (arquivo.is_open()) {
        arquivo << fixed << setprecision(2);
        arquivo << numero << ";" << tipo << ";" << valor << endl;
        arquivo.close();
    } else {
        cout << "Erro ao gravar em " << ARQ_MOVIMENTACOES << "!" << endl;
    }
    return true;
}

// Le um valor real maior que zero
double lerValorPositivo(const string &mensagem) {
    double valor;
    do {
        cout << mensagem;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            valor = -1;
        }
        if (valor <= 0) {
            cout << "Valor invalido! Digite um valor maior que zero." << endl;
        }
    } while (valor <= 0);
    return valor;
}

void mostrarConta(int pos) {
    cout << "Conta:    " << numeroConta[pos] << endl;
    cout << "Cliente:  " << nomeCliente[pos] << endl;
    cout << "CPF:      " << cpf[pos] << endl;
    cout << "Tipo:     " << nomeTipoConta(tipoConta[pos]) << endl;
    cout << "Saldo:    R$ " << fixed << setprecision(2) << saldo[pos] << endl;
    cout << "Situacao: " << (contaAtiva[pos] == 1 ? "Ativa" : "Inativa") << endl;
}

// ============================================================
//                   FUNCIONALIDADES
// ============================================================

// 1 - Cadastrar conta
void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Limite de contas atingido!" << endl;
        return;
    }

    int numero;
    cout << "\n--- CADASTRO DE CONTA ---" << endl;
    cout << "Numero da conta: ";
    cin >> numero;
    if (cin.fail() || numero <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Numero invalido!" << endl;
        return;
    }
    if (buscarConta(numero) != -1) {
        cout << "Ja existe uma conta com esse numero!" << endl;
        return;
    }

    string nome, documento;
    cin.ignore();   // limpa o Enter que ficou no buffer antes do getline
    do {
        cout << "Nome do cliente: ";
        getline(cin, nome);
        // O ';' e o separador do arquivo, entao nao pode fazer parte do nome
        if (nome.empty() || nome.find(';') != string::npos) {
            cout << "Nome invalido (nao pode ser vazio nem conter ';')." << endl;
        }
    } while (nome.empty() || nome.find(';') != string::npos);

    do {
        cout << "CPF (somente numeros): ";
        getline(cin, documento);
        if (documento.length() != 11) {
            cout << "CPF deve ter 11 digitos." << endl;
        }
    } while (documento.length() != 11);

    int tipo;
    do {
        cout << "Tipo da conta (1 - Corrente / 2 - Poupanca): ";
        cin >> tipo;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            tipo = 0;
        }
    } while (tipo != 1 && tipo != 2);

    double depositoInicial;
    cout << "Deposito inicial (0 para nenhum): R$ ";
    cin >> depositoInicial;
    if (cin.fail() || depositoInicial < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        depositoInicial = 0;
    }

    numeroConta[quantidadeContas] = numero;
    nomeCliente[quantidadeContas] = nome;
    cpf[quantidadeContas] = documento;
    tipoConta[quantidadeContas] = tipo;
    saldo[quantidadeContas] = depositoInicial;
    contaAtiva[quantidadeContas] = 1;
    quantidadeContas++;

    // O deposito inicial entra no extrato como um deposito comum
    if (depositoInicial > 0) {
        registrarMovimentacao(numero, 'D', depositoInicial);
    }

    salvarContas();
    cout << "Conta cadastrada e salva com sucesso!" << endl;
}

// 2 - Listar contas
void listarContas() {
    cout << "\n--- CONTAS CADASTRADAS ---" << endl;
    if (quantidadeContas == 0) {
        cout << "Nenhuma conta cadastrada." << endl;
        return;
    }

    cout << left << setw(8) << "Conta"
         << setw(25) << "Cliente"
         << setw(14) << "CPF"
         << setw(10) << "Tipo"
         << setw(10) << "Situacao"
         << right << setw(14) << "Saldo (R$)" << endl;
    cout << string(81, '-') << endl;

    for (int i = 0; i < quantidadeContas; i++) {
        cout << left << setw(8) << numeroConta[i]
             << setw(25) << nomeCliente[i].substr(0, 24)
             << setw(14) << cpf[i]
             << setw(10) << nomeTipoConta(tipoConta[i])
             << setw(10) << (contaAtiva[i] == 1 ? "Ativa" : "Inativa")
             << right << setw(14) << fixed << setprecision(2) << saldo[i] << endl;
    }
}

// 3 - Consultar conta pelo numero
void consultarConta() {
    int numero;
    cout << "\nNumero da conta: ";
    cin >> numero;
    int pos = buscarConta(numero);
    if (pos == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    cout << "\n--- DADOS DA CONTA ---" << endl;
    mostrarConta(pos);
}

// 4 - Depositar
void depositar() {
    int numero;
    cout << "\nNumero da conta: ";
    cin >> numero;
    int pos = buscarConta(numero);
    if (pos == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    if (contaAtiva[pos] == 0) {
        cout << "Conta inativa! Operacao nao permitida." << endl;
        return;
    }

    double valor = lerValorPositivo("Valor do deposito: R$ ");

    if (!registrarMovimentacao(numero, 'D', valor)) return;
    saldo[pos] += valor;
    salvarContas();

    cout << "Deposito realizado! Novo saldo: R$ "
         << fixed << setprecision(2) << saldo[pos] << endl;
}

// 5 - Sacar
void sacar() {
    int numero;
    cout << "\nNumero da conta: ";
    cin >> numero;
    int pos = buscarConta(numero);
    if (pos == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }
    if (contaAtiva[pos] == 0) {
        cout << "Conta inativa! Operacao nao permitida." << endl;
        return;
    }

    double valor = lerValorPositivo("Valor do saque: R$ ");

    if (valor > saldo[pos]) {
        cout << "Saldo insuficiente! Saldo atual: R$ "
             << fixed << setprecision(2) << saldo[pos] << endl;
        return;
    }

    if (!registrarMovimentacao(numero, 'S', valor)) return;
    saldo[pos] -= valor;
    salvarContas();

    cout << "Saque realizado! Novo saldo: R$ "
         << fixed << setprecision(2) << saldo[pos] << endl;
}

// 6 - Transferir (gera um S na origem e um D no destino)
void transferir() {
    int origem, destino;
    cout << "\nConta de origem: ";
    cin >> origem;
    int posOrigem = buscarConta(origem);
    if (posOrigem == -1) {
        cout << "Conta de origem nao encontrada!" << endl;
        return;
    }

    cout << "Conta de destino: ";
    cin >> destino;
    int posDestino = buscarConta(destino);
    if (posDestino == -1) {
        cout << "Conta de destino nao encontrada!" << endl;
        return;
    }

    if (origem == destino) {
        cout << "As contas de origem e destino devem ser diferentes!" << endl;
        return;
    }
    if (contaAtiva[posOrigem] == 0 || contaAtiva[posDestino] == 0) {
        cout << "Uma das contas esta inativa! Operacao nao permitida." << endl;
        return;
    }
    if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
        cout << "Limite de movimentacoes atingido!" << endl;
        return;
    }

    double valor = lerValorPositivo("Valor da transferencia: R$ ");

    if (valor > saldo[posOrigem]) {
        cout << "Saldo insuficiente! Saldo atual: R$ "
             << fixed << setprecision(2) << saldo[posOrigem] << endl;
        return;
    }

    saldo[posOrigem] -= valor;
    saldo[posDestino] += valor;
    registrarMovimentacao(origem, 'S', valor);
    registrarMovimentacao(destino, 'D', valor);
    salvarContas();

    cout << "Transferencia realizada com sucesso!" << endl;
    cout << fixed << setprecision(2);
    cout << "Saldo de " << nomeCliente[posOrigem] << ": R$ " << saldo[posOrigem] << endl;
    cout << "Saldo de " << nomeCliente[posDestino] << ": R$ " << saldo[posDestino] << endl;
}

// 7 - Extrato de uma conta
void exibirExtrato() {
    int numero;
    cout << "\nNumero da conta: ";
    cin >> numero;
    int pos = buscarConta(numero);
    if (pos == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }

    cout << "\n--- EXTRATO DA CONTA " << numero << " - "
         << nomeCliente[pos] << " ---" << endl;
    cout << left << setw(6) << "Tipo" << setw(12) << "Descricao"
         << right << setw(14) << "Valor (R$)" << endl;
    cout << string(32, '-') << endl;

    int encontradas = 0;
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == numero) {
            cout << left << setw(6) << tipoMovimentacao[i]
                 << setw(12) << (tipoMovimentacao[i] == 'D' ? "Deposito" : "Saque")
                 << right << setw(14) << fixed << setprecision(2)
                 << valorMovimentacao[i] << endl;
            encontradas++;
        }
    }

    if (encontradas == 0) {
        cout << "Nenhuma movimentacao registrada." << endl;
    }
    cout << string(32, '-') << endl;
    cout << "Saldo atual: R$ " << fixed << setprecision(2) << saldo[pos] << endl;
}

// 8 - Ativar/Desativar conta (altera a situacao e salva no arquivo)
void alterarSituacaoConta() {
    int numero;
    cout << "\nNumero da conta: ";
    cin >> numero;
    int pos = buscarConta(numero);
    if (pos == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }

    if (contaAtiva[pos] == 1) {
        contaAtiva[pos] = 0;
        cout << "Conta " << numero << " desativada." << endl;
    } else {
        contaAtiva[pos] = 1;
        cout << "Conta " << numero << " ativada." << endl;
    }
    salvarContas();
}
