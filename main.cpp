/*
TUGAS BESAR II ALJABAR GEOMETRI
SIMULASI TRANSFORMASI LINIER PADA BIDANG 2D MENGGUNAKAN OPENGL API
OLEH : Mathias Novianto/13516021
Harry Setiawan Hamjaya/13516079
*/
#include <GL\GL.h>
#include <GL\freeglut.h>
#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
#define PI 3.14159
 
using namespace std;

GLfloat vertices[30], basic[30];
int n,m,iMulti;
GLfloat a, b;
GLfloat temp=0.1;
GLfloat x,y,dx,dy,k,dk,deg,ddeg,tempx,tempy;
int r;
int refreshMills = 30;
char c;
string s;
bool doneMulti = true;
bool baca = true;
bool done = false;
string command = "";

void menu();
/*
	Fungsi ini bertujuan untuk menampilkan menu pada tampilan terminal
*/
void stop(string t);
/*
I.S : Terdefenisi string t.
F.S : terbaca nilai a dan b untuk kasus refleksi terhadap titik (a,b)
string yang terbaca dipecah-pecah sampai ada nilai dari penanda berupa "," maupun ")" lalu nilainya diubah menjadi nilai float
*/
void read();
/*
I.S : Terdapat tampilan untuk menentukan jumlah titik yang ingin diinput
F.S : Titik-titiknya terdefenisi dan tersimpan dalamm bentuk array
Membaca titik yang diinput oleh user
*/
void translate();
/*
I.S : terdefenisi nilai tempx sebagai deltax dan tempy sebagai deltay
F.S : terjadi trasnlasi sebanyak deltax dan deltay yang terdefenisi
penambahan nilai  tiap kompononen titik dengan deltax dan deltay
*/
void dilate();
/*
I.S : terdefenisi nilai temp
F.S : dilakukannya dilatasi sebesar temp
perkalian skalar terhadap semua titik terdefenisi
*/
void rotate();
/*
I.S : terdefenisi nilai sudut serta titik putar
F.S : dilakukannya rotasi terhadap titik tersebut sebesar nilai sudut yang diberikan
rotasi terhadap titik dengan rumus yang terdefenisi
*/
void reflect();
/*
I.S : terdefenisi nilai param
F.S : dilakukannya refleksi terhadap parameter yang diberikan
refleksi dilakukan terhadap parameter input user.
*/
void shear();
/*
I.S : param terdefenisi sebagai 'x' dan 'y', k adalah faktor pengali
F.S : Terdefenisi segitiga dengan gusuran yang diinginkan
Melakukan gusuran terhadap parameter baik x maupun y sebesar k
*/
void stretch();
/*
I.S : param terdefenisi sebagai 'x' dan 'y', k adalah faktor pengali
F.S : Terdefenisi segitiga dengan rengangan yang diinginkan
Melakukan rengangan terhadap parameter baik x maupun y sebesar k
*/
void reset();
/*
I.S : segi-n acak 
F.S : segi-n sesuai dengan inputan awal user
Mengembalikan bentuk awal  dari segi n yang sudah di transformasi
*/
void custom();
/*
I.S : terdapat matriks berukuran 2*2 
F.S : bentuk akhir dari perkalian matriks dengan semua vertex yang ada
Mengubah bentuk dari segi n menjadi bentuk yang diinginkan
*/
void multiple();
/*
Melakukan beberapa perintah transformasi sekaligus serta menapilkan hasilnya tiap perintah yang diinput
*/
void Draw();
/*
Bagian Program yang digunakan untuk menggambarkan segi-n dari vertex yang diinput user
*/
void Initialize();
/*
Mengatur frame tampilan window
*/
void exit();
/*
Untuk keluar dari program
*/
void idle();
/*
Variable yang digunakan untuk melakukan perulangan guna menampilkan animasi dari transformasi yang dilakukan
*/

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutCreateWindow("Tugas Besar 2 Aljabar Geometri");
	Initialize();
	glutDisplayFunc(Draw);
	glutIdleFunc(idle);
	glutMainLoop();
 
	return 0;
}

