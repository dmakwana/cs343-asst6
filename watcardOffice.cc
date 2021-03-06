#include "watcardOffice.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

WATCardOffice::Job::Job(unsigned int sid, unsigned int amount, WATCard* card) :
						sid(sid), amount(amount), card(card) {}

void WATCardOffice::Courier::main() {
	// responsible for deleting every job that it picks up
	cardOffice.prt.print(Printer::Courier, cid, 'S');
	for ( ;; ) {
		_Accept(~Courier) {
			break;
		} _Else {
			Job *job = cardOffice.requestWork(); // blocks until job avaiable
			// job found
			cardOffice.prt.print(Printer::Courier, cid, 't', job->sid, job->amount);
			WATCard *watcard = job->card;
			if (!watcard) {
				watcard = new WATCard();
				cardOffice.outstandingWATCards.push_back(watcard);
			}
			if (!mprng(5)) {			// lost the WATcard
				job->result.exception(new Lost);
			} else {
				bank.withdraw(job->sid, job->amount);
				watcard->deposit(job->amount);
				job->result.delivery(watcard);
				cardOffice.prt.print(Printer::Courier, cid, 'T', job->sid, job->amount);
			}
			delete job;
		}
	}
	cardOffice.prt.print(Printer::Courier, cid, 'F');
}

WATCardOffice::Courier::Courier(unsigned int cid, Bank &bank, WATCardOffice &cardOffice) : 
								cid(cid), bank(bank), cardOffice(cardOffice) {}

WATCardOffice::~WATCardOffice() {
	for (unsigned int i = 0; i < outstandingWATCards.size(); i++) {
		delete outstandingWATCards[i];
	}
}

void WATCardOffice::main() {
	// Create courier pool
	prt.print(Printer::WATCardOffice, 'S');
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers.push_back(new Courier(i, bank, *this));
	}
	_Accept(~WATCardOffice) {
		for (unsigned int i = 0; i < numCouriers; i++) {
			delete couriers[i];
		}
		prt.print(Printer::WATCardOffice, 'F');
	}
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	// Creates new jobs
	Job *job = new Job(sid, amount, NULL);
	jobs.push(job);
	prt.print(Printer::WATCardOffice, 'C', sid, amount);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	Job *job = new Job(sid, amount, card);
	jobs.push(job);
	prt.print(Printer::WATCardOffice, 'T', sid, amount);
	return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	if (jobs.size() == 0) {
		_Accept(WATCardOffice::create) {}
		or _Accept(WATCardOffice::transfer) {}
	}
	Job* retVal = jobs.front();
	jobs.pop();
	prt.print(Printer::WATCardOffice, 'W');
	return retVal;
}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers): 
							 prt(prt), bank(bank), numCouriers(numCouriers) {}


