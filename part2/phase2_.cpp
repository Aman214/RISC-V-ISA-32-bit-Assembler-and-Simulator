#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool memory[2000][32],reg[32][32],IR[32],mux_INC=0;
int RA,RB,PC=0,RZ,RY,RM,immediate,branch_offset,ALU_op=0,c,PC_temp,instype,clock_cycle_count=0;     //declaring memory and intermediate registers.

int bin2dec(bool data[],int n,int sign=0)
{
	int temp=1,sum=0,flag=0;
	bool temp_data[n];
	for(int i=0;i<n;i++)
		temp_data[i]=data[i];
	if(sign!=0&&temp_data[0]==1)
	{
		for(int i=0;i<n;i++)
		{
			if(temp_data[i]==0)
				temp_data[i]=1;
			else
				temp_data[i]=0;
		}
		for(int i=n-1;i>=0;i--)
		{
			if(temp_data[i]==0)
			{
				temp_data[i]=1;
				break;
			}
			else
				temp_data[i]=0;
		}
		flag=1;
	}
	while(n>0)
	{
		sum+=temp*temp_data[n-1];
		temp*=2;
		n--;
	}
	if(flag==1)
		return sum*-1;
	return sum;
}

void dec2bin(bool value[32],int n,int size=32)
{

	for(int j=0;j<size;j++)
		value[j]=0;
	int i=1,flag=0;
	if(n<0)
	{
		flag=1;
		n*=-1;
	}
	while(n!=0)
	{
		value[size-i]=n%2;
		n/=2;
		i++;
	}
	if(flag==1)
	{
		for(i=0;i<size;i++)
		{
			if(value[i]==0)
				value[i]=1;
			else
				value[i]=0;
		}
		for(i=size-1;i>=0;i--)
		{
			if(value[i]==0)
			{
				value[i]=1;
				break;
			}
			else
				value[i]=0;
		}
	}
		
}

void xyz(char abc[],bool b[32])
{
	for(int i=0;i<8;i++)
	{
		if(abc[i]=='0')
		{
			b[4*i]=0;
			b[4*i+1]=0;
			b[4*i+2]=0;
			b[4*i+3]=0;
		}
		else if(abc[i]=='1')
		{
			b[4*i]=0;
			b[4*i+1]=0;
			b[4*i+2]=0;
			b[4*i+3]=1;
		}
		else if(abc[i]=='2')
		{
			b[4*i]=0;
			b[4*i+1]=0;
			b[4*i+2]=1;
			b[4*i+3]=0;
		}
		else if(abc[i]=='3')
		{
			b[4*i]=0;
			b[4*i+1]=0;
			b[4*i+2]=1;
			b[4*i+3]=1;
		}
		else if(abc[i]=='4')
		{
			b[4*i]=0;
			b[4*i+1]=1;
			b[4*i+2]=0;
			b[4*i+3]=0;
		}
		else if(abc[i]=='5')
		{
			b[4*i]=0;
			b[4*i+1]=1;
			b[4*i+2]=0;
			b[4*i+3]=1;
		}
		else if(abc[i]=='6')
		{
			b[4*i]=0;
			b[4*i+1]=1;
			b[4*i+2]=1;
			b[4*i+3]=0;
		}
		else if(abc[i]=='7')
		{
			b[4*i]=0;
			b[4*i+1]=1;
			b[4*i+2]=1;
			b[4*i+3]=1;
		}
		else if(abc[i]=='8')
		{
			b[4*i]=1;
			b[4*i+1]=0;
			b[4*i+2]=0;
			b[4*i+3]=0;
		}
		else if(abc[i]=='9')
		{
			b[4*i]=1;
			b[4*i+1]=0;
			b[4*i+2]=0;
			b[4*i+3]=1;
		}
		else if(abc[i]=='A'||abc[i]=='a')
		{
			b[4*i]=1;
			b[4*i+1]=0;
			b[4*i+2]=1;
			b[4*i+3]=0;
		}
		else if(abc[i]=='B'||abc[i]=='b')
		{
			b[4*i]=1;
			b[4*i+1]=0;
			b[4*i+2]=1;
			b[4*i+3]=1;
		}
		else if(abc[i]=='C'||abc[i]=='c')
		{
			b[4*i]=1;
			b[4*i+1]=1;
			b[4*i+2]=0;
			b[4*i+3]=0;
		}
		else if(abc[i]=='D'||abc[i]=='d')
		{
			b[4*i]=1;
			b[4*i+1]=1;
			b[4*i+2]=0;
			b[4*i+3]=1;
		}
		else if(abc[i]=='E'||abc[i]=='e')
		{
			b[4*i]=1;
			b[4*i+1]=1;
			b[4*i+2]=1;
			b[4*i+3]=0;
		}
		else if(abc[i]=='F'||abc[i]=='f')
		{
			b[4*i]=1;
			b[4*i+1]=1;
			b[4*i+2]=1;
			b[4*i+3]=1;
		}
	}
}

