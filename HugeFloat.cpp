#include "Bscs22133HugeFloat.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;


HugeFloat::HugeFloat()
{
	this->size = 0;
	this->Vs = nullptr;
	this->p_ind = 0;
	this->isneg = false;
}
HugeFloat::HugeFloat(int s)
{
	this->size = s;
	this->Vs = new int[s];
	this->p_ind = 0;
	this->isneg = false;
}
HugeFloat::HugeFloat(const HugeFloat& S)
{
	this->Assign(S);
}
HugeFloat::HugeFloat(ifstream& rdr)
{
	this->Load(rdr);
}
void HugeFloat::Pirnt()
{
	cout << ((isneg == true) ? '-' : '+');
	for (int i = 0; i < this->size; i++)
	{
		if (i == this->p_ind)
		{
			cout << '.';
		}
		cout << this->Vs[this->size-i-1];
	}
}
void HugeFloat::Load(ifstream& rdr)
{
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
	//this->Trim();
}
void HugeFloat::GetFloat(string l)
{
	this->Vs=nullptr;
	this->size = l.size()-1;
	this->Vs = new int[this->size];
	int index = 0;


	for (int i=l.size()-1; i >=0;i--)
	{
		if (l[i] == '.')
		{
			this->p_ind = i;
		}
		if (l[i] != '.')
		{
			int n;
			n = l[i] - '0';
			this->Vs[index] = n;
			index++;
		}
	}
}
const HugeFloat& HugeFloat::operator=(const HugeFloat& S)
{
	this->Assign(S);
	return *this;
}
int HugeFloat::operator[](int i) const
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
int& HugeFloat::operator[](int i)
{
	int t = 0;
	if (i >= this->size)
	{
		return t;
	}
	else
	{
		return this->Vs[i];
	}
	//return this->Vs[i];
}
void HugeFloat::Assign(const HugeFloat& S)
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
}



const HugeFloat HugeFloat::add(const HugeFloat& S)const
{

	if (this->p_ind == 0 && S.p_ind == 0)
	{
		HugeFloat P(this->size + 1);
		int carry = 0;
		int ans = 0;
		for (int i = 0; i < P.size; i++)
		{
			ans = ((*this)[i] + S[i] + carry) % 10;
			carry = ((*this)[i] + S[i] + carry) / 10;

			P[i] = ans;
		}
		P.Trim();
		return P;
	}



	HugeFloat TD=*this;
	HugeFloat SD=S;
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
	HugeFloat P(k+1);
	int carry = 0;
	int ans = 0;
	for (int i = 0; i < P.size; i++)
	{
		ans = ((TD)[i] + SD[i] + carry) % 10;
		carry = ((TD)[i] + SD[i] + carry) / 10;
		P[i] = ans;
	}
	int ind = P.size - max(bef_deci1, bef_deci2);
	P.p_ind = ind;
	P.Trim();
	return P;

		
}
const HugeFloat HugeFloat::sub(const HugeFloat& S)const
{
	if (this->p_ind == 0 && S.p_ind == 0)
	{
		int count=0;
		HugeFloat P(this->size);
		int ans = 0;
		int carry = 0;
		for (int i = 0; i < P.size; i++)
		{
			ans = ((*this)[i] - S[i] - carry) % 10;
			carry = ((ans < 0) ? 1 : 0);
			ans = ((ans < 0) ? ans + 10 : ans);
			P[i] = ans;
		}
		P.p_ind = 0;
		P.Trim();
		return P;
	}



	HugeFloat TD = *this;
	HugeFloat SD = S;
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
	HugeFloat P(k);
	int carry = 0;
	int ans = 0;
	int ccount = 0;
	for (int i = 0; i < P.size; i++)
	{
		/*if (carry == 1)
		{
			ccount--;
		}*/
		ans = ((TD)[i] - SD[i] - carry) % 10;
		/*if (ans < 0 && ccount<=0)
		{*/
			carry = ((ans < 0) ? 1 : 0);
			ccount++;
		/*}*/
		ans = ((ans < 0) ? ans + 10 : ans);
		P[i] = ans;
	}
	int ind = P.size - max(bef_deci1, bef_deci2);
	P.p_ind = ind;
	P.Trim();

	return P;
}
bool HugeFloat::LessThanQuantityWise(const HugeFloat& S) const
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

		if ((*this)[this->size-i-1] > S[S.size-i-1])
		{
			return false;
		}
		if ((*this)[this->size - i - 1] < S[S.size - i - 1])
		{
			return true;
		}
	}
	HugeFloat TD = *this;
	HugeFloat SD = S;
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

	for (int i = n-this->p_ind-1; i >= 0; i--) // Decimal Part Checking
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
bool HugeFloat::GreaterThanQuantityWise(const HugeFloat& S) const
{
	return S.LessThanQuantityWise(*this);
}
bool HugeFloat::EqualQuantityWise(const HugeFloat& S) const
{
	return (!(*this).LessThanQuantityWise(S) && !(*this).GreaterThanQuantityWise(S));
}



