/**********************************************/
/** Grid show + Recognize color + Solve cube **/
/**********************************************/

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SWAP(a,b) TEMP=a;a=b;b=TEMP;
#define CHAROFFSET 65

/************ Defination: recognizing colors ***********/
char range[3][3]; // Recognition results
char    up[3][3]={0};
char  down[3][3]={0};
char front[3][3]={0};
char  back[3][3]={0};
char  left[3][3]={0};
char right[3][3]={0};
float RED=0; // Sum all pixels
float GREEN=0;
float BLUE=0;
UINT8 _red[25][23]; // Store RGB
UINT8 _green[25][23];
UINT8 _blue[25][23];

/************ Defination: solving the cube ***********/
unsigned short int Cube_Solve_Order[100]={0}; // Simplified seq list
char initiate_order[] = "FU BL FR LF BU DR LD LU UR DB DF RB BUR LFU LDF FRU UBL DLB DBR DRF"; // 68 chars with \0 in total.
char
moveamount[20],
*faces = "RLFBUD",*order = "AECGBFDHIJKLMSNTROQP",
*bithash = "TdXhQaRbEFIJUZfijeYV",*perm = "AIBJTMROCLDKSNQPEKFIMSPRGJHLNTOQAGCEMTNSBFDHORPQ",
pos[20], ori[20], val[20],TEMP,*tables[8];
int move1[20],phase = 0,tablesize[] = { 1,4096,  6561,4096,  256,1536,  13824,576 };
char flag[6]={'Y','W','G','B','R','O'};			// Seq info of six faces.
												//#define  y 1
												//#define  w 2
												//#define  g 3
												//#define  b 4
												//#define  r 5
												//#define  o 6

/************ Function statement ***********/
void Color_Output_Square(int x,int y); // Read pixel info in a 25x23 square.
void Color_Discrimination(int k,int l,char range[3][3]); // Recognize colors.
void Cube_Range_Main();
int  Cube_Check(); // Check all six faces of the colors of the cube.
void Cube_Trans(char a[3][3],char flag[6]); // Representation transformer.
int Colorget_Cubeslove(int face); // Recognize colors & Slove cube.


/************ Functions: solving the cube ***********/
void Color_Output_Square(int x,int y) // Read 25x23 square pixels.
{
	int i,j,k,l;
	UINT8 red,green,blue;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xc1f00020)+(0x280*(x+1))+(y+1);
	for(i=0;i<25;i++)
	{
		for(j=0;j<23;j++)
		{
			_red[i][j]=((*(UINT16 *)ADDR)&0xF800)>>8;
			_green[i][j]=((*(UINT16 *)ADDR)&0x07E0)>>3;
			_blue[i][j]=((*(UINT16 *)ADDR)&0x001F)<<3;
			*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF; // Clear after reading data
			//printf("--(%3d:%3d:%3d)\n",_red[i][j],_green[i][j],_blue[i][j]);
			ADDR++;
		}
		ADDR+=0x269;
	}
	for(i=0;i<25;i++) // Averaging 
	{
		for(j=0;j<23;j++)
		{
			RED+=_red[i][j];
			GREEN+=_green[i][j];
			BLUE+=_blue[i][j];
		}
	}
	RED/=575;GREEN/=575;BLUE/=575;
	if(RED<1.0) RED=1;
	if(GREEN<1.0) GREEN=1;
	if(BLUE<1.0) BLUE=1;
	printf("(%3.0f:%3.0f:%3.0f)\n",RED,GREEN,BLUE);
}

