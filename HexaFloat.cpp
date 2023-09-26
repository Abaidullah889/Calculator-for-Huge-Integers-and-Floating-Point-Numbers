#include "Bscs22133HexaFloat.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

HexaFloat::HexaFloat()
{
	this->base = 0;
	this->isneg = false;
	this->Vs = nullptr;
	this->size = 0;
	this->p_ind = 0;

}
HexaFloat::HexaFloat(int size)
{
	this->base = 0;
	this->isneg = false;
	this->Vs = new int[size];
	this->size = size;
	this->p_ind = 0;
}
HexaFloat::HexaFloat(const HexaFloat& S)
{
	this->Assign(S);
}
HexaFloat::HexaFloat(ifstream& rdr)
{
	this->Load(rdr);
}
void HexaFloat::Assign(const HexaFloat& S)
{
	int* Ns = new int[S.size];
	for (int i = 0; i < S.size; i++)
	{
		Ns[i] = S.Vs[i];
	}
	delete[]this->Vs;
	this->Vs = Ns;
	this->size = S.size;
	this->isneg = S.isneg;
	this->p_ind = S.p_ind;
	this->base = S.base;
}
void HexaFloat::Load(ifstream& rdr)
{
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	char s;
	s = rdr.peek();
	if (s == '-')
	{
		this->isneg = true;
		rdr.ignore();
	}
	else
	{
		this->isneg = false;
	}
	string l;
	getline(rdr, l);
	this->GetFloat(l);

}
void HexaFloat::Print()
{
	cout << ((isneg == true) ? '-' : '+');
	for (int i = 0; i < this->size; i++)
	{
		if (i == this->p_ind)
		{
			cout << '.';
		}
		if (this->Vs[this->size - i - 1] >= 0 && this->Vs[this->size - i - 1] <= 9)
		{
			cout << this->Vs[this->size-i-1];
		}
		else
		{
			char c = this->Vs[this->size - i - 1] + 55;
			cout << c;
		}
	}
}
void HexaFloat::GetFloat(string l)
{
	this->Vs = nullptr;
	this->size = l.size() - 1;
	this->Vs = new int[this->size];
	int index = 0;


	for (int i = l.size() - 1; i >= 0; i--)
	{
		if (l[i] == '.')
		{
			this->p_ind = i;
		}
		if (l[i] != '.')
		{
			int n = l[i];
			if (n >= 48 && n <= 57)
			{
				this->Vs[index] = n - '0';
				index++;
			}
			else
			{
				this->Vs[index] = n - 55;
				index++;
			}
		}
	}
}
void HexaFloat::Setbase(int n)
{
	this->base = n;
}
const HexaFloat& HexaFloat::operator=(const HexaFloat& S)
{
	this->Assign(S);
	return *this;
}
int HexaFloat::operator[](int i) const
{
	if (i >= this->size)
	{
		return 0;
	}
	else
	{
		return this->Vs[i];
	}
}
int& HexaFloat::operator[](int i)
{
	if (i >= this->size)
	{
		int t = 0;
		return t;
	}
	else
	{
		return this->Vs[i];
	}
}


