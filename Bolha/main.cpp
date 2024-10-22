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

void aleatorio(venda vendas[], int tamanho){
    srand((unsigned)time(0));
    for (int i = 0; i < tamanho; i++) {
        vendas[i].nome = "Produto_" + to_string(i + 1);
        vendas[i].qntVenda = rand() % 100 + 1;
        vendas[i].preco = (rand() % 10000) / 100.00;
        vendas[i].data = "20/10/2024";
    }


}

void bolha(venda vendas[], int tamanho) {
    int aux;
    aleatorio(vendas, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = i+1 ; j < tamanho; j++) {
            if (vendas[i].preco < vendas[j].preco) {
                aux = vendas[i].preco;
                vendas[i].preco = vendas[j].preco;
                vendas[j].preco = aux;
            }
        }
    }
    for (int i = 0; i < tamanho; i++) {
        cout << (i+1) << "- Nome: " << vendas[i].nome << endl;
        cout << "\t\tQuantidade: " << vendas[i].qntVenda << endl;
        cout << "\t\tPreco: " << vendas[i].preco << endl;
        cout << "\t\tData compra: " << vendas[i].data << endl;
        cout << endl;
    }
}

void insercao(venda vendas[], int tamanho){
    int posicao, aux;
    aleatorio(vendas, tamanho);
    for (int i = 0; i < tamanho; i++) {
        posicao = i;
        aux = vendas[i].preco;

        while (posicao > 0 && vendas[posicao-1].preco < aux){
            vendas[posicao].preco = vendas[posicao-1].preco;
            posicao--;
        }
        vendas[posicao].preco = aux;

    }
    for (int i = 0; i < tamanho; i++) {
        cout << (i+1) << "- Nome: " << vendas[i].nome << endl;
        cout << "\t\tQuantidade: " << vendas[i].qntVenda << endl;
        cout << "\t\tPreco: " << vendas[i].preco << endl;
        cout << "\t\tData compra: " << vendas[i].data << endl;
        cout << endl;
    }
}

