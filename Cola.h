#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <cstdlib>
#define MAX 100

using namespace std;

template <class T>
class Cola
{
	private:
		T EspacioCola[MAX];
		int Frente;
		int Final;
		
	public:
		Cola();
		void InsertarCola(T);
		void EliminarCola(T*);
		int operator + (T);
		int operator - (T*);
		int ColaLlena();
		int ColaVacia();
};

template <class T>
Cola<T>::Cola() 
{
	Frente = -1;
	Final = -1;
}

template <class T>
void Cola<T>::InsertarCola(T Dato)
{
	EspacioCola[++Final] = Dato;
	if(Final == 0)
		Frente = 0;
}

template <class T>
void Cola<T>::EliminarCola(T *Dato)
{
	*Dato = EspacioCola[Frente];
	if(Frente == Final)
	{
		Frente = -1;
		Final = -1;
	}
	else
		Frente++;
}

template <class T>
int Cola<T>::ColaLlena()
{
	if(Final == MAX -1)
		return 1;
	else
		return 0;
}

template <class T>
int Cola<T>::ColaVacia()
{
	if(Frente == -1)
		return 1;
	else
		return 0;
}

template <class T>
int Cola<T>::operator + (T Dato)
{
	int Res = 0; 
	if(ColaLlena() != 1)
	{
		EspacioCola[++Final] = Dato;
		if(Final == 0)
			Frente = 0;
		Res = 1;
	}
	
	return Res;
}

template <class T>
int Cola<T>::operator - (T *Dato)
{
	int Res = 0;
	
	if(!ColaVacia())
	{
		*Dato = EspacioCola[Frente];
		if(Frente == Final)
		{
			Frente = -1;
			Final = -1;
		}
		else
			Frente++;
			
		Res = 1;
	}
	
	return Res;
}

#endif
