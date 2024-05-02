#include<Windows.h>
#include<stdio.h>
#include<Commctrl.h>
#include<cstring>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<Shlobj.h>
#include<cstdlib> ///para que genere un numero diferente cada vez
#include<ctime> //para generar un numero al azar
#include<vector>
#include<algorithm>
#include<cstdio>


#include"resource.h";

using namespace std;

SYSTEMTIME st;
//DECLARACIONES DE VENTANAS
HINSTANCE hInstance;
MSG mensaje;

LRESULT CALLBACK MENU(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND Hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(7), NULL, MENU);

LRESULT CALLBACK INICIO(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(101), Hwnd, INICIO);


LRESULT CALLBACK AU(HWND au, UINT msg, WPARAM wParam, LPARAM lParam);
HWND au = CreateDialog(hInstance, MAKEINTRESOURCE(105), Hwnd,AU);
//void cargausuario(SYSTEMTIME, char[], char[], char[], char[], char[], char[], char[]);

LRESULT CALLBACK VUELO(HWND vue, UINT msg, WPARAM wParam, LPARAM lParam);
HWND vue = CreateDialog(hInstance, MAKEINTRESOURCE(107), Hwnd, VUELO);
/*void cargarvuelo(SYSTEMTIME, char[], char[], char[], char[]);*///cuando,cadntidad de asientos,destino, usuario que registro


LRESULT CALLBACK LISTA(HWND lis, UINT msg, WPARAM wParam, LPARAM lParam);
HWND lis = CreateDialog(hInstance, MAKEINTRESOURCE(109), Hwnd, LISTA);
//void filtrar(char[],char[],char[]);


LRESULT CALLBACK VENTA(HWND ven, UINT msg, WPARAM wParam, LPARAM lParam);
HWND ven = CreateDialog(hInstance, MAKEINTRESOURCE(111), Hwnd, VENTA);
//void newpasajero();


LRESULT CALLBACK CANCEL(HWND can, UINT msg, WPARAM wParam, LPARAM lParam);
HWND can = CreateDialog(hInstance, MAKEINTRESOURCE(113), Hwnd, CANCEL);


LRESULT CALLBACK REGI(HWND reg, UINT msg, WPARAM wParam, LPARAM lParam);
HWND reg = CreateDialog(hInstance, MAKEINTRESOURCE(115), Hwnd, REGI);

LRESULT CALLBACK PASE(HWND pas, UINT msg, WPARAM wParam, LPARAM lParam);
HWND pas = CreateDialog(hInstance, MAKEINTRESOURCE(117), Hwnd, PASE);

LRESULT CALLBACK EVUELO(HWND edivue, UINT msg, WPARAM wParam, LPARAM lParam);
HWND edivue = CreateDialog(hInstance, MAKEINTRESOURCE(119), Hwnd, EVUELO);

LRESULT CALLBACK EPASE(HWND epas, UINT msg, WPARAM wParam, LPARAM lParam);
HWND epas = CreateDialog(hInstance, MAKEINTRESOURCE(121), Hwnd, EPASE);

LRESULT CALLBACK EUSU(HWND eusu, UINT msg, WPARAM wParam, LPARAM lParam);
HWND eusu = CreateDialog(hInstance, MAKEINTRESOURCE(123), Hwnd, EUSU);

//DECLARACIONES DE ESTRUCTURAS Y AUXILIARES
char generos[3][10] = {"Masculino","Femenino","Otro"};
char destinos[4][10] = { "Paris","Tokio","McAllen","Londres" };
char metodosdp[3][10] = { "Efectivo","T.debito","T.Credito" };
char clase[2][10] = { "Turista","Ejecutiva" };

//USUARIOS
struct usuarios
{
	SYSTEMTIME cumple; //datos del usuario
	char dia[5];
	char mes[5];
	char anio[5];
	char usuario[10];
	char correo[10];
	char contra[10];
	char nombre[10];
	char apellidoP[10];
	char apellidoM[10];
	char genero[10];
	//registro del usuario
	char reg[10];
	char hr[5];
	char dr[5];
	char mr[5];

	char imagen[41];

	//HBITMAP pic;
	usuarios* izq;
	usuarios* der;
};
usuarios* arbol = 0;	
usuarios* esa = 0;
usuarios* nvnodo(SYSTEMTIME, char[], char[], char[], char[], char[], char[], char[]);//para crear el nodo
void insertar(usuarios *&, SYSTEMTIME, char[], char[], char[], char[], char[], char[], char[]);


usuarios* cargarArbolBinario(ifstream&);
void guardarArbolBinario(usuarios*, ofstream&);

void ultimito(const char[]);
void nultimito();

//IMAGEN 
HBITMAP imagen = NULL;

HBITMAP Getimage()
{
	return imagen;
}

char fotito[70];

//auxiliares para los usuarios
SYSTEMTIME cum;
char adia[5];
char ames[5];
char aanio[5];
char radia[5];
char rames[5];
char rh[5];
char usu[10];
char cor[10];
char con[10];
char nom[10];
char apP[10];
char apM[10];
char gen[20];
char areg[10];
//inicio de sesion
char acon[10];
char ausu[10];//esta auxiliar la wa usar para que registrar el usuario que entro a la plataforma

//VUELOS
struct vuelo
{
	SYSTEMTIME salida;
	int ihora;
	char hora[10];
	char dia[10];
	char mes[10];
	char anio[10];

	SYSTEMTIME llegada;
	char Lhora[10];
	char Ldia[10];
	char Lmes[10];
	char Lanio[10];

	char novu[10];// numero de vuelo
	char asientos[5];//voy a usarlo para mostrar los disponibles
	int pt; //pasajeros totales
	int ad; //asientos disponibles
	int pa; //pasajeros adultos
	int pm; //pasajeros menores
	int pM; //pasajeros mayores

	char Cpt;
	char Cpa;
	char Cpm;
	char CpM;
	char destino[10];
	char origen[10];

	char vusu[10];//usuario que registro
	char hr[5];
	char dr[5];
	char mr[5];


	//cancelación
	char hc[5];
	char dc[5];
	char mc[5];
	char usuc[10];

	char estado[10];//estado, pendiente, cancelado o realizado.
	vuelo* ant;
	vuelo* sig;

};
vuelo* start = 0;
//AUX PARA LOS VUELOS
SYSTEMTIME asalida;
char ahoras[10]; //hora de salida
char aasientos[10];
char adestino[10];
int hdl;
int ddl;
int mdl;
int adl;
int abnv;//auxiliar busqueda numero de vuelo
int alf;//auxliar local de found
char cann[10];
char mano[5];

char fdia[20]; //pal filtro
char fmes[20];
char fani[20];

char dd[5];
char mm[5];
char aa[5];
char tota[5];//asientos disponibles en la compra


//datos de edición
char avusu[10];
char noma[10];
char ahr[5];
char adr[5];
char amr[5];
char aestado[10];
int apt;
int aad;
int apa;
int apm;
int aapM;

int ifdia;
int ifmes;
int ifani;

int a;
int e;
int i;

void find(vuelo*&, char[]);

//PASAJEROS
struct pasajero
{
	char vuelo[10];
	char nombrep[10];
	char paP[10];
	char paM[10];
	char dia[5];
	char mes[5];
	char canio[5];
	char generop[10];
	char asientito[5];
	char nacio[10];
	char ep[5];//edad pasajero
	char tdb[10];//tipo de boleto, turista, ejecutiva
	char mdp[10];// metodod de pago
	char state[10];//estado activo o cancelado

	char usu[10];//usuario que registro
	char hr[5];
	char dr[5];
	char mr[5];
	char PA[5];

	//cancelación
	char usuca[10];
	char hc[5];
	char dc[5];
	char mc[5];

	char hPA[5];//datos del pase de abordar
	char dPA[5];
	char mPA[5];
	char anioPA[5];

	pasajero* anti;
	pasajero* sigi;
};
pasajero* principio = 0;
std::vector<pasajero>pasita;	
//AUX PARA LOS PASAJEROS
SYSTEMTIME palpase;
char anombrep[20];
char apaP[20];
char apaM[20];
char avue[10];
char aadia[5];
char aames[5];
char agenero[10];
char anacio[10]; //nacionalidad
char aasiento[5];
char atdb[10]; //clase 
char amdp[10];
char astate[10];
char nu[10];//auxiliar para numero de vuelo 
char no[10];
//lo de usuarios
char aausu[10];
int roro;

char datiton[10];
int recordar = 0;


int Md; //asientos para mayores y menores disponibles
int md;
//comparativas de asientos
int eda;
int x;
int y;
int z;
void vuelito(vuelo*&, char[], int);
int veri = 0;

void savuelos();
void carvuelos();
void sapas();
void carpas();

struct Dato {
	char last[10];
};
//CLASES CON LAS FUNCIONES
class usul
{
public:
	static bool busqueda(usuarios* buco, char ausu[])
	{
		strcpy_s(datiton, ausu);
		if (buco == NULL)
		{
			return false;
		}
		else if (strcmp(buco->usuario, ausu) == 0)
		{
			return true;
	/*		imagen = buco->pic;
			strcpy_s(fotito, buco->npic);*/
		}
		else if (strlen(ausu) < strlen(buco->usuario))
		{
			return busqueda(buco->izq, ausu);
		}
		else
		{
			return busqueda(buco->der, ausu);
		}
			
	}

	static bool contras(usuarios* buco, char acon[])
	{
		if (buco == NULL)
		{
			return false;
		}
		else if (strcmp(buco->contra, acon) == 0)
		{
			return true;
		}
		else if (strlen(ausu) < strlen(buco->usuario))
		{
			return busqueda(buco->izq, acon);
		}
		else
		{
			return busqueda(buco->der, acon);
		}
	}

	static bool donde(usuarios*& buco, char usu[])
	{
		if (buco == NULL)
		{
			return false;
		}
		else if (strcmp(buco->usuario, usu) == 0)
		{
			strcpy_s(nom, buco->nombre);
			strcpy_s(apP, buco->apellidoP);
			strcpy_s(apM, buco->apellidoM);
			strcpy_s(cor, buco->correo);
			strcpy_s(acon, buco->contra);
			strcpy_s(gen, buco->genero);
			cum.wYear = buco->cumple.wYear;
			cum.wMonth = buco->cumple.wMonth;
			cum.wDay = buco->cumple.wDay;
			veri = 1;
			return true;
		}
		else if (strlen(usu)<strlen(buco->usuario))
		{
			return busqueda(buco->izq, usu);
		}
		else
		{
			return busqueda(buco->der, usu);
		}
	}

