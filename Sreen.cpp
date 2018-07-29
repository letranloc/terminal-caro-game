#include "Func.h"
void sreen(BOARD brd,bool single)
{
	resizeConsole(125,58);
	
	string a[4];
	char key=-1;
	extern ACCOUNT usr1,usr2;
	int	tbx,tby,
		count1 = 0,
		count2 = 0;
	CELL p1,p2;
	
	for(int r=0;r<brd.row;r++)
		for(int c=0;c<brd.col;c++)
			if(brd.map[r][c]==1) count1++;
			else if(brd.map[r][c]==2) count2++;

	tbx=(92-brd.col*2)/2;
	tby=(54-brd.row)/2;
	while(key!=101)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
		cout<<" Caro Game: Matching     ";

		Drawline(tbx,tby,brd.row,brd.col,brd.c);	//Vẽ bàn cờ
		for(int r=0;r<brd.row;r++)
			for(int c=0;c<brd.col;c++)
			{
				gotoxy(r*2+2+tbx,c+1+tby);
				if(brd.map[r][c]==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
					printf("%c",brd.player[0].s);
				}
				else if(brd.map[r][c]==2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
					printf("%c",brd.player[1].s);
				}
			}
			// Phím chức năng
		gotoxy(1,52);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"OPTION   (Press O)";
		gotoxy(1,53);
		cout<<"HELP     (Press F1)";
		gotoxy(110,52);
		cout<<"(Press E)  EXIT";
		gotoxy(54,52);
		cout<<"UNDO  (Press U)";
		Textbox(5,32,93,40,"Game                          ");

		gotoxy(95,42);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if(brd.turn==1) cout<<usr1.usr<<" turn!!!!!!";		
		else cout<<usr2.usr<<" turn!!!!!!";	
		// Thông tin hai người chơi
		Info(1,usr1,brd.player[0].s,brd.player[0].c,count1,5);
		Info(0,usr2,brd.player[1].s,brd.player[1].c,count2,20);

		int xx = brd.col%2==0?tbx+brd.col:tbx+brd.col-1,
			yy = brd.row/2+tby;

		gotoxy(xx,yy);
		if (key==98)
			key=-1;

		saveTemp(brd);

		while(key!=101 && key!=98)
		{
			int Poin=-1;
			key=getkey();
			controlP(key,xx,yy,Poin);
			if (xx<tbx+2) xx=tbx+brd.col*2-4;
			if (xx>(tbx+brd.col*2-4)) xx=tbx+2;
			if (yy<tby+1) yy=tby+brd.row-2;
			if (yy>tby+brd.row-2) yy=tby+1;
			gotoxy(xx,yy);
			// Người chơi thứ nhất đánh
			if (brd.turn==1 &&(key==13||key==9)&&brd.map[(xx-tbx-2)/2][yy-tby-1]==-1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
				printf("%c",brd.player[0].s);
				brd.map[(xx-tbx-2)/2][yy-tby-1] = brd.turn;
				p1.row = (xx-tbx-2)/2;
				p1.col = yy-tby-1;
				count1++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(109,20);
				cout<<"           ";
				gotoxy(109,20);
				cout<<count1;

				gotoxy(95,42);				
				cout<<"                          ";
				gotoxy(95,42);	
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
				cout<<usr2.usr<<" turn!!!!!!";				
				gotoxy(xx,yy);
				brd.turn = 2;
				saveTemp(brd);
				if(checkWin(brd)>-1) brd.turn = -1;
			}
			// Người chơi thứ hai đánh
			if(brd.turn==2&&single==1)
			{
				
				CELL p = Move(brd,2);
				xx = p.row*2+2+tbx;
				yy = p.col+1+tby;
				gotoxy(xx,yy);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
				printf("%c",brd.player[1].s);	brd.map[p.row][p.col] = brd.turn;
				p2 = p;
				count2++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(109,35);
				cout<<"           ";
				gotoxy(109,35);
				cout<<count2;

				gotoxy(95,42);
				cout<<"                       ";
				gotoxy(95,42);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
				cout<<usr1.usr<<" turn!!!!!!";
				gotoxy(xx,yy);
				brd.turn = 1;
				saveTemp(brd);
			}

			else if (brd.turn==2&&(key==13||key==9)&&single==0&&brd.map[(xx-tbx-2)/2][yy-tby-1]==-1)
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
				printf("%c",brd.player[1].s);	brd.map[(xx-tbx-2)/2][yy-tby-1] = brd.turn;
				p2.row = (xx-tbx-2)/2;
				p2.col = yy-tby-1;
				count2++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(109,35);
				cout<<"           ";
				gotoxy(109,35);
				cout<<count2;

				gotoxy(95,42);
				cout<<"                       ";
				gotoxy(95,42);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
				cout<<usr1.usr<<" turn!!!!!!";
				gotoxy(xx,yy);
				brd.turn = 1;
				saveTemp(brd);
			}
			// Kiểm tra thắng thua
			if(checkWin(brd)>-1)
			{
				int x0=tbx+brd.col-10,
					y0=brd.row/2;
				if(checkWin(brd)==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
					Congratulation(x0,y0,brd.player[0].usr,count1);
					
					infoAcc(brd.player[0].usr,usr1);
					usr1.score.win++;
					updateAcc(usr1);
					infoAcc(brd.player[1].usr,usr2);
					usr2.score.lose++;
					updateAcc(usr2);
				}
				else if(checkWin(brd)==2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
					Congratulation(x0,y0,brd.player[1].usr,count2);

					infoAcc(brd.player[1].usr,usr2);
					usr2.score.win++;
					updateAcc(usr2);
					infoAcc(brd.player[0].usr,usr1);
					usr1.score.lose++;
					updateAcc(usr1);
				}
				else if(checkWin(brd)==0)
				{
					Textbox(3,30,x0,y0,"");
					gotoxy(x0+1,y0+1);
					cout<<"           Draw!!!          ";

					infoAcc(brd.player[0].usr,usr1);
					usr1.score.draw++;
					updateAcc(usr1);
					infoAcc(brd.player[1].usr,usr2);
					usr2.score.draw++;
					updateAcc(usr2);
					_getch();
				}
				remove(FILE_TEMP);	//Xóa tạm

				Textbox(4,30,x0,y0," Messenger box!             ");
				gotoxy(x0+1,y0+1);
				cout<<"Play again?                 ";
				a[0] = "      Yes     ";
				a[1] = "      No     ";
				Poin = 0;
				while (key!=101)
				{
					printout(a,Poin,2,0,0,x0+1,y0+2);
					key=getkey();
					AcessP(key,Poin,1,0);
					if(key==13&&Poin==0)
					{
						for(int r=0;r<brd.row;r++)
							for(int c=0;c<brd.col;c++)
								brd.map[r][c] = -1;
						key=98;
						count1 = count2 = 0;
						brd.turn = 1;
						break;
					} else if(key==13&&Poin==1) key = 101;
				}
				if(key==101) break;
			}
			
			//Phần cài đặt
			if (key==111||key==79)
			{
				clr();
				int Pointer=0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
				gotoxy(1,52);
				cout<<" OPTION ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				while(key!=101 && key!=98)
				{
					a[0]="   LineColor   ";
					a[1]="    Player     ";
					a[2]=" Apply & Resume";
					a[3]="     Renew     ";
					printout(a,Pointer,4,0,0,10,52);
					// Thay đổi bàn cờ
					if (Pointer==0)
					{
						key=-1;
						int poin=0;
						string b[8];
						b[0]="              ";
						b[1]="Xanh bien nhat";
						b[2]="Vang nhat     ";
						b[3]="Xam           ";
						b[4]="Trang nhat    ";
						b[5]="Xanh nhat     ";
						b[6]="None          ";
						b[7]="              ";
						Textbox(10,30,10,42,"Line color                  ");
						gotoxy(30,44);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);cout<<"_";
						gotoxy(30,45);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);cout<<"_";
						gotoxy(30,46);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);cout<<"_";
						gotoxy(30,47);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);cout<<"_";
						gotoxy(30,48);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);cout<<"_";
						gotoxy(30,49);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);cout<<" ";
						gotoxy(30,50);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);cout<<" ";
						gotoxy(30,43);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);cout<<" ";
						while (key!=77 && key!=75 && key!=13)
						{					
							printout(b,poin,8,1,1,11,43);
							key=getkey();
						
							AcessPo(key,poin,7,1);
							if (key==13)
							{
								switch(poin)
								{
								case 1: brd.c=3; break;
								case 2: brd.c=6; break;
								case 3: brd.c=8; break;
								case 4: brd.c=7; break;
								case 5: brd.c=2; break;
								case 6: brd.c=0; break;
								}
								Pointer=1;
								printout(a,Pointer,4,0,0,10,52);
							}
						
						}
						if(key==77)
						{
							Pointer = 1;
							printout(a,Pointer,4,0,0,10,52);
						}
					}
					// Thay đổi symbol
					if (Pointer==1)
					{
						Textbox(10,30,10,42,"Player symbol               ");
						key=-1;
						int poin=0;
						string b[8];
						b[0]="Tim do        ";
						b[1]="O vang        ";
						b[2]="X do          ";
						b[3]="X xanh bien   ";
						b[4]="O xanh        ";
						b[5]="Ro vang       ";
						b[6]="Mat cuoi xanh ";
						b[7]="Mat cuoi do   ";
						gotoxy(30,43);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);printf("%c",3);
						gotoxy(30,44);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);printf("O");
						gotoxy(30,45);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);printf("X");
						gotoxy(30,46);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);printf("X");
						gotoxy(30,47);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);cout<<"O";
						gotoxy(30,48);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);printf("%c",4);
						gotoxy(30,49);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);printf("%c",2);
						gotoxy(30,50);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);printf("%c",2);
						while (key!=77 && key!=75 && key!=13)
						{					
							printout(b,poin,8,1,1,11,43);
							key=getkey();
						
							AcessPo(key,poin,7,1);
							if (key==13)
							{
								int plc,pls;
								switch(poin)
								{
								case 0: plc=12;pls=3;break;
								case 1: plc=14;pls=79; break;
								case 2: plc=12;pls=88; break;
								case 3: plc=11;pls=88; break;
								case 4: plc=10;pls=79; break;
								case 5: plc=14;pls=4; break;
								case 6: plc=10;pls=2; break;
								case 7: plc=12;pls=2; break;
								}
								if (brd.turn==1)
								{
									if (plc==brd.player[1].c)
									{
										brd.player[1].s=brd.player[0].s;
										brd.player[1].c=brd.player[0].c;
									}
									brd.player[0].s=pls;
									brd.player[0].c=plc;
								}
								else
								{
									if (plc==brd.player[0].c)
									{
										brd.player[0].s=brd.player[1].s;
										brd.player[0].c=brd.player[1].c;
									}
									brd.player[1].s=pls;brd.player[1].c=plc;
								}
								Pointer=2;
								clr();
								printout(a,Pointer,4,0,0,10,52);
							}
						}
						if(key==75)
						{
							Pointer = 0;
							continue;
						}
						else if(key==77)
						{
							Pointer = 2;
							clr();
							printout(a,Pointer,4,0,0,10,52);
						}
					}
				
					key=getkey();
					AcessPo(key,Pointer,3,0);
					// Reset lại trò chơi
					if (key==13 && Pointer==3)
					{
						string b[2];
						b[0]="       Yes       ";
						b[1]="       No       ";
						int ppoint=0;
						Textbox(4,35,30,10," Messenger Box                   ");
						gotoxy(31,11);
						printf("Do you sure to Reset the game    ");
						while(key!=98)
						{
							printout(b,ppoint,2,0,2,31,12);
							key=getkey();
							AcessPo(key,ppoint,1,0);
							if(key==13&&ppoint==0)
							{
								//Reset lại mảng
								for(int r=0;r<brd.row;r++)
									for(int c=0;c<brd.col;c++)
										brd.map[r][c] = -1;
								key=98;
								count1 = count2 = 0;
								brd.turn = 1;
							}
							if(key==13&&ppoint==1) key=98;
						}
					}

					if ((Pointer>1))
						clr();
				
					if (Pointer==2 && key==13)
					{
						Textbox(3,30,30,10," Messenger Box              ");
						gotoxy(31,11);
						printf("Your change is actived!     ");
						key=getkey();
					
						if (key==13)
						key=98;
					}
				}
			}
			// menu trợ giúp
			if(key==59)
			{
				gotoxy(1,53);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
				cout<<" HELP ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				int x0=30,
					y0=10;
				Textbox(20,40,x0,y0," Instructions                         ");
				gotoxy(x0+1,y0+1); cout<<"                                      ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				gotoxy(x0+1,y0+2);  cout<<"   *";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									  cout<<" Players try to make five or more ";
				gotoxy(x0+1,y0+3);  cout<<" symbols in a horizontal, vertical or";
				gotoxy(x0+1,y0+4);  cout<<" diagonal line!                       ";
				gotoxy(x0+1,y0+5); cout<<"                                      ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				gotoxy(x0+1,y0+6);  cout<<"- Control keys:                       ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(x0+1,y0+7);  cout<<"   + Move Up:     Forward arrow / [W] ";
				gotoxy(x0+1,y0+8);  cout<<"   + Move Down:   Backward arrow / [S]";
				gotoxy(x0+1,y0+9);  cout<<"   + Move Right:  Right arrow / [D]   ";
				gotoxy(x0+1,y0+10); cout<<"   + Move Left:   Left arrow / [A]    ";
				gotoxy(x0+1,y0+11); cout<<"   + Sign key:    Enter / [Tab]       ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				gotoxy(x0+1,y0+12); cout<<"                                      ";
				gotoxy(x0+1,y0+13); cout<<"- Other key:                          ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(x0+1,y0+14); cout<<"   + Option:      Press [O]           ";
				gotoxy(x0+1,y0+15); cout<<"   + Exit:        Press [E][ESC]      ";
				gotoxy(x0+1,y0+16); cout<<"                                      ";
				gotoxy(x0+1,y0+17);cout<<"      Press any key to go back!       ";
				gotoxy(x0+1,y0+18); cout<<"                                      ";
				_getch();
				key = 98;
				gotoxy(1,53);
				cout<<"HELP ";
			}
			// Chức năng undo
			if(key=='u'||key=='U')
			{
				gotoxy(53,52);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
				cout<<" UNDO ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(95,42);
				cout<<"                       ";
				gotoxy(95,42);
				// Chế độ chơi single
				if(single==1&&p1.row>-1&&p2.row>-1)
				{
					cout<<"Player "<<usr1.usr<<" undo...";
					Sleep(1000);
					//undo nước đi của máy!
					brd.map[p2.row][p2.col] = -1;
					gotoxy(p2.row*2+2+tbx,p2.col+1+tby);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.c);
					cout<<char(197);
					//undo nước đi của người chơi
					brd.map[p1.row][p1.col] = -1;
					gotoxy(p1.row*2+2+tbx,p1.col+1+tby);
					cout<<char(197);
					gotoxy(95,42);
					cout<<"                       ";
					gotoxy(95,42);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
					cout<<usr1.usr<<" turn!!!!!!";
					gotoxy(p1.row*2+2+tbx,p1.col+1+tby);
					brd.turn = 1;
					p1.row = -1;
				}
				// Chế độ hai người chơi
				else if(single==0)//Chỉ undo được khi người chơi thứ hai chưa đánh
				{
					//undo nước đi của người chơi thứ 1
					if(brd.turn==2&&p1.row>-1)
					{
						cout<<"Player "<<usr1.usr<<" undo...";
						Sleep(1000);
						brd.map[p1.row][p1.col] = -1;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.c);
						gotoxy(p1.row*2+2+tbx,p1.col+1+tby);
						cout<<char(197);
						gotoxy(95,42);
						cout<<"                       ";
						gotoxy(95,42);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[0].c);
						cout<<usr1.usr<<" turn!!!!!!";
						gotoxy(p1.row*2+2+tbx,p1.col+1+tby);
						brd.turn = 1;
						p1.row = p2.row = -1;
					}
					//undo nước đi của người chơi thứ 2
					else if(brd.turn==1&&p2.row>-1)
					{
						cout<<"Player "<<usr2.usr<<" undo...";
						Sleep(1000);
						brd.map[p2.row][p2.col] = -1;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.c);
						gotoxy(p2.row*2+2+tbx,p2.col+1+tby);
						cout<<char(197);
						gotoxy(95,42);
						cout<<"                       ";
						gotoxy(95,42);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), brd.player[1].c);
						cout<<usr2.usr<<" turn!!!!!!";
						gotoxy(p2.row*2+2+tbx,p2.col+1+tby);
						brd.turn = 2;
						p2.row = p1.row = -1;
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(53,52);
				cout<<" UNDO ";
				gotoxy(xx,yy);
			}
			// Chức năng lưu game khi thoát
			if (key==101||key==69||key==27)
				{
					gotoxy(120,52);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
					cout<<" EXIT ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Textbox(4,32,30,10," Messenger Box                ");
					gotoxy(31,11);
					printf("Do you want to save the game  ");
					string b[3];
					b[0]="   Yes    ";
					b[1]="    No    ";
					b[2]="  Cancel  ";
					int ppoint=0;
					while (key!=98)
					{
						
						printout(b,ppoint,3,0,-5,31,12);
						key=getkey();
						AcessPo(key,ppoint,2,0);
						if (key==13 && ppoint==2)
							key=98;
						if (key==13 && ppoint==0)
						{
							if(updateBoard(brd))
							{
								remove(FILE_TEMP);
								Textbox(4,32,30,10," Messenger Box                ");
								gotoxy(31,11);
								printf("Game saved!                  ");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
								gotoxy(31,12);
								printf("             Ok               ");
								_getch();
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								key = 101;
								break;
							}
							else
							{
								Textbox(4,32,30,10," Messenger Box                ");
								gotoxy(31,11);
								printf(" Error: Can't save the game!  ");
								string b[2];
								b[0]="     Ok        ";
								b[1]="     Cancel    ";
								while (key!=98)
								{
									printout(b,ppoint,2,0,0,31,12);
									key=getkey();
									AcessPo(key,ppoint,1,0);
									if(key==13&&ppoint==0)
									{
										key = 101;
										break;
									}
									else if(key==13&&ppoint==1) key = 98;
								}
								if(key==101) break;
							}
						}
						if (key==13 && ppoint==1)
						{
							key=101;
							remove(FILE_TEMP);
							break;
						}
					}
				}
		}
	}
	//Trở về menu chính
	system("cls");
}
     