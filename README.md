An eco-friendly smart irrigation system designed to optimize water usage using solar-powered energy and real-time soil monitoring. Built using Arduino Uno, this system combines solar tracking with automatic irrigation, making it ideal for both small-scale and remote agricultural applications.

🏆 Built as part of the B.E. Final Year Mini Project – Electrical & Electronics Engineering, NIEIT Mysuru (VTU)

📌 Abstract
This project integrates solar tracking with an automatic irrigation system powered entirely by solar energy. It adjusts the solar panel's orientation throughout the day to capture maximum sunlight, which charges a battery that powers a water pump. The system uses a soil moisture sensor to determine when irrigation is needed, making it both smart and sustainable.

🛠️ Technologies & Components Used
Component	Purpose
6V Solar Panel	Energy generation via sunlight
Servo Motors	Panel rotation for sun tracking
LDR Sensors	Detect sun direction
Soil Moisture Sensor	Monitor soil wetness
Water Pump	Irrigate crops
Boost Converter	Step-up voltage from solar output
Arduino Uno	Main controller
LCD Display	Display soil status & pump activity
Battery Pack	Store solar energy

🔌 Working Principle
Sunlight Detection – LDRs detect light intensity, and servo motors rotate the solar panels to face the sun.
Energy Storage – Solar panel charges a battery via a boost converter.
Soil Moisture Check – Moisture levels are continuously monitored.
Pump Activation – If soil is dry, the pump is powered by solar energy.
Automatic Shutdown – At night, the panel closes and system goes into idle mode.

💻 Software & Code
Platform: Arduino IDE
Languages: C/C++ (Arduino)
Programs:
solar_tracking.ino – Controls solar tracking and panel movement.
auto_irrigation.ino – Reads soil data and manages pump via relay.

📷 Block & Circuit Diagrams
Available in the report:
Block Diagram
Connection Diagram
Real-world layout and wiring instructions

✅ Advantages
Operates in off-grid locations
Efficient use of water and power
Low maintenance, minimal human intervention
Environmentally friendly and sustainable

🚀 Future Enhancements
Integrate with IoT for remote monitoring
Use AI/ML for crop-specific irrigation prediction
Add cloud-based dashboards and alert systems
Implement drones or remote sensors for large fields
