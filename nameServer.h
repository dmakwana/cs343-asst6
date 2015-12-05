#pragma once
#include "VendingMachine.h"

_Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	VendingMachine **machineList;
	unsigned int *students;
	unsigned int registered;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};
