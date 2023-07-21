//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

//////////////////////////////////////////////////////////////
//
//			Some common functions
//
//////////////////////////////////////////////////////////////
digitList *digitize(char str[80])
{
	digitList*	L = 0;
	digitList*	node;
	int i;
	int n = 0;
	Integer L1, L2;
	for(i = 0; i< strlen(str); i++)
	{
		if(str[i] < '0' || str[i] > '9') break;

		node = new digitList(str[i] - '0', L);
		L = node;
	}
	if (str[i] == '^')
	{
		L1 = Integer(L);
		L2 = L1;
		i = i+1;
		for(; i< strlen(str); i++)
		{
			if(str[i] < '0' || str[i] > '9') break;
			n = n*10 + str[i] - '0';
		}
		for (int i = 1; i < n; i++)
		{
			L2 = L2 * L1;
		}	
		return L2.digits;
	}
	if (str[i] == '!')
	{
		L1 = Integer(L);
		L2 = L1;
		for (int i = 1; compareDigitLists(L1.digits,digitize(1)) == 1; i++)
		{
			L2 = L2* Integer(digitize(i));
			L1 = L1 - Integer(digitize(1));
		}	
		return L2.digits;
	}
	return L;
}
digitList* trimDigitList(digitList* L)
{
	if (L == NULL)
		return L;

	digitList* current = L;
	digitList* testzero = nullptr;

	while (current != NULL) {
		if (current->getDigit() != 0) {
			testzero = NULL;
		}
		if (testzero == NULL) {
			testzero = current;
		}
		current = current->getNextDigit();
	}

	if (testzero != NULL) {
		testzero->nextDigit=NULL;
	}

	return L;
}


digitList *subDigitLists(int b, digitList* L1, digitList* L2)
{
	if((L1 == NULL) && (L2 == NULL))	return 0;
	else if(L1 == NULL)					return L2;
	else if(L2 == NULL)					return L1;
	else
	{
		if (compareDigitLists(L1,L2)==0)
		{
			return digitize(0);
		}else if (compareDigitLists(L1,L2) == -1)
		{
			digitList* head1 = L1;
			digitList* head2 = L2;
			int t;
			while (head1!=NULL)
			{
				t = -b + head2->getDigit() - head1->getDigit();
				if (t >= 0)
				{
					b = 0;
					head2->digit = t;
				}else{
					b = 1;
					head2->digit = t + 10;
				}
				head1 = head1->nextDigit;
				head2 = head2->nextDigit;
			}
			while(head2!=NULL){
				t = -b + head2->getDigit();
				if (t >= 0)
				{
					b = 0;
					head2->digit = t;
				}else{
					b = 1;
					head2->digit = t + 10;
				}				
				head2 = head2->nextDigit;
			}
			return trimDigitList(L2);
		}else{
			digitList* head1 = L1;
			digitList* head2 = L2;
			int t;
			while (head2 != NULL)
			{
				t = -b + head1->getDigit() - head2->getDigit();
				if (t >= 0)
				{
					b = 0;
					head1->digit = t;
				}else{
					b = 1;
					head1->digit = t + 10;
				}
				head1 = head1->nextDigit;
				head2 = head2->nextDigit;
			}
			while(head1!=NULL){
			t = -b + head1->getDigit();
				if (t >= 0)
				{
					b = 0;
					head1->digit = t;
				}else{
					b = 1;
					head1->digit = t + 10;
				}				
				head1 = head1->nextDigit;
			}
			return trimDigitList(L1);
		}
	}
}