const HugeFloat HugeFloat::operator+(const HugeFloat& S)const
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
					HugeFloat R = Zero();
					return R;
				}
			}
		}
	}

	if (this->isneg == S.isneg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HugeFloat R = this->add(S);
			R.isneg = this->isneg;
			return R;
		}
		else
		{
			HugeFloat R = S.add(*this);
			R.isneg = S.isneg;
			return R;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HugeFloat R = this->sub(S);
			R.isneg = this->isneg;
			return R;
		}
		else
		{
			HugeFloat R = S.sub(*this);
			R.isneg = S.isneg;
			return R;
		}
	}



}
const HugeFloat& HugeFloat::operator+=(const HugeFloat& S)
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
					HugeFloat R = Zero();
					return R;
				}
			}
		}
	}

	if (this->isneg == S.isneg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HugeFloat R;
			R = this->add(S);
			//(*this) = this->add(S);
			(*this).isneg = this->isneg;
			*this = R;
			return *this;
		}
		else
		{
			(*this) = S.add(*this);
			(*this).isneg = S.isneg;
			/**this = R;*/
			return *this;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			/*HugeIntegers R = this->sub(S);*/
			(*this) = this->sub(S);
			(*this).isneg = this->isneg;
			/**this = R;*/
			return *this;
		}
		else
		{
			/*HugeIntegers R = S.sub(*this);*/
			(*this) = S.sub(*this);
			(*this).isneg = S.isneg;
			/**this = R;*/
			return *this;
		}
	}
}
const HugeFloat HugeFloat::operator!()const
{
	HugeFloat R = (*this);
	R.isneg = !(this->isneg);
	return R;
}
const HugeFloat HugeFloat::operator-(const HugeFloat& S)const
{
	return (*this) + (!S);
}
const HugeFloat& HugeFloat::operator-=(const HugeFloat& S)
{
	HugeFloat I = (*this) += (!S);
	return I;
}

const HugeFloat HugeFloat::operator++(int d)
{
	HugeFloat R = (*this);
	(*this) = (*this) + One();
	return R;
}
HugeFloat& HugeFloat::operator++()
{
	HugeFloat P = One();
	(*this) = (*this) + P;
	return (*this);
}
const HugeFloat HugeFloat::operator--(int d)
{
	HugeFloat R = (*this);
	(*this) = (*this) - One();
	return R;
}
HugeFloat& HugeFloat::operator--()
{
	HugeFloat P = One();
	(*this) = (*this) + P;
	return (*this);
}