	static bool edite(usuarios* esa,char usu[])
	{
		if (strcmp(usu,esa->usuario) == 0) 
		{
			strcpy_s(esa->nombre, nom);
			strcpy_s(esa->apellidoP, apP);
			strcpy_s(esa->apellidoM, apM);
			strcpy_s(esa->correo, cor);
			strcpy_s(esa->contra, con);
			strcpy_s(esa->usuario, usu);

			esa->cumple = cum;
			_itoa_s(esa->cumple.wYear, esa->anio, 10);
			_itoa_s(esa->cumple.wMonth, esa->mes, 10);
			_itoa_s(esa->cumple.wDay, esa->dia, 10);
			return true;
		}
		else if (strlen(usu) < strlen(esa->usuario))
		{
			return edite(esa->izq, usu);
		}
		else
		{
			return edite(esa->der, usu);
		}

	}
};

class volar
{
public:
	static void cargarvuelo(SYSTEMTIME asalida, char ahoras[], char aasientos[], char adestino[], char ausu[])
	{
		vuelo* last = start;
		vuelo* nuevo = new vuelo;
		int owo = 0;

		nuevo->salida = asalida;
		_itoa_s(nuevo->salida.wYear, nuevo->anio, 10);
		_itoa_s(nuevo->salida.wMonth, nuevo->mes, 10);
		_itoa_s(nuevo->salida.wDay, nuevo->dia, 10);
		strcpy_s(nuevo->hora, ahoras); //hora de salida
		strcpy_s(nuevo->destino, adestino);
		strcpy_s(nuevo->asientos, aasientos);
		nuevo->ad = atoi(aasientos);
		nuevo->pt = atoi(nuevo->asientos);
		nuevo->pM = nuevo->pt * 0.15;
		nuevo->pm = nuevo->pt * 0.10;
		nuevo->pa = nuevo->pt - nuevo->pM - nuevo->pm;
		strcpy_s(nuevo->vusu, ausu);
		_itoa_s(st.wMonth, nuevo->mr, 10);
		_itoa_s(st.wDay, nuevo->dr, 10);
		_itoa_s(st.wHour, nuevo->hr, 10);
		srand(time(NULL));// se genera un numero diferente y al azar
		int cana = rand();
		_itoa_s(cana, nuevo->novu, 10);
		strcpy_s(nuevo->estado, "Proximo");
		int momo = atoi(ahoras);
		nuevo->ihora = momo;

		//calcular llegada
		mdl = nuevo->salida.wMonth;
		adl = nuevo->salida.wYear;
		ddl = nuevo->salida.wDay;

		if (strcmp(nuevo->destino, "Paris") == 0)
		{
			hdl = nuevo->ihora + 15;
		}
		else if (strcmp(nuevo->destino, "Tokio") == 0)
		{
			hdl = nuevo->ihora + 16;
		}
		else if (strcmp(nuevo->destino, "McAllen") == 0)
		{
			hdl = nuevo->ihora + 7;
		}
		else if (strcmp(nuevo->destino, "Londres") == 0)
		{
			hdl = nuevo->ihora + 14;
		}

		if (hdl > 24)
		{
			hdl = hdl - 24;
			ddl = nuevo->salida.wDay + 1;
		}

		if (mdl == 1 || mdl == 3 || mdl == 5 || mdl == 7 || mdl == 8 || mdl == 10 || mdl == 12)//31 dias
		{
			if (ddl > 31)
			{
				mdl = mdl + 1;
				ddl = 1;
			}
		}
		else
		{
			if (ddl > 30)
			{
				mdl = mdl + 1;
				ddl = 1;
			}
		}
		nuevo->llegada.wHour = hdl;
		nuevo->llegada.wDay = ddl;
		nuevo->llegada.wMonth = mdl;
		nuevo->llegada.wYear = nuevo->salida.wYear;
		_itoa_s(nuevo->llegada.wYear, nuevo->Lanio, 10);
		_itoa_s(nuevo->llegada.wMonth, nuevo->Lmes, 10);
		_itoa_s(nuevo->llegada.wDay, nuevo->Ldia, 10);
		_itoa_s(hdl, nuevo->Lhora, 10);
		//organizo en la lista

		vuelo* omega = start;
		vuelo* alfa = NULL;

		while (omega != NULL && omega->salida.wYear > asalida.wYear)
		{
			alfa = omega;
			omega = omega->sig;
			owo = 1;
		}
		if (owo == 0 || omega != NULL)
		{
			while (omega != NULL && omega->salida.wMonth > asalida.wMonth)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 2;
			}
		}
		if (owo == 0 || omega == NULL)
		{
			while (omega != NULL && omega->salida.wDay > asalida.wDay)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 3;
			}
		}
		if (owo == 0 || omega != NULL)
		{
			while (omega != NULL && omega->ihora > momo)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 4;
			}
		}
		if (start == omega)
		{
			start = nuevo;
		}
		else
		{
			alfa->sig = nuevo;
		}
		nuevo->sig = omega;
	}

	static void filtrar(char fdia[], char fmes[], char fani[])
	{
		vuelo* hayar;
		vuelo* anterior = NULL;

		hayar = start;

		ifdia = atoi(fdia);
		ifmes = atoi(fmes);
		ifani = atoi(fani);

		a = atoi(hayar->anio);
		e = atoi(hayar->mes);
		i = atoi(hayar->dia);

		while (hayar != NULL)
		{
			int awas = 0;


			if (a < ifani)
			{
				awas = 2;
			}
			else
			{
				if (e < ifmes)
				{
					awas = 1;
				}
				else if (e > ifmes)
				{
					awas = 0;
				}
				else
				{
					if (i < ifdia)
					{
						awas = 5;
					}
					else
					{
						awas = 0;
					}
				}
			}
			if (awas == 0)
			{
				SendMessage(GetDlgItem(lis, 10278), LB_INSERTSTRING, 0, (LPARAM)"\n");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"\n");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->Lanio);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Año");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->Lmes);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Mes");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->Ldia);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Dia");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->Lhora);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->anio);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Año ");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->mes);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->dia);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Día ");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->hora);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->asientos);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)hayar->novu);
				SendMessage(GetDlgItem(lis, 1028), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");

				anterior = hayar;
				hayar = hayar->sig;
			}
			else
			{
				anterior = hayar;
				hayar = hayar->sig;
			}
		}
	}

	static void find(vuelo*& start, char nu[])
	{
		strcpy_s(no, nu);

		vuelo* found;
		vuelo* anterior = NULL;

		found = start;

		while (found != NULL && strcmp(no, found->novu) != 0)
		{
			anterior = found;
			found = found->sig;
		}

		if (found == NULL)
		{
			int  res = MessageBox(lis, "Ingrese un valor", "invalido", MB_OK);
		}
		else
		{

			strcpy_s(adestino, found->destino);
			strcpy_s(aa, found->anio);
			strcpy_s(mm, found->mes);
			strcpy_s(dd, found->dia);
			_itoa_s(found->ad, tota, 10);
			strcpy_s(mano, found->asientos);
			Md = found->pM;
			md = found->pm;
			ven = CreateDialog(hInstance, MAKEINTRESOURCE(111), Hwnd, VENTA);
			ShowWindow(ven, SW_SHOWDEFAULT);
		}
	}

	static void vuelito(vuelo*& start, char no[], int x)
	{
		strcpy_s(nu, no);

		vuelo* found;
		vuelo* anterior = NULL;

		found = start;

		while (found != NULL && strcmp(nu, found->novu) != 0)
		{
			anterior = found;
			found = found->sig;
		}

		if (found == NULL)
		{
			int  res = MessageBox(lis, "Ingrese un valor", "invalido", MB_OK);
		}
		else
		{
			found->ad = found->ad - 1;
			if (x < 18)
			{
				found->pm = found->pm - 1;
			}
			else if (x > 60)
			{
				found->pM = found->pM - 1;
			}
		}
	}

	static void cancelar(char nu[])
	{
		int was = 0;
		vuelo* aux = start;
		while (aux != NULL)
		{
			if (strcmp(nu, aux->novu) == 0)
			{
				if (strcmp(aux->estado, "Cancelado") == 0)
				{
					int  res = MessageBox(can, "Vuelo ya cancelado", "Ya", MB_OK);
					int was = 2;
				}
				else
				{
					strcpy_s(aux->estado, "Cancelado");
					strcpy_s(aux->usuc, ausu); //registro de cancelacion
					_itoa_s(st.wMonth, aux->mc, 10);
					_itoa_s(st.wDay, aux->dc, 10);
					_itoa_s(st.wHour, aux->hc, 10);

					int  res = MessageBox(can, "Vuelo cancelado", "Listo", MB_OK);

					pasajero* auy = principio;

					while (auy != NULL)
					{
						if (strcmp(nu, auy->vuelo) == 0)
						{
							strcpy_s(auy->state, "Cancelado");
							strcpy_s(auy->usuca, ausu); //registro de cancelacion
							_itoa_s(st.wMonth, auy->hc, 10);
							_itoa_s(st.wDay, auy->dc, 10);
							_itoa_s(st.wHour, auy->hc, 10);
						}
						auy = auy->sigi;
					}
					int was = 1;
				}
			}
			aux = aux->sig;
		}
		if (was != 0)
		{
			int  res = MessageBox(can, "No se encontro el vuelo", "Otro", MB_OK);
		}


	}
	
	//Edición de vuelos

	static void encontrar(vuelo*& start,char nu[])
	{
		strcpy_s(no, nu);

		vuelo* editar;
		vuelo* anterior = NULL;

		editar = start;

		while (editar != NULL && strcmp(editar->novu, no) != 0)
		{
			anterior = editar;
			editar = editar->sig;
		}

		if (editar == NULL)
		{
			int  res = MessageBox(Hwnd, "Ingrese un valor valido", "invalido", MB_OK);
		}
		else if (strcmp(editar->estado, "Cancelado") == 0)
		{
			int  res = MessageBox(Hwnd, "El vuelo a sido cancelado", "invalido", MB_OK);
		}
		else if (anterior==NULL)
		{
			start = start->sig;
			strcpy_s(adestino, editar->destino);
			asalida.wYear = editar->salida.wYear;
			asalida.wMonth = editar->salida.wMonth;
			asalida.wDay = editar->salida.wDay;
			strcpy_s(adestino, editar->destino);
			strcpy_s(avusu, editar->vusu);
			strcpy_s(ahr, editar->hr);
			strcpy_s(adr, editar->dr);
			strcpy_s(amr, editar->mr);
			strcpy_s(aestado, editar->estado);
			//manejo de asientos
			strcpy_s(aasientos, editar->asientos);
			apt=editar->pt;
			aad=editar->ad;
			apa=editar->pa;
			apm=editar->pm;
			aapM=editar->pM;
			delete editar;
			veri = 1;
			return;
		}
		else
		{
			anterior->sig = editar->sig;
			strcpy_s(adestino, editar->destino);
			asalida.wYear = editar->salida.wYear;
			asalida.wMonth = editar->salida.wMonth;
			asalida.wDay = editar->salida.wDay;
			strcpy_s(ahoras, editar->hora);
			strcpy_s(adestino, editar->destino);
			strcpy_s(avusu,editar-> vusu);
			strcpy_s(ahr, editar->hr);
			strcpy_s(adr, editar->dr);
			strcpy_s(amr, editar->mr);
			strcpy_s(aestado, editar->estado);
			//manejo de asientos
			strcpy_s(aasientos, editar->asientos);
			apt = editar->pt;
			aad = editar->ad;
			apa = editar->pa;
			apm = editar->pm;
			aapM = editar->pM;
			delete editar;
			veri = 1;
			return;
		}
	}

	static void cargarvuelo2(SYSTEMTIME asalida, char ahoras[], char adestino[], char ausu[])
	{
		vuelo* last = start;
		vuelo* nuevo = new vuelo;
		int owo = 0;

		nuevo->salida = asalida;
		_itoa_s(nuevo->salida.wYear, nuevo->anio, 10);
		_itoa_s(nuevo->salida.wMonth, nuevo->mes, 10);
		_itoa_s(nuevo->salida.wDay, nuevo->dia, 10);
		strcpy_s(nuevo->hora, ahoras); //hora de salida
		strcpy_s(nuevo->destino, adestino);//destino
		strcpy_s(nuevo->asientos, aasientos);//asientos
		nuevo->pt = apt;
		nuevo->ad = aad;
		nuevo->pa = apa;
		nuevo->pm = apm;
		nuevo->pM = aapM;
		//registro
		strcpy_s(nuevo->hr,ahr );
		strcpy_s(nuevo->dr,adr );
		strcpy_s(nuevo->mr,amr );
		strcpy_s(nuevo->vusu, avusu);
		strcpy_s(nuevo->novu, no);
		strcpy_s(nuevo->estado,aestado);
		//registro de edición
		strcpy_s(nuevo->usuc, ausu);
		_itoa_s(st.wMonth, nuevo->mr, 10);
		_itoa_s(st.wDay, nuevo->dr, 10);
		_itoa_s(st.wHour, nuevo->hr, 10);
		
		int momo = atoi(ahoras);
		nuevo->ihora = momo;
		//calcular llegada
		mdl = nuevo->salida.wMonth;
		adl = nuevo->salida.wYear;
		ddl = nuevo->salida.wDay;

		if (strcmp(nuevo->destino, "Paris") == 0)
		{
			hdl = nuevo->ihora + 15;
		}
		else if (strcmp(nuevo->destino, "Tokio") == 0)
		{
			hdl = nuevo->ihora + 16;
		}
		else if (strcmp(nuevo->destino, "McAllen") == 0)
		{
			hdl = nuevo->ihora + 7;
		}
		else if (strcmp(nuevo->destino, "Londres") == 0)
		{
			hdl = nuevo->ihora + 14;
		}

		if (hdl > 24)
		{
			hdl = hdl - 24;
			ddl = nuevo->salida.wDay + 1;
		}

		if (mdl == 1 || mdl == 3 || mdl == 5 || mdl == 7 || mdl == 8 || mdl == 10 || mdl == 12)//31 dias
		{
			if (ddl > 31)
			{
				mdl = mdl + 1;
				ddl = 1;
			}
		}
		else
		{
			if (ddl > 30)
			{
				mdl = mdl + 1;
				ddl = 1;
			}
		}
		nuevo->llegada.wHour = hdl;
		nuevo->llegada.wDay = ddl;
		nuevo->llegada.wMonth = mdl;
		nuevo->llegada.wYear = nuevo->salida.wYear;
		_itoa_s(nuevo->llegada.wYear, nuevo->Lanio, 10);
		_itoa_s(nuevo->llegada.wMonth, nuevo->Lmes, 10);
		_itoa_s(nuevo->llegada.wDay, nuevo->Ldia, 10);
		_itoa_s(hdl, nuevo->Lhora, 10);
		//organizo en la lista

		vuelo* omega = start;
		vuelo* alfa = NULL;

		while (omega != NULL && omega->salida.wYear > asalida.wYear)
		{
			alfa = omega;
			omega = omega->sig;
			owo = 1;
		}
		if (owo == 0 || omega != NULL)
		{
			while (omega != NULL && omega->salida.wMonth > asalida.wMonth)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 2;
			}
		}
		if (owo == 0 || omega == NULL)
		{
			while (omega != NULL && omega->salida.wDay > asalida.wDay)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 3;
			}
		}
		if (owo == 0 || omega != NULL)
		{
			while (omega != NULL && omega->ihora > momo)
			{
				alfa = omega;
				omega = omega->sig;
				owo = 4;
			}
		}
		if (start == omega)
		{
			start = nuevo;
		}
		else
		{
			alfa->sig = nuevo;
		}
		nuevo->sig = omega;
		DestroyWindow(edivue);
	}
};

