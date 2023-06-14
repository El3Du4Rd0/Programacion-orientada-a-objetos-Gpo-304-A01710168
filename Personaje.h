/*
Proyecto:
Juan Eduardo Rosas Cerón
A01710168
27/05/2023
Esta clase esta definida por la clase Personaje y sus hijos: la clase jugador, la clase Eldritch, la clase Bandido
y la clase Esqueleto, que definen las caracteristicas y habilidades que tienes cada uno de los personajes de mi juego.
*/

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

// bibliotecas
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// clase personaje
class Personaje{

    // atributos protegidos de la clase personaje
    protected:
        string nombre;
        int vida, danio;
        float proteccion, evasion, precision, critico;
    
    public:
        // contructores de la clase personaje
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

        // metodo atacar el cual se define abstracto
        virtual void atacar( Personaje *Per_d, Personaje *Per_a ) = 0;

        // sets de la clase personaje
        void set_nombre(string), set_vida(int), set_danio(int), set_proteccion(float)\
        , set_evasion(float), set_precision(float), set_critico(float);

        // gets de la clase personaje
        string get_nombre();
        int get_vida(), get_danio();
        float get_proteccion(), get_evasion(), get_precision(), get_critico();
};

// definicion de los sets de la clase personaje
void Personaje::set_nombre(string nom){nombre = nom;}
void Personaje::set_vida(int vid){vida = vid;}
void Personaje::set_danio(int dan){danio = dan;}
void Personaje::set_proteccion(float prot){proteccion = prot;}
void Personaje::set_evasion(float eva){evasion = eva;}
void Personaje::set_precision(float pre){precision = pre;}
void Personaje::set_critico(float crit){critico = crit;}

// definicion de los gets de la clase personaje
string Personaje::get_nombre(){return nombre;}
int Personaje::get_vida(){return vida;}
int Personaje::get_danio(){return danio;}
float Personaje::get_proteccion(){return proteccion;}
float Personaje::get_evasion(){return evasion;}
float Personaje::get_precision(){return precision;}
float Personaje::get_critico(){return critico;}

// clase jugador que hereda los atributos y metodos de la clase personaje
class Jugador: public Personaje{

    // atributos de la clase jugador
    private:
        int oro;
        bool envenenado, sangrado,  mermado, aturdido, puertas_de_la_muerte;

    public:
        // costructores de la clase jugador
        Jugador(){}
        Jugador(string nom, int vid, int dan, float prot, float eva, float pre, float crit, int gold)\
        :Personaje(nom, vid, dan, prot, eva, pre, crit){
            oro = gold;
            envenenado = sangrado  = mermado = aturdido = false;
            puertas_de_la_muerte = true;
        }

        // metodo atacar heredado de la clase personaje
        void atacar( Personaje *Per_d, Personaje *Per_a );

        // sets de la clase jugador
        void set_oro( int gold), set_envenenado( bool veneno), set_sangrado( bool hemorragia)\
        , set_mermado( bool merma), set_aturdido( bool stun), set_puertas_muerte( bool muerte);

        // gets de la clase jugador
        int get_oro();
        bool get_envenenado(), get_sangrado(), get_mermado(), get_aturdido(), get_puertas_muerte();
};