const HexaFloat HexaFloat::add(const HexaFloat& S)const
{

	if (this->p_ind == 0 && S.p_ind == 0)
	{
		HexaFloat P(this->size + 1);
		int carry = 0;
		int ans = 0;
		for (int i = 0; i < P.size; i++)
		{
			ans = ((*this)[i] + S[i] + carry) % this->base;
			carry = ((*this)[i] + S[i] + carry) / this->base;

			P[i] = ans;
		}
		P.Trim();
		P.base = this->base;
		return P;
	}



	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	if (bef_deci1 < bef_deci2)
	{
		TD.AddZero(bef_deci2 - bef_deci1);
	}
	else
	{
		SD.AddZero(bef_deci1 - bef_deci2);
	}

	int k = max(TD.size, SD.size);
	HexaFloat P(k + 1);
	int carry = 0;
	int ans = 0;
	for (int i = 0; i < P.size; i++)
	{
		ans = ((TD)[i] + SD[i] + carry) % this->base;
		carry = ((TD)[i] + SD[i] + carry) / this->base;
		P[i] = ans;
	}
	int ind = P.size - max(bef_deci1, bef_deci2);
	P.p_ind = ind;
	P.Trim();
	P.base = this->base;
	return P;


}
const HexaFloat HexaFloat::sub(const HexaFloat& S)const
{
	if (this->p_ind == 0 && S.p_ind == 0)
	{
		int count = 0;
		HexaFloat P(this->size);
		int ans = 0;
		int carry = 0;
		for (int i = 0; i < P.size; i++)
		{
			ans = ((*this)[i] - S[i] - carry) % this->base;
			carry = ((ans < 0) ? 1 : 0);
			ans = ((ans < 0) ? ans + this->base : ans);
			P[i] = ans;
		}
		P.p_ind = 0;
		P.Trim();
		P.base = this->base;
		return P;
	}



	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	if (bef_deci1 < bef_deci2)
	{
		TD.AddZero(bef_deci2 - bef_deci1);
	}
	else
	{
		SD.AddZero(bef_deci1 - bef_deci2);
	}

	int k = max(TD.size, SD.size);
	HexaFloat P(k);
	int carry = 0;
	int ans = 0;
	int ccount = 0;
	for (int i = 0; i < P.size; i++)
	{
		/*if (carry == 1)
		{
			ccount--;
		}*/
		ans = ((TD)[i] - SD[i] - carry) % this->base;
		/*if (ans < 0 && ccount<=0)
		{*/
		carry = ((ans < 0) ? 1 : 0);
		ccount++;
		/*}*/
		ans = ((ans < 0) ? ans + this->base : ans);
		P[i] = ans;
	}
	int ind = P.size - max(bef_deci1, bef_deci2);
	P.p_ind = ind;
	P.base = this->base;
	P.Trim();

	return P;
}
bool HexaFloat::LessThanQuantityWise(const HexaFloat& S) const
{
	if (this->p_ind == 0 && S.p_ind == 0)
	{
		if (this->size > S.size)
		{
			return false;
		}
		else if (this->size < S.size)
		{
			return true;
		}
		for (int i = 0; i < this->size; i++)
		{
			if (this->Vs[this->size - i - 1] > S.Vs[this->size - i - 1])
			{
				return false;
			}
			if (this->Vs[this->size - i - 1] < S.Vs[this->size - i - 1])
			{
				return true;
			}
		}
		return false;
	}


	if (this->p_ind < S.p_ind)
	{
		return true;
	}
	else if (this->p_ind > S.p_ind)
	{
		return false;
	}
	int n = max(this->size, S.size);
	for (int i = 0; i < this->p_ind; i++)//Integer Part Checking
	{

		if ((*this)[this->size - i - 1] > S[S.size - i - 1])
		{
			return false;
		}
		if ((*this)[this->size - i - 1] < S[S.size - i - 1])
		{
			return true;
		}
	}
	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	if (bef_deci1 < bef_deci2)
	{
		TD.AddZero(bef_deci2 - bef_deci1);
	}
	else
	{
		SD.AddZero(bef_deci1 - bef_deci2);
	}

	for (int i = n - this->p_ind - 1; i >= 0; i--) // Decimal Part Checking
	{
		if ((TD)[i] > SD[i])
		{
			return false;
		}
		if ((TD)[i] < SD[i])
		{
			return true;
		}
	} // 
	return false;
}
bool HexaFloat::GreaterThanQuantityWise(const HexaFloat& S) const
{
	return S.LessThanQuantityWise(*this);
}
bool HexaFloat::EqualQuantityWise(const HexaFloat& S) const
{
	return (!(*this).LessThanQuantityWise(S) && !(*this).GreaterThanQuantityWise(S));
}