class pasaje
{
public:
	static void newpasajero()
	{
		pasajero* oct = principio;
		pasajero* nuevo = new pasajero;

		//datos del pasajero
		strcpy_s(nuevo->vuelo, no);
		strcpy_s(nuevo->nombrep, anombrep);
		strcpy_s(nuevo->paP, apaP);
		strcpy_s(nuevo->paM, apaM);
		_itoa_s(palpase.wYear, nuevo->canio, 10);
		_itoa_s(palpase.wMonth, nuevo->mes, 10);
		_itoa_s(palpase.wDay, nuevo->dia, 10);
		strcpy_s(nuevo->generop, agenero);
		strcpy_s(nuevo->asientito, aasiento);
		strcpy_s(nuevo->nacio, anacio);
		_itoa_s(x, nuevo->ep, 10);
		strcpy_s(nuevo->tdb, atdb);
		strcpy_s(nuevo->mdp, amdp);
		strcpy_s(nuevo->state, "Activo");

		//datos del registro
		strcpy_s(nuevo->usu, ausu);
		_itoa_s(st.wMonth, nuevo->mr, 10);
		_itoa_s(st.wDay, nuevo->dr, 10);
		_itoa_s(st.wHour, nuevo->hr, 10);

		//modificar vuelo al que subira
		volar::vuelito(start, no, x);
		//acomodo
		pasajero* omega = principio;
		pasajero* alfa = NULL;

		while (omega != NULL)
		{
			alfa = omega;
			omega = omega->sigi;
		}
		if (principio == omega)
		{
			principio = nuevo;
		}
		else
		{
			alfa->sigi = nuevo;
		}
		nuevo->sigi = omega;
	};

	static void noboleto(char anombrep[])
	{
		int awita = 0;
		pasajero* yu = principio;
		while (yu != NULL)
		{

			if (strcmp(yu->nombrep, anombrep) == 0 && strcmp(yu->paP, apaP) == 0 && strcmp(yu->paM, apaM) == 0)
			{


				if (strcmp("Cancelado", yu->state) == 0)
				{
					int  res = MessageBox(can, "Boleto ya cancelado", "Ya", MB_OK);
				}
				else if (strcmp("Efectuado", yu->state) == 0)
				{
					int  res = MessageBox(can, "Vuelo ya efectuado", "Ya", MB_OK);
				}
				else
				{
					vuelo* dou = start;
					int facha;
					int lol;

					while (dou != NULL)
					{
						lol = st.wDay;
						facha = dou->salida.wDay;
						if (st.wMonth == dou->salida.wMonth)
						{
							int maus = lol - facha;
							if (maus < 10)
							{
								awita = 1;
							}
						}
						lol = st.wMonth;
						facha = dou->salida.wMonth;
						if (lol - facha == 1)
						{
							lol = st.wDay;
							facha = dou->salida.wDay;
							if (lol > 20 && dou->salida.wDay < 10 && lol - facha > 20)
							{
								awita = 1;
							}
						}
						dou = dou->sig;
					}
					if (awita == 0)
					{
						strcpy_s(yu->state, "Cancelado");
						strcpy_s(yu->usuca, ausu); //registro de cancelacion
						_itoa_s(st.wMonth, yu->hc, 10);
						_itoa_s(st.wDay, yu->dc, 10);
						_itoa_s(st.wHour, yu->hc, 10);
						int  res = MessageBox(can, "Boleto cancelado", "Listo", MB_OK);

						vuelo* oi = start;

						while (oi != NULL)
						{
							lol = st.wDay;
							facha = oi->salida.wDay;

							if (strcmp(yu->vuelo, oi->novu) == 0 && facha - lol > 10) //volver a dar disponibilidad
							{
								x = atoi(yu->ep);
								oi->ad = oi->ad + 1;


								if (x < 18)
								{
									oi->pm = oi->pm + 1;
								}
								else if (x > 60)
								{
									oi->pM = oi->pM + 1;
								}
								else
								{
									oi->pa = oi->pa + 1;
								}
							}
							oi = oi->sig;
						}
					}

				}
			}
			yu = yu->sigi;
		}
		if (awita != 0)
		{
			int  res = MessageBox(can, "Boleto no encontrado u hora limite alcanzada", "Listo", MB_OK);
		}
	}

	static void vec(pasajero* nodo, std::vector<pasajero>& vico)
	{
		if (nodo != nullptr)
		{
			vec(nodo->sigi, vico);
			vico.push_back(*nodo);
		}
	}
	
	//PARA EL QUICKSORT
	static void swamp(pasajero& a,pasajero& b)
	{
		pasajero temp = a;
		a = b;
		b = temp;
	}
    
