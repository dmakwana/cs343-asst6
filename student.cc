#include "student.h"
#include "vendingMachine.h"
#include "groupOff.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Student::main() {
	for (unsigned int i = 0; i < num_sodas;) {
		yield(mprng(1,10));
		while(true) {
			try {
				if(fcard.available()) {
					try {
						vm->buy(favorite, *fcard());
					} catch (WATCardOffice::Lost l) {
						fcard = cardOffice.create(id, 5);
						continue;
					} catch (VendingMachine::Funds f) {
						fcard = cardOffice.transfer(id,  vm->cost() + 5, fcard());
						break;
					}
				}
				else if(giftCard.available()) {
					vm->buy(favorite, *giftCard());
					giftCard.reset();
				}
			} catch (VendingMachine::Stock s) {
				vm = nameServer.getMachine(id);
				break;
			}
			i++;
			break;
		}
	}
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
         unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),
         											   groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
    
    num_sodas = mprng(1, maxPurchases);
    favorite = static_cast<VendingMachine::Flavours>(mprng(VendingMachine::NUM_FLAVOURS-1));
    fcard = cardOffice.create(id, 5);
    giftCard = groupoff.giftCard();
    vm = nameServer.getMachine(id);

}