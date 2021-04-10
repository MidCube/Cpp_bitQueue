template<int i> struct amIPrime {
	static constexpr bool prime = isPrime(i);
}

bool isPrime(int i) {
	bool prime = true;
	if (i<=1) {
		prime = false;
	} else {
		for(int j=2;j<=i/2 + 1;j++) {
			if(i%j==0) {
				prime = false;
				break;
			}
		}
	}
	return prime;
}

int main() {
    
    bool xPrime = amIPrime<2>::prime;
	bool yPrime = amIPrime<10>::prime
    return 0;
}