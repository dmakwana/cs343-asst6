#pragma once

#include <vector>
#include <string>

_Monitor Printer {
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	unsigned int numTotalCells;
	bool lineFilled;
	void printParent();
	void printGroupoff();
	void printWATOff();
	void printNameServer();
	void printTruck();
	void printBottlingPlant();
	void printVending(unsigned int id);
	void printStudent(unsigned int id);
	void printCourier(unsigned int id);
	void printCell(unsigned int id);
	void resetCellDetails();
	void flushLine(bool finished);
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    void print(Kind kind, char state);
    void print(Kind kind, char state, int value1);
    void print(Kind kind, char state, int value1, int value2);
    void print(Kind kind, unsigned int lid, char state);
    void print(Kind kind, unsigned int lid, char state, int value1);
    void print(Kind kind, unsigned int lid, char state, int value1, int value2);
  private:
  	struct Cell {
		Cell(Kind kind) : 
			set(false), kind(kind), state('x'), value1(0), value2(0) {}
		bool set;
		Kind kind;
		char state;
		unsigned int id;
		int value1;
		int value2;
	};
	std::vector<Cell> cells;
	unsigned int getIdx(Kind kind, unsigned int lid);
};
