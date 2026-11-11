#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    // ------------------------------------------
    // Dados das contas (item 2.1)
    // ------------------------------------------
    const int MAX_CONTAS = 100; // limite maximo de 100 contas

    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS]; // 1 = Corrente, 2 = Poupanca
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    // Controla quantas contas ja foram cadastradas
    int quantidadeContas = 0;

    // ------------------------------------------
    // Historico de movimentacoes (item 2.2)
    // Cada posicao dos arrays representa uma movimentacao
    // ------------------------------------------
    const int MAX_MOVIMENTACOES = 500;

    int contaMovimentacao[MAX_MOVIMENTACOES];    // numero da conta
    char tipoMovimentacao[MAX_MOVIMENTACOES];    // 'D' = entrada, 'S' = saida
    double valorMovimentacao[MAX_MOVIMENTACOES]; // valor movimentado

    // Controla quantas movimentacoes ja foram registradas
    int quantidadeMovimentacoes = 0;

    // ------------------------------------------
    // Variaveis auxiliares
    // ------------------------------------------
    int opcao;
    int contaEscolhida;
    int contaDestino;
    int posicao;        // indice da conta encontrada (-1 = nao encontrada)
    int posicaoDestino; // indice da conta de destino na transferencia
    int novoTipo;
    int totalExtrato;
    double valor;
    bool repetido;

    // Mostra os valores em dinheiro sempre com 2 casas decimais
    cout << fixed << setprecision(2);

    do
    {
        cout << endl;
        cout << "***************************************" << endl;
        cout << "**             BANCO UNI             **" << endl;
        cout << "***************************************" << endl;
        cout << " 1 - Cadastrar conta" << endl;
        cout << " 2 - Listar contas" << endl;
        cout << " 3 - Consultar conta" << endl;
        cout << " 4 - Depositar" << endl;
        cout << " 5 - Sacar" << endl;
        cout << " 6 - Transferir" << endl;
        cout << " 7 - Exibir extrato" << endl;
        cout << " 8 - Verificar saldo" << endl;
        cout << " 9 - Alterar tipo da conta" << endl;
        cout << "10 - Ativar/Desativar conta" << endl;
        cout << " 0 - Sair" << endl;
        cout << "***************************************" << endl;
        cout << "Escolha uma opcao: ";

        // Leitura protegida: se o usuario digitar algo que nao seja um
        // numero (ex.: letras), a entrada e descartada e o valor vira -1,
        // que sempre cai em "invalido". Esse mesmo bloco se repete em
        // todas as leituras de numeros do programa.
        cin >> opcao;
        if (cin.fail() || cin.peek() != '\n')
        {
            if (cin.eof()) return 0; // entrada encerrada: finaliza o programa
            cin.clear();
            opcao = -1;
        }
        cin.ignore(10000, '\n'); // descarta o resto da linha digitada

        switch (opcao)
        {
            // ==========================================
            // 1 - CADASTRAR CONTA
            // ==========================================
            case 1:

                if (quantidadeContas >= MAX_CONTAS)
                {
                    cout << endl;
                    cout << "Limite de " << MAX_CONTAS << " contas atingido!" << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== CADASTRO DE CONTA =====" << endl;

                    // Validacao do numero da conta:
                    // deve ser maior que zero e nao pode estar em uso
                    do
                    {
                        cout << "Digite o numero da conta: ";
                        cin >> numeroConta[quantidadeContas];
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            numeroConta[quantidadeContas] = -1;
                        }
                        cin.ignore(10000, '\n');

                        repetido = false;

                        if (numeroConta[quantidadeContas] <= 0)
                        {
                            cout << "Erro! O numero da conta deve ser um numero inteiro maior que zero." << endl;
                        }
                        else
                        {
                            // Verifica se ja existe uma conta com esse numero
                            for (int i = 0; i < quantidadeContas; i++)
                            {
                                if (numeroConta[i] == numeroConta[quantidadeContas])
                                {
                                    repetido = true;
                                }
                            }

                            if (repetido == true)
                            {
                                cout << "Erro! Ja existe uma conta com esse numero." << endl;
                            }
                        }

                    } while (numeroConta[quantidadeContas] <= 0 || repetido == true);

                    // Nome do cliente (nao pode ficar em branco)
                    do
                    {
                        cout << "Digite o nome do cliente: ";
                        getline(cin, nomeCliente[quantidadeContas]);
                        if (cin.fail()) return 0;

                        if (nomeCliente[quantidadeContas] == "")
                        {
                            cout << "Erro! O nome nao pode ficar em branco." << endl;
                        }

                    } while (nomeCliente[quantidadeContas] == "");

                    // CPF (nao pode ficar em branco)
                    do
                    {
                        cout << "Digite o CPF do cliente: ";
                        getline(cin, cpf[quantidadeContas]);
                        if (cin.fail()) return 0;

                        if (cpf[quantidadeContas] == "")
                        {
                            cout << "Erro! O CPF nao pode ficar em branco." << endl;
                        }

                    } while (cpf[quantidadeContas] == "");

                    // Tipo da conta
                    do
                    {
                        cout << "Digite o tipo da conta:" << endl;
                        cout << "1 - Corrente" << endl;
                        cout << "2 - Poupanca" << endl;
                        cout << "Opcao: ";
                        cin >> tipoConta[quantidadeContas];
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            tipoConta[quantidadeContas] = -1;
                        }
                        cin.ignore(10000, '\n');

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
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            saldo[quantidadeContas] = -1;
                        }
                        cin.ignore(10000, '\n');

                        if (saldo[quantidadeContas] < 0)
                        {
                            cout << "Erro! Digite um valor que nao seja negativo." << endl;
                            cout << "(use ponto para os centavos, ex.: 150.50)" << endl;
                        }

                    } while (saldo[quantidadeContas] < 0);

                    // Toda conta comeca ativa
                    contaAtiva[quantidadeContas] = true;

                    quantidadeContas++;

                    cout << endl;
                    cout << "Conta cadastrada com sucesso!" << endl;
                }

                break;


            // ==========================================
            // 2 - LISTAR CONTAS
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
                    cout << "===== CONTAS CADASTRADAS =====" << endl;

                    // Percorre todas as contas cadastradas
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        cout << "----------------------------------------" << endl;
                        cout << "Numero da conta: " << numeroConta[i] << endl;
                        cout << "Nome do cliente: " << nomeCliente[i] << endl;
                        cout << "CPF: " << cpf[i] << endl;

                        if (tipoConta[i] == 1)
                        {
                            cout << "Tipo: Corrente" << endl;
                        }
                        else
                        {
                            cout << "Tipo: Poupanca" << endl;
                        }

                        cout << "Saldo: R$ " << saldo[i] << endl;

                        if (contaAtiva[i] == true)
                        {
                            cout << "Situacao: Ativa" << endl;
                        }
                        else
                        {
                            cout << "Situacao: Inativa" << endl;
                        }
                    }

                    cout << "----------------------------------------" << endl;
                    cout << "Total de contas: " << quantidadeContas << endl;
                }

                break;


            // ==========================================
            // 3 - CONSULTAR CONTA
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
                    cout << "===== CONSULTAR CONTA =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
            // 4 - DEPOSITAR
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
                    cout << "===== DEPOSITO =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
                    else if (contaAtiva[posicao] == false)
                    {
                        cout << "A conta esta inativa!" << endl;
                        cout << "Nao e possivel realizar o deposito." << endl;
                    }
                    else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES)
                    {
                        // Sem espaco no historico, a operacao nao e feita
                        cout << "Limite de movimentacoes atingido!" << endl;
                        cout << "Nao e possivel realizar o deposito." << endl;
                    }
                    else
                    {
                        cout << "Digite o valor do deposito: R$ ";
                        cin >> valor;
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            valor = -1;
                        }
                        cin.ignore(10000, '\n');

                        if (valor <= 0)
                        {
                            cout << "Valor invalido! Digite um valor maior que zero." << endl;
                            cout << "(use ponto para os centavos, ex.: 150.50)" << endl;
                        }
                        else
                        {
                            // Atualiza o saldo da conta
                            saldo[posicao] = saldo[posicao] + valor;

                            // Registra a movimentacao no historico
                            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[posicao];
                            tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                            valorMovimentacao[quantidadeMovimentacoes] = valor;

                            quantidadeMovimentacoes++;

                            cout << "Deposito realizado com sucesso!" << endl;
                            cout << "Novo saldo: R$ " << saldo[posicao] << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 5 - SACAR
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
                    cout << "===== SAQUE =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
                    else if (contaAtiva[posicao] == false)
                    {
                        cout << "A conta esta inativa!" << endl;
                        cout << "Nao e possivel realizar o saque." << endl;
                    }
                    else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES)
                    {
                        // Sem espaco no historico, a operacao nao e feita
                        cout << "Limite de movimentacoes atingido!" << endl;
                        cout << "Nao e possivel realizar o saque." << endl;
                    }
                    else
                    {
                        cout << "Digite o valor do saque: R$ ";
                        cin >> valor;
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            valor = -1;
                        }
                        cin.ignore(10000, '\n');

                        if (valor <= 0)
                        {
                            cout << "Valor invalido! Digite um valor maior que zero." << endl;
                            cout << "(use ponto para os centavos, ex.: 150.50)" << endl;
                        }
                        else if (valor > saldo[posicao])
                        {
                            // Verifica se ha saldo suficiente
                            cout << "Saldo insuficiente!" << endl;
                            cout << "Saldo disponivel: R$ " << saldo[posicao] << endl;
                        }
                        else
                        {
                            // Atualiza o saldo da conta
                            saldo[posicao] = saldo[posicao] - valor;

                            // Registra a movimentacao no historico
                            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[posicao];
                            tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                            valorMovimentacao[quantidadeMovimentacoes] = valor;

                            quantidadeMovimentacoes++;

                            cout << "Saque realizado com sucesso!" << endl;
                            cout << "Novo saldo: R$ " << saldo[posicao] << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 6 - TRANSFERIR
            // ==========================================
            case 6:

                if (quantidadeContas < 2)
                {
                    cout << endl;
                    cout << "E preciso ter pelo menos 2 contas cadastradas para transferir." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== TRANSFERENCIA =====" << endl;

                    cout << "Digite o numero da conta de ORIGEM: ";
                    cin >> contaEscolhida;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

                    cout << "Digite o numero da conta de DESTINO: ";
                    cin >> contaDestino;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaDestino = -1;
                    }
                    cin.ignore(10000, '\n');

                    posicao = -1;
                    posicaoDestino = -1;

                    // Procura as duas contas
                    for (int i = 0; i < quantidadeContas; i++)
                    {
                        if (numeroConta[i] == contaEscolhida)
                        {
                            posicao = i;
                        }

                        if (numeroConta[i] == contaDestino)
                        {
                            posicaoDestino = i;
                        }
                    }

                    if (posicao == -1)
                    {
                        cout << "Conta de origem nao encontrada!" << endl;
                    }
                    else if (posicaoDestino == -1)
                    {
                        cout << "Conta de destino nao encontrada!" << endl;
                    }
                    else if (posicao == posicaoDestino)
                    {
                        cout << "A conta de origem e a de destino devem ser diferentes!" << endl;
                    }
                    else if (contaAtiva[posicao] == false)
                    {
                        cout << "A conta de origem esta inativa!" << endl;
                        cout << "Nao e possivel realizar a transferencia." << endl;
                    }
                    else if (contaAtiva[posicaoDestino] == false)
                    {
                        cout << "A conta de destino esta inativa!" << endl;
                        cout << "Nao e possivel realizar a transferencia." << endl;
                    }
                    else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES)
                    {
                        // A transferencia gera 2 registros (saida e entrada),
                        // entao precisa de espaco para os dois no historico
                        cout << "Limite de movimentacoes atingido!" << endl;
                        cout << "Nao e possivel realizar a transferencia." << endl;
                    }
                    else
                    {
                        cout << "Digite o valor da transferencia: R$ ";
                        cin >> valor;
                        if (cin.fail() || cin.peek() != '\n')
                        {
                            if (cin.eof()) return 0;
                            cin.clear();
                            valor = -1;
                        }
                        cin.ignore(10000, '\n');

                        if (valor <= 0)
                        {
                            cout << "Valor invalido! Digite um valor maior que zero." << endl;
                            cout << "(use ponto para os centavos, ex.: 150.50)" << endl;
                        }
                        else if (valor > saldo[posicao])
                        {
                            // Verifica se a origem tem saldo suficiente
                            cout << "Saldo insuficiente na conta de origem!" << endl;
                            cout << "Saldo disponivel: R$ " << saldo[posicao] << endl;
                        }
                        else
                        {
                            // Atualiza os saldos das duas contas
                            saldo[posicao] = saldo[posicao] - valor;
                            saldo[posicaoDestino] = saldo[posicaoDestino] + valor;

                            // Registro 1: saida ('S') na conta de origem
                            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[posicao];
                            tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                            valorMovimentacao[quantidadeMovimentacoes] = valor;

                            // Registro 2: entrada ('D') na conta de destino
                            contaMovimentacao[quantidadeMovimentacoes + 1] = numeroConta[posicaoDestino];
                            tipoMovimentacao[quantidadeMovimentacoes + 1] = 'D';
                            valorMovimentacao[quantidadeMovimentacoes + 1] = valor;

                            // Uma transferencia = 2 movimentacoes
                            quantidadeMovimentacoes = quantidadeMovimentacoes + 2;

                            cout << "Transferencia realizada com sucesso!" << endl;
                            cout << "Conta " << numeroConta[posicao] << " - "
                                 << nomeCliente[posicao] << ": novo saldo R$ "
                                 << saldo[posicao] << endl;
                            cout << "Conta " << numeroConta[posicaoDestino] << " - "
                                 << nomeCliente[posicaoDestino] << ": novo saldo R$ "
                                 << saldo[posicaoDestino] << endl;
                        }
                    }
                }

                break;


            // ==========================================
            // 7 - EXIBIR EXTRATO
            // ==========================================
            case 7:

                if (quantidadeContas == 0)
                {
                    cout << endl;
                    cout << "Nenhuma conta cadastrada." << endl;
                }
                else
                {
                    cout << endl;
                    cout << "===== EXTRATO =====" << endl;

                    cout << "Digite o numero da conta: ";
                    cin >> contaEscolhida;
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
                        cout << endl;
                        cout << "Conta: " << numeroConta[posicao] << " - "
                             << nomeCliente[posicao] << endl;
                        cout << "----------------------------------------" << endl;

                        totalExtrato = 0;

                        // Percorre o historico e mostra somente as
                        // movimentacoes que pertencem a conta consultada
                        for (int i = 0; i < quantidadeMovimentacoes; i++)
                        {
                            if (contaMovimentacao[i] == numeroConta[posicao])
                            {
                                if (tipoMovimentacao[i] == 'D')
                                {
                                    cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                                }
                                else if (tipoMovimentacao[i] == 'S')
                                {
                                    cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                                }

                                totalExtrato++;
                            }
                        }

                        if (totalExtrato == 0)
                        {
                            cout << "Nenhuma movimentacao registrada para esta conta." << endl;
                        }

                        cout << "----------------------------------------" << endl;
                        cout << "Total de movimentacoes: " << totalExtrato << endl;
                        cout << "Saldo atual: R$ " << saldo[posicao] << endl;
                    }
                }

                break;


            // ==========================================
            // 8 - VERIFICAR SALDO
            // ==========================================
            case 8:

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
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
            // 9 - ALTERAR TIPO DA CONTA
            // ==========================================
            case 9:

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
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
                                if (cin.fail() || cin.peek() != '\n')
                                {
                                    if (cin.eof()) return 0;
                                    cin.clear();
                                    novoTipo = -1;
                                }
                                cin.ignore(10000, '\n');

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
            // 10 - ATIVAR/DESATIVAR CONTA
            // ==========================================
            case 10:

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
                    if (cin.fail() || cin.peek() != '\n')
                    {
                        if (cin.eof()) return 0;
                        cin.clear();
                        contaEscolhida = -1;
                    }
                    cin.ignore(10000, '\n');

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
            // 0 - SAIR
            // ==========================================
            case 0:

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
                cout << "Escolha uma opcao entre 0 e 10." << endl;

                break;
        }

    } while (opcao != 0);

    return 0;
}