int assign(int instype)
{
	if(instype==28||instype==10||(instype>=24&&instype<=26)||instype==51||instype==50||(instype>=1&&instype<=7))
		return 1;
	else if(instype==29)
		return 2;
	else if(instype==37||instype==18)
		return 3;
	else if(instype==36||instype==17)
		return 4;
	else if(instype==29)
		return 5;
	else if(instype==33||instype==14)
		return 6;
	else if(instype==29)
		return 7;
	else if(instype==30||instype==11)
		return 8;
	else if(instype==34||instype==15||instype==35)
		return 9;
	else if(instype==46||instype==48||instype==31)
		return 10;
	else if(instype==44)
		return 11;
	else if(instype==49)
		return 17;
	else if(instype==45)
		return 16;
	else if(instype==16)
		return 14;
	else if(instype==32)
		return 15;
	else if(instype==47)
		return 17;
}
	
void read()
{
	ifstream f;
	f.open("machine_code.mc");
	char arr[1000][8];
	c=0;
	string line;
	getline(f,line);
	while(f)
	{
		cout<<line<<" ";
		for(int i=0;i<8;i++)
		arr[c][i]=line[i];
		c++;
	getline(f,line);
	}
	f.close();
	for(int i=0;i<c;i++)
	{
		xyz(arr[i],memory[i]);
	}
	ifstream fin;
	fin.open("MEM.txt");
	string line1;
	int c1=1000;
	getline(fin,line1);
	while(fin){
	for(int j=0;j<32;j++)
    {
       memory[c1][j]=(line1[j]-48);
    }
    getline(fin,line1);
    c1++;
	}
	fin.close();
}


void fetch()
{
	for(int i=0;i<32;i++)
		IR[i]=memory[PC][i];
	
	PC+=1;
}


int decode(bool data[])         //Takes the word as input and gives an integer
{                                //decode
	bool opcode[7],fn3[3],fn7[7];
	int op,fun3,fun7,i;
	for(i=0;i<7;i++)
	{
		fn7[i]=data[i];
		opcode[i]=data[25+i];
	}
	for(i=0;i<3;i++)
		fn3[i]=data[17+i];
	op=bin2dec(opcode,7);
	fun3=bin2dec(fn3,3);
	fun7=bin2dec(fn7,7);
	if(op==3)
		{
			if(fun3==0)
				return 1;
			else if(fun3==1)
				return 2;
			else if(fun3==2)
				return 3;
			else if(fun3==3)
				return 4;
			else if(fun3==4)
				return 5;
			else if(fun3==5)
				return 6;
			else if(fun3==6)
				return 7;
		}
	else if(op==19)
	{
			if(fun3==0)
				return 10;
			else if(fun3==1&&fun7==0)
				return 11;
			else if(fun3==2)
				return 12;
			else if(fun3==3)
				return 13;
			else if(fun3==4)
				return 14;
			else if(fun3==5&&fun7==0)
				return 15;
			else if(fun3==5&&fun7==32)
				return 16;
			else if(fun3==6)
				return 17;
			else if(fun3==7)
				return 18;
	}
	else if(op==23)
		return 19;
	else if(op==27)
	{
			if(fun3==0)
				return 20;
			else if(fun3==1)
				return 21;
			else if(fun3==5&&fun7==0)
				return 22;
			else if(fun3==5&&fun7==32)
				return 23;
	}
	else if(op==35)
	{
			if(fun3==0)
				return 24;
			else if(fun3==1)
				return 25;
			else if(fun3==2)
				return 26;
			else if(fun3==3)
				return 27;
	}
	else if(op==51)
	{
			if(fun3==0&&fun7==0)
				return 28;
			else if(fun3==0&&fun7==32)
				return 29;
			else if(fun3==1)
				return 30;
			else if(fun3==2&&fun7==0)
				return 31;
			else if(fun3==3&&fun7==0)
				return 32;
			else if(fun3==4&&fun7==0)
				return 33;
			else if(fun3==5&&fun7==0)
				return 34;
			else if(fun3==5&&fun7==32)
				return 35;
			else if(fun3==6&&fun7==0)
				return 36;
			else if(fun3==7&&fun7==0)
				return 37;
	}
	else if(op==55)
	{
		if(fun3==0&&fun7==0)
				return 39;
		else if(fun3==0&&fun7==32)
				return 40;
		else if(fun3==1&&fun7==0)
				return 41;
		else if(fun3==5&&fun7==0)
				return 42;
		else if(fun3==5&&fun7==32)
				return 43;
		else 
			return 38;
	}
	else if(op==99)
	{
		if(fun3==0)
				return 44;
		else if(fun3==1)
				return 45;
		else if(fun3==4)
				return 46;
		else if(fun3==5)
				return 47;
		else if(fun3==6)
				return 48;
		else if(fun3==7)
				return 49;
	}
	else if(op==103)
		return 50;
	else if(op==111)
		return 51;
	
	return 0;
}



