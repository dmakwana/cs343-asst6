#include "watcardOffice.h"

void WATCardOffice::main() {
	
}

void WATCardOffice::Courier::main() {
	
}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ): prt(prt), bank(bank), numCouriers(numCouriers) {}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	return WATCard::FWATCard();
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	return WATCard::FWATCard();
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	Args args;
	WATCardOffice::Job job(args);
	return &job;
}