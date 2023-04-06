/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main Stack data structure class named "Pila"
*/

#include "ListaSimple.hpp"

template <typename T>
class Pila{ //Stack
    ListaSimple<T> * pila;
    public:
        Pila(){
            this->pila=new ListaSimple<T>();
        }
        void push(T valor){
            this->pila->agregarInicio(valor);
        }

        NodoT<T> * pop(){
            return this->pila->eliminarInicio();
        }       

        NodoT<T> * top(){
            return this->pila->getHead(); 
        }

        void imprimirPila(){
            this->pila->imprimirLista();
        }

};