	static int partition(std::vector<pasajero>& pasita, int low, int high) {
		pasajero pivot = pasita[high]; 
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++) {
			if (strlen(pasita[j].nombrep) < strlen(pivot.nombrep)) {
				i++; 
				swap(pasita[i], pasita[j]);
			}
		}
		swap(pasita[i + 1], pasita[high]);
		return (i + 1);
	}

	static void quickSort(std::vector<pasajero>& pasita, int low, int high) {
		if (low < high) {
			int pi = partition(pasita, low, high);

			quickSort(pasita, low, pi - 1);
			quickSort(pasita, pi + 1, high);
		}
	}

	//Editar pasajero
	static void encontrar(pasajero*& principio,char anombrep[], char apaP[], char apaM[])
	{
		pasajero* editar;
		pasajero* anterior=NULL;

		editar = principio;

		while (editar != NULL && strcmp(editar->nombrep, anombrep) != 0 && strcmp(editar->paP, apaP) != 0 && strcmp(editar->paM, apaM) != 0)
		{
			anterior = editar;
			editar = editar->sigi;
		}

		if (editar == NULL)
		{
			int  res = MessageBox(Hwnd, "No se encontro el pasajero", "invalido", MB_OK);
		}
		else if (strcmp(editar->state, "Cancelado") == 0)
		{
			int  res = MessageBox(Hwnd, "el boleto esta cancelado", "invalido", MB_OK);
		}
		else if (anterior == NULL)
		{
			principio = principio->sigi;
			strcpy_s(avue, editar->vuelo);
			strcpy_s(aadia, editar->dia);
			strcpy_s(aames, editar->mes);
			strcpy_s(anacio, editar->canio);
			strcpy_s(aasiento, editar->asientito);
			strcpy_s(atdb, editar->tdb);
			strcpy_s(amdp, editar->mdp);
			strcpy_s(astate, editar->state);
			strcpy_s(aausu, editar->usu);
			strcpy_s(ahr, editar->hr);
			strcpy_s(adr, editar->dr);
			strcpy_s(amr, editar->mr);
			x = atoi(editar->dia);
			y = atoi(editar->mes);
			z = atoi(editar->canio);
			palpase.wYear = z;
			asalida.wMonth = y;
			asalida.wDay = x;
			pasaje::hayo(start);
			roro = 1;
			delete editar;
			return;
		}
		else
		{
			anterior->sigi = editar->sigi;
			strcpy_s(avue, editar->vuelo);
			strcpy_s(aadia, editar->dia);
			strcpy_s(aames, editar->mes);
			strcpy_s(anacio, editar->canio);
			strcpy_s(aasiento, editar->asientito);
			strcpy_s(atdb, editar->tdb);
			strcpy_s(amdp, editar->mdp);
			strcpy_s(astate, editar->state);
			strcpy_s(aausu, editar->usu);
			strcpy_s(ahr, editar->hr);
			strcpy_s(adr, editar->dr);
			strcpy_s(amr, editar->mr);
			x = atoi(editar->dia);
			y = atoi(editar->mes);
			z = atoi(editar->canio);
			palpase.wYear = z;
			asalida.wMonth = y;
			asalida.wDay = x;
			pasaje::hayo(start);
			delete editar;
			roro = 1;
			return;
		}
	}

	static void hayo(vuelo*& start)
	{
		strcpy_s(no, avue);

		vuelo* found;
		vuelo* anterior = NULL;

		found = start;

		while (found != NULL && strcmp(no, found->novu) != 0)
		{
			anterior = found;
			found = found->sig;
		}

		if (found == NULL)
		{
			int  res = MessageBox(lis, "Ingrese un valor", "invalido", MB_OK);
		}
		else
		{
			strcpy_s(adestino, found->destino);
			strcpy_s(aa, found->anio);
			strcpy_s(mm, found->mes);
			strcpy_s(dd, found->dia);
			_itoa_s(found->ad, tota, 10);
			strcpy_s(mano, found->asientos);
			Md = found->pM;
			md = found->pm;
			strcpy_s(noma, no);
		}
	}
};


//HEAPSORT EN ESTA PARTE
std::vector<usuarios>usuVector;
void HEAP(usuarios*, std::vector<usuarios>&);

//EL WIN MAIN	
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//cargas los biarios de los usuarios,vuelos y pasajeros
	usuarios* arbolCargado = nullptr;
	ifstream archivoEntrada("arbol.bin", ios::binary);
	if (archivoEntrada.is_open()) {
		arbolCargado = cargarArbolBinario(archivoEntrada);
		arbol = arbolCargado;
		archivoEntrada.close();
		cout << "Arbol binario cargado desde arbol.bin" << endl;
	}
	else {
		cerr << "Error al abrir el archivo para lectura" << endl;
	}

	carvuelos();
	carpas();

	nultimito();

	hInstance = hInst;

	hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(101),Hwnd , INICIO);
	ShowWindow(hwnd, SW_SHOWDEFAULT);

	while (TRUE == GetMessage(&mensaje, 0, 0, 0))
	{
		TranslateMessage(&mensaje);
		DispatchMessage(&mensaje);
	}
}

//VENTANAS
LRESULT CALLBACK MENU(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(Hwnd, 1035, ausu);
	}
	break;
	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == 1004)
		{

			
			if (strcmp(ausu, "Mod") == 0)
			{
				au = CreateDialog(hInstance, MAKEINTRESOURCE(105), Hwnd, AU);
				ShowWindow(au, SW_SHOWDEFAULT);
			}
			else
			{
				int  res = MessageBox(Hwnd, "Solo el usuario admin puede dar de alta usuarios", "No admin", MB_OK);
			}
			//extra
			au = CreateDialog(hInstance, MAKEINTRESOURCE(105), Hwnd, AU);
			HEAP(arbol, usuVector);
			ShowWindow(au, SW_SHOWDEFAULT);
		}
		if (LOWORD(wParam) == 1005)
		{
			vue = CreateDialog(hInstance, MAKEINTRESOURCE(107), Hwnd, VUELO);
			ShowWindow(vue, SW_SHOWDEFAULT);
		}
		if (LOWORD(wParam) == 1026)
		{
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			lis = CreateDialog(hInstance, MAKEINTRESOURCE(109), Hwnd, LISTA);
			ShowWindow(lis,SW_SHOWDEFAULT);
		}

		if (LOWORD(wParam) == 1031)
		{
			ofstream Salida("usuarios.bin", ios::binary);
			if (Salida.is_open()) 
			{
				guardarArbolBinario(arbol, Salida);
				Salida.close();
			}
			savuelos();
			sapas();
			DestroyWindow(Hwnd);
		}

		if (LOWORD(wParam) == 1006)
		{
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			can = CreateDialog(hInstance, MAKEINTRESOURCE(113), Hwnd, CANCEL);
			ShowWindow(can, SW_SHOWDEFAULT);
		}

		if (LOWORD(wParam) == 1007)
		{
		
			pasaje::vec(principio, pasita);
			int n = pasita.size();
			pasaje::quickSort(pasita, 0, n - 1);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			reg = CreateDialog(hInstance, MAKEINTRESOURCE(115), Hwnd, REGI);
			ShowWindow(reg, SW_SHOWDEFAULT);
		}

		if (LOWORD(wParam) == 1091)
		{
			GetDlgItemText(Hwnd, 1086,anombrep, 10);
			GetDlgItemText(Hwnd, 1087, apaP, 10);
			GetDlgItemText(Hwnd, 1088, apaM, 10);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);

			pasajero* plo = principio;
			int mobo = 0;
			while (plo != NULL )
			{
				if ( strcmp(anombrep, plo->nombrep) == 0 && strcmp(apaP, plo->paP) == 0 && strcmp(apaM, plo->paM) == 0 && strcmp(plo->state, "Cancelado") != 0)
				{
					strcpy_s(plo->PA, "si");
					_itoa_s(st.wYear, plo->anioPA, 10);
					_itoa_s(st.wMonth, plo->mPA, 10);
					_itoa_s(st.wDay, plo->dPA, 10);
					_itoa_s(st.wHour, plo->hPA, 10);
					pas = CreateDialog(hInstance, MAKEINTRESOURCE(117), Hwnd, PASE);
					ShowWindow(pas, SW_SHOWDEFAULT);
					mobo = 1;
				}
				plo = plo->sigi;
			}
			if (mobo == 0)
			{
				int  res = MessageBox(Hwnd, "Pase ya obtenido o cliente no encontrado", "invalido", MB_OK);
			}
		}

		if (LOWORD(wParam) == 1105)
		{
			veri = 0;
			GetDlgItemText(Hwnd, 1089, nu, 10);
			SetDlgItemText(Hwnd, 1089, "");
			volar::encontrar(start,nu);
			if (veri == 1)
			{
				edivue = CreateDialog(hInstance, MAKEINTRESOURCE(119), Hwnd, EVUELO);
				ShowWindow(edivue, SW_SHOWDEFAULT);
			}
		}

		if (LOWORD(wParam) == 1106)
		{
			roro = 0;
			GetDlgItemText(Hwnd, 1090, anombrep,10);
			GetDlgItemText(Hwnd, 1092,apaP ,10);
			GetDlgItemText(Hwnd, 1093, apaM,10);
			pasaje::encontrar(principio, anombrep, apaP, apaM);
			if (roro == 1)
			{
				epas= CreateDialog(hInstance, MAKEINTRESOURCE(121), Hwnd, EPASE);
				ShowWindow(epas, SW_SHOWDEFAULT);

			}
		}

		if (LOWORD(wParam) == 1107)
		{
			GetDlgItemText(Hwnd, 1094, usu, 10);
			if(usul::donde(arbol, usu)==true)
			{
				eusu = CreateDialog(hInstance, MAKEINTRESOURCE(123), Hwnd, EUSU);
				ShowWindow(eusu, SW_SHOWDEFAULT);
			}
			else
			{
				int  res = MessageBox(Hwnd, "No se encontro el usuario", "invalido", MB_OK);
			}
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	}
	return 0;
}

LRESULT CALLBACK INICIO(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hwnd, 1001, ausu);
	}
	break;
	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == 1003)
		{
			
			GetDlgItemText(hwnd, 1001, ausu, 10);
			GetDlgItemText(hwnd, 1002, acon, 10);
			
			usuarios*& buco=arbol;

			if (usul::busqueda(buco, ausu) == true)
			{
				usuarios* buco = arbol;

				if (usul::contras(buco, acon) == true)
				{
					DestroyWindow(hwnd);
					Hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(7),0, MENU);
					ShowWindow(Hwnd, SW_SHOWDEFAULT);
				}
				else
				{
					int  res = MessageBox(hwnd, "Contraseña incorrecta", "recuerde", MB_OK);
				}
			}
			else
			{
				int  res = MessageBox(hwnd, "Este usuario no existe", "invalido", MB_OK);
			}
			//extra
			DestroyWindow(hwnd);
			Hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(7), 0, MENU);
			ShowWindow(Hwnd, SW_SHOWDEFAULT);
			
			if (recordar == 1)
			{
				Dato last;
				strcpy_s(last.last, datiton);

				std::ofstream chivo("datito.bin",std::ios::binary);
				if (chivo.is_open())
				{
					chivo.write(reinterpret_cast<char*>(&last), sizeof(Dato));
				}
				chivo.close();
			}
			else if (recordar == 0)
			{
				Dato last;
				strcpy_s(last.last, "");

				std::ofstream chivo("datito.bin", std::ios::binary);
				if (chivo.is_open())
				{
					chivo.write(reinterpret_cast<char*>(&last), sizeof(Dato));
				}
				chivo.close();
			}
		}

		if (SendDlgItemMessage(hwnd, 1104, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			recordar = 1;
		}
		
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{

	}
	break;
	}
	return 0;
}

