// BlackJack.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>


using namespace std;

//Variables JUGADOR
int puntosJugador = 0;
string nombreJugador;
bool estadoJugador = true;
int eleccionAs;
string eleccionJugador;
string eleccionVolver;
bool empezar = true;


//Variables BANCA
int puntosBanca = 0;
string nombreBanca = "Banca";
bool estadoBanca = true;

//Variables CARTAS
int arrayCartas[4][13] = { {0,1,2,3,4,5,6,7,8,9,10,11,12},{0,1,2,3,4,5,6,7,8,9,10,11,12},{0,1,2,3,4,5,6,7,8,9,10,11,12},{0,1,2,3,4,5,6,7,8,9,10,11,12} };
bool arrayRepetidas[4][13];
int valorCarta;
int paloCarta;
string nombrePalo;
string nombreCarta;
int puntosCarta;
int contadorFalse;


//Funciones
//Rellenar array repetidas
void rellenarRepetidas() {
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 13; j++)
		{
			arrayRepetidas[i][j] = true;
		}
	}
}
//Intro
void intro() {
	cout << "Bienvenido a la mesa de BlackJack. Cual es su nombre?" << endl;
	cin >> nombreJugador;
	cout << "Tome asiento " << nombreJugador << ". La partida va a empezar." << endl;
}
//lanzar Cartas
void lanzarCartas() {
	paloCarta = rand() % 4;
	valorCarta = rand() % 13;
	arrayRepetidas[paloCarta][valorCarta];
	if (arrayRepetidas[paloCarta][valorCarta] == true)
	{
		arrayRepetidas[paloCarta][valorCarta] = false;
	}
	else
	{
		contadorFalse = 0;
		while (arrayRepetidas[paloCarta][valorCarta] == false)
		{
			paloCarta = rand() % 4;
			valorCarta = rand() % 13;
			contadorFalse++;
			if (contadorFalse > 52)
			{
				cout << "Procedemos a recargar la baraja. Un momento por favor." << endl;
				Sleep(3000);
				for (size_t i = 0; i < 4; i++)
				{
					rellenarRepetidas();
				}
				
			}
		}
		arrayRepetidas[paloCarta][valorCarta] = false;
	}
}
//Reconocer Cartas
void reconocerPalo() {
	if (paloCarta == 0)
	{
		nombrePalo = "Diamantes";
	}
	else if (paloCarta == 1)
	{
		nombrePalo = "Corazones";
	}
	else if (paloCarta == 2)
	{
		nombrePalo = "Treboles";
	}
	else
	{
		nombrePalo = "Picas";
	}
}
//Reconocer valor real carta
void reconocerCarta () {
	if (valorCarta == 0)
	{
		nombreCarta = "As";
	}
	else if (valorCarta == 10)
	{
		nombreCarta = "J";
	}
	else if (valorCarta == 11)
	{
		nombreCarta = "Q";
	}
	else if (valorCarta == 12)
	{
		nombreCarta = "K";
	}
	else
	{
		nombreCarta = to_string (valorCarta + 1);
	}
}
//Mostrar carta
void mostrarCarta() {
	cout << "Ha salido " << nombreCarta << " de " << nombrePalo << endl;

}
//Puntos de la Carta
void puntosCartasJugador() {
	if (valorCarta == 0)
	{
		if (puntosJugador + 11 > 21)
		{
			puntosCarta = 1;
		}
		else
		{
			cout << "Cuantos puntos quieres para tu As (1 u 11)?" << endl;
			cin >> eleccionAs;
			if (eleccionAs == 1)
			{
				puntosCarta = 1;
			}
			else
			{
				puntosCarta = 11;
			}

		}
	}
	else if (valorCarta == 10 || valorCarta == 11 || valorCarta == 12)
	{
		puntosCarta = 10;
	}
	else
	{
		puntosCarta = valorCarta + 1;
	}
}

