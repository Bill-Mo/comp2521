
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Record.h"
#include "AVLTree.h"
#include "FlightDb.h"

void ListShow(List l);
// TODO: Add your tests to this file 

/*
 * The following template is just a partial example to quickly 
 * create FlightDb for your testing.
*/
FlightDb getFlightDb_test1() {

    bool result = true;

    FlightDb fldb = DbNew();
    // Daily flights QF409 at 07:05 from SYD to MEL
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 0, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 1, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 2, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 3, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 4, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 5, 7, 05, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 6, 7, 05, 90));

    // Three flights QF419 at 08:00 from SYD to MEL
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 0, 8, 00, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 2, 8, 00, 90));
    result = DbInsertRecord(fldb, RecordNew("QF409", "SYD", "MEL", 5, 8, 00, 90));

    // Flights VA323 from MEL to BNE (Brisbane)
    result = DbInsertRecord(fldb, RecordNew("VA323", "MEL", "BNE", 1, 11, 00, 110));
    result = DbInsertRecord(fldb, RecordNew("VA323", "MEL", "BNE", 3, 11, 30, 110));
    result = DbInsertRecord(fldb, RecordNew("VA323", "MEL", "BNE", 4, 11, 00, 110));
    result = DbInsertRecord(fldb, RecordNew("VA323", "MEL", "BNE", 6, 11, 30, 110));
    
    (void) result;
    // add more flights ...

    return fldb;
}



int main(int argc, char *argv[]) {

    FlightDb db = getFlightDb_test1(); 
    //ListShow(DbFindBetweenTimes(db, 4, 7, 00, 6, 10, 00));
    assert(NULL == DbFindNextFlight(db, "SYD", 0, 7, 05));
    //ListShow(DbFindByDepartureAirportDay(db, "SYD", 0));
    //ListShow(DbFindByFlightNumber(db, "QF409"));
}

void ListShow(List l) {
    ListIterator it = ListItNew(l);
    printf("------------------------------\n");
    while (ListItHasNext(it)) {
        RecordShow(ListItNext(it));
        printf("\n");
    }
    printf("------------------------------\n");
    ListItFree(it);
}

////////////////////////////////////////////////////////////////////////

