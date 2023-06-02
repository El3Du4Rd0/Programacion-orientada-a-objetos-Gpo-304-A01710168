/*
* Proyecto:
* Juan Eduardo Rosas Cerón
* A01710168
* 27/05/2023
* Esta clase esta definida por la clase Personaje
*/

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Personaje{

    protected:

    string nombre;
    int vida;
    int danio;
    float proteccion;
    float evasion;
    float precision;
    float critico;
    
    public:

    Personaje(){}

    Personaje(string nom, int vid, int dan, float prot, float eva, float pre, float crit){
        nombre = nom;
        vida = vid;
        danio = dan;
        proteccion = prot;
        evasion = eva;
        precision = pre;
        critico = crit;
    }

    virtual void atacar( Personaje *Per_d, Personaje *Per_a ) = 0;

    void set_nombre(string);
    void set_vida(int);
    void set_danio(int);
    void set_proteccion(float);
    void set_evasion(float);
    void set_precision(float);
    void set_critico(float);

    string get_nombre();
    int get_vida();
    int get_danio();
    float get_proteccion();
    float get_evasion();
    float get_precision();
    float get_critico();
};

void Personaje::set_nombre(string nom){nombre = nom;}
void Personaje::set_vida(int vid){vida = vid;}
void Personaje::set_danio(int dan){danio = dan;}
void Personaje::set_proteccion(float prot){proteccion = prot;}
void Personaje::set_evasion(float eva){evasion = eva;}
void Personaje::set_precision(float pre){precision = pre;}
void Personaje::set_critico(float crit){critico = crit;}

string Personaje::get_nombre(){return nombre;}
int Personaje::get_vida(){return vida;}
int Personaje::get_danio(){return danio;}
float Personaje::get_proteccion(){return proteccion;}
float Personaje::get_evasion(){return evasion;}
float Personaje::get_precision(){return precision;}
float Personaje::get_critico(){return critico;}

class Jugador: public Personaje{

    private:

    int oro;

    public:

    Jugador(string nom, int vid, int dan, float prot, float eva, float pre, float crit, int gold)\
    :Personaje(nom, vid, dan, prot, eva, pre, crit){
        oro = gold;
    }

    void atacar( Personaje *Per_d, Personaje *Per_a );

    void set_oro( int gold);

    int get_oro();
};

void Jugador::atacar( Personaje *Per_d, Personaje *Per_a ){

    srand(time(NULL));

    int porcentaje_1, porcentaje_2, mod_danio;
    porcentaje_1 = rand() % 100;
    porcentaje_2 = rand() % 100;
    mod_danio = rand() % 7;

    if( (float(porcentaje_1) / 100.0) > (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio()) * 1.5 + float(mod_danio - 2.0)));
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio()) + float(mod_danio - 2.0)));
        }
    } 
}

void Jugador::set_oro( int gold ){oro = gold;}
int Jugador::get_oro(){return oro;}

class Bandido : public Personaje{

    public:

    Bandido(string nom, int vid, int dan, float prot, float eva, float pre, float crit)\
    :Personaje(nom, vid, dan, prot, eva, pre, crit){}

    void atacar( Personaje *Per_d, Personaje *Per_a );
    void robar( Jugador *Per_d, Bandido *Per_a );

};

void Bandido::atacar( Personaje *Per_d, Personaje *Per_a ){

    srand(time(NULL));

    int porcentaje_1, porcentaje_2, mod_danio;
    porcentaje_1 = rand() % 100;
    porcentaje_2 = rand() % 100;
    mod_danio = rand() % 13;

    if( (float(porcentaje_1) / 100.0) > (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio()) * 2.0 + float(mod_danio - 3.0)));
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio()) + float(mod_danio - 3.0)));
        }
    } 
}

void Bandido::robar( Jugador *Per_d, Bandido *Per_a ){

    srand(time(NULL));

    int porcentaje_1, porcentaje_2, mod_danio;
    porcentaje_1 = rand() % 100;
    porcentaje_2 = rand() % 100;
    mod_danio = rand() % 13;

    if( (float(porcentaje_1) / 100.0) > (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_oro( Per_d -> get_oro() - 50);
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio() * 0.2) * 2.0 + float(mod_danio - 3.0)));
        } else {
            Per_d -> set_oro( Per_d -> get_oro() - 20);
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio() * 0.2) + float(mod_danio - 3.0)));
        }
    }

}

#endif