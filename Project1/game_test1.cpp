#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

//asigna un nombre con respecto a ASCII
#define arriba 72
#define abajo 80
#define izquierda 75 
#define derecha 77

using namespace std;

//posiciona coordenadas.
void gotoxy(int x, int y) {
	HANDLE puntero; //indicador.
	puntero = GetStdHandle(STD_OUTPUT_HANDLE); //funcion GetStdHandle recupera el identificador de la consola, parametro (STD_OUTPUT_HANDLE) toma el control de la salida de la consola
	COORD coordenadas; //variable para coordenadas.
	coordenadas.X = x;
	coordenadas.Y = y;
	SetConsoleCursorPosition(puntero, coordenadas); //posiciona el HANDLE.
}

//dibuja los limites de la pantalla.
void bordes() {
	//		ASCII
	char x = 205;
	char y = 186;
	char nw = 201;
	char ne = 187;
	char sw = 200;
	char se = 188;
	// X
	for (int i = 0; i < 118; i++) {
		gotoxy(i, 2);
		cout << x;
		gotoxy(i, 29);
		cout << x;
	}
	// Y
	for (int i = 2; i < 30; i++) {
		gotoxy(0, i);
		cout << y;
		gotoxy(118, i);
		cout << y;
	}
	//esquinas
	gotoxy(0, 2); cout << nw;
	gotoxy(118, 2); cout << ne;
	gotoxy(0, 29); cout << sw;
	gotoxy(118, 29); cout << se;
}

// ================== persona ======================
class persona {
	int x, y;
	int hp;

public:
	persona(int _x, int _y, int _hp);
	void imprimir();
	void borrar();
	void mover();
	void vida();
};

//constructor
persona::persona(int _x, int _y, int _hp) {
	x = _x;
	y = _y;
	hp = _hp;
}

//dibuja a la persona
void persona::imprimir() {
	/*gotoxy(x, y);
	cout << " ( )";
	gotoxy(x, y + 1);
	cout << "/ | \\";
	gotoxy(x, y + 2);
	cout << " / \\";*/

	gotoxy(x, y);
	cout << "       |";
	gotoxy(x, y + 1);
	cout << " ( )   |";
	gotoxy(x, y + 2);
	cout << "/ | \\ -|-";
	gotoxy(x, y + 3);
	cout << " / \\";

}


//borra las impresiones anteriores creando un efecto de movimiento
void persona::borrar() {
	gotoxy(x, y);
	cout << "        ";
	gotoxy(x, y + 1);
	cout << "        ";
	gotoxy(x, y + 2);
	cout << "          ";
	gotoxy(x, y + 3);
	cout << "     ";
}

//controla el movimiento de la persona
void persona::mover() {
	if (_kbhit()) { //funcion que detecta si se preciona una tecla.
	char tecla = _getch();//getch() guarda la letra que se presione.
		borrar(); //		&& limites.
		if (tecla == derecha && x + 3 < 118) { 
			x++;
			gotoxy(x, y);
			cout << "       |";
			gotoxy(x, y + 1);
			cout << " ( )   |";
			gotoxy(x, y + 2);
			cout << "/ | \\ -|-";
			gotoxy(x, y + 3);
			cout << " /  \\";
			Sleep(50);
			borrar();
		}
		if (tecla == izquierda && x > 1) { 
			x--;
			gotoxy(x, y);
			cout << "       |";
			gotoxy(x, y + 1);
			cout << " ( )   |";
			gotoxy(x, y + 2);
			cout << "/ | \\ -|-";
			gotoxy(x, y + 3);
			cout << "/  \\";
			Sleep(50);
			borrar();
		}
		if (tecla == arriba && y > 1) { 
			y--;
			gotoxy(x, y);
			cout << " ( )   |";
			gotoxy(x, y + 1);
			cout << "/ | \\  |";
			gotoxy(x, y + 2);
			cout << "      -|-";
			gotoxy(x, y + 3);
			cout << " / \\";
			Sleep(50);
			borrar();
		}
		if (tecla == abajo && y + 3 < 29) { 
			y++; 
		}
	imprimir();
	}
}
	

//vida
void persona::vida() {
	gotoxy(1, 1);
	cout << "HP:";
	gotoxy(4,1);
	cout << "  ";
	for (int i = 0; i < hp; i++) {
		gotoxy(4, 1);
		cout << hp;
	}
}

// =============== enemigo test =================
class enemigo {
	int x, y;
public:
	enemigo(int _x, int _y);
	void imprimir();
	void mover();
};

enemigo::enemigo(int _x, int _y){
	x = _x;
	y = _y;
}

void enemigo::imprimir() {
	gotoxy(x, y);
	cout << '@';
}

void enemigo::mover() {
	gotoxy(x, y);
	cout << ' ';
	x--;
	if (x < 1) {
		y = rand() % 30;
		x = 118;
	}
	imprimir();
}

// ================== juego ======================
int main() {
	
	bordes();

	persona p(7, 7, 3);
	p.vida();
	p.imprimir();

	enemigo e(118, 0);

	bool game_over = false;
	while (!game_over)
	{
		e.mover();
		p.mover();
		Sleep(25);
	}

	return 0;
}