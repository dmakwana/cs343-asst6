#include "groupOff.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Groupoff::main() {
    prt.print(Printer::Groupoff, 'S');
    for (unsigned int i = 0; i < numStudents; i++) {
        _Accept(giftCard);
    }
    while (true) {
        _Accept(~Groupoff) {
            prt.print(Printer::Groupoff, 'F');
            break;
        } _Else {
            yield(groupoffDelay);
            if (giftcard_id.empty()) {
                break;
            }
            unsigned int id = mprng(giftcard_id.size()-1);
            giftcard_id.erase(giftcard_id.begin() + id);
            prt.print(Printer::Groupoff, 'D', sodaCost);
            giftCards[id].delivery(&watCards[id]);
        }
    }
}

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost,
                   unsigned int groupoffDelay): prt(prt),
                                                numStudents(numStudents),
                                                sodaCost(sodaCost),
                                                groupoffDelay(groupoffDelay),
                                                currCard(0) {
    giftCards = new WATCard::FWATCard[numStudents];
    watCards = new WATCard[numStudents];
    for (unsigned int i = 0; i < numStudents; i++) {
        watCards[i].deposit(sodaCost);
        giftcard_id.push_back(i);
    }
}

Groupoff::~Groupoff() {
    delete[] giftCards;
    delete[] watCards;
}

WATCard::FWATCard Groupoff::giftCard() {
    currCard++;
    return giftCards[currCard - 1];
}