const HexaFloat HexaFloat::operator!()const
{
	HexaFloat R = (*this);
	R.isneg = !(this->isneg);
	return R;
}
const HexaFloat HexaFloat::operator+(const HexaFloat& S)const
{
	/*if (this->isneg != S.isneg)
	{
		if (this->size == S.size)
		{
			int count = 0;
			for (int i = 0; i < this->size; i++)
			{

				if (this->Vs[i] != S.Vs[i])
				{
					break;
				}
				count++;
				if (count == this->size)
				{
					HugeFloat R = Zero();
					return R;
				}
			}
		}
	}
	if (this->isneg == S.isneg)
	{
		int bef_deci1 = 0;
		int bef_deci2 = 0;
		bef_deci1 = this->BeforeDecimal();
		bef_deci2 = S.BeforeDecimal();

		if (this->GreaterThanQuantityWise(S))
		{
			if(bef_deci2<bef_deci1)
			{
				HugeFloat D = S;
				int n = bef_deci1 - bef_deci2;
				D.AddZero(n);
				HugeFloat R = this->add(D);
				R.p_ind = this->p_ind+1;
				R.isneg = this->isneg;
				return R;
			}
			if (bef_deci1 < bef_deci2)
			{
				HugeFloat D = *this;
				int n = bef_deci2 - bef_deci1;
				D.AddZero(n);
				HugeFloat R = S.add(D);
				R.isneg = S.isneg;
				R.p_ind = S.p_ind + 1;
				return R;
			}
			else
			{
				HugeFloat R = this->add(S);
				R.isneg = S.isneg;
				return R;
			}

		}
		else
		{
			if (bef_deci1 < bef_deci2)
			{
				HugeFloat D = *this;
				int n = bef_deci2 - bef_deci1;
				D.AddZero(n);
				HugeFloat R = S.add(D);
				R.isneg = S.isneg;
				R.p_ind = S.p_ind+1;
				return R;
			}
			if (bef_deci2 < bef_deci1)
			{
				HugeFloat D = S;
				int n = bef_deci1 - bef_deci2;
				D.AddZero(n);
				HugeFloat R = D.add(*this);
				R.p_ind = S.p_ind+1;
				R.isneg = S.isneg;
				return R;
			}
			else
			{
				HugeFloat R = S.add(*this);
				R.isneg = S.isneg;
				return R;
			}
		}
	}
	else
	{
		int bef_deci1 = 0;
		int bef_deci2 = 0;
		bef_deci1 = this->BeforeDecimal();
		bef_deci2 = S.BeforeDecimal();

		if (this->GreaterThanQuantityWise(S))
		{
			if (bef_deci2 < bef_deci1)
			{
				HugeFloat D = S;
				int n = bef_deci1 - bef_deci2;
				D.AddZero(n);
				HugeFloat R = this->sub(D);
				R.p_ind = this->p_ind;
				R.isneg = this->isneg;
				return R;
			}
			else
			{
				HugeFloat R = this->sub(S);
				R.isneg = this->isneg;
				return R;
			}
		}
		else
		{
			if (bef_deci2 < bef_deci1)
			{
				HugeFloat D = S;
				int n = bef_deci1 - bef_deci2;
				D.AddZero(n);
				HugeFloat R = D.sub(*this);
				R.p_ind = S.p_ind;
				R.isneg = S.isneg;
				return R;
			}
			else if (bef_deci1 < bef_deci2)
			{
				HugeFloat D = *this;
				int n = bef_deci2 - bef_deci1;
				D.AddZero(n);
				HugeFloat R = S.sub(D);
				R.isneg = S.isneg;
				R.p_ind = this->p_ind;
				return R;
			}
			else
			{
				HugeFloat R = S.sub(*this);
				R.isneg = S.isneg;
				return R;
			}

		}
	}*/
	if (this->isneg != S.isneg)
	{
		if (this->size == S.size)
		{
			int count = 0;
			for (int i = 0; i < this->size; i++)
			{

				if (this->Vs[i] != S.Vs[i])
				{
					break;
				}
				count++;
				if (count == this->size)
				{
					HexaFloat R = Zero(this->base);
					return R;
				}
			}
		}
	}

	if (this->isneg == S.isneg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaFloat R = this->add(S);
			R.isneg = this->isneg;
			return R;
		}
		else
		{
			HexaFloat R = S.add(*this);
			R.isneg = S.isneg;
			return R;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaFloat R = this->sub(S);
			R.isneg = this->isneg;
			return R;
		}
		else
		{
			HexaFloat R = S.sub(*this);
			R.isneg = S.isneg;
			return R;
		}
	}



}
const HexaFloat& HexaFloat::operator+=(const HexaFloat& S)
{
	if (this->isneg != S.isneg)
	{
		if (this->size == S.size)
		{
			int count = 0;
			for (int i = 0; i < this->size; i++)
			{

				if (this->Vs[i] != S.Vs[i])
				{
					break;
				}
				count++;
				if (count == this->size)
				{
					HexaFloat R = Zero(this->base);
					return R;
				}
			}
		}
	}

	if (this->isneg == S.isneg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaFloat R = this->add(S);
			R.isneg = this->isneg;
			*this = R;
			return *this;
		}
		else
		{
			HexaFloat R = S.add(*this);
			R.isneg = S.isneg;
			*this = R;
			return *this;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaFloat R = this->sub(S);
			R.isneg = this->isneg;
			*this = R;
			return *this;
		}
		else
		{
			HexaFloat R = S.sub(*this);
			R.isneg = S.isneg;
			*this = R;
			return *this;
		}
	}
}
const HexaFloat HexaFloat::operator-(const HexaFloat& S)const
{
	return (*this) + (!S);
}
const HexaFloat& HexaFloat::operator-=(const HexaFloat& S)
{
	HexaFloat R;
	R= (*this) + (!S);
	*this = R;
	return *this;
}


