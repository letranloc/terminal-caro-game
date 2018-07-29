#include "Func.h"

int Defend[] = { 0, 1, 9, 85, 769 };
int Attack[] = { 0, 4, 28, 256, 2308 };
int **Val,
	_branch = 3;

int Count(int num,int isLocked,int turn,BOARD brd)
{
	int count = 0;
	for(int row = 0;row<brd.row;row++)
		for(int col=0;col<brd.col;col++)
			if(brd.map[row][col]==turn&&CountAt(row,col,num,isLocked,brd)) count++;
	return count;
}

void getStats(STATS &s,int turn,BOARD brd)
{
	s.oo	= Count( 2, 0, turn, brd );
	s.ooo	= Count( 3, 0, turn, brd );
	s.xooo	= Count( 3, 1, turn, brd );
	s.oooo	= Count( 4, 0, turn, brd );
	s.xoooo = Count( 4, 1, turn, brd );
	s.ooooo = Count( 5, 0, turn, brd );
}

int EvaluateBoard(BOARD b)
{
	STATS u,c;
	getStats(u,1,b);
	getStats(c,2,b);
	return 6*(c.oo-u.oo)+4*(c.xooo-u.xooo)+12*(c.ooo-u.ooo)+30*(c.xoooo-u.xoooo)+3000*(c.oooo-u.oooo)+10000*(c.ooooo-u.ooooo);
}

bool isOk(BOARD b,int row,int col)
{
	return (row>=0&&col>=0&&row<b.row&&col<b.col);
}

