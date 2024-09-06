#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <pqxx/pqxx>
using namespace std;
// Options menu
void MENU_BAR()
{

    cout << "\n\n\n";
    cout << endl;
    cout << "\t\t\t\t\t\t *******************************************";
    cout << endl;
    cout << "\t\t\t\t\t FLIGHT RESERVATION & HOTEL BOOKING & CAR RESERVATION";
    cout << endl;
    cout << "\t\t\t\t\t\t *******************************************";

    cout << endl;
    cout << endl;

    cout << "\t\t\t\t\t 1 => Customer Information.";
    cout << endl;

    cout << "\t\t\t\t\t 2 => Flight Registration.";
    cout << endl;

    cout << "\t\t\t\t\t 3 => Ticket Generation.";
    cout << endl;

    cout << "\t\t\t\t\t 4 => Hotel Reservation.";
    cout << endl;

    cout << "\t\t\t\t\t 5 => Car Reservation.";
    cout << endl;

    cout << "\t\t\t\t\t 6 => Cancel reservation and delete the information.";
    cout << endl;

    cout << "\t\t\t\t\t 7 => Exit.";
    cout << endl;\

    cout << "\n Choose Option: ";
}



// Saves and shows customer private information.
class Customer
{
protected:

    string first_name;
    string last_name;
    int age;
    int passport_id;
    string nationality;
    char gender;

public:

    Customer () : first_name(""),last_name(""),age(0),passport_id(0),nationality(""),gender('0'){}

    friend class Ticket_Gen;
    friend class car;
    friend class Hotel_Booking;

    friend istream &operator >> (istream& in, Customer& cust);
    friend ostream &operator << (ostream& out, Customer& cust);

    bool operator ==(const Customer& c)
    {
        if(first_name == c.first_name && last_name == c.last_name && age == c.age  && passport_id == c.passport_id && nationality == c.nationality && gender == c.gender)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};



// cin for customer - istream operator overloader
istream& operator >> (istream& in, Customer& cust)
{
    cout << "Enter first name:  ";
    in >> cust.first_name;
    char a = cust.first_name[0];
    cust.first_name[0] = a;
    cout << endl;

    cout << "Enter last name:  ";
    in >> cust.last_name;
    char b = cust.last_name[0];
    cust.last_name[0] = b;
    cout << endl;

    cout << "Enter age:  ";
    in >> cust.age;
    cout << endl;

    cout << "Enter Nationality:  ";
    in >> cust.nationality;
    char c = cust.nationality[0];
    cust.nationality[0] = c;
    cout << endl;

    cout << "Enter Passport ID:  ";
    in >> cust.passport_id;
    cout << endl;

    cout << "Enter gender(M/F):  ";
    in >> cust.gender;

    return in;
}

//cout for customer class - - istream operator overloader
ostream& operator << (ostream& out, Customer& cust)
{
    out << "Customer Details preview.";
    out << endl;
    out << endl;
    out << "Customer Name: " << cust.first_name << " " << cust.last_name;
    out << endl;
    out << "Customer Age: " << cust.age;
    out << endl;
    out << "Customer Passport ID: " << cust.passport_id;
    out << endl;
    out << "Customer Nationality: " << cust.nationality;
    out << endl;
    out << "Customer gender: " << cust.gender;
    out << endl;

    return out;
}


// Saves flight details.
class Flight_Details
{
protected:

    int Destination;
    int Departure;
    int Departure_time;
    int Seat_Class;

    string airline;
    string departure;
    string arrival;
    string departureTime;
    string arrivalTime;
    double price;

    string name;
    string location;
    string price_1;
    string rating;

public:
    Flight_Details() {}

    int flightNumber;
    vector<pqxx::result::const_iterator> flights;
    void storeFlightData(const string& airline, const string& departure, const string& arrival, const string& departureTime, const string& arrivalTime, double price)
    {
        this->airline = airline;
        this->departure = departure;
        this->arrival = arrival;
        this->departureTime = departureTime;
        this->arrivalTime = arrivalTime;
        this->price = price;
    }

    void storeHotelData(const string &hotelName, const string &address, const string &phoneNumber, string basicString)
    {
        this->name = name;
        this->location = location;
        this->price_1 = price_1;
        this->rating = rating;
    }


