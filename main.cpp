#include <iostream>
#include<graphics.h>
using namespace std;
int tabla[7][8];///tabla de 6 linii si 7 coloane
bool jucatorRosu=false,jucatorGalben=false;///1 rosu 2 galben

void fereastra()
{
    initwindow(700,600,"Connect 4");
    for(int i=1; i<=6; i++)
    {
        line(i*100,0,i*100,600);
        line(0,i*100,700,i*100);
    }
}
void cerc(int a,int b,int culoare)
{
    circle(b*100-50,a*100-50,49.5);
    if(culoare==1)
    floodfill(b*100-50,a*100-50,RED);
    else if(culoare==2)
        floodfill(b*100-50,a*100-50,YELLOW);
}
void rosu()
{
    setfillstyle(SOLID_FILL,RED);
    setcolor(RED);
}
void galben()
{
    setfillstyle(SOLID_FILL,YELLOW);
    setcolor(YELLOW);
}
void punereCerc(int coloana,int culoare)
{
    int i=6;
    while(i)
    {
        if(!tabla[i][coloana])
        {
            if(jucatorRosu)
                tabla[i][coloana]=1;
            else
                tabla[i][coloana]=2;

            cerc(i,coloana,culoare);
            if(jucatorRosu)
            {
                jucatorRosu=false;
                jucatorGalben=true;
                galben();
            }
            else
            {
                jucatorGalben=false;
                jucatorRosu=true;
                rosu();
            }
            break;
        }
        else i--;
    }
}


bool conditieCastig(int numar)
{
    int i,j;
    int piese;
    for(i=1; i<=6; i++)
    {
        piese=0;
        for(j=1; j<=7; j++)
        {
            if(tabla[i][j]==numar)
                piese++;
            if(piese==4)
                return true;
            if(tabla[i][j]!=numar)
                piese=0;
        }
    }
    for(j=1; j<=7; j++)
    {
        piese=0;
        for(i=1; i<=6; i++)
        {
            if(tabla[i][j]==numar)
                piese++;
            if(piese==4)
                return true;
            if(tabla[i][j]!=numar)
                piese=0;
        }
    }
    for(i=1;i<=3;i++)
        for(j=1;j<=4;j++)
        if(tabla[i][j]==numar&&tabla[i+1][j+1]==numar&&tabla[i+2][j+2]==numar&&tabla[i+3][j+3]==numar)
        return true;
    for(i=1;i<=3;i++)
        for(j=4;j<=7;j++)
        if(tabla[i][j]==numar&&tabla[i+1][j-1]==numar&&tabla[i+2][j-2]==numar&&tabla[i+3][j-3]==numar)
        return true;
    return false;


}
void afisareMatrice()
{
    for(int i=1; i<=6; i++)
    {
        for(int j=1; j<=7; j++)
            cout<<tabla[i][j]<<" ";
        cout<<endl;
    }
}
void logicaJoc()
{
    jucatorRosu=true;
    int x,y;
    fereastra();

    rosu();
    while(!conditieCastig(1)&&!conditieCastig(2))
        while(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            int matriceColoana=x/100+1;
            if(jucatorRosu)
            punereCerc(matriceColoana,1);
            else
                punereCerc(matriceColoana,2);
            // afisareMatrice();
            if(conditieCastig(1))
                cout<<"A castigat rosu";
            else if(conditieCastig(2))
                cout<<"A castigat galben";

        }
}
int main()
{
    logicaJoc();
    //Sleep(1000000);
    return 0;
}