int alu()                     //alu
{
	if(ALU_op==1)
		return RA+RB;
	else if(ALU_op==2)
		return RA-RB;
	else if(ALU_op==3)
	{
		bool RA_binary[32],RB_binary[32],RZ_binary[32];
		dec2bin(RA_binary,RA);
		dec2bin(RB_binary,RB);
		for(int i=0;i<32;i++)
			if(RA_binary[i]==1&&RB_binary[i]==1)
				RZ_binary[i]=1;
			else
				RZ_binary[i]=0;
		RZ=bin2dec(RZ_binary,32);
		return RZ;
	}
	else if(ALU_op==4)
	{
		bool RA_binary[32],RB_binary[32],RZ_binary[32];
		dec2bin(RA_binary,RA);
		dec2bin(RB_binary,RB);
		for(int i=0;i<32;i++)
			if(RA_binary[i]==1||RB_binary[i]==1)
				RZ_binary[i]=1;
			else
				RZ_binary[i]=0;
		RZ=bin2dec(RZ_binary,32);
		return RZ;
	}
	else if(ALU_op==5)
		return RA*RZ;
	else if(ALU_op==6)
	{
		
		return (RA^RB);
	}
	else if(ALU_op==7)
		return RA/RZ;
	else if(ALU_op==8)
	{
		int k=pow(2,RB);

		RZ=k*RA;
		return RZ;
	}
	else if(ALU_op==9)
	{
		int k=pow(2,RB);

		RZ=RA/k;
		return RZ;
	}
	else if(ALU_op==10)
	{
		mux_INC=0;
		if(RA<RB)
			mux_INC=1;
		else
			mux_INC=0;
		if(mux_INC==1)
	{
		PC+=(branch_offset-1);
	}
		return mux_INC;
	}
	else if(ALU_op==12)
	{
		return   RA<RB?1:0;
	}
	else if(ALU_op==11)
	{
		mux_INC=0;
		if(RA==RB)
			mux_INC=1;
		else
			mux_INC=0;
		if(mux_INC==1)
	{
		PC+=(branch_offset-1);
	}
		return 0;
	}
	else if(ALU_op==13)
	{
		return   RA<abs(RB)?1:0;
	}
	else if(ALU_op==14)
	{
		int k=pow(2,RB);
		RZ=RA/k;
		return RZ;
	}
	else if(ALU_op==15)
	{
		return abs(RA)<abs(RB)?1:0;
	}
	else if(ALU_op==16)
	{
		mux_INC=0;
		if(RA!=RB)
			mux_INC=1;
		else
			mux_INC=0;
		if(mux_INC==1)
	{
		PC+=(branch_offset-1);
	}
		return 0;
	}
	else if(ALU_op==17)
	{
		mux_INC=0;
		if(RA>=RB)
			mux_INC=1;
		else
			mux_INC=0;
		if(mux_INC==1)
	{
		PC+=(branch_offset-1);
	}
		return mux_INC;
	}
}			
				
