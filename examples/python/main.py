#!/usr/bin/env python3
"""
UDP Logger Sample for Python

This module provides a Python implementation of the UDP logger
that is compatible with the LogViewer application.
"""

import socket
import time
import os
from datetime import datetime
from typing import Optional


class UDPLogger:
    """UDP Logger class for sending log messages to LogViewer"""
    
    def __init__(self, host: str = "localhost", port: int = 1024):
        """
        Initialize UDP Logger
        
        Args:
            host: Target hostname (default: localhost)
            port: Target port (default: 1024)
        """
        self.host = host
        self.port = port
        self.socket: Optional[socket.socket] = None
        
    def open(self) -> bool:
        """
        Open UDP connection
        
        Returns:
            True if successful, False otherwise
        """
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            return True
        except Exception as e:
            print(f"Failed to create socket: {e}")
            return False
    
    def close(self) -> None:
        """Close UDP connection"""
        if self.socket:
            self.socket.close()
            self.socket = None
    
    def send(self, message: str) -> bool:
        """
        Send log message to LogViewer
        
        Args:
            message: Log message to send
            
        Returns:
            True if successful, False otherwise
        """
        if not self.socket:
            return False
            
        try:
            # Get current timestamp with microsecond precision
            now = datetime.now()
            pid = os.getpid()
            
            # Format timestamp components
            date_str = now.strftime("%Y-%m-%d")
            time_str = now.strftime("%H:%M:%S")
            microseconds = now.microsecond
            
            # Create message in the format expected by LogViewer
            # Format: <pid>PID<d>DATE<t>TIME<us>MICROSECONDS<m>MESSAGE
            formatted_message = (
                f"<pid>{pid}"
                f"<d>{date_str}"
                f"<t>{time_str}"
                f"<us>{microseconds:06d}"
                f"<m>{html_encode(message)}"
            )
            
            # Send UDP message
            self.socket.sendto(
                formatted_message.encode('utf-8'),
                (self.host, self.port)
            )
            return True
            
        except Exception as e:
            print(f"Failed to send message: {e}")
            return False


def html_encode(text: str) -> str:
    """
    Encode HTML special characters
    
    Args:
        text: Input text to encode
        
    Returns:
        HTML-encoded text
    """
    replacements = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&apos;'
    }
    
    result = text
    for char, encoded in replacements.items():
        result = result.replace(char, encoded)
    
    return result


def main():
    """Main function demonstrating UDP logger usage"""
    
    # Create logger instance
    logger = UDPLogger()
    
    if not logger.open():
        print("Failed to initialize UDP logger")
        return
    
    print("Sending log messages to LogViewer...")
    
    # Sample messages to send
    messages = [
        "Python application started",
        "Initializing database connection",
        "Loading configuration file",
        "Starting main processing loop",
        "Warning: Memory usage is high",
        "Processing user request #12345",
        "Error: Network timeout occurred",
        "Retrying failed operation",
        "Operation completed successfully",
        "Python application shutting down"
    ]
    
    try:
        for i, message in enumerate(messages, 1):
            log_message = f"[{i:02d}] {message}"
            
            if logger.send(log_message):
                print(f"Sent: {log_message}")
            else:
                print(f"Failed to send: {log_message}")
            
            # Wait 1 second between messages for demonstration
            time.sleep(1.0)
            
    except KeyboardInterrupt:
        print("\nInterrupted by user")
    
    finally:
        logger.close()
        print("Logger closed. All messages sent!")


if __name__ == "__main__":
    main()
