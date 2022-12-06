#ifndef PROCESO_H
#define PROCESO_H
#include <iostream>
#include <string.h>
#include <windows.h> 
#include <cstdlib>

using namespace std;

class Proceso
{
	private:
		char Nombre[30];
		int ID;
		int Operacion;
		string Noperacion;
		string Estatus;
		int Res; //RESPUESTA
		int Val1; //VARIABLE 1
		int Val2; //VARIABLE 2
		int TME; //TIEMPO MAXIMO ESTIMADO
		int TRestante; //TIEMPO RESTANTE
		int TEjecutado; //TIEMPO DE EJECUCION / TIEMPO SERVICIO
		int Tllegada;//TIEMPO EN EL QUE LLEGO 
		int TFinal; //TIEMPO EN EL QUE TERMINO
		int TRetorno; //TIEMPO RETORNO / TIEMPO TOTAL EN EL SISTEMA
		int TRespuesta; //TIEMPO EN EL QUE LLEGO A EJECUCION
		int TEspera; //TIEMPO DE ESPERA /TIEMPO EN EL QUE DURO FUERA DE EJECUCION
		int TBloqueado;
		int Lote;
		int M;
		int Tam; //TAMAÑI DE PAGINA
		COORD coord;
		
	public:
		Proceso();
		void setNombre(char n[]);
		void setID(int id);
		int getID();
		void setTME(int tiempo);
		int getTME();
		void setTiempos(int TE, int TR);
		int getTR();
		int getTE();
		void setLlegada(int TiempoLLegada);
		void setRespuesta(int TiempoRespuesta);
		void setSalida(int TiempoSalida);
		void setTiempoBloqueado(int Modulo);
		int getTiempoBloqueado();
		int getOperacion();
		int getNum1();
		int getNum2();
		//void setOperacion(int ope);
		void setOperacion2(int Op, int Num1, int Num2);
		void setLote(int L);
		int getLote();
		void setM(int op);
		int getM();
		void Mostrar(int NProceso);
		void MostrarEjecucion();
		void LimpiarEjecucion();
		void MostrarFinal(int NProceso, int Y);
		void MostrarBloqueado(int X, int Y);
		void LimpiarBloqueado(int X, int Y);
		void MostrarReinicio();
		void gotoxy(int x, int y);
		void setEstatus(string E);
		void CalcularTiempos();
		void MostrarTiempos(int NProceso, int Y);
		void MostrarTabla(int y, int ContadorGlobal);
		void MostrarNuevo(int y);
		string getEstatus();
		void setTam(int tamano);
		int getTam();
		
};

#endif
