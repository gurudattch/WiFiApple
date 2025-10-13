# NodeMCU Iframe-Based Captive Portal

## Overview

This project demonstrates an innovative solution for creating a rich web experience on resource-constrained IoT devices. By utilizing NodeMCU's limited capabilities in conjunction with an iframe embedding technique, this implementation provides a fully functional web portal while maintaining the efficiency of small IoT devices.

## Architecture

The solution addresses the fundamental challenge of hosting complex web applications on microcontrollers with limited resources. Instead of attempting to serve a large, complex site directly from the NodeMCU, this implementation uses an iframe to embed a fully functional web portal hosted on a more powerful external server.

### Key Components

- **NodeMCU ESP8266**: Acts as a Wi-Fi access point and serves the minimal HTML wrapper
- **External Server**: Hosts the complex web application at `192.168.4.100:8000`
- **Iframe Integration**: Seamlessly embeds the external portal within the NodeMCU-served page

## Technical Implementation

### Hardware Requirements
- NodeMCU ESP8266 development board
- External server (Raspberry Pi, PC, or cloud instance) running on `192.168.4.100:8000`

### Software Features

#### Captive Portal Functionality
- Creates Wi-Fi access point named "AccessPoint"
- Implements DNS server to capture all requests
- Redirects all traffic to the iframe-embedded portal
- Handles HTTP requests and redirections

#### Iframe Implementation
```html
<iframe id="cover" src="http://192.168.4.100:8000"></iframe>
```
- Full-screen iframe covering entire viewport
- Seamless integration with external web application
- Responsive design for various device sizes

#### Network Configuration
- **Access Point IP**: Dynamically assigned via `WiFi.softAPIP()`
- **DNS Server**: Port 53, captures all domain requests
- **Web Server**: Port 80, serves the iframe wrapper
- **External Portal**: `192.168.4.100:8000`

## Code Structure

### Core Libraries
```cpp
#include <ESP8266WiFi.h>      // Wi-Fi functionality
#include <DNSServer.h>        // DNS server for captive portal
#include <ESP8266WebServer.h> // HTTP server
#include <EEPROM.h>          // Optional persistent storage
```

### Main Functions

#### `setup()`
- Initializes Wi-Fi access point
- Configures DHCP server
- Starts web server with route handlers
- Initializes DNS server for request capture

#### `loop()`
- Processes DNS requests continuously
- Handles incoming HTTP client requests

#### `handleRoot()`
- Serves the main HTML page with iframe
- Returns minimal HTML wrapper

#### `handleNotFound()`
- Redirects unknown requests to main portal
- Implements captive portal behavior

## Innovation Highlights

This solution showcases effective technology integration by:

1. **Resource Optimization**: Leveraging NodeMCU's limited capabilities for essential functions only
2. **Hybrid Architecture**: Combining lightweight IoT device with powerful external server
3. **Seamless User Experience**: Providing rich functionality through iframe embedding
4. **Scalability**: Allowing complex applications to run independently of IoT constraints

## Setup Instructions

1. **Hardware Setup**
   - Connect NodeMCU to power source
   - Ensure external server is running on `192.168.4.100:8000`

2. **Software Configuration**
   - Upload the code to NodeMCU using Arduino IDE
   - Verify serial output for AP IP address
   - Connect devices to "AccessPoint" Wi-Fi network

3. **Testing**
   - Connect to the NodeMCU access point
   - Open any web browser
   - Verify iframe loads external portal content

## Benefits

- **Minimal Resource Usage**: NodeMCU handles only basic networking and HTML serving
- **Rich Functionality**: Complex web applications run on dedicated server
- **Easy Maintenance**: Updates to web portal don't require NodeMCU reprogramming
- **Cost Effective**: Utilizes inexpensive IoT hardware for network access
- **Flexible Deployment**: External server can be local or cloud-based

## Use Cases

- IoT device configuration portals
- Public Wi-Fi access points with custom interfaces
- Educational demonstrations of hybrid IoT architectures
- Prototype development for resource-constrained environments

## Technical Considerations

- Ensure external server accessibility from NodeMCU network
- Monitor iframe loading performance based on network conditions
- Consider security implications of captive portal implementation
- Plan for external server availability and failover scenarios

This implementation demonstrates how different technologies can work together effectively, providing a practical solution for delivering rich web experiences through resource-constrained IoT devices
