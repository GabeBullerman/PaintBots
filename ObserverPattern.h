// @author: Gabriel Bullerman
#ifndef OBSERVERPATTERN_H
#define OBSERVERPATTERN_H

#include <vector>
#include <algorithm>

// Abstract base class that defines the update method.
class Observer {
public:
    virtual void update() = 0; // Pure virtual function to be implemented by derived classes.
};

class Observable {
public:
    // Adds an observer to the list.
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    // Removes an observer from the list.
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    // Notifies all observers of a change by calling their update method.
    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
private:
    std::vector<Observer*> observers; // List of observers.
};

#endif // OBSERVERPATTERN_H