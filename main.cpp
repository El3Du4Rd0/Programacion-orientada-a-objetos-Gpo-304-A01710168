/*
* Proyecto:
* Juan Eduardo Rosas Cerón
* A01710168
* 13/06/2023
* El archivo Main de mi proyecto dicta como debe transcurrir la partida modelando una IA muy basica la cual
* toma desiciones con un generador de numeros aleatorios y varias condiciones para cada uno de los enemigos
*/

// archivos de mis clases
#include "Personaje.h"
#include "Partida.h"

// bibliotecas
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
* Esta funcion evita que el jugador muera por primera vez dejandolo a un punto de vida, pero solo lo salva una vez
* despues de eso cualquier cosa podria acabar la partida. 
*/

void puertas_muerte( Jugador *Per ){
    if ( Per->get_vida() < 1){
        if ( Per->get_puertas_muerte()){
            Per->set_vida(1);
            Per->set_puertas_muerte(false);
            cout << "usted esta en las puertas de la muerte" << endl;
        } else {
            Per->set_vida(0);
        }
    } 
}

/*
* Esta funcion solo comprueba la vida de un personaje para que no baje más alla de uno, esto unicamente tiene propositos esteticos,
* ya que no afecta esta comprobacion a los calculos que se hacen durante la partida.
*/

void comprobar( Personaje *Per){
    if (Per->get_vida() < 1){
        Per->set_vida(0);
    }
}

