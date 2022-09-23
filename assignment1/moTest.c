#include <stdio.h>
#include <string.h>

#include "List.h"
#include "Record.h"
#include "AVLTree.h"

int compareByDepartureAirportDay(Record r1, Record r2);

int main (void) {
    Record r1 = RecordNew("QF409", "SYD", "MEL", 0, 7, 05, 90);
    Tree t = TreeNew(compareByDepartureAirportDay);
    TreeInsert(t, r1);
    
    return 0;
}

int compareByDepartureAirportDay(Record r1, Record r2) {
    int diffDAirport = strcmp(RecordGetDepartureAirport(r1), RecordGetDepartureAirport(r2));
    if (diffDAirport) {
        return diffDAirport;
    } else {
        int diffDay = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
        if (diffDay) {
            return diffDay;
        } else {
            int diffHour = RecordGetDepartureHour(r1) - RecordGetDepartureMinute(r2);
            if (diffHour) {
                return diffHour;
            } else {
                int diffMinute = RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
                if (diffMinute) {
                    return diffMinute;
                } else {
                    return strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
                }
            }
        }
    }
}
