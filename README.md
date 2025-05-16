# Philosophers Project

The Philosophers project is part of the 42 Common Core curriculum and involves solving the classic "Dining Philosophers Problem" using processes and semaphores in C. The goal is to simulate the behavior of philosophers who alternately think and eat while sharing a limited number of resources (forks).

Specifically, this project aims to simulate the behavior of philosophers sitting around a table, where they alternate between thinking and eating. Each philosopher needs two forks to eat, and only one philosopher can hold a fork at a time. The challenge is to avoid deadlock and ensure that all philosophers can eat without starvation.

### Objectives
- Implement synchronization using semaphores.
- Avoid deadlock by ensuring philosophers can access forks in a way that prevents circular waiting.
- Ensure that no philosopher is starved and every philosopher gets a chance to eat.

### Skills Demonstrated
Through this project, I have demonstrated proficiency in several important areas of systems programming:

- **Process Management**: 
  - Using `fork()` to create multiple processes that run concurrently.
  - Managing process synchronization to ensure that philosophers alternate between eating and thinking without conflicts.
  
- **Concurrency and Synchronization**:
  - Implementing semaphores and mutexes to manage shared resources (forks) between processes.
  - Using synchronization mechanisms to prevent race conditions, deadlocks, and ensure fair access to shared resources.
  
- **Deadlock Prevention**:
  - Designing and implementing a solution to avoid deadlock, ensuring that philosophers can always eventually eat without waiting forever.
  - Understanding and applying concepts like resource allocation graphs and lock ordering to avoid circular wait conditions.

- **Multi-threading (in C)**:
  - Simulating multiple philosophers interacting with each other while sharing resources (forks).
  - Using threads (or processes) to simulate concurrent philosophers' actions, handling time-related events such as thinking, eating, and sleeping.

- **Time Management**:
  - Implementing timed operations, such as defining the amount of time a philosopher should eat, think, and sleep.
  - Handling timeouts and conditions related to philosopher death (if they cannot eat in time).

- **Memory Management**:
  - Efficient memory allocation and deallocation, particularly when handling the creation and destruction of philosopher processes.

- **Debugging and Optimization**:
  - Testing for edge cases and race conditions.
  - Optimizing performance to ensure the system works efficiently for a larger number of philosophers.
