#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h> 
#include <ctime>
#include <string.h>
#include "Proceso.h"
#include "Cola.h"
#include "Marco.h"
#include <clocale>
#include <fstream> //PARA UTILIZAR ARCHIVOS 

using namespace std;

COORD coord = {0,0};

void gotoxy(int x, int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	
}

void Inicio(int cantidad);
void MostrarTodos(Cola<Proceso> Memoria, int CantidadListos); //MOSTRAMOS LOS PROCESOS QUE ESTAN EN MEMORIA 
int Calcular(); //CALCULAMOS LOS PROCESOS QUE ESTAN EN MEMORIA
void EjecucionCola(Proceso EnEjecucion, int Pendiente, int Listos);
void TerminadosCola();
void Limpiar();
void LimpiarBloqueado();
void Limpiar_TablaMemoria();
void CargarNuevos();
void FinalCola();
Proceso CrearProceso(int id);
void LlenarTabla(Proceso EnEjecucion, int final);
void TablaProcesos(Proceso EnEjecucion, int final);
void LimpiarBloqueado1();
void CrearArchivo(); //PARA LA CREACION DEL ARCHIVO
void Insertar_Suspendido(int id); //PARA INSERTAR LOS DATOS
void Eliminar_Suspendido(int id); //PARA BORRAR DEL ARCHIVO

//VARIABLES GLOBALES
int ContGlobal = 0,  terminados = 0, ProcesoI = 0, Indice, NumeroPendientes, Listos, Nterminados = 0, ID, Quantum;
int ContadorSuspendidos = 0;
int IDbloqueados[100];
Cola <Proceso> Memoria; //COLA DE MEMORIA
Cola <Proceso> CListos; //COLA DE PROCESOS QUE ESPERAN ENTRAR EN MEMORIA
Cola <Proceso> CTerminados; //COLA DE PROCESOS TERMINADOS
Cola <Proceso> CBloqueados; //COLA PROCESOS TERMINADOS 
Cola <Proceso> Tabla; //COLA Tabla de prcesos
Cola <Proceso> Suspendidos; //COLA BLOQUEADOS Y SUSPENDIDOS
Marco M;

int main() 
{
	setlocale(LC_CTYPE,"Spanish");
	CrearArchivo();
	int Cantidad;

	cout<<"---------------------------------------------------------"<<endl;
	cout<<"SIMULACION PLANIFICADOR ROUND ROBIN - [SUSPENDIDOS]"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Introduce la cantidad de procesos a ejectutar: ";
	cin>>Cantidad;
	cout<<"Introduce la cantidad de quatum para el procesador: ";
	cin>>Quantum;
	
	Inicio(Cantidad);
	
}

void Inicio(int Cantidad)
{
	int CantidadP;
	int tiempo, LoteE, NumeroLotes, Cargar;
	bool Prueba;
	
	Proceso P[Cantidad];
	Proceso Nuevo;
	
	srand(time(NULL)); //SEMILLA PARA QUE NO SE REPITAN SIEMPRE LOS NUMEROS ALEATORIOS
	
	for(int i=0; i<Cantidad; i++)
	{	
		ID++;
		
		Nuevo = CrearProceso(ID);
		Prueba = M.Espacio_Disponible(Nuevo.getTam());
		
		if(Prueba)
		{
			Nuevo.setLlegada(ContGlobal);
			Nuevo.setEstatus("Listo");
			M.Insertar(Nuevo.getID(), Nuevo.getTam(), "---------");
			Memoria.InsertarCola(Nuevo);	
		}
		else
		{
			Nuevo.setEstatus("Nuevo");
			CListos.InsertarCola(Nuevo);
			NumeroPendientes++;
		}
		
	}
	
	cout<<"\nGenerando "<<Cantidad<<" PROCESOS, con un QUANTUM de "<<Quantum<<"... Espere un momento ;)\n\n"<<endl;
	
	system("pause");
	system("cls");
		
	
	Listos = Calcular();
	Proceso EnEjecucion;
	
	while(Memoria.ColaVacia() == 0) //Mientras la cola (MEMORIA) no este vacia  
	{	
		if(Memoria.ColaVacia() == 1)
			break;
			
		MostrarTodos(Memoria, Listos);
		Sleep(1000);
		Memoria.EliminarCola(&EnEjecucion);
		EnEjecucion.setEstatus("Ejecucion");
		//CAMBIAR ESTADO PARA QUE SE MUESTRE EN MEMORIA
		M.Cambio_Estado(EnEjecucion.getID(), EnEjecucion.getEstatus());
		Limpiar();
		MostrarTodos(Memoria, Listos);
		Sleep(1000);
		EjecucionCola(EnEjecucion, NumeroPendientes, Listos);
		Sleep(1000);
		EnEjecucion.LimpiarEjecucion();
		TerminadosCola();
		terminados = 0;
		Limpiar();
		Listos = Calcular();
			
	}
	
	gotoxy(0, 40*2);
	system("pause");
	system("cls");
	//FinalCola();
	TablaProcesos(EnEjecucion, 1);
	
}


