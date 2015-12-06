#include "vendingMachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    		   unsigned int maxStockPerFlavour): prt(prt), nameServer(nameServer), id(id),
                    		   									 sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour),
                    		   									 stocked(true) {
    stock = new unsigned int[NUM_FLAVOURS];
}

VendingMachine::~VendingMachine(){
	delete stock;
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
	if (!stocked) {
		_Accept(restocked);
	}
	if (card.getBalance() < sodaCost) {
		_Throw Funds();  
	}
	if (!stock[flavour]) {
		_Throw Stock();
	}
	stock[flavour]--;
	card.withdraw(sodaCost);
}

unsigned int *VendingMachine::inventory() {
	stocked = false;
	return stock;
}

void VendingMachine::restocked() {
	stocked = true;
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	 return id;
}