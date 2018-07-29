#include "Func.h"
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>


bool FEOF(FILE* FILE)
{
	unsigned long c = ftell(FILE),n;
	fseek(FILE,0,SEEK_END);
	n = ftell(FILE);
	if(c==n){
		fseek(FILE,c,SEEK_SET);
		return true;
	}
	else
	{
		fseek(FILE,c,SEEK_SET);
		return false;
	}
}

bool firstRun()
{
	ACCOUNT acc;
	strcpy_s(acc.usr,"admin");
	strcpy_s(acc.pwd,"m4l");
	Encrypt(acc.pwd);
	acc.admin = true;
	acc.rank = 0;
	acc.score.draw = 0;
	acc.score.last = now();
	acc.score.level = 0;
	acc.score.lose = 0;
	acc.score.max = 0;
	acc.score.total = 0;
	acc.score.win = 0;

	FILE* FILE;
	if(isFile(FILE_GAME)==0)
	{;
		fopen_s(&FILE,FILE_GAME,"wb");
		fclose(FILE);
	}
	if(isFile(FILE_DATA)==0)
		if (fopen_s(&FILE,FILE_DATA,"wb")==0)
		{
			fwrite(&acc,sizeof(ACCOUNT),1,FILE);
			fclose(FILE);
			signUp("Computer","12345");
			return true;
		}
	return false;
}

void loading()
{
	Textbox(4,50,1,14,"");
	gotoxy(2,16);
	for(int i=0;i<48;i++)
	{
		gotoxy(15,15); cout<<"Initializing..."<<i*2<<"%";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(2+i,16); cout<<char(178);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Sleep(20);
	}
	Sleep(100);
	system("cls");
}

void wellcome(int x,int y)
{
	char wc1[] =  {45,45,45,220,223,223,223,220,220,220,220,220,220,220,223,223,223,220,45,45,45,0};
	char wc2[] =  {45,45,45,219,178,178,177,177,177,177,177,177,177,177,177,178,178,219,45,45,45,0};
	char wc3[] =  {45,45,45,45,219,177,177,219,177,177,177,177,177,219,177,177,219,45,45,45,45,0};
	char wc4[] =  {45,220,220,45,45,219,177,177,177,223,219,223,177,177,177,219,45,45,220,220,45,0};
	char wc5[] =  {219,177,177,219,45,223,220,177,177,177,177,177,177,177,220,223,45,219,177,177,219,0};
	char wc6[] =  {219,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,219,0};
	char wc7[] =  {219,177,203,45,203,201,187,203,45,203,45,201,187,201,187,201,203,187,203,187,219,0};
	char wc8[] =  {219,177,186,186,186,204,45,186,45,186,45,186,45,186,186,186,186,186,204,45,219,0};
	char wc9[] =  {219,177,200,202,188,200,188,200,188,200,188,200,188,200,188,202,45,202,200,188,219,0};
	char wc10[] = {219,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,219,0};

	gotoxy(x,y);cout<<wc1;
	gotoxy(x,y+1);cout<<wc2;
	gotoxy(x,y+2);cout<<wc3;
	gotoxy(x,y+3);cout<<wc4;
	gotoxy(x,y+4);cout<<wc5;
	gotoxy(x,y+5);cout<<wc6;
	gotoxy(x,y+6);cout<<wc7;
	gotoxy(x,y+7);cout<<wc8;
	gotoxy(x,y+8);cout<<wc9;
	gotoxy(x,y+9);cout<<wc10;
	gotoxy(x,y+10);cout<<"                         ";
}

void Encrypt(char str[])
{
	char key = str[0]++;
	for(int i=0;i<strlen(str);i++)
	{
		str[i] ^= key;
		str[i]++;
		key += i;
	}
}

bool isFile(char *fileName)
{
	FILE* FILE;
	if(fopen_s(&FILE,fileName,"rb")==0){
		fclose(FILE);
		return true;
	}
	else{
		return false;
	}
}

