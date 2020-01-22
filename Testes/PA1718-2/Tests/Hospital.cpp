/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>
#include <iostream>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    list<Doctor> temp = this->getDoctors();
    unsigned int tot = 0;

	while(!temp.empty()) {
	    Doctor d = temp.front();
	    if (d.getMedicalSpecialty() == medicalSpecialty)
            tot += d.getPatients().size();
	    temp.pop_front();
	}
	return tot;
}

bool sorting(Doctor & d1, Doctor & d2) {
    if (d1.getPatients().size() < d2.getPatients().size())
        return true;
    else if (d1.getPatients().size() > d2.getPatients().size())
        return false;
    else {
        if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty())
            return true;
        else if (d1.getMedicalSpecialty() > d2.getMedicalSpecialty())
            return false;
        else
            return d1.getCode() < d2.getCode();
    }
}

void Hospital::sortDoctors() {
    doctors.sort(sorting);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	list<Doctor>::iterator itD = doctors.begin();
	int counter = 0;

	for (; itD != doctors.end(); itD++) {
        if ((*itD).getMedicalSpecialty() == medicalSpecialty1)
            counter++;
	}

	if (counter < 3) {
	    doctors.push_back(Doctor(codM1, medicalSpecialty1));
	    return true;
	}
	else
	    return false;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;

    list<Doctor>::iterator itD = doctors.begin();

    for (; itD != doctors.end(); itD++) {
        if ((*itD).getCode() == codM1)
            break;
    }

	if (itD == doctors.end())
	    throw DoctorInexistent();

	p1 = (*itD).getPatients();
	doctors.erase(itD);

	return p1;
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    list<Doctor>::iterator itD = doctors.begin();
    list<Doctor>::iterator itMin;
    int min = 9999;
    double found = false;

    for (; itD != doctors.end(); itD++) {
        if ((*itD).getMedicalSpecialty() == medicalSpecialty1) {
            found = true;
            if ((*itD).getPatients().size() < min) {
                itMin = itD;
                min = (*itD).getPatients().size();
            }
        }
    }

    if (!found)
        return false;

    (*itMin).addPatient(Patient(cod1, medicalSpecialty1));
    return true;

}



void Hospital::processPatient(unsigned codM1) {
    list<Doctor>::iterator itD = doctors.begin();

    for (; itD != doctors.end(); itD++) {
        if ((*itD).getCode() == codM1) {
            if ((*itD).getPatients().empty())
                return;
            else
                break;
        }
    }

    if (itD == doctors.end())
        return;

    Patient p = (*itD).removeNextPatient();

    list<stack<Patient>>::iterator itP = letterTray.begin();

    for (; itP != letterTray.end(); itP++) {
        if ((*itP).size() < trayCapacity) {
            (*itP).push(p);
            return;
        }
    }

    stack<Patient> newstack;
    newstack.push(p);
    letterTray.push_back(newstack);

}


unsigned Hospital::removePatients(unsigned codP1) {
    list<stack<Patient>>::iterator itP = letterTray.begin();
    unsigned int counter = 0;

    for (; itP != letterTray.end(); itP++) {
        if ((*itP).top().getCode() == codP1) {
            (*itP).pop();
            counter++;
            if ((*itP).empty()) {
                itP = letterTray.erase(itP);
                itP--;
            }
        }
    }

	return counter;

}



