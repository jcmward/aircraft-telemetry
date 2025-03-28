/****************************************************************************
 * CSCN73060: Project VI -- Client/Server Project
 *
 * This file implements functions to parse telemetry data.  These handle:
 *      - Parsing timestamp and fuel remaining from a line
 *      - Parsing the first line (and the expected header)
 *      - Trimming leading and trailing spaces
 *
 * A separate function is needed to parse the first line due to the expected
 * header (and the slightly unusual format that includes data on the first
 * line immediately after the header).
 *
 * Here is an example from one of the given data files for context:
 * FUEL TOTAL QUANTITY,12_3_2023 14:56:47,47.865124,
 *  12_3_2023 14:56:48,47.865021,
 *  12_3_2023 14:56:49,47.864925,
 *  12_3_2023 14:56:50,47.864826,
 *  [...]
 *
 * Note that there are leading and trailing spaces in the data files, so
 * another function is used to trim those.
 *
 ****************************************************************************/

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "parse.h"

// Parse first line of data: remove header then extract first data point
// Use with HEADER constant.  Parameter exists for modularity.
bool parseFirstLine(string& line, TelemetryDataPoint& dataPoint, const char* header) {
	// Ensure the line starts with the expected header
	if (line.find(header) != 0) {
		cerr << "[ERROR] Unexpected header format in first line: " << line << endl;
		return false;
	}

	// Remove the header
	string dataPart = line.substr(strlen(header));

	// Use parseTelemetryData to extract the timestamp and fuel value
	if (!parseTelemetryData(dataPart, dataPoint)) {
		cerr << "[ERROR] Failed to parse first data point from: " << line << endl;
		return false;
	}

	return true;
}

// Parse a line of telemetry data
// Line format: " dd_mm_yyyy HH:MM:SS,fuelRemaining "
// Note the leading and trailing spaces.
bool parseTelemetryData(const string& line, TelemetryDataPoint& dataPoint) {
	string trimmedLine = trim(line);    // Remove leading/trailing spaces
	stringstream ss(trimmedLine);
	string timestampStr;
	string fuelValueStr;

	// Extract timestamp and remaining fuel from line of data
	if (getline(ss, timestampStr, FIELD_DELIMITER) && getline(ss, fuelValueStr, RECORD_DELIMITER)) {
		// Parse timestamp into struct tm
		if (!parseTimestamp(timestampStr, dataPoint.timestamp, TIMESTAMP_FORMAT)) {
			cerr << "[ERROR] Failed to parse timestamp: " << timestampStr << endl;
			return false;
		}

		// Convert fuel string to double
		char* endPtr;
		dataPoint.fuelRemaining = strtod(fuelValueStr.c_str(), &endPtr);

		// Check if conversion was successful: endPtr should point to '\0'
		if (*endPtr == '\0') {
			return true;
		} else {
			cerr << "[ERROR] Invalid fuel value: " << fuelValueStr << endl;
		}
	}

	return false;
}

// Parse timestamp into struct tm
// Timestamp is in the format "dd_mm_yyyy HH:MM:SS"
// No leading zeros are used for either time or date values.
// Use with TIMESTAMP_FORMAT constant.  Parameter exists for modularity.
bool parseTimestamp(const string& timestampStr, struct tm& timeStruct, const char* format) {
	istringstream ss(timestampStr);
	ss >> get_time(&timeStruct, format);

	if (ss.fail()) {
		return false;
	}
	return true;
}

// Trim leading and trailing spaces from a string
string trim(const string& str) {
	size_t start = str.find_first_not_of(" ");
	size_t end = str.find_last_not_of(" ");

	// If all spaces, return empty string
	if (start == string::npos || end == string::npos) {
		return "";
	}

	return str.substr(start, end - start + 1);
}