int Calcular()
{
	Cola <Proceso> MostrarCola;
	MostrarCola = Memoria;
	Proceso P;
	int cantidad = 0;
	
	while(MostrarCola.ColaVacia() != 1)
	{
		MostrarCola.EliminarCola(&P);	
		if(P.getID() != 0)
			cantidad++;
	}	
		
	
	return cantidad;
}

void Limpiar()
{
	gotoxy(0, 3);
	cout<<"                                                                                                                                          "<<endl; 
	gotoxy(0, 4);
	cout<<"                                                                                                                                          "<<endl; 
	gotoxy(0, 5);
	cout<<"                                                                                                                                           "<<endl; 
	gotoxy(0, 6);
	cout<<"                                                                                                                                           "<<endl; 
	gotoxy(0, 7);
	cout<<"                                                                                                                                           "<<endl; 
	gotoxy(0, 8);
	cout<<"                                                                                                                                           "<<endl; 
	
}


void MostrarTodos(Cola<Proceso> Memoria, int CantidadListos)
{
	Cola <Proceso> MostrarCola;
	Cola <Proceso> MostrarCola2;
	Cola <Proceso> MostrarCola3;
	
	Proceso P, Nuevo;
	MostrarCola = Memoria;
	MostrarCola2 = CListos;
	MostrarCola3 = Suspendidos;
	
	int NProceso = 0, N=4, ID_Nuevo = 0, Tam_Nuevo = 0, ID_Suspendido = 0, Tam_Suspendido = 0;
	
	if(MostrarCola2.ColaVacia() != 1)
	{
		MostrarCola2.EliminarCola(&Nuevo);
		ID_Nuevo = Nuevo.getID();
		Tam_Nuevo = Nuevo.getTam();
	}
	
	if(MostrarCola3.ColaVacia() != 1)
	{
		MostrarCola3.EliminarCola(&Nuevo);
		ID_Suspendido = Nuevo.getID();
		Tam_Suspendido = Nuevo.getTam();
	}
	
	gotoxy(0, 1);
	cout<<"                                                                                                                 "<<endl;
	
	gotoxy(0, 0);
	cout<<"-------------------[NUEVOS]: "<<NumeroPendientes<<" -----------------[SUSPENDIDOS]: "<<ContadorSuspendidos<<endl;
	gotoxy(0, 1);
	cout<<"Listos: "<<CantidadListos<<"\tID: "<<ID_Nuevo<<"  Tamaño: "<<Tam_Nuevo;
	cout<<"\t\tID: "<<ID_Suspendido<<"  Tamaño: "<<Tam_Suspendido<<endl;
	gotoxy(0, 2);
	cout<<"----------------------------------------------------------------------[VALOR QUANTUM]: "<<Quantum<<endl;
	
	int mostrar = 0, cont = 5;
	while(MostrarCola.ColaVacia() != 1)
	{
		MostrarCola.EliminarCola(&P);
		P.Mostrar(mostrar);
		mostrar++;
		cont--;
		
		if(cont == 1)
			break;
	}
				
	
}