void menu()
{
	cout << "PROGRAM TRANSFORMASI LINEAR" << endl;
	cout << "Ketik perintah yang ingin dilakukan" << endl;
	cout << "1. input" << endl;
	cout << "2. translate <dx> <dy>" << endl;
	cout << "3. dilate <k>" << endl;
	cout << "4. rotate <deg> <a> <b>" << endl;
	cout << "5. reflect <param>" << endl;
	cout << "6. shear <param> <k>" << endl;
	cout << "7. stretch <param> <k>" << endl;
	cout << "8. custom <a> <b> <c> <d>" << endl;
	cout << "9. multiple <n>" << endl;
	cout << "10. reset" << endl;
	cout << "11. exit" << endl;
}

void stop(string t)
{
	int i;
	string temp = "";
	for (i = 1; t[i] != ','; i++) {
		temp += t[i];
	}
	a = stof(temp);
	temp = "";
	i++;
	while (t[i] != ',' && t[i] != ')') {
		temp += t[i];
		i++;
	}
	b = stof(temp);
}

void read()
{
	cout << "Masukkan jumlah titiknya" << endl;
	int i = 0;
	cin >> n;
	for (i = 0; i < 3 * n; i += 3) {
		cin >> vertices[i];
		cin >> vertices[i + 1];
		cin >> vertices[i + 2];
		basic[i] = vertices[i];
		basic[i + 1] = vertices[i + 1];
		basic[i + 2] = vertices[i + 2];
	}
}

void translate(GLfloat tempx,GLfloat tempy)
{
	int i;
	for (i = 0; i < 3 * n; i++) {
		if (i % 3 == 0) {
			vertices[i] += tempx;
		}
		else if (i % 3 == 1) {
			vertices[i] += tempy;
		}
	}
	
}

void dilate(GLfloat temp)
{
	int i;
	for (i = 0; i < 3 * n; i++) {
		if (i % 3 == 0 || i % 3 == 1) {
			vertices[i] *= temp;
		}
	}
}


void rotate(GLfloat deg,GLfloat a,GLfloat b)
{
	int i;
	GLfloat tempX, tempY;
	for (i = 0; i < 3 * n; i += 3) {
		tempX = vertices[i];
		tempY = vertices[i + 1];
		vertices[i] = a + (tempX - a)*cos(deg*PI / 180.0) - (tempY - b)*sin(deg*PI / 180.0);
		vertices[i + 1] = b + (tempX - a)*sin(deg*PI / 180.0) + (tempY - b)*cos(deg*PI / 180.0);
	}
}

void reflect(string param)
{
	int i;
	if (param == "x") {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i + 1] = -vertices[i + 1];
		}
	}
	else if (param == "y") {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i] = -vertices[i];
		}
	}
	else if (param == "y=x") {
		for (i = 0; i < 3 * n; i += 3) {
			GLfloat temp;
			temp = vertices[i + 1];
			vertices[i + 1] = vertices[i];
			vertices[i] = temp;
		}
	}
	else if (param == "y=-x") {
		for (i = 0; i < 3 * n; i += 3) {
			GLfloat temp;
			temp = vertices[i + 1];
			vertices[i + 1] = -vertices[i];
			vertices[i] = -temp;
		}
	}
	else {
		stop(param);
		for (i = 0; i < 3 * n; i += 3) {
			GLfloat tempX, tempY;
			tempX = vertices[i];
			tempY = vertices[i + 1];
			vertices[i + 1] = 2 * b - tempY;
			vertices[i] = 2 * a - tempX;
		}
	}

}

void shear(char param, GLfloat k)
{
	int i;
	if (param == 'x') {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i] = vertices[i] + k*vertices[i + 1];
		}
	}
	else if (param == 'y') {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i + 1] = k*vertices[i] + vertices[i + 1];
		}
	}
	else {
		cout << "Parameter tidak terdefinisi" << endl;
	}
}

void stretch(char param,GLfloat k)
{
	int i;
	if (param == 'x') {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i] = k*vertices[i];
		}
	}
	else if (param == 'y') {
		for (i = 0; i < 3 * n; i += 3) {
			vertices[i + 1] = k*vertices[i + 1];
		}
	}
	else {
		cout << "Parameter tidak terdefinisi" << endl;
	}
}

