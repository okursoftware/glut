//gcc Yeni.c -o Okur -lGL -lGLU -lglut
/*Copyright 2016 Muhammed OKUR*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <string.h> 
#include <unistd.h> //sleep için
#include <time.h>// srand için

#define ESC 27
#define SPACE 32 

//#define asteroitHizi 2
#define gemiBaslangicHizi 5
#define kursunHizi 15
int score ;
int asteroitHizi[3]; 
int krsnAdet = 0;
int tus[5];// tus kontrol için
int zorluk ;
int scoreKontrol =0;
//int ast[4][2];

int asteroitBelirleme = 0;//asteroit adet için ama sorunlu

struct gemim{
	float gemiCizim[8][2];
	int gemiHizi;
	
	}uzayGemisi;

struct kursunum{
	int aktif;
	int kursunCizim[4][2];
	
	}krsn[100];
struct asteroitim{
	int asteroitCizim[4][2];
	
}asteroitler[5];

//void asteroid();
void asteroitCizim();
void asteroitHareket(); 
void gemiCizim();
void gemiHareket();
void kursunCizim();
void kursunbaslangic(float x);
void kursunHareket(int adet);
void display();
void myKey(unsigned char key,int x,int y);
void upmyKey(unsigned char key,int x,int y);
void init();
void carpismaKontrol();
void scoreHesapla();
void skorYaz();
int randomAsteroitPosizyon();

int randomAsteroitPosizyon() //rasgele sayi uretme
{    
        int n;
     	srand(time(NULL));
		n=rand()%520;
		return n;
}


void kursunCizim(){ // kursun cizme
	int d;
	glColor3f(1.0,1.0,0.0);
	for(d=0;d<100;d++){
		glBegin(GL_POLYGON);
	    glVertex2f(krsn[d].kursunCizim[0][0],krsn[d].kursunCizim[0][1]);
        glVertex2f(krsn[d].kursunCizim[1][0],krsn[d].kursunCizim[1][1]);
        glVertex2f(krsn[d].kursunCizim[2][0],krsn[d].kursunCizim[2][1]);
        glVertex2f(krsn[d].kursunCizim[3][0],krsn[d].kursunCizim[3][1]);
	glEnd();
	}glutPostRedisplay();
	//if(tus[3]==1)
	kursunHareket(krsnAdet);
	//kursunHareket(krsnAdet+1);
			
}

void kursunbaslangic(float x){//kursun ilk çıkış yeri belirleme	
	
		krsn[krsnAdet].kursunCizim[0][0] = x-3;
		krsn[krsnAdet].kursunCizim[1][0] = x-3;
		krsn[krsnAdet].kursunCizim[2][0] = x+2;
		krsn[krsnAdet].kursunCizim[3][0] = x+2;
	    krsn[krsnAdet].kursunCizim[0][1] = 710;
	    krsn[krsnAdet].kursunCizim[1][1] = 720;
	    krsn[krsnAdet].kursunCizim[2][1] = 720;
	    krsn[krsnAdet].kursunCizim[3][1] = 710;
	//glutPostRedisplay();
	
	
}

void kursunHareket(int adet){//kursun yukarı kareketi
	
	int a;
	int i =0;
	carpismaKontrol();
	     if(krsn[adet].kursunCizim[0][1]>0){
	         for(a=0;a<4;a++){
				
		            krsn[adet].kursunCizim[a][1] -=kursunHizi;  
		            // krsn[krsnAdet+1].kursunCizim[a+5][1] -=kursunHizi;              								
	            }//glutPostRedisplay();
   
             }
}



void asteroitCizim(int d){
	int i , j = 0,k;
		glColor3f(1.0,1.0,1.0); // beyaz
	    glBegin(GL_POLYGON);
	
		for(i=0;i<4;i++){
		
		glVertex2f(asteroitler[0].asteroitCizim[i][j],asteroitler[0].asteroitCizim[i][j+1]);
	
	}
	
	glEnd();
	glColor3f(0.0,1.0,1.0); // beyaz
	    glBegin(GL_POLYGON);
	
		for(i=0;i<4;i++){
		
		glVertex2f(asteroitler[1].asteroitCizim[i][j],asteroitler[1].asteroitCizim[i][j+1]);
	
	}
	
	glEnd();
	
	carpismaKontrol();// kursun carpısma kontrol

	asteroitHareket(d);
}

void asteroitHareket(int d){	// asteroid hareket
	
	int i ;
              if(score == 5)//score 5 olunca zorluk artır
	  	      zorluk = 2;
	  	       if(score == 10)//score 10 olunca score artır
	  	      zorluk = 4;

			 if(asteroitler[0].asteroitCizim[3][0]>596)
	  	     asteroitHizi[0] = -1-zorluk;
	  	     if(asteroitler[0].asteroitCizim[0][0]<4)
	  	     asteroitHizi[0] = 1+zorluk;
		      for(i=0;i<4;i++){
			     asteroitler[0].asteroitCizim[i][0]+= asteroitHizi[0];
			     
	  	     }//glutPostRedisplay();
	  	     if(asteroitler[1].asteroitCizim[3][0]>595)
	  	     asteroitHizi[1] = 2+zorluk;
	  	     if(asteroitler[1].asteroitCizim[0][0]<5)
	  	     asteroitHizi[1] = -2-zorluk;
	  	     for(i=0;i<4;i++){
			     asteroitler[1].asteroitCizim[i][0]-= asteroitHizi[1];
			     
	  	     }glutPostRedisplay();
	  	     
   
	     
	
}

void  gemiCizim()    //gemi cizme
{

	glColor3f(1.0,0.1,0.1);
	
	glBegin(GL_POLYGON);
	glVertex2f(uzayGemisi.gemiCizim[0][0],uzayGemisi.gemiCizim[0][1]);
	glVertex2f(uzayGemisi.gemiCizim[1][0],uzayGemisi.gemiCizim[1][1]);	
	glVertex2f(uzayGemisi.gemiCizim[2][0],uzayGemisi.gemiCizim[2][1]);
	glVertex2f(uzayGemisi.gemiCizim[3][0],uzayGemisi.gemiCizim[3][1]);
	glVertex2f(uzayGemisi.gemiCizim[4][0],uzayGemisi.gemiCizim[4][1]);
	glVertex2f(uzayGemisi.gemiCizim[5][0],uzayGemisi.gemiCizim[5][1]);
	glVertex2f(uzayGemisi.gemiCizim[6][0],uzayGemisi.gemiCizim[6][1]);
	glVertex2f(uzayGemisi.gemiCizim[7][0],uzayGemisi.gemiCizim[7][1]);
	glEnd();
	
	gemiHareket();

}

void gemiHareket(){//gemi sag ve sool hareket
	int i;
	
	
	if(tus[2]==1)//gemi saga hareket
	{
		if(uzayGemisi.gemiCizim[4][0]<600){
			for(i=0;i<8;i++){
		     uzayGemisi.gemiCizim[i][0] += uzayGemisi.gemiHizi;
		    glutPostRedisplay();	     
	         }	       
		}   
	}else if(tus[1]==1){//gemi sola hareket
		if(uzayGemisi.gemiCizim[3][0]>0){
			for(i=0;i<8;i++){
		    uzayGemisi.gemiCizim[i][0] -= uzayGemisi.gemiHizi;
		    glutPostRedisplay();
	        }     
		}		
	}
}
void skorYaz() {//skor yazdırma
	char metin[10];
	sprintf(metin,"SCORE : %d ",score); 

	int j = strlen( metin );//metin uzunlugu
 
	glColor3f( 1, 1, 1 );
	glRasterPos2f( 15, 25 );//yeri
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, metin[i] );
	}
}

void display(){// ekrana çizdirme
	//int saniye 1;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	asteroitCizim(asteroitBelirleme);
	kursunCizim();	
    gemiCizim();
    skorYaz(); 
    
      
	glutSwapBuffers();
	// sleep(100);
}


void myKey(unsigned char key,int x,int y){
	int i ;
	 switch(key)
		 {
			case ESC: 
			//printf("esc basildi \n"); 
			 exit(0);break;//esc
			case 'w':
			// printf("w basildi \n");   
			tus[0] = 1; break;
			case 'a': 
			//printf("a basildi \n");  
			tus[1] = 1; break;		
			case 'd': 
			//printf("d basildi \n");  
			tus[2] = 1; break;	
			case SPACE:
			//printf("space basildi \n");	
			//tus[3] = 1;
			scoreKontrol = 0;
			kursunbaslangic(uzayGemisi.gemiCizim[0][0]);
			kursunHareket(krsnAdet);
			break;
			case 'r':  break;
		
		  }glutPostRedisplay();
}

void upmyKey(unsigned char key,int x,int y) //normal butonlar
 {
	  
	  switch(key)
		 {
			
			case 'w': 
			//printf("w cekildi \n");   
			tus[0] = 0; break;
			case 'a': 
			//printf("a cekildi \n");  
			tus[1] = 0; break;		
			case 'd': 
			//printf("d cekildi \n");  
			tus[2] = 0; break;	
			//case SPACE:printf("space basildi \n");	tus[3] = 0; break;	
		  }glutPostRedisplay();
	 
}

void carpismaKontrol(){
	// a =  krsn[krsnAdet].kursunCizim[0][0]
    
	if(krsn[krsnAdet].kursunCizim[0][1]==140)
	if(krsn[krsnAdet].kursunCizim[0][0]>asteroitler[1].asteroitCizim[1][0]&&krsn[krsnAdet].kursunCizim[0][0]<asteroitler[1].asteroitCizim[2][0]){
		 scoreKontrol++;
		//printf("\n 1.scorekontrol = %d", scoreKontrol);
	}
    
	if(krsn[krsnAdet].kursunCizim[0][1]==65)
	if(krsn[krsnAdet].kursunCizim[0][0]>asteroitler[0].asteroitCizim[1][0]&&krsn[krsnAdet].kursunCizim[0][0]<asteroitler[0].asteroitCizim[2][0]){
		scoreKontrol++;
		//printf("\n 2.scorekontrol = %d", scoreKontrol);
	}
	
	
	scoreHesapla();
	
}

void scoreHesapla(){
	if(scoreKontrol==4){
		score++;
	
	//printf("\n score = %d",score);
	scoreKontrol = 0;
	}
}
void init()  // başlangıç ayarları
{

	int d , rand, fark=0;
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(0,600,800,0,-1,1);// ekran ölçüsü

	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.2,0.2,0.2,0.0); //arkaplan rengi

	glLineWidth(4);
	
	
	for(d=0;d<5;d++){
		
		rand = randomAsteroitPosizyon();
		asteroitler[d].asteroitCizim[0][0]=0+rand+fark;
	    asteroitler[d].asteroitCizim[1][0]=0+rand+fark;
	    asteroitler[d].asteroitCizim[2][0]=100+rand+fark;
	    asteroitler[d].asteroitCizim[3][0]=100+rand+fark;
	    asteroitler[d].asteroitCizim[0][1]=50+fark;
	    asteroitler[d].asteroitCizim[1][1]=70+fark;
	    asteroitler[d].asteroitCizim[2][1]=70+fark;
	    asteroitler[d].asteroitCizim[3][1]=50+fark;
	    fark += 70;
	}
	
	uzayGemisi.gemiCizim[0][0] = 300;
	uzayGemisi.gemiCizim[1][0] = 280;
	uzayGemisi.gemiCizim[2][0] = 280;
	uzayGemisi.gemiCizim[3][0] = 270;
	uzayGemisi.gemiCizim[4][0] = 330; 
	uzayGemisi.gemiCizim[5][0] = 300;
	uzayGemisi.gemiCizim[6][0] = 320;
	uzayGemisi.gemiCizim[7][0] = 320;
	uzayGemisi.gemiCizim[0][1] = 700;
	uzayGemisi.gemiCizim[1][1] = 720;
	uzayGemisi.gemiCizim[2][1] = 770;
	uzayGemisi.gemiCizim[3][1] = 780;
	uzayGemisi.gemiCizim[4][1] = 780; 
	uzayGemisi.gemiCizim[5][1] = 770; 
	uzayGemisi.gemiCizim[6][1] = 770;
    uzayGemisi.gemiCizim[7][1] = 720;
	
	uzayGemisi.gemiHizi =gemiBaslangicHizi;
	
	asteroitHizi[0]=1;
	asteroitHizi[1]=3;
	asteroitHizi[2]=4;
	score = 0;
	zorluk = 0;
	//ast[0][0]=0+randm();ast[1][0]=0+randm();ast[2][0]=80+randm();ast[3][0]=80+randm();
	//ast[0][1]=0;ast[1][1]=80;ast[2][1]=80;ast[3][1]=0;
	
	
}
void MainMenu(int menuitem){
	char metin1[] = "a ile saga d ile sola space ile ateş edilir";
	int j = strlen( metin1 );
	 int i;
	switch(menuitem){
		case 1:
		glColor3f( 1, 1, 1 );
		glRasterPos2f( 130,130 );//yeri
	    for(i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, metin1[i] ); }break ;
		
	case 2:
	init(); break;
	case 3:
	exit(1);
              }
	}
	


 

int main(int argc, char **argv)
{

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);//renkle alakalı
	
	glutInitWindowPosition(600,200);//ekranın ilk çıkış pozizyonu

	glutInitWindowSize(600,800);//ekranın boyutu
 
	glutCreateWindow("DeadShot");//ust ekrandaki ismi
	
	init();//başlangıç fonksiyonum

	glutDisplayFunc(display);//ekranı render etme
	
	glutKeyboardFunc(myKey);//normal klavye basma fonksiyonu
	
	glutKeyboardUpFunc(upmyKey);//normal klavye cekme fonksiyonu
	

    int iMainMenu = glutCreateMenu(MainMenu);//menu oluşturma

	glutAddMenuEntry("Nasil Oynanir",1);
	glutAddMenuEntry("Tekrar Oyna",2);
	glutAddMenuEntry("Cikis",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON); //menu sag tıklama ile oluşuyor
	//	glutTimerFunc(33, time, 33);
	glutMainLoop();
	
	return 1;
}

/*Copyright 2016 Muhammed OKUR*/
