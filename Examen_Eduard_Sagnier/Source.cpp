#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <windows.h> // Para hacer un Sleep para poder dejar un tiempo y borrar la terminal. (Sacado de mi proyecto hundir la flota).

using namespace std;

#define NUM_PALABARAS_JUEGO 3

void main()
{
	//std::string palabras[NUM_PALABARAS_JUEGO] = { "Buenas", "Programacion", "Perro" };

	vector <string> palabras;
	palabras.push_back("buenas"); //Insertamos manualmente las palabras.
	palabras.push_back("perro");
	palabras.push_back("programador");


	srand(std::time(NULL));

	bool partida_finalizada = false; // Para el while de toda la partida

	short partidas_ganadas = 0; 
	short partidas_perdidas = 0;
	char letra_usuario;

	short numero_palabras_restantes = NUM_PALABARAS_JUEGO; //Guardamos una variable la cual se ira modificando las palabras restantes en el

	cout << "El Ahorcado" << endl;
	cout << "Made by EduSagnier" << endl;
	cout << endl << endl;


	while (!partida_finalizada)
	{
		/*cout << "Num Restante" << numero_palabras_restantes;*/

		short num_palabra_random = (rand() % numero_palabras_restantes); //Hacemos un random con la cantidad de palabras que hay en el vector.

		cout << endl << endl;

		string palabra_random = palabras[num_palabra_random]; //Creo una string la que me permite almacenar el valor del vector. 
		for (int i = 0; i < palabras.size(); i++)
		{
			if (palabras[i] == palabra_random)
			{
				palabras.erase(palabras.begin() + i); //Borraremos la palabra ya almacendada para que no se repita
				numero_palabras_restantes--; // Restaremos uno al numero de palabras que hay.

				//cout << "Palabra borrada y numero de palabras restantes (en el vector) = "<< numero_palabras_restantes << endl; //DEBUG
			}
		}

		cout << "La palabra random es: " << palabra_random << endl;

		Sleep(5000); // DEBUG DE LA PALABRA RANDOM
		system("cls"); //Limpia la terminal


		int intentos = palabra_random.length();
		//cout << "Tus Intentos son " << intentos << " Porque tu palabra tiene " << palabra_random.length() << endl; //DEBUG

		cout << "Tienes estos intentos para la palabra: " << intentos << endl;
		cout << "Tu siguiente palabra es:" << endl;


		for (int i = 0; i < palabra_random.length(); i++) //Sacamos los espacios de la palabra que tendra el user.
		{
			cout << "_ ";
		}
		cout << endl << endl;


		bool palabra_accertada = false; //Seria para el while "de ronda".
		string intento_palabra_user; //Sera donde se almacene las letras correctas.
		int letra_correctas = 0; //Calculara las letras que el usuario ha accertado y si esta variable es == a lo largo de la palabra significara que la ha encertado.
		int ronda = 0; // Las rondas que lleva el usuario.(Me permitira decir el tipo de motivo de derrota) 


		for (int i = 0; i < palabra_random.length(); i++)
		{
			intento_palabra_user = intento_palabra_user + '_';

		}
		//cout << "intento_palabra_user: " << intento_palabra_user; //DEBUG

		while (!palabra_accertada)
		{
			ronda++;
			system("cls");

			bool letra_introducido_bien = false;

			while (!letra_introducido_bien) //Mietras no ponga un character valido no saldra el user.
			{
				for (int i = 0; i < intento_palabra_user.length(); i++) // SACO EL INTENTO QUE TIENE EL USUARIO CADA VEZ QUE INSERTA
				{
					cout << intento_palabra_user[i] << " ";
				}
				cout << endl << endl;

				cout << "Introduce la letra que quieres: " << endl;
				cin >> letra_usuario;

				if (letra_usuario > 64 && letra_usuario < 91) // En caso que sea MAYUS pasara a MINUS
				{
					letra_usuario = letra_usuario + 32;

				}

				if (letra_usuario > 96 && letra_usuario < 123) //Si la letra es minus en la tabla ascci lo dara por correcto
				{
					//cout << "Letra introducioda es correcta"; //DEBUG
					letra_introducido_bien = true;
				}
				else
				{
					cout << "No has introducido un character correcto" << endl; //Si no pone ninguna letra valida
				}
			}


			bool algun_acierto = false;
			bool palabra_repetida = false;

			for (int i = 0; i < palabra_random.length(); i++) //VERIFICA SI YA HA UTILIZADO ESA LETRA POR EL USUARIO (SI ESTA)
			{
				if (letra_usuario == intento_palabra_user[i])
				{
					palabra_repetida = true;
				}
			}

			if (!palabra_repetida) //En caso de que no haya palabra repetida verificara igual
			{
				for (int i = 0; i < palabra_random.length(); i++)
				{


					if (letra_usuario == palabra_random[i] && intento_palabra_user[i] == '_')
					{
						intento_palabra_user[i] = letra_usuario;

						letra_correctas++;
						algun_acierto = true;

						//cout << "Letras correctas: " << letra_correctas << endl; //DEBUG
					}

				}
			}
			else // Si es repetida
			{
				cout << "Ya has utilizado esta letra" << endl;
				algun_acierto = true; //DE ESTA MANERA NO LE RESTARA INTENTOS AUNQUE TENGA LA LETRA REPETIDA.
			}

			for (int i = 0; i < intento_palabra_user.length(); i++)
			{
				cout << intento_palabra_user[i] << " ";
			}
			cout << endl << endl;


			if (algun_acierto == false)
			{
				intentos--;
				cout << "Numeros de intentos restantes: " << intentos << endl;
			}
			Sleep(2500);


			if (letra_correctas == palabra_random.length())
			{
				palabra_accertada = true;
				partidas_ganadas++;
				cout << "Has accertado la palabra" << endl;
			}
			if (intentos <= 0)
			{
				palabra_accertada = true; //NO LA HA ACERTADO PERO PARA CERRAR EL BUCLE DE LA PALABRA.
				partidas_perdidas++;

				cout << "No has aceertado la palabra" << endl;
			}

		}




		if (partidas_ganadas == 2)
		{
			cout << "Has Ganadado 2 partidas. Fin del juego ganador." << endl;
			partida_finalizada = true;
		}

		if (partidas_perdidas == 2 && ronda == 3)
		{
			cout << "No has conseguido hacerar 2 palabaras en las 3 rondas. Has perdido" << endl;
			partida_finalizada = true;
		}
		else if (partidas_perdidas == 2)
		{
			cout << "Has perdido 2 rondas principales ya no puedes ganar. Fin del juego" << endl;
			partida_finalizada = true;
		}

	}

}