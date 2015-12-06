#include "watcardOffice.h"
#include <queue>

void WATCardOffice::main() {
	// Create courier pool
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers.push_back(new Courier(bank));
	}
}

void WATCardOffice::Courier::main() {
	for ( ;; ) {
		_Accept(~Courier) {
			break;
		} _Else {
			Job *job = requestWork(); // blocks until job avaiable
			
		}

	}
}

void WATCardOffice::Courier::Courier(Bank &bank, WATCardOffice &cardOffice) :
								 	 bank(bank), cardOffice(cardOffice) {}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers): 
							 prt(prt), bank(bank), numCouriers(numCouriers) {}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {

	return WATCard::FWATCard();
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	return WATCard::FWATCard();
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	if (jobs.size() == 0) {
		_Accept(WATCardOffice::create) {}
		or _Accept(WATCardOffice::transfer) {}
	}
	Job* retVal = jobs.front();
	jobs.pop();
	return retVal;
}

WATCardOffice::Job::Job(Args args) : args(args) {}

WATCardOffice::Job::Args::Args(unsigned int sid, unsigned int amount, bool newWatcard) : 
                 			   sid(sid), amount(amount), newWatcard(newWatcard) {}