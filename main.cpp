/*
 * @author: Gabriel Magro, Jesiel Pfeifer, Joao Hartmann, Matheus Vargas.
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Veiculo {
private:
    char tipo;
    float peso;
public:
    Veiculo(char tipo, float peso) {
        this->tipo = tipo;
        this->peso = peso;
    }

    float getPeso() {
        return this->peso;
    }

    char getTipo() {
        return this->tipo;
    }
};

class Balsa {
private:
    vector<Veiculo *> veiculos;
    int capMax;
    float capTon;
    float pesoAtual;
    float qtdAtual;
    float pesoTotal;

public:
    Balsa(int capMax, float capTon) {
        this->capMax = capMax;
        this->capTon = capTon;
    }

    bool estouro(float vPeso) {
        string continua;
        if ((this->pesoAtual + vPeso) > this->capTon) {
            cout << "=================================================================="<<endl;
            cout << "\nLimite de peso atingido!"<<endl;
            cout << "A seguradora nao cobre os custos de um eventual sinistro.";
            cout << " Se deseja continuar a responsabilidade sera toda do balseiro";
            cout << "este tera de arcar com eventuais custos.\n";
            do {
                cout << "Deseja continuar? [S] ou [N]: ";
                cout << "=================================================================="<<endl;
                cin >> continua;
            } while (continua != "s" && continua != "S" && continua != "n" && continua != "N");

            if (continua == "s" || continua == "S") {
                return true;
            } else {
                return false;
            }

        } else {
            return true;
        }
    }

    void adicionaVeiculo(Veiculo *v) {
        if (estouro(v->getPeso())) {
            this->veiculos.push_back(v);
            this->qtdAtual += 1;
            this->pesoAtual += v->getPeso();
        } else {
            cout << "Veiculo nao adcionado\n" << endl;;
        }
        cout << endl;
        system("pause");
    }

    int getCapMax() {
        return capMax;
    }

    int getQtdAtual() {
        return qtdAtual;
    }

    void limpaVetor() {
        while (!(this->veiculos.empty())) {
            Veiculo *v;
            v = veiculos.back();
            veiculos.pop_back();
            delete v;
        }
        this->qtdAtual = 0;
        this->pesoAtual = 0;
    }

    void geraRelatorio() {
        system("cls");
        cout << "==================RELATORIO=================="<<endl;
        cout << "Veiculo     Quantidade          Peso(kg)\n";
        cout << "Carro       " << this->retornaCarro() << "\t\t\t" << this->retornaPesoCarro() * 1000 << endl;
        cout << "Moto        " << this->retornaMoto() << "\t\t\t" << this->retornaPesoMoto() * 1000 << endl;
        cout << "Van         " << this->retornaVan() << "\t\t\t" << this->retornaPesoVan() * 1000 << endl;
        cout << "Total       " << this->getQtdAtual() << "\t\t\t" << this->retornaPesoTotal() << endl;
        cout << "Maximo      " << this->capMax << "\t\t\t" << this->capTon*1000 << endl;
        cout << "Saldo       " << this->capMax - this->qtdAtual << "\t\t\t" << (this->capTon*1000) - this->retornaPesoTotal()<< endl;
        cout << "============================================="<<endl;
        cout << endl;
        system("pause");
    }

    int retornaMoto() {
        int m = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'M') {
                m++;
            }
        }
        return m;
    }

    float retornaPesoMoto() {
        float m = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'M') {
                m += veiculos[i]->getPeso();
            }
        }
        return m;
    }

    int retornaCarro() {
        int c = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'C') {
                c++;
            }
        }
        return c;
    }

    float retornaPesoCarro() {
        float c = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'C') {
                c += veiculos[i]->getPeso();
            }
        }
        return c;
    }

    int retornaVan() {
        int v = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'V') {
                v++;
            }
        }
        return v;
    }

    float retornaPesoVan() {
        int v = 0;
        for (int i = 0; i < this->veiculos.size(); i++) {
            if (veiculos[i]->getTipo() == 'V') {
                v += veiculos[i]->getPeso();
            }
        }
        return v;
    }
    float retornaPesoTotal() {
        this->pesoTotal = (this->retornaPesoCarro() + this->retornaPesoMoto() + this->retornaPesoVan()) * 1000;
        return this->pesoTotal;
    }
};


int main() {
    int capMax;
    float capTon;
    do {
        cout << "============================================="<<endl;
        cout << "Informe a capacidade maxima de veiculos: ";
        cin >> capMax;

        cout << "Informe a capacidade maxima de toneladas: ";
        cin >> capTon;
        cout << "============================================="<<endl;

    } while (capMax <= 0 && capTon <= 0);

    Balsa *balsa = new Balsa(capMax, capTon);

    while (1) {
        int opc;
        char tipo;
        float peso;

        system("cls");

        cout << "====================MENU====================="<<endl;
        cout << "\n";
        cout << "1 - Embarcar veiculo" << endl;
        cout << "2 - Gerar relatorio" << endl;
        cout << "3 - Desembarcar todos" << endl;
        cout << "4 - Sair" << endl;
        cout << "\n";
        cout << "=============================================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opc;

        switch (opc) {
        case 1:
            system("cls");
            cout << "============================================="<<endl;
            if (balsa->getCapMax() > balsa->getQtdAtual()) {
                do {
                    cout << "Informe o tipo veiculo ('C', 'M', 'V')" << endl;
                    cin >> tipo;
                    if (tipo > 90)
                        tipo = tipo - 32;
                } while (tipo != 'C' && tipo != 'M' && tipo != 'V');
                cout << "============================================="<<endl;
                cout << "Informe o peso do veiculo" << endl;
                cin >> peso;
                Veiculo *v = new Veiculo(tipo, peso);
                balsa->adicionaVeiculo(v);
                cout << "============================================="<<endl;
            } else {
                cout << "\n\nCapacidade maxima atingida.";
                cout << endl;
                system("pause");
            }
            break;
        case 2:
            balsa->geraRelatorio();
            break;
        case 3:
            balsa->limpaVetor();
            cout << "============================================="<<endl;
            cout << "Veiculos desembarcados!";
            cout << "============================================="<<endl;
            cout << endl;
            system("pause");
            break;
        case 4:
            return 0;
        }
        system("cls");
    }

    return 0;
}
