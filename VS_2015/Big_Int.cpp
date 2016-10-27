#include<string.h>
#include<stdio.h>
#include<cmath>
#define MAX 200000
#define MAXN 100000
#define MAX1 10000
#define PI 3.14159265359
#define YES 1
#define NO 0
#define OK 1
#define ERROR 0


////////*****�Ӽ������벿�ֿ�ʼ*******/////////
int maxlen;

void Trans(char *str1, char *str2, int A[MAX], int B[MAX]) {
	int len1, len2;
	len1 = strlen(str1);
	len2 = strlen(str2);
	maxlen = (len1 > len2 ? len1 : len2) + 1;
	for (int i = 0; i < len1; ++i)
		A[i] = str1[len1 - i - 1] - '0';
	for (int i = 0; i < len2; ++i)
		B[i] = str2[len2 - i - 1] - '0';
	//���� 
	for (int i = len1; i < maxlen; ++i)
		A[i] = 0;
	for (int i = len2; i < maxlen; ++i)
		B[i] = 0;
}

void Adjust_Add(int *res) {
	for (int i = 0; i < maxlen; ++i) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//�����ӷ���� 
	while (res[maxlen - 1] == 0)
		maxlen--;
}

void Adjust_Sub(int *res) {
	int borrow = 0;
	for (int i = 0; i < maxlen; ++i) {
		if (res[i] < 0)
			borrow = 1;
		res[i + 1] -= borrow;
		borrow = 0;
		res[i] = (res[i] + 10) % 10;
	}
	//����������� 
	while (res[maxlen - 1] == 0)
		maxlen--;
}

int isLeftBigger(char *str1, char *str2) {
	if (strlen(str1) > strlen(str2))
		return YES;
	else if (strlen(str1) < strlen(str2))
		return NO;
	else {
		if (strcmp(str1, str2) >= 0)
			return YES;
		else
			return NO;
	}
}

void Add(char *leftVal, char *rightVal, int *resBuf) {//�޷��żӷ� 
	int *A = new int[MAX], *B = new int[MAX];
	Trans(leftVal, rightVal, A, B);
	for (int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] + B[i];
	Adjust_Add(resBuf);
}

void Sub(char *leftVal, char *rightVal, int *resBuf) {//�޷��ż��� 
	int *A = new int[MAX], *B = new int[MAX];
	Trans(leftVal, rightVal, A, B);
	for (int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] - B[i];
	Adjust_Sub(resBuf);
}

