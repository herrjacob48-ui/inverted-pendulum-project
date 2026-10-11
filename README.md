# Inverted Pendulum Balancing Robot

An inverted pendulum cart-pole system built from scratch to implement closed-loop PID control on physical hardware. The cart balances a free-swinging pendulum by tracking its angle and accelerating a stepper motor to keep the center of mass centered.

![Demonstration Video](docs/assets/pendulumbalancing.gif)

## Hardware & Mechanical
The chassis was designed in Onshape using a mix of 3D-printed mounts and standard industrial hardware.
* **Actuation:** Nema 17 stepper motor with a GT2 timing belt and 20T pulley.
* **Linear Motion:** 8mm rods with LM8UU linear bearings.
* **Documentation:** Full CAD assemblies, exploded views, and the BOM are in the repository.

![Top-Level Assembly Drawing](hardware/drawings/IP-A-001.png)

## Electronics
I used an ESP32 for this project because the control loop runs at 1 kHz, which required fast hardware interrupts to read the high-resolution encoder without missing counts.
* **Microcontroller:** ESP32
* **Feedback:** 600 P/R Optical Quadrature Rotary Encoder (mounted on the pendulum pivot)
* **Motor Driver:** A4988 Stepper Motor Driver

![System Wiring Diagram](docs/assets/wiring_diagram.png)

## Firmware
The firmware is written in C++ and uses a discrete-time PID controller. 
* Hardware-timer-backed interrupt service routines (ISRs) decode the A/B quadrature signals to calculate the pendulum's exact angle and velocity.
* The PID loop calculates the required correction velocity, which is translated into step and direction pulses for the A4988 driver.

---

## Repository Structure

```text
├── docs/
│   └── assets/                  # Demo GIFs, wiring diagrams, and photos
├── firmware/                    # ESP32 C++ source code (main, PID, encoder)
├── hardware/
│   ├── CAD_exports/             # STEP files for the mechanical assemblies
│   ├── drawings/                # Exploded view and BOM (IP-A-001)
│   └── stl_prints/              # Ready-to-print meshes for custom brackets
└── README.md
