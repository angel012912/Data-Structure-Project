/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that defines the main Graph data structure class named "Grafo"
*/

#include "NodoGrafo.hpp"
#include "Fila.hpp"
#include "Pila.hpp"
#include <vector>
#include <fstream>

template <typename T>
class Grafo{
    int tam;
    ListaSimple<NodoGrafo<T> *> * nodos;
    public:
        Grafo(){
            this->tam=0;
            this->nodos=new ListaSimple<NodoGrafo<T>*>();
        }
        
        int getTam(){return this->tam;}
        ListaSimple<NodoGrafo<T> *> * getNodos(){return this->nodos;}

        NodoGrafo<T> * buscarNodoGrafo(T valor){
            NodoT<NodoGrafo<T>*> * actual=this->nodos->getHead();
            while(actual){
                //Busqueda del valor dentro de los nodos
                if(actual->getDato()->getValor()==valor)
                    return actual->getDato();
                actual=actual->getSiguiente();
            }
            return nullptr;            
        }    

        void insertarNodoGrafo(T valor){
            //Si el nodo no existe
            if(!this->buscarNodoGrafo(valor)){
                this->nodos->agregarInicio(new NodoGrafo<T>(valor));
                this->tam++;
            }else
                cout<<"Nodo existente"<<endl;
        }

        void agregarArco(T valorNodoOrigen, T valorNodoDestino, int peso){
            //Validar la existencia de los nodos origen y destino
            NodoGrafo<T> * origen=this->buscarNodoGrafo(valorNodoOrigen);
            NodoGrafo<T> * destino=this->buscarNodoGrafo(valorNodoDestino);
            if(origen&&destino)
                origen->getArcos()->agregarInicio(new Arco<T>(valorNodoDestino,peso));
            else
                cout<<"Ambos nodos tanto origen como destino deben existir"<<endl;
        }

        void imprimirGrafo(){
            NodoT<NodoGrafo<T>*> * nodo=this->nodos->getHead();
            //Recorrer la lista de nodos
            while(nodo){
                cout<<"Nodo:"<< nodo->getDato()->getValor()<<" \n";
                NodoT<Arco<T>*> * arco = nodo->getDato()->getArcos()->getHead();
                //Recorrer la lista de arcos de cada nodo
                while(arco){
                    cout<<"->"<<arco->getDato()->getValorNodoDestino()<<":"<<arco->getDato()->getPeso()<<" ";
                    arco=arco->getSiguiente();
                }
                cout<<endl;
                nodo=nodo->getSiguiente();                
            }
            cout<<endl;
        }

        void BreadthFirst(NodoGrafo<T> * nodoG){
            //Crear la fila de control
            Fila<NodoGrafo<T> *> * fila = new Fila<NodoGrafo<T> *>();
            //Inicializar procesado de cada NodoGrafo
            NodoT<NodoGrafo<T>*> * actual=this->nodos->getHead();
            if(actual){
                while(actual){ // --> O(n)
                    actual->getDato()->setProcesado(false);
                    actual=actual->getSiguiente();
                }
                //Metemos el NodoGrafo por el que inicia el recorrido
                nodoG->setProcesado(true);
                fila->push(nodoG);
                while(fila->front()){ // --> O(n^2)
                    NodoGrafo<T> * aux = fila->pop()->getDato();
                    //Imprimo el valor del nodoGrafo
                    cout<< aux->getValor()<<" ";
                    //Checar las conexiones sin procesar
                    NodoT<Arco<T>*> * con=aux->getArcos()->getHead();
                    while(con){  // --> O(n)
                        NodoGrafo<T> * vecino = this->buscarNodoGrafo(con->getDato()->getValorNodoDestino());
                        if(!vecino->getProcesado()){
                            vecino->setProcesado(true);
                            //Meter a la fila
                            fila->push(vecino);
                        }
                        con=con->getSiguiente();
                    }
                }
                cout<<endl;

            }else{
                cout<<"Grafo vacio"<<endl;
            }
        }
        vector<T>  DepthFirst(NodoGrafo<T> * inicio){ //O(n^2)
            //Crear el vector donde se guardaran los valores a desplegar
            vector<T> valores;
            //Validar que el Grafo tenga nodos
            if(this->nodos->getHead()){
                //Validar que el nodo por el que se inicia esté dentro del Grafo
                NodoGrafo<T> * ini = buscarNodoGrafo(inicio->getValor());
                if(ini){
                    //Crear la fila de control
                    Pila<NodoGrafo<T> *> * pila = new Pila<NodoGrafo<T> *>();
                    //Meter el nodo inicial dentro de la pila
                    pila->push(ini);
                    while(pila->top()){  //O(n^2)
                        //Sacar el nodo
                        NodoGrafo<T> * act = pila->pop()->getDato();
                        //Procesarlo
                        //Meter las conexiones del nodo a la pila
                        NodoT<Arco<T> * > * conexion = act->getArcos()->getHead();
                        while(conexion){ //O(n)
                            NodoGrafo<T> * vecino = this->buscarNodoGrafo(conexion->getDato()->getValorNodoDestino());
                            if(!vecino->getProcesado()){
                                //Meterlo a la fila
                                pila->push(vecino);
                            }
                            //Actualizar el valor de conexion
                            conexion = conexion->getSiguiente();
                        }
                        //Verificar que el nodo que se sacó no esté procesado
                        if(!act->getProcesado()){
                            
                            //Cambiar el estatus del nodo a procesado
                            act -> setProcesado(true);
                            //Imprimir el valor del nodo procesado
                            valores.push_back(act->getValor());
                        }
                    }
                    cout<<endl;
                }else //Desplegar mensaje de error
                    cout<<"El nodo que se ingreso no se encontró dentro del Grafo"<<endl;    
            }else //Desplegar mensaje de error
                cout<<"El Grafo no tiene nodos ingresados"<<endl;
            return valores;
            }
};