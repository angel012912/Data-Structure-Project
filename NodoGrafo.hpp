/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main GraphNode data structure class named "NodoGrafo"
*/

#include "Arco.hpp"
#include "ListaSimple.hpp"

template <typename T>
class NodoGrafo{
    T valor;
    ListaSimple<Arco<T>*> * arcos;
    bool procesado;
    public:
        T getValor(){return this->valor;}
        ListaSimple<Arco<T>*> * getArcos(){return this->arcos;}
        bool getProcesado(){return this->procesado;}
        void setProcesado(bool procesado){this->procesado=procesado;}
        NodoGrafo(T valor){
            this->valor=valor;
            this->arcos=new ListaSimple<Arco<T>*>();
            this->procesado=false;
        }
};