void Color_Discrimination(int k,int l,char range[3][3]) // Recognize colors.
{
	// we design a very simple method to recognize colors of the cube. 
	if( (RED>50)&&(GREEN>50)&&(BLUE>50)&&(GREEN/BLUE<2)&&(GREEN/RED<2)&&((GREEN/RED-GREEN/BLUE)<0.3)&&((GREEN/RED-GREEN/BLUE)>-0.3)&&(GREEN/BLUE<1.2)&&(GREEN/BLUE>0.8) )	//white
		range[k][l]='W';
	else if( (RED/GREEN<1.5)&&(RED/GREEN>1)&&(GREEN/BLUE>1)&&(GREEN/BLUE<3))	//yellow
		range[k][l]='Y';
	else if( ((RED+GREEN)>150)&&(RED/GREEN<2.5)&&(RED/GREEN>1) )	//orange
		range[k][l]='O';

	else if((RED>GREEN)&&(RED>BLUE))
		range[k][l]='R';
	else if((GREEN>RED)&&(GREEN>BLUE))
		range[k][l]='G';
	else if((BLUE>GREEN)&&(BLUE>RED))
		range[k][l]='B';
	else
		{
			printf("ERROR!!!");
			range[k][l]='#';
		}
}

int Colorget_Cubeslove(int face)
{
	int k,l;
    for(k=0;k<3;k++) // Get average and recognize colors.
    {
	   for(l=0;l<3;l++)
	   {
		   Color_Output_Square(146+k*80,226+l*80);
		   Color_Discrimination(k,l,range);
		   RED=0;GREEN=0;BLUE=0; // For the next one
	   }
    }
    for(k=0;k<3;k++)
    {
	   for(l=0;l<3;l++)
	   {
		   printf("%c ",range[k][l]);
	   }
	   printf("\n");
    }
    printf("\n");
    printf("\n");
    switch(face)
    {
    case 1:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   up[k][l]=range[k][l];
        return 0;
    case 2:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   down[k][l]=range[k][l];
        return 0;
    case 3:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   front[k][l]=range[k][l];
        return 0;
    case 4:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   back[k][l]=range[k][l];
        return 0;
    case 5:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   left[k][l]=range[k][l];
        return 0;
    case 6:
        for(k=0;k<3;k++)
    	   for(l=0;l<3;l++)
    		   right[k][l]=range[k][l];
        Cube_Range_Main();
        if( Cube_Check() )
        {
        	Cube_main();
        	return 1;
        }
        else
        	return 0;
    }
}

/************ Functions: grids ***********/
void Grid_Square(int x,int y)
{
	int i,j;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xc1f00020)+(0x280*x)+y;
	for(i=0;i<13;i++)
	{
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		*(UINT16 *)(ADDR+0x4100)=(*(UINT16 *)(ADDR+0x4100))|0xFFFF;
		ADDR+=2;
	}
	ADDR=(UINT16 *)(0xc1f00020)+(0x280*x)+y;
	for(i=0;i<13;i++)
	{
		ADDR+=2*0x280;
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		*(UINT16 *)(ADDR+24)=(*(UINT16 *)(ADDR+24))|0xFFFF;
	}
}

void Grid_Hang(int hang,int hang_left,int hang_right)
{
	int i;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xc1f00020)+(0x280*hang)+hang_left;
	for(i=0;i<(hang_right-hang_left);i++)
	{
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		ADDR++;
	}
}

void Grid_Lie(int lie,int lie_up,int lie_down)
{
	int i;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xc1f00020)+(lie)+(0x280*lie_up);
	for(i=0;i<(lie_down-lie_up);i++)
	{
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		ADDR=ADDR+0x280;
	}
}

void Grid_On_All() // The big box
{
	int k,l;
	Grid_Hang(120,200,440);
	Grid_Hang(200,200,440);
	Grid_Hang(280,200,440);
    Grid_Hang(360,200,440);
    Grid_Lie(200,120,360);
    Grid_Lie(280,120,360);
    Grid_Lie(360,120,360);
    Grid_Lie(440,120,360);
    for(k=0;k<3;k++)
    {
	   for(l=0;l<3;l++)
	   {
		   Grid_Square(146+k*80,226+l*80);
	   }
    }
}