void Big_Add(char *leftVal, char *rightVal, char *res) {//���������ӷ� 
	int len0;
	len0 = strlen(leftVal) > strlen(rightVal) ? strlen(leftVal) : strlen(rightVal);
	int *resBuf = new int[len0];
	if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <= '9')) {
		//�������߾�Ϊֱ������
		Add(leftVal, rightVal, resBuf);
		for (int i = maxlen - 1; i >= 0; --i)
			res[maxlen - i - 1] = resBuf[i] + '0';
	}
	else if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] == '+' || rightVal[0] == '-')) {
		if (rightVal[0] == '+') {
			//���Ϊֱ���������ұ�Ϊ����+������
			Add(leftVal, rightVal + 1, resBuf);
			for (int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else {				 
			//���Ϊֱ���������ұ�Ϊ��'-'����
			if (isLeftBigger(leftVal, rightVal + 1)) {
				Sub(leftVal, rightVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else {
				Sub(rightVal + 1, leftVal, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;

			}
		}
	}
	else if ((rightVal[0] >= '0' && rightVal[0] <= '9') && (leftVal[0] == '+' || leftVal[0] == '-')) {

		if (leftVal[0] == '+') {
			//���Ϊ����+�����������ұ�Ϊֱ������
			Add(leftVal + 1, rightVal, resBuf);
			for (int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else {	 
			//���Ϊ����-�����������ұ�Ϊֱ������
			if (isLeftBigger(leftVal + 1, rightVal)) {
				Sub(leftVal + 1, rightVal, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else {
				Sub(rightVal, leftVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '+') || (leftVal[0] == '-' && rightVal[0] == '-')) {
		//��������ͬΪ����+����������������ͬΪ��'-'�ĸ���
		Add(leftVal + 1, rightVal + 1, resBuf);
		if (leftVal[0] == '+')
			for (int i = 0; i <= maxlen - 1; ++i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		else {
			for (int i = maxlen; i >= 1; --i)
				res[maxlen - i + 1] = resBuf[i - 1] + '0';
			res[0] = '-';
			maxlen++;
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '-') || (leftVal[0] == '-' && rightVal[0] == '+')) {
		//���Ϊ����+�����������ұ�Ϊ����-���ĸ���
		if (leftVal[0] == '+') {
			if (isLeftBigger(leftVal + 1, rightVal + 1)) {
				Sub(leftVal + 1, rightVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else {
				Sub(rightVal + 1, leftVal + 1, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
		}
		else {	             
			if (isLeftBigger(leftVal + 1, rightVal + 1)) {
				Sub(leftVal + 1, rightVal + 1, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else {
				Sub(rightVal + 1, leftVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
		}
	}
	if (maxlen == 0) {
		res[maxlen] = '0';
		res[maxlen + 1] = '\0';
	}
	else
		res[maxlen] = '\0';
}
/////////*******�Ӽ�������********///////////////////////

////////********�˷����뿪ʼ******///////////////////////
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

void Swap(Complex &a, Complex &b) {
	Complex tmp = a;
	a = b;
	b = tmp;
}//����

int max(int a, int b) {
	return a > b ? a : b;
}

void Prepare(char *str1, char *str2, Complex A[MAX], Complex B[MAX]) {
	int len1, len2, mlen;
	len1 = strlen(str1);
	len2 = strlen(str2);
	mlen = max(len1, len2);
	len = 1;
	//Ҫ��FFT����len����Ϊ2����������
	while (len < (mlen << 1))
		len <<= 1;
	//��ʼ������ʽ��ϵ��
	for (int i = 0; i < len1; ++i)
		A[i].setValue(str1[len1 - i - 1] - '0', 0.0);
	for (int i = 0; i < len2; ++i)
		B[i].setValue(str2[len2 - i - 1] - '0', 0.0);
	//��0
	for (int i = len1; i < len; ++i)
		A[i].setValue();
	for (int i = len2; i < len; ++i)
		B[i].setValue();
}

void Rader(Complex y[]) {
	for (int i = 1, j = len >> 1, k; i < len - 1; ++i) {
		if (i < j)
			Swap(y[i], y[j]);
		k = len >> 1;
		while (j >= k) {
			j -= k;
			k >>= 1;
		}
		if (j < k)
			j += k;
	}
}//�׵��㷨��λ�����û�

void FFT(Complex y[], int op) {
	//��λ�����û�
	Rader(y);
	//hΪÿ��Ҫ����ĳ���,h=1ʱ����Ҫ����
	for (int h = 2; h <= len; h <<= 1) {
		//Wn = e^(2 * PI / n)
		Complex Wn(cos(op * 2 * PI / h), sin(op * 2 * PI / h));
		for (int i = 0; i < len; i += h) {
			//��ת���ӣ���ʼ��Ϊe^0
			Complex W(1, 0);
			for (int j = i; j < i + h / 2; ++j) {
				Complex u = y[j];
				Complex t = W * y[j + h / 2];
				//��������
				y[j] = u + t;
				y[j + h / 2] = u - t;
				//������ת����
				W = W * Wn;
			}
		}
	}
	//��ֵ��ʱ��Ҫ����len
	if (op == -1) {
		for (int i = 0; i < len; ++i)
			y[i].real /= len;
	}
}//opΪ1:DFT,opΪ-1:IDFT

void Convolution(Complex *A, Complex *B, int *res) {
	//evaluation
	FFT(A, 1), FFT(B, 1);
	for (int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	//interpolation
	FFT(A, -1);
	for (int i = 0; i < len; ++i)
		res[i] = (int)(A[i].real + 0.5);
}//�����A*B,���������res��

void Adjust(int *res) {
	for (int i = 0; i < len; ++i) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//ȥ�������0
	while (res[len] == 0 && len != -1)
		len--;
	len++;
}

void Mul(char *leftVal, char *rightVal, int *resBuf) {
	Complex *A = new Complex[MAX1], *B = new Complex[MAX1];
	Prepare(leftVal, rightVal, A, B);
	Convolution(A, B, resBuf);
	Adjust(resBuf);
}

void Big_Mul(char *leftVal, char *rightVal, char *res) {
	int *resBuf = new int[MAX];
	for (int i = 0; i < MAX; i++)
		resBuf[i] = 0;
	if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <= '9')) {
		Mul(leftVal, rightVal, resBuf);
		for (int i = len - 1; i >= 0; --i)
			res[len - i - 1] = resBuf[i] + '0';
	}//�����޷�������
	else if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] == '+' || rightVal[0] == '-')) {
		Mul(leftVal, rightVal + 1, resBuf);
		if (rightVal[0] == '+')//��ʽ������
			for (int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else {				  //��ʽ������
			for (int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			res[0] = '-';
			len++;
		}
	}
	else if ((rightVal[0] >= '0' && rightVal[0] <= '9') && (leftVal[0] == '+' || leftVal[0] == '-')) {
		Mul(leftVal + 1, rightVal, resBuf);
		if (leftVal[0] == '+')//��ʽ������
			for (int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else {	             //��ʽ������
			res[0] = '-';
			for (int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			len++;
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '+') || (leftVal[0] == '-' && rightVal[0] == '-')) {
		Mul(leftVal + 1, rightVal + 1, resBuf);
		for (int i = len - 1; i >= 0; --i)
			res[len - i - 1] = resBuf[i] + '0';
	}//��ʽ�������Ż��߸���
	else if ((leftVal[0] == '+' && rightVal[0] == '-') || (leftVal[0] == '-' && rightVal[0] == '+')) {
		Mul(leftVal + 1, rightVal + 1, resBuf);
		res[0] = '-';
		for (int i = len; i >= 1; --i)
			res[len - i + 1] = resBuf[i - 1] + '0';
		len++;
	}//��ʽһ��һ��
	if (len == 0) {
		res[len] = '0';
		res[len + 1] = '\0';
	}
	else
		res[len] = '\0';
}
////////////******�˷�����********///////////////////////////////

///////////*******�������뿪ʼ****///////////////////////////////
void mul(char *Val, char *res, int x) {//xΪһλ��������������л�ȡ�� 
	int len0 = strlen(Val) + 1;
	int *tmp = new int[len0];
	tmp[len0 - 1] = 0;
	int i;
	for (i = 0; i < len0 - 1; i++) {
		tmp[len0 - i - 2] = (Val[i] - '0') * x;
	}
	for (i = 0; i < len0 - 1; i++) {
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	if (tmp[len0 - 1] == 0)
		len0--;
	for (i = 0; i < len0; i++)
		res[i] = tmp[len0 - i - 1] + '0';
	res[i] = '\0';
}

void Div(char *leftVal, char *rightVal, int &res, char *extra) {//������ֻ�ȳ�����һλ������� ����ֻ��һλ 
	int len1;
	len1 = strlen(leftVal);
	char *tmp = new char[len1];
	int *array = new int[len1];
	res = 1;
	if (!isLeftBigger(leftVal, rightVal)) {
		res = 0;
		int i = 0;
		while (leftVal[i] != '\0')
		{
			extra[i] = leftVal[i];
			i++;
		}
	}
	else if (strcmp(leftVal, rightVal) == 0) {
		res = 1;
		extra[0] = '0', extra[1] = '\0';
	}
	else {
		while (res <= 9) {
			mul(rightVal, tmp, res);
			if (isLeftBigger(leftVal, tmp)) {
				res++;
			}
			else {
				res--;
				break;
			}
		}
		if (res == 10)
			res--;
		mul(rightVal, tmp, res);
		Sub(leftVal, tmp, array);
		for (int i = maxlen - 1; i >= 0; --i)
			extra[maxlen - i - 1] = array[i] + '0';
		extra[maxlen] = '\0';
	}
}

int Big_Div(char *leftVal, char *rightVal, char *res, char *extra) {//ģ����ʽ�������� 
	int len1, len2, c, i;
	len1 = strlen(leftVal), len2 = strlen(rightVal);
	if (len2 == 1 && rightVal[0] == '0') {
		printf("INPUT ERROR\n");
		return 0;
	}
	else if (len1 == 1 && leftVal[0] == '0') {
		res[0] = '0';
		res[1] = '\0';
		extra[0] = '0';
		extra[1] = '\0';
	}
	else if (len1 < len2) {
		res[0] = '0';
		res[1] = '\0';
		int i=0; 
		while (leftVal[i]!='\0')
		{
			extra[i] = leftVal[i];
			i++;
		}
	}
	else if (len1 == len2) {
		Div(leftVal, rightVal, c, extra);
		res[0] = c + '0';
	}
	else {
		int now = 0;
		int j = 1;
		for (; now < len2; now++)
			extra[now] = leftVal[now];
		extra[now] = '\0';
		Div(extra, rightVal, c, extra);
		res[0] = '0' + c;
		while (leftVal[now] != '\0') {
			int len3 = strlen(extra);
			extra[len3] = leftVal[now];
			extra[len3 + 1] = '\0';
			Div(extra, rightVal, c, extra);
			res[j] = '0' + c;
			j++;
			now++;
		}
		res[j] = '\0';
		//strcpy_s(extra, sizeof(tmp), tmp);//	extra = tmp;
		now = 0, j = 0;
		while (res[now] != '\0' && res[now] == '0')
			now++;
		for (j = now, i = 0; res[j] != '\0'; j++, i++)
			res[i] = res[j];
		res[i] = '\0';
	}
	if (extra[0] == '\0') 
	{
		extra[0] = '0';
		extra[1] = '\0';
	}
	return OK;

}
//////////********��������******///////////////////////////////

using namespace std;
char str1[MAXN], str2[MAXN], res[MAX],extra[MAXN];;//��ǰ�����ڴ� 

int Inspect(char *s) {//�������� 
	int i = 0;
	if (s[i] == '\0') {
		printf("INPUT ERROR\n");
		return ERROR;
	}//�ǿ��ַ���
	if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '+' || s[i] == '-')) {
		printf("INPUT ERROR\n");
		return ERROR;
	}//��һ���ַ���Ϊ0~9����'+'��'-'
	i++;//֮�����Ϊ0~9
	while (s[i] != '\0') {
		if (!(s[i] >= '0' && s[i] <= '9')) {
			printf("INPUT ERROR\n");
			return ERROR;
		}
		i++;
	}
	return OK;
}

int InspectOp(char *op) {//�������� 
	if ((op[0] == '+' || op[0]== '-' || op[0] == '*' || op[0] == '/') && op[1] == '\0') {

		return OK;
	}
	else {
		printf_s("INPUT ERROR\n");
		return ERROR;
	}
}

int main() {
	char op[100];
	char tmp[MAX];
	while (gets_s(str1)!= NULL
	&&gets_s(str2)!= NULL
	&&gets_s(op)!= NULL
	)
	{
		res[0] = '\0';
		extra[0] = '\0';
		if (Inspect(str1) && Inspect(str2) && InspectOp(op)) {
			switch (op[0]) {//���ݲ��������� 
			case '+':
				Big_Add(str1, str2, res);
				printf("%s\n", res);
				break;

			case '-':
				if (str2[0] == '+') {
					str2[0] = '-';
					Big_Add(str1, str2, res);
				}
				else if (str2[0] == '-') {
					str2[0] = '+';
					Big_Add(str1, str2, res);
				}
				else {
					strcpy_s(tmp + 1, sizeof(str2), str2);
					tmp[0] = '-';
					Big_Add(str1, tmp, res);
				}
				printf("%s\n", res);
				break;

			case '*':
				Big_Mul(str1, str2, res);
				printf("%s\n", res);
				break;

			case '/':
				if (Big_Div(str1, str2, res, extra))
				{
					printf("%s ", res);
					printf("%s\n", extra);
				}
				break;

			}

		}
		else
			continue;
	}
}
