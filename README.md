# UDP Logger

A cross-platform UDP-based logging system consisting of a C++ logging library and a Qt-based log viewer application.

## Overview

UDP Logger provides a lightweight, real-time logging solution that uses UDP communication to transmit log messages from applications to a centralized viewer. The system is designed for distributed applications and multi-process environments where real-time log monitoring is essential.

## Features

- **Cross-platform support**: Works on both Windows and Linux
- **High-precision timestamps**: Microsecond-precision timestamping
- **Structured logging**: XML-like message format with process ID, timestamp, and message content
- **Real-time viewing**: Qt-based GUI application for live log monitoring
- **HTML encoding**: Safe message encoding for special characters
- **UDP communication**: Fast, lightweight network protocol
- **Static library**: Easy integration into existing projects

## Architecture

The project consists of two main components:

### 1. Logger Library (`liblogger.pro`)
A static library that provides UDP logging functionality:
- `Logger` class for sending log messages
- Cross-platform socket implementation
- HTML encoding for message safety
- Microsecond-precision timestamp generation

### 2. LogViewer Application (`LogViewer.pro`)
A Qt-based GUI application for receiving and displaying logs:
- Real-time log reception via UDP
- Table-based log display with sorting capabilities
- Test message sending functionality
- Log clearing and management features

## Message Format

Log messages are transmitted in a structured XML-like format:
```
<pid>PROCESS_ID<d>YYYY-MM-DD<t>HH:MM:SS<us>MICROSECONDS<m>MESSAGE_CONTENT
```

Example:
```
<pid>1234<d>2025-05-24<t>14:30:15<us>123456<m>Application started successfully
```

## Building

### Prerequisites
- Qt 6.9.0 or later (for LogViewer)
- C++17 compatible compiler
- CMake or qmake

### Build Instructions

1. **Build the Logger Library:**
   ```bash
   cd udplogger
   qmake liblogger.pro
   make
   ```

2. **Build the LogViewer Application:**
   ```bash
   cd LogViewer
   qmake LogViewer.pro
   make
   ```

3. **Alternative: Use provided Makefile:**
   ```bash
   make
   ```

## Usage

### Using the Logger Library

```cpp
#include "Logger.h"

int main() {
    // Initialize the logger system (required on Windows)
    Logger::initialize();
    
    // Create logger instance
    Logger logger;
    
    // Open connection (default: localhost:1024)
    logger.open();
    
    // Send log messages
    logger.send("Application started");
    logger.send("Processing data...");
    logger.send("Operation completed");
    
    // Close connection
    logger.close();
    
    // Cleanup (required on Windows)
    Logger::cleanup();
    return 0;
}
```

### Using with Custom Host/Port

```cpp
Logger logger;
logger.open("192.168.1.100", 8080);  // Custom host and port
logger.send("Remote logging message");
```

## Configuration

### Default Settings
- **Default Port**: 1024
- **Default Host**: 127.0.0.1 (localhost)
- **Protocol**: UDP
- **Message Encoding**: UTF-8 with HTML entity encoding

### Customization
You can modify the default port by changing the `PORT` constant in `Logger.h`:
```cpp
static constexpr int PORT = 1024;  // Change to your preferred port
```

## File Structure

```
udplogger/
├── README.md                 # This file
├── liblogger.pro             # Logger library project file
├── main.cpp                  # Library test application
├── Makefile                  # Build configuration
├── include/
│   └── Logger.h              # Logger class header
├── src/
│   ├── Logger.cpp            # Logger implementation
│   ├── htmlencode.cpp        # HTML encoding utilities
│   ├── htmlencode.h          # HTML encoding header
│   └── strformat.h           # String formatting utilities
└── LogViewer/
    ├── LogViewer.pro         # Viewer application project file
    ├── main.cpp              # Application entry point
    ├── MainWindow.h/cpp      # Main window implementation
    ├── LogView.h/cpp         # Log display widget
    ├── MainWindow.ui         # UI layout file
    └── build/                # Build output directory
```

## Platform-Specific Notes

### Windows
- Requires Winsock2 library (`ws2_32.lib`)
- Uses `GetSystemTimePreciseAsFileTime()` for high-precision timestamps
- Automatically initializes/cleans up Winsock

### Linux
- Uses POSIX sockets
- Uses `gettimeofday()` for microsecond timestamps
- No additional dependencies required

## Thread Safety

The Logger class is designed to be used from a single thread. For multi-threaded applications, create separate Logger instances for each thread or implement your own synchronization.

## Performance Considerations

- UDP is connectionless and does not guarantee delivery
- Messages are sent asynchronously without blocking
- Consider message size limits (typical UDP payload: ~1400 bytes)
- High-frequency logging may cause network congestion

## Troubleshooting

### Common Issues

1. **LogViewer not receiving messages:**
   - Check firewall settings
   - Verify port 1024 is not in use by another application
   - Ensure Logger and LogViewer are using the same port

2. **Build errors:**
   - Verify Qt installation and version compatibility
   - Check that all required development tools are installed

3. **Missing timestamps or garbled messages:**
   - Ensure proper character encoding (UTF-8)
   - Check for network packet loss

