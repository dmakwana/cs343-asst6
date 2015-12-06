#include "parent.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"
#include <iostream>

using namespace std;

extern MPRNG mprng;

void Parent::main() {
	prt.print(Printer::Parent, 'S');
	for (;;) {
		_Accept(~Parent) {
			break;
		} _Else {					// busy-waiting for call to its destructor
			unsigned int randStudent = mprng(numStudents-1);
			unsigned int randAmount = mprng(1,3);
			yield(parentalDelay);
			// prt.print(Printer::Parent, 'D', randStudent, randAmount);
			bank.deposit(randStudent, randAmount);
		}
	}
	prt.print(Printer::Parent, 'F');
}

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
	prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}