bool HexaFloat::operator>(const  HexaFloat& S)const
{

	if (this->isneg != S.isneg)
	{
		return this->isneg == false;
	}
	else if (this->isneg == true)
	{
		return this->LessThanQuantityWise(S);
	}
	else
	{
		return this->GreaterThanQuantityWise(S);
	}

}
bool HexaFloat::operator>=(const HexaFloat& S)const
{
	if ((*this > S) || (*this == S))
	{
		return true;
	}
	return false;
}
bool HexaFloat::operator<(const  HexaFloat& S)const
{
	return S > (*this);
}
bool HexaFloat::operator<=(const HexaFloat& S)const
{
	if (this->p_ind == 0 && S.p_ind == 0)
	{
		if (this->size > S.size)
		{
			return false;
		}
		else if (this->size < S.size)
		{
			return true;
		}
		for (int i = 0; i < this->size; i++)
		{
			if (this->Vs[this->size - i - 1] > S.Vs[this->size - i - 1])
			{
				return false;
			}
			if (this->Vs[this->size - i - 1] < S.Vs[this->size - i - 1])
			{
				return true;
			}
		}
		return false;
	}

	if ((*this < S) || (*this == S))
	{
		return true;
	}
	return false;
}
bool HexaFloat::operator==(const HexaFloat& S)const
{

	return (!(*this < S) && !(*this > S));
}
bool HexaFloat::operator!=(const HexaFloat I)const
{
	if (this->p_ind == 0)
	{
		if (this->size > 1)
		{
			return true;
		}
		if (this->Vs[0] == 0)
		{
			return false;
		}
		return true;
	}

	if (*this == I)
	{
		return false;
	}
	return true;
}


