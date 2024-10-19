#!/bin/bash

# Compile the UDP server
gcc udp_server.c -o udp_server
if [ $? -eq 0 ]; then
    echo "udp_server compiled successfully."
else
    echo "Failed to compile udp_server."
    exit 1
fi

# Compile the UDP client
gcc udp_client.c -o udp_client
if [ $? -eq 0 ]; then
    echo "udp_client compiled successfully."
else
    echo "Failed to compile udp_client."
    exit 1
fi
