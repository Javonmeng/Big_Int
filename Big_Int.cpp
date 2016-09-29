#include "Big_Int.h"
using namespace std;
char str1[MAXN],str2[MAXN],res[MAX];

void ReadData(){
	ifstream myfile;
	int i = 0;
	char c;
	myfile.open("/data.txt",ios::in);

	if(!myfile){
		cout << "Unable to open myfile";
	}
	while(!myfile.eof()){
		myfile>>c;
		str1[i] = c;
		i++;
	}
}
int Inspect(char *s)
{
	int i=0;
	if (s==NULL)
		return ERROR;
	while(s[i]!='\0'){
		if(s[i]>='0'&&s[i]<='9')
			i++;
		else if(i == 0){
			if(s[i] == '+' || s[i] =='-')
				i++;
			else
				return ERROR;
		}
		else{
			return OK;
		}
	}
	return OK;	
}
int InspectOp(char *op){
	if(op[0]=='+'||op[0]=='-'||op[0]=='*'||op[0]=='/'){
		if(op[1]!='\0'){
			return 0;
		} 
		return 1;
	}
	else
		return 0;
}
int main(){
	char res[MAX1],res1[MAX1];
	char tmp[MAX],extra[MAX];
	char op,ch;
	FILE *fp;
	int i=0;
	if((fp = fopen("data.txt","rt")) == NULL){
		printf("OPEN ERROR\n");
	}
	ch = fgetc(fp);
	while(ch != EOF){
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
	printf("%c",op);
	getchar();
   	switch(op){
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