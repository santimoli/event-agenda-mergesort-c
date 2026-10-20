# Event Agenda Manager

A **university room scheduling system** written in C, using a **linked list** to store events and **Mergesort** to keep them sorted. The program supports creating, listing, filtering and deleting events through an interactive menu.

## Problem

Manage a collection of academic events (lectures, exams, etc.) associated with rooms, dates, times and instructors. All data lives in a sorted linked list; Mergesort is used to maintain order after insertions.

## Features

- Create an event (room, course unit, instructor, date, time, duration)
- List all events for a given room
- List events for a room on a specific day
- List the next *n* upcoming events
- List the next *n* events from a given date
- List all events on a specific day
- List events between two dates
- Delete an event by start time and room
- Delete all events before a given date
- Print the full agenda (debug view)

## Data structures

| Structure | Description |
|-----------|-------------|
| `Evento` | An event with room, course, instructor, date/time and duration |
| `Lista` | Doubly-linked list of events |
| `Agenda` | Wrapper around the list, entry point for all operations |

## Sorting

Events are sorted by **date and time** using **Mergesort** on the linked list — O(n log n) time, O(log n) space.

## Technologies

- C (C standard library only)
- Visual Studio (`.sln` / `.vcxproj` project files included)

## Project structure

```
Main.c              # Entry point and interactive menu
Agenda.c / .h       # Agenda operations (create, list, delete, filter)
Evento.c / .h       # Event struct and operations
Lista.c / .h        # Linked list implementation
Mergesort.c / .h    # Mergesort for linked list
Utils.c / .h        # String utilities (trim, copy)
```

## How to build and run

### With Visual Studio
1. Open `Project2AED.sln`
2. Build → Run (`Ctrl+F5`)

### With GCC (command line)
```bash
gcc Main.c Agenda.c Evento.c Lista.c Mergesort.c Utils.c -o agenda
./agenda
```

### Example interaction
```
1 -> Criar Evento
2 -> Listar os eventos de uma sala
3 -> Listar os eventos de uma sala para um determinado dia
4 -> Listar os proximos n eventos
5 -> Listar os proximos n eventos a partir de uma determinada data
6 -> Listar todos eventos de um determinado dia
7 -> Listar os eventos entre 2 datas
8 -> Apagar evento (indicando o inicio e a sala)
9 -> Apagar todos os eventos anteriores a uma data
0 -> Sair
```

### Event input format
```
ano mes dia hora min duracao sala : uc : docente
2024 6 10 9 0 120 A101 : Algoritmos e Estruturas de Dados : Prof. Silva
```

## Course

Algorithms and Data Structures — 1st year, 2nd semester (2023/2024)
