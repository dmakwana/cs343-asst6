#include "watcardOffice.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

void WATCardOffice::main() {
	// Create courier pool
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers.push_back(new Courier(bank, *this));
	}
	_Accept(~WATCardOffice) {
		for (unsigned int i = 0; i < numCouriers; i++) {
			delete couriers[i];
		}
		for (unsigned int i = 0; i < outstandingWATCards.size(); i++) {
			delete outstandingWATCards[i];
		}
	}
}

void WATCardOffice::Courier::main() {
	// responsible for deleting every job that it picks up
	for ( ;; ) {
		_Accept(~Courier) {
			break;
		} _Else {
			Job *job = cardOffice.requestWork(); // blocks until job avaiable
			// job found
			WATCard *watcard = job->card;
			if (!watcard) {
				watcard = new WATCard();
				cardOffice.outstandingWATCards.push_back(watcard);
			}
			job->result.reset();
			if (!mprng(5)) {			// lost the WATcard
				job->result.exception(new Lost);
			} else {
				bank.withdraw(job->sid, job->amount);
				watcard->deposit(job->amount);
				job->result.delivery(watcard);
			}
			delete job;
		}
	}
}

WATCardOffice::Courier::Courier(Bank &bank, WATCardOffice &cardOffice) : 
									 bank(bank), cardOffice(cardOffice) {}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers): 
							 prt(prt), bank(bank), numCouriers(numCouriers) {}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	// Creates new jobs
	Job *job = new Job(sid, amount, NULL);
	jobs.push(job);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	Job *job = new Job(sid, amount, card);
	jobs.push(job);
	return job->result;
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

WATCardOffice::Job::Job(unsigned int sid, unsigned int amount, WATCard* card) :
						sid(sid), amount(amount), card(card) {}