/************ Subunctions: solving the cube () ***********/

void Cube_Solve_Order_Transmission(int a[100])
{
	int x;
	for(x=0;x<100;x++)
	{
		a[x]=Cube_Solve_Order[x];
	}
}

int Cube_Check()
{
	int z,i_Y=1,i_W=1,i_G=1,i_B=1,i_R=1,i_O=1;
	for ( z = 0; z<68; z++)
	{
		if(initiate_order[z]=='U')
			i_Y++;
		else if(initiate_order[z]=='D')
			i_W++;
		else if(initiate_order[z]=='F')
			i_G++;
		else if(initiate_order[z]=='B')
			i_B++;
		else if(initiate_order[z]=='L')
			i_R++;
		else if(initiate_order[z]=='R')
			i_O++;
	}
	if( (i_Y==9)&&(i_W==9)&&(i_G==9)&&(i_B==9)&&(i_R==9)&&(i_O==9) )
	{
		printf("/*****Got the color rightly! ******/\n");
		return(1);
	}
	else
	{
		printf("Cannot get the color rightly! \n");
		return(0);
	}
}

void Cube_Range_Main() // Generate standrad string
{
	int i,j,k=1,z,p;

    Cube_Trans(up,flag);
	Cube_Trans(down,flag);
	Cube_Trans(front,flag);
	Cube_Trans(back,flag);
	Cube_Trans(left,flag);
	Cube_Trans(right,flag);

	initiate_order[0]=up[2][1],initiate_order[1]=front[0][1],initiate_order[2]=' ';
	initiate_order[3]=up[1][2],initiate_order[4]=right[0][1],initiate_order[5]=' ';
	initiate_order[6]=up[0][1],initiate_order[7]=back[0][1],initiate_order[8]=' ';
	initiate_order[9]=up[1][0],initiate_order[10]=left[0][1],initiate_order[11]=' ';

	initiate_order[12]=down[0][1],initiate_order[13]=front[2][1],initiate_order[14]=' ';
	initiate_order[15]=down[1][2],initiate_order[16]=right[2][1],initiate_order[17]=' ';
	initiate_order[18]=down[2][1],initiate_order[19]=back[2][1],initiate_order[20]=' ';
	initiate_order[21]=down[1][0],initiate_order[22]=left[2][1],initiate_order[23]=' ';

	initiate_order[24]=front[1][2],initiate_order[25]=right[1][0];initiate_order[26]=' ';
	initiate_order[27]=front[1][0],initiate_order[28]=left[1][2];initiate_order[29]=' ';
	initiate_order[30]=back[1][0],initiate_order[31]=right[1][2];initiate_order[32]=' ';
	initiate_order[33]=back[1][2],initiate_order[34]=left[1][0];initiate_order[35]=' ';

	initiate_order[36]=up[2][2],initiate_order[37]=front[0][2],initiate_order[38]=right[0][0];initiate_order[39]=' ';
	initiate_order[40]=up[0][2],initiate_order[41]=right[0][2],initiate_order[42]=back[0][0];initiate_order[43]=' ';
	initiate_order[44]=up[0][0],initiate_order[45]=back[0][2],initiate_order[46]=left[0][0];initiate_order[47]=' ';
	initiate_order[48]=up[2][0],initiate_order[49]=left[0][2],initiate_order[50]=front[0][0];initiate_order[51]=' ';

	initiate_order[52]=down[0][2],initiate_order[53]=right[2][0],initiate_order[54]=front[2][2];initiate_order[55]=' ';
	initiate_order[56]=down[0][0],initiate_order[57]=front[2][0],initiate_order[58]=left[2][2];initiate_order[59]=' ';
	initiate_order[60]=down[2][0],initiate_order[61]=left[2][0],initiate_order[62]=back[2][2];initiate_order[63]=' ';
	initiate_order[64]=down[2][2],initiate_order[65]=back[2][0],initiate_order[66]=right[2][2];initiate_order[67]='\0';
	printf("\n*********\n");
}

