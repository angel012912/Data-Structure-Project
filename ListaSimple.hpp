/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main SimpleLinkedList data structure class named "ListaSimple"
*/

#ifndef LISTASIMPLE_C
#define LISTASIMPLE_C
#include "NodoT.hpp"
template <typename T>
class ListaSimple{
    //Atributos
    NodoT<T> * head;
    int tam;
    public:
        NodoT<T> * getHead(){return this->head;}
        ListaSimple(){
            this->head=nullptr;
            this->tam=0;
        }
        void agregarInicio(T valor){
            //Crear el nuevo nodo y actualizar la referencia 
            NodoT<T> * nuevo= new NodoT<T>(valor,this->head);
            //Actualizar el head de la lista al nuevo nodo
            this->head=nuevo;
            //Actualizar el tamaño
            this->tam++;
        }

        void agregarFin(T valor){
            //Crear el nuevo nodo
            NodoT<T> * nuevo= new NodoT<T>(valor,nullptr);
            //Verificar el caso si la lista esta vacio o tiene valor
            if(this->head){ //la lista tiene valores
                NodoT<T> * nodo=this->head;
                //Encontrar el último nodo
                while(nodo->getSiguiente())
                    nodo=nodo->getSiguiente();
                nodo->setSiguiente(nuevo); //Actualizar el ultimo siguiente con el nuevo
            }else{//La lista esta vacia
                //El head es igual al nuevo nodo
                this->head=nuevo;  
            }
            //Actualizat el tamaño
            this->tam++;
        }

        void imprimirLista(){
            NodoT<T> * nodo=this->head;
            while(nodo){
                cout<<nodo->getDato()<<" ";
                nodo=nodo->getSiguiente();
            }
            cout<<endl;            
        }

        NodoT<T> * buscarNodo(T dato){
            NodoT<T> * nodo=this->head;
            while(nodo){
                //Busqueda del valor dentro de los nodos
                if(nodo->getDato()==dato)
                    return nodo;
                nodo=nodo->getSiguiente();
            }
            return nullptr; //No encontre el valor que buscas  
        } 

        //Eliminar un nodo al inicio de la lista
        NodoT<T> * eliminarInicio(){
            if(this->head){
                NodoT<T> * eliminado=this->head; //Guardo la direccion del elemento a eliminar
                this->head=this->head->getSiguiente(); //Actualizar el head
                this->tam--;
                return eliminado;
            }
            return nullptr;            
        }  
};
#endif