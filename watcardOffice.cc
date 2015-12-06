#include "watcardOffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ): prt(prt), bank(bank), numCouriers(numCouriers) {}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	return WATCard::FWATCard();
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	return WATCard::FWATCard();
}

Job *WATCardOffice::requestWork() {
	return &Job();
}