#include "Big_Int.h"
using namespace std;
char str1[MAXN],str2[MAXN],res[MAX];//提前开辟内存 


int Inspect(char *s){//检查操作数 
	int i=0;
	if (s==NULL){
		printf("INPUT ERROR\n");
		return ERROR;
	}
	while(s[i]!='\0'){
		if(s[i]>='0'&&s[i]<='9')
			i++;
		else if(i == 0){
			if(s[i] == '+' || s[i] =='-')
				i++;
			else{
				printf("INPUT ERROR\n");
				return ERROR;
			}
		}
		else{
			return OK;
		}
	}
	return OK;	
}
int InspectOp(char op){//检查运算符 
	if(op=='+'||op=='-'||op=='*'||op=='/'){		
	
		return OK;
	}
	else{
		printf("INPUT ERROR\n");
		return ERROR;
	}
}
int main(){
	char res[MAX1];
	char tmp[MAX],extra[MAX];
	char op,ch;
	FILE *fp;
	int i=0;
	if((fp = fopen("data.txt","rt")) == NULL){//读入左操作数 
		printf("OPEN ERROR\n");
	}
	ch = fgetc(fp);
	while(ch != EOF){//读入右操作数 
		str1[i] = ch;
		i++;
		ch = fgetc(fp);
		if(ch == '\n'){
			str1[i] = '\0';
			break;
		}
	}
	i=0;
	ch = fgetc(fp);
	while(ch != EOF){
		str2[i] = ch;
		i++;
		ch = fgetc(fp);
		if(ch == '\n'){
			str2[i] = '\0';
			break;
		}
	}
	ch = fgetc(fp);
	op = ch;
	printf("%s\n",str1);
	printf("%s\n",str2);
	printf("%c\n",op);

	if(Inspect(str1)&&Inspect(str2)&&InspectOp(op)){
	
   	switch(op){//根据操作数运算 
   		case '+':
   			Big_Add(str1,str2,res);
   			printf("%s\n",res);
   			break;
   		case '-':
   			if(str2[0] == '+'){
   				str2[0] = '-';
   				Big_Add(str1,str2,res);
			}
   			else if(str2[0] == '-'){
   				str2[0] = '+';	
   				Big_Add(str1,str2,res);
			}
   			else{
   				strcpy(tmp+1,str2);
   				tmp[0] = '-';
   				Big_Add(str1,tmp,res);
			}
   			printf("%s\n",res);
   			break;
   		case '*':
   				Big_Mul(str1,str2,res);
   				printf("%s\n",res);
   			break;
   		case '/':
   				Big_Div(str1, str2, res, extra);
   				printf("%s\n",res);
   				printf("%s\n",extra);
   				
   			break;
		}
		
	}
}