void selecao(venda vendas[], int tamanho){
    int maior, aux;
    aleatorio(vendas, tamanho);
    for (int i = 0; i < tamanho-1; i++) {
        maior = i;
        for (int j = i+1; j < tamanho; ++j) {
            if (vendas[maior].preco < vendas[j].preco){
                maior = j;
            }

        }
        if (i != maior){
            aux = vendas[i].preco;
            vendas[i].preco = vendas[maior].preco;
            vendas[maior].preco = aux;
        }
    }
    for (int i = 0; i < tamanho; i++) {
        cout << (i+1) << "- Nome: " << vendas[i].nome << endl;
        cout << "\t\tQuantidade: " << vendas[i].qntVenda << endl;
        cout << "\t\tPreco: " << vendas[i].preco << endl;
        cout << "\t\tData compra: " << vendas[i].data << endl;
        cout << endl;
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

    // Preenchendo o array temporário com os itens ordenados em ordem CRESCENTE
    for (int i = tamanho - 1; i >= 0; i--) {
        int preco = static_cast<int>(vendas[i].preco * 100);
        output[--count[preco]] = vendas[i];  // Decrementa o valor de contagem
    }

    // Copiando os elementos de volta para o array original
    for (int i = 0; i < tamanho; i++) {
        vendas[i] = output[i];
    }

    // Liberando a memória alocada dinamicamente
    delete[] count;
    delete[] output;

    // Exibindo as vendas ordenadas
    for (int i = 0; i < tamanho; i++) {
        cout << (i + 1) << "- Nome: " << vendas[i].nome << endl;
        cout << "\t\tQuantidade: " << vendas[i].qntVenda << endl;
        cout << "\t\tPreço: " << vendas[i].preco << endl;
        cout << "\t\tData compra: " << vendas[i].data << endl;
        cout << endl;
    }
}


void shell(venda vendas[], int tamanho) {
    aleatorio(vendas, tamanho);
    // Loop para determinar o intervalo inicial e ir reduzindo o intervalo (gap)
    for (int intervalo = tamanho / 2; intervalo > 0; intervalo /= 2) {
        // Itera sobre os elementos, iniciando em "intervalo"
        for (int j = intervalo; j < tamanho; j++) {
            venda preco = vendas[j];
            int k;
            // Ordena comparando elementos que estão à "intervalo" de distância
            for (k = j; k >= intervalo && vendas[k - intervalo].preco < preco.preco; k -= intervalo) {
                vendas[k] = vendas[k - intervalo];
            }
            vendas[k] = preco;
        }
    }

    // Exibe os resultados em ordem decrescente
    for (int i = 0; i < tamanho; i++) {
        cout << (i + 1) << "- Nome: " << vendas[i].nome << endl;
        cout << "\t\tQuantidade: " << vendas[i].qntVenda << endl;
        cout << "\t\tPreco: " << vendas[i].preco << endl;
        cout << "\t\tData compra: " << vendas[i].data << endl;
        cout << endl;
    }
}

int partition(venda vendas[], int low, int high) {
    double pivot = vendas[high].preco; // Escolhe o último elemento como pivô
    int i = (low - 1); // Índice do menor elemento
    for (int j = low; j < high; j++) {
        // Se o preço do elemento atual for maior ou igual ao pivô
        if (vendas[j].preco >= pivot) {
            i++; // Incrementa o índice do menor elemento
            swap(vendas[i], vendas[j]);
        }
    }
    swap(vendas[i + 1], vendas[high]); // Coloca o pivô no lugar correto
    return (i + 1);
}

// Função quicksort
void quickSort(venda vendas[], int low, int high) {
    if (low < high) {
        int pi = partition(vendas, low, high); // Índice de partição
        quickSort(vendas, low, pi - 1); // Ordena a parte à esquerda do pivô
        quickSort(vendas, pi + 1, high); // Ordena a parte à direita do pivô
    }

}

void TempoExecucao(void (*func)(venda[], int), venda arr[], int tamanho, const string& nomeMetodo) {
    auto inicio = chrono::high_resolution_clock::now();

    func(arr, tamanho);  // Chama a função de ordenação

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim - inicio;

    cout << "Modo " << nomeMetodo << " executado em: " << duracao.count() << " milissegundos" << endl;
}

void exibirMenu() {
    cout << "\n==========================================" << endl;
    cout << "         SELECIONE UM METODO DE ORDENACAO" << endl;
    cout << "==========================================\n" << endl;
    cout << "  [1] - Ordenação Bolha (Bubble Sort)" << endl;
    cout << "  [2] - Ordenação Inserção (Insertion Sort)" << endl;
    cout << "  [3] - Ordenação Seleção (Selection Sort)" << endl;
    cout << "  [4] - Ordenação Contagem (Counting Sort)" << endl;
    cout << "  [5] - Ordenação Shell (Shell Sort)" << endl;
    cout << "  [6] - QuickSort" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  [7] - Sair" << endl;
    cout << "==========================================\n" << endl;
    cout << "Escolha uma opcao: ";
}


int main() {
    int tamanho =1000;
    venda vendas[tamanho];
    int opcao;

    do {

        exibirMenu();  // Exibe o menu atualizado
        cin >> opcao;

        switch (opcao) {
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

                for (int i = 0; i < tamanho; ++i) {
                    cout << (i + 1) << "- Nome: " << vendas[i].nome << endl;
                    cout << "\tQuantidade: " << vendas[i].qntVenda << endl;
                    cout << "\tPreco: " << vendas[i].preco << endl;
                    cout << "\tData compra: " << vendas[i].data << endl;
                    cout << endl;
                }

                TempoExecucao([](venda arr[], int tam) { quickSort(arr, 0, tam - 1); }, vendas, tamanho, "QuickSort");

                break;

            case 7:
                cout << "\n>> Saindo do programa" << endl;
                break;

            default:
                cout << "\n Opcao invalida! Tente novamente." << endl;
                break;
        }
        cin.ignore();
        cin.get();
    } while (opcao != 7);

    return 0;
}

