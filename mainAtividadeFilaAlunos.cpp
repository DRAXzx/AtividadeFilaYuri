#include <iostream>
using namespace std;

struct Conteudo {
    string nome;
    Conteudo* next;

    Conteudo(string nome, Conteudo* next = NULL) : nome(nome), next(next) {}
};

struct Disciplina {
    string nome;
    int quantidadeCreditos;
    Conteudo* listaConteudos;
    Disciplina* next;

    Disciplina(string nome, int quantidadeCreditos, Conteudo* listaConteudos = NULL, Disciplina* next = NULL)
        : nome(nome), quantidadeCreditos(quantidadeCreditos), listaConteudos(listaConteudos), next(next) {}
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    Disciplina* listaDisciplina;

    Aluno(string nome, string cpf, int idade, string matricula, Disciplina* listaDisciplina = NULL)
        : nome(nome), cpf(cpf), idade(idade), matricula(matricula), listaDisciplina(listaDisciplina) {}
};

struct No {
    Aluno aluno;
    No* next;

    No(Aluno aluno, No* next = NULL) : aluno(aluno), next(next) {}
};

struct Fila {
    No* inicio;
    No* fim;

    Fila() : inicio(NULL), fim(NULL) {}
};

bool isEmpty(Fila &fila) {
    return (fila.inicio == NULL && fila.fim == NULL);
}

void Enqueue(Fila &fila, Aluno aluno) {
    No* novoAluno = new No(aluno);

    if (isEmpty(fila)) {
        fila.inicio = novoAluno;
        fila.fim = novoAluno;
    } else {
        fila.fim->next = novoAluno;
        fila.fim = novoAluno;
    }
}

void Dequeue(Fila &fila) {
    if (isEmpty(fila)) {
        cout << "Fila vazia. Nenhum aluno a ser removido." << endl;
    } else {
        No* temp = fila.inicio;
        fila.inicio = fila.inicio->next;
        delete temp;
    }
}
int Size(Fila &fila) {
    No* temp = fila.inicio;
    int contador = 0;
    while (temp != NULL) {
        contador++;
        temp = temp->next;
    }
    return contador;
}

Aluno Front(Fila &fila) {
    if (isEmpty(fila)) {
        cout << "Fila vazia. Nenhum aluno na frente." << endl;
        return Aluno("", "", 0, "");
    } else {
        return fila.inicio->aluno;
    }
}

void printAluno(Aluno aluno) {
    cout << "Nome: " << aluno.nome << endl;
    cout << "CPF: " << aluno.cpf << endl;
    cout << "Idade: " << aluno.idade << endl;
    cout << "Matrícula: " << aluno.matricula << endl;
    cout << "Disciplinas: " << endl;
    Disciplina* disciplina = aluno.listaDisciplina;
    while (disciplina != NULL) {
        cout << "  Nome da disciplina: " << disciplina->nome << endl;
        cout << "  Créditos: " << disciplina->quantidadeCreditos << endl;
        cout << "  Conteúdos: ";
        Conteudo* conteudo = disciplina->listaConteudos;
        while (conteudo != NULL) {
            cout << conteudo->nome << " ";
            conteudo = conteudo->next;
        }
        cout << endl;
        disciplina = disciplina->next;
    }
    cout << "*******************************" << endl;
}

void addDisciplina(Aluno &aluno, Disciplina disciplina) {
    if (aluno.listaDisciplina == NULL) {
        aluno.listaDisciplina = new Disciplina(disciplina);
    } else {
        Disciplina *temp = aluno.listaDisciplina;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new Disciplina(disciplina);
    }
}

void addConteudo(Disciplina &disciplina, string nomeConteudo) {
    if (disciplina.listaConteudos == NULL) {
        disciplina.listaConteudos = new Conteudo(nomeConteudo);
    } else {
        Conteudo *temp = disciplina.listaConteudos;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new Conteudo(nomeConteudo);
    }
}

