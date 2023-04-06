/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main Arc data structure class named "Arco"
*/

template <typename T>
//Representa el arco de un nodo origen a un nodo destino con su peso
class Arco{
    T valorNodoDestino;
    int peso;
    public:
        int getPeso(){return this->peso;}
        T getValorNodoDestino(){return this->valorNodoDestino;}
        //Agregar metodos sets
        Arco(T valorNodoDestino,int peso){
            this->valorNodoDestino=valorNodoDestino;
            this->peso=peso;
        }
        void agregarPeso(){this->peso++;}
};