bool signUp(string usr,string pwd)
{
	ACCOUNT acc;
	for(int i=0;i<=usr.length();i++) acc.usr[i] = usr[i];
	for(int i=0;i<=pwd.length();i++) acc.pwd[i] = pwd[i];
	Encrypt(acc.pwd);
	acc.admin = false;
	acc.rank = 0;
	acc.score.draw = 0;
	acc.score.last = now();
	acc.score.level = 0;
	acc.score.lose = 0;
	acc.score.max = 0;
	acc.score.total = 0;
	acc.score.win = 0;
	return addAcc(acc);
}

bool signIn(string usr,string pwd,ACCOUNT &acc)
{
	char name[21],pass[21];
	for(int i=0;i<=usr.length();i++) name[i] = usr[i];
	for(int i=0;i<=pwd.length();i++) pass[i] = pwd[i];
	Encrypt(pass);

	if(infoAcc(name,acc)&&(string)acc.usr==usr&&(string)acc.pwd==(string)pass)	return true;
	else return false;
}

bool checkUsr(string usr)
{
	ACCOUNT acc;
	char name[21];
	for(int i=0;i<=usr.length();i++) name[i] = usr[i];
	infoAcc(name,acc);
	if((string)acc.usr==usr) return true;
	else return false;
}

TIME now()
{

	time_t t = time(0);
	struct tm * now = localtime( & t );

	TIME TMP;
	TMP.h = now->tm_hour;
	TMP.m = now->tm_min;
	TMP.s = now->tm_sec;
	TMP.day = now->tm_mday;
	TMP.month = now->tm_mon+1;
	TMP.year = now->tm_year + 1900;
	return TMP;
}

bool equalArray(int a[],int b[],int n,int k)
{
	int count = 0;
	for(int i=0;i<n;i++)
	{
		if(a[i]==k*b[i]) count++;
		else return false;
	}
	if(count==n) return true;
	else return false;
}

void Congratulation(int x0,int y0,char usr[],int count)
{
	int score;

	if(count<=5) score = 100;
	else if(count<=10) score = 90;
	else if(count<=15) score = 75;
	else if(count<=20) score = 35;
	else score = 10;

	gotoxy(95,42);
	cout<<"                       ";
	gotoxy(95,42);
	cout<<"Game Over!!!";
	Textbox(4,30,x0,y0,"Congratulations!            ");
	gotoxy(x0+1,y0+1);
	cout<<"                            ";
	gotoxy(x0+10-strlen(usr)/2,y0+1);
	cout<<usr<<" win!  ";
	gotoxy(x0+1,y0+2);
	cout<<"                            ";
	gotoxy(x0+20,y0+2);
	cout<<"+"<<score;
	gotoxy(x0+13,y0+3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
	cout<<"  OK  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while(getkey()!=13);
	//
	ACCOUNT acc;
	infoAcc(usr,acc);
	acc.score.total += score;
	if(acc.score.max<score) acc.score.max = score;
	acc.score.last = now();
	updateAcc(acc);
	updateRank();
}
void Info(bool pl,ACCOUNT usr,int pls,int plc,int count,int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (pl==1)
		Textbox(15,32,93,10,"Player 1                      ");
	else
	{
		Textbox(15,32,93,25,"Player 2                      ");
	}
	gotoxy(95,7+x);
	cout<<"- Name: "<<usr.usr;
	gotoxy(95,8+x);
	cout<<"- Symbol: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), plc);
	cout<<(char)pls;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(95,9+x);
	cout<<"- Rank: "<<usr.rank;
	gotoxy(95,10+x);
	cout<<"- Score: "<<usr.score.total;
	gotoxy(95,11+x);
	cout<<"- Max score: "<<usr.score.max;
	gotoxy(95,12+x);
	cout<<"- Win : "<<usr.score.win;
	gotoxy(95,15+x);
	cout<<"- Total move: "<<count;
}

void updateRank()
{
	ACCOUNT *acc = new ACCOUNT[100];
	int n;
	listAcc(acc,n);
	for(int i=n-1;i>0;i--)
		for(int j=0;j<i;j++)
			if(acc[j].score.total<acc[j+1].score.total||acc[j].score.win<acc[j+1].score.win||acc[j].score.lose>acc[j+1].score.lose)
			{
				ACCOUNT temp = acc[j];
				acc[j] = acc[j+1];
				acc[j+1] = temp;
			}

	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		for(int i=0;i<n;i++)
		{
			acc[i].rank = i+1;
			fwrite(&acc[i],sizeof(ACCOUNT),1,FILE);
		}
		fclose(FILE);
	}
}


