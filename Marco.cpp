#include "Marco.h"

Marco::Marco()
{
	coord = {0,0};
	Disponibles = 50;
	Posicion = 0;
	LlenarInicio();
}

void Marco::LlenarInicio()
{
	Disponibles = Disponibles - 4;
	
	for(int i=46; i<50; i++)
		Pag[i].InsertarMarco(4, "SO", "SO");
}

void Marco::MostrarMemoria()
{
	//111
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"  [TABLA DE PAGINAS] \t   [Marcos Disponibles]: "<<Disponibles<<endl;
	cout<<"--------------------------------------------------------"<<endl;
	cout<<" Marco  /   Espacio Ocupado   /     ID     /   Estado   "<<endl;
	cout<<"--------------------------------------------------------"<<endl;
	
	for(int i=0; i<50; i++)
	{
		cout<<"   "<<i<<"\t\t "; Pag[i].MostrarLongitud();
		gotoxy(36, 5+i);
		cout<<Pag[i].getID_Ocupado();
		gotoxy(46, 5+i);
		cout<<Pag[i].getEstado()<<endl;
	}
}

void Marco::Mostrar_Principal()
{
	//111
	gotoxy(110, 0);
	cout<<"--------------------------------------------------------"<<endl;
	gotoxy(110, 1);
	cout<<"  [TABLA DE PAGINAS] \t   [Marcos Disponibles]: "<<Disponibles<<endl;
	gotoxy(110, 2);
	cout<<"--------------------------------------------------------"<<endl;
	gotoxy(110, 3);
	cout<<" Marco  /   Espacio Ocupado   /     ID     /   Estado   "<<endl;
	gotoxy(110, 4);
	cout<<"--------------------------------------------------------"<<endl;
	
	for(int i=0; i<50; i++)
	{
		gotoxy(110, 5+i);
		cout<<"   "<<i<<"\t      "; Pag[i].MostrarLongitud();
		gotoxy(146, 5+i);
		cout<<Pag[i].getID_Ocupado();
		gotoxy(155, 5+i);
		cout<<Pag[i].getEstado()<<endl;
	}
	
}

bool Marco::Espacio_Disponible(int tamano)
{	
	int division, residuo, total_pag;
	
	division = tamano / 4;
	residuo = tamano % 4;
	total_pag = division;
	
	if(residuo > 0)
		total_pag++;
		
	if(total_pag <= Disponibles)
		return true;
	else
		return false;
}

void Marco::Insertar(int id, int tamano, string Estado)
{
	string New_id;
	int division, residuo, total_pag;
	bool incompleto = false;
	
	New_id = to_string(id);
	
	division = tamano / 4;
	residuo = tamano % 4;
	total_pag = division;
	
	if(residuo > 0)
	{
		total_pag++;
		incompleto = true;
	}
		
	Disponibles -= total_pag;
		
	//Insertar
	while(total_pag != 0)
	{
		if(Pag[Posicion].getID_Ocupado() == "Libre")
		{
			if(total_pag == 1 && incompleto == true)
				Pag[Posicion].InsertarMarco(residuo, New_id, Estado);
			else
				Pag[Posicion].InsertarMarco(4, New_id, Estado);
				
			total_pag--;
		}

		Posicion++;
		
		if(Posicion == 46)
			Posicion = 0;
	}
	//Termina Insertar

}

void Marco::Cambio_Estado(int id, string Estado)
{
	string id_Cambio;
	id_Cambio = to_string(id);
	
	for(int i=0; i<46; i++)
	{
		if(Pag[i].getID_Ocupado() == id_Cambio)
			Pag[i].setEstado(Estado);
	}
}

void Marco::LiberarEspacio(int id)
{
	string id_Liberar;
	id_Liberar = to_string(id);
	int Cont = 0;
	
	for(int i=0; i<46; i++)
	{
		if(Pag[i].getID_Ocupado() == id_Liberar)
		{
			Pag[i].setEstado(" "); //INICIALIZAMOS EN LIBRE EL ESTADO
			Pag[i].setId("Libre"); // EL ID
			Pag[i].Llenar(); // EL ESPACIO LIBERADO LO COLOCAMOS CON - 
			Cont++;
		}	
	}
	
	Disponibles += Cont;
}

void Marco::gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	
}