ostream& operator<<(ostream& cout, const HugeFloat& H)
{
	cout << ((H.isneg == true) ? '-' : '+');
	for (int i = 0; i < H.size; i++)
	{
		if (i == H.p_ind)
		{
			cout << '.';
		}
		cout << H.Vs[H.size - i - 1];
	}
	return cout;
}
ostream& HugeFloat::operator<< (ostream& cout)
{
	this->Pirnt();
	return cout;
}
ifstream& operator>>(ifstream& rdr, HugeFloat& H)
{
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
ifstream& HugeFloat::operator>>(ifstream& rdr)
{
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
istream& operator>>(istream& cin, HugeFloat& H)
{
	int size=0;
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
		size = c.size()-1;
		isneg = false;
	}
	HugeFloat R(size);
	for (int i = 0,j=0; i < c.size(); i++)
	{
		if (c[i] != '-' && c[i]!='.')
		{
			int n = c[i] - '0';
			R.Vs[R.size-j-1] = n;
			j++;
		}
		else if (c[i] == '.')
		{
			R.p_ind = j;
		}
	}
	H = R;
	H.isneg = isneg;
	return cin;
};


bool  HugeFloat::operator>(const HugeFloat& S)const
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
bool  HugeFloat::operator>=(const HugeFloat& S)const
{
	if ((*this > S) || (*this == S))
	{
		return true;
	}
	return false;
}
bool  HugeFloat::operator<(const HugeFloat& S)const
{
	return S > (*this);
}
bool  HugeFloat::operator<=(const HugeFloat& S)const
{
	if (this->p_ind ==0 && S.p_ind == 0)
	{
		if (this->size > S.size)
		{
			return false;
		}
		else if (this->size < S.size)
		{
			return true;
		}
		for (int i = 0; i <this->size; i++)
		{
			if (this->Vs[this->size-i-1] > S.Vs[this->size - i - 1])
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
bool  HugeFloat::operator==(const HugeFloat& S)const
{

	return (!(*this < S) && !(*this > S));
}
bool HugeFloat::operator!=(const HugeFloat I)const
{
	if (this->p_ind==0)
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


const HugeFloat HugeFloat:: operator*(const HugeFloat& S)const
{
	/*HugeFloat R;
	HugeFloat I;
	HugeFloat A;
	HugeFloat B;
	if (this->GreaterThanQuantityWise(S))
	{
		A = *this;
		A.isneg = false;
		A.p_ind = 0;
		B = S;
		B.isneg = false;
		B.p_ind = 0;
	}
	else
	{

		A = S;
		A.isneg = false;
		A.p_ind = 0;
		B = *this;
		B.isneg = false;
		B.p_ind = 0;
	}
	HugeFloat Ch;
	Ch.p_ind = 0;


	HugeFloat C = One();
	while (B != Zero())
	{
		R = A;
		C = One();
		while (Ch <= B)
		{
			R += R;
			C += C;
			Ch = C + C;
			Ch.p_ind = 0;
		}
		I += R;
		B.p_ind = 0, C.p_ind = 0;
		B =B- C;
		B.p_ind = 0;
	}

	if ((*this).isneg != S.isneg)
	{
		I.isneg = true;
	}
	if ((*this).isneg == S.isneg)
	{
		I.isneg = false;
	}

	int in = this->p_ind + S.p_ind-1;
	I.p_ind = in;
	return I;*/

	HugeFloat TD = *this;
	HugeFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	HugeFloat R;
	HugeFloat I;
	HugeFloat A = *this;
	A.Trim();
	A.isneg = false;
	A.p_ind = 0;
	HugeFloat B = S;
	B.isneg = false;
	B.Trim();
	B.p_ind = 0;
	HugeFloat C = MOne();
	HugeFloat Ch;
	HugeFloat T;
	while (B != Zero())
	{
		R = A;
		C = MOne();
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
		T=T+R;
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

	I.p_ind = I.size-(bef_deci2+bef_deci1);
	int t = I.p_ind;
	return I;


}
const HugeFloat& HugeFloat::operator*=(const HugeFloat& S)
{
	HugeFloat TD = *this;
	HugeFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();

	HugeFloat R;
	HugeFloat I;
	HugeFloat A = *this;
	A.Trim();
	A.isneg = false;
	A.p_ind = 0;
	HugeFloat B = S;
	B.isneg = false;
	B.Trim();
	B.p_ind = 0;
	HugeFloat C = MOne();
	HugeFloat Ch;
	HugeFloat T;
	while (B != Zero())
	{
		R = A;
		C = MOne();
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
const HugeFloat HugeFloat::operator/(const HugeFloat& S)const
{

	HugeFloat TD = *this;
	HugeFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();
	int div_precision = 0;
	HugeFloat A;
	HugeFloat B;
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
			int s = S.size - S.p_ind-this->p_ind;
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
			int aft_deci = this->p_ind + bef_deci2+1;
			div_precision = aft_deci - S.size;
		}
		else
		{
			if (B.size != S.size)
			{
				int aft_deci = this->p_ind + bef_deci2;
				div_precision = aft_deci-B.size;
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
		HugeFloat R;
		HugeFloat l;
		HugeFloat I;
		HugeFloat T;
		HugeFloat C = MOne();
		HugeFloat Ch;
		while (A != Zero())
		{
			R = B;
			R.p_ind = 0;

			Ch=R+R;
			Ch.p_ind = 0;
			C = MOne();
			while (Ch <= A)
			{
				R += R;
				C += C;
				Ch = R + R;
				Ch.p_ind = 0;
				R.p_ind = 0;
				C.p_ind = 0;
			}
			T =T+C;
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
		//if (bef_deci1 == bef_deci2)
		//{
		//	if (this->size-bef_deci1 > S.size-bef_deci2)
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size-n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//	}
		//	else
		//	{
		//		I.p_ind = this->p_ind;
		//		int t = I.p_ind;
		//	}
		//}
		//if (bef_deci1 != bef_deci2)
		//{
		//	if (this->size - bef_deci1 < S.size - bef_deci2)
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size - n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//		/*int n = bef_deci1 - bef_deci2;
		//		int p = (this->size - bef_deci1)-(S.size - bef_deci2);
		//		I.p_ind = n + p;
		//		int t = I.p_ind;*/
		//	}
		//	else
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size - n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//	}
		//}
		//{
		//	int n = S.size - S.p_ind;
		//	int p = (this->size - this->p_ind)-n;
		//	I.p_ind = p;
		//}
	/*	if ((this->size-bef_deci1) == (S.size-bef_deci2))
		{
			I.p_ind = this->p_ind;
			int t = I.p_ind;
		}
		else if ((this->size - bef_deci1) != (S.size - bef_deci2))
		{
			I.p_ind = S.size-S.p_ind;
			int t = I.p_ind;
		}*/
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
		HugeFloat I = Zero();
		return I;
	}
}
const HugeFloat& HugeFloat::operator/=(const HugeFloat& S)
{

	HugeFloat TD = *this;
	HugeFloat SD = S;
	int bef_deci1 = 0;
	int bef_deci2 = 0;
	bef_deci1 = this->BeforeDecimal();
	bef_deci2 = S.BeforeDecimal();
	int div_precision = 0;
	HugeFloat A;
	HugeFloat B;
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
		HugeFloat R;
		HugeFloat l;
		HugeFloat I;
		HugeFloat T;
		HugeFloat C = MOne();
		HugeFloat Ch;
		while (A != Zero())
		{
			R = B;
			R.p_ind = 0;

			Ch = R + R;
			Ch.p_ind = 0;
			C = MOne();
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
		//if (bef_deci1 == bef_deci2)
		//{
		//	if (this->size-bef_deci1 > S.size-bef_deci2)
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size-n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//	}
		//	else
		//	{
		//		I.p_ind = this->p_ind;
		//		int t = I.p_ind;
		//	}
		//}
		//if (bef_deci1 != bef_deci2)
		//{
		//	if (this->size - bef_deci1 < S.size - bef_deci2)
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size - n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//		/*int n = bef_deci1 - bef_deci2;
		//		int p = (this->size - bef_deci1)-(S.size - bef_deci2);
		//		I.p_ind = n + p;
		//		int t = I.p_ind;*/
		//	}
		//	else
		//	{
		//		int n = bef_deci2;
		//		I.p_ind = I.size - n; //max(this->p_ind, S.p_ind);
		//		int t = I.p_ind;
		//	}
		//}
		//{
		//	int n = S.size - S.p_ind;
		//	int p = (this->size - this->p_ind)-n;
		//	I.p_ind = p;
		//}
	/*	if ((this->size-bef_deci1) == (S.size-bef_deci2))
		{
			I.p_ind = this->p_ind;
			int t = I.p_ind;
		}
		else if ((this->size - bef_deci1) != (S.size - bef_deci2))
		{
			I.p_ind = S.size-S.p_ind;
			int t = I.p_ind;
		}*/
		if ((*this).isneg != S.isneg)
		{
			I.isneg = true;
		}
		if ((*this).isneg == S.isneg)
		{
			I.isneg = false;
		}
		//I.Trim();
		this->Assign(I);
		return *this;
	}

	else if (A < B)
	{
		HugeFloat I = Zero();
		this->Assign(I);
		return *this;
	}
}


HugeFloat HugeFloat::One()
{
	HugeFloat R(4);
	R.Vs[0] = 0;
	R.Vs[1] = 0;
	R.Vs[2] = 0;
	R.Vs[3] = 1;
	R.p_ind = 1;
	return R;
}
HugeFloat HugeFloat::MOne()
{
	HugeFloat R(1);
	R.Vs[0] = 1;
	R.p_ind = 0;
	return R;
}
HugeFloat HugeFloat::Zero()
{
	HugeFloat R(1);
	R.Vs[0] = 0;
	return R;
}
void HugeFloat::Trim()
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

	HugeFloat P(this->size - zcount);
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
void HugeFloat::TrimFromLast()
{
	int zcount = 0;
	for (int i =0; i < this->size; i++)
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
	for (int i = zcount,j=0; i < this->size; i++,j++)
	{
		n[j] = this->Vs[i];
	}
	delete[]this->Vs;
	this->Vs = n;
	this->size = this->size - zcount;
}
void HugeFloat::MultiplyFloat(int s)
{
	HugeFloat N(this->size + s);
	for (int i = 0; i < N.size; i++)
	{
		if (i < s)
		{
			N.Vs[i] = 0;
		}
		else
		{
			N.Vs[i] = this->Vs[i-s];
		}
	}
	*this = N;
}
void HugeFloat::AddZero(int n)
{
	HugeFloat N(this->size + n);

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
	*this = N;
}
int HugeFloat::BeforeDecimal()const
{
	int count = 0;
	for (int i = 0,j=this->size; i < this->size; i++,j--)
	{
		if (j > this->p_ind)
		{
			count++;
		}
	}
	return count;
}
HugeFloat::~HugeFloat()
{
	delete[]this->Vs;
}