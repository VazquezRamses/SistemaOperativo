#ifndef PAGINA_H
#define PAGINA_H

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h> 
#include <string.h>

using namespace std;

class Pagina
{
	private:
		string id;
		string Estado;
		int tam;
		char Longitud[4];
		
	public:
		Pagina();
		void Llenar();
		void setId(string id);
		string getID_Ocupado();
		void setEstado(string status);
		string getEstado();
		void setLongitud(int t);
		void InsertarMarco(int t, string id, string Estado);
		void MostrarLongitud();
};

#endif
