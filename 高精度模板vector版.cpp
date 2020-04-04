#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

bool insigma(char ch){
	return ch=='-'||('0'<=ch&&ch<='9');
}



struct number{
	vector<int> num; 
	bool fu;	
	number(){
		clear();
	}
	
	unsigned int size(){
		return updata_len();
	}
	
	unsigned int updata_len(){
		for(int i=num.size()-1;i>=0;i--) if(!num[i]) num.pop_back();else break;
		return num.size();
	}
	
	int & operator[] (unsigned int i)
	{
		while(i>=num.size()) num.push_back(0);
		return num[i];
	} 
	
	int at(unsigned int i)
	{
		if(i>=num.size()||i<0) return -1;
		return num[i];
	}
	
	void clear(){
		num.clear();
		fu=0;
	}
	/*
	number operator= (int x){//隐式转换
		this->clear();
		fu=(x<0);
		num.push_back(abs(x));
		if(x>9) carry_bit();
		if(x<-9) back_space();
		return *this;
	}
	*/
	number operator= (number x){
		cout<<"fuzhi\n";
		fu=x.fu;
		num=x.num;
		return *this;
	}
	
	number (int x){
		cout<<"经过yinshi转换\n";
		clear();
		fu=(x<0);
		num.push_back(abs(x));
		if(x>9) carry_bit();
	}
	
	
	void input(){
		string a;
		cin>>a;
		if(a[0]=='-'){
			fu=1;
			for(unsigned int i=0;i<a.size()-1;i++) num.push_back(a[a.size()-i-1]-'0');
		}
		else{
			for(unsigned int i=0;i<a.size();i++) num.push_back(a[a.size()-i-1]-'0');
		}
	}
	
	void output(){
		if(fu) cout<<"-";
		bool flag=0;
		for(int i=num.size();i>0;i--){
			if(num[i]) flag=1;
			if(num[i]>9) carry_bit();
			if(flag) putchar(num[i]+'0');//putchar加速输出 
		}
		putchar(num[0]+'0');
	}
	
    friend istream & operator>> (istream &in, number &obj);	
	friend ostream & operator<< (ostream &out, number obj);
	friend number abs(number x);
	friend number max(number a,number b);
	friend number min(number a,number b);
	
	
	int compare(number x){//2=	1> 0<
		if(fu^x.fu){
			if(fu) return 0; 
			else return 1;
		}
		if(updata_len()!=x.updata_len()) return (size()>x.size())^fu;
		for(int i=max(num.size(),x.num.size());i>=0;i--)
		{
			if(num[i]>x.num[i]) return !fu;//大于(1)
			if(num[i]<x.num[i]) return fu;//小于(0)
		}
		return 2;//等于
	}
	
	//利用compare()重载比较运算符 
	 
	bool operator> (number x){return (compare(x)==1);} 
	bool operator< (number x){return (compare(x)==0);}
	bool operator>= (number x){return !(*this<x);}
	bool operator<= (number x){return !(*this>x);}
	bool operator== (number x){return compare(x)==2;}
	bool operator!= (number x){return compare(x)!=2;}

	number operator++ (){
		num[0]++;
		if(num[0]>9) carry_bit();
		return *this;
	}
	
	number operator++ (int){
		number save=*this;
		++*this;
		return save;
	}
	
	number operator-- (){
		if(*this==0)
		num[0]--;
		if(num[0]<0) back_space();
		return *this;
	}
	
	number operator-- (int){
		number save=*this;
		num[0]--;
		if(num[0]<0) back_space();
		return save;
	}
	
	bool judge_zero(){
		for(int i=num.size()-1;i>=0;i--)
			if(num[i]) return 0;
		return 1;
	}
	
	bool judge_non_zero(){
		return !judge_zero();
	}
	
	bool convert_bool(){
		return !judge_zero();
	}
	
	bool even(){
		if(num[0]&1) return 0;
		return 1;
	}
	
	bool odd(){
		if(num[0]&1) return 1;
		return 0;
	}
	
	void carry_bit(){
		cout<<"zhelidedaoxiaoshi "<<num.size()<<endl;
		for(unsigned int i=0;i<num.size();i++){
			cout<<"检查第"<<i<<"位溢出\n";
			cout<<"第"<<i<<"位是"<<num[i]<<endl; 
			if(num[i]>9)
			{
				cout<<"在第"<<i<<"位上发现溢出\n"; 
				(*this)[i+1]+=num[i]/10;
				num[i]%=10;
			}
		}
		cout<<"jinwei over\n";
	}
	
	void back_space(){
		cout<<"开始退位\n";
		carry_bit();
		cout<<"tuiweijieshu\n";
	}
	
	number add(number x){
		number res=*this;
		for(unsigned int i=0;i<x.size();i++){
			res[i]+=x.num[i];
		}
		res.carry_bit();
		return res;
	}
	
