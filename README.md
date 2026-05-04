# Urgentify: Task Assistant
 
A simple console-based task management system built in C++ that helps you prioritize and track tasks using classic data structures.
 
## Overview
 
Urgentify uses a combination of a **Stack**, **Priority Queue**, and **Queue** to manage tasks from input to completion. Tasks are sorted by urgency — fewer days remaining comes first, with difficulty as a tiebreaker.
 
## Features
 
- Add tasks with a name, days remaining, and difficulty rating
- View tasks in insertion order (Stack)
- View tasks sorted by urgency (Priority Queue)
- Finish the most urgent task automatically
- Track completed tasks in a history log (Queue)
- Remove the oldest history entry
## Data Structures Used
 
| Structure | Role |
|---|---|
| Stack (LIFO) | Stores tasks in the order they were added |
| Priority Queue | Sorts tasks by urgency (days ↑, difficulty ↓) |
| Queue (FIFO) | Logs completed tasks as history |
 
## How to Run
 
1. **Compile** the program:
   ```bash
   g++ Urgentify.cpp -o Urgentify
   ```
 
2. **Run** the executable:
   ```bash
   ./Urgentify
   ```
 
3. Follow the on-screen menu to manage your tasks.
## Menu Options
 
```
1. Add Task
2. Show Stack (insertion order)
3. Show Priority Queue (urgency order)
4. View History
5. Finish Most Urgent Task
6. Remove Oldest History (Dequeue)
0. Exit
```

## Team Members
 
- Capul, Reen Earl Paolo
- Magbojos, Karenza Arabela C.
- Seda, John Emmanuel Q.
## Course
 
**CC103** — Final Project | CS1205 Team 2
 
