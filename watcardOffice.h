#pragma once

#include "watcard.h"
#include "bank.h"
#include "printer.h"

#include <queue>
#include <vector>

using std::queue;
using std::vector;

_Task WATCardOffice {
    Printer &prt;
    Bank &bank;
    unsigned int numCouriers; 
    struct Job {                           // marshalled arguments and return future
        unsigned int sid;
        unsigned int amount;
        WATCard *card;
        WATCard::FWATCard result;          // return future
        Job(unsigned int sid, unsigned int amount, WATCard* card);
    };
    queue<Job*> jobs;
    _Task Courier {
        Bank &bank;
        WATCardOffice &cardOffice;
      public:
        void main();
        Courier(Bank &bank, WATCardOffice &cardOffice);
    };                 // communicates with bank
    vector<Courier*> couriers;
    vector<WATCard*> outstandingWATCards;
    void main();
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers);
    WATCard::FWATCard create(unsigned int sid, unsigned int amount);
    WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard *card);
    Job *requestWork();
};
