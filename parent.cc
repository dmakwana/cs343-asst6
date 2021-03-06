#include "parent.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

void Parent::main() {
	prt.print(Printer::Parent, 'S');
	for (;;) {
		_Accept(~Parent) {
			prt.print(Printer::Parent, 'F');
			break;
		} _Else {					// busy-waiting for call to its destructor
			unsigned int randStudent = mprng(numStudents-1);
			unsigned int randAmount = mprng(1,3);
			yield(parentalDelay);
			prt.print(Printer::Parent, 'D', randStudent, randAmount);
			bank.deposit(randStudent, randAmount);
		}
	}
}

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
	prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}
