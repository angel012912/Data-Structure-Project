/*
Author: Jose Angel Garcia Gomez
Date: 23/11/2021
Description: Program that reads a text file with a server failure log and creates a graph with the ips that are in the file, in addition to being able to obtain the ips that generate the most failures and the ones that receive the most failures.
*/

#include "Grafo.hpp"
#include <vector>


void obtenerIpRecibe(Grafo<string> * Ips){ // --> O(max(n^3, n^3, n, n)) --> O(n^3)
    //Declarar vetor de IPdestino
    vector<string> IpsDest;
    //Buscar todas las ip destino
    NodoT<NodoGrafo<string>*> * actual =Ips->getNodos()->getHead();
    while(actual){ //O(n^3)
        NodoT<Arco<string> *>* conexion = actual->getDato()->getArcos()->getHead();
        while(conexion){ //O(n^2)
            string IpDestino = conexion->getDato()->getValorNodoDestino();
            bool enc=false;
            for(int i = 0; i<IpsDest.size(); i++){ //O(n)
                //Verificar que no se repita
                if(IpsDest[i] == IpDestino)
                    enc = true;
            }
            //Agregar todas las IP a un vector verificando que no se repita el valor dentro del vector. 
            if(!enc)
                IpsDest.push_back(IpDestino);
            conexion = conexion->getSiguiente();
        }
        //Actualizar el apuntador para ir iterando los nodos
        actual = actual->getSiguiente();
    }
    vector<int> Contadores;  
    //Por cada ip destino en el vector, sumar al contador el peso de sus arcos
    for(int a = 0; a<IpsDest.size(); a++){ // -->O(n^3)
        //Inicializar el contador en 0
        int cont = 0;
        //Iterar los nodos que estan en el grafo
        NodoT<NodoGrafo<string>*> * actual = Ips->getNodos()->getHead();
        while(actual){ // -->O(n^2)
            //Iterar los arcos de cada nodo
            NodoT<Arco<string> *>* conexion = actual->getDato()->getArcos()->getHead();
            while(conexion){  //-->O(n)
                //Se obtiene el valor del nodo destino
                string IpDestino = conexion->getDato()->getValorNodoDestino();
                //Si encuentra el ip destino en los arco del nodo, sumar el peso del arco que lo contiene al contador
                if(IpDestino == IpsDest[a])
                    cont = cont + conexion->getDato()->getPeso();        
                //Actualizar el apuntador de la lista de arcos
                conexion = conexion->getSiguiente();
            }
            //Actualizar el apuntador de los nodos
            actual = actual->getSiguiente();
        }
        //Agregar el contador a un vector
        Contadores.push_back(cont);
    }
    //Buscar en el vector de contadores el valor mayor
    int mayor =0;
    for(int b = 0; b<Contadores.size(); b++) // --> O(n) 
        if(mayor<Contadores[b])
            mayor = Contadores[b];
    //Buscar las posiciones que tengan ese valor
    cout<<"     ---- Ip(s) que mas fallas recibe --- "<<endl;
    for(int c = 0; c<Contadores.size(); c++) //--> O(n)
        //Imprimir 
        if(mayor == Contadores[c])
            cout<<"Ip: "<<IpsDest[c]<<" con: "<<mayor<<" fallas recibidas"<<endl;
}