void EjecucionCola(Proceso EnEjecucion, int Pendiente, int Listos)
{
	int tiempo, tiempoE, tiempoR, tiempoB = 1, TiempoMax, AuxQuantum = 0;
		
	tiempoR = EnEjecucion.getTR(); //SETEAMOS EL TIEMPO RESTANTE
	TiempoMax = EnEjecucion.getTME();
	if(EnEjecucion.getM() == 0)
	{
		EnEjecucion.setRespuesta(ContGlobal);	
		EnEjecucion.setM(1);
	}
	
	//Iniciamos el contador con el tiempo en que lleva en ejecucion / tiempo transcurrido
	//Hasta que sea menor o igual al tiempo estimado
	for(tiempoE = EnEjecucion.getTE(); tiempoE <= TiempoMax; tiempoE++, tiempoR--, ContGlobal++, AuxQuantum++)
	{
		M.Mostrar_Principal();
		gotoxy(0, 9);
		cout<<"-----------------------[PROCESOS EN EJECUCION]------------------------"<<endl;
		gotoxy(0, 10);
		cout<<"Tiempo Transcurrido: "<<tiempoE<<"\t\t\t\tTiempo Restante: "<<tiempoR<<endl;
		gotoxy(0, 11);
		cout<<"----------------------------------------------------------------------[QUANTUM]: "<<AuxQuantum<<endl;
		
		gotoxy(0, 26);
		cout<<"-------------------------------[PROCESOS TERMINADOS]-------------------------------"<<endl;
		gotoxy(0, 27);
		cout<<"\t\t\t        Contador Global: "<<ContGlobal<<endl;
		gotoxy(0, 28);
		cout<<"---------------------------------------------------------------------------------"<<endl;
		
		EnEjecucion.MostrarEjecucion();
		Sleep(1000);
		
		if(AuxQuantum == Quantum && tiempoE != TiempoMax)
		{
			EnEjecucion.setTiempos(tiempoE, tiempoR);
			EnEjecucion.setEstatus("Listo");
			//CAMBIO DE ESTADO EN LA MEMORIA 
			M.Cambio_Estado(EnEjecucion.getID(), "---------");
			Memoria.InsertarCola(EnEjecucion);
			Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
			M.Mostrar_Principal(); //LA MOSTRAMOS
			return;
		}
			
		
		if(ProcesoI > 0)
		{
			Proceso Bloqueado;
		
			gotoxy(0, 18);
			cout<<"-----------------------[PROCESOS BLOQUEADOS]------------------------"<<endl;
			gotoxy(0, 19);
			cout<<"----------------------------------------------------------------------"<<endl;
			for(int i=0; i<ProcesoI; i++)
			{
				if(CBloqueados.ColaVacia() != 1)
				{
					CBloqueados.EliminarCola(&Bloqueado);
					Bloqueado.MostrarBloqueado(ProcesoI-1, 0);
					Bloqueado.setTiempoBloqueado(0);
					
					if(Bloqueado.getTiempoBloqueado() == 9)
					{
						Bloqueado.setTiempoBloqueado(1);
						Bloqueado.setEstatus("Listo");
						M.Cambio_Estado(Bloqueado.getID(), "---------");
						Bloqueado.LimpiarBloqueado(ProcesoI-1, 0);
						Memoria.InsertarCola(Bloqueado);
						ProcesoI--;
						Limpiar();
						MostrarTodos(Memoria, Listos);
						Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
						M.Mostrar_Principal(); //LA MOSTRAMOS
					}	
					else
						CBloqueados.InsertarCola(Bloqueado);
				}
	
			}	
		}
			
		if(kbhit())
		{
			char tecla = getch();
			if(tecla == 'i')
			{
				IDbloqueados[ProcesoI] = EnEjecucion.getID();
				EnEjecucion.setTiempos(tiempoE, tiempoR); //Guardamos los tiempos del proceso interrumpido
				EnEjecucion.setEstatus("Bloqueado");
				M.Cambio_Estado(EnEjecucion.getID(), EnEjecucion.getEstatus());
				CBloqueados.InsertarCola(EnEjecucion); //Guardamos el proceso en bloqueados
				terminados = 0;
				ProcesoI++; //BANDERA
				return;
			}
				
			if(tecla == 'e')
			{
				EnEjecucion.setSalida(ContGlobal);
				EnEjecucion.setEstatus("Error");
				EnEjecucion.setTiempos(tiempoE, tiempoR); //Guardamos los tiempos
				int val1 = EnEjecucion.getNum1();
				int val2 = EnEjecucion.getNum2();
				EnEjecucion.setOperacion2(0, val1, val2); 
				EnEjecucion.CalcularTiempos();
				M.LiberarEspacio(EnEjecucion.getID()); //LIBERAMOS EL ESPACIO EN MEMORIA
				CTerminados.InsertarCola(EnEjecucion);	
				terminados = 1;
				Nterminados++;
				Listos--;
				CargarNuevos();
				Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
				M.Mostrar_Principal(); //LA MOSTRAMOS
				return; 
			}
				
			if(tecla == 'p')
			{
				while(tecla != 'c')
				{
					cin.get();
					tecla = getch();
				}	
			}
			
			if(tecla == 'n')
			{
				Proceso Nuevo;
				bool Prueba;
				ID++;
				Nuevo = CrearProceso(ID);
				Prueba = M.Espacio_Disponible(Nuevo.getTam());
				//ACOMODAR ESTA PARTE 
				if(CListos.ColaVacia() == 1)
				{
					if(Prueba == false)
					{
						Nuevo.setEstatus("Nuevo");
						CListos.InsertarCola(Nuevo);
						NumeroPendientes++;
					}
					else
					{	
						Nuevo.setLlegada(ContGlobal);
						Nuevo.setEstatus("Listo");
						M.Insertar(Nuevo.getID(), Nuevo.getTam(), "---------");
						Memoria.InsertarCola(Nuevo);
						Listos++;
					}
				}
				else
				{
					Nuevo.setEstatus("Nuevo");
					CListos.InsertarCola(Nuevo);
					NumeroPendientes++;
				}
				
				MostrarTodos(Memoria, Listos);
			}
			
			if(tecla == 't')
			{
				while(tecla != 'c')
				{
					EnEjecucion.setTiempos(tiempoE, tiempoR); //Guardamos los tiempos
					TablaProcesos(EnEjecucion, 0);
					cin.get();
					tecla = getch();
				}	
				system("cls");
				TerminadosCola();
			}
			
			if(tecla == 'a')
			{
				while(tecla != 'c')
				{
					system("cls");
					M.MostrarMemoria();
					cin.get();
					tecla = getch();
				}	
				system("cls");
			}
			
			if(tecla == 's')
			{
				Proceso BSuspendido;
				if(CBloqueados.ColaVacia() != 1)
				{
					Listos--;
					ContadorSuspendidos++;
					CBloqueados.EliminarCola(&BSuspendido);
					BSuspendido.setEstatus("Suspendido");
					BSuspendido.LimpiarBloqueado(ProcesoI-1,0);
					ProcesoI--;
					M.LiberarEspacio(BSuspendido.getID()); //LIBERAMOS LA MEMORIA
					Insertar_Suspendido(BSuspendido.getID()); //GUARDAMOS SU ID EN EL ARCHIVO
					Suspendidos.InsertarCola(BSuspendido); //GUARDAMOS EL SUSPENDIDO
					
					for(int i=0; i<NumeroPendientes; i++)
						CargarNuevos(); //SI LA MEMORIA SE LIBERO CARGAMOS SI ES QUE EXISTEN NUEVOS
				}
			}
			
			if(tecla == 'r')
			{
				Proceso Entra, Entra2;
				bool Prueba;
				
				Cola <Proceso> ColaSuspendidos;
				ColaSuspendidos = Suspendidos;
				
				if(Suspendidos.ColaVacia() != 1)
				{
					ColaSuspendidos.EliminarCola(&Entra2);
					Prueba = M.Espacio_Disponible(Entra2.getTam());
					
					if(Prueba) //SI CABE SACAMOS EL PROCESO DE LA COLA DE NUEVOS
					{
						Suspendidos.EliminarCola(&Entra);
						Entra.setEstatus("Bloqueado"); 
						//INSERTAMOS EL PROCESO EN LA MEMORIA 
						M.Insertar(Entra.getID(), Entra.getTam(), "Bloqueado");  
						CBloqueados.InsertarCola(Entra);
						ContadorSuspendidos--;
						Listos++;	
						ProcesoI++;
						Eliminar_Suspendido(Entra.getID()); //SACAMOS SU ID DEL ARCHIVO
					}
				}
			}
			
			MostrarTodos(Memoria, Listos);	
			TerminadosCola();
			Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
			M.Mostrar_Principal(); //LA MOSTRAMOS
		}
			
		
		gotoxy(65, 10);
		cout<<"   "<<endl;
		gotoxy(20, 10);
		cout<<"   "<<endl;
	}
		
	EnEjecucion.setTiempos(tiempoE-1, tiempoR+1); //Guardamos los tiempos
	EnEjecucion.setSalida(ContGlobal-1);
	EnEjecucion.CalcularTiempos();
	EnEjecucion.setEstatus("Terminado");
	M.LiberarEspacio(EnEjecucion.getID()); //LIBERAMOS EL ESPACIO EN MEMORIA
	Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
	M.Mostrar_Principal(); //LA MOSTRAMOS
	CTerminados.InsertarCola(EnEjecucion);	
	terminados = 1;	
	Nterminados++;
	Listos--;
	CargarNuevos();
}

