#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

struct venda {
    string nome;
    int qntVenda;
    float preco;
    string data;
};

void aleatorio(venda vendas[], int tamanho) {
    srand((unsigned)time(0));
    for (int i = 0; i < tamanho; i++) {
        vendas[i].nome = "Produto_" + to_string(i + 1);
        vendas[i].qntVenda = rand() % 100 + 1;
        vendas[i].preco = (rand() % 10000) / 100.00;
        vendas[i].data = "20/10/2024";
    }
}

void bolha(venda vendas[], int tamanho) {
    aleatorio(vendas, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (vendas[i].preco < vendas[j].preco) {
                swap(vendas[i], vendas[j]);
            }
        }
    }
}

void insercao(venda vendas[], int tamanho) {
    aleatorio(vendas, tamanho);
    for (int i = 1; i < tamanho; i++) {
        venda chave = vendas[i];
        int j = i - 1;
        while (j >= 0 && vendas[j].preco < chave.preco) {
            vendas[j + 1] = vendas[j];
            j--;
        }
        vendas[j + 1] = chave;
    }
}

void selecao(venda vendas[], int tamanho) {
    aleatorio(vendas, tamanho);
    for (int i = 0; i < tamanho - 1; i++) {
        int maior = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vendas[maior].preco < vendas[j].preco) {
                maior = j;
            }
        }
        if (i != maior) {
            swap(vendas[i], vendas[maior]);
        }
    }
}

void contagem(venda vendas[], int tamanho) {
    // Encontrar o maior preço para definir o range
    aleatorio(vendas, tamanho);  // Se necessário, embaralha as vendas

    int max_preco = 0;
    for (int i = 0; i < tamanho; ++i) {
        int preco = static_cast<int>(vendas[i].preco * 100);  // Preço em centavos
        if (preco > max_preco) {
            max_preco = preco;
        }
    }

    // Definir o range baseado no maior preço
    int range = max_preco + 1;  // +1 para incluir o maior valor

    // Alocar o array de contagem
    int* count = new int[range]();

    // Contagem das vendas por preço (convertendo para centavos)
    for (int i = 0; i < tamanho; i++) {
        int preco = static_cast<int>(vendas[i].preco * 100);
        count[preco]++;
    }

    // Acumulando as contagens (contagem cumulativa)
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];  // Acumula para ordenação crescente
    }

    // Criando array temporário para a ordenação
    venda* output = new venda[tamanho];

    // Preenchendo o array temporário com os itens ordenados em ordem DECRESCENTE
    for (int i = 0; i < tamanho; i++) {
        int preco = static_cast<int>(vendas[i].preco * 100);
        output[--count[preco]] = vendas[i];  // Decrementa o valor de contagem
    }

    // Copiando os elementos de volta para o array original em ordem inversa (decrescente)
    for (int i = 0, j = tamanho - 1; i < tamanho; i++, j--) {
        vendas[j] = output[i];
    }

    // Liberando a memória alocada dinamicamente
    delete[] count;
    delete[] output;

}

void shell(venda vendas[], int tamanho) {
    aleatorio(vendas, tamanho);
    for (int intervalo = tamanho / 2; intervalo > 0; intervalo /= 2) {
        for (int j = intervalo; j < tamanho; j++) {
            venda chave = vendas[j];
            int k;
            for (k = j; k >= intervalo && vendas[k - intervalo].preco < chave.preco; k -= intervalo) {
                vendas[k] = vendas[k - intervalo];
            }
            vendas[k] = chave;
        }
    }
}

int partition(venda vendas[], int low, int high) {
    float pivot = vendas[high].preco;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (vendas[j].preco >= pivot) {
            i++;
            swap(vendas[i], vendas[j]);
        }
    }
    swap(vendas[i + 1], vendas[high]);
    return (i + 1);
}

void quickSort(venda vendas[], int low, int high) {
    if (low < high) {
        int pi = partition(vendas, low, high);
        quickSort(vendas, low, pi - 1);
        quickSort(vendas, pi + 1, high);
    }
}

void TempoExecucao(void (*func)(venda[], int), venda arr[], int tamanho, const string& nomeMetodo) {
    auto inicio = chrono::high_resolution_clock::now();

    func(arr, tamanho);

    for (int i = 0; i < tamanho; i++) {
        cout << "\nNome produto: " << arr[i].nome << endl;
        cout << "Quantidade vendido: " << arr[i].qntVenda << endl;
        cout << "Preco unitario: " << arr[i].preco << endl;
        cout << "Data compra: " << arr[i].data << endl;
    }

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim - inicio;

    cout << "\nModo " << nomeMetodo << " executado em: " << duracao.count() << " milissegundos" << endl;

}

void exibirMenu() {
    cout << "\n==========================================" << endl;
    cout << "      SELECIONE UM METODO DE ORDENACAO" << endl;
    cout << "==========================================\n" << endl;
    cout << "  [1] - Ordenacao Bolha (Bubble Sort)" << endl;
    cout << "  [2] - Ordenacao Insercao (Insertion Sort)" << endl;
    cout << "  [3] - Ordenacao Selecao (Selection Sort)" << endl;
    cout << "  [4] - Ordenacao Contagem (Counting Sort)" << endl;
    cout << "  [5] - Ordenação Shell (Shell Sort)" << endl;
    cout << "  [6] - Ordenacao QuickSort" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  [7] - Sair" << endl;
    cout << "==========================================\n" << endl;
    cout << "Escolha uma opcao: ";
}

void exibirMenuTamanho() {
    cout << "\n==========================================" << endl;
    cout << "        SELECIONE O TAMANHO DO DADO" << endl;
    cout << "==========================================\n" << endl;
    cout << "  [1] - 1.000 dados" << endl;
    cout << "  [2] - 100.000 dados" << endl;
    cout << "  [3] - 1.000.000 dados" << endl;
    cout << "  [4] - Sair" << endl;
    cout << "==========================================\n" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    int opcaoTamanho, opcaoOrdenacao;
    const int tamanhos[] = {1000, 100000, 1000000};  // Tamanhos possíveis
    venda* vendas = nullptr;

    do {
        exibirMenuTamanho();
        cin >> opcaoTamanho;

        if (opcaoTamanho >= 1 && opcaoTamanho <= 3) {
            int tamanho = tamanhos[opcaoTamanho - 1];
            vendas = new venda[tamanho];  // Aloca dinamicamente

            do {

                exibirMenu();  // Exibe o menu atualizado
                cin >> opcaoOrdenacao;

                switch (opcaoOrdenacao) {
                    case 1:
                        TempoExecucao(bolha, vendas, tamanho, "Bolha");
                        break;

                    case 2:
                        TempoExecucao(insercao, vendas, tamanho, "Insercao");
                        break;

                    case 3:
                        TempoExecucao(selecao, vendas, tamanho, "Selecao");
                        break;

                    case 4:
                        TempoExecucao(contagem, vendas, tamanho, "Contagem");
                        break;

                    case 5:
                        TempoExecucao(shell, vendas, tamanho, "Shell");
                        break;

                    case 6:
                        aleatorio(vendas, tamanho);

                        TempoExecucao([](venda arr[], int tam) { quickSort(arr, 0, tam - 1); }, vendas, tamanho, "QuickSort");


                        break;

                    case 7:
                        cout << "\nSaindo do programa" << endl;
                        break;

                    default:
                        cout << "\n Opcao invalida! Tente novamente." << endl;
                        break;
                }
                cin.ignore();
                cin.get();
            } while (opcaoOrdenacao != 7);

            delete[] vendas;  // Libera a memória
        }

    } while (opcaoTamanho != 4);

    return 0;
}
