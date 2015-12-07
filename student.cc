#include "student.h"
#include "vendingMachine.h"
#include "groupOff.h"
#include "MPRNG.h"

#include <iostream>

extern MPRNG mprng;

using namespace std;

void Student::main() {
    prt.debug("student7"  );
	for (unsigned int i = 0; i < num_sodas;) {
    	prt.debug("student8"  );
		yield(mprng(1,10));
		prt.debug("student8.5"  );
		while(true) {
			try {
				if(fcard.available()) {
					try {
    					prt.debug("student9"  );
						vm->buy(favorite, *fcard());
						prt.print(Printer::Student, id, 'B', giftCard()->getBalance());
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
				else if(giftCard.available()) {
					prt.debug("student10"  );
					vm->buy(favorite, *giftCard());
					prt.debug("student12"  );
					prt.print(Printer::Student, id, 'G', giftCard()->getBalance());
					prt.debug("student13"  );
					giftCard.reset();
					i++;
					break;
				}
				// prt.debug("student11"  );
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
    
    prt.debug("student1"  );
    num_sodas = mprng(1, maxPurchases);
    prt.debug("student2"  );
    favorite = static_cast<VendingMachine::Flavours>(mprng(VendingMachine::NUM_FLAVOURS-1));
    prt.debug("student3"  );
    fcard = cardOffice.create(id, 5);
    prt.debug("student4"  );
    giftCard = groupoff.giftCard();
    prt.debug("student5"  );
    vm = nameServer.getMachine(id);
    prt.print(Printer::Student, id, 'S', favorite, num_sodas);
    prt.print(Printer::Student, id, 'V', vm->getId());
    prt.debug("student6"  );

}