void CargarNuevos()
{
	Proceso Nuevo, Nuevo2;
	bool Prueba;
	Cola <Proceso> ColaNuevos;
	ColaNuevos = CListos;
	
	if(CListos.ColaVacia() != 1)
	{
		ColaNuevos.EliminarCola(&Nuevo2);
		Prueba = M.Espacio_Disponible(Nuevo2.getTam());
		
		if(Prueba) //SI CABE SACAMOS EL PROCESO DE LA COLA DE NUEVOS
		{
			CListos.EliminarCola(&Nuevo);
			Nuevo.setLlegada(ContGlobal);
			Nuevo.setEstatus("Listo"); 
			//INSERTAMOS EL PROCESO EN LA MEMORIA 
			M.Insertar(Nuevo.getID(), Nuevo.getTam(), "---------");  
			Limpiar_TablaMemoria(); //LIMPIAMOS EL ESPACIO DE LA MEMORIA
			M.Mostrar_Principal(); //LA MOSTRAMOS
			Memoria.InsertarCola(Nuevo);
			NumeroPendientes--;
			Listos++;	
		}
	}
}

void TerminadosCola()
{
	Cola<Proceso> MostrarCola;
	MostrarCola = CTerminados;
	Proceso Terminado;
	int mostrar = 0, N = 3, Y=0;
	
	while(MostrarCola.ColaVacia() != 1)
	{
		if(mostrar > N)
		{
			N = 3;
			Y+=10;
			mostrar = 0;
		}	
			
		MostrarCola.EliminarCola(&Terminado);
		Terminado.MostrarFinal(mostrar, Y);	
		mostrar++;
	}	
}

