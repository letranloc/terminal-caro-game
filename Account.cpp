#include "Func.h"

bool addAcc(ACCOUNT acc)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		fseek(FILE,0,SEEK_END);
		fwrite(&acc,sizeof(ACCOUNT),1,FILE);
		fclose(FILE);
		return true;
	}
	return false;
}

bool updateAcc(ACCOUNT acc)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		ACCOUNT tmp;
		while (FEOF(FILE)==0)
		{
			fread_s(&tmp,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);
			if((string)tmp.usr==(string)acc.usr)		// Kiểm tra đúng usrname
			{
				fseek(FILE,-sizeof(ACCOUNT),SEEK_CUR);
				fwrite(&acc,sizeof(ACCOUNT),1,FILE);
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return false;
	}
	return false;
}

bool changePwd(char usr[],string oldpwd,string newpwd)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		ACCOUNT tmp;
		char oldpass[21];
		for(int i=0;i<=oldpwd.length();i++) oldpass[i] = oldpwd[i];
		Encrypt(oldpass);

		while (FEOF(FILE)==0)
		{
			fread_s(&tmp,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);
			if((string)tmp.usr==(string)usr&&(string)tmp.pwd==(string)oldpass)
			{
				for(int i=0;i<=newpwd.length();i++) tmp.pwd[i] = newpwd[i];
				Encrypt(tmp.pwd);
				fseek(FILE,-sizeof(ACCOUNT),SEEK_CUR);
				fwrite(&tmp,sizeof(ACCOUNT),1,FILE);
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return false;
	}
	return false;
}

bool changeUsr(char usr[],char new_usr[])
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		ACCOUNT tmp;
		while (FEOF(FILE)==0)
		{
			fread_s(&tmp,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);
			if((string)tmp.usr==(string)usr)
			{
				strcpy_s(tmp.usr,new_usr);
				fseek(FILE,-sizeof(ACCOUNT),SEEK_CUR);
				fwrite(&tmp,sizeof(ACCOUNT),1,FILE);
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return false;
	}
	return false;
}

bool setPwd(string usr,string pwd)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		ACCOUNT tmp;
		while (FEOF(FILE)==0)
		{
			fread_s(&tmp,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);
			if((string)tmp.usr==usr)
			{
				for(int i=0;i<=pwd.length();i++) tmp.pwd[i] = pwd[i];
				Encrypt(tmp.pwd);
				fseek(FILE,-sizeof(ACCOUNT),SEEK_CUR);
				fwrite(&tmp,sizeof(ACCOUNT),1,FILE);
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return false;
	} 
	return false;
}

bool infoAcc(char usr[],ACCOUNT &acc)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		while (FEOF(FILE)==0)
		{
			fread_s(&acc,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);
			if((string)acc.usr==(string)usr)
			{
				fclose(FILE);
				return true;
			}
		}
		fclose(FILE);
		return false;
	}
	return false;
}

bool delAcc(char usr[])
{
	FILE* FILE_IN;
	if(fopen_s(&FILE_IN,FILE_DATA,"r+b")==0)
	{
		FILE* FILE_OUT;
		char FILE_DATA_NEW[13];
		strcpy_s(FILE_DATA_NEW,FILE_DATA);
		strcat_s(FILE_DATA_NEW,".new");
		fopen_s(&FILE_OUT,FILE_DATA_NEW,"wb");
		ACCOUNT tmp;
		while (FEOF(FILE_IN)==0)
		{
			fread_s(&tmp,sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE_IN);
			if(tmp.usr==(string)usr) continue;
			fwrite(&tmp,sizeof(ACCOUNT),1,FILE_OUT);
		}
		_fcloseall();
		remove(FILE_DATA);
		rename(FILE_DATA_NEW,FILE_DATA);
		return true;
	}
	_fcloseall();
	return false;
}

bool listAcc(ACCOUNT acc[],int &n)
{
	FILE* FILE;
	if(fopen_s(&FILE,FILE_DATA,"r+b")==0)
	{
		n = 0;
		while (FEOF(FILE)==0)
		{
			n++;
			fread_s(&acc[n-1],sizeof(ACCOUNT),sizeof(ACCOUNT),1,FILE);		
	    }
		fclose(FILE);
		return true;
	}
	return false;
}


bool topAcc(ACCOUNT acc[],int &n)
{
	ACCOUNT *temp = new ACCOUNT[100];
	int m;
	if(listAcc(temp,m))
	{
		if(n>m) n=m;
		for(int i=0;i<n;i++) acc[i] = temp[i];
		return true;
	}
	else return false;
}
