## Class Structure

### Menu
This class is responsible for displaying the console menu and handling user input. It does not have any attributes.
It's supposed to be extended later for each view that we will later have.

### FlightManagement
This class is responsible for managing all flight-related operations.
It will operate side-by-side with the Graph.h class.

### Dataset
This class contains all the data related to airports, airlines, and flights. It has the following attributes:
- `std::vector<Flight> flights`: A vector to store all the flights.
- `std::vector<Airport> airports`: A vector to store all the airports.
- `std::vector<Airline> airlines`: A vector to store all the airlines.

### Flight
This class represents a flight. It has the following attributes:
- `std::string flightNumber`: The flight number.
- `std::string departureAirport`: The departure airport.
- `std::string arrivalAirport`: The arrival airport.
- `std::string departureTime`: The departure time.
- `std::string arrivalTime`: The arrival time.

### Airport
This class represents an airport. It has the following attributes:
- `std::string airportCode`: The airport code.
- `std::string airportName`: The airport name.
- `std::string city`: The city where the airport is located.
- `std::string country`: The country where the airport is located.

### Airline
This class represents an airline. It has the following attributes:
- `std::string airlineCode`: The airline code.
- `std::string airlineName`: The airline name.