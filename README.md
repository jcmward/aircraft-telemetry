# Real-Time Flight Telemetry Monitor

## Overview
This is a client-server implementation of an aircraft telemetry system, built for a CS project course.  The server reads telemetry data, verifies that it matches the expected format, and parses it to extract fuel data, then calculates the total fuel consumption for each flight.

## Testing
Apart from implementation, a key goal of the project was to performance-test the system (using Windows Batch scripts and Visual Studio Performance Profiler), and subsequently refactor to improve its performance.

## Performance Improvements
Several performance enhancements were made following testing.  These include:
- Increasing the server's data buffer size
- Using a C++17 `string_view` for marginally more efficient buffer handling
- Removing unnecessary print statements (the major bottleneck)

These changes substantially reduced CPU and memory utilization.

## Authors
Developed by [Jon Ward](https://github.com/jcmward) and [Kahan Desai](https://github.com/Kahan-CS).

