#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

bool insigma(char ch){
    return ch=='-'||('0'<=ch&&ch<='9')||ch=='+';
}



const int maxn = 1000;
struct number{
    int num[maxn];
    int len;
    bool fu;
    
    number(){//初始化 
        len=fu=0;
        memset(num,0,sizeof(num));
    }
    
    int updata_len(){//更新长度 
        for(int i=maxn-1;i>=0;i--) if(num[i]) return len=i+1;
        return len=0;
    }
    
    //    /*
    number operator= (int x){//隐式转换 
        fu=(x<0);
        num[0]=abs(x);
        if(x>9) carry_bit();
        if(x<-9) back_space();
        return *this;
    }
//    */
    /*
    number (int x){//有bug的构造函数 暂时用重载=替代 
        fu=(x<0);
        num[0]=abs(x);
        if(x>9) carry_bit();
        if(x<-9) back_space();
    }
    */
    
    void input(){
//        /*
        string a;
        cin>>a;
        if(a[0]=='-'){
            fu=1;
            len=a.size()-1;
            for(unsigned int i=0;i<a.size()-1;i++) num[i]=a[a.size()-i-1]-'0';
        }
        else{
            len=a.size();
            for(unsigned int i=0;i<a.size();i++)    num[i]=a[a.size()-i-1]-'0';
        }
        
//        */
        /*
        len=0;
        char ch;
        while(!insigma(ch=getchar()));
        if(ch=='-')
            fu=true;
        else 
            num[len++]=ch-'0';
        while(isdigit(ch=getchar())){
            num[len++]=ch-'0';
        }
        int t;
        for(int i=0;i<len;i++)
        {
            t=num[i];
            num[i]=num[len-i-1];
            num[len-i-1]=t; 
        }
        */
    }
    
    void output(){
        if(fu) cout<<"-";
        bool flag=0;
        for(int i=len;i>0;i--){
            if(num[i]) flag=1;
            if(num[i]>9) carry_bit(); 
            if(flag) putchar(num[i]+'0');//putchar加速 
        }
        putchar(num[0]+'0');
    }
    
    friend istream & operator>> (istream &in, number &obj);    
    friend ostream & operator<< (ostream &out, number &obj);
    
    int compare(number x){//2=    1> 0<
        if(fu^x.fu){
            if(fu) return 0; 
            else return 1;
        }
        for(int i=max(len,x.len);i>=0;i--)
        {
            if(num[i]>x.num[i]) return !fu;//大于 (1)
            if(num[i]<x.num[i]) return fu;//小于 (0)
        }
        return 2;//相等 
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
        for(int i=maxn-1;i>=0;i--)
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
        if(num[0]%2) return 0;
        return 1;
    }
    
    bool odd(){
        if(num[0]%2) return 1;
        return 0;
    }
    
    void carry_bit(){
        for(int i=0;i<maxn;i++){
            num[i+1]+=num[i]/10;
            num[i]%=10;
        }
        updata_len();
    }
    
    void back_space(){
        for(int i=0;i<maxn;i++){
            while(num[i]<0) num[i]+=10,num[i+1]--;
        }
    }
    
    number operator+ (int x){
        number newness=*this;
        newness.num[0]+=x;
        if(newness.num[0]>9) newness.carry_bit();
        return newness;
    }
    
    number operator+ (number x){
        number res=x;
        for(int i=0;i<maxn;i++)
        {
            res.num[i]+=num[i];
        }
        res.carry_bit();
        return res;
    }
    
    number operator+= (int x){
        *this=(*this+x);
        return *this;
    }
    
    number operator+= (number x){
        *this=*this+x;
        return *this;
    }
    
    number operator- (number x){
        number i,j;
        if(compare(x)) {i=*this,j=x;}
        else {i=x,j=*this;}
        for(int t=0;t<maxn;t++)
        {
            i.num[t]-=j.num[t];
        }
        i.back_space();
        return i;
    }
    
    number operator-= (number x){
        *this=*this-x;
        return *this; 
    }
    
    number operator* (number x){
        number sum;
        sum.fu=fu^x.fu;
        for(int i=0;i<updata_len();i++)
        for(int j=0;j<x.updata_len();j++)
        {
            if(i+j>maxn-1) continue;
            sum.num[i+j]+=num[i]*x.num[j];
        }
        sum.carry_bit();
        return sum;
    }
    
    number operator*= (number x){
        return *this=*this*x;
    }
    
    number nabs(){
    	number ret=*this;
    	ret.fu=0;
    	return ret;
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
        for(int i=maxn-1;i>=0;i--){
            if(num[i]&1&&i!=0) num[i-1]+=10;
            num[i]>>=1;
        }
        return *this;
    }
    number operator/(number b){
    	bool f=fu^b.fu;
    	number a=nabs();
		b=b.nabs();
    	number l=0,r=a,mid;
    	while(l<r)
    	{
    		mid=(l+r).division2();
    		if(mid*a)
		}
	}
};

number nabs(number x){
	return x.abs();
}

istream & operator>> (istream &in, number &obj)
{
    string a;
    in>>a;
    if(a[0]=='-'){
        obj.fu=1;
        obj.len=a.size()-1;
        for(unsigned int i=0;i<a.size()-1;i++) obj.num[i]=a[a.size()-i-1]-'0';
    }
    else{
        obj.len=a.size();
        for(unsigned int i=0;i<a.size();i++) obj.num[i]=a[a.size()-i-1]-'0';
    }
    if (!in) obj = number();
    return in;
}

ostream & operator<< (ostream &out, number &obj)
{
    if(obj.fu) cout<<"-";
        bool flag=0;
        for(int i=obj.len;i>0;i--){
            if(obj.num[i]) flag=1;
            if(obj.num[i]>9) obj.carry_bit(); 
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
	a=abs(a);b=abs(b);
    if(a.judge_zero()) return a;
    for(number t;!b.judge_zero();t=b,b=a-b,a=t);
    return a;
}
/*
number gcd_short(number a,number b){
	a=abs(a);b=abs(b);
	if(a.judge_zero()) return a;
	if(b.judge_zero()) return b;
	if(a<b) swap(a,b);
	for(number i=2;i<a.division2();i++)
	{
		if(a%2)
		
	}
}
*/
number power(number a,number n){
    number zero;
    number c;c=1;
    for(;n>zero;n.division2(),a*=a) if(n.odd()) c*=a;
    return c;
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
