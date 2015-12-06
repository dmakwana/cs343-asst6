#pragma once

#include "watcard.h"
#include "printer.h"
#include "nameServer.h"
#include "config.h"

_Task VendingMachine {
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int *stock;
    WATCard *curr_card;
    bool stocked, funds;
    void main();
  public:
    enum Flavours { B, C, R, J, NUM_FLAVOURS };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
  private:
    Flavours curr_flavour;
};