ostream& operator<<(ostream& cout, const HexaFloat& H)
{
	cout << ((H.isneg == true) ? '-' : '+');
	for (int i = 0; i < H.size; i++)
	{
		if (i == H.p_ind)
		{
			cout << '.';
		}
		if (H.Vs[H.size - i - 1] >= 0 && H.Vs[H.size - i - 1] <= 9)
		{
			cout << H.Vs[H.size - i - 1];
		}
		else
		{
			char c = H.Vs[H.size - i - 1] + 55;
			cout << c;
		}
	}
	return cout;
}
ostream& HexaFloat::operator<< (ostream& cout)
{
	cout << ((isneg == true) ? '-' : '+');
	for (int i = 0; i < this->size; i++)
	{
		if (i == this->p_ind)
		{
			cout << '.';
		}
		if (this->Vs[this->size - i - 1] >= 0 && this->Vs[this->size - i - 1] <= 9)
		{
			cout << this->Vs[this->size - i - 1];
		}
		else
		{
			char c = this->Vs[this->size - i - 1] + 55;
			cout << c;
		}
	}
	return cout;
}
ifstream& operator>>(ifstream& rdr, HexaFloat& H)
{
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	char s;
	s = rdr.peek();
	if (s == '-')
	{
		H.isneg = true;
		rdr.ignore();
	}
	else
	{
		H.isneg = false;
	}
	string l;
	getline(rdr, l);
	H.GetFloat(l);

	return rdr;
}
ifstream& HexaFloat::operator>>(ifstream& rdr)
{
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	char s;
	s = rdr.peek();
	if (s == '-')
	{
		this->isneg = true;
		rdr.ignore();
	}
	else
	{
		this->isneg = false;
	}
	string l;
	getline(rdr, l);
	this->GetFloat(l);

	return rdr;
}
istream& operator>>(istream& in, HexaFloat& H)
{
	int base = 0;
	cout << "Enter the Base: ";
	cin >> base;
	int size = 0;
	bool isneg = false;
	char l;
	string c;
	cin >> c;

	if (c[0] == '-')
	{
		size = c.size() - 2;
		isneg = true;
	}
	else
	{
		size = c.size() - 1;
		isneg = false;
	}
	HexaFloat R(size);
	R.base = base;
	for (int i = 0, j = 0; i < c.size(); i++)
	{
		if (c[i] != '-' && c[i] != '.')
		{
			int n = c[i];
			if (n >= 48 && n <= 57)
			{
				R.Vs[R.size-j-1] = n - 48;
				j++;
			}
			else
			{
				R.Vs[R.size - j - 1] = n - 55;
				j++;
			}

			/*int n = c[i] - '0';
			R.Vs[R.size - j - 1] = n;
			j++;*/
		}
		else if (c[i] == '.' || c[i] == '-')
		{
			if (c[i] == '.')
			{
				R.p_ind = j;
			}
			else
			{
				continue;
			}

			
		}
	}
	H = R;
	H.isneg = isneg;
	return cin;
}

const HexaFloat HexaFloat::operator++(int d)
{
	HexaFloat R = (*this);
	(*this) = (*this) + One(this->base);
	return R;
}
HexaFloat& HexaFloat::operator++()
{
	HexaFloat P = One(this->base);
	(*this) = (*this) + P;
	return (*this);
}
const HexaFloat HexaFloat::operator--(int d)
{
	HexaFloat R = (*this);
	(*this) = (*this) - One(this->base);
	return R;
}
HexaFloat& HexaFloat::operator--()
{
	HexaFloat P = One(this->base);
	(*this) = (*this) + P;
	return (*this);
}


