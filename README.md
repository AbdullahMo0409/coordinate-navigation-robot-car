# coordinate-navigation-robot-car

An Arduino-based smart car prototype that simulates GPS-style coordinate navigation while avoiding obstacles and returning to its target path.

The goal of this project was to build a small autonomous car that can move toward a destination coordinate, detect obstacles, avoid them, and then continue moving toward the target after the obstacle is cleared.

---

## Overview

This project combines robotics, embedded systems, sensors, motors, and navigation logic.

Instead of using a real GPS module, the car simulates a coordinate-based navigation system. The user provides a target coordinate, and the car attempts to move toward it while maintaining awareness of its approximate position.

When an obstacle is detected, the car avoids it, then tries to return to its original route and continue toward the destination.

---

## Features

- Arduino-based smart car prototype
- Simulated coordinate-based navigation
- Destination coordinate input
- Obstacle detection and avoidance
- Path correction after avoiding obstacles
- Motor control and sensor-based decision-making
- Real-time movement logic

---

## How It Works

The system follows this general workflow:

1. The user provides destination coordinates.
2. The car starts moving toward the target.
3. The system continuously estimates the car’s current position.
4. Sensors check for obstacles in the path.
5. If an obstacle is detected, the car performs an avoidance maneuver.
6. After avoiding the obstacle, the car attempts to return to the correct path.
7. The process continues until the car reaches or approaches the destination.

---

## Hardware Components

The project may include components such as:

- Arduino board
- Motor driver
- DC motors
- Ultrasonic sensor
- Car chassis
- Wheels
- Battery source
- Jumper wires
- Optional additional sensors

---

## Technologies Used

- Arduino
- C / Arduino C
- Embedded Systems
- Robotics
- Sensors
- Motor Control
- Obstacle Avoidance
- Navigation Algorithms

---

## Repository Structure

```text
self-driving-car-arduino/
├── src/        # Arduino source code
├── designs/   # Chasis design
├── media/      # Prototype photos or demo videos
├── .gitignore
└── README.md
```

---

## Notes

This project is a prototype and does not use a real GPS module.  
The coordinate navigation system is simulated to demonstrate the logic of destination-based autonomous movement.

The main focus of the project is combining movement control, obstacle avoidance, and path correction in a small robotics prototype.

---

## Future Improvements

- Add real GPS support
- Improve position estimation accuracy
- Add encoder-based movement tracking
- Improve obstacle avoidance logic
- Add path planning algorithms
- Add a mobile or desktop control interface