void Cube_Trans(char a[3][3],char flag[6])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			{
					if(a[i][j]==flag[0]) a[i][j]='U';
					else if(a[i][j]==flag[1]) a[i][j]='D';
					else if(a[i][j]==flag[2]) a[i][j]='F';
					else if(a[i][j]==flag[3]) a[i][j]='B';
					else if(a[i][j]==flag[4]) a[i][j]='L';
					else if(a[i][j]==flag[5]) a[i][j]='R';
			}
}

void cycle(char*p, char*a)
{
	SWAP(p[*a - CHAROFFSET], p[a[1] - CHAROFFSET]);
	SWAP(p[*a - CHAROFFSET], p[a[2] - CHAROFFSET]);
	SWAP(p[*a - CHAROFFSET], p[a[3] - CHAROFFSET]);
}

void twist(int i, int a)
{
	i -= CHAROFFSET;
	ori[i] = (ori[i] + a + 1) % val[i];
}

void reset()
{
	int i;
	for ( i = 0; i<20; pos[i] = i, ori[i++] = 0);
}

// convert permutation of 4 chars to a number in range 0..23
int permtonum(char* p)
{
	int n = 0,a,b;
	for ( a = 0; a<4; a++) {
		n *= 4 - a;
		for ( b = a; ++b<4; )
			if (p[b]<p[a]) n++;
	}
	return n;
}

// convert number in range 0..23 to permutation of 4 chars.
void numtoperm(char* p, int n, int o)
{
	int a,b;
	p += o;
	p[3] = o;
	for ( a = 3; a--;) {
		p[a] = n % (4 - a) + o;
		n /= 4 - a;
		for ( b = a; ++b<4; )
			if (p[b] >= p[a]) p[b]++;
	}
}

// get index of cube position from table t
int getposition(int t)
{
	int i = -1, n = 0;
	int corn[8], j, k, l, corn2[4];
	switch (t) {
		// case 0 does nothing so returns 0
	case 1://edgeflip
		   // 12 bits, set bit if edge is flipped
		for (; ++i<12;) n += ori[i] << i;
		break;
	case 2://cornertwist
		   // get base 3 number of 8 digits - each digit is corner twist
		for (i = 20; --i>11;) n = n * 3 + ori[i];
		break;
	case 3://middle edge choice
		   // 12 bits, set bit if edge belongs in Um middle slice
		for (; ++i<12;) n += (pos[i] & 8) ? (1 << i) : 0;
		break;
	case 4://ud slice choice
		   // 8 bits, set bit if UD edge belongs in Fm middle slice
		for (; ++i<8;) n += (pos[i] & 4) ? (1 << i) : 0;
		break;
	case 5://tetrad choice, twist and parity
		// 8 bits, set bit if corner belongs in second tetrad.
		// also separate pieces for twist/parity determination
		k = j = 0;
		for (; ++i<8;)
			if ((l = pos[i + 12] - 12) & 4) {
				corn[l] = k++;
				n += 1 << i;
			}
			else corn[j++] = l;
			//Find permutation of second tetrad after solving first
			for (i = 0; i<4; i++) corn2[i] = corn[4 + corn[i]];
			//Solve one piece of second tetrad
			for (; --i;) corn2[i] ^= corn2[0];

			// encode parity/tetrad twist
			n = n * 6 + corn2[1] * 2 - 2;
			if (corn2[3]<corn2[2])n++;
			break;
	case 6://two edge and one corner orbit, permutation
		n = permtonum(pos) * 576 + permtonum(pos + 4) * 24 + permtonum(pos + 12);
		break;
	case 7://one edge and one corner orbit, permutation
		n = permtonum(pos + 8) * 24 + permtonum(pos + 16);
		break;
	}
	return n;
}