void FinalCola()
{
	Proceso Terminado;
	
	gotoxy(0, 1);
	cout<<"\t\t-----------------------[TIEMPOS DE LOS PROCESOS]------------------------"<<endl;
	gotoxy(0, 2);
	cout<<"\t\t------------------------------------------------------------------------"<<endl;
	int mostrar = 0, N = 4, Y = 0, cont = 5;
	
	while(CTerminados.ColaVacia() != 1)
	{
		if(mostrar > N)
		{
			N+=5;
			Y+=9;
			mostrar = 0;
		}
		
		CTerminados.EliminarCola(&Terminado);
		Terminado.MostrarTiempos(mostrar, Y);	
		mostrar++;
	}
}

Proceso CrearProceso(int id)
{
	Proceso P;
	int num1, num2, operacion, tme, tamano;
	
	P.setID(id); //Valor de i consecutivo
	tme = 6 + rand() % (17 - 6); //Numero para el tiempo aleatorio de 6 a 16
	P.setTME(tme); //Tiempo 
	operacion = 1 + rand() % 5;
	num1 = 0 + rand() % 501;	//Generar los numeros aleatorios para las operaciones
	num2 = 0 + rand() % 501;	//Generar los numeros aleatorios para las operaciones
	P.setOperacion2(operacion, num1, num2);
	tamano = 5 + rand() %  21;
	P.setTam(tamano);
	
	return P;
}

