#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std;

// Declaração dos métodos
string invertSequence(string sequence);
void printSet(unordered_set<int> control);

int main() 
{
    using namespace std::chrono;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    /*
        Conjunto que irá guardar os números únicos que somados ao seu inverso resultam em um número ímpar.
        unordered_set é um container que guarda elementos únicos de maneira desordenada

        https://www.cplusplus.com/reference/unordered_set/unordered_set/#:~:text=Unordered%20sets%20are%20containers%20that,key%2C%20that%20identifies%20it%20uniquely.
    */
    unordered_set<int> control;
    
    for (int i = 0; i < 1000000; i++)
    {
        
        // Convertendo o número da iteração para string
        string number = std::to_string(i);
        // Invertendo a string
        string invertedSequence = invertSequence(number);
        // Convertendo a string para número novamente
        int invertedNumber = stoi(invertedSequence);
        // int invertedNumber = stoi(invertSequence(number)); <- Poderia ser feito direto desta forma também
        // Somando os valores do número da iteração com o seu invertido
        int sumValue = i + invertedNumber;
        // A soma será válida se for ímpar e menor que um milhão.
        bool sumIsValid = sumValue % 2 != 0 && sumValue < 1000000;
        /*
            Condições:
                control.count(): verifica quantas ocorrências do valor passado no parâmetro existem no set. Como só podem o
                correr no máximo uma vez, o método retora 1 ou 0;
                
                O inverso do número não pode existir no set, pois não podemos calcular duas vezes o mesmo resultado, ex: 12 e 21.
                O número não pode terminar com 0, pois 99910 teria inverso 1999.
                Por final, a soma deve ser ímpar.

                Note que, quando um número entrar pela primeira vez no set, quando a iteração passar sobre o seu invertido,
                a lógica retornará false e não adicionará no set.
        */
        if (!control.count(invertedNumber) && number.at(number.length() - 1) != '0' && sumIsValid) {
            control.insert(i);
        }
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    printSet(control);

    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    duration<double, std::milli> time_span1 = t2 - t1;
    duration<double, std::milli> time_span2 = t3 - t2;
    duration<double, std::milli> time_span = t3 - t1;

    std::cout << "Calculation time: " << time_span1.count() << " milliseconds." << endl;
    std::cout << "Print time: " << time_span2.count() << " milliseconds." << endl;
    std::cout << "Total time: " << time_span.count() << " milliseconds." << endl;

    return 0;
}

void printSet(unordered_set<int> control) {
    for (int const& element : control)
    {
        string invertedSequence = invertSequence(to_string(element));
        int invertedNumber = stoi(invertedSequence);
        printf("%d + %d = %d \n", element, invertedNumber, (element + invertedNumber));
    }
}

string invertSequence(string sequence) 
{
    reverse(sequence.begin(), sequence.end());
    return sequence;
}