const HexaFloat HexaFloat::operator*(const HexaFloat& S)const
{
	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	HexaFloat R;
	HexaFloat I;
	HexaFloat A = *this;
	A.Trim();
	A.isneg = false;
	A.p_ind = 0;
	HexaFloat B = S;
	B.isneg = false;
	B.Trim();
	B.p_ind = 0;
	HexaFloat C = MOne(this->base);
	HexaFloat Ch;
	HexaFloat T;
	while (B != Zero(this->base))
	{
		R = A;
		C = MOne(this->base);
		Ch = C + C;
		Ch.p_ind = 0;
		while (Ch <= B)
		{
			R += R;
			C += C;
			Ch = C + C;
			Ch.p_ind = 0;
		}
		T.p_ind = 0, R.p_ind = 0;
		T = T + R;
		T.p_ind = 0, R.p_ind = 0;
		B.p_ind = 0, C.p_ind = 0;
		B.isneg = false;
		B = B - C;
		B.p_ind = 0;
	}
	I = T;
	if ((*this).isneg != S.isneg)
	{
		I.isneg = true;
	}
	if ((*this).isneg == S.isneg)
	{
		I.isneg = false;
	}
	/*if(this->size-bef_deci1==1)*/

	I.p_ind = I.size - (bef_deci2 + bef_deci1);
	int t = I.p_ind;
	return I;
}
const HexaFloat& HexaFloat::operator*=(const HexaFloat& S)
{
	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	HexaFloat R;
	HexaFloat I;
	HexaFloat A = *this;
	A.Trim();
	A.isneg = false;
	A.p_ind = 0;
	HexaFloat B = S;
	B.isneg = false;
	B.Trim();
	B.p_ind = 0;
	HexaFloat C = MOne(this->base);
	HexaFloat Ch;
	HexaFloat T;
	while (B != Zero(this->base))
	{
		R = A;
		C = MOne(this->base);
		Ch = C + C;
		Ch.p_ind = 0;
		while (Ch <= B)
		{
			R += R;
			C += C;
			Ch = C + C;
			Ch.p_ind = 0;
		}
		T.p_ind = 0, R.p_ind = 0;
		T = T + R;
		T.p_ind = 0, R.p_ind = 0;
		B.p_ind = 0, C.p_ind = 0;
		B.isneg = false;
		B = B - C;
		B.p_ind = 0;
	}
	I = T;
	if ((*this).isneg != S.isneg)
	{
		I.isneg = true;
	}
	if ((*this).isneg == S.isneg)
	{
		I.isneg = false;
	}
	/*if(this->size-bef_deci1==1)*/

	I.p_ind = I.size - (bef_deci2 + bef_deci1);
	int t = I.p_ind;
	*this = I;
	return *this;
}
const HexaFloat HexaFloat::operator/(const HexaFloat& S)const
{
	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();
	int div_precision = 0;
	HexaFloat A;
	HexaFloat B;
	A = *this;
	B = S;
	A.isneg = false;
	B.isneg = false;
	A.Trim();
	B.Trim();
	int precision = 0;
	if (A >= B)
	{
		if (bef_deci1 < bef_deci2)
		{
			B.TrimFromLast();
			int s = S.size - S.p_ind - this->p_ind;
			precision = bef_deci1 + bef_deci2;
			A.MultiplyFloat(precision);
		}
		else
		{
			precision = ((bef_deci1 > bef_deci2) ? bef_deci1 : bef_deci2);
			A.MultiplyFloat(precision);
		}

		if (bef_deci1 < bef_deci2)
		{
			int aft_deci = this->p_ind + bef_deci2 + 1;
			div_precision = aft_deci - S.size;
		}
		else
		{
			if (B.size != S.size)
			{
				int aft_deci = this->p_ind + bef_deci2;
				div_precision = aft_deci - B.size;
			}
			else
			{
				int aft_deci = this->p_ind + bef_deci2 + 1;
				div_precision = aft_deci - S.size;
			}
		}

		B.isneg = false;
		A.isneg = false;
		A.p_ind = 0;
		B.p_ind = 0;
		HexaFloat R;
		HexaFloat l;
		HexaFloat I;
		HexaFloat T;
		HexaFloat C = MOne(this->base);
		HexaFloat Ch;
		while (A != Zero(this->base))
		{
			R = B;
			R.p_ind = 0;

			Ch = R + R;
			Ch.p_ind = 0;
			C = MOne(this->base);
			while (Ch <= A)
			{
				R += R;
				C += C;
				Ch = R + R;
				Ch.p_ind = 0;
				R.p_ind = 0;
				C.p_ind = 0;
			}
			T = T + C;
			T.p_ind = 0;
			A.p_ind = 0, R.p_ind = 0;
			A = A - R;
			A.p_ind = 0;
			if (A < B)
			{
				break;
			}
		}
		I = T;
		I.p_ind = div_precision;
		if ((*this).isneg != S.isneg)
		{
			I.isneg = true;
		}
		if ((*this).isneg == S.isneg)
		{
			I.isneg = false;
		}
		//I.Trim();
		return I;
	}

	else if (A < B)
	{
		HexaFloat I = Zero(this->base);
		return I;
	}
}
const HexaFloat& HexaFloat::operator/=(const HexaFloat& S)
{
	HexaFloat TD = *this;
	HexaFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();
	int div_precision = 0;
	HexaFloat A;
	HexaFloat B;
	A = *this;
	B = S;
	A.isneg = false;
	B.isneg = false;
	A.Trim();
	B.Trim();
	int precision = 0;
	if (A >= B)
	{
		if (bef_deci1 < bef_deci2)
		{
			B.TrimFromLast();
			int s = S.size - S.p_ind - this->p_ind;
			precision = bef_deci1 + bef_deci2;
			A.MultiplyFloat(precision);
		}
		else
		{
			precision = ((bef_deci1 > bef_deci2) ? bef_deci1 : bef_deci2);
			A.MultiplyFloat(precision);
		}

		if (bef_deci1 < bef_deci2)
		{
			int aft_deci = this->p_ind + bef_deci2 + 1;
			div_precision = aft_deci - S.size;
		}
		else
		{
			if (B.size != S.size)
			{
				int aft_deci = this->p_ind + bef_deci2;
				div_precision = aft_deci - B.size;
			}
			else
			{
				int aft_deci = this->p_ind + bef_deci2 + 1;
				div_precision = aft_deci - S.size;
			}
		}

		B.isneg = false;
		A.isneg = false;
		A.p_ind = 0;
		B.p_ind = 0;
		HexaFloat R;
		HexaFloat l;
		HexaFloat I;
		HexaFloat T;
		HexaFloat C = MOne(this->base);
		HexaFloat Ch;
		while (A != Zero(this->base))
		{
			R = B;
			R.p_ind = 0;

			Ch = R + R;
			Ch.p_ind = 0;
			C = MOne(this->base);
			while (Ch <= A)
			{
				R += R;
				C += C;
				Ch = R + R;
				Ch.p_ind = 0;
				R.p_ind = 0;
				C.p_ind = 0;
			}
			T = T + C;
			T.p_ind = 0;
			A.p_ind = 0, R.p_ind = 0;
			A = A - R;
			A.p_ind = 0;
			if (A < B)
			{
				break;
			}
		}
		I = T;
		I.p_ind = div_precision;
		if ((*this).isneg != S.isneg)
		{
			I.isneg = true;
		}
		if ((*this).isneg == S.isneg)
		{
			I.isneg = false;
		}
		//I.Trim();
		*this = I;
		return *this;
	}

	else if (A < B)
	{
		HexaFloat I = Zero(this->base);
		*this = I;
		return *this;
	}
}

