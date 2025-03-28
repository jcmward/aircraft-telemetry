#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <ctime>

using namespace std;

const char FIELD_DELIMITER = ',';
const char RECORD_DELIMITER = ',';
const char* const HEADER = "FUEL TOTAL QUANTITY,";
const char* const TIMESTAMP_FORMAT = "%d_%m_%Y %H:%M:%S";

// TODO: maybe add a calculated fuel consumption?
struct TelemetryDataPoint {
    struct tm timestamp;
    double fuelRemaining;
};

bool parseFirstLine(string& line, TelemetryDataPoint& dataPoint, const char* header);

bool parseTelemetryData(const string& line, TelemetryDataPoint& dataPoint);

bool parseTimestamp(const string& timestampStr, struct tm& timeStruct, const char* format);

string trim(const string& str);

#endif // PARSE_H