void LlenarTabla(Proceso EnEjecucion, int final)
{
	Cola<Proceso> Mostrar;
	Cola<Proceso> Mostrar2;
	Cola<Proceso> Mostrar3;
	Cola<Proceso> Mostrar4;
	Cola<Proceso> Mostrar5;
	Proceso M;
	
	Mostrar = Memoria;
	Mostrar2 = CListos;
	Mostrar3 = CTerminados;
	Mostrar4 = CBloqueados;
	Mostrar5 = Suspendidos;
	
	
	while(Mostrar.ColaVacia() != 1)
	{
		Mostrar.EliminarCola(&M);
		Tabla.InsertarCola(M);
	}
	
	if(final == 0)
		Tabla.InsertarCola(EnEjecucion);
	
	while(Mostrar2.ColaVacia() != 1)
	{
		Mostrar2.EliminarCola(&M);
		Tabla.InsertarCola(M);
	}
	
	while(Mostrar4.ColaVacia() != 1)
	{
		Mostrar4.EliminarCola(&M);
		Tabla.InsertarCola(M);
	}
	
	while(Mostrar3.ColaVacia() != 1)
	{
		Mostrar3.EliminarCola(&M);
		Tabla.InsertarCola(M);
	}
	
	while(Mostrar5.ColaVacia() != 1)
	{
		Mostrar5.EliminarCola(&M);
		Tabla.InsertarCola(M);
	}
}

void TablaProcesos(Proceso EnEjecucion, int final)
{
	LlenarTabla(EnEjecucion, final);
	
	system("cls");
	gotoxy(0, 1);
	cout<<"\t\t\t----------------------------[TABLA DE PROCESOS]--------------------------"<<endl;
	gotoxy(0, 2);
	cout<<"\t\t\t------------------------------------------------------[Contador Global]: "<<ContGlobal<<endl;
	cout<<"\nID \tOperacion \tValor 1 \tValor 2 \tRespuesta \tEstado \t\tTME \tTLL \tTF \tTE \tTResp \tTRet \tTS\tTRes\tTBloq"<<endl;
	
	Proceso MT;
	int cont = 1;
	while(Tabla.ColaVacia() != 1)
	{	
		Tabla.EliminarCola(&MT);
		
		if(MT.getEstatus() == "Nuevo")
		{
			MT.MostrarNuevo(cont);
		}
		else
			MT.MostrarTabla(cont, ContGlobal);	
		
		cont++;
	}
}

void Limpiar_TablaMemoria()
{
	for(int i=0; i<55; i++)
	{
		gotoxy(110, i);
		cout<<"                                                        "<<endl;
	}
	
}

void CrearArchivo()
{
	fstream ArchivoSuspendidos;
	//Verificando si el archivo existe
	ArchivoSuspendidos.open("Suspendidos.dat", ios::in | ios::out); 
	//Si el archivo no existe
	if( !ArchivoSuspendidos.is_open() ) //PARA CHECAR QUE EL ARCHIVO SE HAYA CREADO CORRECTAMENTE
	{
		ArchivoSuspendidos.open("Suspendidos.dat", ios::out); 
		
		if( !ArchivoSuspendidos.good() ) //DEVUELVE FALSO SI NO ES POSIBLE CREAR EL ARCHIVO
		{
			cout<<"ERROR AL CREAR EL ARCHIVO...ABORTANDO"<<endl;
			exit(1);
		}
		else
			ArchivoSuspendidos.close(); //CERRAMOS EL ARCHIHVO 
	}
	
	ArchivoSuspendidos.close(); //CERRAMOS EL ARCHIVO
}

void Insertar_Suspendido(int id)
{
	fstream ArchivoSuspendidos;
	ArchivoSuspendidos.open("Suspendidos.dat", ios::in | ios::out | ios::binary); 	
	string ID_Suspendido;
	ID_Suspendido = to_string(id);
	ArchivoSuspendidos.seekp((id-1) * sizeof(string)); 
	ArchivoSuspendidos<<"ID: "<<ID_Suspendido<<endl;
	ArchivoSuspendidos.close(); 
}

void Eliminar_Suspendido(int id)
{
	fstream ArchivoSuspendidos;
	ArchivoSuspendidos.open("Suspendidos.dat", ios::in | ios::out | ios::binary); 	
	string ID_Suspendido;
	ID_Suspendido = to_string(id);
	ArchivoSuspendidos.seekp((id-1) * sizeof(string)); 
	ArchivoSuspendidos<<"      "<<endl;
	ArchivoSuspendidos.close(); 
}