void HexaFloat::TrimFromLast()
{
	int zcount = 0;
	for (int i = 0; i < this->size; i++)
	{
		if (this->Vs[i] == 0)
		{
			zcount++;
		}
		if (this->Vs[i] != 0)
		{
			break;
		}
	}
	int* n = new int[this->size - zcount];
	for (int i = zcount, j = 0; i < this->size; i++, j++)
	{
		n[j] = this->Vs[i];
	}
	delete[]this->Vs;
	this->Vs = n;
	this->size = this->size - zcount;
}
void HexaFloat::MultiplyFloat(int s)
{
	HexaFloat N(this->size + s);
	for (int i = 0; i < N.size; i++)
	{
		if (i < s)
		{
			N.Vs[i] = 0;
		}
		else
		{
			N.Vs[i] = this->Vs[i - s];
		}
	}
	N.base = this->base;
	*this = N;
}
HexaFloat HexaFloat::One(int n)
{
	HexaFloat R(4);
	R.Vs[0] = 0;
	R.Vs[1] = 0;
	R.Vs[2] = 0;
	R.Vs[3] = 1;
	R.p_ind = 1;
	R.Setbase(n);
	return R;
}
HexaFloat HexaFloat::MOne(int n)
{
	HexaFloat R(1);
	R.Vs[0] = 1;
	R.p_ind = 0;
	R.Setbase(n);
	return R;
}
HexaFloat HexaFloat::Zero(int n)
{
	HexaFloat R(1);
	R.Vs[0] = 0;
	R.Setbase(n);
	return R;
}
int HexaFloat::BeforeDecimal()const
{
	int count = 0;
	for (int i = 0, j = this->size; i < this->size; i++, j--)
	{
		if (j > this->p_ind)
		{
			count++;
		}
	}
	return count;
}
void HexaFloat::AddZero(int n)
{
	HexaFloat N(this->size + n);

	for (int i = 0; i < N.size; i++)
	{
		if (i < n)
		{
			N.Vs[i] = 0;
		}
		else
		{
			N.Vs[i] = this->Vs[i - n];
		}
	}
	N.base = this->base;
	*this = N;
}
void HexaFloat::Trim()
{
	int zcount = 0;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if (this->Vs[i] == 0)
		{
			zcount++;
		}
		if (this->Vs[i] != 0)
		{
			break;
		}
	}

	HexaFloat P(this->size - zcount);
	for (int i = this->size - 1 - zcount, j = 0; i >= 0; i--, j++)
	{
		P.Vs[P.size - 1 - j] = this->Vs[i];
	}
	delete[]this->Vs;
	this->size = P.size;
	this->Vs = P.Vs;
	P.Vs = nullptr;
	this->p_ind = this->p_ind - zcount;
}