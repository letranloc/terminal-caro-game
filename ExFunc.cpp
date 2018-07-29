#include "Func.h"

void gotoxy(int x,int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x-1,y-1};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void resizeConsole(int Width, int Height)
{
	_COORD coord; 
	coord.X = Width; 
	coord.Y = Height; 

	_SMALL_RECT Rect; 
	Rect.Top = 0; 
	Rect.Left = 0; 
	Rect.Bottom = Height - 1; 
	Rect.Right = Width - 1; 

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

int getkey()
{
	int key=_getch();
	if (key==0||key==224)
		return _getch();
	else
		return key;
}

void printout(string a[],int poin,int n, int playout, int step,int x,int y)
{
	int z=x;
	for (int i=0;i<n;i++)
	{
		if (playout==1)
		{
			gotoxy(x,step*i+y);
		}
		else
		{
			
			gotoxy(z,y);
			z=step+15+z;
		}
		if (i==poin)
		{	
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
			cout<<a[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			cout<<a[i];
		}
	}
}

void AcessP(char &key, int &Pointer,int n,int playout)
{
	int up,down;
	if (playout==1)
	{
		up=80;
		down=72;
	}
	else
	{
		up=77;
		down=75;
	}
	if (key==up )
		{
			Pointer++;
			if (Pointer > n)
				Pointer=0;
		}
		if (key==down)
		{
			Pointer--;
			if (Pointer < 0)
				Pointer=n;
		}
		if (key==13 && Pointer==n)
			key=101;
}

void Textbox(int x, int y, int tox, int toy, string title)
{
	gotoxy(tox,toy);
	
	
	for(int i=1;i<=x;i++)
	{
		if (i==1)
		{
			for(int j=1;j<=y;j++)
			{
				if (j==1)
				{
					printf("%c",218);
				}
				else
				{
					if(j==y)
					{
						printf("%c",191);
					}
					else
					{
						printf("%c",196);
					}
				}
				
			}gotoxy(tox,toy+1);
		}
		else
		{
			if (i==x)
			{
				for(int j=1;j<=y;j++)
				{
					if (j==1)
					{
						printf("%c",192);
					}
					else
					{
						if(j==y)
						{
							printf("%c",217);
						}
						else
						{
							printf("%c",196);
						}
					}
				}
			}
			else
			{
				printf("%c",179);
				gotoxy(tox+y-1,toy+i-1);
				printf("%c",179);
				gotoxy(tox,toy+i);
			}
		}
	}
	if (title != "none")
	{
	gotoxy(tox+1,toy);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
		cout<<title;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

 void Drawline(int x,int y,int dai,int rong,int color)
{
	gotoxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i=1;i<=dai;i++)
	{
		if (i==1)
		{
			for (int j=1;j<=rong;j++)
			{
				if (j==1)
					printf("%c",201);
				else
				{
					if (j==rong)
						printf("%c%c",205,187);
					else
						printf("%c%c",205,209);
				}
			}
			gotoxy(x,y+i);
		}
		else
		{
			if (i==dai)
			{
				for (int j=1;j<=rong;j++)
				{
					if (j==1)
						printf("%c",200);
					else
					{
						if (j==rong)
							printf("%c%c",205,188);
						else
							printf("%c%c",205,207);
					}
				}
				gotoxy(x,y+i);
			}
			else
			{
				for (int j=1;j<=rong;j++)
				{
					if (j==1)
						printf("%c",199);
					else
						if(j==rong)
							printf("%c%c",196,182);
						else

					printf("%c%c",196,197);
				}
				gotoxy(x,y+i);
			}
		}
	}
 }

 void controlP(char &key,int &x,int &y,int Poin)
 {
	 if (key==72||key==119)
		y--;
	 if (key==80||key==115)
		 y++;
	 if (key==77||key==100)
		 x=x+2;
	 if (key==75||key==97)
		 x=x-2;
	 if (key==13&& Poin==2)
		 key=98;
 }

 void clr()
 {
	gotoxy(1,42);
	for (int j=1;j<=920;j++)
		if (j%92==0)
		{
			cout<<" "<<endl;
		}
		else
		cout<<" ";

}

 void AcessPo(char &key, int &Pointer,int n,int playout)
{
	int up,down;
	if (playout==1)
	{
		up=80;
		down=72;
	}
	else
	{
		up=77;
		down=75;
	}
	if (key==up )
		{
			Pointer++;
			if (Pointer > n)
				Pointer=0;
		}
		if (key==down)
		{
			Pointer--;
			if (Pointer < 0)
				Pointer=n;
		}
 }
 
 string getname(int kt, int x,int y)
 {
	 string nam="";
	 int i=-1;
	 char name[100];
	 char key=-1;
	 while(key!=13&&key!=27)
		{
			
			key=getkey();
		 if (key==8 && i>=0)
			{
			
				gotoxy(x+i,y);

				cout<<" ";
				gotoxy(x+i,y);
				i--;
			}
			else
			{
				if (key!=13&&key!=8&&key!=9&&key!=27)
				{
					i++;
					gotoxy(x+i,y);
					name[i]=key;
					if (kt==1)
					cout<<name[i];
					else
						cout<<"*";
			
				}
			}
	 }
	 if (key!=27)
	 for(int j=0;j<=i;j++)
			nam=nam+name[j];
	 return nam;
}