# OpsCore

## What is it?
A desktop application that allows the quick setup of Command Operations Centers with a variable number of connected screens. Surveillance equipment can be added to the network in a modular manner by running the OpsUnit cross-platform app on a client machine. Slave machines connected to the master machine in the operations center can be added by running the cross-platform OpsNode on a locally connected machine and configuring it with the OpsCore server ip address and port. This is what the product is expected to look like. Refer to the below sketches for more details. ( TODO: Add sketches)

## How does it work?

Let's start with some definitions:

- OpsCore machine: A main server machine that allows multiple client machines and surveillance equipment to connect to it via local or global (ex. Internet based) networks.

- Node machine: A node machine is a client machine that connects to a main OpsCore server machine. The main OpsCore server machine would be the main screen in a command operations center, and the node machines would be secondary screens that allow information exchange with the main OpsCore server machine. 

- OpsUnit machine: A typically small machine serving as a piece of surveillance equipment, that connects to an OpsCore machine and streams all accumulated data (ex. Video, Audio, sensory measurements, ... ). This unit is allowed to connect via internet or local area connections (when connected via the internet, uses SSH tunnels if OpsCore does not have a static public IP, to overcome NAT setups imposed by ISPs). 
