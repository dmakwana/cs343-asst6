#include "nameServer.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents): prt(prt), 
																								 numVendingMachines(numVendingMachines),
																								 numStudents(numStudents) {};

void NameServer::VMregister(VendingMachine *vendingmachine) {

}

VendingMachine *NameServer::getMachine(unsigned int id) {

}

VendingMachine **NameServer::getMachineList() {
	
}