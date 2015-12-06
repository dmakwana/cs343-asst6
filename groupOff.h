#pragma once
#include "printer.h"
#include "watcard.h"
#include <vector>

_Task Groupoff {
	Printer &prt;
	WATCard::FWATCard *giftCards;
	WATCard *watCards;
	std::vector<unsigned int> giftcard_id;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay; 
	unsigned int currCard;
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    ~Groupoff();
    WATCard::FWATCard giftCard();
};
