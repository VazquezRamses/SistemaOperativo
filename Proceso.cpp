#include "Proceso.h"

Proceso::Proceso()
{
	ID = 0;
	coord = {0,0};
	ID = 0;
	M = 0;
	Estatus = "Terminado";
	TEjecutado = 0;
	TBloqueado = 0;
	TRespuesta = -1;
	TFinal = 0;
	TRetorno = 0;
}

void Proceso::setNombre(char n[])
{
	strcpy(Nombre, n);
}

void Proceso::setID(int id)
{
	ID = id;
}

int Proceso::getID()
{
	return ID;
}

void Proceso::setTME(int tiempo)
{
	TME = tiempo;
	TRestante = TME;
}

int Proceso::getTME()
{
	return TME;
}

void Proceso::setTiempos(int TE, int TR)
{
	TEjecutado = TE;
	TRestante = TR;
}

int Proceso::getTE()
{
	return TEjecutado;
}

int Proceso::getTR()
{
	return TRestante;
}

void Proceso::setTiempoBloqueado(int Modulo)
{
	if(Modulo == 1)
	{
		TBloqueado = 0;	
	}
	else
	{
		TBloqueado++;	
	}
	
}

int Proceso::getTiempoBloqueado()
{
	return TBloqueado;
}

void Proceso::setLote(int L)
{
	Lote = L;	
}

int Proceso::getLote()
{
	return Lote;
}

void Proceso::setM(int op)
{
	M = op;	
}

int Proceso::getM()
{
	return M;
}

void Proceso::setEstatus(string E)
{
	Estatus = E;
}

string Proceso::getEstatus()
{
	return Estatus;
}

int Proceso::getOperacion()
{
	return Operacion;
}

int Proceso::getNum1()
{
	return Val1;
}

int Proceso::getNum2()
{
	return Val2;
}

void Proceso::setOperacion2(int Op, int Num1, int Num2)
{
	Operacion = Op;
	Val1 = Num1;
	Val2 = Num2;
	
	switch(Operacion)
	{
		case 0:
			Res = 0;
		break;
		
		case 1:
			{
				Noperacion = "SUMA";
				Res = Val1 + Val2;
			}
		break;
		
		case 2:
			{
				Noperacion = "RESTA";
				Res = Val1 - Val2;
			}
		break;
		
		case 3:
			{
				Noperacion = "MULTIPLICACION";
				Res = Val1 * Val2;
			}
		break;
		
		case 4:
			{
				Noperacion = "DIVISION";
				Res = Val1 / Val2;
			}
		break;
		
		case 5:
			{
				Noperacion = "RESIDUO";
				Res = Val1 % Val2;
			}
		break;
	}
}


void Proceso::Mostrar(int NProceso)
{
	gotoxy(NProceso*27, 3);
	cout<<"--------------------------"<<endl;
	gotoxy(NProceso*27, 4);
	cout<<"ID: "<<ID<<endl;
	gotoxy(NProceso*27, 5);
	cout<<"Tiempo Maximo Estimado: "<<TME<<endl;
	gotoxy(NProceso*27, 6);
	cout<<"Tiempo En Ejecucion: "<<TEjecutado<<endl;
	gotoxy(NProceso*27, 7);
	cout<<"Tamaño: "<<Tam<<endl;
	gotoxy(NProceso*27, 8);
	cout<<"--------------------------"<<endl;
}

void Proceso::MostrarReinicio()
{
	gotoxy(27, 3);
	cout<<"                                                                        "<<endl; 
	gotoxy(27, 4);
	cout<<"                                                                        "<<endl; 
	gotoxy(27, 5);
	cout<<"                                                                        "<<endl; 
	gotoxy(27, 6);
	cout<<"                                                                        "<<endl; 
	gotoxy(27, 7);
	cout<<"                                                                        "<<endl; 
}

void Proceso::MostrarEjecucion()
{
	gotoxy(0, 12);
	cout<<"--------------------------"<<endl;
	gotoxy(0, 13);
	cout<<"ID programa: "<<ID<<endl;
	gotoxy(0, 14);
	cout<<"Operacion: "<<Noperacion<<endl;
	gotoxy(0, 15);
	cout<<"Tiempo Maximo Estimado: "<<TME<<endl;
	gotoxy(0, 16);
	cout<<"Tamaño: "<<Tam<<endl;
	gotoxy(0, 17);
	cout<<"--------------------------"<<endl;
}

void Proceso::LimpiarEjecucion()
{
	gotoxy(0, 9);
	cout<<"                                                                                         "<<endl;
	gotoxy(0, 10);
	cout<<"                                                                      "<<endl;
	gotoxy(0, 11);
	cout<<"                                                                                           "<<endl;
	gotoxy(0, 12);
	cout<<"                            "<<endl;
	gotoxy(0, 13);
	cout<<"                            "<<endl;
	gotoxy(0, 14);
	cout<<"                            "<<endl;
	gotoxy(0, 15);
	cout<<"                            "<<endl;
	gotoxy(0, 16);
	cout<<"                           "<<endl;
	gotoxy(0, 17);
	cout<<"                           "<<endl;
}


void Proceso::MostrarFinal(int NProceso, int Y)
{
	gotoxy(NProceso*28, Y+29);
	cout<<"-------------------------"<<endl;
	gotoxy(NProceso*28, Y+30);
	cout<<"ID programa: "<<ID<<endl;
	gotoxy(NProceso*28, Y+31);
	cout<<"Operacion: "<<Noperacion<<endl;
	gotoxy(NProceso*28, Y+32);
	cout<<"Valor 1: "<<Val1<<endl;
	gotoxy(NProceso*28, Y+33);
	cout<<"Valor 2: "<<Val2<<endl;
	gotoxy(NProceso*28, Y+34);
	cout<<"Resultado: "<<Res<<endl;
	gotoxy(NProceso*28, Y+35);
	cout<<"Tiempo Maximo Estimado: "<<TME<<endl;
	gotoxy(NProceso*28, Y+36);
	cout<<"Estatus: "<<Estatus<<endl;
	gotoxy(NProceso*28, Y+37);
	cout<<"Tamaño: "<<Tam<<endl;
	gotoxy(NProceso*28, Y+38);
	cout<<"-------------------------"<<endl;
}

