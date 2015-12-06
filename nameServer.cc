#include "nameServer.h"

void NameServer::main() {
	prt.print(Printer::NameServer, 'S');
	int vm_id = 0;
	for (unsigned int i = 0; i < numStudents; i++) {
		students[i] = vm_id;
		vm_id = (vm_id + 1) % numVendingMachines; 
	}
	_Accept(~NameServer) {
		prt.print(Printer::NameServer, 'F');
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
	delete[] machineList;
	delete[] students;
}

void NameServer::VMregister(VendingMachine *vendingmachine) {
	prt.print(Printer::NameServer, 'R', registered);
	machineList[registered] = vendingmachine;
	registered++;
}

VendingMachine *NameServer::getMachine(unsigned int id) {
	VendingMachine *vm = machineList[students[id]];
	students[id] = (students[id] + 1) % numVendingMachines;
	prt.print(Printer::NameServer, 'N', id, students[id]);
	return vm;   
}

VendingMachine **NameServer::getMachineList() {
	return machineList;
}