#include "student.h"
#include "vendingMachine.h"
#include "groupOff.h"
#include "MPRNG.h"

#include <iostream>

extern MPRNG mprng;

using namespace std;

void Student::main() {
	prt.print(Printer::Student, 'S', favorite, num_sodas);
    cout << "student7"  << endl;
	for (unsigned int i = 0; i < num_sodas;) {
    	cout << "student8"  << endl;
		yield(mprng(1,10));
		cout << "student8.5"  << endl;
		while(true) {
			try {
				if(fcard.available()) {
					try {
    					cout << "student9"  << endl;
						vm->buy(favorite, *fcard());
						prt.print(Printer::Student, 'B', giftCard()->getBalance());
					} catch (WATCardOffice::Lost l) {
						prt.print(Printer::Student, 'L');
						fcard = cardOffice.create(id, 5);
						continue;
					} catch (VendingMachine::Funds f) {
						fcard = cardOffice.transfer(id,  vm->cost() + 5, fcard());
						break;
					}
				}
				else if(giftCard.available()) {
					cout << "student10"  << endl;
					vm->buy(favorite, *giftCard());
					cout << "student12"  << endl;
					prt.print(Printer::Student, 'G', giftCard()->getBalance());
					cout << "student13"  << endl;
					giftCard.reset();
				}
				cout << "student11"  << endl;
			} catch (VendingMachine::Stock s) {
				vm = nameServer.getMachine(id);
				prt.print(Printer::Student, 'V', vm->getId());
				break;
			}
			i++;
			break;
		}
	}
	prt.print(Printer::Student, 'F');
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
         unsigned int id, unsigned int maxPurchases ): prt(prt), nameServer(nameServer), cardOffice(cardOffice),
         											   groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
    
    cout << "student1"  << endl;
    num_sodas = mprng(1, maxPurchases);
    cout << "student2"  << endl;
    favorite = static_cast<VendingMachine::Flavours>(mprng(VendingMachine::NUM_FLAVOURS-1));
    cout << "student3"  << endl;
    fcard = cardOffice.create(id, 5);
    cout << "student4"  << endl;
    giftCard = groupoff.giftCard();
    cout << "student5"  << endl;
    vm = nameServer.getMachine(id);
    cout << "student6"  << endl;

}