// sets cube to any position which has index n in table t
void setposition(int t, int n)
{
	int i = 0, j = 12, k = 0;
	char *corn = "QRSTQRTSQSRTQTRSQSTRQTSR";
	reset();
	switch (t) {
		// case 0 does nothing so leaves cube solved
	case 1://edgeflip
		for (; i<12; i++, n >>= 1) ori[i] = n & 1;
		break;
	case 2://cornertwist
		for (i = 12; i<20; i++, n /= 3) ori[i] = n % 3;
		break;
	case 3://middle edge choice
		for (; i<12; i++, n >>= 1) pos[i] = 8 * n & 8;
		break;
	case 4://ud slice choice
		for (; i<8; i++, n >>= 1) pos[i] = 4 * n & 4;
		break;
	case 5://tetrad choice,parity,twist
		corn += n % 6 * 4;
		n /= 6;
		for (; i<8; i++, n >>= 1)
			pos[i + 12] = n & 1 ? corn[k++] - CHAROFFSET : j++;
		break;
	case 6://slice permutations
		numtoperm(pos, n % 24, 12); n /= 24;
		numtoperm(pos, n % 24, 4); n /= 24;
		numtoperm(pos, n, 0);
		break;
	case 7://corner permutations
		numtoperm(pos, n / 24, 8);
		numtoperm(pos, n % 24, 16);
		break;
	}
}

// do a clockwise quarter turn cube move1
void domove(int m)
{
	char *p = perm + 8 * m, i = 8;
	//cycle the edges
	cycle(pos, p);
	cycle(ori, p);
	//cycle the corners
	cycle(pos, p + 4);
	cycle(ori, p + 4);
	//twist corners if RLFB
	if (m<4)
		for (; --i>3;) twist(p[i], i & 1);
	//flip edges if FB
	if (m<2)
		for (i = 4; i--;) twist(p[i], 0);
}

// calculate a pruning table
void filltable(int ti)
{
	int n = 1, l = 1, tl = tablesize[ti],i,f,q,r;
	// alocate table memory
	char* tb = tables[ti] = (char *)malloc(sizeof(char)*tl);//new char[tl];
															//clear table
	memset(tb, 0, tl);
	//mark solved position as depth 1
	reset();
	tb[getposition(ti)] = 1;

	// while there are positions of depth l
	while (n) {
		printf("%d\n",n);
		n = 0;
		// find each position of depth l
		for ( i = 0; i<tl; i++) {
			if (tb[i] == l) {
				//construct that cube position
				setposition(ti, i);
				// try each face any amount
				for ( f = 0; f<6; f++) {
					for ( q = 1; q<4; q++) {
						domove(f);
						// get resulting position
						 r = getposition(ti);
						// if move1 as allowed in that phase, and position is a new one
						if ((q == 2 || f >= (ti & 6)) && !tb[r]) {
							// mark that position as depth l+1
							tb[r] = l + 1;
							n++;
						}
					}
					domove(f);
				}
			}
		}
		l++;
	}
}

// Pruned tree search. recursive.
int searchphase(int movesleft, int movesdone, int lastmove)
{
	int i,j;
	// prune - position must still be solvable in the remaining moves available
	if (tables[phase][getposition(phase)] - 1 > movesleft ||
		tables[phase + 1][getposition(phase + 1)] - 1 > movesleft) return 0;

	// If no moves left to do, we have solved this phase
	if (!movesleft) return 1;

	// not solved. try each face move1
	for ( i = 6; i--;) {
		// do not repeat same face, nor do opposite after DLB.
		if (i - lastmove && (i - lastmove + 1 || i | 1)) {
			move1[movesdone] = i;
			// try 1,2,3 quarter turns of that face
			for ( j = 0; ++j<4;) {
				//do move1 and remember it
				domove(i);
				moveamount[movesdone] = j;
				//Check if phase only allows half moves of this face
				if ((j == 2 || i >= phase) &&
					//search on
					searchphase(movesleft - 1, movesdone + 1, i)) return 1;
			}
			// put face back to original position.
			domove(i);
		}
	}
	// no solution found
	return 0;
}