    friend class Ticket_Gen;
    friend class car;
    friend class Hotel_Booking;

// Overloading cin and cout operators.
    friend istream& operator >> (istream& in, Flight_Details& fd);
    friend ostream& operator << (ostream& out, Flight_Details& fd);

// Overloading == operator.
    bool operator == (const Flight_Details& f) const
    {
        if(Destination == f.Destination && Departure == f.Departure && Departure_time == f.Departure_time && Seat_Class == f.Seat_Class)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


};



istream &operator >> (istream& in, Flight_Details& fd)
{
    vector<pqxx::result::const_iterator> flights;

    while (flights.empty()) {
        system("clear");
        cout << "\t\t\t***********************************";
        cout << endl;
        cout << "\t\t\t Available Flight Destinations.";
        cout << endl;
        cout << "\t\t\t*********************************** ";
        cout << endl;

        string departureAirportPart1, departureAirportPart2;
        cout << "Enter your departure airport: ";
        in >> departureAirportPart1;
        getline(in, departureAirportPart2);
        string departureAirport = departureAirportPart1 + (departureAirportPart2.empty() ? "" : departureAirportPart2);
        cout << endl;

        string destinationAirportPart1, destinationAirportPart2;
        cout << "Enter your destination airport: ";
        in >> destinationAirportPart1;
        getline(in, destinationAirportPart2);
        string destinationAirport = destinationAirportPart1 + (destinationAirportPart2.empty() ? "" : destinationAirportPart2);
        cout << endl;

        try {
            pqxx::connection c("dbname=flights user=postgres password=1212 hostaddr=127.0.0.1 port=5432");
            if (c.is_open()) {
                pqxx::work W(c);

                pqxx::result R = W.exec("SELECT * FROM Flights WHERE Departure = " + W.quote(departureAirport) + " AND Arrival = " + W.quote(destinationAirport));
                W.commit();

                cout << "Available flights from " << departureAirport << " to " << destinationAirport << ":" << endl;
                int i = 1;
                for (auto row: R) {
                    cout << i << ". Airline: " << row[1].as<string>() << "Departure: " << row[2].as<string>() << ", Arrival: " << row[3].as<string>() << ", DepartureTime: " << row[4].as<string>() << ", ArrivalTime: " << row[5].as<string>() << ", Price: " << row[6].as<double>() << endl;
                    flights.push_back(row);
                    i++;
                }
            } else {
                cout << "Can't open database" << endl;
            }
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }

            if (flights.empty()) {
                cout << "No flights found from " << departureAirport << " to " << destinationAirport << ".\n";
                cout << "Would you like to enter another flight (Y/N)? ";
                char choice;
                in >> choice;
                if (choice == 'N' || choice == 'n') {
                    break;
                }
            }
        }

        if (!flights.empty()) {
            system("clear");

            int flightChoice;
            cout << "Choose the Number for the flight you want to book: ";
            in >> flightChoice;

            // Retrieve the chosen flight
            auto chosenFlight = flights[flightChoice - 1];

            // Store the chosen flight details in the Flight_Details object
            fd.storeFlightData(chosenFlight[1].as<string>(), chosenFlight[2].as<string>(), chosenFlight[3].as<string>(), chosenFlight[4].as<string>(), chosenFlight[5].as<string>(), chosenFlight[6].as<double>());
        }

        return in;
    }

// cout for flight_Details class - ostream operator overloader.
ostream& operator << (ostream& out, Flight_Details& fd)
{
    try {
        pqxx::connection c("dbname=flights user=postgres password=1212 hostaddr=127.0.0.1 port=5432");
        if (c.is_open()) {
            pqxx::work W(c);

            // Fetch the flight details based on the flight that the user has chosen
            pqxx::result R = W.exec("SELECT * FROM Flights WHERE Airline = " + W.quote(fd.airline)  + " AND Departure = " + W.quote(fd.departure) + " AND Arrival = " + W.quote(fd.arrival) + " AND DepartureTime = " + W.quote(fd.departureTime) + " AND ArrivalTime = " + W.quote(fd.arrivalTime) + " AND Price = " + W.quote(fd.price));
            W.commit();

            if (R.size() == 0) {
                out << "No flight found with the given departure and arrival." << endl;
                return out;
            }

            auto row = R[0];
            fd.airline = row[1].as<string>();
            fd.departure = row[2].as<string>();
            fd.arrival = row[3].as<string>();
            fd.departureTime = row[4].as<string>();
            fd.arrivalTime = row[5].as<string>();
            fd.price = row[6].as<double>();
        } else {
            out << "Can't open database" << endl;
        }
    } catch (const std::exception &e) {
        out << e.what() << endl;
    }

    out << "\t\t\t ************************************ ";
    out << endl;
    out << "\t\t\t            FLIGHT DETAILS            ";
    out << endl;
    out << "\t\t\t ************************************ ";
    out << endl;
    out << endl;

    out << "Airline: " << fd.airline;
    out << endl;

    out << "Departure: " << fd.departure;
    out << endl;

    out << "Arrival: " << fd.arrival;
    out << endl;

    out << "Departure Time: " << fd.departureTime;
    out << endl;

    out << "Arrival Time: " << fd.arrivalTime;
    out << endl;

    out << "Price: " << fd.price;
    out << endl;

    return out;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ticket_Gen : protected Customer , protected Flight_Details{
protected:
    int total;
    string time;
    int seat_price;

public:
    Ticket_Gen() : total(0),time(""),seat_price(0){}

    void gen_time(const Flight_Details& f)
    {
        // Assuming departureTime is in the format "YYYY-MM-DD HH:MM:SS"
        string departureTime = f.departureTime;

        // Extract the time part from the departureTime
        string time = departureTime.substr(11, 8); // Extracts HH:MM:SS

        // Now you can use the time variable as needed
    }

    void gen_total(const Flight_Details& f) {
        // Display the price of the flight
        cout << "Total price for flight: " << f.price << endl;
    }


// Deletes customer instance and flight_Details instance.
    static void deletion(Customer& c,Flight_Details& f)
    {

        c.first_name = "";
        c.last_name = "";
        c.age = 0;
        c.passport_id = 0;
        c.nationality = "";
        c.gender = '-';
        f.Destination = 11;
        f.Departure = 4;
        f.Departure_time = 4;
        f.Seat_Class = 3;
    }


    static void delete_customer(Customer& c)
    {
        c.first_name = "";
        c.last_name = "";
        c.age = 0;
        c.passport_id = 0;
        c.nationality = "";
        c.gender = '-';
    }


    static void delete_flight_details(Flight_Details& f)
    {
        f.Destination = 11;
        f.Departure = 4;
        f.Departure_time = 4;
        f.Seat_Class = 3;
    }

// Outputs a unique ticket with the data in a .txt file
    virtual void gen_ticket(const Customer& c,const Flight_Details& f)
    {
        static int tickets;
        ofstream Tick_File;
        string File = "Flight_Ticket_"+to_string(tickets+1)+".txt";
        Tick_File.open(File);

        Tick_File << "*******************************************************************************************************";
        Tick_File << endl;
        Tick_File << "*  ----------------------------------CUSTOMER DETAILS-----------------------------------------------";
        Tick_File << endl;
        Tick_File << "*  - First Name : "<< c.first_name << "                \n*  - Last Name : " << c.last_name << "            ";
        Tick_File << endl;
        Tick_File << "*  - Age : " << c.age << "                              \n*  - Gender : " << c.gender << "                  ";
        Tick_File << endl;
        Tick_File << "*                   \n*  - Nationality : " << c.nationality << "        ";
        Tick_File << endl;
        Tick_File << "*  - Passport ID : " << c.passport_id << "               \n*  - Customer ID : " << (tickets+1) << "                     ";
        Tick_File << endl;
        Tick_File << "*  -------------------------------------------------------------------------------------------------  ";
        Tick_File << endl;
        Tick_File << endl;
        Tick_File << "*  ---------------------------------FLIGHT INFORMATION---------------------------------------------- n";
        Tick_File << endl;
        Tick_File << "*  - " << "Departure Place : " << f.departure << "                                     ";
        Tick_File << endl;
        Tick_File << "*  - " << "Departure Time : " << f.departureTime << "                                                                  ";
        Tick_File << endl;
        Tick_File << "*  - " << "Destination Place : " << f.arrival << "                              ";
        Tick_File << endl;
        Tick_File << "*  - " << "Price : " << f.price << "                                   ";
        Tick_File << endl;
        Tick_File << "*  ------------------------------------------------------------------------------------------------- ";
        Tick_File << endl;
        Tick_File << "*******************************************************************************************************";
        Tick_File << endl;

        cout << "Your file has been saved with name Ticket_" << (tickets + 1) <<" and extension *.txt" << endl;
        tickets++;
    }
};

////////////

class car : protected Customer, protected Flight_Details{
protected:

    int car_number = 7777;
    string name[8] = {"Vlad","Vlad","Vlad","Andrij","Vlad","Vlad","Vlad","Andrij"};
    string pickup[4] = {"Main street","Airport 1","Airport 2","Airport 3"};

    string customer_number;
    string car_destination;

public:

    void get_info()
    {
        system("clear");

        cout << "\t\t\t ************************************ ";
        cout << endl;

        cout << "\t\t\t            CAR RESERVATION            ";
        cout << endl;

        cout << "\t\t\t ************************************ ";
        cout << endl;

        cout << endl;

        cout << "Enter your Contact number: ";
        cin >> customer_number;
        cout << endl;

        cout << "Enter your Dropoff place: ";
        cin >> car_destination;
        cout << endl;
    }

    // Saves car booking ticket in a .txt file.
    virtual void print(const Customer c, const Flight_Details f1)
    {
        cout<<"Booking a Car";

        static int cars;

        ofstream Car_File;
        string file = "Car_Reservation"+to_string(cars+1)+".txt";
        Car_File.open(file);

        Car_File << "*******************************************************************************************************";
        Car_File << endl;
        Car_File << "*  ----------------------------------CUSTOMER DETAILS-----------------------------------------------  ";
        Car_File << endl;
        Car_File << "*  - First Name : " << c.first_name << "                " << "\n*  - Last Name : " << c.last_name << "            ";
        Car_File << endl;
        Car_File << "*  - Age : " << c.age << "                              " << "\n*  - Gender : " << c.gender << "                  ";
        Car_File << endl;
        Car_File << "*                   " << "\n*  - Nationality : " << c.nationality<<"        \n";
        Car_File << endl;
        Car_File << "*  - Passport ID : " << c.passport_id << "               \n*  - Customer ID : " << (cars + 1) << "                     ";
        Car_File << endl;
        Car_File << "*  - Contact No :" << customer_number << "                     \n";
        Car_File << endl;
        Car_File << "*  -------------------------------------------------------------------------------------------------  ";

        Car_File << endl;
        Car_File << endl;

        Car_File << "*  ---------------------------------RIDE INFORMATION----------------------------------------------  ";
        Car_File << endl;
        Car_File << "*  - " << "Driver's Name : " << name[f1.Destination%7] << "";
        Car_File << endl;
        Car_File << "*  - " << "Pickup spot :" << pickup[f1.Destination%4] << "";
        Car_File << endl;
        Car_File << "*  - " << "Destination Place : " << car_destination << "                              ";
        Car_File << endl;
        Car_File << "*  - " << "Car number : " << car_number << "                                   ";
        Car_File << endl;
        Car_File << endl;
        Car_File << "*  NOTE : Fare would be generated according to the meter reading at the time of your ride.";
        Car_File << endl;
        Car_File << "*  ------------------------------------------------------------------------------------------------- ";
        Car_File << endl;
        Car_File << "*******************************************************************************************************";
        Car_File << endl;

        cout << endl;
        cout << "Your file has been saved with name Car_Reservation"<< (cars + 1) << " and extension *.txt";
        cout << endl;
        cars++;
    }
};


class Hotel_Booking :public car{

    int Hotel_Selection;
    int Days_booked;

    string Address;
    string phone_number;
    string Hotel_name;


public:

    Hotel_Booking() : Hotel_Selection(0),Days_booked(0){}

    vector<pqxx::result::const_iterator> hotels;

    void select_Hotel(string city) {
        // Query the hotels database for all hotels in the destination city
        try {
            pqxx::connection c("dbname=hotels user=postgres password=1212 hostaddr=127.0.0.1 port=5432");
            if (c.is_open()) {
                pqxx::nontransaction N(c);
                string sql = "SELECT * FROM hotels WHERE location = '" + city + "';";
                pqxx::result R(N.exec(sql));

                cout << "Available hotels in " << city << ":\n";
                // Store the hotels in a vector
                int i = 1;
                for (auto row: R) {
                    cout << i << ". Name: " << row[1].as<string>() << ", Location: " << row[2].as<string>() << ", Price: " << row[3].as<double>() << ", Rating: " << row[4].as<double>() << endl;
                    hotels.push_back(row);
                    i++;
                }

                int hotelSelection = -1;

                if (hotels.empty()) {
                    cout << "No hotels found in " << city << endl;
                    cout << "Would you like to enter another destination (Y/N)? ";
                    char choice;
                    cin >> choice;
                    if (choice == 'N' || choice == 'n') {
                        return;
                    }
                }
                if (!hotels.empty()) {
                    system("clear");
                    int hotelSelection;
                    cout << "Enter the number for the hotel you want to book: ";
                    cin >> hotelSelection;

                    auto chosenHotel = hotels[hotelSelection - 1];
                    std::string hotelName = chosenHotel[1].is_null() ? "" : chosenHotel[1].as<std::string>();
                    std::string address = chosenHotel[2].is_null() ? "" : chosenHotel[2].as<std::string>();
                    std::string price_1 = chosenHotel[3].is_null() ? "" : chosenHotel[3].as<std::string>();
                    std::string rating = chosenHotel[4].is_null() ? "" : chosenHotel[4].as<std::string>();

                    this->storeHotelData(hotelName, address, price_1, rating);

                    hotelSelection = 1;

                }
                if (hotelSelection != -1) {
                    // Retrieve the chosen hotel
                    auto chosenHotel = hotels[hotelSelection - 1];

                    cout << "You have chosen the hotel: " << chosenHotel[1].as<string>() << " in " << chosenHotel[2].as<string>() << " with a price of " << chosenHotel[3].as<double>() << " per night.\n";
                }
            }
        } catch (const std::exception &e) {
            cerr << e.what() << endl;
        }
    }

    // Prints the Hotel Booking receipt in a .txt file.
    void Print_Hotel (const Customer& c,const Flight_Details& f1)
    {

        int Charges_per_day = 0;
        int Total_charges = 0;


        static int hotels;
        ofstream Book_File;
        string File = "Hotel_Booking_"+to_string(hotels+1)+".txt";
        Book_File.open(File);
        // Makes form to hotel receipt.
        Book_File << "*******************************************************************************************************";
        cout << endl;
        Book_File << "*  ----------------------------------CUSTOMER DETAILS-----------------------------------------------";
        cout << endl;
        Book_File << "*  - First Name : " << c.first_name<<"                " << "\n*  - Last Name : " << c.last_name << "            ";
        cout << endl;
        Book_File << "*  - Age : " << c.age<<"                              " << "\n*  - Gender : " << c.gender << "                  ";
        cout << endl;
        Book_File << "*                   " << "\n*  - Nationality : " << c.nationality << "        \n";
        cout << endl;
        Book_File << "*  - Passport ID : " << c.passport_id << "               \n*  - Customer ID : " << hotels + 1 << "                     ";
        cout << endl;
        Book_File << "*  -------------------------------------------------------------------------------------------------";
        cout << endl;
        cout << endl;


        Book_File << "*  ---------------------------------Hotel BOOKING---------------------------------------------------";
        cout << endl;
        Book_File << "*  - Hotel Name : " << Hotel_name << " ";
        cout << endl;
        Book_File << "*  - Hotel Address : " << Address << " ";
        cout << endl;
        Book_File << "*  - Charges per day :" << Charges_per_day << " ";
        cout << endl;
        Book_File << "*  - Booked Days: " << Days_booked << " ";
        cout << endl;
        Book_File << "*  - Total Charges:" << Total_charges << "€ ";
        cout << endl;
        Book_File << "*  -------------------------------------------------------------------------------------------------";
        cout << endl;
        Book_File << "*******************************************************************************************************";
        cout << endl;
        cout << "Your hotel was booked successfully.";
        cout << endl;
        cout << "Your file has been saved with name Stay Booking_" << hotels + 1 << " and extension *.txt";
        cout << endl;

        hotels++;
    }

    // Overriding the print function
    void print(Customer c,Flight_Details f1) override
    {
        cout<<"Booking a Car";
        cout << endl;

        static int ca;
        ofstream carFile;
        string file = "car_Reservation"+to_string(ca + 1)+".txt";
        carFile.open(file);

        carFile << "*******************************************************************************************************";
        carFile << endl;
        carFile << "*  ----------------------------------CUSTOMER DETAILS-----------------------------------------------  ";
        carFile << endl;
        carFile << "*  - First Name : " << c.first_name << "                " << "\n*  - Last Name : " << c.last_name << "            ";
        carFile << endl;
        carFile << "*  - Age : " << c.age << "                              " << "\n*  - Gender : " << c.gender << "                  ";
        carFile << endl;
        carFile << "*                   " << "\n*  - Nationality : " << c.nationality << "        ";
        carFile << endl;
        carFile << "*  - Passport ID : " << c.passport_id << "               \n*  - Customer ID : " << (ca + 1) << "                     ";
        carFile << endl;
        carFile << "*  - Contact No :" << phone_number << "                     \n";
        carFile << endl;
        carFile << "*  -------------------------------------------------------------------------------------------------  ";

        carFile << endl;
        carFile << endl;

        carFile << "*  ---------------------------------RIDE INFORMATION----------------------------------------------  ";
        carFile << endl;
        carFile << endl;
        carFile << "*  - " << "Driver's Name : " << name[f1.Destination - 1] << " ";
        carFile << endl;
        carFile << "*  - " << "Pickup spot :" << pickup[f1.Destination % 7] << " ";
        carFile << endl;
        carFile << "*  - " << "Hotel Name: " << Hotel_name << " ";
        carFile << endl;
        carFile << "*  - " << "Destination Place : " << Address << "                              ";
        carFile << endl;
        carFile << "*  - " << "Car plate number : " << car_number << "                                   ";
        carFile << endl;
        carFile << endl;
        carFile << "*  ------------------------------------------------------------------------------------------------- ";
        carFile << endl;
        carFile << "*******************************************************************************************************";
        carFile << endl;
        cout << "Your ride is booked from the airport to " << Address;
        cout << endl;

        cout << "Your file has been saved with name Car_Reservation" << (ca + 1) << " and extension *.txt";
        cout << endl;
        ca++;
    }
};



int main()
{
    Ticket_Gen t1;

    Customer ci1;
    Flight_Details fd1;

    Customer ci2;
    Flight_Details fd2;

    car cb1;

    Hotel_Booking hb1;
    Hotel_Booking hb2;

    car *cb2ptr;
    cb2ptr = &hb1;

    string hotel_city;

    try {
        pqxx::connection c("dbname=flights user=postgres password=1212 hostaddr=127.0.0.1 port=5432");
        if (c.is_open()) {
            std::cout << "Opened database successfully: " << c.dbname() << endl;
            pqxx::work W(c);

            pqxx::result R = W.exec("SELECT * FROM Flights where  flights.flightid > 1 and flights.flightid < 100");
            W.commit();

            for (auto row: R) {
                for (auto field: row) {
                    std::cout << field.c_str() << '\t';
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    cout << "********************** Welcome To Andrew's Airline Tickets Reservation  **********************";
    cout << endl;

    while (true){
        int command;
        MENU_BAR();
        cin >> command;
        switch (command)
        {


            case 1:

                char sur;
                do
                {

                    system("clear");
                    cin >> ci1;
                    cout << endl;
                    cout << endl;
                    cout << ci1;
                    cout << "Are you sure that you want to continue with this preview?(Y/N)";
                    cout << endl;
                    cin >> sur;
                }
                while(sur == 'N' || sur == 'n');
                system("clear");
                break;



            case 2:

                char sure;
                do
                {
                    system("clear");
                    cin >> fd1;
                    cout << fd1;
                    cout << "Are you sure you want to continue with this data?(Y/N)" << endl;
                    cin >> sure;
                }
                while (sure == 'N' || sure == 'n');
                system("clear");
                break;



            case 3:

                if(ci1 == ci2 && fd1 == fd2)
                {
                    cout << "You have not selected any field.";
                    cout << endl;

                    cout << "Your blank ticket will be generated empty.";
                    cout << endl;

                    cout << "Do you want to continue?(Y/N) ";
                    cout << endl;
                    char empty;
                    cin >> empty;
                    if(empty == 'Y' || empty == 'y')
                    {
                        t1.deletion(ci1,fd1);

                        t1.gen_time(fd1);
                        t1.gen_total(fd1);
                        t1.gen_ticket(ci1,fd1);
                    }
                    else
                    {
                        cout << "Your Ticket is not printed.";
                        cout << endl;
                    }
                }
                else if(!(ci1 == ci2) && fd1 == fd2)
                {
                    cout << "You have to enter your personal information to print the ticket.";
                    cout << endl;

                    cout << "Do you want to enter the information now?(Y/N)";
                    cout << endl;
                    char info;
                    cin >> info;
                    if(info == 'Y' || info == 'y')
                    {
                        system("clear");
                        cin >> ci1;
                        t1.gen_time(fd1);
                        t1.gen_total(fd1);
                        t1.gen_ticket(ci1,fd1);
                    }
                    else
                    {
                        cout << "Your ticket is not printed.";
                        cout << endl;
                    }
                }
                else if(ci1 == ci2 && !(fd1 == fd2))
                {
                    system("clear");
                    cout << "Please enter customer information before printing the ticket.(OK/NO)";
                    cout << endl;

                    string inf;
                    cin >> inf;
                    if(inf == "OK")
                    {
                        cin >> ci1;
                        t1.gen_time(fd1);
                        t1.gen_total(fd1);
                        t1.gen_ticket(ci1, fd1);
                    }
                    else
                    {
                        cout << "Your ticket is not printed.";
                        cout << endl;
                    }
                }
                else if(!(ci1 == ci2) && !(fd1 == fd2))
                {
                    t1.gen_time(fd1);
                    t1.gen_total(fd1);
                    t1.gen_ticket(ci1,fd1);

                }
                system( "read -n 1 -s -p \"Press any key to continue...\"" );
                system("clear");

                break;



            case 4:
                if(ci1 == ci2)
                {
                    cout << "You have to enter your personal information.";
                    cout << endl;

                    char cf;
                    cout << "Do you want to enter the information and book a seat now?(Y/N)";
                    cout << endl;
                    cin >> cf;
                    if(cf == 'Y' || cf == 'y')
                    {
                        system("clear");
                        cout << "Please enter your information.";
                        cout << endl;
                        cin >> ci1;
                        system( "read -n 1 -s -p \"Press any key to continue...\"" );
                        system("clear");
                        cout << "Enter please city ypu want to stay in: ";
                        cin >> hotel_city;
                        cout << "Now book the Hotel.";
                        cout << endl;


                        // Now call select_Hotel with all required arguments
                        hb1.select_Hotel(hotel_city);
                        hb1.Print_Hotel(ci1,fd1);
                    }
                    else
                    {
                        cout << "Your hotel can not booked without any details.";
                        cout << endl;
                    }
                }
                else if(!(ci1 == ci2))
                {
                    cout << "You have to enter city of hotel to book the hotel.";
                    cout << endl;

                    char f;
                    cout << "Do you want to enter the city now?(Y/N)";
                    cout << endl;
                    cin >> f;
                    if(f == 'Y' || f == 'y')
                    {
                        system("clear");
                        cout << "Enter please city ypu want to stay in: ";
                        cin >> hotel_city;

                        cout << "Now you can book the hotel.";
                        cout << endl;



                        // Now call select_Hotel with all required arguments
                        hb1.select_Hotel(hotel_city);
                        hb1.Print_Hotel(ci1,fd1);
                    }
                    else
                    {
                        cout << "Your hotel can not booked without the details.";
                        cout << endl;
                    }
                }
                break;



            case 5:

                if(ci1 == ci2 && !(fd1 == fd2))
                {
                    cout << "You have to enter your customer's information before reserving the car.";
                    cout << endl;

                    cout << "Do you want to enter the customer information now?(Y/N)";
                    cout << endl;

                    char ci;
                    cin >> ci;
                    if(ci == 'Y' || ci == 'y')
                    {
                        cin >> ci1;
                        cb1.get_info();
                        cb1.print(ci1,fd1);
                    }
                    else
                    {
                        cout << "You can't book the car without entering your information.";
                        cout << endl;
                    }
                }
                else if(!(ci1 == ci2) && fd1 == fd2)
                {
                    cout << "You first have to book a flight.";
                    cout << endl;

                    cout << "Do you want to book a flight now?(Y/N)";
                    cout << endl;

                    char answe;
                    cin >> answe;
                    if(answe == 'Y' || answe == 'y')
                    {
                        cin >> fd1;
                        cb1.get_info();
                        cb1.print(ci1,fd1);
                    }
                    else
                    {
                        cout << "You can't book the car without booking a flight.";
                        cout << endl;
                    }
                }
                else if(!(ci1 == ci2) && !(fd1 == fd2))
                {
                    cb1.get_info();
                    cb1.print(ci1,fd1);
                }
                else if(ci1 == ci2 && fd1 == fd2)
                {
                    cout << "You first have to enter your information and book a flight before booking the ride";
                    cout << endl;
                    cout << "Do you want to enter the information and book a flight a now?(Y/N)";
                    cout << endl;
                    char answ;
                    cin >> answ;
                    if(answ == 'Y' || answ == 'y')
                    {
                        cin >> ci1;
                        cin >> fd1;

                    }
                    else
                    {
                        cout << "You can't book the car without entering your information and flight details.";
                        cout << endl;
                    }
                }

                system( "read -n 1 -s -p \"Press any key to continue...\"" );
                system("clear");
                break;



            case 6:

                cout << "Are you sure?(Y/N)";
                cout << endl;

                char answer;
                cin >> answer;
                if(answer == 'Y' || answer == 'y')
                {
                    if(!(ci1 == ci2) && !(fd1 == fd2))
                    {
                        bool cnt;
                        do
                        {
                            string del[3] = {"Customer information","FLight reservation","Both"};
                            for(int i=0;i<3;i++)
                            {
                                cout << i+1 << ". " << del[i];
                                cout << endl;
                            }
                            cout << endl;

                            cout << "Enter which information you want to delete.";
                            cout << endl;

                            int e;
                            cin >> e;
                            if(e == 1)
                            {
                                t1.delete_customer(ci1);
                                cout << "Your infromation is deleted.";
                                cout << endl;
                                cout << "You can enter new information by selecting " << "Customer Details " << "from the menu";
                                cout << endl;
                                cnt = false;
                            }
                            else if(e == 2)
                            {
                                t1.delete_flight_details(fd1);
                                cout << "Your reservation is cancelled.";
                                cout << endl;
                                cout << "You can book new flight by selecting " << "Flight Registration " << "from the menu";
                                cout << endl;
                                cnt = false;
                            }
                            else if(e == 3)
                            {
                                t1.deletion(ci1,fd1);
                                cout << "Your information is deleted and reservation is cancelled.";
                                cout << endl;
                                cout << "You can enter new information by selecting " << "Customer Details " << "from the menu";
                                cout << endl;
                                cout << "You can book new flight by selecting " << "Flight Registration " << "from the menu";
                                cout << endl;
                                cnt = false;
                            }
                            else
                            {
                                cout << "Please select between 1-3.";
                                cout << endl;
                                cnt = true;
                            }
                        }
                        while(cnt);
                    }
                    else if(ci1 == ci2 && !(fd1 == fd2))
                    {
                        t1.delete_flight_details(fd1);
                        cout << "Your flight reservation is cancelled.";
                        cout << endl;
                        cout << "You can book new flight by selecting " << "Flight Registration " << "from the menu";
                        cout << endl;
                    }
                    else if(!(ci1 == ci2) && fd1 == fd2)
                    {
                        t1.delete_customer(ci1);
                        cout << "Your customer's infromation is deleted.";
                        cout << endl;
                        cout << "You can enter new information by selecting " << "Customer Details " << "from the menu";
                        cout << endl;
                    }
                    else if(ci1 == ci2 && fd1 == fd2)
                    {
                        cout << "You have not enter any information and have not resereved any seat.";
                        cout << endl;
                        cout << "So nothing is deleted.";
                        cout << endl;
                    }

                }
                else
                {
                    cout << "Your customer's information is not deleted and seat reservation is not cancelled. ";
                    cout << endl;
                }
                system( "read -n 1 -s -p \"Press any key to continue...\"" );
                system("clear");
                break;



            case 7:

                cout << "Are you sure you want to exit ?(Y/N)";
                cout << endl;

                cout << "Press Y to EXIT  or  N to CONTINUE";
                cout << endl;

                char ans;
                cin >> ans;

                if(ans == 'Y' || ans == 'y')
                {
                    cout << " Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye";
                    cout << endl;
                    cout << " ******************************** Thanks for using Andrew's Airlines. **********************************";
                    cout << endl;
                    cout << " Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye Bye";
                    cout << endl;
                    exit(0);
                    break;
                }
                else
                {
                    system("clear");
                    break;
                }
                cout << endl;
                break;
            default:
                system("clear");
                cout << "Please select number from 1 to 7.";
                break;
        }


    }

    return 0;
}



