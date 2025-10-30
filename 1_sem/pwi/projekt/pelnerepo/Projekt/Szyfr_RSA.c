#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Szyfr_RSA.h"


#define ll unsigned long long
#define min(a, b) ((a) < (b) ? (a) : (b))
#define true 1
#define false 0

 int1024 multiply(int1024 a, int1024 b){
	int1024 c = {0};
	int a_len = -1;
	int b_len = -1;
	for(int i = 66-1; i >= 0; i--){
		if(a.chunk[i] != 0){
			a_len = i;
			break;
		}
	}
	for(int i = 66-1; i >= 0; i--){
		if(b.chunk[i] != 0){
			b_len = i;
			break;
		}
	}
	for(int i  = 0; i < min(66,a_len+b_len+2); i++){
		for(int j = 0; j <= i; j++){
			if(i+1 < 66) c.chunk[i+1]+=c.chunk[i]>>32;
			c.chunk[i]=c.chunk[i]-((c.chunk[i]>>32)<<32);
			c.chunk[i]+=a.chunk[j]*b.chunk[i-j];
		}
		if(i+1 < 66) c.chunk[i+1]+=c.chunk[i]>>32;
		c.chunk[i]=c.chunk[i]-((c.chunk[i]>>32)<<32);	
	}
	return c;
}


 int1024 shift(int1024 a, int s){
	int1024 c = {0};
	for(int i = s; i < 66; i++){
		c.chunk[i] = a.chunk[i-s];
	}
	return c;
}
 int1024 right_shift(int1024 a, int s){
	int1024 c = {0};
	for(int  i = 66-s-1; i >= 0; i--){
		c.chunk[i] = a.chunk[i+s];
	}
	return c;
}
 int get_bits(int1024 a){
	for(int i = 2102-1; i >= 0; i--){
		int czunk = i/32;
		int j = i%32;
		if(a.chunk[czunk]&((ll)(1)<<j)) return i+1;
	}
	return 0;
}
 int1024 subtract(int1024 a, int1024 b){
	int1024 c = {0};
	for(int i = 0; i < 66; i++){
		if(a.chunk[i]  < b.chunk[i]){
			a.chunk[i]+=((ll)(1)<<32);
			int j = i+1;
			while(a.chunk[j] == 0){
				a.chunk[j]+=((ll)(1)<<32)-1;
				j++;
			}
			a.chunk[j]--;
		}
		c.chunk[i] = a.chunk[i]-b.chunk[i];
	}
	return c;
}
 int1024 add(int1024 a, int1024 b){
	int1024 c = {0};
	for(int i = 0; i < 66; i++){
		c.chunk[i] += a.chunk[i]+b.chunk[i];
		if(c.chunk[i] >= ((ll)(1)<<32)){
			if(i < 66-1){
				c.chunk[i+1] += (c.chunk[i]/((ll)(1)<<32));
			}
			c.chunk[i] %= ((ll)(1)<<32);
		}
	}
	return c;
}


 bool isGreaterOrEqual(int1024 *a, int1024 *b){
	for(int i = 66-1; i >= 0; i--){
		if(a->chunk[i] > b->chunk[i]) return true;
		if(a->chunk[i] < b->chunk[i]) return false;
	}
	return true;
}
 int1024 bitshift(int1024 a, ll s){
	int1024 b = {0};
	ll bity = s%32;
	ll czunki = s/32;
	ll carry = 0;
	for(int i = czunki; i < 66; i++){
		b.chunk[i] = ((ll)(a.chunk[i-czunki])<<(ll)(bity)) + (ll)(carry);
		carry = (b.chunk[i]/((ll)(1)<<32));
		b.chunk[i]%=((ll)(1)<<32);
	}
	return b;
}
 int1024 right_bitshift(int1024 a, ll s){
	int1024 b = {0};
	ll bity = s%32;
	ll czunki = s/32;
	b = right_shift(bitshift(a,32-bity),czunki+1);
	return b;
}
 int1024 fast_divide_by_two(int1024 a){
	ll carry = 0; 
	ll ocarry = 0;
	for(int i = 66 - 1; i>=0 ;i--){
		carry = a.chunk[i]&((ll)(1));
		a.chunk[i]>>=1;
		a.chunk[i]|=(ocarry<<31); 
		ocarry = carry;	
	}
	return a;
}
 int count_zeroes(int1024 a){
	int i =0;
	while(i < 1024){
		if( (a.chunk[i/32]&(1<<(ll)(i%32)) ) != 0 ) return i;
		i++;
	}
	return i;
}
 int1024 modulo(int1024 a, int1024 b){
	for(int i = 2102-get_bits(b); i>=0; i--){  
		int1024 d = bitshift(b,i);
		if(isGreaterOrEqual(&a,&d)) {
			a = subtract(a,d);
		}
	}
	return a;
}


 pair_int1024 division_with_modulo(int1024 a, int1024 b){ 
	int1024 c = {0};
	pair_int1024 res;
	for(int i = 2102-get_bits(b); i>=0; i--){
		int1024 d = bitshift(b,i);
		if(isGreaterOrEqual(&a,&d)) {
			a = subtract(a,d);
			c.chunk[i/32]+=((ll)(1)<<(i%32));
		}
	}
	res.fi = c; res.se = a;
	return res;
}
 int1024 random_int1024_v(){
	int1024 a = {0};
	for(int i = 1024/32-1; i  >= 0; i-- ){
		for(int j = 31; j>=0; j--){	
				ll r = rand()%2;
				a.chunk[i]+=r*((ll)(1)<<j);
		}
	}
	return a;
}
 int1024 random_int1024(int1024 n){ 
	int1024 a = modulo(random_int1024_v(), n);
	return a;
}







 bool isEqual(int1024 a, int1024 b){
	if(isGreaterOrEqual(&a,&b) && isGreaterOrEqual(&b,&a)) return true;
	return false;
}

 void init_vec_pair_int(vec_pair_int* a){
	a->rozm = 0;
	a->rozm_max = 1;
	a->wsk = (struct pair_int *)malloc(a->rozm_max * sizeof(struct pair_int));
}

 void push_vec_pair_int(vec_pair_int* a, int f, int s){

	a->wsk[(a->rozm)].fi = f;
	a->wsk[(a->rozm)].se = s;
	a->rozm+=1;
	if(a->rozm == a->rozm_max){
		a->rozm_max*=2;
		a->wsk = (struct pair_int *)realloc(a->wsk, a->rozm_max * sizeof(struct pair_int));
	}

}

 void free_vec_pair_int(vec_pair_int* a){
	free(a->wsk);
	
}

 pair_int top_vec_pair_int(vec_pair_int* a){
	return a->wsk[(a->rozm)-1];
}

 void pop_vec_pair_int(vec_pair_int* a){
	a->rozm-=1;
}


 pair_int1024 Binary_Euclidean_Algorithm(int1024 a , int1024 b){
	static int1024 tab[5000];
	static int1024 tab2[5000];
	int1024 zero = {0};
	int1024 x = {0};
	int1024 y = {0};
	pair_int1024 result = {0};
	const ll jed = 1;
	vec_pair_int stos; init_vec_pair_int(&stos);
	
	int t = 0;
	while(!isEqual(a,zero) && !isEqual(b,zero)){
		if(a.chunk[0]&jed){
			
			if(b.chunk[0]&jed){
				if(isGreaterOrEqual(&a,&b)){
					a = subtract(a,b);
					push_vec_pair_int(&stos,1,0);
				}else{
					b = subtract(b,a);
					push_vec_pair_int(&stos,2,0);
				}
			}else{
				b = fast_divide_by_two(b);
				t++; tab[t] = b; tab2[t] = a;
				push_vec_pair_int(&stos,3,t);
			}
		
		}else{
			
			if(b.chunk[0]&jed){
				
				a = fast_divide_by_two(a);
				
				t++; tab[t] = a; tab2[t] = b;
				
				push_vec_pair_int(&stos,4,t);
				
				
			}else{	
				
				a = fast_divide_by_two(a);
				b = fast_divide_by_two(b);
				push_vec_pair_int(&stos,5,0);
				
			}
		}
		
	}
	if(isEqual(a,zero)) y.chunk[0]=1;
	if(isEqual(b,zero))	x.chunk[0]=1;
	while(stos.rozm > 0){
		pair_int wierzch = top_vec_pair_int(&stos);
		switch(wierzch.fi){
			case 1:
					y = add(x,y);
				break;
			case 2:
					x = add(x,y);
				break;
			case 3:
					if(y.chunk[0]&jed){
						x =add(x,tab[wierzch.se]);
						y =fast_divide_by_two(add(y,tab2[wierzch.se]));
					}else{
						y  = fast_divide_by_two(y);
					}
				break;
			case 4:
					if(x.chunk[0]&jed){
						x = fast_divide_by_two(add(x,tab2[wierzch.se]));
						y = add(y,tab[wierzch.se]);
					}else{
						x  = fast_divide_by_two(x);
					}
				break;
			case 5:
				break;
		}
		pop_vec_pair_int(&stos);
	}
	result.fi = x;
	result.se = y;
	free_vec_pair_int(&stos);
	return result;
}

 int1024 fast_divide(int1024 A, int b){
	return right_shift(A,b/32);
}

 int1024 fast_modulo(int1024 A, int b){
	int1024 C = {0};
	int czunki = b/32;
	for(int i = 0; i < czunki; i++) C.chunk[i] = A.chunk[i];
	return C;
}

 Montgomery_pack init_Montgomery_algorithm(int1024 N, int wykladnik){
	Montgomery_pack pack = {0};
	pack.R_wykladnik = wykladnik;
	pack.R.chunk[wykladnik/32]=1; 
	pack.N = N;
	pair_int1024 para = Binary_Euclidean_Algorithm(pack.R,N);
	int1024 ax = multiply(pack.R,para.fi);
	int1024 by = multiply(N,para.se);
	if(!isGreaterOrEqual(&ax,&by)){
		para.fi = subtract(N,para.fi);
		para.se = subtract(pack.R,para.se);
	} 
	pack.R_ = para.fi;
	pack.M = para.se;
	return pack;
}

 int1024 ConvertToMontgomeryForm(int1024 a, Montgomery_pack pack){
	return modulo(multiply(a,pack.R),pack.N);
}

 int1024 ConvertFromMontgomeryForm(int1024 a, Montgomery_pack pack){
	return modulo(multiply(a,pack.R_),pack.N);
}

 int1024 REDC(int1024 T, Montgomery_pack pack){
	int1024 S = {0};
	int1024 m = fast_modulo(multiply(fast_modulo(T,pack.R_wykladnik),pack.M),pack.R_wykladnik);
	S = fast_divide(add(T,multiply(m,pack.N)),pack.R_wykladnik);
	if(isGreaterOrEqual(&S,&pack.N)) return subtract(S,pack.N);
	return S;
}


 int1024 fast_montgomery_exponentation(int1024 a, int1024 b, int1024 mod, Montgomery_pack pack){
	int1024 c = {0}; c.chunk[0] = 1;
	a = ConvertToMontgomeryForm(a,pack);
	c = ConvertToMontgomeryForm(c,pack);

	bool ok = false;
	for(int i = 1024/32 - 1; i >= 0 ; i-- ){
		for(int j = 31; j >= 0; j--){
			int bit = (b.chunk[i]&(1<<j))>>j;
			if(bit) ok =true;
			if(!ok) continue;
			c = multiply(c,c);
			c = REDC(c,pack);
			if(bit == 1){
				c = multiply(c,a);
				c = REDC(c,pack);
			}
		}
		
	}
	c = ConvertFromMontgomeryForm(c,pack);
	return c;
}

 bool RabinMiller(int1024 p, int k){
	Montgomery_pack pack = init_Montgomery_algorithm(p,512);
	if(p.chunk[0]%2 == 0) return false; 
	int1024 c = {0}; int1024 jeden = {0}; jeden.chunk[0] = 1;
	c = subtract(p,jeden);
	int s= count_zeroes(c);
	int1024 d = right_bitshift(c,s);
	while(k--){
		int1024 a = random_int1024(c);
		int1024 jeden = {0}; jeden.chunk[0] = 1;
		bool ok = true;	
		int1024 res = fast_montgomery_exponentation(a,d,p,pack);
		for(int r = 0; r < s; r++){
			int1024 q = bitshift(d,r);
			res = fast_montgomery_exponentation(a,q,p,pack);
			if(r == 0){
				if(isEqual(res,jeden)) ok = false;
				if(!ok) break;
			}
			if(isEqual(res,c)) ok = false;
			if(!ok) break;
		}
		if(!ok) continue;
		if(ok) return false;
	}
	return true;
}

 key RSA(){
	int1024 Z = {0}; Z.chunk[512/32] = 1;
	int1024 p = {0}; int1024 q = {0};
	p = random_int1024(Z);
	q = random_int1024(Z);
	int1024 jeden = {0}; jeden.chunk[0] = 1;
	int1024 dwies = {0}; dwies.chunk[0] = 510510;
	pair_int1024 dziel = {0};
	dziel = division_with_modulo(p,dwies);
	p = add(multiply(dwies,dziel.fi),jeden);
	dziel = division_with_modulo(q,dwies);
	q = add(multiply(dwies,dziel.fi),jeden);
	while(!RabinMiller(p,10)){
		p = subtract(p,dwies);
	}
	while(!RabinMiller(q,10)){
		q = subtract(q,dwies);
	}
	int1024 n = multiply(p,q);
	int1024 phi = multiply(subtract(p,jeden),subtract(q,jeden));
	int1024 e = random_int1024(phi);
	int1024 d = {0};
	bool ok = false;
	while(!ok){
		pair_int1024 ab = Binary_Euclidean_Algorithm(e,phi);
		int1024 ax = multiply(ab.fi,e);
		int1024 by = multiply(ab.se,phi);
		int1024 diff = {0};
		if(isGreaterOrEqual(&ax,&by)) diff = subtract(ax,by);
		else diff = subtract(by,ax);
		if(isEqual(diff,jeden)) ok = true;
		d = modulo(ab.fi,phi);
		if(ok){
			if(!isEqual(modulo(multiply(d,e),phi),jeden)){
				d = modulo(multiply(d,subtract(phi,jeden)),phi);
			}
			break;
		}
		e = random_int1024(phi);
	}
	key klucz;
	klucz.privatekey.d = d;
	klucz.privatekey.n = n;
	klucz.publickey.e = e;
	klucz.publickey.n = n;
	return klucz; 
}


 void init_c_string(c_string* a){
	a->rozm = 0;
	a->rozm_max = 1;
	a->wsk = (char *)malloc(a->rozm_max * sizeof(char));
}

 void push_c_string(c_string* a, char z){
	a->wsk[(a->rozm)] = z;
	a->rozm+=1;
	if(a->rozm == a->rozm_max){
		a->rozm_max*=2;
		a->wsk = (char *)realloc(a->wsk, a->rozm_max * sizeof(char));
	}

}

 void free_c_string(c_string* a){
	if(a != NULL){
		if(a->wsk != NULL){
			free(a->wsk);
			a->wsk = NULL;
		}
		
	}
}

 char get_c_string(c_string* a, int i){
	return a->wsk[i];
}



 void RSA_encode(c_string* s, public_key klucz, c_string* res){
	free_c_string(res);
	init_c_string(res);
	int dlug = s->rozm;
	const int czunk_size = 124;
	int czunki = dlug/(czunk_size);
	Montgomery_pack pack = init_Montgomery_algorithm(klucz.n,1024);
	for(int i = 0; i < czunki+1; i++){
		int1024 c = {0};
		for(int j = 0; j < czunk_size; j++){
			if(i * czunk_size + j < dlug){
				if(i*czunk_size+j < (int)(s->rozm)) c.chunk[j/4]+=(((ll)( get_c_string( s,i*czunk_size+j) ) )<<(8*(j%4)));
			}
		}
		c = fast_montgomery_exponentation(c,klucz.e,klucz.n,pack);
		for(int j = 0; j < 256; j++){
			push_c_string(res,(char)(70+((c.chunk[j/8]&((ll)(15)<< ((j%8)*4)))>>((j%8)*4)))); 
		}
	}

}



 void RSA_decode(c_string* s, private_key klucz, c_string* res){
	//assert(res!=s || "RSA_decode powinno przyjmowac rozne wskazniki do c_stringow");
	free_c_string(res);
	init_c_string(res);
	int dlug = s->rozm;
	const int czunk_size = 256;
	int czunki = dlug/(czunk_size); 
	Montgomery_pack pack = init_Montgomery_algorithm(klucz.n,1024);
	for(int i = 0; i < czunki; i++){
		int1024 c = {0};
		for(int j = 0; j < 256; j++){
			c.chunk[j/8] += (((ll)(  get_c_string(s, i*256+j) )-(ll)(70))<<((j%8)*4));
		}
		c = fast_montgomery_exponentation(c,klucz.d,klucz.n,pack);
		for(int j = 0; j < 124; j++){
			push_c_string(res,  (char)(( (c.chunk[j/4])&(  255<<(8*(j%4))  ) )>>(8*(j%4))) ); 
			
		}	
		
	}
}
 void print_hex(int1024 a, c_string* res){
	free_c_string(res);
	init_c_string(res);
	for(int i = 0; i < 66; i++){
		for(int j = 0; j < 32; j+=4){
			push_c_string(	res , (char)('A'+((a.chunk[i]&((ll)(15)<<j))>>j)) );
		}
	}
}
 int1024 read_hex(c_string* a){
	int1024 res = {0};
	for(int i = 0; i < 66; i++){
		for(int j = 0; j < 32; j+=4){
			res.chunk[i] += (ll)(get_c_string(a,8*i+j/4) -'A')<<j;   
		}
	}
	return res;

}
 void print_c_string(c_string* a){
	for(int i = 0; i < a->rozm; i++){
		putchar(a->wsk[i]);
	}
	putchar('\n');
}
 void read_c_string(c_string* res){

	 free_c_string(res);
	 init_c_string(res);
	char litera = 'a';
	while(litera!='\n'){
		litera = getchar();
		if(litera!='\n') push_c_string(res,litera);
	}
}