void puntosCartasBanca() {
	if (valorCarta == 0)
	{
		if (puntosBanca + 11 > 21)
		{
			puntosCarta = 1;
		}
		else
		{
			puntosCarta = 11;
		}
	}
	else if (valorCarta == 10 || valorCarta == 11 || valorCarta == 12)
	{
		puntosCarta = 10;
	}
	else
	{
		puntosCarta = valorCarta + 1;
	}
}
//Calcular y mostrar puntos
void calcularPuntos(int& puntos, string& nombre) {
	puntos += puntosCarta;
	if (nombre == nombreJugador)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << nombre << " tiene un total de " << puntos << " puntos." << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << nombre << " tiene un total de " << puntos << " puntos." << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

//Jugador consigue 21 puntos
void jugador21() {
	cout << "Felicidades " << nombreJugador << ". Le toca a la banca." << endl;
	while (puntosBanca < puntosJugador)
	{
		Sleep(1500);
		lanzarCartas();
		reconocerPalo();
		reconocerCarta();
		mostrarCarta();
		puntosCartasBanca();
		calcularPuntos(puntosBanca, nombreBanca);
	}
	if (puntosBanca == 21)
	{
		cout << nombreBanca << " empata." << endl;
	}
	else
	{
		cout << nombreBanca << " pierde. Felicidades " << nombreJugador << endl;
	}
}
//Resultado banca
void resultadoBanca() {
	if (puntosBanca > puntosJugador &&  puntosBanca <= 21)
	{
		cout << nombreBanca << " ha ganado." << endl;
	}
	else if (puntosBanca > 21)
	{
		cout << nombreBanca << " pierde." << endl;
	}
	else if (puntosBanca == puntosJugador)
	{
		cout << nombreBanca << " ha empatado." << endl;
	}
	
}

//Volver a jugar
void volverJugar() {
	cout << "Quieres volver a jugar? (si o no)" << endl;
	cin >> eleccionVolver;
	if (eleccionVolver == "si")
	{
		empezar = true;
		puntosJugador = 0;
		puntosBanca = 0;
		eleccionJugador;
		estadoJugador = true;
		estadoBanca = true;
	}
	else if (eleccionVolver == "no")
	{
		cout << "Gracias por jugar con nosotros. Hasta la proxima " << nombreJugador << "." << endl;
		empezar = false;
	}
	else
	{
		cout << "Debes responder si o no." << endl;
	}
}

int main()
{
	srand(time(NULL));
	rellenarRepetidas();


	intro();

	while (empezar == true)
	{
		for (size_t i = 0; i < 2; i++)
		{
			Sleep(1500);
			lanzarCartas();
			reconocerPalo();
			reconocerCarta();
			mostrarCarta();
			puntosCartasJugador();
			calcularPuntos(puntosJugador, nombreJugador);
		}
		Sleep(1500);
		lanzarCartas();
		reconocerPalo();
		reconocerCarta();
		mostrarCarta();
		puntosCartasBanca();
		calcularPuntos(puntosBanca, nombreBanca);
		if (puntosJugador == 21)
		{
			jugador21();
		}
		else
		{
			while (puntosJugador < 21 && estadoJugador == true)
			{
				cout << nombreJugador << " quiere otra carta? (si o no)" << endl;
				cin >> eleccionJugador;
				if (eleccionJugador == "si")
				{
					Sleep(1500);
					lanzarCartas();
					reconocerPalo();
					reconocerCarta();
					mostrarCarta();
					puntosCartasJugador();
					calcularPuntos(puntosJugador, nombreJugador);
				}
				else if (eleccionJugador == "no")
				{
					estadoJugador = false;
				}
				else
				{
					cout << "Debe responder si o no." << endl;
				}
			}
			if (puntosJugador == 21)
			{
				jugador21();
			}
			else if (puntosJugador > 21)
			{
				cout << "Lo siento " << nombreJugador << ". Has perdido." << endl;
			}
			else
			{
				cout << "Es el turno de la " << nombreBanca << endl;
				while (puntosBanca < puntosJugador && puntosBanca < 21 && estadoBanca == true)
				{
					Sleep(1500);
					lanzarCartas();
					reconocerPalo();
					reconocerCarta();
					mostrarCarta();
					puntosCartasBanca();
					calcularPuntos(puntosBanca, nombreBanca);
					if (puntosBanca > puntosJugador && puntosBanca < 21)
					{
						estadoBanca = false;
					}
				}
				resultadoBanca();
			}
		}
		volverJugar();
	}	
}

