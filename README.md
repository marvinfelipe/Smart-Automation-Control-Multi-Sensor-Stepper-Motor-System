# Smart-Automation-Control-Multi-Sensor-Stepper-Motor-System
This repository contains the firmware and documentation for an integrated control system using an Arduino Uno. The project demonstrates how to interface industrial-grade sensors (Capacitive and Inductive) with high-torque motion control (Stepper Motor) and power electronics (Dual Relay Switch).

Technical Note: PNP vs. NPN Logic
This project specifically utilizes PNP Sensors. Because PNP sensors output a high voltage (typically 6V–24V) when triggered, they cannot be connected directly to the Arduino's 5V digital pins without risking hardware damage.

Current Setup (PNP): The Relay Switches (or a voltage divider/optocoupler) act as the necessary interface to isolate the high-voltage sensor signal and provide a "clean" dry contact for the Arduino.
The NPN Alternative: If you were to swap these for NPN (Sinking) sensors, the relays could be omitted. NPN sensors pull the signal to Ground (0V), allowing you to use the Arduino’s internal INPUT_PULLUP resistors to detect the trigger safely.


Integration Warning
Warning: Do not connect the signal wire of a 12V/24V PNP sensor directly to your Arduino. Without the relay isolation used in this project, you will likely fry the ATmega328P chip.

Power & Logic Architecture
The system is designed to run off a single 12V DC power supply, distributed as follows:
Arduino Uno: Receives 12V through the DC Barrel Jack. The onboard voltage regulator steps this down to 5V for the ATmega328P and the Relay coils.
PNP Sensors: Powered directly by the 12V rail.
The Relay Bridge: Because the sensors output 12V (PNP High), they trigger the Relay Coils rather than the Arduino pins. The relay contacts then act as a "dry switch" to safely signal the Arduino's 5V logic.
Note: If NPN sensors were used, relays would be unnecessary as NPN sensors sink current to Ground.
Stepper Motor: The ULN2003 driver should ideally be powered by the Arduino's 5V or Vin pin (if using 5V/12V variants respectively), ensuring common ground across the system.