void memaccess(int choice=0,int z=0)
{	
		int tempo=0,modtemp=0,j=0;
		bool temporary[32];
		if(choice==1)
		{
			if(instype==1)//byte
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				for(int i=0;i<8;i++)
					temporary[i]=memory[tempo][(24-modtemp*8)+i];
				RY=bin2dec(temporary,8,1);
			}
			else if(instype==2)
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				for(int i=0;i<16;i++)
				{
					if(modtemp<3)
						temporary[i]=memory[tempo][(16-modtemp*8)+i];
					else
					{
						if(i<8)
							temporary[i]=memory[tempo+1][24+i];
						else
							temporary[i]=memory[tempo][i-8];
					}
				}
				RY=bin2dec(temporary,16,1);
			}
			else if(instype==3)
			{ 
				tempo=RZ/4;
				modtemp=RZ%4;
				if(modtemp==0)
					RY=bin2dec(memory[tempo],32,1);
				else
				{
					for(int i=0;i<32;i++)
					{
						if(i<modtemp*8)
							temporary[i]=memory[tempo+1][(32-modtemp*8)+i];
						else
							temporary[i]=memory[tempo][i-modtemp*8];
					}
					RY=bin2dec(temporary,32,1);
				}		
			}
			else if(instype==5)
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				for(int i=0;i<8;i++)
					temporary[i]=memory[tempo][(24-modtemp*8)+i];
				RY=bin2dec(temporary,8);
			}
			else if(instype==6)
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				for(int i=0;i<16;i++)
				{
					if(modtemp<3)
						temporary[i]=memory[tempo][(16-modtemp*8)+i];
					else
					{
						if(i<8)
							temporary[i]=memory[tempo+1][24+i];
						else
							temporary[i]=memory[tempo][i-8];
					}
				}
				RY=bin2dec(temporary,16);
			}
			else if(instype==7)
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				if(modtemp==0)
					RY=bin2dec(memory[tempo],32,1);
				else
				{
					for(int i=0;i<32;i++)
					{
						if(i<modtemp*8)
							temporary[i]=memory[tempo+1][(32-modtemp*8)+i];
						else
							temporary[i]=memory[tempo][i-modtemp*8];
					}
					RY=bin2dec(temporary,32);
				}		
			}
			
		}
		if(choice==2)
		{
			if(instype==24)
			{
				tempo=RZ/4; 
				modtemp=RZ%4; 
				dec2bin(temporary,z,8);
				for(int i=0;i<8;i++)
					memory[tempo][(24-modtemp*8)+i]=temporary[i];
				
			}
			else if(instype==25)
			{
				tempo=RZ/4;
				modtemp=RZ%4;
				dec2bin(temporary,z,16);
				for(int i=0;i<16;i++)
				{
					if(modtemp<3)
						memory[tempo][(16-modtemp*8)+i]=temporary[i];
					else
					{
						if(i<8)
							memory[tempo+1][24+i]=temporary[i];
						else
							memory[tempo][i-8]=temporary[i];
					}
				}
				
			}
			else if(instype==26)
			{
				tempo=RZ/4; 
				modtemp=RZ%4;
				
				if(modtemp==0)
				{
					dec2bin(temporary,z,32);
					for(int i=0;i<32;i++)
					memory[tempo][i]=temporary[i];
				}
				else
				{
					dec2bin(temporary,z,32);
					for(int i=0;i<32;i++)
					{
						if(i<modtemp*8)
							memory[tempo+1][(32-modtemp*8)+i]=temporary[i];
						else
							memory[tempo][i-modtemp*8]=temporary[i];
					}
				}		
			}
		}
}

void update(int rd_i)
{
	bool bin_value[32];
	if(instype>=1&&instype<=7)
    {
        dec2bin(bin_value,RY,32);
        for(int i=0;i<32;i++)
            reg[rd_i][i]=bin_value[i];
        return;
    }
	dec2bin(bin_value,RZ,32);
	for(int i=0;i<32;i++)
	{
		reg[rd_i][i]=bin_value[i];
	}
	cout<<"\n";
	for(int i=0;i<32;i++)
	{
			reg[0][i]=0;
	}
}
		
	



