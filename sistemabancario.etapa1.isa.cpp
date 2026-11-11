#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Quantidade máxima de contas
    const int MAX_CONTAS = 5;

    // Variáveis para armazenar os dados das contas
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    // Controla quantas contas já foram cadastradas
    int quantidadeContas = 0;

    // Variáveis auxiliares
    int opcao;
    int contaEscolhida;
    int posicao;
    int novoTipo;

    do
    {
        cout << endl;
        cout << "***************************************" << endl;
        cout << "**             BANCO UNI             **" << endl;
        cout << "***************************************" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Consultar conta" << endl;
        cout << "3 - Verificar saldo" << endl;
        cout << "4 - Alterar tipo da conta" << endl;
        cout << "5 - Ativar/Desativar conta" << endl;
        cout << "6 - Sair" << endl;
        cout << "***************************************" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
            // ==========================================
            // 1 - CADASTRAR CONTA
            // ==========================================
            case 1:

                if (quantidadeContas >= MAX_CONTAS)
                {
                    cout << endl;
                    cout << "Limite de 5 contas atingido!" << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== CADASTRO DE CONTA =====" << endl;

                    // Validação do número da conta
                    do
                    {
                        cout << "Digite o numero da conta: ";
                        cin >> numeroConta[quantidadeContas];

                        if (numeroConta[quantidadeContas] <= 0)
                        {
                            cout << "Erro! O numero da conta deve ser maior que zero." << endl;
                        }

                    } while (numeroConta[quantidadeContas] <= 0);

                    // Nome do cliente
                    cout << "Digite o nome do cliente: ";
                    cin.ignore();
                    getline(cin, nomeCliente[quantidadeContas]);

                    // CPF
                    cout << "Digite o CPF do cliente: ";
                    getline(cin, cpf[quantidadeContas]);

                    // Tipo da conta
                    do
                    {
                        cout << "Digite o tipo da conta:" << endl;
                        cout << "1 - Corrente" << endl;
                        cout << "2 - Poupanca" << endl;
                        cout << "Opcao: ";
                        cin >> tipoConta[quantidadeContas];

                        if (tipoConta[quantidadeContas] != 1 &&
                            tipoConta[quantidadeContas] != 2)
                        {
                            cout << "Erro! Digite 1 para Corrente ou 2 para Poupanca." << endl;
                        }

                    } while (tipoConta[quantidadeContas] != 1 &&
                             tipoConta[quantidadeContas] != 2);

                    // Saldo inicial
                    do
                    {
                        cout << "Digite o saldo inicial: R$ ";
                        cin >> saldo[quantidadeContas];

                        if (saldo[quantidadeContas] < 0)
                        {
                            cout << "Erro! O saldo nao pode ser negativo." << endl;
                        }

                    } while (saldo[quantidadeContas] < 0);

                    // Toda conta começa ativa
                    contaAtiva[quantidadeContas] = true;

                    quantidadeContas++;

                    cout << endl;
                    cout << "Conta cadastrada com sucesso!" << endl;
                }

                break;


            // ==========================================
            // 2 - CONSULTAR CONTA
            // ==========================================
            case 2:

                if (quantidadeContas == 0)
                {
                    cout << endl;
                    cout << "Nenhuma conta cadastrada." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== CONSULTAR CONTA =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;

                    posicao = -1;

                    // Procura a conta cadastrada
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        if (numeroConta[i] == contaEscolhida)
                        {
                            posicao = i;
                        }
                    }

                    if (posicao == -1)
                    {
                        cout << "Conta nao encontrada!" << endl;
                    }
                    else
                    {
                        cout << endl;
                        cout << "===== DADOS DA CONTA =====" << endl;
                        cout << "Numero da conta: " << numeroConta[posicao] << endl;
                        cout << "Nome do cliente: " << nomeCliente[posicao] << endl;
                        cout << "CPF: " << cpf[posicao] << endl;

                        if (tipoConta[posicao] == 1)
                        {
                            cout << "Tipo: Corrente" << endl;
                        }
                        else
                        {
                            cout << "Tipo: Poupanca" << endl;
                        }

                        cout << "Saldo: R$ " << saldo[posicao] << endl;

                        if (contaAtiva[posicao] == true)
                        {
                            cout << "Situacao: Ativa" << endl;
                        }
                        else
                        {
                            cout << "Situacao: Inativa" << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 3 - VERIFICAR SALDO
            // ==========================================
            case 3:

                if (quantidadeContas == 0)
                {
                    cout << endl;
                    cout << "Nenhuma conta cadastrada." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== VERIFICAR SALDO =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;

                    posicao = -1;

                    // Procura a conta
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        if (numeroConta[i] == contaEscolhida)
                        {
                            posicao = i;
                        }
                    }

                    if (posicao == -1)
                    {
                        cout << "Conta nao encontrada!" << endl;
                    }
                    else
                    {
                        // Verifica se a conta esta ativa
                        if (contaAtiva[posicao] == true)
                        {
                            cout << "Saldo da conta: R$ "
                                 << saldo[posicao] << endl;
                        }
                        else
                        {
                            cout << "A conta esta inativa!" << endl;
                            cout << "Nao e possivel consultar o saldo." << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 4 - ALTERAR TIPO DA CONTA
            // ==========================================
            case 4:

                if (quantidadeContas == 0)
                {
                    cout << endl;
                    cout << "Nenhuma conta cadastrada." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== ALTERAR TIPO DA CONTA =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;

                    posicao = -1;

                    // Procura a conta
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        if (numeroConta[i] == contaEscolhida)
                        {
                            posicao = i;
                        }
                    }

                    if (posicao == -1)
                    {
                        cout << "Conta nao encontrada!" << endl;
                    }
                    else
                    {
                        // A operacao depende da conta estar ativa
                        if (contaAtiva[posicao] == true)
                        {
                            do
                            {
                                cout << endl;
                                cout << "Novo tipo da conta:" << endl;
                                cout << "1 - Corrente" << endl;
                                cout << "2 - Poupanca" << endl;
                                cout << "Opcao: ";
                                cin >> novoTipo;

                                if (novoTipo != 1 && novoTipo != 2)
                                {
                                    cout << "Opcao invalida!" << endl;
                                }

                            } while (novoTipo != 1 && novoTipo != 2);

                            tipoConta[posicao] = novoTipo;

                            cout << "Tipo da conta alterado com sucesso!" << endl;
                        }
                        else
                        {
                            cout << "A conta esta inativa!" << endl;
                            cout << "Nao e possivel alterar o tipo." << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 5 - ATIVAR/DESATIVAR CONTA
            // ==========================================
            case 5:

                if (quantidadeContas == 0)
                {
                    cout << endl;
                    cout << "Nenhuma conta cadastrada." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== ATIVAR/DESATIVAR CONTA =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;

                    posicao = -1;

                    // Procura a conta
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        if (numeroConta[i] == contaEscolhida)
                        {
                            posicao = i;
                        }
                    }

                    if (posicao == -1)
                    {
                        cout << "Conta nao encontrada!" << endl;
                    }
                    else
                    {
                        // Inverte o estado da conta
                        if (contaAtiva[posicao] == true)
                        {
                            contaAtiva[posicao] = false;
                            cout << "Conta desativada com sucesso!" << endl;
                        }
                        else
                        {
                            contaAtiva[posicao] = true;
                            cout << "Conta ativada com sucesso!" << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 6 - SAIR
            // ==========================================
            case 6:

                cout << endl;
                cout << "Obrigado por utilizar o Banco UNI!" << endl;
                cout << "Sistema encerrado." << endl;

                break;


            // ==========================================
            // OPCAO INVALIDA
            // ==========================================
            default:

                cout << endl;
                cout << "Opcao invalida!" << endl;
                cout << "Escolha uma opcao entre 1 e 6." << endl;

                break;
        }

    } while (opcao != 6);

    return 0;
}