int spldit(char dst[][8], char* str, const char* spl)
{
	int n = 0;
	char *result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}

void Cube_GetResult(char sInput[])
{
	int l=0,x=0,count=0,f, i = 0, j = 0, k = 0, pc, mor,arg;
	char argv[25][8];
	arg = spldit(argv, sInput, " ");
	if (arg != 20)
	{
		printf("error");
	}
	for (k = 0; k < 20; k++) val[k] = k < 12 ? 2 : 3;
	for (j = 0; j < 8; j++) {printf("----%d----\n",j);filltable(j);}
	for (i = 0; i < 20; i++) {
		f = pc = k = mor = 0;
		for (; f < val[i]; f++) {
			j = strchr(faces, argv[i][f]) - faces;
			if (j > k) { k = j; mor = f; }
			pc += 1 << j;
		}
		for (f = 0; f < 20; f++)
			if (pc == bithash[f] - 64) break;
		pos[order[i] - CHAROFFSET] = f;
		ori[order[i] - CHAROFFSET] = mor%val[i];
	}
	for (phase=0; phase < 8; phase += 2)
	{
		for (j = 0; !searchphase(j, 0, 9); j++);
		for (i = 0; i < j; i++)
		{
			printf("%c%d", "FBRLUD"[move1[i]], moveamount[i]);
			printf(" ");
			Cube_Solve_Order[2*count]=("FBRLUD"[move1[i]]);
			Cube_Solve_Order[2*count+1]=moveamount[i];
			count++;
		}
	}
	Cube_Solve_Order[2*count+1]='\0';
	/*
	for (x = 0; x < count; x++)
	{
		if(Cube_Solve_Order[2*x]==Cube_Solve_Order[2*x+2])
		{
			if((Cube_Solve_Order[2*x+1]+Cube_Solve_Order[2*x+3])==3)
			{
				Cube_Solve_Order[2*x+1]=3;
				l=2*x;
				while(Cube_Solve_Order[l+4]!=0)
				{
					Cube_Solve_Order[l+2]=Cube_Solve_Order[l+4];
					Cube_Solve_Order[l+4]=0;
					l++;
				}
			}
		}
	}*/
	printf("\n");
	for(x=0;x<80;x+=2)
	{
		printf("%c%d ",Cube_Solve_Order[x],Cube_Solve_Order[x+1]);
	}
	printf("\n");
}

int Cube_main()
{
	int z;
	for ( z = 0; z<100; z++)
		Cube_Solve_Order[z]=0;
	for ( z = 0; z<68; z++)
		printf("%c", initiate_order[z]);
	printf("\n");
	Cube_GetResult(initiate_order);
}

/******************** Original code *******************/

/*
void Color_RGB2_3() // Color_RGB2_3() RGB565 decoding program
{
	UINT8 red,green,blue;
	UINT16 i,j;
	UINT16 *ptr;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xC1000000);
	for(i=0;i<480;i++)
	{
		for(j=0;j<640;j++)
		{
			red=((*(UINT16 *)ADDR)&0xF800)>>8;
			green=((*(UINT16 *)ADDR)&0x07E0)>>3;
			blue=((*(UINT16 *)ADDR)&0x001F)<<3;
			printf("(%d,%d)--(%3d:%3d:%3d)\n",i,j,red,green,blue);
			ADDR++;
		}
	}
}*/

/*void Grid()
{
	int i;
	UINT16 *ADDR;
	ADDR=(UINT16 *)(0xc1f4B020);

	for(i=0;i<640;i++)
	{
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		ADDR++;
	}
	for(i=0;i<640;i++)
	{
		*(UINT16 *)ADDR=(*(UINT16 *)ADDR)|0xFFFF;
		ADDR++;
	}
}*/