LRESULT CALLBACK AU(HWND au, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(au, 1037, ausu);

		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(au, 1016, CB_INSERTSTRING, a, (LPARAM)generos[a]);
		}

		for (auto i = usuVector.begin(); i != usuVector.end(); e++)
		{
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->hr);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"hora registro");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->dr);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"día registro");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->mr);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"mes registro");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->reg);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"usuario que registró");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->genero);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Género");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->apellidoM);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Apellido Materno");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->apellidoP);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Apellido Paterno");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->nombre);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Nombre");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->usuario);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Usuario");
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->anio);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->mes);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)i->dia);
			SendMessage(GetDlgItem(au, 1103), LB_INSERTSTRING, 0, (LPARAM)"Cumpleaños día, mes y año");

		}

	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1019)
		{
			SendDlgItemMessage(au, 1018, DTM_GETSYSTEMTIME, 0, (LPARAM)&cum);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			GetDlgItemText(au, 1006, usu, 10);
			GetDlgItemText(au, 1007, cor, 10);
			GetDlgItemText(au, 1008, con, 10);
			GetDlgItemText(au, 1010, nom, 10);
			GetDlgItemText(au, 1012, apP, 10);
			GetDlgItemText(au, 1014, apM, 10);
			GetDlgItemText(au, 1016, gen, 10);

			int wasa = 0;
			if (st.wYear - cum.wYear < 18)
			{
				int  res = MessageBox(au, "Edad insuficiente", "invalido", MB_OK);
				wasa = 1;
			}
			int uyu = 0;
			int lol = strlen(usu);

			if (lol == 0)
			{
				int  res = MessageBox(au, "Ingrese un  nombre de usuario", "invalido", MB_OK);
				uyu = 1;
			}
			else
			{
				lol = strlen(cor);
				if (lol == 0)
				{
					int  res = MessageBox(au, "Ingrese un correo", "invalido", MB_OK);
					uyu = 1;
				}
				else
				{
					lol = strlen(con);
					if (lol == 0)
					{
						int  res = MessageBox(au, "Ingrese contraseña", "invalido", MB_OK);
						uyu = 1;
					}
					else
					{
						lol = strlen(nom);
						if (lol == 0)
						{
							int  res = MessageBox(au, "Ingrese un su nombre", "invalido", MB_OK);
							uyu = 1;
						}
						else
						{
							lol = strlen(apP);
							if (lol == 0)
							{
								int  res = MessageBox(au, "Ingrese un su apellido paterno", "invalido", MB_OK);
								uyu = 1;
							}
							else
							{
								lol = strlen(apM);
								if (lol == 0)
								{
									int  res = MessageBox(au, "Ingrese un su apellido materno", "invalido", MB_OK);
									uyu = 1;
								}
								else
								{
									lol = strlen(gen);
									if (lol == 0)
									{
										int  res = MessageBox(au, "seleccione un genero", "invalido", MB_OK);
										uyu = 1;
									}
								}
							}
						}
					}
				}
			}

			if (wasa == 0 && uyu == 0)
			{
				insertar(arbol, cum, usu, cor, con, nom, apP, apM, gen);
				SetDlgItemText(au, 1006, "");
				SetDlgItemText(au, 1007, "");
				SetDlgItemText(au, 1008, "");
				SetDlgItemText(au, 1010, "");
				SetDlgItemText(au, 1012, "");
				SetDlgItemText(au, 1014, "");
				SetDlgItemText(au, 1016, "");
			}
		}

		if (LOWORD(wParam) == 1162)
		{
			OPENFILENAME ofn;
			char szFileName[MAX_PATH] = "";

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = au;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof(szFileName);
			ofn.lpstrFilter = "Archivos de Imagen\0*.bmp;\0";
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

			// carga de mapa de bits
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);

			if (GetOpenFileName(&ofn)) {
				HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
				if (hBitmap != NULL) {
					HWND hwndStatic = GetDlgItem(au, 1163);
					SendMessage(hwndStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

					imagen = hBitmap;  // Guarda el identificador del mapa de bits en la variable global
					strcpy_s(fotito, szFileName);
					

					MessageBox(au, "Imagen cargada exitosamente", "CARGA EXITOSA", MB_OK);
				}
				else 
				{
					MessageBox(au, "Error al cargar la imagen", "ERROR UnU", MB_OK | MB_ICONERROR);
				}
			}

		}

		if (LOWORD(wParam) == 1033)
		{
			DestroyWindow(au);
			usuVector.clear();
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{

	}
	break;
	}
	return 0;
}

usuarios *nvnodo(SYSTEMTIME cum, char usu[], char cor[], char con[], char nom[], char apP[], char apM[], char gen[])
{
	usuarios* nuevo = new usuarios;
	nuevo->cumple = cum;
	_itoa_s(nuevo->cumple.wYear, nuevo->anio, 10);
	_itoa_s(nuevo->cumple.wMonth, nuevo->mes, 10);	
	_itoa_s(nuevo->cumple.wDay, nuevo->dia, 10);
	strcpy_s(nuevo->usuario, usu);
	strcpy_s(nuevo->correo, cor);
	strcpy_s(nuevo->contra, con);
	strcpy_s(nuevo->nombre, nom);
	strcpy_s(nuevo->apellidoP, apP);
	strcpy_s(nuevo->apellidoM, apM);
	strcpy_s(nuevo->genero, gen);
	strcpy_s(nuevo->reg, ausu);
	_itoa_s(st.wMonth, nuevo->mr, 10);//fecha del registro
	_itoa_s(st.wHour, nuevo->hr, 10);
	_itoa_s(st.wDay, nuevo->dr, 10);

	strcpy_s(nuevo->imagen, fotito);

	nuevo->izq = NULL;
	nuevo->der = NULL;
	
	return nuevo;
}
void insertar(usuarios *&arbol, SYSTEMTIME cum, char usu[], char cor[], char con[], char nom[], char apP[], char apM[], char gen[])
{
	if (arbol == NULL)
	{
		usuarios* nuevo = nvnodo(cum, usu, cor, con, nom, apP, apM, gen);
		arbol = nuevo;
	}
	else
	{
			if (strlen(usu)<strlen(arbol->usuario))//strcmp compara dos strings
			{
				insertar(arbol->izq, cum, usu, cor, con, nom, apP, apM, gen);
		    }
			else
			{
				insertar(arbol->der, cum, usu, cor, con, nom, apP, apM, gen);
			}
	}
}
//HEAPSORT
void HEAP(usuarios* nodo, std::vector<usuarios>& arreglo)//guarda lo del arbol en un arreglo
{
	if (nodo != nullptr)
	{
		HEAP(nodo->izq, arreglo);
		arreglo.push_back(*nodo);
		HEAP(nodo->der, arreglo);
	}
} //guarda lo del arbol en un arreglo

LRESULT CALLBACK VUELO(HWND vue, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(vue, 1039, ausu);

		for (int a = 0; a < 4; a++)
		{
			SendDlgItemMessage(vue, 1023, CB_INSERTSTRING, a, (LPARAM)destinos[a]);
		}
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam)==1024)
		{
			GetDlgItemText(vue, 1021, ahoras, 10);
			GetDlgItemText(vue, 1022, aasientos, 10);
			GetDlgItemText(vue, 1023, adestino, 10);
			SendDlgItemMessage(vue, 1020, DTM_GETSYSTEMTIME, 0, (LPARAM)&asalida);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);

			int horiwis = atoi(ahoras);
			int ayuyu = st.wMonth + 6;
			int awas = 0; //fecha ya pasada

			if (asalida.wYear < st.wYear)
			{
				int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
				awas = 2;
			}
			else if (asalida.wMonth > st.wMonth)
			{
				awas = 0;
			}
			else
			{
				if (asalida.wDay < st.wDay)
				{
					int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
					awas = 3;
				}
				else
				{
					awas = 0;
				}
			}
			if (asalida.wYear < st.wYear)
			{
				int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
				awas = 2;
			}
			if (asalida.wMonth > ayuyu)//fecha fuera de los 6 meses
			{
				int  res = MessageBox(vue, "Ingrese una fecha anterior", "invalido", MB_OK);
				awas = 2;
			}
			int owo = 0; //hora
			if (horiwis <= 0 || horiwis > 24)
			{
				int  res = MessageBox(vue, "Ingrese una hora entre las 0 y 23", "invalido", MB_OK);
				owo = 1;
			}
			if (horiwis < st.wHour && asalida.wDay==st.wDay)
			{
				int  res = MessageBox(vue, "Ingrese una hora posterior a la actual", "invalido", MB_OK);
				owo = 1;
			}
		    //determinar asientos
			int sisi = atoi(aasientos);
			if (sisi < 10 || sisi > 20)
			{
				int  res = MessageBox(vue, "Minimo de 10 asientos y maximo de 20", "invalido", MB_OK);
				owo = 1;
			}
			int lalon = strlen(adestino);
			if (lalon==0)
			{
				int  res = MessageBox(vue, "seleccione un destino", "invalido", MB_OK);
				owo = 1;
			}

			//si todo lo anterior se cumple sin problemas se hace el proceso
			if (awas == 0 && owo == 0)
			{
				volar::cargarvuelo(asalida, ahoras, aasientos, adestino, ausu);
				SetDlgItemText(vue,1023, "");
				SetDlgItemText(vue,1022, "");
				SetDlgItemText(vue,1021, "");
			}
	    }

		if (LOWORD(wParam) == 1028)
		{
			DestroyWindow(vue);
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{
		
	}
	break;
	}
	return 0;
}

