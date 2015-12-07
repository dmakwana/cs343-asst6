#include "vendingMachine.h"
#include <iostream>

void VendingMachine::main() {
	prt.print(Printer::Vending, id, 'S', sodaCost);
	for ( ;; ){
		_Accept(~VendingMachine) {
			break;
		} or _Accept(inventory) {
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
			bench.signalBlock();
		}
	}
	prt.print(Printer::Vending, id, 'F');
}

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    		   unsigned int maxStockPerFlavour): prt(prt), nameServer(nameServer), id(id),
                    		   									 sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour),
                    		   									 stocked(true) {
    stock = new unsigned int[NUM_FLAVOURS]();
    nameServer.VMregister(this);
}

VendingMachine::~VendingMachine() {
	delete[] stock;
}

void VendingMachine::buy(Flavours flavour, WATCard &card) {
	curr_flavour = flavour;
	curr_card = &card;
	bench.wait();
	prt.debug("before:");
	prt.debug(std::to_string(stock[flavour]));
	if (!funds) {
		_Throw Funds();  
	}
	if (!stocked) {
		_Throw Stock();
	}
	if (stock[flavour]) {
		stock[flavour]--;
	} else {
		prt.debug("trying to decrement 0 stock");
	}
	card.withdraw(sodaCost);
	prt.print(Printer::Vending, id, 'B', flavour, stock[flavour]);
}

unsigned int *VendingMachine::inventory() {
	//prt.print(Printer::Vending, id, 'r');
	return stock;
}

void VendingMachine::restocked() {
	prt.print(Printer::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	 return id;
}