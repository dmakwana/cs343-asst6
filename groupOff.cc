#include "groupOff.h"

void Groupoff::main() {
	
}

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ): prt(prt),
																												 numStudents(numStudents),
																												 sodaCost(sodaCost),
																												 groupoffDelay(groupoffDelay) {

}

WATCard::FWATCard Groupoff::giftCard(){
	return WATCard::FWATCard();
}