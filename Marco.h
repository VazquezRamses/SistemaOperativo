#ifndef MEMORIA_H
#define MEMORIA_H

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h> 
#include <string.h>
#include "Pagina.h"


using namespace std;

class Marco
{
	private: 
		int Disponibles;
		int Posicion;
		Pagina Pag[50];
		COORD coord;
		
	public:
		Marco();
		void LlenarInicio();
		void MostrarMemoria();
		void Mostrar_Principal();
		void Insertar(int id, int tamano, string Estado);
		bool Espacio_Disponible(int tamano);
		void Cambio_Estado(int id, string Estado);
		void LiberarEspacio(int id);
		void gotoxy(int x, int y);
		
};

#endif
