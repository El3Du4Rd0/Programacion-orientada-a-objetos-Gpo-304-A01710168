#include "Personaje.h"

#include <iostream>
using namespace std;

int main(){

    srand(time(NULL));

    Jugador jugador1("juan", 100, 20, 0.2, 0.1, 0.1, 0.2, 500);
    Bandido enemigo("kevin", 100, 20, 0.2, 0.1, 0.1, 0.1);

    enemigo.robar(&jugador1, &enemigo);
    cout << "oro: " << jugador1.get_oro() << " vida: " << jugador1.get_vida() << endl;

    enemigo.robar(&jugador1, &enemigo);
    cout << "oro: " << jugador1.get_oro() << " vida: " << jugador1.get_vida() << endl;

    enemigo.robar(&jugador1, &enemigo);
    cout << "oro: " << jugador1.get_oro() << " vida: " << jugador1.get_vida() << endl;

    int a = 0;
    cin >> a;

    return 0;
}