int main()
{
	bool rs1[5],rs2[5],rd[5],imm[13],immu[21],ti[32];
	int aluresult,rs1_i,rs2_i,rd_i,imm_i,imm_u,t;
	t=1999*4;
	dec2bin(ti,t);


	read();
	cout<<"\n";
	for(int j=0;j<c;j++)
	{
		for(int k=0;k<32;k++)
			cout<<memory[j][k];
		cout<<endl;
	}
	for(int j=0;j<32;j++)
	{
		for(int k=0;k<32;k++)
			reg[j][k]=0;
	}
		for(int i=0;i<32;i++)
		reg[2][i]=ti[i];

	while(PC<c)
	{
		clock_cycle_count++;
		fetch();
	instype=decode(IR);
	cout<<"instype="<<instype<<"\n";
	cout<<"PC="<<PC;
	if((instype>=28&&instype<=37)||(instype>=39&&instype<=43))					//R type
	{
		for(int i=0;i<5;i++)
		{
			rs1[i]=IR[12+i];
			rs2[i]=IR[7+i];
			rd[i]=IR[20+i];
		}
	
		rs1_i=bin2dec(rs1,5);
		rs2_i=bin2dec(rs2,5);
		RA=bin2dec(reg[rs1_i],32,1);
		RB=bin2dec(reg[rs2_i],32,1);
		rd_i=bin2dec(rd,5);
		ALU_op=assign(instype);
		RZ=alu();
		cout<<"ALU_op="<<ALU_op<<" ";
		update(rd_i);
	}
	else if((instype>=1&&instype<=18)||(instype>=20&&instype<=23)||instype==27||instype==50)		//I TYpe
	{
		for(int i=0;i<5;i++)
		{
			rs1[i]=IR[12+i];
			rd[i]=IR[20+i];
		}
		if(instype==16||instype==23)
		{
			for(int i=0;i<5;i++)
			{
			imm[i]=IR[7+i];
			}
			RB=bin2dec(imm,5);
		}
		else	
		{
		for(int i=0;i<12;i++)
		{
			imm[i]=IR[i];
		}
			RB=bin2dec(imm,12,1);
		}
		cout<<"\n";
		rs1_i=bin2dec(rs1,5);
		rd_i=bin2dec(rd,5);
		RA=bin2dec(reg[rs1_i],32,1);
		ALU_op=assign(instype);
		cout<<"ALU_op="<<ALU_op<<"\n";
		RZ=alu();
		if(instype==50)
		{
			PC=RZ/4;
			RZ=PC_temp*4;
		}
		if(instype>=1&&instype<=7)
			memaccess(1);
		update(rd_i);
	}
	else if((instype>=24&&instype<=26))				//S Type
	{
		for(int i=0;i<5;i++)
		{
			rs1[i]=IR[12+i];
			rs2[i]=IR[7+i];
			imm[7+i]=IR[20+i];
		}
		for(int i=0;i<7;i++)
		{
			imm[i]=IR[i];
		}
		rs1_i=bin2dec(rs1,5);
		rs2_i=bin2dec(rs2,5);
		RA=bin2dec(reg[rs1_i],32,1);
		RB=bin2dec(imm,12,1);
		ALU_op=assign(instype);
		cout<<"ALU_op="<<ALU_op<<"\n";
		RZ=alu();
		int q=bin2dec(reg[rs2_i],32,1);
		memaccess(2,q);
	}
	else if((instype>=44&&instype<=49))		//SB Type
	{
		for(int i=0;i<5;i++)
		{
			rs1[i]=IR[12+i];
			rs2[i]=IR[7+i];
			imm[2+i]=IR[1+i];
		}
		imm[0]=IR[0];
		imm[1]=IR[24];
		imm[7]=IR[6];
		imm[12]=0;
		for(int i=0;i<4;i++)
		{
			imm[8+i]=IR[20+i];
		}
		rs1_i=bin2dec(rs1,5);
		rs2_i=bin2dec(rs2,5);
		RA=bin2dec(reg[rs1_i],32,1);
		RB=bin2dec(reg[rs2_i],32,1);
		if(instype==48||instype==49)
		{
			RA=abs(RA);
			RB=abs(RB);
		}
		cout<<"\n";
		branch_offset=bin2dec(imm,13,1)/4;
		ALU_op=assign(instype);
		cout<<"ALU_op="<<ALU_op<<endl;
		RZ=alu();		
	}
	else if(instype==51)				//UJ type
	{
		for(int i=0;i<5;i++)
		{
			rd[i]=IR[20+i];
		}
		immu[0]=IR[0];
		for(int i=0;i<8;i++)
			immu[i+1]=IR[12+i];
		immu[9]=IR[11];
		for(int i=0;i<10;i++)
			immu[10+i]=IR[1+i];
		immu[20]=0;
		for(int i=0;i<5;i++)
		{
			rd[i]=IR[20+i];
		}
		rd_i=bin2dec(rd,5);
		RA=PC-1;
		
		
		RB=bin2dec(immu,21,1)/4;
		ALU_op=assign(instype);
		PC_temp=PC;
		cout<<"ALU_op="<<ALU_op<<"\n";
		PC=alu();
		RZ=PC_temp*4;
		update(rd_i);
	}
	else if(instype==19)
	{
		for(int i=0;i<20;i++)
			imm[i]=IR[i];
		RZ=bin2dec(imm,20);
		for(int i=0;i<5;i++)
			rd[i]=IR[20+i];
		rd_i=bin2dec(rd,5);
		update(rd_i);
	}
	}
	cout<<"\n";
	for(int i=0;i<32;i++)
	{
		cout<<"reg"<<i<<"=";
		for(int j=0;j<32;j++)
		{
			cout<<reg[i][j];
		}
		cout<<"\n";
	}
	 ofstream fout1;
  fout1.open("MEM1.txt");
  for(int i=1000;i<1500;i++)
  {
      for(int j=0;j<32;j++)
        fout1<<memory[i][j];
      fout1<<endl;
  }
  fout1.close();
  cout<<"Cycle_count="<<clock_cycle_count<<"\n";
}