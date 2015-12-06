#include "printer.h"
#include <iostream>

//enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };

void Printer::resetCellDetails() {
    for (unsigned int i = 0; i < numTotalCells; i++) {
        cells[i].set = false;
    }
}

void Printer::printParent() {
	std::cout<< cells[Parent].state;
	if (cells[Parent].state == 'D') {
		std::cout<< " " << cells[Parent].value1 << "," << cells[Parent].value2;
	}
	std::cout<< "\t";
}

void Printer::printGroupoff() {
	std::cout<< cells[Groupoff].state;
	if (cells[Groupoff].state == 'D') {
		std::cout<< " " << cells[Groupoff].value1;
	}
	std::cout<< "\t";
}

void Printer::printWATOff() {
	std::cout<< cells[WATCardOffice].state;
	if (cells[WATCardOffice].state == 'C' || cells[WATCardOffice].state == 'T') {
		std::cout<< " " << cells[WATCardOffice].value1 << "," << cells[WATCardOffice].value2;
	}
	std::cout<< "\t";
}

void Printer::printNameServer() {
	std::cout<< cells[NameServer].state;
	if (cells[NameServer].state == 'R') {
		std::cout<< " " << cells[NameServer].value1;
	} else if (cells[NameServer].state == 'N') {
		std::cout<< " " << cells[NameServer].value1 << "," << cells[NameServer].value2;
	}
	std::cout<< "\t";
}

void Printer::printTruck() {
	std::cout<< cells[Truck].state;
	if (cells[Truck].state == 'P') {
		std::cout<< " " << cells[Truck].value1;
	} else if (cells[Truck].state == 'd' || 
				cells[Truck].state == 'U'  || 
				cells[Truck].state == 'D' ) {
		std::cout<< " " << cells[Truck].value1 << "," << cells[Truck].value2;
	}
	std::cout<< "\t";
}

void Printer::printBottlingPlant() {
	std::cout<< cells[BottlingPlant].state;
	if (cells[BottlingPlant].state == 'G') {
		std::cout<< " " << cells[BottlingPlant].value1;
	}
	std::cout<< "\t";
}

void Printer::printStudent(unsigned int id) {
	std::cout<< cells[id].state;
	if (cells[id].state == 'V' || cells[id].state == 'G' || cells[id].state == 'B') {
		std::cout<< " " << cells[id].value1;
	} else if (cells[id].state == 'S') {
		std::cout<< " " << cells[id].value1 << "," << cells[id].value2;
	}
	std::cout<< "\t";
}

void Printer::printVending(unsigned int id) {
	std::cout<< cells[id].state;
	if (cells[id].state == 'S') {
		std::cout << " " << cells[id].value1;
	} else if (cells[id].state == 'B') {
		std::cout << " " << cells[id].value1 << "," << cells[id].value2;
	}
	std::cout<< "\t";
}

void Printer::printCourier(unsigned int id) {
	std::cout<< cells[id].state;
	if (cells[id].state == 't' || cells[id].state == 'T') {
		std::cout<< " " << cells[id].value1 << "," << cells[id].value2;
	}
	std::cout<< "\t";
}

void Printer::printCell(unsigned int id) {
    if (id <= BottlingPlant) {
    	switch (id) {
    		case Parent:
    			printParent();
    			break;
    		case Groupoff:
    			printGroupoff();
    			break;
    		case WATCardOffice:
    			printWATOff();
    			break;
    		case NameServer:
    			printNameServer();
    			break;
    		case Truck:
    			printTruck();
    			break;
    		case BottlingPlant:
    			printBottlingPlant();
    			break;
    		default:
    			break;
    	}
    } else if (id <= BottlingPlant + numStudents) {
    	printStudent(id);
    } else if (id <= BottlingPlant + numStudents + numVendingMachines) {
    	printVending(id);
    } else {
    	printCourier(id);
    }
}

void Printer::flushLine(bool finished) {
    for (unsigned int i = 0; i < numTotalCells; i++) {
        if (cells[i].set || (finished && cells[i].state == 'F')) { 
            printCell(i);
        } else if (finished) {
            std::cout<< "...\t";
        }
    }
    std::cout<< std::endl;
    resetCellDetails();
}

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines,
				unsigned int numCouriers) :
				numStudents(numStudents),
				numVendingMachines(numVendingMachines),
				numCouriers(numCouriers) {
	numTotalCells = Student + numStudents + numCouriers + numVendingMachines;
    std::cout<< "Parent\tGroupoff\tWATOff\tNames\tTruck\tPlant\t";
    
    cells.push_back(Cell(Parent));
    cells.push_back(Cell(Groupoff));
    cells.push_back(Cell(WATCardOffice));
    cells.push_back(Cell(NameServer));
    cells.push_back(Cell(Truck));
    cells.push_back(Cell(BottlingPlant));

    for (unsigned int i = 0; i < numStudents; i++){
        std::cout<< "Stud" << i << "\t";
        cells.push_back(Cell(Student));
    }

    for (unsigned int i = 0; i < numVendingMachines; i++){
        std::cout<< "Mach" << i << "\t";
        cells.push_back(Cell(Vending));
    }

    for (unsigned int i = 0; i < numCouriers; i++){
        std::cout<< "Cour" << i << "\t";
        cells.push_back(Cell(Courier));
    }
	std::cout<< std::endl;
    
    for (unsigned int i = 0; i < numTotalCells; i++) {
        std::cout<< "*******\t";
    }
    std::cout<< std::endl;
}

void Printer::print(Kind kind, char state) {
	if (state == 'F') flushLine(false);
	cells[kind].set = true;
	cells[kind].state = state;
	if (state == 'F') flushLine(true);
}

void Printer::print(Kind kind, char state, int value1) {
	print(kind, state);
	cells[kind].value1 = value1;
}

void Printer::print(Kind kind, char state, int value1, int value2) {
	print(kind, state, value1);
	cells[kind].value2 = value2;	
}

unsigned int Printer::getIdx(Kind kind, unsigned int lid) {
	if (kind == Student) {
		return Student + lid;
	} else if (kind == Vending) {
		return Student + numStudents + lid;
	} else {
		return Student + numStudents + numVendingMachines + lid;
	}
}

// Students, Vending Machines, and Couriers
void Printer::print(Kind kind, unsigned int lid, char state) {
	unsigned int idx = getIdx(kind, lid);
	if (state == 'F') flushLine(false);
	cells[idx].set = true;
	cells[idx].state = state;
	if (state == 'F') flushLine(true);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
	print(kind, lid, state);
	cells[getIdx(kind, lid)].value1 = value1;
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
	print(kind, lid, state, value1);
	cells[getIdx(kind, lid)].value2 = value2;
}
