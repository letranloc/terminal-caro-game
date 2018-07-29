#include "Func.h"

void signup(ACCOUNT &acc,int &slot)
{
	char key=-1;
	int kt=0;
	string pass,pass1,name;
	while (key!=27 && kt!=1)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
		cout<<" Caro Game: Sign Up";
		gotoxy(9,10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"Username: ";
		name=getname(1,21,10);

		if (name!="")
		{
			gotoxy(9,12);
			cout<<"Password: ";
			pass=getname(0,21,12);
			gotoxy(9,14);
			cout<<"Re-Pasword: ";
			pass1=getname(0,21,14);
		}
		//Kiểm tra tài khoản
		if (pass!=pass1 || pass==""||pass1==""||pass.length()<1||pass.length()>21||pass1.length()<1||pass1.length()>21||name==""||name.length()<1||name.length()>21||checkUsr(name))
		{
			Textbox(4,26,13,5," Messenger Box          ");
			gotoxy(14,6);
			if(name==""||name.length()<1||name.length()>21) cout<<"Username is incorretc!";
			else if(pass!=pass1||pass==""||pass1==""||pass.length()<1||pass.length()>21||pass1.length()<1||pass1.length()>21) cout<<"Password is incorrect!";
			else if(checkUsr(name)) cout<<"Account already exists!"; 
			string b[2];
			b[0]="   Retry    ";
			b[1]="    Exit    ";
			int ppoint=0;
			while (1)
			{
							
				printout(b,ppoint,2,0,-3,14,7);
				key=getkey();
						//Continuos
				AcessPo(key,ppoint,1,0);
				if (key==13 && ppoint==1)
				{
					key=27;
					system("cls");
					break;
				}
				if (key==13 && ppoint==0)
				{
					system("cls");
					kt=0;
					break;
				}

			}
		}
		else kt=1;
	}

	if(key!=27)
	{
		Textbox(3,30,13,5," Messenger Box              ");
		gotoxy(14,6);
		if(signUp(name,pass)==0) cout<<"Unknown Error!";	//Lỗi không xác định có thể do quá trình ghi dữ lieu bị lỗi
		else
		{
			cout<<"Sign up successed!";
			slot=1;
		}
		_getch();
		system("cls");
		signIn(name,pass,acc);
	}
}

int dangnhap(char key,ACCOUNT &acc)
{

	string nam,pas;

	while (true)
	{
		char key=-1;
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
		cout<<" Caro Game: Sign In     ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		gotoxy(7,10);
		cout<<"Username: ";
		nam=getname(1,17,10);		
		if (key!=27&&nam!="")
		{	
			key=-1;
			gotoxy(7,12);
			cout<<"Password: ";
			pas=getname(0,17,12);	
		}

		if (nam==""||pas==""||signIn(nam,pas,acc)==0|| key==27 )
		{
			Textbox(4,26,13,5," Messenger Box          ");
			gotoxy(14,6);
			printf(" Login Fail!");
			string b[2];
			b[0]="   Retry    ";
			b[1]="    Exit    ";
			int ppoint=0;
			while (key!=98)
			{

				printout(b,ppoint,2,0,-3,14,7);
				key=getkey();
				//Continuos
				AcessPo(key,ppoint,1,0);
				if (key==13 && ppoint==1)
				{
					system("cls");
					return 0;
				}
				if (key==13 && ppoint==0)
				{
					system("cls");
					break;
				}

			}	
		} else break;	
	}
	return 1;
}