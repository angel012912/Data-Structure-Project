/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main Simple Circular List  data structure class named "ListaCircular"
*/

#include "NodoT.hpp"

template <typename T>
class ListaCircular{
    NodoT<T> * last;
    int tam;
    //setters y getters
    public: 
    NodoT<T> * getLast(){return this->last;}
    void setLast(NodoT<T> * last){this->last=last;}
    ListaCircular(){
        this->last=nullptr;
        this->tam=0;
    }

    void agregarInicio(T dato){ //O(1)
        if(this->last){//Lista circular tiene nodos
            //Crea un nuevo nodo y lo apunta al head (last->getSiguiente)
            NodoT<T> * nuevo = new NodoT<T>(dato,this->last->getSiguiente());
            //Actualizr el apuntador de last y conectarlo al nuevo nodo
            this->last->setSiguiente(nuevo);
        }else{//Lista vacia
            NodoT<T> * nuevo = new NodoT<T>(dato,nullptr);//Creando el nuevo nodo
            nuevo->setSiguiente(nuevo);//Como solo hay un nodo el apuntador siguiente será asi mismo
            this->last=nuevo; //El nuevo nodo será el último y el primero al mismo tiempo            
        }
        this->tam++;
    }

    void agregarFin(T dato){
        if(this->last){//Lista circular tiene nodos
            //Crea un nuevo nodo y lo apunta al head (last->getSiguiente)
            NodoT<T> * nuevo = new NodoT<T>(dato,this->last->getSiguiente());
            //Actualizr el apuntador de last y conectarlo al nuevo nodo
            this->last->setSiguiente(nuevo);
            this->last=nuevo;
        }else{//Lista vacia
            NodoT<T> * nuevo = new NodoT<T>(dato,nullptr);//Creando el nuevo nodo
            nuevo->setSiguiente(nuevo);//Como solo hay un nodo el apuntador siguiente será asi mismo
            this->last=nuevo; //El nuevo nodo será el último y el primero al mismo tiempo            
        }
        this->tam++;
    }

    void imprimirLista(){
        if(this->last){
            NodoT<T> * nodo = this->last->getSiguiente();
            do{
                cout<<nodo->getDato()<<" ";
                nodo = nodo->getSiguiente();
            }while(nodo!=this->last->getSiguiente());
        }
        cout<<endl;
    }

    NodoT<T> * eliminarInicio(){
        if(this->last){
            NodoT<T> * nodoInicial = this->last->getSiguiente();
            if(this->tam==1)
                this->last=nullptr;
            else    
                this->last->setSiguiente(nodoInicial->getSiguiente());
            this->tam--;
            //opc
            nodoInicial->setSiguiente(nullptr);
            return nodoInicial;
        }
        return nullptr;
    }

};