	number sub(number x){
		number res=*this;
		for(unsigned int i=0;i<x.size();i++){
			res[i]-=x.num[i];
		}
		res.back_space();
		return res;
	}
	
	number operator+ (number x){
		number res;
		if(fu==x.fu){
			res=x.add(*this);
			res.fu=fu;
		}
		else{
			if(abs(*this)>abs(x)) res=this->sub(x),res.fu=fu;
			else res=x.sub(*this),res.fu=x.fu;
		}
		return res;
	}
	
	number operator+= (const number & x){
		*this=*this+x;
		return *this;
	}
	
	number operator- (number x){
		number i,j;
		i=max(*this,x);
		j=min(*this,x);
		if(fu==x.fu){
			
		}
		else{
			
		}
		
		return i;
	}
	
	number operator-= (number x){
		*this=*this-x;
		return *this; 
	}
	
	number operator* (number x){
		number sum;
		
		for(unsigned int i=0;i<size();i++)
		for(unsigned int j=0;j<x.size();j++)
		{
			sum[i+j]+=num[i]*x.num[j];
		}
		sum.fu=fu^x.fu;
		sum.carry_bit();
		return sum;
	}
	
	number operator*= (number x){
		return *this=*this*x;
	}
	
	number factor(){
		number ans,t;
		t.num[0]=1;
		ans.num[0]=1;
		for(;t<=*this;t.num[0]+=1,t.carry_bit())
			ans*=t;
		return ans;
	}
	
	number division2(){
		number res=*this;
		for(unsigned int i=res.size()-1;i>0;i--){
			cout<<"第"<<i<<"位ing\n"; 
			if((res[i]&1)) res[i-1]+=10;
			res[i]>>=1;
		}
		res[0]>>=1;
		cout<<"结束/2\n";
		return res;
	}
	
	number operator/ (number x){
//		if(x==2) return this->division2();
		number a=abs(*this),b=abs(x),c;
		for(c=0;c<=a;c++)
		{
			cout<<"try"<<c<<endl;
			if(c*b<=a&&(c+1)*b>a){
				break;
			}
		}
		c.fu=x.fu^fu;
		return c;
	}
	
	number operator/= (number x){
		return *this=*this/x;
	}
	
	number operator% (number x){
		number last=abs(*this/x*x),a=abs(*this);
		a-=last;
		a.fu=fu^x.fu;
		return a;
	}
	number operator%= (number x){
		return *this=*this%x;
	}
};

number max(number a,number b){
	return a>b?a:b;
}

number min(number a,number b){
	return a<b?a:b;
}

number abs(number x){
	number rec=x;
	rec.fu=0;
	return rec;
}

istream & operator>> (istream &in, number &obj)
{
	string a;
	in>>a;
	
	if(a[0]=='-'){
		obj.fu=1;
		for(unsigned int i=0;i<a.size()-1;i++) obj.num.push_back(a[a.size()-i-1]-'0');
	}
	else{
		for(unsigned int i=0;i<a.size();i++) obj.num.push_back(a[a.size()-i-1]-'0');
	}
	if (!in) obj.clear();
    return in;
}

ostream & operator<< (ostream &out,number obj)
{
	obj.carry_bit();
    if(obj.fu) out<<"-";
		bool flag=0;
		for(unsigned int i=obj.size()-1;i>0;i--){
			if(obj.num[i]) flag=1;
			if(flag) out<<obj.num[i]; 
		}
		out<<obj.num[0];
    return out;
}


number gcd_rec(number a,number b){
	if(b.judge_zero()) return a;
	return gcd_rec(b,a-b);
}

number gcd(number a,number b){
	if(a.judge_zero()) return a;
	number t;
	for(;;t=b,b=a-b,a=t)
		if(b.judge_zero()) return a;
	return a;
}

number gcd_mod(number a,number b){
	if(a.judge_zero()) return a;
	number t;
	for(;;t=b,b=a%b,a=t)
		if(b.judge_zero()) return a;
	return a;
}

number power(number a,number n){
	number zero;
	number c;c=1;
	for(;n>zero;n.division2(),a*=a) if(n.odd()) c*=a;
	return c;
}

number C(number r,number n)
{
	number res=1;
	for(number i=0;i<r;i++) res*=n-i;
	for(number i=0;i<r;i++)
}

int main()
{
number a,b,c;
    cin>>a>>b;
    c=a+b;
	cout<<"a+b="<<c<<endl;
	c=a-b;
	cout<<"a-b="<<c<<endl;
    c=a*b;
    cout<<"a*b="<<c<<endl;
    c=a.division2();
    cout<<"a/2="<<c<<endl;
    c=a/b;
    cout<<"a/b="<<c<<endl;
    c=a.factor();
    cout<<"a!="<<c<<endl;
    c=gcd(a,b);
    cout<<"gcd(a,b)="<<c;
    return 0;
}
