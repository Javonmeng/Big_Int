int len;
class Complex
{
public:
    double real, imag;
    Complex(double real = 0.0, double imag = 0.0)
    {
        this->real = real, this->imag = imag;
    }
    Complex operator - (const Complex &elem) const
    {
        return Complex(this->real - elem.real, this->imag - elem.imag);
    }
    Complex operator + (const Complex &elem) const
    {
        return Complex(this->real + elem.real, this->imag + elem.imag);
    }
    Complex operator * (const Complex &elem) const
    {
        return Complex(this->real * elem.real - this->imag * elem.imag, this->real * elem.imag + this->imag * elem.real);
    }
    void setValue(double real = 0.0, double imag = 0.0)
    {
        this->real = real, this->imag = imag;
    }
};


void Swap(Complex &a, Complex &b){
	Complex tmp = a;
	a = b;
	b = tmp;
}//交换
int max(int a, int b){
	return a > b ? a : b;
}
void Prepare(char *str1,char *str2,Complex A[MAX],Complex B[MAX]){
	int len1,len2,mlen;
	len1 = strlen(str1);
	len2 = strlen(str2);
	mlen = max(len1,len2);
	len = 1;
	//要用FFT，将len扩充为2的整数次幂
	while(len < (mlen << 1))
		len <<= 1;
	//初始化多项式的系数
	for(int i = 0; i < len1; ++i)
		A[i].setValue(str1[len1 - i - 1] - '0',0.0);
	for(int i = 0; i < len2; ++i)
		B[i].setValue(str2[len2 - i - 1] - '0',0.0);
	//补0
	for(int i = len1; i < len; ++i)
		A[i].setValue();
	for(int i = len2; i < len; ++i)
		B[i].setValue();
}

void Rader(Complex y[]){
	for(int i = 1, j = len >>1, k; i < len - 1; ++i){
		if(i < j)
			Swap(y[i], y[j]);
		k = len >> 1;
		while(j >= k){
			j -=k;
			k >>= 1;
		}
		if(j < k)
			j +=k;
	}
}//雷德算法，位逆序置换

void FFT(Complex y[],int op){
	//先位逆序置换
	Rader(y);
	//h为每次要处理的长度,h=1时不需要处理
	for(int h=2; h <= len; h <<= 1){
		//Wn = e^(2 * PI / n)
		Complex Wn(cos(op * 2 * PI / h), sin(op * 2 * PI / h));
		for(int i = 0; i < len; i += h){
			//旋转因子，初始化为e^0
			Complex W(1,0);
			for(int j = i; j < i + h / 2; ++j){
				Complex u = y[j];
				Complex t = W * y[j + h / 2];
				//蝴蝶操作
				y[j] = u + t;
				y[j + h / 2] = u - t;
				//更新旋转因子
				W = W * Wn;
			}
		}
	}
	//插值的时候要除以len
	if(op == -1){
		for(int i = 0; i < len; ++i)
			y[i].real /= len;
	}
}//op为1:DFT,op为-1:IDFT

void Convolution(Complex *A, Complex *B, int *res){
	//evaluation
	FFT(A, 1),FFT(B, 1);
	for(int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	//interpolation
	FFT(A, -1);
	for(int i = 0; i < len; ++i)
		res[i] = (int)(A[i].real + 0.5);
}//卷积求A*B,结果放置在res中

void Adjust(int *res){
	for(int i = 0; i < len; ++i){
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//去除多余的0
	while(res[len] == 0)
		len--;
	len++;
}

void Mul(char *leftVal, char *rightVal, int *resBuf){
	Complex A[MAX1],B[MAX1];
	Prepare(leftVal,rightVal,A,B);
	Convolution(A, B,resBuf);
	Adjust(resBuf);
}
void Big_Mul(char *leftVal, char *rightVal, char *res){
	int resBuf[MAX];
	if((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <='9')){
		Mul(leftVal, rightVal, resBuf);
		for(int i = len - 1; i >= 0; --i)
			res[len - i -1] = resBuf[i]+'0';
	}//正常无符号输入
	if((leftVal[0] >= '0' && leftVal[0] <= '9') &&(rightVal[0] == '+' || rightVal[0] == '-')){
		Mul(leftVal, rightVal+1, resBuf);
		if(rightVal[0] == '+')//右式带正号
			for(int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else{				  //右式带负号
			for(int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1]+'0';
			res[0] = '-';
			len++;
		}
	}
	if((rightVal[0] >= '0' && rightVal[0] <= '9') &&(leftVal[0] == '+' || leftVal[0] == '-')){
		Mul(leftVal + 1, rightVal, resBuf);
		if(leftVal[0] == '+')//左式带正号
			for(int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else{	             //左式带负号
			res[0]='-';
			for(int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			len++;
		}
	}
	if((leftVal[0] == '+' && rightVal[0] == '+') ||(leftVal[0] == '-' && rightVal[0] == '-') ){
		Mul(leftVal+1, rightVal+1, resBuf);
		for(int i = len - 1; i >= 0; --i)
			res[len - i - 1] = resBuf[i]+'0';
	}//两式都带正号或者负号
	if((leftVal[0] == '+' && rightVal[0] == '-') ||(leftVal[0] == '-' && rightVal[0] == '+')){
			Mul(leftVal+1, rightVal+1, resBuf);
			res[0]='-';
			for(int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			len++;
	}//两式一正一负
}