int main(){

    // iniciador de numeros aleatorios con respecto al tiempo
    srand(time(NULL));

    // objetos para el funcionamiento del codigo
    Personaje *player = new Jugador();
    Partida partida;

    /*
    * Esta parte del codigo sirve como creador de personaje inicial, aqui el usuario puede seleccionar entre tres
    * posibles opciones y tambien se va a poder escoger un nombre el cual servira para que el jugador se identifique
    * entre los demas personajes que apareceran durante la partida. 
    */

    bool aux = true;
    while (aux){

        int seleccion_personaje = 0;
        string name = "";

        // aqui se imprime el menu para crear el personaje que usara el jugador
        partida.print_creacion_jugador();
        cin >> seleccion_personaje;

        switch (seleccion_personaje){
            case 1:
                cout << "Introduce el nombre de tu personaje: ";
                cin >> name;
                player->set_nombre(name);

                player->set_vida(500);
                player->set_danio(15);
                player->set_proteccion(0.3);
                player->set_evasion(0.1);
                player->set_precision(0.9);
                player->set_critico(0.1);

                aux = false;
                break;
            case 2:
                cout << "Introduce el nombre de tu personaje: ";
                cin >> name;
                player->set_nombre(name);

                player->set_vida(300);
                player->set_danio(40);
                player->set_proteccion(0.0);
                player->set_evasion(0.3);
                player->set_precision(1.0);
                player->set_critico(0.25);

                aux = false;
                break;
            case 3:
                cout << "Introduce el nombre de tu personaje: ";
                cin >> name;
                player->set_nombre(name);

                player->set_vida(400);
                player->set_danio(30);
                player->set_proteccion(0.1);
                player->set_evasion(0.1);
                player->set_precision(0.9);
                player->set_critico(0.1);   

                aux = false;  
                break;  
            default:

                /* 
                * Aqui utilizo la funcion cin.clear() & numeri_limits<> para comprobar si el usuario puso la entrada correcta, 
                * esto unicamente lo utilizo aqui, ya que si el usuario se equivocaba al escoger su personaje el juego no
                * podria iniciar.
                */

                cout << "Entrada invalida" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }

    system("cls");

    // agregar player al arreglo de personajes en el objeto partida
    partida.agrega_personaje(player);

    // cast al objeto player
    Jugador *jugador = dynamic_cast< Jugador *>(player);
    jugador->set_oro(200);

    // creacion de los enemigos y sus casts
    Personaje *eldritch = new Eldritch;
    Personaje *bandido = new Bandido;
    Personaje *esqueleto = new Esqueleto;

    Eldritch *_eldritch = dynamic_cast< Eldritch *>(eldritch);
    Bandido *_bandido = dynamic_cast< Bandido *>(bandido);
    Esqueleto *_esqueleto = dynamic_cast< Esqueleto *>(esqueleto);
    
    /*
    * En esta parte del codigo se ejecutara un ciclo while el cual se va a ejecutar hasta que el jugador se quede sin puntos
    * de vida. Esto define como transcurre la partida y tambien cuando termina.
    */

    while( jugador->get_vida() > 0){

        // variable auxiliar el cual sirve para que el usuario introduzca que quiere comprar el la tienda
        int aux = 0;

        // numero aleatorio para generar un enemigo 
        int random_enemigo = rand() % 3 + 1;

        switch (random_enemigo){
        case 1:

            _eldritch->set_nombre("eldritch");
            _eldritch->set_vida(125);
            _eldritch->set_danio(40);
            _eldritch->set_proteccion(0.2);
            _eldritch->set_evasion(0.2);
            _eldritch->set_precision(1.0);
            _eldritch->set_critico(0.2);

            partida.agrega_personaje(_eldritch);

            /*
            * En esta parte de mi codigo el usuario vuelve a entrar a un ciclo while el cual define la IA del objeto
            * _eldritch, este ciclo define las acciones que puede tomar el personaje enemigo y que se repetira hasta que
            * el jugador tenga puntos de vida o hasta que el personaje enemigo tenga puntos de vida.
            */

            while (jugador->get_vida() > 0 && _eldritch->get_vida() > 0){

                // numero random el cual selecciona la accion que realizara el personaje enemigo
                int random_numero = rand() % 3 + 1;

                switch (random_numero){
                case 1:
                    if( jugador->get_envenenado() ){
                        _eldritch->atacar(jugador, _eldritch);
                        jugador->atacar(_eldritch, jugador);
                    } else {
                        _eldritch->envenenar(jugador, _eldritch);
                        jugador->atacar(_eldritch, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    // aqui se comprueban la vida del jugador y la vida del personaje enemigo
                    puertas_muerte(jugador);
                    comprobar(_eldritch);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;
                
                case 2:
                    if ( jugador->get_mermado() ){
                        _eldritch->atacar(jugador, _eldritch);
                        jugador->atacar(_eldritch, jugador);
                    } else {
                        _eldritch->mermar(jugador, _eldritch);
                        jugador->atacar(_eldritch, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_eldritch);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;

                default:
                    _eldritch->atacar(jugador, _eldritch);
                    jugador->atacar(_eldritch, jugador);

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_eldritch);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;
                }
            }

            // oro que obtiene el jugador por eliminar a un enemigo tipo eldritch
            jugador->set_oro(jugador->get_oro() + 125);

            // aqui se elimina el personaje _eldritch del arreglo de personajes en partida
            partida.elemina_personaje(_eldritch);

            if (jugador->get_vida() > 0){

                partida.print_tienda();

                cout << "su oro es: " << jugador->get_oro() << endl;
                cout << "seleccione una opcion con numeros enteros: " << endl << endl;

                cin >> aux;
                system("cls");
                partida.comprar(aux, jugador);
            }
            break;
        case 2:
            
            _bandido->set_nombre("bandido");
            _bandido->set_vida(80);
            _bandido->set_danio(30);
            _bandido->set_proteccion(0.0);
            _bandido->set_evasion(0.25);
            _bandido->set_precision(0.8);
            _bandido->set_critico(0.2);
            
            partida.agrega_personaje(_bandido);

            while (jugador->get_vida() > 0 && _bandido->get_vida() > 0){
                
                int random_numero = rand() % 3 + 1;

                switch (random_numero){
                case 1:
                    if( jugador->get_oro() > 0){
                        _bandido->robar(jugador, _bandido);
                        jugador->atacar(_bandido, jugador);
                    } else {
                        _bandido->atacar(jugador, _bandido);
                        jugador->atacar(_bandido, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_bandido);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;
                
                case 2:
                    if ( _bandido->get_oro_robado() > 0){
                        _bandido->huir();
                    } else {
                        _bandido->atacar(jugador, _bandido);
                        jugador->atacar(_bandido, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_bandido);
            
                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;

                default:
                    _bandido->atacar(jugador, _bandido);
                    jugador->atacar(_bandido, jugador);

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_bandido);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;
                }
            }

            // aqui el jugador obtiene oro por eliminar el objeto de _bandido y tambien obtiene el oro que tenia almacenado
            jugador->set_oro( jugador->get_oro() + 50 + _bandido->get_oro_robado() );

            partida.elemina_personaje(_bandido);

            if (jugador->get_vida() > 0){
                partida.print_tienda();

                cout << "su oro es: " << jugador->get_oro() << endl;
                cout << "seleccione una opcion con numeros enteros: " << endl << endl;

                cin >> aux;

                partida.comprar(aux, jugador);
            }

            break;
        case 3:
            
            _esqueleto->set_nombre("esqueleto");
            _esqueleto->set_vida(150);
            _esqueleto->set_danio(20);
            _esqueleto->set_proteccion(0.3);
            _esqueleto->set_evasion(0.05);
            _esqueleto->set_precision(0.9);
            _esqueleto->set_critico(0.1);

            partida.agrega_personaje(_esqueleto);

            while (jugador->get_vida() > 0 && _esqueleto->get_vida() > 0){
                
                int random_numero = rand() % 3 + 1;

                switch (random_numero){
                case 1:
                    _esqueleto->aturdir(jugador, _esqueleto);
                    if( jugador->get_aturdido()){
                        cout << "jugador: - - - " << endl;
                        jugador->set_aturdido(false);
                    } else {
                        jugador->atacar(_esqueleto, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_esqueleto);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                 
                    break;
                
                case 2:
                    if ( jugador->get_sangrado() ){
                        _esqueleto->atacar(jugador, _esqueleto);
                        jugador->atacar(_esqueleto, jugador);
                    } else {
                        _esqueleto->hemorragia(jugador, _esqueleto);
                        jugador->atacar(_esqueleto, jugador);
                    }

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_esqueleto);
            
                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;

                default:
                    _esqueleto->atacar(jugador, _esqueleto);
                    jugador->atacar(_esqueleto, jugador);

                    if( jugador->get_sangrado() ){
                            cout << "esta sangrando: -2" << endl;
                            jugador->set_vida( jugador->get_vida() - 2);
                    } else if ( jugador->get_envenenado() ){
                        cout << "esta envenenado: -5" << endl;
                        jugador->set_vida( jugador->get_vida() - 5);
                    }

                    puertas_muerte(jugador);
                    comprobar(_esqueleto);

                    partida.print_personajes();

                    system("pause");
                    system("cls");
                    break;
                }
            }

            // oro obtenido por eliminar un personaje enemigo tipo Esqueleto
            jugador->set_oro( jugador->get_oro() + 100);

            partida.elemina_personaje(_esqueleto);

            if( jugador->get_vida() > 0){
                partida.print_tienda();

                cout << "su oro es: " << jugador->get_oro() << endl;
                cout << "seleccione una opcion con numeros enteros: " << endl << endl;

                cin >> aux;

                partida.comprar(aux, jugador);
            }

            break;
        
        default:
            break;
        }
    }

    // liberacion de memoria
    delete player, _esqueleto, _bandido, _eldritch;

    return 0;
}