LRESULT CALLBACK LISTA(HWND lis, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(lis, 1067, ausu);

		vuelo* aux = start;
		int ya = 0;
		while (aux != NULL)
		{
			ya = 0;
			if (st.wMonth > aux->salida.wMonth)//MES
			{
				ya = 1;
			}
			else if(st.wMonth==aux->salida.wMonth)
			{
				ya = 2;
			}
			if (st.wDay > aux->salida.wDay && ya == 2)
			{
				ya = 1;
			}
			else if (st.wDay == aux->salida.wDay)
			{
				ya = 4;
			}
			if (st.wHour >= aux->salida.wHour && ya==4)
			{
				ya = 1;
			}

			if (ya == 1)
			{
				strcpy_s(aux->estado, "Efectuado");
			}
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->estado);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Estado");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->Lanio);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Año");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->Lmes);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Mes");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->Ldia);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Dia");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->Lhora);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->anio);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Año ");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->mes);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->dia);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Día ");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->hora);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->asientos);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)aux->novu);
			SendMessage(GetDlgItem(lis, 1027), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
			aux = aux->sig;
		}
		delete aux;
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1029)
		{
			DestroyWindow(lis);
		}
		if (LOWORD(wParam) == 1062) //filtrar lista de vuelos
		{
			GetDlgItemText(lis, 1064, fdia, 10);
			GetDlgItemText(lis, 1068,fmes, 10);
			GetDlgItemText(lis, 1069, fani, 10);
			HWND wero = GetDlgItem(lis, 1028);
			SendMessage(wero, LB_RESETCONTENT, 0, 0);
			volar::filtrar(fdia,fmes,fani);
		}
		if (LOWORD(wParam) == 1030)
		{
			GetDlgItemText(lis, 1049, nu, 10);

			int wasama = 0;

			if (strlen(nu) == 0)
			{
				int  res = MessageBox(lis, "Ingrese un valor", "invalido", MB_OK);
				wasama = 2;
			}
			else
			{
				volar::find(start, nu);
				//funcion para sacar la otra pantalla
			}
		}

	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{
		DestroyWindow(lis);
	}
	break;
	}
	return 0;
}

LRESULT CALLBACK VENTA(HWND ven, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(ven, 1042, ausu);

		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(ven, 1045, CB_INSERTSTRING, a, (LPARAM)generos[a]);
		}
		for (int a = 0; a < 2; a++)
		{
			SendDlgItemMessage(ven, 1047, CB_INSERTSTRING, a, (LPARAM)clase[a]);
		}
		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(ven, 1046, CB_INSERTSTRING, a, (LPARAM)metodosdp[a]);
		}

		SetDlgItemText(ven,1051,no);
		SetDlgItemText(ven, 1052, adestino);
		SetDlgItemText(ven, 1058, aa);
		SetDlgItemText(ven, 1057, mm);
		SetDlgItemText(ven, 1064, dd);
		SetDlgItemText(ven, 1062, tota);
		SetDlgItemText(ven, 1065, mano);

		pasajero* aux = principio;
		while (aux != NULL)
		{
			if (strcmp(no, aux->vuelo) == 0 && strcmp(aux->state,"Cancelado") !=0)
			{
				SendMessage(GetDlgItem(ven, 1060), LB_INSERTSTRING, 0, (LPARAM)aux->asientito);
			}
			aux = aux->sigi;
		}
		delete aux;
	}
	break;

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1048)//COMPRAR
		{
			//found NO se quedo apuntando al vuelo al que quiere subir

			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			SendDlgItemMessage(ven, 1041, DTM_GETSYSTEMTIME, 0, (LPARAM)&palpase);
			GetDlgItemText(ven, 1040,anombrep , 20);
			GetDlgItemText(ven, 1049, apaP, 20);
			GetDlgItemText(ven, 1050, apaM, 20);
			GetDlgItemText(ven, 1045, agenero, 10);
			GetDlgItemText(ven, 1044, anacio, 10);
			GetDlgItemText(ven, 1046, amdp, 10);
			GetDlgItemText(ven, 1059, aasiento, 5);
			GetDlgItemText(ven, 1047, atdb, 10);

			pasajero* aux = principio;
			int wasa = 0;
			x = atoi(aasiento);
			y = atoi(mano);
			if (strlen(anombrep) == 0)
			{
				wasa = 8;
			}
			if (strlen(agenero) == 0)
			{
				wasa = 8;
			}
			if (strlen(anacio) == 0)
			{
				wasa = 8;
			}
			if (strlen(amdp) == 0)
			{
				wasa = 8;
			}
			if (strlen(aasiento) == 0)
			{
				wasa = 8;
			}
			if (strlen(atdb) == 0)
			{
				wasa = 8;
			}

			if (x<0 && x > y)//verificar que el asiento sea valido
			{
				int  res = MessageBox(ven, "Numero de asiento invalido", "Otro", MB_OK);
				wasa = 1;
			}
			if (wasa == 8)
			{
				int  res = MessageBox(ven, "Llene todos los apartados", "Disculpe", MB_OK);
			}
			if (wasa == 0)
			{
				while (aux != NULL) //Verificar si el asiento está ocupado
				{
					if (strcmp(no, aux->vuelo) == 0 && strcmp(aux->state,"Cancelado") != 0)//revisa cuales pasajeros van a subir a dicho vuelo
					{
						if (strcmp(aasiento, aux->asientito) == 0)//revisa en que asiento van
						{
							wasa = 2;
						}
					}
					aux = aux->sigi;
				}
			}
			aux = principio;
			if (wasa == 0)
			{
				while (aux != NULL) //Verificar si el asiento está ocupado
				{
					if (strcmp(no, aux->vuelo) == 0)//revisa cuales pasajeros van a subir a dicho vuelo
					{
						if (strcmp(anombrep, aux->nombrep) == 0)//revisa en que asiento van
						{
							wasa = 9;

						}
					}
					aux = aux->sigi;
				}
			}
			if (x <= 0 || x > y)
			{
				int  res = MessageBox(ven, "ingrese un numero de asiento mayor a 0 y menor a la cantidad de asientos", "Otro", MB_OK);
				wasa = 10;
			}
			if (wasa == 2)
			{
				int  res = MessageBox(ven, "Asiento ocupado", "Otro", MB_OK);
			}
			if (wasa == 9)
			{
				int  res = MessageBox(ven, "Pasajero ya tiene boleto", "Otro", MB_OK);
			}

			x = st.wYear - palpase.wYear;
			if (y == 0)
			{
				int  res = MessageBox(ven, "no hay asientos disponibles", "Disculpe", MB_OK);
				DestroyWindow(ven);
				wasa = 3;
			}
			else if(x < 18 && md <= 0)
			{
				int  res = MessageBox(ven, "cupo para menores lleno", "Disculpe", MB_OK);
				wasa = 4;
			}
			else if (x > 60 && Md <= 0)
			{
				int  res = MessageBox(ven, "cupo para mayores lleno", "Disculpe", MB_OK);
				wasa = 5;
			}

			if (wasa == 0)
			{
				pasaje::newpasajero();
				DestroyWindow(ven);
			}
		}

		if (LOWORD(wParam) == 1068)
		{
			DestroyWindow(ven);
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{

	}
	break;
	}
	return 0;
}

LRESULT CALLBACK CANCEL(HWND can, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(can,1074 , ausu);
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1071)//cancelar vuelo
		{
			GetDlgItemText(can,1069,nu,10);
			volar::cancelar(nu);
		}
	    
		if (LOWORD(wParam) == 1072)
		{
			GetDlgItemText(can, 1070, anombrep, 10);
			GetDlgItemText(can,1076 , apaM, 10);
			GetDlgItemText(can,1075, apaP, 10);
			pasaje::noboleto(anombrep);

		}

		if (LOWORD(wParam) == 1073)
		{
			DestroyWindow(can);
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{

	}
	break;
	}
	return 0;
}

LRESULT CALLBACK REGI(HWND reg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(reg, 1085, ausu);

		vuelo* hu = start;
		while (hu != NULL)
		{
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->hr);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Hora de registro");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->dr);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Día de registro");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->mr);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Mes de registro");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->vusu);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Usuario que esta registrando");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Registro");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->estado);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Estado");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->Lanio);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Año");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->Lmes);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Mes");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->Ldia);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Dia");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->Lhora);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->anio);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Año ");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->mes);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->dia);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Día ");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->hora);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->asientos);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)hu->novu);
			SendMessage(GetDlgItem(reg, 1075), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");

			hu = hu->sig;
		}

		vuelo* op = start;

		while (op != NULL)
		{
			if (strcmp(op->estado, "Cancelado") == 0)
			{
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"\n");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"\n");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->hr);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Hora de cancelación");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->dr);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Día de cancelación");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->mr);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Mes de cancelación");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->usuc);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Usuario que cancelo");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Cancelación");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->estado);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Estado");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->Lanio);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Año");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->Lmes);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Mes");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->Ldia);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Dia");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->Lhora);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->anio);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Año ");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->mes);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->dia);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Día ");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->hora);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->asientos);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)op->novu);
				SendMessage(GetDlgItem(reg, 1076), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
			}
			op = op->sig;
		}

		std::vector<pasajero>::iterator it;
		for (it = pasita.begin(); it != pasita.end(); it++)
		{
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->mr);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Mes");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->dr);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Día");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->hr);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Hora");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->usu);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Usuario");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Registro");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"\n");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->state);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Estado");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->mdp);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Pago");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->tdb);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Tipo de boleto");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->ep);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Edad");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->nacio);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Nacionalidad");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->asientito);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Asiento");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->vuelo);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->generop);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Genero");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->paM);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Apellido materno");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->paP);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Apellido paterno");
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)it->nombrep);
			SendMessage(GetDlgItem(reg, 1077), LB_INSERTSTRING, 0, (LPARAM)"Nombre");
			
		}
		int a = 0;
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1082)
		{
			pasita.clear();
			DestroyWindow(reg);
		}
		
		if (LOWORD(wParam) == 1081)
		{
			GetDlgItemText(reg, 1080, no, 10);

			HWND ore = GetDlgItem(reg, 1078);
			SendMessage(ore, LB_RESETCONTENT, 0, 0);

			HWND ora = GetDlgItem(reg, 1084);
			SendMessage(ora, LB_RESETCONTENT, 0, 0);


			pasajero* ol = principio;
			while (ol != NULL)
			{
				if (strcmp(no, ol->vuelo) == 0 && strcmp(ol->state, "Cancelado") != 0)
				{
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->mr);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Mes");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->dr);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Día");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->hr);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Hora");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->usu);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Usuario");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Registro");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->state);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Estado");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->mdp);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Pago");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->tdb);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Tipo de boleto");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->ep);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Edad");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->nacio);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Nacionalidad");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->asientito);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Asiento");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->vuelo);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->generop);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Genero");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->paM);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Apellido materno");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->paP);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Apellido paterno");
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)ol->nombrep);
					SendMessage(GetDlgItem(reg, 1078), LB_INSERTSTRING, 0, (LPARAM)"Nombre");
				}
				else if (strcmp(ol->state, "Cancelado") == 0)
				{
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->mr);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Mes");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->dr);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Día");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->hr);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Hora");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->usu);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Usuario");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Registro");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->state);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Estado");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->mdp);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Pago");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->tdb);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Tipo de boleto");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->ep);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Edad");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->nacio);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Nacionalidad");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->asientito);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Asiento");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->vuelo);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->generop);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Genero");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->paM);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Apellido materno");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->paP);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Apellido paterno");
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)ol->nombrep);
					SendMessage(GetDlgItem(reg, 1084), LB_INSERTSTRING, 0, (LPARAM)"Nombre");
				}
				ol = ol->sigi;
			}

			vuelo* oyo = start;
			int loko = 0;
			while (oyo != NULL)
			{
				if (strcmp(oyo->novu, no) == 0 && strcmp(oyo->estado,"Proximo")==0)
				{
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->hr);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora de registro");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->dr);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Día de registro");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->mr);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes de registro");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->vusu);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Usuario que registro");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Registro");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->estado);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Estado");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lanio);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Año");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lmes);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Ldia);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Dia");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lhora);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->anio);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Año ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->mes);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->dia);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Día ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->hora);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->asientos);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->novu);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
					loko = 1;
				}
				else if (strcmp(oyo->novu, no) == 0)
				{
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"\n");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->hc);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->dc);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Día");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->mc);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->usuc);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Usuario que cancelo");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Cancelacion");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->estado);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Estado");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lanio);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Año");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lmes);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Ldia);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Dia");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->Lhora);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora de llegada");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->anio);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Año ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->mes);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Mes ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->dia);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Día ");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->hora);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Hora de salida");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->asientos);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Asientos totales");
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)oyo->novu);
					SendMessage(GetDlgItem(reg, 1086), LB_INSERTSTRING, 0, (LPARAM)"Numero de vuelo");
					loko = 1;
				}
				oyo = oyo->sig;
			}
			if (loko == 0)
			{
				int  res = MessageBox(reg, "Vuelo no encontrado", "invalido", MB_OK);
			}
		}
	}
	break;
	case WM_CLOSE:
	{

	}
	break;
	case WM_DESTROY:
	{

	}
	break;
	}
	return 0;
	}

