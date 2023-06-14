# Programacion-orientada-a-objetos-Gpo-304-A01710168
Juan Eduardo Rosas Ceron - A01710168
## Descripción
Mi codigo consta de un pequeño juego el cual te va enfrentando contra enemigos hasta que el jugador se quede sin puntos de vida, esta accion se va intercalando con la aparicion de una tienda en la cual puedes mejorar una de tus estadisticas para poder eliminar mas eficientemente a los enemigos con los que te vas enfrentando. El transcurso de la partida como la creacion del personaje, y el como vana air apareciendo lso enemigos se modela en el main, ademas que despues para que los enemigos tengan una IA cree un switch el cual toma elecciones apoyado por un pequeño generador de numeros aleatoriosy diversos if() para cada uno de los enemigos posibles.
tambien justo en el inicio del main modele unas pequeñas funciones para que el jugador tenga una segunda oportunidad quedandose a un punto de vida, y otra para que los enemigos no se quedaran con vida negativa. Esto se pudo haber integrado de forma base en los metodos de sus respectivas clases, pero considere que asi se ejemplificaba mejor su funcionamiento.
En el archivo Personaje.h se encuentran definidos todos los hijos de la clase Personaje junto con la misma, aqui se definen los metodos de cada clase y sus atributos. Cabe aclarar que la clase Personaje es abstracta, ya que nunca se crean objetos de tipo Personaje y solo hereda sus atributos a sus clase hijas.
## Funcionalidad
El codigo funciona unicamente en el sistema operativo de Windows, ya que utiliza la funcion system() para pausar el sistema y para limpiar la consola. Por lo mismo el codigo debe correrse en consola para su correcto funcionamiento. 
## Consideraciones
Mi codigo esta hecho completamente con C++ estandar.

Al estar ejecutar mi codigo se pueden generar unos errores si pones mal las entradas que se solicitan, por ejemplo a la hora de crear personajes solo debes introducir una palabra sin espacios, pero este no genera tantos problemas. Despues en el codigo se te solicitara comprar algo en la tienda, aqui debes de poner unicamente numeros, ya que sino la tienda nunca volvera a aparecer y ya no podras volver a comprar nada.

Finalmente una cosa que podria ser antiintuitivo es que puedes comprar cosas aunque no te alcanze el dinero, esto se me paso cambiarlo, pero la tienda no te deja comprar nada si el valor de tu oro en negativo y te ejecuta automaticamente la unica accion que no cuesta oro para ser comprada. Esto despues decidi dejarlo ya que parece que la tienda te deja pedir fiado, pero cuando le debes mucho ya no te quiere seguir vendindo nada.

Las librerias que utilize son: stdlib.h & time.h para poder inicializar el generador de numeros aleatorios, la libreria vector para hacer agregacion en la clase Partida, la libreria limits para comprobar que el usuario introdujo la entrada correcta en una parte del codigo que seria catastrofico que no se ejecutara bien, y finalmente se utiliza la libreria algorithm en el metodo elimina personaje de la clase Pertida.