Integer computeValue(int operatorNum)
{
	Integer		L1, L2;
	L1 = operandArr[0];
	
	for(int i = 0; i<operatorNum; i++)
	{
		L2 = operandArr[i+1];
		switch(operatorArr[i])
		{
		case '+':
			L1 = L1 + L2;
			break;
		case '-':
			L1 = L1 - L2;
			break;
		case '*':
			L1 = L1 * L2;
			break;
		}
	}
	
	return L1;
}
///////////////////////////////////////////////////////////////////////////
//
//		Some methods of Integer class
//
////////////////////////////////////////////////////////////////////
Integer Integer::operator +(Integer L)
{
	if(sign == L.sign)
		return Integer(sign, addDigitLists(0, digits, L.digits));
	else if (sign != L.sign){
		if (sign == -1 && L.sign == 1)
		{
			if (compareDigitLists(digits, L.digits) == 1)
			{
				return Integer(-1, subDigitLists(0, digits, L.digits));
			}else if (compareDigitLists(digits, L.digits) == -1)
			{
				return Integer(1, subDigitLists(0, digits, L.digits));
			}else if (compareDigitLists(digits,L.digits)==0)
			{
				return Integer(1,digitize(0));
			}			
		}else if (sign == 1 && L.sign == -1)
		{
			if (compareDigitLists(digits, L.digits) == 1)
			{
				return Integer(1, subDigitLists(0, digits, L.digits));
			}else if (compareDigitLists(digits, L.digits) == -1)
			{
				return Integer(-1, subDigitLists(0, digits, L.digits));
			}else if (compareDigitLists(digits,L.digits)==0)
			{
				return Integer(1,digitize(0));
			}		
		}
	}
	return Integer(0, digitize(0));
}

Integer Integer::operator -(Integer L)
{
	if (sign == L.sign)
	{
		if (sign == -1)
		{
			return Integer(-1, addDigitLists(0,digits, L.digits));	
		}else if(sign == 1){
			if (compareDigitLists(digits,L.digits)==1)
			{
				return Integer(1, subDigitLists(0,digits, L.digits));
			}else if (compareDigitLists(digits,L.digits)==-1)
			{
				return Integer(-1, subDigitLists(0,digits, L.digits));
			}else if (compareDigitLists(digits,L.digits)==0)
			{
				return Integer(1,digitize(0));
			}			
		}
	}else if (sign != L.sign){
		if(sign == 1 && L.sign == -1){
			return Integer(1, addDigitLists(0,digits, L.digits));
		}else if (sign == -1 && L.sign == 1){
			return Integer(-1, addDigitLists(0,digits, L.digits));
		}	
	}
	return Integer(0, digitize(0));
}

Integer Integer::leftDigits(int n)
{
	return Integer(sign,digits->leftDigits(n));
}

Integer Integer::rightDigits(int n)
{
	return Integer(sign, digits->rightDigits(n));
}

Integer	Integer::shift(int n)
{
	if (n == 0) return Integer(sign, digits);
	else{
		while (n--)
		{	
			digitList* newNode = new digitList;
			newNode->digit = 0;
			newNode->nextDigit = digits;
			digits = newNode;
		}
		return Integer(sign, digits);
	}	
	return Integer();
}

Integer Integer::operator *(Integer Y)
{
	if (this->digits->length() > Y.digits->length())
	{
		int a = this->digits->length() - Y.digits->length();
		while (a--)
		{
			digitList* headY = Y.digits;
			digitList* newNode = new digitList;
			newNode->digit = 0;
			while(headY->nextDigit!=NULL){
				headY = headY->nextDigit;
			}
			headY->nextDigit = newNode;
		}	
	}else if(this->digits->length() < Y.digits->length()){
		int a = Y.digits->length()- this->digits->length();
		while (a--)
		{
			digitList* headX = this->digits;
			digitList* newNode = new digitList;
			newNode->digit = 0;
			while(headX->nextDigit!=NULL){
				headX = headX->nextDigit;
			}
			headX->nextDigit = newNode;
		}
	}
	if (Y.digits == NULL || digits == NULL)
	{
		return Integer(sign, digitize(0));
	}	
	else if (this->digits->length() >= 2)
	{		
		int L = this->digits->length();
		int n = L/2;
		Integer Xleft = this->leftDigits(n),
				Xright = this->rightDigits(L-n),
				Yleft = Y.leftDigits(n),
				Yright = Y.rightDigits(L-n),
				res = Xleft*Yleft + ((Xright * Yleft) + (Xleft * Yright)).shift(n)
						+ (Xright * Yright).shift(2*n);
		if (this->sign != Y.sign)
		{
			res.sign = -1;
		}else res.sign =1;
		
		return res.trimDigit();
	}else{
		if (digits->getDigit()*Y.digits->getDigit() == 0)
		{
			return Integer(1, digitize(0));
		}else{
			if (this->sign != Y.sign)
			{
				return Integer(-1,digitize(digits->getDigit()*Y.digits->getDigit()));
			}else return Integer(1,digitize(digits->getDigit()*Y.digits->getDigit()));
			
		}	
	}
	return Integer();
}
