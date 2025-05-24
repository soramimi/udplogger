package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

type UDPLogger struct {
	conn *net.UDPConn
	addr *net.UDPAddr
}

// NewUDPLogger creates a new UDP logger instance
func NewUDPLogger(host string, port int) (*UDPLogger, error) {
	addr, err := net.ResolveUDPAddr("udp", fmt.Sprintf("%s:%d", host, port))
	if err != nil {
		return nil, err
	}

	conn, err := net.DialUDP("udp", nil, addr)
	if err != nil {
		return nil, err
	}

	return &UDPLogger{
		conn: conn,
		addr: addr,
	}, nil
}

// Send sends a log message in the format expected by LogViewer
func (l *UDPLogger) Send(message string) error {
	now := time.Now()
	processID := os.Getpid()

	// Format timestamp to match C++ logger format
	date := now.Format("2006-01-02")
	timeStr := now.Format("15:04:05.000000")

	// Create XML-like message format that matches the C++ logger
	logMessage := fmt.Sprintf("<pid>%d<d>%s<t>%s<m>%s",
		processID, date, timeStr, htmlEncode(message))

	_, err := l.conn.Write([]byte(logMessage))
	return err
}

// Close closes the UDP connection
func (l *UDPLogger) Close() error {
	if l.conn != nil {
		return l.conn.Close()
	}
	return nil
}

// htmlEncode encodes special HTML characters
func htmlEncode(s string) string {
	result := ""
	for _, r := range s {
		switch r {
		case '<':
			result += "&lt;"
		case '>':
			result += "&gt;"
		case '&':
			result += "&amp;"
		case '"':
			result += "&quot;"
		case '\'':
			result += "&apos;"
		default:
			result += string(r)
		}
	}
	return result
}

func main() {
	// Create UDP logger (default: localhost:1024)
	logger, err := NewUDPLogger("localhost", 1024)
	if err != nil {
		fmt.Printf("Failed to create logger: %v\n", err)
		return
	}
	defer logger.Close()

	// Send sample messages
	messages := []string{
		"Application started",
		"Processing user request",
		"Database connection established",
		"Warning: High memory usage detected",
		"Error: Failed to connect to external API",
		"Processing completed successfully",
		"Application shutting down",
	}

	fmt.Println("Sending log messages to LogViewer...")

	for i, msg := range messages {
		err := logger.Send(fmt.Sprintf("[%d] %s", i+1, msg))
		if err != nil {
			fmt.Printf("Failed to send message: %v\n", err)
			continue
		}
		fmt.Printf("Sent: %s\n", msg)

		// Wait 1 second between messages for demonstration
		time.Sleep(1 * time.Second)
	}

	fmt.Println("All messages sent!")
}
