#include "watcardOffice.h"
#include "bank.h"
#include "MPRNG.h"
#include <iostream>

using namespace std;

extern MPRNG mprng;

WATCardOffice::Job::Job(unsigned int sid, unsigned int amount, WATCard* card) :
						sid(sid), amount(amount), card(card) {}

void WATCardOffice::Courier::main() {
    cout << "officeCourier" << endl;

	// responsible for deleting every job that it picks up
	cardOffice.prt.print(Printer::Courier, cid, 'S');
	for ( ;; ) {
		_Accept(~Courier) {
			break;
		} _Else {
    		cout << "officeCourier1"  << endl;
    		// cardOffice.testMethod();	
    		cout << "officeCourier2"  << endl;
			Job *job = cardOffice.requestWork(); // blocks until job avaiable
    		cout << "officeCourier3"  << endl;
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

void WATCardOffice::testMethod() {
	cout << "IN TEST" << endl;
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
	cout << "officeMain1"  << endl;
	prt.print(Printer::WATCardOffice, 'S');
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers.push_back(new Courier(i, bank, *this));
	}
	cout << "officeMain2"  << endl;
	while(true){
		_Accept(~WATCardOffice) {
			for (unsigned int i = 0; i < numCouriers; i++) {
				delete couriers[i];
			}
			prt.print(Printer::WATCardOffice, 'F');
			break;
		} or _Accept(create) {}
	 	or _Accept(transfer) {}
	 	or _Accept(requestWork) {}
	}
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
	// Creates new jobs
    cout << "officeCreate1"  << endl;

	Job *job = new Job(sid, amount, NULL);
    cout << "officeCreate2"  << endl;
	jobs.push(job);
	prt.print(Printer::WATCardOffice, 'C', sid, amount);
    cout << "officeCreate3"  << endl;
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
    cout << "officeTransfer1"  << endl;
	Job *job = new Job(sid, amount, card);
    cout << "officeTransfer2"  << endl;
	jobs.push(job);
	prt.print(Printer::WATCardOffice, 'T', sid, amount);
	return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	cout << "officeRequestWork1" << endl;

	if (jobs.size() == 0) {
		cout << "officeRequestWork2"  << endl;
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


