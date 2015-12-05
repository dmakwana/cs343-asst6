#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

Parent::main() {
	for (;;) {
		_Accept(~Parent) {
			break;
		} _Else {					// busy-waiting for call to its destructor
			unsigned int randStudent = mprng(numStudents-1);
			unsigned int randAmount = mprng(1,3);
			yield(parentalDelay);
			bank.deposit(randStudent, randAmount);
		}
	}
}

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
	prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}
