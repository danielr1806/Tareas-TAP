// Integrantes:
// Juan Martins CI 23707563
// Daniel Rodriguez CI 24883818

#include <iostream>
#include <string>
using namespace std;

class NumeroGrande{

private:
	string num1;
	string num2;

public:
	NumeroGrande(){
		num1 = "";
		num2 = "";
	}

	void set(string a, string b){
		num1 = a;
		num2 = b;
	}

	string completar_ceros(int n){
		string ceros = "";
		for(int i = 0; i<n; i++){
			ceros += "0";
		}
		return ceros;
	}

	void rellenar(string &numero, int n){
		string ceros = completar_ceros(n);
		numero = ceros + numero;
	}

	string mult10(string numero, int n){
		string ceros = completar_ceros(n);
		numero += ceros;
		return numero;
	}

	string trim(string a)   // for removing leading 0s
	{
		string res="";
		int i=0;

		while(a[i]=='0') //Se omiten los 0
		i++;

		for(;i<a.size();i++)
		res+=a[i];

		if(res.length() == 0){
			return "0";
		}

		return res;
	}

	string suma(string a, string b){
		//Rellena el string a si es menor que b y viceversa
		if(a.length() > b.length()) rellenar(b, a.length() - b.length());
		else rellenar(a, b.length() - a.length());

		int al=a.size()-1;
		int bl=b.size()-1;

		//Variable de acarreo
		int carry=0;
		string result="";

		while(al>=0 && bl>=0){
			int temp = (int)(a[al] - '0') + (int)(b[bl] - '0') + carry ; //Se suman ambos digitos y el acarreo
			carry = 0;
			if(temp > 9 )
			{//Si la suma resultante es mayor a 9, se acarrea 1
			carry=1;
			temp=temp-10; //Se resta 10 para que el nuevo valor sea valido
			}
			//Agrega al resultado
			result+=char(temp + '0'); 
			al--;
			bl--;
		}
		//Si hay acarreo, se agrega un 1
		if(carry) result+="1";

		string addition="";

		for(int i=result.size()-1;i>=0;i--) addition+=result[i];   // reversing the answer

		return trim(addition);
	}

	//Invierte un string
	void reverse(string &a){
	    string aux = "";
		for(int i=a.size()-1;i>=0;i--){
	        aux+=a[i];
		}
		a = aux;
	}

	string resta(string a, string b){
		//Rellena el string a si es menor que b y viceversa
		if(a.length() > b.length()) rellenar(b, a.length() - b.length());
		else rellenar(a, b.length() - a.length());

		//Variable de acarreo
		int carry = 0;
		int digitos = b.length();
		//Variable auxiliar para retornar el resultado
		std::string c(digitos,'\n');
		
		//Inversion de los strings
		reverse(a);
		reverse(b);

		//Resto digito a digito desde d0 a dn
		//ademas de llevar el acarreo
		for (int i = 0; i < digitos; i++) {
        	int diff = (int)(a[i] - '0') - (int)(b[i] - '0') - carry;
        	if (diff < 0) {
           		diff += 10;
           		carry = 1;
        	} else {
            	carry = 0;
        	}
        	c[i] = diff + '0';
    	}
    	//Por ultimo invierto el resultado
    	//y retorno
        reverse(c);
        return c;
	}

	string mult(string a, string b){
		int n;
		string w, x, y, z, p, q, r;
		
		if(a.length() > b.length()) rellenar(b, a.length() - b.length());
		else rellenar(a, b.length() - a.length());

		if(a.length() == 1){
			return to_string(stoi(a) * stoi(b));
		}

		if(a.length() % 2 != 0) {
			a = "0" + a;
			b = "0" + b;
		}

		n = a.length()/2;

		w = a.substr(0, n);
		x = a.substr(n, a.length() - n);
		y = b.substr(0, n);
		z = b.substr(n, b.length() - n);
		//cout << w << " " << x << " " << y <<" " << z << endl;
		p = mult(w, y);
		q = mult(x, z);
		r = mult(suma(w,x), suma(y,z));
		//cout << p << " " << q << " " << r << endl;
		r = resta(r, suma(p,q));
		r = mult10(r, n);
		p = mult10(p, n*2);
		//cout << p << " + " << r << " + " << q << endl;
		r = suma(suma(p, r), q);
		//cout << "res " << r <<endl;
		return r;
	}

	string res(){
		return mult(num1, num2); 
	}
};

int main(){
	string a, b;

	cin >> a;
	cin >> b;

	NumeroGrande Res;
	Res.set(a, b);

	cout << Res.res() << endl;

	return 0;
}