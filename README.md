# Philosophers-42

The `Philosophers` project is an algorithmic and programming challenge that simulates a synchronization problem. 

It implements the famous Dining Philosophers problem by Diderot, where several philosophers spend their time thinking and eating. In order to better understand this project and to image it, I watched the following video : 
[Philosophers Project Overview](https://www.youtube.com/watch?v=HbBYHRBJ47Q) .

This project aims to develop skills in thread management, synchronization, and the use of mutexes.

## Objectives

- Understand and solve concurrency problems.
- Use mutexes and semaphores to manage access to shared resources.
- Implement an efficient solution without deadlocks for the philosophers' problem.

## Overview

- The program must simulate a certain number of philosophers seated around a table.
- Each philosopher alternates between thinking and eating.
- To eat, a philosopher must take two forks (shared resources).
- The program should manage termination conditions and avoid deadlock situations.

## Installation

To use `Philosophers`, simply clone the repository and compile it:
   ```bash
   git clone https://github.com/your-username/Philosophers-42.git
   cd Philosophers-42
   ```

## Usage

- `number_of_philosophers`: The number of philosophers (at least 1).
- `time_to_eat`: Time (in milliseconds) each philosopher spends eating.
- `time_to_think`: Time (in milliseconds) each philosopher spends thinking.
- `time_to_live`: Time (in milliseconds) each philosopher lives before dying.

Run the program as followed :
  ```bash
  make
  ./philosophers [number_of_philosophers] [time_to_eat] [time_to_think] [time_to_live]
  ```