// definicion del metodo abstracto atacar heredado de la personaje a la clase jugador
void Jugador::atacar( Personaje *Per_d, Personaje *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 7;

    /* 
    *Calculo de daño el cual toma todos los atributos defensivos del personaje defensor "Per_d", y todos los atributos ofensivos
    *del personaje atacante "Per_a"; los atributos vienen heredados de la clase personaje a la clase jugador. 
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 3)) * 1.5));
            cout << "jugador: ataque critico" << endl;
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - (Per_a -> get_danio() + mod_danio - 3));
            cout << "jugador: ataque exitoso" << endl;
        }
    } else {
        cout << "jugador: ataque fallido" << endl;;
    }
}

// definicion de los sets de la clase jugador
void Jugador::set_oro( int gold ){oro = gold;}
void Jugador::set_envenenado( bool veneno){if(veneno == true){envenenado = true;}else{envenenado = false;}}
void Jugador::set_sangrado( bool sangre){if(sangre == true){sangrado = true;}else{sangrado = false;}}
void Jugador::set_mermado( bool merma){if(merma == true){mermado = true;}else{mermado = false;}}
void Jugador::set_aturdido( bool stun){if(stun == true){aturdido = true;}else{mermado = false;}}
void Jugador::set_puertas_muerte( bool muerte){ if(muerte == true){puertas_de_la_muerte = true;}else{puertas_de_la_muerte = false;}}

// definicion de los gets de la clase jugador
int Jugador::get_oro(){return oro;}
bool Jugador::get_envenenado(){return envenenado;}
bool Jugador::get_sangrado(){return sangrado;}
bool Jugador::get_mermado(){return mermado;}
bool Jugador::get_aturdido(){return aturdido;}
bool Jugador::get_puertas_muerte(){return puertas_de_la_muerte;}

// clase eldritch que hereda los atributos y metodos de la clase personaje
class Eldritch : public Personaje{

    public:
    // costructores de la clase eldritch
    Eldritch(){}
    Eldritch(string nom, int vid, int dan, float prot, float eva, float pre, float crit)\
    :Personaje(nom, vid, dan, prot, eva, pre, crit){}

    // metodos de la clase eldritch
    void atacar( Personaje *Per_d, Personaje *Per_a );
    void mermar( Jugador *Per_d, Eldritch *Per_a );
    void envenenar( Jugador *Per_d, Eldritch *Per_a);
};

// definicion del metodo abstracto atacar heredado de la personaje a la clase eldritch
void Eldritch::atacar( Personaje *Per_d, Personaje *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 13;

    /* 
    * Aqui el calculo de daño es casi igual a la de la clase personaje, unicamente cambia el multiplicador de critico y el
    * margen del modificador de daño para hacer a la clase eldritch mucho mas peligrosa
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 5.0)) * 1.5));
            cout << "eldritch: ataque critico" << endl;
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - (Per_a -> get_danio() + mod_danio - 5));
            cout << "eldritch: ataque exitoso" << endl;
        }
    } else {
        cout << "eldritch: ataque fallido" << endl;;
    }
}

void Eldritch::mermar( Jugador *Per_d, Eldritch *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 13;

    /* 
    * En este apartado el metodo mermar funciona de forma similar al metodo atacar, pero con la diferencia que deja mermado
    * al jugador y que este tiene un modificador de daño extra de 0.5
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_mermado(true);
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 5)) * 1.5 * 0.5));
            cout << "eldritch: merma critica" << endl;
        } else {
            Per_d -> set_mermado(true);
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 5)) * 0.5));
            cout << "eldritch: merma exitosa" << endl;
        }
    } else {
        cout << "eldritch: merma fallida" << endl;
    }
}

void Eldritch::envenenar( Jugador *Per_d, Eldritch *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 13;

    /* 
    * En este apartado el metodo envenenar funciona de forma similar al metodo atacar, pero con la diferencia que deja envenenado
    * al jugador y que este tiene un modificador de daño extra de 0.4
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_envenenado(true);
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 5)) * 1.5 * 0.4));
            cout << "eldritch: envenenamiento critico" << endl;
        } else {
            Per_d -> set_envenenado(true);
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 5)) * 0.4));
            cout << "eldritch: envenenamiento exitoso" << endl;
        }
    } else {
        cout << "eldritch: envenenamineto fallido" << endl;
    }
}

// clase bandido que hereda los atributos y metodos de la clase personaje
class Bandido : public Personaje{

    private:
    int oro_robado;

    public:
        // constructores de la clase bandido
        Bandido(){oro_robado = 0;};
        Bandido(string nom, int vid, int dan, float prot, float eva, float pre, float crit)\
        :Personaje(nom, vid, dan, prot, eva, pre, crit){oro_robado = 0;}

        // sets y gets
        void set_oro_robado(int gold);
        int get_oro_robado();

        // metodos de la clase bandido
        void atacar( Personaje *Per_d, Personaje *Per_a );
        void robar( Jugador *Per_d, Bandido *Per_a );
        void huir();

};

void Bandido::set_oro_robado(int gold){oro_robado = gold;}
int Bandido::get_oro_robado(){return oro_robado;}


// definicion del metodo abstracto atacar heredado de la personaje a la clase bandido
void Bandido::atacar( Personaje *Per_d, Personaje *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1, porcentaje_2, mod_danio;
    porcentaje_1 = rand() % 100 + 1;
    porcentaje_2 = rand() % 100+ 1;
    mod_danio = rand() % 13;

    /* 
    * Aqui el calculo de daño es casi igual a la de la clase personaje, unicamente cambia el multiplicador de critico y el
    * margen del modificador de daño para hacer a la clase bandido mucho mas volatil
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida( (Per_d -> get_vida() - int(float(Per_a -> get_danio()) + float(mod_danio - 6)) * 1.5));
            cout << "bandido: ataque critico" << endl;
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - int(float(Per_a -> get_danio()) + float(mod_danio - 6)));
            cout << "bandido: atauqe exitoso" << endl;
        }
    } else {
        cout << "bandido: ataque fallido" << endl;
    }
}

// definicion del metodo robar de la clase bandido
void Bandido::robar( Jugador *Per_d, Bandido *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 13;

    /* 
    * En este apartado el metodo robar funciona de forma similar al metodo atacar, pero que su principal objetivo es bajar las
    * reservas de oro de un objeto creado de la clase jugador, ademas que cuanta con un modificar de extra de daño de 0.2 para
    * que lo unico preocupante de este ataque sea el oro perdido. 
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_oro( Per_d -> get_oro() - 50);
            oro_robado += 50;
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 6)) * 0.2 * 1.5));
            cout << "bandido: robo critico" << endl;
        } else {
            Per_d -> set_oro( Per_d -> get_oro() - 20);
            oro_robado += 20;
            Per_d -> set_vida( Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 6)) * 0.2));
            cout << "bandido: robo exitoso" << endl;
        }
    } else {
        cout << "bandido: robo fallido" << endl;
    }
}

void Bandido::huir(){
    oro_robado = 0;
    vida = 0;
}

// clase esqueleto que hereda los atributos y metodos de la clase personaje
class Esqueleto : public Personaje{

    public:
        // costructores de la clase esqueleto
        Esqueleto(){}
        Esqueleto(string nom, int vid, int dan, float prot, float eva, float pre, float crit)\
        :Personaje(nom, vid, dan, prot, eva, pre, crit){}
    
        // metodos de la calse esqueleto
        void atacar( Personaje *Per_d, Personaje *Per_a );
        void aturdir( Jugador *Per_d, Esqueleto *Per_a );
        void hemorragia( Jugador *Per_d, Esqueleto *Per_a);
};

// definicion del metodo abstracto atacar heredado de la personaje a la clase esqueleto 
void Esqueleto::atacar( Personaje *Per_d, Personaje *Per_a ){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 4;

    /* 
    * Aqui el calculo de daño es casi igual a la de la clase personaje, unicamente cambia el multiplicador de critico y el
    * margen del modificador de daño para hacer a la clase esqueleto mas debil
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida(Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 2 )) * 1.5 ));
            cout << "esuqueleto: ataque critico" << endl;
        } else {
            Per_d -> set_vida(Per_d -> get_vida() - (Per_a -> get_danio() + mod_danio - 2) );
            cout << "esqueleto: atauque exitoso" << endl;
        }
    } else {
        cout << "esqueleto: ataque fallido" << endl;
    }
}

void Esqueleto::aturdir( Jugador *Per_d, Esqueleto *Per_a){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 4;

    /* 
    * En este apartado el metodo aturdir funciona de forma similar al metodo atacar, pero que su principal objetivo es aturdir
    * a un objeto creado de la clase jugador, ademas que cuanta con un modificar de extra de daño de 0.2 para que lo unico que sea
    * preocupante sea el aturdimiento y no el daño causado por el esqueleto.
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_vida( Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 2)) * 1.5 * 0.2));
            cout << "esqueleto: aturdimiento critico" << endl;
            Per_d->set_aturdido(true);
        } else {
            Per_d -> set_vida( Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 2)) * 0.2 ));
            cout << "esqueleto: aturdimiento exitoso" << endl;
            Per_d->set_aturdido(true);
        }
    } else {
        cout << "esqueleto: aturdimiento fallido" << endl;
    }
}

void Esqueleto::hemorragia( Jugador *Per_d, Esqueleto *Per_a){

    // generacion de numeros aleatorios auxiliares para las probabilidades
    int porcentaje_1 = rand() % 100 + 1;
    int porcentaje_2 = rand() % 100 + 1;
    int mod_danio = rand() % 4;

    /*
    * En este apartado el metodo hemorragia funciona de forma similar al metodo atacar, pero que su principal objetivo es aplicar
    * sangrado a un objeto creado de la clase jugador, ademas que cuanta con un modificar de extra de daño de 0.2 para que lo unico
    * que sea preocupante sea el sangrado y no el daño causado por el esqueleto. 
    */

    if( (float(porcentaje_1) / 100.0) < (Per_a -> get_precision() - Per_d -> get_evasion())){
        if( (float(porcentaje_2) / 100.0) < (Per_a -> get_critico())){
            Per_d -> set_sangrado(true);
            Per_d -> set_vida( Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 2) )* 1.5 * 0.2 ));
            cout << "esqueleto: hemorragia critica" << endl;
        } else {
            Per_d -> set_sangrado(true);
            Per_d -> set_vida( Per_d -> get_vida() - int( (float(Per_a -> get_danio()) + float(mod_danio - 2) )* 0.2 ));
            cout << "esqueleto: hemorragia exitosa" << endl;
        }
    } else {
        cout << "esqueleto: hemorragia fallida" << endl;
    }
}

#endif