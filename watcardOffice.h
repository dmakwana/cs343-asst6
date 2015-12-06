#pragma once
#include "watcard.h"
#include "bank.h"
#include "printer.h"
#include <queue>

using std::queue;

_Task WATCardOffice {
    Printer &prt;
    Bank &bank;
    unsigned int numCouriers; 
    struct Job {                           // marshalled arguments and return future
        struct Args {
            unsigned int sid;
            unsigned int amount;
            bool newWatcard;
            Args(unsigned int sid, unsigned int amount, bool newWatcard);
        };
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job(Args args);
    };
    queue<Job*> jobs;
    _Task Courier {
        Bank &bank;
        WATCardOffice &cardOffice
        void main();
        Courier(Bank &bank, WATCardOffice &cardOffice);
    };                 // communicates with bank
    vector<Courier*> couriers;
    void main();
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};
