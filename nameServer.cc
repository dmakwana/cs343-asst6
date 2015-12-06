#include "nameServer.h"

void NameServer::main() {
	int vm_id = 0;
	for (unsigned int i = 0; i < numStudents; i++) {
		students[i] = vm_id;
		vm_id = (vm_id + 1) % numVendingMachines; 
	}
}

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents): prt(prt), 
																								 numVendingMachines(numVendingMachines),
																								 numStudents(numStudents),
																								 registered(0) {
	machineList = new VendingMachine*[numVendingMachines];
	students = new unsigned int[numStudents];
}

NameServer::~NameServer() {
	delete machineList;
	delete students;
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
	machineList[registered] = vendingmachine;
	registered++;
}

VendingMachine *NameServer::getMachine(unsigned int id) {
	VendingMachine *vm = machineList[students[id]];
	students[id] = (students[id] + 1) % numVendingMachines;
	return vm;   
}

VendingMachine **NameServer::getMachineList() {
	return machineList;
}