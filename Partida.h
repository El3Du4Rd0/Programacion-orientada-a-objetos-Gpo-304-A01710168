/*
* Proyecto:
* Juan Eduardo Rosas Cerón
* A01710168
* 13/06/2023
* Esta clase estadefinida por la clase Partida que toma nota del estado general del juego, contanto el numero de persojes vivos, ademas
* que cuenta con la clase Tienda que modifica los atributos de la clase Jugador y es parte de la clase Partida.
*/

#ifndef PARTIDA_H_
#define PARTIDA_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include "Personaje.h"

using namespace std;

// clase Tienda
class Tienda{

    public:

    void mejorar_vida(Jugador *Per);
    void mejorar_danio(Jugador *Per);
    void mejorar_proteccion(Jugador *Per);
    void mejorar_evasion(Jugador *Per);
    void mejorar_precision(Jugador *Per);
    void mejorar_critico(Jugador *Per);
    void descansar( Jugador *Per);
};

/*
* A continuacion se definen cada uno de los metodos de la clase Tienda los cuales modifica a coste de oro los atributos
* de la clase Jugador, tambien se incluye un metodo el cual no cuata oro para que el jugador decida utilizarlo si no tiene oro.
*/

void Tienda::mejorar_vida(Jugador *Per){
    Per->set_oro( Per->get_oro() - 100);
    Per->set_vida( Per->get_vida() + 100);
}

void Tienda::mejorar_danio(Jugador *Per){
    Per->set_oro( Per->get_oro() - 150);
    Per->set_danio( Per->get_danio() + 10);
}

void Tienda::mejorar_proteccion(Jugador *Per){
    Per->set_oro( Per->get_oro() - 150);
    Per->set_vida( Per->get_proteccion() + 0.1);
}

void Tienda::mejorar_evasion(Jugador *Per){
    Per->set_oro( Per->get_oro() - 75);
    Per->set_vida( Per->get_evasion() + 0.05);
}

void Tienda::mejorar_precision(Jugador *Per){
    Per->set_oro( Per->get_oro() - 75);
    Per->set_vida( Per->get_vida() + 0.05);
}

void Tienda::mejorar_critico(Jugador *Per){
    Per->set_oro( Per->get_oro() - 150);
    Per->set_vida( Per->get_vida() + 0.05);
}

void Tienda::descansar(Jugador *Per){
    if( Per->get_envenenado() == true){
        Per->set_envenenado(false);
    }
    if( Per->get_mermado() == true){
        Per->set_mermado(false);
    }
    if( Per->get_sangrado() == true){
        Per->set_sangrado(false);
    }
    Per->set_vida( Per->get_vida() + 25);
}

// clase Partida
class Partida{

    private:

    vector<Personaje*> personajes;
    int num_personajes;
    Tienda tienda;

    public:

    Partida(){num_personajes = 0;}

    void print_creacion_jugador();
    void print_tienda();
    void print_personajes();
    void comprar(int num, Jugador *Per);
    void agrega_personaje( Personaje *Per);
    void elemina_personaje( Personaje *Per);

};

// metodo que muestra un pequeño menu el cual se meutran las opciones que puedes escoger para crear a tu jugador
void Partida::print_creacion_jugador(){
    cout << "Escoge tu clase: " << endl;
    cout << "\t1. Guerrero" << endl;
    cout << "\t\t- Vida elevada" << endl;
    cout << "\t\t- Proteccion elevada" << endl;
    cout << "\t\t- Danio moderado" << endl;
    cout << endl;
    cout << "\t2. Asesino" << endl;
    cout << "\t\t- Vida baja" << endl;
    cout << "\t\t- Evasion elevada" << endl;
    cout << "\t\t- Critico elevado" << endl;
    cout << endl;
    cout << "\t3. Luchador" << endl;
    cout << "\t\t- Vida moderada" << endl;
    cout << "\t\t- Danio moderado" << endl;
    cout << "\t\t- Critico moderado" << endl;
    cout << endl;
}

// metodo que muestra un pequeño menu el cual te muestra las opciones que puedes comprar y sus respectivos costes en oro
void Partida::print_tienda(){
    cout << "\t-- Tienda --" << endl;
    cout << "1. mejorar vida. ( 100 )" << endl;
    cout << "2. mejorar danio. ( 150 )" << endl;
    cout << "3. mejorar proteccion. ( 150 )" << endl;
    cout << "4. mejorar evasion. ( 75 )" << endl;
    cout << "5. mejorar presicion. ( 75 )" << endl;
    cout << "6. mejorar critico ( 150 )" << endl;
    cout << "7. descansar ( gratis )" << endl;
}

// metodo el cual muestra en pantalla los atributos de los personajes que se encuentran en juego
void Partida::print_personajes(){
    for(int i = 0; i < num_personajes; i++){
        cout << endl;
        cout << "Nombre: " << personajes[i]->get_nombre() << endl;
        cout << "Vida: " << personajes[i]->get_vida() << endl;
        cout << "Danio: " << personajes[i]->get_danio() << endl;
        cout << "Proteccion: " << personajes[i]->get_proteccion() << endl;
        cout << "Evasion: " << personajes[i]->get_evasion() << endl;
        cout << "Precision: " << personajes[i]->get_precision() << endl;
        cout << "Critico: " << personajes[i]->get_critico() << endl;
    }
}

// metodo que utiliza los metodos de la clase tienda para modificar a la clase jugador
void Partida::comprar(int num, Jugador *Per){
    if( Per->get_oro() > 0){
        switch (num){
            case 1:
                tienda.mejorar_vida( Per );
                break;
            case 2:
                tienda.mejorar_danio( Per );
                break;
            case 3:
                tienda.mejorar_proteccion( Per );
                break;
            case 4:
                tienda.mejorar_evasion( Per );
                break;
            case 5:
                tienda.mejorar_precision( Per );
                break;
            case 6:
                tienda.mejorar_critico( Per );
                break;
            case 7:
                tienda.descansar( Per );
                break;
            default:
                break;
        }
    } else {
        tienda.descansar( Per );
        cout << "oro insuficiente" << endl;
        system("pause");
    }
}

// metodo para agregar personajes al vector que guarda los personajes en la clsae partida
void Partida::agrega_personaje( Personaje *Per){
    personajes.push_back( Per );
    num_personajes = num_personajes + 1;
    cout << num_personajes << endl;
}

// metodo que elimina personajes del vector que guarda los personajes en la clase partida
void Partida::elemina_personaje( Personaje *Per){
    auto aux = find( personajes.begin(), personajes.end(), Per);
    if (aux != personajes.end()) {
        personajes.erase(aux);
        num_personajes --;
    }
}

#endif