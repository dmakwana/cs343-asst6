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
						prt.print(Printer::Student, id, 'B', fcard()->getBalance());
						i++;
						break;
					} catch (WATCardOffice::Lost l) {
						prt.print(Printer::Student, id, 'L');
						fcard = cardOffice.create(id, 5);
						continue;
					} catch (VendingMachine::Funds f) {
						fcard = cardOffice.transfer(id,  vm->cost() + 5, fcard());
						break;
					}
				}
				if(giftCard.available()) {
					vm->buy(favorite, *giftCard());
					prt.print(Printer::Student, id, 'G', giftCard()->getBalance());
					giftCard.reset();
					i++;
					break;
				}
			
			} catch (VendingMachine::Stock s) {
				vm = nameServer.getMachine(id);
				prt.print(Printer::Student, id, 'V', vm->getId());
				break;
			}
		}
	}
	prt.print(Printer::Student, id, 'F');
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
         unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),
         											   groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
    num_sodas = mprng(1, maxPurchases);
    favorite = static_cast<VendingMachine::Flavours>(mprng(VendingMachine::NUM_FLAVOURS-1));
    fcard = cardOffice.create(id, 5);
    giftCard = groupoff.giftCard();
    vm = nameServer.getMachine(id);
    prt.print(Printer::Student, id, 'S', favorite, num_sodas);
    prt.print(Printer::Student, id, 'V', vm->getId());
}