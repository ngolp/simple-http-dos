#!/bin/bash

# CONFIG
PORT=8080
# Replace TARGET's value with your own server
TARGET=your-target-server-dot-com.com

# Compile everything
make clean
make all

# Launch HTTP server in background
./http_server $PORT &
SERVER_PID=$!
echo "Server started with PID $SERVER_PID"

# Give server time to start
sleep 1

# Optionally launch normal client
./http_client -p $TARGET $PORT

# Start DoS attack
./dos_client $TARGET $PORT

# (Optional) To stop the server manually later:
# kill $SERVER_PID