LRESULT CALLBACK PASE(HWND pas, UINT msg, WPARAM wParam, LPARAM lParam)
{
		switch (msg)
		{
		case WM_INITDIALOG:
		{
			pasajero* pla = principio;
			while (pla != NULL)
			{
				if (strlen(pla->hPA) != 0 && strcmp(anombrep, pla->nombrep) == 0 && strcmp(apaP, pla->paP) == 0 && strcmp(apaM, pla->paM) == 0 && strcmp(pla->state, "Cancelado") != 0)
				{
					SetDlgItemText(pas, 1093,pla->nombrep);
					SetDlgItemText(pas, 1094, pla->paP);
					SetDlgItemText(pas, 1095, pla->paM);
					SetDlgItemText(pas, 1096, pla->vuelo);
					SetDlgItemText(pas, 1097, pla->tdb);
					SetDlgItemText(pas, 1098, pla->ep);
					SetDlgItemText(pas, 1099, pla->generop);
					SetDlgItemText(pas, 1100, pla->asientito);
					SetDlgItemText(pas, 1101, pla->hPA);
					SetDlgItemText(pas, 1102, pla->dPA);
					SetDlgItemText(pas, 1103, pla->mPA);
					SetDlgItemText(pas, 1104, pla->anioPA);
				}
				pla = pla->sigi;
			}
		}
		break;
		case WM_COMMAND:
		{
			if (LOWORD(wParam == 1092))
			{
				DestroyWindow(pas);
			}
		}
		break;
		case WM_CLOSE:
		{

		}
		break;
		case WM_DESTROY:
		{

		}
		break;
		}
		return 0;
}

//Ediciones
LRESULT CALLBACK EVUELO(HWND edivue, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(edivue, 1111, ausu);
		SendDlgItemMessage(edivue, 1106, DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&asalida);
		SetDlgItemText(edivue, 1107, ahoras);
		SetDlgItemText(edivue, 1109, adestino);

		for (int a = 0; a < 4; a++)
		{
			SendDlgItemMessage(edivue, 1109, CB_INSERTSTRING, a, (LPARAM)destinos[a]);
		}

	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1110)
		{
			GetDlgItemText(edivue, 1107, ahoras, 10);
			GetDlgItemText(edivue, 1109, adestino, 10);
			SendDlgItemMessage(edivue, 1106, DTM_GETSYSTEMTIME, 0, (LPARAM)&asalida);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);

			int horiwis = atoi(ahoras);
			int ayuyu = st.wMonth + 6;
			int awas = 0; //fecha ya pasada

			if (asalida.wYear < st.wYear)
			{
				int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
				awas = 2;
			}
			else if (asalida.wMonth > st.wMonth)
			{
				awas = 0;
			}
			else
			{
				if (asalida.wDay < st.wDay)
				{
					int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
					awas = 3;
				}
				else
				{
					awas = 0;
				}
			}
			if (asalida.wYear < st.wYear)
			{
				int  res = MessageBox(vue, "Ingrese una fecha posterior", "invalido", MB_OK);
				awas = 2;
			}
			if (asalida.wMonth > ayuyu)//fecha fuera de los 6 meses
			{
				int  res = MessageBox(vue, "Ingrese una fecha anterior", "invalido", MB_OK);
				awas = 2;
			}
			int owo = 0; //hora
			if (horiwis <= 0 || horiwis > 24)
			{
				int  res = MessageBox(vue, "Ingrese una hora entre las 0 y 23", "invalido", MB_OK);
				owo = 1;
			}
			if (horiwis < st.wHour && asalida.wDay == st.wDay)
			{
				int  res = MessageBox(vue, "Ingrese una hora posterior a la actual", "invalido", MB_OK);
				owo = 1;
			}

			if (awas == 0 && owo == 0)
			{
				volar::cargarvuelo2(asalida, ahoras, adestino, ausu);
				SetDlgItemText(edivue, 1107, "");
				SetDlgItemText(edivue, 1109, "");

			}
		}
	}
	break;
	case WM_CLOSE:
	{
	}
	break;
	case WM_DESTROY:
	{
	}
	break;
	}
	return 0;
}

LRESULT CALLBACK EPASE(HWND epas, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(epas, 1147, ausu);
		SendDlgItemMessage(epas, 1131, DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&palpase);

		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(epas, 1135, CB_INSERTSTRING, a, (LPARAM)generos[a]);
		}
		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(epas, 1137, CB_INSERTSTRING, a, (LPARAM)metodosdp[a]);
		}
		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(epas, 1139, CB_INSERTSTRING, a, (LPARAM)clase[a]);
		}
		
		//Datos anteriores
		SetDlgItemText(epas, 1132, anombrep);
		SetDlgItemText(epas, 1133 ,apaP );
		SetDlgItemText(epas, 1134 ,apaM );
		SetDlgItemText(epas, 1135 ,agenero);
		SetDlgItemText(epas, 1136 ,anacio );
		SetDlgItemText(epas, 1137 ,amdp);
		SetDlgItemText(epas, 1138 ,aasiento);
		SetDlgItemText(epas, 1139 ,atdb);

		//Datos de venta
		SetDlgItemText(epas, 1140, noma);
		SetDlgItemText(epas, 1141,adestino);
		SetDlgItemText(epas, 1142, aa);
		SetDlgItemText(epas,1143 , mm);
		SetDlgItemText(epas,1144 , dd);
		SetDlgItemText(epas, 1145, tota);
		SetDlgItemText(epas, 1148, mano);

		pasajero* aux = principio;
		while (aux != NULL)
		{
			if (strcmp(avue, aux->vuelo) == 0 && strcmp(aux->state, "Cancelado") != 0)
			{
				SendMessage(GetDlgItem(ven, 1146), LB_INSERTSTRING, 0, (LPARAM)aux->asientito);
			}
			aux = aux->sigi;
		}
		delete aux;


	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1150)
		{
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			SendDlgItemMessage(epas, 1131, DTM_GETSYSTEMTIME, 0, (LPARAM)&palpase);
			GetDlgItemText(epas, 1132, anombrep, 20);
			GetDlgItemText(epas, 1133, apaP, 20);
			GetDlgItemText(epas, 1134, apaM, 20);
			GetDlgItemText(epas, 1135, agenero, 10);
			GetDlgItemText(epas, 1136, anacio, 10);
			GetDlgItemText(epas, 1137, amdp, 10);
			GetDlgItemText(epas, 1138, aasiento, 5);
			GetDlgItemText(epas, 1139, atdb, 10);

			pasajero* aux = principio;
			int wasa = 0;
			x = atoi(aasiento);
			y = atoi(mano);
			if (strlen(anombrep) == 0)
			{
				wasa = 8;
			}
			if (strlen(agenero) == 0)
			{
				wasa = 8;
			}
			if (strlen(anacio) == 0)
			{
				wasa = 8;
			}
			if (strlen(amdp) == 0)
			{
				wasa = 8;
			}
			if (strlen(aasiento) == 0)
			{
				wasa = 8;
			}
			if (strlen(atdb) == 0)
			{
				wasa = 8;
			}

			if (x<0 && x > y)//verificar que el asiento sea valido
			{
				int  res = MessageBox(epas, "Numero de asiento invalido", "Otro", MB_OK);
				wasa = 1;
			}
			if (wasa == 8)
			{
				int  res = MessageBox(epas, "Llene todos los apartados", "Disculpe", MB_OK);
			}
			if (wasa == 0)
			{
				while (aux != NULL) //Verificar si el asiento está ocupado
				{
					if (strcmp(no, aux->vuelo) == 0 && strcmp(aux->state, "Cancelado") != 0)//revisa cuales pasajeros van a subir a dicho vuelo
					{
						if (strcmp(aasiento, aux->asientito) == 0)//revisa en que asiento van
						{
							wasa = 2;
						}
					}
					aux = aux->sigi;
				}
			}
			aux = principio;
			if (wasa == 0)
			{
				while (aux != NULL) //Verificar si el asiento está ocupado
				{
					if (strcmp(no, aux->vuelo) == 0)//revisa cuales pasajeros van a subir a dicho vuelo
					{
						if (strcmp(anombrep, aux->nombrep) == 0)//revisa en que asiento van
						{
							wasa = 9;

						}
					}
					aux = aux->sigi;
				}
			}
			if (x <= 0 || x > y)
			{
				int  res = MessageBox(ven, "ingrese un numero de asiento mayor a 0 y menor a la cantidad de asientos", "Otro", MB_OK);
				wasa = 10;
			}
			if (wasa == 2)
			{
				int  res = MessageBox(ven, "Asiento ocupado", "Otro", MB_OK);
			}
			if (wasa == 9)
			{
				int  res = MessageBox(ven, "Pasajero ya tiene boleto", "Otro", MB_OK);
			}

			x = st.wYear - palpase.wYear;
			if (y == 0)
			{
				int  res = MessageBox(ven, "no hay asientos disponibles", "Disculpe", MB_OK);
				DestroyWindow(ven);
				wasa = 3;
			}
			else if (x < 18 && md <= 0)
			{
				int  res = MessageBox(ven, "cupo para menores lleno", "Disculpe", MB_OK);
				wasa = 4;
			}
			else if (x > 60 && Md <= 0)
			{
				int  res = MessageBox(ven, "cupo para mayores lleno", "Disculpe", MB_OK);
				wasa = 5;
			}

			if (wasa == 0)
			{
				DestroyWindow(epas);
				pasaje::newpasajero();
			}
		}
	}
	break;
	case WM_CLOSE:
	{
	}
	break;
	case WM_DESTROY:
	{
	}
	break;
	}
	return 0;
}

