# 🍎 WiFiApple

<p align="center">
  <img src="https://github.com/gurudattch/WiFiApple/blob/main/wifiapple_logo.png" width="300"  style="border-radius:50%" alt="WiFiApple Logo"/>
</p>

**WiFiApple** is a lightweight ESP8266-based Wi-Fi toolkit inspired by WiFi Pineapple, designed for captive portal and phishing-based security research.

---

## Overview

WiFiApple enables ESP8266 devices to host a captive portal by embedding an external web application using an iframe.
This help you to run heavy backend application or multiple phishing captive portals without reprogramming the nodeMCU again & again 
This approach overcomes hardware limitations while delivering a rich web interface. 

---

## Architecture

Instead of hosting a full web portal on the ESP8266, WiFiApple uses a hybrid model:

* **NodeMCU ESP8266** → Hosts minimal captive portal
* **External Server** → Hosts main web application
* **Iframe** → Displays portal inside ESP page

```
Client → ESP8266 AP → Iframe → External Server
```

---

## Key Components

* NodeMCU ESP8266 (Access Point)
* DNS Server (Captive Portal)
* Web Server (HTML Wrapper)
* External Portal (`192.168.4.100:8000`)

---

## Core Features

* Creates fake Wi-Fi Access Point
* Captures all DNS requests
* Redirects traffic to captive portal
* Embeds external website via iframe
* Supports responsive web pages
* Minimal resource usage

---

## Iframe Example

```html
<iframe id="cover" src="http://192.168.4.100:8000"></iframe>
```

* Full-screen display
* Loads external portal
* Works on all devices

---

## Libraries Used

```cpp
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
```

---

## Setup Guide

### 1. Hardware

* NodeMCU ESP8266
* External server (PC / Raspberry Pi / Cloud)

### 2. Upload Code

* Flash firmware using Arduino IDE
* Open Serial Monitor
* Note AP IP address

### 3️3. Start Server

Run portal on:

```
192.168.4.100:8000
```

### 4️4. Connect

* Join Wi-Fi: `AccessPoint`
* Open browser
* Portal loads automatically

---

##  Benefits

* Low memory usage
* Easy maintenance
* Scalable design
* Cheap hardware
* No frequent reflashing

---

##  Use Cases

* Captive portal testing
* Wireless security research
* IoT networking demos
* Education & training
* Prototype development

---

##  Security Notes

* Monitor external server availability
* Secure portal endpoints
* Avoid unauthorized usage
* Use only in legal environments

---

## ❓ Disclaimer

This project is intended **for educational and security research purposes only**.
Unauthorized use against networks or users is illegal.

---
