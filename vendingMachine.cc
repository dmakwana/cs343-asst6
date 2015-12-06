#include "vendingMachine.h"

void VendingMachine::main() {
	_Accept(inventory) {
		_Accept(restocked);
	} or _Accept(buy){
		if (curr_card->getBalance() < sodaCost) {
			funds = false;
		} else {
			funds = true;
		}
		if (!stock[curr_flavour]) {
			stocked = false;
		} else {
			stocked = true;
		}
	}
}

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    		   unsigned int maxStockPerFlavour): prt(prt), nameServer(nameServer), id(id),
                    		   									 sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour),
                    		   									 stocked(true) {
    stock = new unsigned int[NUM_FLAVOURS];
}

VendingMachine::~VendingMachine(){
	delete[] stock;
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
	curr_flavour = flavour;
	curr_card = &card;
	if (!funds) {
		_Throw Funds();  
	}
	if (!stocked) {
		_Throw Stock();
	}
	stock[flavour]--;
	card.withdraw(sodaCost);
}

unsigned int *VendingMachine::inventory() {
	return stock;
}

void VendingMachine::restocked() {
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	 return id;
}