#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY 5000//4kb
int fix=0;
int p,r;
int m=0;
char* filename;
char* a;
char* f;
char b,o,*s;
int is_end_with(const char *str1, char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
        return -1;
    while(len2 >= 1)
    {
        if(str2[len2 - 1] != str1[len1 - 1])
            return 0;
        len2--;
        len1--;
    }
    return 1;
}
void itp_c(char *c,FILE *file){
	char MEM[1024]="";
	itoa(MEMORY,MEM,10);
	if(m!=0){
		itoa(m,MEM,10);
	}
	printf("Generating...(Please make sure you have run this program,if not,please try\"brainfuck %s\")\n",filename);
	char HEAD[1024]="";
	strcat(HEAD,"//Generate by brainfuck-comp\n#include <conio.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n#define MEMORY ");
	strcat(HEAD,MEM);
	strcat(HEAD,"\nchar a[MEMORY];\nint p;\nint main(){\n");
	fprintf(file,HEAD);
	char *d;
	r++;
	int ch=1;
	while(*c){
		switch(o=1,*c++){
			case '<':
				fprintf(file,"p--;\n");
				break;
			case '>':
				fprintf(file,"p++;\n");
				break;
			case '+':
				fprintf(file,"a[p]++;\n");
				break;
			case '-':
				fprintf(file,"a[p]--;\n");
				break;
			case '.':
				fprintf(file,"putchar(a[p]);\n");
				break;
			case ',':
				fprintf(file,"a[p]=getch();\nif(a[p]==3){\n	exit(0);\n}\n");
				break;
			case '[':
				fprintf(file,"while(a[p]){\n");
				break;
			case ']':
				fprintf(file,"}\n");
				break;
			default:
				break;
		}
	}
	fprintf(file,"}\n//use \"gcc out.c\" to build\n");
	printf("Done!Use \"gcc out.c\" to build\n");
	r--;
}
void itp(char *c){
	char *d;
	r++;
	int ch=1;
	while(*c){
		switch(o=1,*c++){
			case '<':
				if(p==0){
					printf("ERROR:MEMORY Overflow=>Pointer<0(Charter-%d)",ch);
					exit(0);
				}
				p--;
				ch++;
				break;
			case '>':
				if(p==MEMORY){
					printf("ERROR:MEMORY Overflow=>Pointer>Max Memory(Charter-%d)",ch);
					exit(0);
				}
				p++;
				ch++;
				break;
			case '+':
				if(a[p]==127&!fix){
					printf("ERROR:Data Overflow=>Data>127(Charter-%d)",ch);
					exit(0);
				}else if(fix){
					if(a[p]==127){
						a[p]=0;
					}else{
						a[p]++;
					}
				}else{
					a[p]++;
				}
				ch++;
				break;
			case '-':
				if(a[p]==0&!fix){
					printf("ERROR:Data Overflow=>Data<0(Charter-%d)",ch);
					exit(0);
				}else if(fix){
					if(a[p]==0){
						a[p]=127;
					}else{
						a[p]--;
					}
				}else{
					a[p]--;
				}
				ch++;
				break;
			case '.':putchar(a[p]);ch++;break;
			case ',':
				a[p]=getch();
				if(a[p]==3){
					exit(0);
				}
				ch++;
				break;
			case '[':
				for(b=1,d=c;b&&*c;c++)b+=*c=='[',b-=*c==']';
				if(!b){
					c[-1]=0;
					while(a[p])itp(d);
					c[-1]=']';
					break;
				}else{
					printf("ERROR:Loop error(Charter-%d)",ch);
					exit(0);
				}
				ch++;
		}
	}
	r--;
}
int e=0;
void main(int rc,char *rv[]){
	//a=malloc(MEMORY);
	//f=malloc(MEMORY);
	/*
	if(rc==4){
		if(strcmp(rv[2],"-m")==0){
			int MEM=atoi(rv[3]);
			printf("Set memory to %d(%dBytes)\n",MEM,MEM*sizeof(char));
			a=(char *)calloc(MEM-1,sizeof(char));
			f=(char *)calloc(MEM-1,sizeof(char));
			s=f;
			e=1;
		}else{
			printf("Usage:brainfuck [-c] <file> [-m memory]");
			return ;
		}
	}else{
		if(rc==5){
			if(strcmp(rv[3],"-m")==0){
				int MEM=atoi(rv[4]);
				printf("Set memory to %d(%dBytes)\n",MEM,MEM*sizeof(char));
				m=MEM;
				a=(char *)calloc(MEM-1,sizeof(char));
				f=(char *)calloc(MEM-1,sizeof(char));
				s=f;
			}else{
				printf("Usage:brainfuck [-c] <file> [-m memory]");
				return ;
			}
		}else{
			a=(char *)calloc(MEMORY,sizeof(char));
			f=(char *)calloc(MEMORY,sizeof(char));
			s=f;
		}
	}
	if(rc==1){
		printf("Usage:brainfuck [-c] <file> [-m memory]");
		return;
	}
	if(rc>2){
		if(strcmp(rv[1],"-c")==0){
			if(is_end_with(rv[2],".bf")!=1){
				printf("Not a brainfuck file");
				return;
			}
			FILE *z=fopen(rv[2],"r");
			filename=rv[2];
			if(z!=NULL){
				while((b=getc(z))>0)*s++=b;
				*s=0;
				FILE *file=fopen("out.c","w");
		 		itp_c(f,file);
		 		fclose(file);
			}else{
				printf("File doesn't exisit!");
			}
			return;
		}
	}
	if(rc==2|e==1){
		if(is_end_with(rv[1],".bf")!=1){
			printf("Not a brainfuck file");
			return;
		}
		FILE *z=fopen(rv[1],"r");
		filename=rv[1];
		if(z!=NULL){
			while((b=getc(z))>0)*s++=b;
			*s=0;
	 		itp(f);
	 		return;
		}else{
			printf("File doesn't exisit!");
			return;
		}
	}
	printf("Usage:brainfuck [-c|-m memory|fix] <file>");
	*/
	int comp=0;
	int memory_size=MEMORY;
	int i;
	for(i=0;i<rc;i++){
		/*
		char* str=rv[i];
		switch(str){
			case "-c":
				comp=1;
				break;
			case "-fix":
				fix=1;
				break;
			case "-m":
				memory_size=atoi(rv[i+1]);
				break;
		}
		*/
		if(strcmp(rv[i],"-c")==0){
			comp=1;
		}
		if(strcmp(rv[i],"-fix")==0){
			fix=1;
		}
		if(strcmp(rv[i],"-m")==0){
			memory_size=atoi(rv[i+1]);
		}
		if(strcmp(rv[i],"-h")==0){
			printf("Usage:brainfuck [-c|-m memory|-fix|-h|-v] <file>");
			exit(0);
		}
		if(strcmp(rv[i],"-v")==0){
			printf("Brainfuck compiler V1.2.0\nMade by zihaoxu");
			exit(0);
		}
	}
	if(!fix){
		printf("Set memory to %d(%dBytes)\n",memory_size,memory_size*sizeof(char));
		m=memory_size;
		a=(char *)calloc(memory_size-1,sizeof(char));
		f=(char *)calloc(memory_size-1,sizeof(char));
		s=f;
	}else{
		printf("Set memory to %d(%dBytes)\n",memory_size,memory_size*2);
		m=memory_size;
		a=(char *)calloc(memory_size-1,2);
		f=(char *)calloc(memory_size-1,2);
		s=f;
	}
	if(comp){
		if(is_end_with(rv[rc-1],".bf")!=1){
			printf("Not a brainfuck file");
			return;
		}
		FILE *z=fopen(rv[rc-1],"r");
		filename=rv[rc-1];
		if(z!=NULL){
			while((b=getc(z))>0)*s++=b;
			*s=0;
			FILE *file=fopen("out.c","w");
	 		itp_c(f,file);
	 		fclose(file);
		}else{
			printf("File doesn't exisit!");
		}
		return;
	}else{
		if(is_end_with(rv[rc-1],".bf")!=1){
			printf("Not a brainfuck file");
			return;
		}
		FILE *z=fopen(rv[rc-1],"r");
		filename=rv[rc-1];
		if(z!=NULL){
			while((b=getc(z))>0)*s++=b;
			*s=0;
	 		itp(f);
	 		return;
		}else{
			printf("File doesn't exisit!");
			return;
		}
	}
}


