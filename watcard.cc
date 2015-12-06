#include "watcard.h"

void WATCard::deposit(unsigned int amount) {
	balance += amount;
}

void WATCard::withdraw( unsigned int amount ) {
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}

WATCard::WATCard(): balance(0) {}
