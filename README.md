# 🔫 Metal Slug Remake

A **Metal Slug**-inspired 2D run-and-gun action game built in **C++** using **SFML**, developed as the semester project for **Object-Oriented Programming (CS-1004)** at FAST-NUCES Islamabad.

## 📖 About

This project reimagines the classic Metal Slug arcade experience while serving as a deep, practical application of object-oriented design principles. Beyond just building a playable game, the focus was on demonstrating strong OOP fundamentals — inheritance hierarchies, polymorphism, abstraction, and clean class design — all backed by UML diagrams and design documentation.

## ✨ Features

- 🕹️ 2D run-and-gun gameplay mechanics
- 👾 Multiple enemy AI types with distinct behaviors
- 🗺️ Procedurally generated terrain using **Perlin noise**
- 🔫 Weapon system with damage calculation logic
- 💥 Collision detection and combat mechanics
- 🎮 Built entirely with **SFML** for rendering, input, and audio

## 🧠 OOP Concepts Demonstrated

- **Virtual functions & polymorphism** — dynamic behavior for enemy types and weapons
- **Abstract classes** — base interfaces for enemies, weapons, and game entities
- **Templates** — generic, reusable component logic
- **Operator overloading** — cleaner syntax for game object interactions
- **All four C++ casts** — `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast` used contextually
- **UML-driven design** — class hierarchies planned and documented before implementation

## 🛠️ Tech Stack

- **Language:** C++
- **Library:** SFML (Simple and Fast Multimedia Library)
- **Design:** UML Class Diagrams

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++ recommended)
- SFML library installed

### Run Locally
```bash
git clone https://github.com/ahmadraza2730/Metal-Slug-Remake.git
cd Metal-Slug-Remake
g++ -c main.cpp
g++ main.o -o MetalSlug -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./MetalSlug
```

## 📐 Design Documentation

This project was built with UML class diagrams outlining inheritance relationships between game entities (Player, Enemy types, Weapons) before implementation — ensuring clean, maintainable OOP architecture from the start.

## 🎓 Context

Built for **Object-Oriented Programming (CS-1004)** at FAST-NUCES Islamabad. This project represents the OOP evolution of an earlier procedural project, [Tumble Pop Remake](#), and laid the groundwork for my current [Pathfinder AI Maze Game](#) built with C++/SFML.

## 📌 Author

**Muhammad Ahmad**
CS Student @ FAST-NUCES | C++ & Game Dev | OOP Enthusiast
