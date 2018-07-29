#include "Func.h"

void writeBoard(BOARD brd,FILE* FILE)
{
	fwrite(&brd.id,sizeof(int),1,FILE);
	fwrite(&brd.row,sizeof(int),1,FILE);
	fwrite(&brd.col,sizeof(int),1,FILE);
	for(int i=0;i<brd.row;i++)
		for(int j=0;j<brd.col;j++)
			fwrite(&brd.map[i][j],sizeof(char),1,FILE);
	fwrite(brd.player,sizeof(PLAYER)*2,1,FILE);
	fwrite(&brd.turn,sizeof(int),1,FILE);
	fwrite(&brd.level,sizeof(int),1,FILE);
	fwrite(&brd.c,sizeof(int),1,FILE);
	fwrite(&brd.last,sizeof(TIME),1,FILE);
}

void readBoard(BOARD &brd,FILE* FILE)
{
	fread_s(&brd.id,sizeof(int),sizeof(int),1,FILE);
	fread_s(&brd.row,sizeof(int),sizeof(int),1,FILE);
	fread_s(&brd.col,sizeof(int),sizeof(int),1,FILE);
	
	brd.map = new char *[brd.row];
	for(int i=0;i<brd.row;i++) brd.map[i] = new char[brd.col];

	for(int i=0;i<brd.row;i++)
		for(int j=0;j<brd.col;j++)
			fread_s(&brd.map[i][j],sizeof(char),sizeof(char),1,FILE);

	fread_s(brd.player,sizeof(PLAYER)*2,sizeof(PLAYER),2,FILE);
	fread_s(&brd.turn,sizeof(int),sizeof(int),1,FILE);
	fread_s(&brd.level,sizeof(int),sizeof(int),1,FILE);
	fread_s(&brd.c,sizeof(int),sizeof(int),1,FILE);
	fread_s(&brd.last,sizeof(TIME),sizeof(TIME),1,FILE);
}

void intiBoard(BOARD &brd)
{
	// khởi tạo mảng kích thước NxN
	brd.map = new char*[brd.row];
	for(int i=0;i<brd.row;i++)
		brd.map[i] = new char[brd.col];

	for(int i=0;i<brd.row;i++)
		for(int j=0;j<brd.col;j++)
			brd.map[i][j] = -1;
	brd.turn = 1;
	brd.c = 8;
	brd.player[0].c = 12;
	brd.player[0].s = 88;
	brd.player[1].c = 10;
	brd.player[1].s = 79;
}

bool loadBoard(int id,BOARD &brd)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_GAME,"r+b")==0)
	{
		while (FEOF(FILE)==0)
		{
			readBoard(brd,FILE);
			if(brd.id==id)
			{
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return true;
	}
	return false;
}

bool clearBoard(int id)
{
	FILE* FILE_IN;
	FILE* FILE_OUT;
	if(fopen_s(&FILE_IN,FILE_GAME,"r+b")==0)
	{
		BOARD brd;
		char FILE_DATA_NEW[13];
		strcpy_s(FILE_DATA_NEW,FILE_DATA);
		strcat_s(FILE_DATA_NEW,".new");
		fopen_s(&FILE_OUT,FILE_DATA_NEW,"wb");
		while (FEOF(FILE_IN)==false)
		{
			readBoard(brd,FILE_IN);
			if(brd.id==id) continue;
			if(brd.id>id) brd.id--;
			writeBoard(brd,FILE_OUT);
		}
		_fcloseall();
		remove(FILE_GAME);
		rename(FILE_DATA_NEW,FILE_GAME);
		return true;
	}
	_fcloseall();
	return false;
}

bool updateBoard(BOARD brd)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_GAME,"r+b")==0)
	{
		BOARD tmp;
		tmp.id = 0;
		while (FEOF(FILE)==false)
			readBoard(tmp,FILE);
		brd.id = tmp.id+1;
		brd.last = now();
		writeBoard(brd,FILE);
		fclose(FILE);
		return true;
	}
	return false;
}

