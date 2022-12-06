#include "Pagina.h"

Pagina::Pagina()
{
	id = "Libre";
	tam = 4;
	Llenar();
}

void Pagina::Llenar()
{
	tam = 4;
	
	for(int i=0; i<tam; i++)
		Longitud[i] = '-';	
}

void Pagina::setId(string id)
{
	this->id = id;
}

string Pagina::getID_Ocupado()
{
	return id;
}

void Pagina::setEstado(string status)
{
	this->Estado = status;
}

string Pagina::getEstado()
{
	return Estado;
}

void Pagina::setLongitud(int t)
{
	tam = t;
	
	for(int i=0; i<tam; i++)
		Longitud[i] = '*';
}

void Pagina::InsertarMarco(int t, string id, string Estado)
{
	setId(id);
	setLongitud(t);
	setEstado(Estado);
}

void Pagina::MostrarLongitud()
{
	for(int i=0; i<tam; i++)
		cout<<Longitud[i]<<" ";
}

