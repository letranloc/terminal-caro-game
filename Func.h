#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <iomanip>
using namespace std;


struct PLAYER
{
	char usr[21];																// Tên tài khoản
	int 	s,																	// Symbol người chơi
		    c;																	// Màu sắc người chơi
};

struct TIME
{
	int h,										
		m,										
		s,										
		day,									
		month,									
		year;									
};

struct BOARD
{
	char **map;																	// Lưu trữ các ô trên bàn cờ
	int	row,																	// Chiều rộng (số dòng)
		col,																	// Chiều dài (số cột)
		level,																	// Cấp độ đâng chơi (dành cho đánh với máy)
		id,																		// Mã (ID) bàn cờ
		turn,																	// Trạng thái bàn cờ: đến lượt ai
		c;																		// Màu sắc bàn cờ
	PLAYER player[2];															// Thông tin hai người đang chơi
	TIME last;																	// Thời gian lưu bàn cờ
};

struct SCORE
{
	int level,																	// Cấp độ người chơi
		total,																	// Tổng số điểm
		max,																	// Điểm lần chơi cao nhất
		win,																	// Tổng bàn thắng
		draw,																	// Tổng bàn hòa
		lose;																	// Tổng bàn thua
	TIME last;																	// Lần chơi (đăng nhập) cuối cùng
};

struct ACCOUNT
{
	char usr[21],																// Username dùng để đăng nhập
		pwd[21];																// Password dùng để đăng nhập
	bool admin;																	// Có quyền quản trị hay không
	int	rank;																	// Xếp hạng trong tổng số người chơi
	SCORE score;																// Điểm số
};

struct CELL
{
	int row,																	// Số dòng
		col;																	// Số cột
};

struct STATS																	// Trạng thái bàn cờ
{
	int oo,
		xoo,
		ooo,
		xooo,
		oooo,
		xoooo,
		ooooo;
};

#define  FILE_DATA		 "Data.loc"												// Tập tin lưu trữ thông tin các tài khoản
#define  FILE_GAME		 "Game.loc"												// Tập tin lưu trữ dữ liệu trò chơi
#define  FILE_TEMP		 "Temp.loc"												// Tập tin lưu bàn cờ tạm thời trong lúc đánh

#define MAX 2147483647															// Giá trị kiểu INT_MAX

TIME now();																		// trả về thời gian hiện tại
bool firstRun();																// Thiết lập các thông số mặc định cho lần đầu tiên mở game
void wellcome(int x,int y);														// Biểu tượng wellcome
void loading();
bool FEOF(FILE *FILE);															// kiểm tra cuối tập tin hay chưa
void Encrypt(char str[]);														// Mã hóa chuỗi kí tự
bool isFile(char *filename);													// Kiểm tra một tập tin có tồn tại hay không
bool signUp(string usr,string pwd);												// Đăng kí tài khoản mới
bool signIn(string usr,string pwd,ACCOUNT &acc);								// Kiểm tra đăng nhập
bool checkUsr(string usr);														// Kiểm tra usrname có tồn tại hay không
void readBoard(BOARD &b,FILE *FILE);											// Đọc dữ liệu game từ tập tin FILE_GAME
void writeBoard(BOARD b,FILE *FILE);											// Ghi dừ liệu vào tập tin FILE_GAME
void intiBoard(BOARD &b);														// Tạo mảng lưu trạng thái bàn cờ
bool loadBoard(int id,BOARD &b);												// Load game đã luu
bool clearBoard(int id);														// Xóa dữ liệu game đã lưu
bool updateBoard(BOARD b);														// Lưu game đang chơi
int  checkWin(BOARD b);															// Kiểm tra tình trạng bàn cờ
BOARD BoardCpy(BOARD b);														// Sao chép bàn giá trị bàn cờ
bool listBoard(BOARD b[],int &n,char usr[]);									// Lấy danh sách các game đã lưu
void writeAcc(ACCOUNT acc,FILE *FILE);											// Ghi dữ liệu ACCOUNT vào tập tin FILE_DATA
void readAcc(ACCOUNT &acc,FILE *FILE);											// Dọc dữ liệu ACCOUNT từ tập tin FILE_DATA
bool addAcc(ACCOUNT acc);														// Thêm tài khoản mới
bool updateAcc(ACCOUNT acc);													// Cập nhật thông tin tài khoản
bool changePwd(char usr[],string oldpwd,string newpwd);							// Thay đổi mật khẩu
bool setPwd(string usr,string newpwd);											// Đặt lại mật khẩu (cần quyền admin)
bool infoAcc(char usr[],ACCOUNT &acc);											// Lấy thông tin tài khoản
bool delAcc(char usr[]);														// Xóa tài khoản (cần quyền quản trị)
bool listAcc(ACCOUNT acc[],int &n);												// Liệt kê danh sách các tài khoản
bool topAcc(ACCOUNT acc[],int &n);												// Liệt kê top n người chơi hay nhất
bool equalArray(int a[],int b[],int g,int k);									// So sánh hai mảng
int Count(int num,int isLocked,int turn,BOARD brd);								// Đếm số đường num quân cờ bị chặn isLocked đầu
int CountAt(int row,int col,int num,int isLocked,BOARD b);						// Đếm số dường num quân cờ tại xung quanh ô đang xét
void getStats(STATS &s,int turn,BOARD brd);										// Cập nhật trạng thái bàn cờ
void gotoxy(int x,int y);														// Đưa con nháy đến tọa độ (x;y)
void resizeConsole(int width,int Height);										// Thay đổi kích thước console
int getkey();																	// Đọc một phím từ bàn phím
void printout(string a[],int poin,int n,int playout, int step,int x,int y);		// In danh sách menu lựa chọn
void AcessP(char &key, int &Pointer,int n, int playout);						// Điều khiển Pointer (loại 1)
void AcessPo(char &key, int &Pointer,int n,int playout);						//Điều khiển Pointer (loại 2)
void Textbox(int x, int y, int tox, int toy, string title);						// In textbox
void Drawline(int x,int y,int dai,int rong,int color);							// Vẽ bàn cờ
void controlP(char &key,int &x,int &y,int Poin);								// Điều khiển con nháy trên bàn cờ
void sreen(BOARD,bool=true);													// Bàn cờ
void clr();																		// Xóa màn hình
int dangnhap(char key,ACCOUNT &);												// Xử lí đăng nhập
void signup(ACCOUNT&,int &slot);												// Xử lí đăng kí
string getname(int kt,int x,int y);												// Lấy chuỗi người dùng nhập vào
void Congratulation(int,int,char[],int);										// Thông báo thắng
void Info(bool pl,ACCOUNT usr,int pls,int plc,int count,int x);					// In bảng thông tin người chơi
void updateRank();																// Cập nhật điểm số
bool saveTemp(BOARD);															// Lưu bàn cờ vào file tạm
bool isOk(BOARD b,int row,int col);												// Kiểm dòng cột
void EvaluateCell(BOARD b,int turn);											// Tính điểm cho các ô trên bàn cờ
int EvaluateBoard(BOARD b);														// Tính điểm toàn bàn cờ
CELL GetMaxCell(BOARD b);														// Tìm ô có điểm cao nhất
CELL Move(BOARD brd,int turn);													// Tính toán nước đi kế tiếp cho máy
int MaxVal(BOARD b,int alpha,int beta,int depth);								// Tính giá trị max của nước đi
int MinVal(BOARD b,int alpha,int beta,int depth);								// Tính giá trị min của nước đi