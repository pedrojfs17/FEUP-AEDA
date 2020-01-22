/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include <typeinfo>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}


template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle) {
    if (capacity <= vehicles.size())
        return false;

    typename std::vector<Vehicle *>::const_iterator it;

    for (it = vehicles.begin(); it != vehicles.end(); it++)
        if (*vehicle == *(*it))
            return false;

    vehicles.push_back(vehicle);
    return true;
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles() {
    /*
    for (unsigned int i = 1; i < vehicles.size(); i++) {
        Vehicle tmp = *vehicles[i];
        int j;
        for (j = i - 1; j > 0; j--) {
            if ((tmp)->getBrand() < *vehicles[j]->getBrand())
                vehicles[j] = vehicles[j - 1];
            else if ((tmp)->getBrand() == *vehicles[j]->getBrand() && (tmp)->getPrice() < *vehicles[j]->getPrice())
                vehicles[j] = vehicles[j - 1];
            else
                break;
        }
        vehicles[j] = tmp;
    }*/
}

#endif /* SRC_GARAGE_H_ */
