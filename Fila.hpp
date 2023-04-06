/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main Queue data structure class named "Fila"
*/

#include "ListaCircular.hpp"

template <typename T>
class Fila{ //Queue o Cola
    ListaCircular<T> * fila;
    public:
        Fila(){
            this->fila=new ListaCircular<T>();
        }
        void push(T valor){
            this->fila->agregarFin(valor);
        }

        NodoT<T> * pop(){
            return this->fila->eliminarInicio();
        }       

        NodoT<T> * front(){
           if(this->fila->getLast())
                return this->fila->getLast()->getSiguiente();
            return nullptr; 
        }

        void imprimirFila(){
            this->fila->imprimirLista();
        }



};