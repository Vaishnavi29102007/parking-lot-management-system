# Project Overview

## Problem statement
In a busy parking area, staff need a simple way to track parked vehicles and manage vehicles waiting when all slots are occupied.

## Objective
Create a small parking lot management program in C that demonstrates how a queue can organize waiting vehicles fairly.

## Proposed solution
The program stores parked vehicles in an array. When the lot is full, new vehicles are inserted into a circular FIFO queue. When a parked vehicle leaves, the program removes the first waiting vehicle from the queue and gives it the available slot.

## Algorithm

### Arriving vehicle
1. Read owner name and vehicle number.
2. If a parking slot is available, add the vehicle to the parked array.
3. Otherwise, enqueue the vehicle into the waiting queue.
4. Display the result.

### Releasing a vehicle
1. Read the vehicle number.
2. Search the parked array.
3. If it is not found, display a message.
4. If found, remove it from the array by shifting later entries.
5. If the waiting queue is not empty, dequeue its front vehicle and park it.

## Complexity
Let `n` be the number of parked vehicles and `w` be the number of waiting vehicles.

- Enqueue: O(1)
- Dequeue: O(1)
- Search parked vehicles: O(n)
- Remove a parked vehicle from the array: O(n)
- Display waiting queue: O(w)

## Conclusion
The project demonstrates FIFO queue operations in a real-world-style example and gives beginners practice with structures, arrays, functions, and menu-driven C programming.
