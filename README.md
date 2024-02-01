# SimuTradeX
## Simulate. Trade. Exchange.
SimuTradeX is a C++ based simulation platform designed for testing and demonstrating the functionalities of a trading order book system. This system includes a matching engine that processes buy and sell orders, maintaining an order book for each trading symbol. It's equipped with a simple user interface via the command line, where users can input orders, display order books for specific symbols, and access help for using the system.

## Features
- **Order Book Management:** Allows adding, showing, and matching orders (buy/sell) based on price and quantity.
- **Matching Engine:** A continuous loop that matches buy and sell orders from the order book.
- **Command Line Interface:** Interact with the system using commands like `-h` for help, `show [symbol]` to display the order book for a symbol, and `exit` to quit the program.

## How to Build and Run
Ensure you have C++ and CMake installed. Clone the repository, build the project using CMake, and then run the executable generated.

## Usage
Start the application, then follow the on-screen instructions. Enter orders by specifying symbol, price, quantity, and side (0 for BUY, 1 for SELL). Use the `show [symbol]` command to display the current order book for a symbol.

## Dependencies
- C++ compiler with support for C++11 or later
- CMake for building the project
