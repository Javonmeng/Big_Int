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
	//µπ÷√ 
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
	//µ˜’˚º”∑® ‰≥ˆ 
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
	//µ˜’˚ºı∑® ‰≥ˆ 
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
void Add(char *leftVal,char *rightVal,int *resBuf){//Œﬁ∑˚∫≈º”∑® 
	int A[MAX],B[MAX];
	Trans(leftVal,rightVal,A,B);
	for(int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] + B[i];
	Adjust_Add(resBuf);
}
void Sub(char *leftVal,char *rightVal, int *resBuf){//Œﬁ∑˚∫≈ºı∑® 
	int A[MAX],B[MAX];
	Trans(leftVal,rightVal,A,B);
	for(int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] - B[i];
	Adjust_Sub(resBuf);
}

void Big_Add(char *leftVal, char *rightVal, char *res){//ºı∑®ø¥◊ˆº”∑® 
	int len0;
	len0 = strlen(leftVal) > strlen(rightVal) ? strlen(leftVal) : strlen(rightVal);
	int resBuf[len0];
	if((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <='9')){
		Add(leftVal, rightVal, resBuf);
		for(int i = maxlen - 1; i >= 0; --i)
			res[maxlen - i - 1] = resBuf[i]+'0';
	}//Ê≠£Â∏∏Êó†Á¨¶Âè∑ËæìÂÖ•
	else if((leftVal[0] >= '0' && leftVal[0] <= '9') &&(rightVal[0] == '+' || rightVal[0] == '-')){
		if(rightVal[0] == '+'){
			Add(leftVal, rightVal+1, resBuf);//Âè≥ÂºèÂ∏¶Ê≠£Âè∑
			for(int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else{				  //Âè≥ÂºèÂ∏¶Ë¥üÂè∑
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
			//Â∑¶ÂºèÂ∏¶Ê≠£Âè∑
			Add(leftVal + 1, rightVal, resBuf);
			for(int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else{	             //Â∑¶ÂºèÂ∏¶Ë¥üÂè∑
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
	}//‰∏§ÂºèÈÉΩÂ∏¶Ê≠£Âè∑ÊàñËÄÖË¥üÂè∑
	else if((leftVal[0] == '+' && rightVal[0] == '-') ||(leftVal[0] == '-' && rightVal[0] == '+')){
		if(leftVal[0] == '+'){
			//Â∑¶ÂºèÂ∏¶Ê≠£Âè∑
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
		else{	             //Â∑¶ÂºèÂ∏¶Ë¥üÂè∑
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
	}//‰∏§Âºè‰∏ÄÊ≠£‰∏ÄË¥ü
}