void Proceso::MostrarBloqueado(int X, int Y)
{
	gotoxy(X*28, 20+Y);
	cout<<"-------------------------"<<endl;
	gotoxy(X*28, 21+Y);
	cout<<"ID programa: "<<ID<<endl;
	gotoxy(X*28, 22+Y);
	cout<<"Tiempo Bloqueado: "<<TBloqueado<<endl;
	gotoxy(X*28, 23+Y);
	cout<<"-------------------------"<<endl;
}

void Proceso::LimpiarBloqueado(int X, int Y)
{
	gotoxy(X*28, 20+Y);
	cout<<"                         "<<endl;
	gotoxy(X*28, 21+Y);
	cout<<"                         "<<endl;
	gotoxy(X*28, 22+Y);
	cout<<"                         "<<endl;
	gotoxy(X*28, 23+Y);
	cout<<"                         "<<endl;
}

void Proceso::gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	
}

void Proceso::setLlegada(int TiempoLlegada)
{
	this->Tllegada = TiempoLlegada;
}

void Proceso::setSalida(int TiempoSalida)
{
	this->TFinal = TiempoSalida;
}

void Proceso::setRespuesta(int TiempoRespuesta)
{
	this->TRespuesta = TiempoRespuesta - Tllegada;
}

void Proceso::CalcularTiempos()
{	
	TRetorno = TFinal - Tllegada;
	TEspera = TRetorno - TEjecutado; 
}

void Proceso::MostrarTiempos(int NProceso, int Y) 
{
	gotoxy(NProceso*28, Y+3);
	cout<<"--------------------------"<<endl;
	gotoxy(NProceso*28, Y+4);
	cout<<"ID programa: "<<ID<<endl;
	gotoxy(NProceso*28, Y+5);
	cout<<"Tiempo de LLEGADA: "<<Tllegada<<endl;
	gotoxy(NProceso*28, Y+6);
	cout<<"Tiempo de SALIDA: "<<TFinal<<endl;
	gotoxy(NProceso*28, Y+7);
	cout<<"Tiempo de RETORNO: "<<TRetorno<<endl;
	gotoxy(NProceso*28, Y+8);
	cout<<"Tiempo de RESPUESTA: "<<TRespuesta<<endl;
	gotoxy(NProceso*28, Y+9);
	cout<<"Tiempo de ESPERA: "<<TEspera<<endl;
	gotoxy(NProceso*28, Y+10);
	cout<<"Tiempo de Servicio: "<<TEjecutado<<endl;
	gotoxy(NProceso*28, Y+11);
	cout<<"--------------------------"<<endl;
}

void Proceso::MostrarTabla(int y, int ContadorGlobal)
{
	string Tf = "-", Tret = "-", Tres = "-", Tser = "-", estado = "Terminado", resultado = "-", TB = "-";
	string TE = "-", Trestante = "-";
	
	if(Estatus == "Terminado" || Estatus == "Error")
	{	
		TE = to_string(TEspera);
	}
	else
	{
		TEspera = ContadorGlobal - Tllegada - TEjecutado;	
		TE = to_string(TEspera);
	}
	
	//if(Estatus == "Ejecucion")
		if(TRestante != 0)
			Trestante = to_string(TRestante);
		
	if(TFinal != 0)
		Tf = to_string(TFinal);
	
	if(Estatus == "Terminado")
		resultado = to_string(Res);
	
	if(TRetorno != 0)
		Tret = to_string(TRetorno);
	
	if(TRespuesta != -1)
		Tres = to_string(TRespuesta);
		
	if(TEjecutado != 0)
		Tser = to_string(TEjecutado);
	
	if(TBloqueado != 0)
		TB = to_string(TBloqueado);
	
	
		
	gotoxy(0, 5+y);
	cout<<ID;
	gotoxy(7, 5+y);
	cout<<Noperacion;
	gotoxy(24, 5+y);
	cout<<Val1;
	gotoxy(40, 5+y);
	cout<<Val2;
	gotoxy(56, 5+y);
	cout<<resultado;
	gotoxy(72, 5+y);
	cout<<Estatus;
	gotoxy(88, 5+y);
	cout<<TME<<" \t"<<Tllegada<<" \t";
	cout<<Tf<<" \t"<<TE<<" \t"<<Tres<<" \t"<<Tret<<" \t"<<Tser<<" \t"<<Trestante<<" \t"<<TB<<endl;
}

void Proceso::MostrarNuevo(int y)
{
	gotoxy(0, 5+y);
	cout<<ID;
	gotoxy(7, 5+y);
	cout<<"-";
	gotoxy(24, 5+y);
	cout<<"-";
	gotoxy(40, 5+y);
	cout<<"-";
	gotoxy(56, 5+y);
	cout<<"-";
	gotoxy(72, 5+y);
	cout<<Estatus;
	gotoxy(88, 5+y);
	cout<<"-"<<" \t"<<"-"<<" \t";
	cout<<"-"<<" \t"<<"-"<<" \t"<<"-"<<" \t"<<"-"<<" \t"<<"-"<<" \t"<<"-"<<" \t-"<<endl;	
}

void Proceso::setTam(int tamano)
{
	this->Tam = tamano;
}

int Proceso::getTam()
{
	return this->Tam;
}

