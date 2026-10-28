# Parking Lot Management System Using Queues

A beginner-friendly Data Structures and Algorithms mini project written in C. It manages a small parking lot and uses a **FIFO queue** to keep vehicles waiting when all parking slots are occupied.

## Features

- Park a vehicle when a slot is available
- Add arriving vehicles to a waiting queue when the lot is full
- Release a parked vehicle by vehicle number
- Automatically park the next waiting vehicle when a slot becomes free
- View parking status, parked vehicles, and waiting queue
- Store owner name, vehicle number, and entry time during the running session

## DSA concepts used

- **Queue (FIFO):** First In, First Out. The first vehicle to join the waiting queue is the first one to receive a free slot.
- **Circular queue:** `front`, `rear`, and `count` manage the waiting queue efficiently.
- **Array:** Stores the currently parked vehicles.
- **Searching:** Finds a vehicle by its registration number before releasing it.

## Project structure

```text
parking-lot-management-system/
├── main.c
├── README.md
├── .gitignore
└── docs/
    └── project-overview.md
```

## Requirements

- A C compiler such as GCC
- Terminal / Command Prompt

## Compile and run

### Windows (MinGW GCC)

```bash
gcc main.c -o parking
parking.exe
```

### Linux / macOS

```bash
gcc main.c -o parking
./parking
```

## How to use

1. Choose `1` to park a vehicle.
2. Enter the owner's name and vehicle number.
3. If all five slots are occupied, the vehicle is added to the waiting queue.
4. Choose `2` to release a parked vehicle.
5. If anyone is waiting, the first vehicle in the queue is automatically parked.
6. Use options `3`, `4`, and `5` to view the status and vehicle lists.
7. Choose `0` to exit.

## Example scenario

The lot has five slots. After five vehicles are parked, a sixth vehicle joins the waiting queue. When one parked vehicle leaves, the sixth vehicle is automatically moved into the newly available slot.

## Limitations

- This is a console-based C program, not a web application.
- Data is held in memory and is cleared when the program exits.
- The parking capacity is fixed at five slots for easy demonstration.
- This educational project does not calculate parking fees or use a database.

## Future improvements

- Save records to a file
- Add parking fees based on duration
- Make the parking capacity configurable
- Add a web interface as a separate frontend project

## License

This project is provided for learning and educational use.
