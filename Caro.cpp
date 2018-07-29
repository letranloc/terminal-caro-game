#include "Func.h"

ACCOUNT usr1,usr2;
BOARD b;

void main()
{
	SetConsoleTitle(L"Caro Game");
	resizeConsole(50,30);

	if(firstRun()) loading();
	int Pointer=0;
	int slot=0;
	char key=1;

	// Kiểm tra ván cuối nếu thoát không đúng cách
	if(isFile(FILE_TEMP))
	{
		resizeConsole(50,30);
		Textbox(4,38,5,13," Messenger box                      ");
		gotoxy(6,14);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"WARM:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<" Do you want restore last game?";
		string a[2];
		a[0] = "    Yes    ";
		a[1] = "     No    ";
		while (true)
		{
			printout(a,Pointer,2,0,0,11,15);
			key = getkey();
			AcessPo(key,Pointer,1,0);
			if(key==13&&Pointer==0)
			{
				FILE* FILE;
				if(fopen_s(&FILE,FILE_TEMP,"r+b")==0)
				{
					readBoard(b,FILE);
					fclose(FILE);

					infoAcc(b.player[0].usr,usr1);
					infoAcc(b.player[1].usr,usr2);
					if(b.level==-1) sreen(b,0);
					else sreen(b);
				}
				else
				{
					Textbox(3,32,10,13," Messenger box               ");
					gotoxy(11,14);	
				//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout<<"ERROR:";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout<<" Can't load game!       ";
					_getch();
				}
				system("cls");
				key=105;
				slot = 1;
				break;
			}
			if(key==13&&Pointer==1)
			{
				key=-1;
				remove(FILE_TEMP);
				system("cls");
				break;
			}
		}
	}
	Pointer = 0;
	// Menu chính
	while (key != 101 )
	{
		resizeConsole(50,30);
		gotoxy(1,1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
		cout<<" Caro Game ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		string a[5];

		//Đăng kí tài khoản
		if (key==13 && Pointer==1)
		{
			signup(usr1,slot);
			if (slot==1)
			{
				key=105;
				Pointer = 0;
				usr1.admin = false;
			}
		}
		//Đã đăng nhập
		if ((key==13 && Pointer==0)||key==105)
		{
			if (slot==1 || dangnhap(key,usr1)==1)
			{
				system("cls");
				key=1;
				while(key!=101)
				{
					// menu chọn trò chơi
					if ((key==13 && Pointer==0)||key==110)
					{
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
						cout<<" Caro Game: New Game     ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

						while(key!=101)
						{
							resizeConsole(50,30);
							
							a[0]="     Quick     ";
							a[1]="   Multiplay   ";
							a[2]="     Back      ";	
							printout(a,Pointer,3,1,2,18,10);	
							key=getkey();
							AcessP(key,Pointer,2,1);
							if((key==13&&Pointer<2)||key==113)
							{
								system("cls");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
								cout<<" Caro Game: Initializing     ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								
								// Các thiết lập ban đầu
								strcpy_s(b.player[0].usr,usr1.usr);
								do
								{
									string s;
									gotoxy(5,14);
									cout<<"num-Row (20 - 50):           ";
									gotoxy(24,14);
									s = getname(1,24,14);
									if(s.length()!=2||s[0]<'0'||s[0]>'9'||s[1]<'0'||s[1]>'9') continue;
									b.row = ((int)s[0]-48)*10 + (int)s[1]-48; 
								}while(b.row>50||b.row<20);
								do
								{
									string s;
									gotoxy(5,15);
									cout<<"num-Col (20 - 45):          ";
									gotoxy(24,15);
									s = getname(1,24,15);
									if(s.length()!=2||s[0]<'0'||s[0]>'9'||s[1]<'0'||s[1]>'9') continue;
									b.col = ((int)s[0]-48)*10 + (int)s[1]-48; 
								}while(b.col<20||b.col>45);

								if(Pointer==0)
								{
									do
									{
										string s;
										gotoxy(5,16);
										cout<<"Level (max: 6)   :           ";
										gotoxy(24,16);
										s = getname(1,24,16);
										if(s.length()!=1||s[0]<'1'||s[0]>'6') continue;
										b.level = (int)s[0]-48; 
									}while(b.level<1||b.level>6);
									strcpy_s(b.player[1].usr,"Computer");
									infoAcc(b.player[1].usr,usr2);
								}

								else
								{
									gotoxy(10,17);
									cout<<"Waiting for player 2...";
									Sleep(500);
									if(dangnhap(key,usr2)==0)
									{
										Textbox(4,26,13,5," Messenger Box          ");
										gotoxy(14,6);
										cout<<"Do you want sign up?";
										string c[2];
										c[0]="    Yes  ";
										c[1]="    No   ";
										while (key!=101)
										{
											printout(c,Pointer,2,0,0,14,7);
											key=getkey();
											AcessP(key,Pointer,1,0);
											if(key==13&&Pointer==0)
											{
												signup(usr2,slot);
												if(slot==1);
												break;
											}								
										}
										if(key==101)
										{
											system("cls");
											break;
										}
									}
									b.level = -1;
									strcpy_s(b.player[1].usr,usr2.usr);
								}
								intiBoard(b);
								if(b.level==-1) sreen(b,0);
								else sreen(b);
							}
						}
						Pointer = 0;
					}
					// menu tiếp tục trò chơi
					if ((key==13 && Pointer==1)||key==115)
					{
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
						cout<<" Caro Game: Game saved  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						Pointer = 0;
						while(key!=101)
						{
							resizeConsole(50,30);
							a[0]="  Countinoue   ";
							a[1]="  Clear game   ";
							a[2]="     Back      ";	
							printout(a,Pointer,3,1,2,18,10);
							key=getkey();
							AcessP(key,Pointer,2,1);

							if(key==13&&Pointer<2)
							{
								int pPointer = 0;
								BOARD *brd = new BOARD[10];
								int n;
								listBoard(brd,n,usr1.usr);
								system("cls");
								if(n<1)
								{
									Textbox(3,32,13,14," Messenger box                ");
									gotoxy(14,15);
									cout<<"No data saved!";
									_getch();
									system("cls");
									break;
								}

								gotoxy(1,1);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
								cout<<" Caro Game: Game saved  ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								while (key!=101)
								{
									listBoard(brd,n,usr1.usr);

									resizeConsole(50,30);
									for(int i=0;i<n;i++)
									{
										Textbox(4,40,6,3+4*i,"");
										Textbox(3,6,40,4+4*i,"");
										gotoxy(7,4+4*i);
										cout<<"Match: ";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
										cout<<brd[i].player[0].usr<<" vs "<<brd[i].player[1].usr;
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
										gotoxy(7,5+4*i);
										printf_s("Last: %d:%d:%d %d/%d/%d",brd[i].last.h,brd[i].last.m,brd[i].last.s,brd[i].last.day,brd[i].last.month,brd[i].last.year);
									}
									while (key!=101)
									{
										string *c = new string[n+1];
										for(int i=0;i<n;i++)
											if(Pointer==0) c[i] = "PLAY";
											else c[i] = " DEL";
										c[n] = "<= BACK";
										printout(c,pPointer,n+1,1,4,41,5);
										key=getkey();
										AcessP(key,pPointer,n,1);
										if (key==101) system("cls");
										if(key==13&&Pointer==0)
										{
											if(brd[pPointer].level==-1)
											{
												system("cls");
												gotoxy(10,17);
												cout<<"Waiting for player 2...";
												Sleep(500);
												if(dangnhap(key,usr2)==0||(string)usr2.usr!=(string)brd[pPointer].player[1].usr)
												{
													system("cls");
													Textbox(3,30,12,14," Messenger box              ");
													gotoxy(14,15);
												//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
													cout<<"ERROR: ";
													SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
													cout<<"Player is incorrect!";
													_getch();
													system("cls");
													break;
												}
											} else strcpy_s(usr2.usr,"Computer");
											if(brd[pPointer].level==-1) sreen(brd[pPointer],0);
											else sreen(brd[pPointer]);
											Pointer = 0;
											break;
										}
										if(key==13&&Pointer==1)
										{
											system("cls");
											Textbox(3,32,10,14," Messenger box                ");
											gotoxy(14,15);
											cout<<"Deleting data...";
											Sleep(500);
											if(clearBoard(brd[pPointer].id)==0)
											{
												Textbox(3,32,10,14," Messenger box                ");
												gotoxy(14,15);
												//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
												cout<<"ERROR:";
												SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
												cout<<"Can't delete!";
											}
											else
											{
												Textbox(3,32,10,14," Messenger box                ");
												gotoxy(14,15);
												cout<<"Successful!          ";
											}
											_getch();
											system("cls");
											Pointer = 1;
											break;
										}
									}
								}
							}
						}
						Pointer = 1;
					}

					if(key==13&&Pointer==2)
					{
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
						cout<<" Caro Game: My Account  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						Pointer = 0;
						a[0]="    Information   ";
						a[1]="  Change Password ";
						a[2]="        Back      ";	
						while(key!=101)
						{
							printout(a,Pointer,3,1,2,18,10);
							key=getkey();
							AcessP(key,Pointer,2,1);
							if(key==13&&Pointer==0)
							{
								system("cls");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
								cout<<" Caro Game: My Account  ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

								Textbox(13,40,5,5,"");
								gotoxy(23,6);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
								cout<<"INFO";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								gotoxy(7,9);  cout<<"- Name: "<<usr1.usr;
								gotoxy(7,10); cout<<"- Account type: "<<(usr1.admin==1?"Administrator":"Normal user");
								gotoxy(7,11); cout<<"- Total score: "<<usr1.score.total;
								gotoxy(7,12); cout<<"- Record: "<<usr1.score.max;
								gotoxy(7,13); cout<<"- Achivement: "<<usr1.score.win<<" win "<<usr1.score.draw<<" draw "<<usr1.score.lose<<" lose";
								gotoxy(7,14); cout<<"- Rank: ";
								cout<<usr1.rank;
								gotoxy(7,15); printf_s("- Last: %d:%d:%d %d/%d/%d",usr1.score.last.h,usr1.score.last.m,usr1.score.last.s,usr1.score.last.day,usr1.score.last.month,usr1.score.last.year);
								gotoxy(23,30);
								cout<<" BACK ";
								_getch();
								gotoxy(23,30);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
								cout<<" BACK ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								Sleep(500);
								system("cls");
								Pointer = 0;
							}
							if(key==13&&Pointer==1)
							{
								string pass = "",
									pass1 = "",
									pass2 = "";
								while (key!=101)
								{
									system("cls");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
									cout<<" Caro Game: Change Password  ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

									gotoxy(5,14);cout<<"Old Password:";
									pass = getname(0,24,14);
									if(pass!="")
									{
										gotoxy(5,15);cout<<"New Password:";
										pass1 = getname(0,24,15);
										gotoxy(5,16);cout<<"Re-NewPassword:";
										pass2 = getname(0,24,16);
									}
									if(pass==""||pass1==""||pass2==""||pass.length()<1||pass.length()>21||pass1.length()<1||pass1.length()>21||pass2.length()<1||pass2.length()>21||pass1!=pass2||changePwd(usr1.usr,pass,pass1)==0)
									{
										system("cls");
										Textbox(4,30,10,14," Messenger box              ");
										gotoxy(12,15);
										cout<<"Password is Incorrect!";
										a[0] = "  Retry  ";
										a[1] = "  Back  ";
										while (true)
										{
											printout(a,Pointer,2,0,0,12,16);
											key = getkey();
											AcessP(key,Pointer,1,0);

											if((key==13&&Pointer==0)||key==101) break;
										}
									}
									else
									{
										system("cls");
										Textbox(4,30,11,14," Messenger box              ");
										gotoxy(12,15);
										cout<<"Password is changed!";
										_getch();
										system("cls");
										break;
									}
								}
								Pointer = 1;
							}
							if(key==101&&Pointer==2) system("cls");
						}
						system("cls");
						Pointer = 2;
					}

					// menu quản lí tài khoản (dành cho admin)
					if ((key==13 && Pointer==3)||key==97)
					{
						system("cls");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
						cout<<" Caro Game: Account Manager  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						Pointer = 0;
						while(key!=101)
						{
							a[0]=" Account Manager  ";
							a[1]="  Reset Password  ";
							a[2]="    Make Admin    ";
							a[3]="      Back        ";	
							printout(a,Pointer,4,1,2,18,10);
							key=getkey();
							AcessP(key,Pointer,3,1);

							if(key==13&&Pointer==0)
							{
								while (key!=101)
								{
									ACCOUNT *acc = new ACCOUNT[100];
									int n;
									listAcc(acc,n);

									system("cls");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
									cout<<" Caro Game: Account Manager  ";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
									if(n>28) resizeConsole(55,30+n-28);
									gotoxy(12,2);cout<<"Be careful with what you do!";
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
									for(int i=0;i<n;i++)
									{
										gotoxy(5,4+i);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
										cout<<acc[i].usr;
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
										gotoxy(26,4+i);
										cout<<"Score: "<<acc[i].score.total;
										gotoxy(39,4+i);
										cout<<"Rank:"<<acc[i].rank;
									}

									string *a = new string[n];
									for(int i=0;i<n;i++) a[i] = "DEL";

									gotoxy(20,30);
									cout<<"BACK (Press E)";
									while (key!=101)
									{
										printout(a,Pointer,n,1,1,1,4);
										key=getkey();
										AcessP(key,Pointer,n,1);

										if(key==13)
										{
											system("cls");
											Textbox(3,32,10,14," Messenger box                ");
											gotoxy(14,15);
											cout<<"Deleting data...";
											Sleep(500);
											if((string)acc[Pointer].usr=="admin"||delAcc(acc[Pointer].usr)==0)
											{
												Textbox(3,32,10,14," Messenger box                ");
												gotoxy(14,15);
												//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
												cout<<"ERROR:";
												SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
												cout<<"Can't delete!";
											}
											else
											{
												Textbox(3,32,10,14," Messenger box                ");
												gotoxy(14,15);
												cout<<"Successful!          ";
											}
											_getch();
											system("cls");
											break;
										}
										if(key==101)
										{
											gotoxy(20,30);
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
											cout<<" BACK ";
											SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
											Sleep(200);
											system("cls");
										}
									}
								//	key = -1;
									Pointer = 0;
								}
									
								Pointer = 0;
								key = -1;
							}

							if(key==13&&Pointer==1)
							{
								system("cls");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
								cout<<" Caro Game: Reset Password  ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(12,2);cout<<"Be careful with what you do!";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								string name = "",
										pass = "";
								while (key!=101)
								{
									gotoxy(5,14); cout<<"Usrname: ";
									name = getname(1,20,14);
									if(name!="")
									{
										gotoxy(5,15); cout<<"New Password: ";
										pass = getname(1,20,15);
									}
									if(name==""||pass==""||name.length()<1||name.length()>21||pass.length()<1||pass.length()>21||setPwd(name,pass)==0)
									{
										system("cls");
										Textbox(4,30,10,14," Messenger box              ");
										gotoxy(14,15);
										//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
										cout<<"ERROR:";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
										cout<<"Can't set!";
										a[0] = "   Retry   ";
										a[1] = "   Back   ";
										while (true)
										{
											printout(a,Pointer,2,0,0,12,16);
											key = getkey();
											AcessP(key,Pointer,1,0);

											if((key==13&&Pointer==0)||key==101) break;
										}
										if(key==101) system("cls");
									}
									else
									{
										system("cls");
										Textbox(3,30,13,14," Messenger box              ");
										gotoxy(14,15);
										cout<<"Successful!";
										_getch();
										system("cls");
										break;
									}
									system("cls");
								  }
								Pointer = 1;
								key = -1;
								}

							if(key==13&&Pointer==2)
							{
								system("cls");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
								cout<<" Caro Game: Set Admin";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

								string name = "";
								ACCOUNT acc;
								char usr[21];
								while (key!=101)
								{
									gotoxy(5,15); cout<<"Usrname: ";
									name = getname(1,20,15);
									for(int i=0;i<=name.length();i++) usr[i] = name[i];
									if(infoAcc(usr,acc)==1)
									{
										acc.admin = true;
										updateAcc(acc);
										system("cls");
										Textbox(3,30,13,14," Messenger box              ");
										gotoxy(14,15);
										cout<<"Successful!";
										_getch();
										system("cls");
										break;
									}
									else
									{
										system("cls");
										Textbox(4,30,13,14," Messenger box              ");
										gotoxy(14,15);
										//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
										cout<<"ERROR:";
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
										cout<<"Can't set!";
										a[0] = "  Retry  ";
										a[1] = "  Back  ";
										while (true)
										{
											printout(a,Pointer,2,0,0,16,16);
											key = getkey();
											AcessP(key,Pointer,1,0);

											if((key==13&&Pointer==0)||key==101) break;
										}
										system("cls");
									}
								}
								Pointer = 2;
								key = -1;
							}
						}
						system("cls");
						Pointer = 3;
					}
					// Menu sau khi đăng nhập
					{
						gotoxy(1,1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
						cout<<" Caro Game  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						a[0]="    New Game   ";
						a[1]="   Game Saved  ";
						a[2]="   My  Account ";

						if(usr1.admin==true)	// Nếu là admin
						{
						a[3]="  Adminstrator ";
						a[4]="    Sign Out   ";	
						printout(a,Pointer,5,1,2,18,10);
						key=getkey();
						AcessP(key,Pointer,4,1);
						}
						else	// Nếu chỉ là User bình thường
						{
							a[3]="    Sign Out   ";	
							printout(a,Pointer,4,1,2,18,10);
							key=getkey();
							AcessP(key,Pointer,3,1);
						}
						if (key==101)
							slot=0;
					}
				}
			}
			Pointer = 0;
		}
		//Top 5 người chơi cao nhất
		if(key==13&&Pointer==2)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
			cout<<" Caro Game: Top 5 Player  ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			
			ACCOUNT acc[5];
			int n = 5;
			updateRank();
			topAcc(acc,n);
			for(int i=0;i<n;i++)
			{
				Textbox(5,40,5,3+5*i,"");
				Textbox(3,5,6,4+5*i,"");
				gotoxy(8,5+5*i);
				cout<<acc[i].rank;
				gotoxy(12,4+5*i);
				cout<<"Name: ";
				cout<<acc[i].usr;
				gotoxy(12,5+5*i);
				cout<<"Total score: "<<acc[i].score.total;
				gotoxy(12,6+5*i);
				cout<<"Records: "<<acc[i].score.win<<" win "<<acc[i].score.draw<<" draw "<<acc[i].score.lose<<" lose";
			}
			gotoxy(23,30);
			cout<<" BACK ";
			while(getkey()!=13);
			gotoxy(23,30);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 496);
			cout<<" BACK ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			Sleep(200);
			system("cls");
			Pointer = 2;
		}

		if(key==13&&Pointer==3)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 500);
			cout<<" Caro Game: About  ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			string *a = new string[18];
			a[0] = "CARO VIET NAM";
			a[1] = "v.2.0  ";
			a[2] = "12CTT2 Class";
			a[3] = "University of Science HCM city";
			a[4] = "--------------------------------------------";
			a[5] = "          ";
			a[6] = "Coder, AI";
			a[7] = "Le Tran Loc - 1212213";
			a[8] = "          ";
			a[9] = "Designer";
			a[10] = "Nguyen Thanh Loc - 1212215";
			a[11] = "          ";
			a[12] = "Program that uses algorithms Min-Max and";
			a[13] = "Alpha-Beta Pruning";
			a[14] = "Language C++";
			a[15] = "           ";
			a[16] = "           ";
			a[17] = "Date created: 1/1/2013";
			for(int i=0;i<18;i++)
			{
				gotoxy(25-a[i].length()/2,5+i);
				if(i==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				if(i>11&&i<15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				if(i==2||i==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				if(i==1||i==6||i==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				for(int j=0;j<a[i].length();j++)
				{
					cout<<a[i][j];
					if(i==4) continue;
					Sleep(30);
				}
				Sleep(50);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			while(_getch()!=13);
			system("cls");
			Pointer = 0;
		}
		wellcome(15,2);
		// danh sách menu chính
		a[0]="    Sign In    ";
		a[1]="    Sign Up    ";
		a[2]="   High Score  ";
		a[3]="     About     ";
		a[4]="     Exit      ";
		printout(a,Pointer,5,1,2,18,14);
		cout<<endl;
		key=getkey();
		AcessP(key,Pointer,4,1);
	}
}
