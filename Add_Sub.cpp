int maxlen;
void Trans(char *str1,char *str2,int A[MAX],int B[MAX]){
	int len1,len2;
	len1 = strlen(str1);
	len2 = strlen(str2);
	maxlen = (len1 > len2 ? len1 : len2)+1;
	for(int i = 0; i < len1; ++i)
		A[i] = str1[len1 - i - 1] - '0';
	for(int i = 0; i < len2; ++i)
		B[i] = str2[len2  - i - 1] - '0';
	//倒置 
	for(int i = len1; i < maxlen; ++i)
		A[i] = 0;
	for(int i = len2; i < maxlen; ++i)
		B[i] = 0;
}
void Adjust_Add(int *res){
	for(int i = 0; i < maxlen; ++i){
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//调整加法输出 
	while(res[maxlen-1] == 0)
		maxlen--;
}

void Adjust_Sub(int *res){
	int borrow = 0;
	for(int i = 0; i < maxlen; ++i){
		if(res[i] < 0)
			borrow = 1;
		res[i + 1] -= borrow;
		borrow = 0;
		res[i] = (res[i]+10)%10;
	}
	//调整减法输出 
	while(res[maxlen-1] == 0)
		maxlen--;
}
int isLeftBigger(char *str1,char *str2){
	if(strlen(str1) > strlen(str2))
		return YES;
	else if(strlen(str1) < strlen(str2))
		return NO;
	else{
		if(strcmp(str1,str2)>=0)
			return YES;
		else
			return NO;
	}
}
void Add(char *leftVal,char *rightVal,int *resBuf){//无符号加法 
	int A[MAX],B[MAX];
	Trans(leftVal,rightVal,A,B);
	for(int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] + B[i];
	Adjust_Add(resBuf);
}
void Sub(char *leftVal,char *rightVal, int *resBuf){//无符号减法 
	int A[MAX],B[MAX];
	Trans(leftVal,rightVal,A,B);
	for(int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] - B[i];
	Adjust_Sub(resBuf);
}

void Big_Add(char *leftVal, char *rightVal, char *res){//减法看做加法 
	int len0;
	len0 = strlen(leftVal) > strlen(rightVal) ? strlen(leftVal) : strlen(rightVal);
	int resBuf[len0];
	if((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <='9')){
		Add(leftVal, rightVal, resBuf);
		for(int i = maxlen - 1; i >= 0; --i)
			res[maxlen - i - 1] = resBuf[i]+'0';
	}//姝ｅ父鏃犵鍙疯緭鍏�
	else if((leftVal[0] >= '0' && leftVal[0] <= '9') &&(rightVal[0] == '+' || rightVal[0] == '-')){
		if(rightVal[0] == '+'){
			Add(leftVal, rightVal+1, resBuf);//鍙冲紡甯︽鍙�
			for(int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else{				  //鍙冲紡甯﹁礋鍙�
			if(isLeftBigger(leftVal,rightVal+1)){
				Sub(leftVal, rightVal+1, resBuf);
				for(int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else{
				Sub(rightVal + 1, leftVal, resBuf);
				res[0] = '-';
				for(int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;

			}
		}
	}
	else if((rightVal[0] >= '0' && rightVal[0] <= '9') &&(leftVal[0] == '+' || leftVal[0] == '-')){

		if(leftVal[0] == '+'){
			//宸﹀紡甯︽鍙�
			Add(leftVal + 1, rightVal, resBuf);
			for(int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else{	             //宸﹀紡甯﹁礋鍙�
			if(isLeftBigger(leftVal+1,rightVal)){
				Sub(leftVal+1, rightVal, resBuf);
				res[0] = '-';
				for(int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else{
				Sub(rightVal, leftVal + 1, resBuf);
				for(int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
	    }
	}
	else if((leftVal[0] == '+' && rightVal[0] == '+') ||(leftVal[0] == '-' && rightVal[0] == '-') ){
		Add(leftVal+1, rightVal+1, resBuf);
		if(leftVal[0] == '+')
			for(int i = 0; i <= maxlen - 1; ++i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		else{
			for(int i = maxlen; i >= 1; --i)
				res[maxlen - i + 1] = resBuf[i - 1]+'0';
			res[0] = '-';
			maxlen++;
		}
	}//涓ゅ紡閮藉甫姝ｅ彿鎴栬�呰礋鍙�
	else if((leftVal[0] == '+' && rightVal[0] == '-') ||(leftVal[0] == '-' && rightVal[0] == '+')){
		if(leftVal[0] == '+'){
			//宸﹀紡甯︽鍙�
			if(isLeftBigger(leftVal+1,rightVal + 1)){
				Sub(leftVal+1, rightVal + 1, resBuf);
				for(int i = maxlen - i; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else{
				Sub(rightVal + 1, leftVal + 1, resBuf);
				res[0] = '-';
				for(int i = maxlen; i >= 1; --i)
					res[maxlen - i +1] = resBuf[i - 1] + '0';
			}
		}
		else{	             //宸﹀紡甯﹁礋鍙�
			if(isLeftBigger(leftVal+1,rightVal + 1)){
				Sub(leftVal+1, rightVal + 1, resBuf);
				res[0] = '-';
				for(int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else{
				Sub(rightVal + 1, leftVal + 1, resBuf);
				for(int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
	    }
	}//涓ゅ紡涓�姝ｄ竴璐�
}

