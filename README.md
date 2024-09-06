# Booking

---

# Reservation Management System

## Description

The **Reservation Management System** is a command-line based application written in C++ that allows users to manage reservations for flights, hotels, and car rentals. The system provides a simple menu-driven interface for managing customer information, booking reservations, generating tickets, and canceling bookings. It uses PostgreSQL as the backend database to store and manage all reservation-related data.

## Features

- **Customer Information Management**: Add and manage customer details.
- **Flight Registration**: Register flights for customers.
- **Ticket Generation**: Generate tickets based on flight reservations.
- **Hotel Reservation**: Book hotel reservations for customers.
- **Car Reservation**: Reserve cars for customers.
- **Cancellation and Deletion**: Cancel reservations and delete associated data.
- **Exit**: Safely exit the application.

## Technology Stack

- **Programming Language**: C++
- **Database**: PostgreSQL (via `pqxx` library)
- **File Handling**: Persistent file handling alongside the PostgreSQL database.

## Prerequisites

1. **C++ Compiler**: A working C++ compiler like GCC or Clang.
2. **PostgreSQL**: Install PostgreSQL on your system.
3. **pqxx Library**: Install the `pqxx` library to interface with PostgreSQL.

   - On Ubuntu: `sudo apt-get install libpqxx-dev`
   - On MacOS: `brew install libpqxx`

## Installation

1. **Clone the Repository**:
    ```bash
    git clone <repository-url>
    cd <project-directory>
    ```

2. **Set Up PostgreSQL**:
    - Create a PostgreSQL database for the project.
    - Update the connection details in `main.cpp` to match your PostgreSQL setup.

3. **Compile the Project**:
    ```bash
    g++ -o reservation_system main.cpp -lpqxx -lpq
    ```

4. **Run the Application**:
    ```bash
    ./reservation_system
    ```

## Usage

- After running the application, a menu will appear with options to manage customer information, make reservations, generate tickets, and more.
- Follow the on-screen prompts to perform the desired actions.
  
The application uses PostgreSQL to persistently store and manage data. For example:
- Customer information is saved in the database.
- Reservations for flights, hotels, and cars are managed through the database.

## Database Schema

Ensure you create the following tables in PostgreSQL:

```sql
CREATE TABLE customers (
    customer_id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    contact_info VARCHAR(150)
);

CREATE TABLE flights (
    flight_id SERIAL PRIMARY KEY,
    customer_id INT REFERENCES customers(customer_id),
    flight_number VARCHAR(50),
    departure_date DATE,
    destination VARCHAR(100)
);

CREATE TABLE hotels (
    hotel_id SERIAL PRIMARY KEY,
    customer_id INT REFERENCES customers(customer_id),
    hotel_name VARCHAR(100),
    check_in_date DATE,
    check_out_date DATE
);

CREATE TABLE cars (
    car_id SERIAL PRIMARY KEY,
    customer_id INT REFERENCES customers(customer_id),
    car_model VARCHAR(100),
    rental_start_date DATE,
    rental_end_date DATE
);
```

## Project Structure

```
/project-directory
│
├── main.cpp                # Main C++ source file
└── README.md               # Documentation (this file)
```

## Contributing

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a detailed explanation of your changes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

This README format provides clear instructions and is structured for use on GitHub. You can customize further based on your specific project needs!