LRESULT CALLBACK EUSU(HWND eusu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(eusu, 1151, DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&cum);

		for (int a = 0; a < 3; a++)
		{
			SendDlgItemMessage(eusu, 1158, CB_INSERTSTRING, a, (LPARAM)generos[a]);
		}

		SetDlgItemText(eusu, 1160, ausu);
		SetDlgItemText(eusu, 1161, usu );
		SetDlgItemText(eusu, 1153 ,cor );
		SetDlgItemText(eusu, 1154,con );
		SetDlgItemText(eusu, 1155,nom );
		SetDlgItemText(eusu, 1156, apP);
		SetDlgItemText(eusu, 1157, apM);
		SetDlgItemText(eusu, 1158, gen);
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1159)
		{
			SendDlgItemMessage(eusu, 1151, DTM_GETSYSTEMTIME, 0, (LPARAM)&cum);
			SendDlgItemMessage(Hwnd, 1025, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);

			GetDlgItemText(eusu, 1153 ,cor, 10);
			GetDlgItemText(eusu, 1154, con, 10);
			GetDlgItemText(eusu, 1155, nom, 10);
			GetDlgItemText(eusu, 1156, apP, 10);
			GetDlgItemText(eusu, 1157, apM, 10);
			GetDlgItemText(eusu, 1158, gen, 10);

			int wasa = 0;
			if (st.wYear - cum.wYear < 18)
			{
				int  res = MessageBox(eusu, "Edad insuficiente", "invalido", MB_OK);
				wasa = 1;
			}
			int uyu = 0;
			int lol = strlen(usu);

			if (lol == 0)
			{
				int  res = MessageBox(eusu, "Ingrese un  nombre de usuario", "invalido", MB_OK);
				uyu = 1;
			}
			else
			{
				lol = strlen(cor);
				if (lol == 0)
				{
					int  res = MessageBox(eusu, "Ingrese un correo", "invalido", MB_OK);
					uyu = 1;
				}
				else
				{
					lol = strlen(con);
					if (lol == 0)
					{
						int  res = MessageBox(eusu, "Ingrese contraseña", "invalido", MB_OK);
						uyu = 1;
					}
					else
					{
						lol = strlen(nom);
						if (lol == 0)
						{
							int  res = MessageBox(eusu, "Ingrese un su nombre", "invalido", MB_OK);
							uyu = 1;
						}
						else
						{
							lol = strlen(apP);
							if (lol == 0)
							{
								int  res = MessageBox(eusu, "Ingrese un su apellido paterno", "invalido", MB_OK);
								uyu = 1;
							}
							else
							{
								lol = strlen(apM);
								if (lol == 0)
								{
									int  res = MessageBox(eusu, "Ingrese un su apellido materno", "invalido", MB_OK);
									uyu = 1;
								}
								else
								{
									lol = strlen(gen);
									if (lol == 0)
									{
										int  res = MessageBox(eusu, "seleccione un genero", "invalido", MB_OK);
										uyu = 1;
									}
								}
							}
						}
					}
				}
			}

			if (wasa == 0 && uyu == 0)
			{
				usul::edite(arbol,usu);
				SetDlgItemText(eusu, 1160, "");
				SetDlgItemText(eusu, 1152, "");
				SetDlgItemText(eusu, 1153, "");
				SetDlgItemText(eusu, 1154, "");
				SetDlgItemText(eusu, 1155, "");
				SetDlgItemText(eusu, 1156, "");
				SetDlgItemText(eusu, 1157, "");
				SetDlgItemText(eusu, 1158, "");
				DestroyWindow(eusu);
			}
		}
	}
	break;
	case WM_CLOSE:
	{
	}
	break;
	case WM_DESTROY:
	{
	}
	break;
	}
	return 0;
}

void guardarArbolBinario(usuarios* nodo,ofstream& archivin) {
	if (nodo == nullptr) {
		return;
	}

	// Guarda los datos del nodo en el archivo
	archivin.write(reinterpret_cast<const char*>(nodo), sizeof(usuarios));

	// Llama recursivamente a la función para los hijos izquierdo y derecho
	guardarArbolBinario(nodo->izq, archivin);
	guardarArbolBinario(nodo->der, archivin);

}

//EL ULTIMO USUARIO
void nultimito()
{
	std::ifstream archivo("datito.bin", std::ios::binary);

	archivo.read(ausu, sizeof(ausu));

	archivo.close();
}

//CARGAR ARBOLES BINARIOS
usuarios* insertarEnOrden(usuarios* raiz, usuarios* nuevoNodo) {

	if (raiz == nullptr) {
		return nuevoNodo;
	}

	if (strlen(nuevoNodo->usuario) < strlen(raiz->usuario))
	{
		raiz->izq = insertarEnOrden(raiz->izq, nuevoNodo);
	}
	else{
		raiz->der = insertarEnOrden(raiz->der, nuevoNodo);
	}

	return raiz;
}
void insertar(usuarios*& arbol,usuarios* nodo)
{
	if (arbol == NULL)
	{
		usuarios* nuevo = nvnodo(cum, usu, cor, con, nom, apP, apM, gen);
		arbol = nuevo;
	}
	else
	{
		if (strlen(arbol->usuario) < strlen(arbol->usuario))//strcmp compara dos strings
		{
			insertar(arbol->izq,nodo);
		}
		else
		{
			insertar(arbol->der,nodo);
		}
	}
}
usuarios* cargarArbolBinario(ifstream& archivo) {
	usuarios* nodo = nullptr;
	usuarios temp;

	// Lee un nodo del archivo
	archivo.read(reinterpret_cast<char*>(&temp), sizeof(usuarios));

	while (!archivo.eof()) {
		// Crea un nuevo nodo con los datos leídos
		usuarios* nodo = new usuarios;
		*nodo = temp;
		nodo->izq = nullptr;
		nodo->der = nullptr;

		// Inserta el nuevo nodo en el árbol manteniendo el orden
		arbol = insertarEnOrden(arbol, nodo);

		// Lee el siguiente nodo del archivo
		archivo.read(reinterpret_cast<char*>(&temp), sizeof(usuarios));
	}
	return arbol;

}

//GUARDAR Y CARGAR LOS VUELOS
void savuelos()
{
	wchar_t documentosDir[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_MYDOCUMENTS, nullptr, 0, documentosDir)))
	{
		std::wstring documentosPath(documentosDir);
		std::wstring archivoPath = documentosPath + L"\\EdD_Final\\Vuelos.bin";
		std::ofstream arc(archivoPath, std::ios::binary | std::ios::out);

		if (!arc.is_open())
		{
			MessageBox(NULL, "Error al guardar", "No se pudo", MB_OK | MB_ICONERROR);
			return;
		}

		vuelo* este = start;
		while (este != nullptr)
		{
			arc.write(reinterpret_cast<const char*>(este), sizeof(vuelo));
			este = este->sig;
		}
		arc.close();
	}
	else
	{
		MessageBox(NULL, "Error al obtener la ruta de documentos", "No se pudo", MB_OK | MB_ICONERROR);
	}
}
void carvuelos()
{
	wchar_t documentosDir[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_MYDOCUMENTS, nullptr, 0, documentosDir)))
	{
		std::wstring documentosPath(documentosDir);
		std::wstring archivoPath=documentosPath + L"\\EdD_Final\\Vuelos.bin";
		std::ifstream arc(archivoPath, std::ios::binary | std::ios::in);

		if (!arc.is_open())
		{
			return;
		}
		while (start != nullptr)
		{
			vuelo* temp = start;
			start = start->sig;
			delete temp;
		}
		vuelo leido;
		while (arc.read(reinterpret_cast<char*>(&leido), sizeof(vuelo)))
		{
			vuelo* nuvuelo = new vuelo;
			memcpy(nuvuelo, &leido, sizeof(vuelo));

			nuvuelo->sig = start;
			nuvuelo->ant = nullptr;

			if (start != nullptr)
			{
				start->ant = nuvuelo;
			}
			start = nuvuelo;
		}
		arc.close();
	}
}
//GUARDAR Y CARGAR PASAJEROS
void sapas()
{
	wchar_t documentosDir[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_MYDOCUMENTS, nullptr, 0, documentosDir)))
	{
		std::wstring documentosPath(documentosDir);
		std::wstring archivoPath = documentosPath + L"\\EdD_Final\\Pass.bin";
		std::ofstream arcee(archivoPath, std::ios::binary | std::ios::out);

		if (!arcee.is_open())
		{
			MessageBox(NULL, "Error al guardar", "No se pudo", MB_OK | MB_ICONERROR);
			return;
		}

		pasajero* onda = principio;
		while (onda != nullptr)
		{
			arcee.write(reinterpret_cast<const char*>(onda), sizeof(pasajero));
			onda = onda->sigi;
		}
		arcee.close();
	}
	else
	{
		MessageBox(NULL, "Error al obtener la ruta de documentos", "No se pudo", MB_OK | MB_ICONERROR);
	}
}
void carpas()
{
	wchar_t documentosDir[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_MYDOCUMENTS, nullptr, 0, documentosDir)))
	{
		std::wstring documentosPath(documentosDir);
		std::wstring archivoPath = documentosPath + L"\\EdD_Final\\Vuelos.bin";
		std::ifstream arcee(archivoPath, std::ios::binary | std::ios::in);

		if (!arcee.is_open())
		{
			return;
		}
		while (principio != nullptr)
		{
			pasajero* onda = principio;
			principio = principio->sigi;
			delete onda;
		}
		pasajero* leido;
		while (arcee.read(reinterpret_cast<char*>(&leido), sizeof(pasajero)))
		{
			pasajero* nupa = new pasajero;
			memcpy(nupa, &leido, sizeof(pasajero));

			nupa->sigi = principio;
			nupa->anti = nullptr;

			if (principio != nullptr)
			{
				principio->anti = nupa;
			}
			principio = nupa;
		}
		arcee.close();
	}
}