BOARD BoardCpy(BOARD brd)
{
	BOARD temp;
	temp.col = brd.col;
	temp.id = brd.id;
	temp.last = brd.last;
	temp.row = brd.row;
	temp.turn = brd.turn;
	temp.level = brd.level;
	temp.c = brd.c;
	temp.map = new char *[brd.row];
	for(int i=0;i<brd.row;i++) temp.map[i] = new char[brd.col];
	for(int i=0;i<brd.row;i++)
		for(int j=0;j<brd.col;j++) temp.map[i][j] = brd.map[i][j];
	
	return temp;
}

int checkWin(BOARD brd)
{
	int X5[] = {1,1,1,1,1};

	int ROW[5];
	int COLUMN[5];
	int DOWN[5];
	int UP[5];

	bool draw = true;

	for(int r=0;r<brd.row;r++)
		for(int c=0;c<brd.col;c++)		
		{			
			if(brd.map[r][c]==-1) draw = 0;
			for(int i=0;i<5;i++)
			{
				// Lưu các ô cờ trên một dòng
				if(c<brd.col-4) ROW[i]=brd.map[r][c+i];
				// Lưu các ô cờ trên một cột
				if(r<brd.row-4) COLUMN[i]=brd.map[r+i][c];
				// Lưu các ô cờ trên đường chéo đi lên
				if(r>=4&&c<brd.col-4) UP[i]=brd.map[r-i][c+i];
				// Lưu các ô cờ trên đường chéo đi xuống
				if(r<brd.row-4&&c<brd.col-4) DOWN[i]=brd.map[r+i][c+i];
			}
			// 5 quân hai đầu bị chặn không thắng
			if((equalArray(ROW,X5,5,1)&&((c>0&&brd.map[r][c-1]==-1)||(c<brd.col-5&&brd.map[r][c+5]==-1)))||
				(equalArray(COLUMN,X5,5,1)&&((r>0&&brd.map[r-1][c]==-1)||(r<brd.row-5&&brd.map[r+5][c]==-1)))||
				(equalArray(DOWN,X5,5,1)&&((r<brd.row-1&&c>0&&brd.map[r+1][c-1]==-1)||(r>4&&c<brd.col-5&&brd.map[r-5][c+5]==-1)))||
				(equalArray(UP,X5,5,1)&&((r>0&&c>0&&brd.map[r-1][c-1]==-1)||(r<brd.row-5&&c<brd.col-5&&brd.map[r+5][c+5]==-1))))
				return 1;

			if((equalArray(ROW,X5,5,2)&&((c>0&&brd.map[r][c-1]==-1)||(c<brd.col-5&&brd.map[r][c+5]==-1)))||
				(equalArray(COLUMN,X5,5,2)&&((r>0&&brd.map[r-1][c]==-1)||(r<brd.row-5&&brd.map[r+5][c]==-1)))||
				(equalArray(DOWN,X5,5,2)&&((r<brd.row-1&&c>0&&brd.map[r+1][c-1]==-1)||(r>4&&c<brd.col-5&&brd.map[r-5][c+5]==-1)))||
				(equalArray(UP,X5,5,2)&&((r>0&&c>0&&brd.map[r-1][c-1]==-1)||(r<brd.row-5&&c<brd.col-5&&brd.map[r+5][c+5]==-1))))
				return 2;
		}
	if(draw==true) return 0;
	else return -1;
}

bool listBoard(BOARD b[],int& n,char usr[])
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_GAME,"r+b")==0)
	{
		n = 0;
		while (FEOF(FILE)==0)
		{
			readBoard(b[n],FILE);
			if((string)b[n].player[0].usr==(string)usr||(string)b[n].player[1].usr==(string)usr) n++;
		}
		fclose(FILE);
		return true;
	}
	return false;
}

bool saveTemp(BOARD b)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_TEMP,"w+b")==0)
	{
		writeBoard(b,FILE);
		fclose(FILE);
		return true;
	}
	return false;
}