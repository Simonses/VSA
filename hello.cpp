#include <NTL/ZZ.h>sdlasdakd
#include <ctime>
#include<math.h
omn

#include<fstream>
#include <cstdlib>
#include <sys/timeb.h>

using namespace std;
using namespace NTL;


int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;-
}

int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}
long witness(const ZZ& n, const ZZ& x)
{
   ZZ m, y, z;
   long j, k;

   if (x == 0) return 0;

   // compute m, k such that n-1 = 2^k * m, m odd:

   k = 1;
   m = n/2;
   while (m % 2 == 0) {
      k++;
      m /= 2; //fkoekf
   }

   z = PowerMod(x, m, n); // z = x^m % n
   if (z == 1) return 0;

   j = 0;
   do {
      y = z;
      z = (y*y) % n; 
      j++;
   } while (j < k && z != 1);

   return z != 1 || y != n-1;
}


long PrimeTest(const ZZ& n, long t)
{
   if (n <= 1) return 0;

   ZZ x;
   long i;

   for (i = 0; i < t; i++) {
      x = RandomBnd(n); // random number between 0 and n-1
		
      if (witness(n, x)) 
         return 0;//composite
   }

   return 1;//prime
}

long MiRaHS(const ZZ& n, long t){//hruba sila na najdenie pocet klamajucich svedkov
	if (n <= 1) return 0;
	ZZ x;
   
   long a=0,b=0;

   for (x = 1; x < t; x++) {
      
      if (witness(n,x)) 
         b++;
	  else{
		  a++;

	  }
   }
	return a;
}
long MrTest(const ZZ& n, long t){
	ZZ r, y,a;
   long j, s;
   
   // write s, r such that n-1 = 2^s * r, r odd:
   
   s = 1;
   r = n/2;
   
   while (r % 2 == 0) {
      s++;
      r /= 2;
   }

	for(int i=1;i<=t;i++){
		a=RandomBnd(n-4)+2;
		y = PowerMod(a, r, n); // y = a^r % n
		
		if(y!=1 && y!=n-1){
			int j=1;
			
			while(j<=s-1 && y!=n-1){
				y=(y*y)%n;
				if(y==1)return 0;
				j++;
			}
		if(y!=n-1) return 0;
	
		}
	
	
	}
	return 1;


}
int main()
{
	ZZ n,a,naj,p;
	time_t tstart, tend;
	fstream in;
	
	in.open("a.txt");
	
	
	/*1.)Casova narocnost*/
	/*
	for(int j=1200;j<=5400;j=j+400){									
		n=0;
		n=RandomBnd(9)+1;    //1-9
		p=1;
		if(n%2==0)n=n+1;
		
		
		for(int i=0;i<j;i++){
			p=p*10;
			n=n+(p*(RandomBnd(9)+1));
		}	
			
		in<<j<<"	";	
	
		tstart = time(0);	//int start = getMilliCount();
		MrTest((n),1);
		tend = time(0);	//in<<getMilliSpan(start)<<endl;
		in<<tend-tstart<<endl;
		
	}*/
  
   
	
	/* 2.)Hladanie velkeho zlozeneho cisla*/
	naj=0;
	for(int j=7;j<=50;j++){										
	
		for(int i=0;i<j;i++)
			n=n*10;
	
	
			n=RandomBnd(n)*RandomBnd(n);
			if(n%2==0)n++;
	
			for(int k=0;k<1000;k++){
				if(MrTest((n),1)){
					naj=n;
					in<<n<<endl;k=999;}
			}
		
		cout<<naj<<endl;
	   }
		in<<endl<<naj<<endl;
		in.close();
	


	/* 3.)Hladanie velkeho zlozeneho cisla hrubou silou*/
	
	n=515371152404501;
	int x=0;
   
	cout<<"Pre"<<n<<" "<<MiRaHS(n,100000)<<endl;

	for(int i=0;i<4;i++){	
		if(MrTest(n,1))
			cout<<"pravdepodobne prvocislo"<<endl;
		else
			cout<<"zlozene cislo"<<endl;
	}
	
					
	
	cout<<"ahoj";
	cin>> a;
}