void printConteudos(Disciplina &disciplina) {
    cout << "Conteúdos da disciplina " << disciplina.nome << ": " << endl;
    Conteudo *temp = disciplina.listaConteudos;
    while (temp != NULL) {
        cout << temp->nome << endl;
        temp = temp->next;
    }
}

void removeDisciplina(Aluno &aluno, string nomeDisciplina) {
    if (aluno.listaDisciplina == NULL) {
        cout << "Lista de disciplinas vazia" << endl;
    } else {
        Disciplina *atual = aluno.listaDisciplina;
        Disciplina *anterior = NULL;

        while (atual != NULL && atual->nome != nomeDisciplina) {
            anterior = atual;
            atual = atual->next;
        }

        if (atual == NULL) {
            cout << "Disciplina não encontrada" << endl;
        } else {
            if (anterior == NULL) {
                aluno.listaDisciplina = atual->next;
            } else {
                anterior->next = atual->next;
            }
            delete atual;
        }
    }
}

void removeConteudo(Disciplina &disciplina, string nomeConteudo) {
    if (disciplina.listaConteudos == NULL) {
        cout << "Lista de conteúdos vazia" << endl;
    } else {
        Conteudo *atual = disciplina.listaConteudos;
        Conteudo *anterior = NULL;

        while (atual != NULL && atual->nome != nomeConteudo) {
            anterior = atual;
            atual = atual->next;
        }

        if (atual == NULL) {
            cout << "Conteúdo não encontrado" << endl;
        } else {
            if (anterior == NULL) {
                disciplina.listaConteudos = atual->next;
            } else {
                anterior->next = atual->next;
            }
            delete atual;
        }
    }
}

void printTodosAlunos(Fila &fila) {
    No *temp = fila.inicio;
    while (temp != NULL) {
        printAluno(temp->aluno);
        temp = temp->next;
    }
}
void printDisciplina(Aluno &aluno) {
    if (aluno.listaDisciplina == NULL) {
        cout << "Disciplina vazia" << endl;
    } else {
        cout << "Disciplinas do aluno " << aluno.nome << ":" << endl;
        Disciplina *temp = aluno.listaDisciplina;
        while (temp != NULL) {
            cout << temp->nome << endl;
            temp = temp->next;
        }
    }
}

int main() {
    Fila fila;

    Disciplina calculo("calculo", 3, new Conteudo("formatos", new Conteudo("quadrados")));
    Disciplina estrutura("estrutura", 4, new Conteudo("filas", new Conteudo("ponteiros")));
    Disciplina POO("POO", 3, new Conteudo("classes", new Conteudo("herança")));

    Aluno aluno1("Arione", "125.557.244-61", 20, "001", &calculo);
    Aluno aluno2("Pedro", "542.451.225-50", 18, "002", &estrutura);
    Aluno aluno3("marcos", "424.102.325-30",25,"003", &calculo);
    Aluno aluno4("paulo", "365.561.856-36",30,"004", &estrutura);
    Aluno aluno5("joao", "540.268.125-12",22,"005", &POO);
    Enqueue(fila, aluno1);
    Enqueue(fila, aluno2);
    Enqueue(fila, aluno3);
    Enqueue(fila, aluno4);
    Enqueue(fila, aluno5);


    cout << "Tamanho da fila: " << Size(fila) << endl;
    cout << "Aluno na frente da fila: " << endl;
    printAluno(Front(fila));

    Dequeue(fila);

    cout << "Tamanho da fila após remoção: " << Size(fila) << endl;

    cout << "Aluno na frente da fila: " << endl;
    printAluno(Front(fila));

    addDisciplina(aluno1, POO);
    printDisciplina(aluno1);
    cout << endl;

    addConteudo(POO, "encapsulamento");
    addConteudo(estrutura, "arvore");

    printConteudos(calculo);
    printConteudos(estrutura);
    printConteudos(POO);

    return 0;
}