void EvaluateCell(BOARD b,int turn)
{
	Val = new int*[b.row];
	for(int i=0;i<b.row;i++) Val[i] = new int[b.col];

	for(int r=0;r<b.row;r++)
		for(int c=0;c<b.col;c++)
			Val[r][c] = 0;

	int cComputer,cPlayer;
	//Kiểm tra trên hàng
	for(int r=0;r<b.row;r++)
		for(int c=0;c<b.col-4;c++)
		{
			cComputer = cPlayer = 0;
			for(int i=0;i<5;i++)	//Đếm số quân cờ block 5 con
			{
				if(b.map[r][c+i]==1) cPlayer++;
				if(b.map[r][c+i]==2) cComputer++;
			}
			//Nếu tồn tại quân cờ
			if(cComputer * cPlayer == 0 && cComputer != cPlayer)
				for(int i=0;i<5;i++)
					if(b.map[r][c+i]==-1)
					{
						//Cộng điểm cho từng ô cờ
						if(cComputer==0)
						{
							if(turn==2) Val[r][c+i] += Defend[cPlayer];
							else Val[r][c+i] += Attack[cPlayer];
							//Chặn hai đầu không thắng
							if(isOk(b,r,c-1)&&isOk(b,r,c+5)&&b.map[r][c-1]==2&&b.map[r][c+5]==2)
								Val[r][c+i] = 0;
						}
						if(cPlayer==0)
						{
							if(turn==1) Val[r][c+i] += Defend[cComputer];
							else Val[r][c+i] += Attack[cComputer];
							if(isOk(b,r,c-1)&&isOk(b,r,c+5)&&b.map[r][c-1]==1&&b.map[r][c+5]==1)
								Val[r][c+i] = 0;
						}
						if((cComputer==4||cPlayer==4)&&((isOk(b,r,c+i-1)&&b.map[r][c+i-1]==-1)||(isOk(b,r,c+i+1)&&b.map[r][c+i+1]==-1)))
							Val[r][c+i] *= 2;
						else if(cComputer==4||cPlayer==4)
							Val[r][c+i] *= 2;
					}
		}
		//Kiểm tra trên cot
		for(int r=0;r<b.row-4;r++)
			for(int c=0;c<b.col;c++)
			{
				cComputer = cPlayer = 0;
				for(int i=0;i<5;i++)
				{
					if(b.map[r+i][c]==1) cPlayer++;
					if(b.map[r+i][c]==2) cComputer++;
				}
				if(cComputer * cPlayer == 0 && cComputer != cPlayer)
					for(int i=0;i<5;i++)
						if(b.map[r+i][c]==-1)
						{
							if(cComputer==0)
							{
								if(turn==2) Val[r+i][c] += Defend[cPlayer];
								else Val[r+i][c] += Attack[cPlayer];
								
								if(isOk(b,r-1,c)&&isOk(b,r+5,c)&&b.map[r-1][c]==2&&b.map[r+5][c]==2)
									Val[r+i][c] = 0;
							}
							if(cPlayer==0)
							{
								if(turn==1) Val[r+i][c] += Defend[cComputer];
								else Val[r+i][c] += Attack[cComputer];
								if(isOk(b,r-1,c)&&isOk(b,r+5,c)&&b.map[r-1][c]==1&&b.map[r+5][c]==1)
									Val[r+i][c] = 0;
							}
							if((cComputer==4||cPlayer==4)&&((isOk(b,r+i-1,c)&&b.map[r+i-1][c]==-1)||(isOk(b,r+i+1,c)&&b.map[r+i+1][c]==-1)))
								Val[r+i][c] *= 2;
							else if(cComputer==4||cPlayer==4)
								Val[r+i][c] *= 2;
						}
			}
			//Kiểm tra trên đường chéo chính
			for(int r=0;r<b.row-4;r++)
				for(int c=0;c<b.col-4;c++)
				{
					cComputer = cPlayer = 0;
					for(int i=0;i<5;i++)
					{
						if(b.map[r+i][c+i]==1) cPlayer++;
						if(b.map[r+i][c+i]==2) cComputer++;
					}
					if(cComputer * cPlayer == 0 && cComputer != cPlayer)
						for(int i=0;i<5;i++)
							if(b.map[r+i][c+i]==-1)
							{
								if(cComputer==0)
								{
									if(turn=2) Val[r+i][c+i] += Defend[cPlayer];
									else Val[r+i][c+i] += Attack[cPlayer];
									if(isOk(b,r-1,c-1)&&isOk(b,r+5,c+5)&&b.map[r-1][c-1]==2&&b.map[r+5][c+5]==2)
										Val[r+i][c+i] = 0;
								}
								if(cPlayer==0)
								{
									if(turn=1) Val[r+i][c+i] += Defend[cComputer];
									else Val[r+i][c+i] += Attack[cComputer];
									if(isOk(b,r-1,c-1)&&isOk(b,r+5,c+5)&&b.map[r-1][c-1]==1&&b.map[r+5][c+5]==1)
										Val[r+i][c+i] = 0;
								}
								if((cComputer==4||cPlayer==4)&&((isOk(b,r+i-1,c+i-1)&&b.map[r+i-1][c+i-1]==-1)||(isOk(b,r+i+1,c+i+1)&&b.map[r+i+1][c+i+1]==-1)))
									Val[r+i][c+i] *= 2;
								else if(cComputer==4||cPlayer==4)
									Val[r+i][c+i] *= 2;
							}
				}
				//Kiểm tra trên đường chéo phụ
				for(int r=4;r<b.row;r++)
					for(int c=0;c<b.col-4;c++)
					{
						cComputer = cPlayer = 0;
						for(int i=0;i<5;i++)
						{
							if(b.map[r-i][c+i]==1) cPlayer++;
							if(b.map[r-i][c+i]==2) cComputer++;
						}
						if(cComputer * cPlayer == 0 && cComputer != cPlayer)
							for(int i=0;i<5;i++)
								if(b.map[r-i][c+i]==-1)
								{
									if(cComputer==0)
									{
										if(turn=2) Val[r-i][c+i] += Defend[cPlayer];
										else Val[r-i][c+i] += Attack[cPlayer];
										if(isOk(b,r+1,c-1)&&isOk(b,r-5,c+5)&&b.map[r+1][c-1]==2&&b.map[r-5][c+5]==2)
											Val[r-i][c+i] = 0;
									}
									if(cPlayer==0)
									{
										if(turn=1) Val[r-i][c+i] += Defend[cComputer];
										else Val[r-i][c+i] += Attack[cComputer];
										if(isOk(b,r+1,c-1)&&isOk(b,r-5,c+5)&&b.map[r+1][c-1]==1&&b.map[r-5][c+5]==1)
											Val[r+i][c+i] = 0;
									}
									if((cComputer==4||cPlayer==4)&&((isOk(b,r-i+1,c+i-1)&&b.map[r-i+1][c+i-1]==-1)||(isOk(b,r-i-1,c+i+1)&&b.map[r-i-1][c+i+1]==-1)))
										Val[r-i][c+i] *= 2;
									else if(cComputer==4||cPlayer==4)
										Val[r-i][c+i] *= 2;
								}
					}	
}

