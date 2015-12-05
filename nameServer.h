#pragma once

_Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};
