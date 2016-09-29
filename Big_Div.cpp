void mul(char *Val, char *res, int x){//x为一位整数，运算过程中获取商 
	int len0 = strlen(Val);
	int tmp[len0 ++];
	tmp[len0-1]=0;
	int i;
	for(i = 0; i < len0 - 1; i++){
		tmp[len0 - i - 2] = (Val[i] - '0') * x;
	}
	for(i = 0; i < len0 - 1; i++){
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	if(tmp[len0-1] == 0)
		len0--;
	for(i = 0; i < len0; i++)
			res[i] = tmp[len0 - i - 1] + '0';
}

void Div(char *leftVal, char *rightVal, int &res, char *extra){//被除数只比除数多一位或者相等 ，商只有一位 
	int i,len1;
	len1 = strlen(leftVal);
	char tmp[len1];
	int array[len1];
	res = 1;
	if(!isLeftBigger(leftVal,rightVal)){
		res = 0;
		extra=leftVal;
	}
	else if(strcmp( leftVal, rightVal ) == 0){
		res = 1;
		extra[0] = '0', extra[1] = '\0';
	}
	else{
	while(res <= 9){
		mul(rightVal, tmp, res);
		if(isLeftBigger(leftVal,tmp)){
			res++;
		}
		else{
			res--;
			break;
		}
	}
	mul(rightVal, tmp, res);
	Sub(leftVal,tmp, array);
	for(int i = maxlen - 1; i >= 0; --i)
		extra[maxlen - i - 1] = array[i] + '0';	
	extra[maxlen] = '\0';
	}
} 
void Big_Div(char *leftVal, char *rightVal, char *res, char *extra){//模拟竖式除法运算 
	int len1,len2,c,i;
	len1 = strlen(leftVal), len2 = strlen(rightVal);
	char tmp[len2+1];
	if(len2 == 1 && rightVal[0] == '0'){
		printf("INPUT ERROR\n");
	}
	else if(len1 == 1 && leftVal[0] == '0'){
		strcpy(res,"0");
		strcpy(extra,"0");
	}
	else if(len1 < len2){
		strcpy(res,"0");
		extra = leftVal;
	}
	else if(len1 ==len2){
		Div(leftVal, rightVal, c, extra);
		res[0] = c + '0';
	}
	else{
		int now = 0;
		int j=1;
		for(;now < len2; now++)
			tmp[now] = leftVal[now];
		Div(tmp,rightVal,c,tmp);
		res[0] = '0' + c;
		while(leftVal[now] != '\0'){
			int len3 = strlen(tmp);
			tmp[len3] = leftVal[now];
			tmp[len3+1] = '\0';
			Div(tmp, rightVal, c, tmp);
			res[j] = '0' + c;
			j++;
			now++;
		}
		strcpy(extra,tmp);//	extra = tmp;
		now = 0, j = 0;
		while(res[now] != '\0' && res[now] == '0')
			now++;
		for(j = now,i = 0; res[j] != '\0'; j++,i++)
			res[i] = res[j];
		res[i] = '\0';
	}

}

