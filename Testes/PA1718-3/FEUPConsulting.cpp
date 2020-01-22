/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	//TODO
	BSTItrIn<Expertize> it(expertizes);

   while (!it.isAtEnd()) {
       if (it.retrieve().getName() == expertizeAvailable && it.retrieve().getCost() == cost) {
           it.retrieve().addConsultant(student);
           return;
       }
       it.advance();
   }

   Expertize e(expertizeAvailable, cost);
   e.addConsultant(student);
   expertizes.insert(e);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
    BSTItrIn<Expertize> it(expertizes);

    while(!it.isAtEnd()) {
        if (it.retrieve() == Expertize(project->getExpertize(),project->getCost())) {
            for (auto x : it.retrieve().getConsultants()) {
                if (x->getCurrentProject().empty())
                    temp.push_back(x);
            }
        }
        it.advance();
    }

	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    if (project->getConsultant() != NULL)
        return false;

    vector<Student*> temp = getCandidateStudents(project);

    for (auto x : temp) {
        if (x == student) {
            x->addProject(project->getTitle());
            project->setConsultant(x);
            return true;
        }
    }

    return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	//TODO:
    students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	//TODO
    student->setEMail(newEMail);

}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (auto x : candidates) {
	    if(x.getPastProjects().size() >= min)
	        activeStudents.push(x);
	}

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	if (activeStudents.size() == 0)
	    return 0;
	else if (activeStudents.size() == 1) {
	    studentMaximus = activeStudents.top();
	    return 1;
	}

	Student first = activeStudents.top();
	activeStudents.pop();
	Student second = activeStudents.top();
	activeStudents.push(first);

	if (first.getPastProjects().size() == second.getPastProjects().size())
	    return 0;

	studentMaximus = first;
	return activeStudents.size();

}





