void obtenerIpGenera(Grafo<string> * Ips){ // --> O(max(n,n,n^2)) --> O(n^2)
    //Se declaran los vectores que van a contener la lista de ips origen y los contadores
    vector<string> origen;
    vector<int> acum;
    //Se iteran todos los nodos dentro del grafo
    NodoT<NodoGrafo<string> *> * actual = Ips->getNodos()->getHead();
    while(actual){ // --> O(n^2)
        //Se guardan todos los ips dentro del vector correspondiente
        origen.push_back(actual->getDato()->getValor());
        //Si inicializa un contador en 0
        int c = 0;
        //Se itera los arcos de cada ip
        NodoT<Arco<string> *> * conexion = actual->getDato()->getArcos()->getHead();
        while(conexion){ // --> O(n)
            //Se le suma al contador el valor del peso de cada uno de sus arcos
            c += conexion->getDato()->getPeso();
            //Se actualiza el apuntador
            conexion = conexion->getSiguiente();
        }
        //Ya que se tiene el contador de cada ip se agrega dicho contador al vector correspondiente
        acum.push_back(c);
        //Se actualiza el apuntador de los nodos dentro del grafo
        actual = actual->getSiguiente();
    }
    //Si inicializa un valor en 0 para que sea el auxiliar que nos ayude a encontrar el valor mayor
    int mayor = 0;
    //Buscar el valor mayor dentro del vector de contadores de cada ip
    for(int i = 0; i < acum.size(); i++) // --> O(n)
        //Si el valor que esta en la iteracion es mayor al auxiliar se le asigna el valor de la iteracion al auxiliar 
        if(mayor<acum[i])
            mayor = acum[i];
    //Imprime todas las ip que tengan el valor del auxiliar
    cout<<"     ---- Ip(s) que mas fallas genera --- "<<endl;
    //Busca dentro del vector las posiciones que tienen ese valor
    for(int a = 0; a < acum.size();a++) // --> O(n)
        //Si tiene el mismo valor, imprime la ip que tiene la misma posicion en el vector de ips
        if(mayor == acum[a])
            cout<<"Ip: "<<origen[a]<<" con: "<<mayor<<" fallas generadas"<<endl;
}


int main(){
    Grafo<string> * Ips=new Grafo<string>();  
    //Lectura de la bitacora 
    ifstream datos;
    datos.open("bitacoraCompleta1.txt");
    string IpOrigen, IpDestino;
    string basura;
    while(datos.good()){
        //Obtener los ip origen y destino del archivo
        getline(datos, basura, ' ');
        getline(datos, basura, ' ');
        getline(datos, basura, ' ');
        getline(datos, IpOrigen, ' ');
        getline(datos, IpDestino, ' ');
        getline(datos, basura);
        //Validar la existencia de los nodos origen y destino
        NodoGrafo<string> * origen=Ips->buscarNodoGrafo(IpOrigen);
        NodoGrafo<string> * destino=Ips->buscarNodoGrafo(IpDestino);
        //Verificar que el ip origen no este ya registrado en el grafo
        if(!origen)
            Ips->insertarNodoGrafo(IpOrigen);
        //Verificar que el ip destino no este ya registrado en el grafo
        if(!destino)
            Ips->insertarNodoGrafo(IpDestino);
        //Verificar que el arco no esté ya registrado.
        NodoGrafo<string> * origenAct = Ips->buscarNodoGrafo(IpOrigen);
        NodoT<Arco<string>*> * arco = origenAct->getArcos()->getHead();
        //Valor booleano para verificar que no haya encontrado el arco con el nodo destino
        bool encontrado = false;
        //Recorrer la lista de arcos de cada nodo
        while(arco){
            //Si encuentra la conexion, aumentar el peso
            if(arco->getDato()->getValorNodoDestino() == IpDestino){
                arco->getDato()->agregarPeso();
                encontrado = true;
            }
            arco = arco->getSiguiente();
        }
        //Si no encontro el arco, agregar un arco al Ip Origen registrado
        if(!encontrado)
            Ips->agregarArco(IpOrigen, IpDestino, 1);
    }
    datos.close();
    //Obtener el recorrido por DepthFirst en un vector
    vector<string> val = Ips->DepthFirst(Ips->getNodos()->getHead()->getDato());
    //Imprimir el recorrido dentro de un archivo txt
    if(val.size() > 0){
        ofstream miArchivo("DepthFirst.txt");
        for(int i = 0; i<val.size(); i++){
            miArchivo<<"Ip: "<<val[i]<<endl;
        }
        miArchivo.close();
    }
    obtenerIpGenera(Ips);
    obtenerIpRecibe(Ips);
}