int CountAt(int row,int col,int num,int isLocked,BOARD brd)
{
	int count = 0,	//đếm số đường num quân liên tiếp
		count2,		//đếm số quân chặng đầu isLocked?
		c,r;
	bool stop;	//

	if(brd.map[row][col]==-1) return 0;	//Không có ô liền kề nào (ô đã đánh!)

	//Kiểm tra trên dòng
	if(brd.col-col>=num)
	{
		//Kiểm tra có tồn tại đường cần tìm hay không
		stop = false;
		for(c=col+1;c<col+num&&!stop;c++)
			if(brd.map[row][c]!=brd.map[row][col])  stop = true;

		if(!stop)	//nếu tồn tại
		{
			count2 = 0;
			//kiểm tra bên trái
			if((col==0)||(brd.map[row][col-1]!=-1&&brd.map[row][col-1]!=brd.map[row][col])) count2++;
			//kiểm tra bên phải
			if((col+num==brd.col)||(brd.map[row][col+num]!=-1&&brd.map[row][col+num]!=brd.map[row][col])) count2++;

			if(count2==isLocked) count++;
		}
	}
	//Kiểm tra trên cột
	if(brd.row-row>=num)
	{
		stop = false;
		for(r=row+1;r<row+num&&!stop;r++)
			if(brd.map[r][col]!=brd.map[row][col]) stop = true;

		if(!stop)
		{
			count2 = 0;
			if((row==0)||(brd.map[row-1][col]!=-1&&brd.map[row-1][col]!=brd.map[row][col])) count2++;
			if((row+num==brd.row)||(brd.map[row+num][col]!=-1&&brd.map[row+num][col]!=brd.map[row][col])) count2++;

			if(count2==isLocked) count++;
		}
	}
	//Kiểm tra trên đường chéo chính
	if(brd.row-row>=num&&brd.col-col>=num)
	{
		stop = false;
		for(r=row+1,c=col+1;r<row+num&&c<col+num&&!stop;r++,c++)
			if(brd.map[r][c]!=brd.map[row][col]) stop = true;

		if(!stop)
		{
			count2 = 0;
			if((row==0||col==0)||(brd.map[row-1][col-1]!=-1&&brd.map[row-1][col-1]!=brd.map[row][col])) count2++;
			if((row+num==brd.row||col+num==brd.col)||(brd.map[row+num][col+num]!=-1&&brd.map[row+num][col+num]!=brd.map[row][col])) count2++;

			if(count2==isLocked) count++;
		}
	}
	//Kiểm tra trên đường chéo phụ
	if(brd.row-row>=num&&col>=num-1)
	{
		stop = false;		
		for(r=row+1,c=col-1;r<row+num&&c>=0&&!stop;r++,c--)
			if(brd.map[r][c]!=brd.map[row][col]) stop = true;

		if(!stop)
		{
			int count2 = 0;
			if((row==brd.row-1||col==num)||(brd.map[row+1][col-1]!=-1&&brd.map[row+1][col-1]!=brd.map[row][col])) count2++;
			if((row==0||col==brd.col-1)||(brd.map[row-1][col+1]!=-1&&brd.map[row-1][col+1]!=brd.map[row][col])) count2++;

			if(count2==isLocked) count++;
		}
	}
	return count;
}