void reset()
{
	int i;
	for (i = 0; i < 3 * n; i++) {
		vertices[i] = basic[i];
	}
}

void custom(GLfloat k1,GLfloat k2,GLfloat k3,GLfloat k4)
{
	int i;
	GLfloat tempX, tempY;
	for (i = 0; i < 3 * n; i += 3) {
		tempX = vertices[i];
		tempY = vertices[i + 1];
		vertices[i] = tempX*k1 + tempY*k2;
		vertices[i + 1] = tempX*k3 + tempY*k4;
	}
}


void multiple()
{
	int i, n;
	string command;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> command;
		if (command == "translate") {
			translate(dx,dy);
		}
		else if (command == "dilate") {
			dilate(dk);
		}
		else if (command == "rotate") {
			rotate(ddeg,x,y);
		}
		else if (command == "reflect") {
			reflect(s);
		}
		else if (command == "shear") {
			shear(c,dk);
		}
		else if (command == "stretch") {
			stretch(c,dk);
		}
		else if (command == "custom") {
			custom(x,y,tempx,tempy);
		}
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_POLYGON, 0, n);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBegin(GL_LINE_STRIP);
	glVertex2i(-500, 0);
	glVertex2i(500, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(0, -500);
	glVertex2i(0, 500);
	glEnd();
	glFlush();
}

void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void exit()
{
	exit(EXIT_FAILURE);
}

void idle()
{
	if (baca) {
		if(doneMulti)
			menu();
		cin >> command;
		if (command == "input") {
			read();
			done=true;
			r=0;
			baca = false;
		}
		else if (command == "translate") {
			cin>>x>>y;
			r=0;
			dx=x/100;
			dy=y/100;
			baca = false;
			iMulti++;
		}
		else if (command == "dilate") {
			cin>>k;
			r=0;
			dk=pow(k,0.1);
			baca = false;
			iMulti++;
		}
		else if (command == "rotate") {
			cin>>deg>>x>>y;
			r=0;
			ddeg=deg/100;
			baca = false;
			iMulti++;
		}
		else if (command == "reflect") {
			cin>>s;
			baca = false;
			iMulti++;
		}
		else if (command == "shear"){
			cin>>c>>k;
			r=0;
			dk=k/100;
			baca = false;
			iMulti++;
		}
		else if (command == "stretch"){
			cin>>c>>k;
			r=0;
			dk=pow(k,0.1);
			baca = false;
			iMulti++;
		}
		else if (command == "custom"){
			cin>>x>>y>>tempx>>tempy;
			baca = false;
			iMulti++;
		}
		else if (command == "multiple"){
			cin>>m;
			iMulti = 0;
			doneMulti = false;
			baca = true;
		}
		else if (command == "reset"){
			reset();
			baca=true;
		}
		else if (command == "exit"){
			exit();
		}
		if(iMulti==m){
			doneMulti = true;
		}
	}
	if (!baca) {
		if (command == "translate") {
			if(r<100){
				Sleep(20);
				translate(dx,dy);
				r++;
			}
			else{
				done = true;
			}
		}
		else if (command == "dilate"){
			if(r<10){
				Sleep(20);
				dilate(dk);
				r++;
			}
			else{
				done = true;
			}
		}
		else if (command == "rotate"){
			if(r<100){
				Sleep(20);
				rotate(ddeg,x,y);
				r++;
			}
			else{
				done = true;
			}
		}
		else if (command == "reflect"){
			reflect(s);
			done = true;
		}
		else if (command == "shear"){
			if(r<100){
				Sleep(20);
				shear(c,dk);
				r++;
			}
			else{
				done = true;
			}
		}
		else if (command == "stretch"){
			if(r<10){
				Sleep(20);
				stretch(c,dk);
				r++;
			}
			else{
				done = true;
			}
		}
		else if (command == "custom"){
			custom(x,y,tempx,tempy);
			done = true;
		}
	}
	if(done){
		baca = true;
		done = false;
	}
	glutPostRedisplay();
}