CELL GetMaxCell(BOARD b)
{
	CELL *cell = new CELL[100];
	int t = -MAX, d = -1;
	for(int i=0;i<b.row;i++)
		for(int j=0;j<b.col;j++)
		{
			if(t<Val[i][j])
			{
				t = Val[i][j];
				d = 0;
				cell[d].row = i;
				cell[d].col = j;
			}
			else if(t==Val[i][j]&&t>0)
			{
				d++;
				cell[d].row = i;
				cell[d].col = j;
			}
			if(d>=100) break;
		}
		for(int i=0;i<=d;i++) Val[cell[i].row][cell[i].col] = 0;
		srand ( time(NULL) );
		int x = rand() % (d+1) + 0;
		return cell[x];
}

CELL Move(BOARD brd,int turn)
{
	CELL p;
	BOARD b = BoardCpy(brd);
	b.col -= 2;
	b.row -= 2;
	EvaluateCell(b,2);

	CELL *cell = new CELL[_branch];
	for(int i=0;i<_branch;i++) cell[i] = GetMaxCell(b);

	int max = -MAX;
	CELL*cp = new CELL[_branch];
	int d = -1;
	for(int i=0;i<_branch;i++)
	{
		p.row = cell[i].row;
		p.col = cell[i].col;
		b.map[p.row][p.col] = 2;
		int t = MinVal(b,-MAX,MAX,b.level);
		if(max<t)
		{
			max = t;
			d = 0;
			cp[d] = cell[i];
		}
		else if(max==t)
		{
			d++;
			cp[d] = cell[i];
		}
		b.map[p.row][p.col] = -1;
	}
	srand ( time(NULL) );
	int x = rand() % (d+1) + 0;
	return cp[x];
}

int MaxVal(BOARD b,int alpha,int beta,int depth)
{
	int val = EvaluateBoard(b);
	if(depth==0||abs(val)>3000) return val;
	EvaluateCell(b,2);

	CELL*cell = new CELL[_branch];
	for(int i=0;i<_branch;i++) cell[i] = GetMaxCell(b);

	for(int i=0;i<_branch;i++)
	{
		b.map[cell[i].row][cell[i].col] = 2;
		alpha = max(alpha,MinVal(b,alpha,beta,depth-1));
		b.map[cell[i].row][cell[i].col] = -1;
		if(alpha>beta) break;
	}
	return alpha;
}

int MinVal(BOARD b,int alpha,int beta,int depth)
{
	int val = EvaluateBoard(b);
	if(depth==0||abs(val)>3000) return val;
	EvaluateCell(b,1);

	CELL*cell = new CELL[_branch];
	for(int i=0;i<_branch;i++) cell[i] = GetMaxCell(b);

	for(int i=0;i<_branch;i++)
	{
		b.map[cell[i].row][cell[i].col] = 1;
		beta = min(beta,MaxVal(b,alpha,beta,depth-1));
		b.map[cell[i].row][cell[i].col] = -1;
		if(alpha>=beta) break;
	}
	return beta;
}