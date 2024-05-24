# Firenitrix

## Overview

Firenitrix is an IoT project that uses Uno R3 and ESP8266 to gather data and send it to a FastAPI backend. The data is then stored in MongoDB and displayed on a website.

## Prerequisites

- Python 3.8

## Setting up the Environment

### 1. Clone the Repository
```
git clone https://github.com/RiwRiwara/Firenitrix
cd Firenitrix
```

### 2. Create Virtual Environment
```
python3 -m venv myenv
```

### 3. Activate Virtual Environment
```
myenv\Scripts\activate
```

### 4. Install Dependencies
```
pip install -r requirements.txt
```

## How to Run

### 1. Start the FastAPI server
```
uvicorn main:app --reload
```

## Project Details

### Hardware
- **Uno R3**: Microcontroller board used for reading data from sensors.
- **ESP8266**: Wi-Fi module used to send data to the FastAPI server.

### Software
- **FastAPI**: A modern, fast web framework for building APIs with Python 3.6+.
- **MongoDB**: A NoSQL database used for storing the data gathered by the IoT devices.

### Workflow
1. **Data Gathering**: The Uno R3 reads data from connected sensors.
2. **Data Transmission**: The ESP8266 sends the gathered data to the FastAPI backend.
3. **Data Storage**: FastAPI receives the data and stores it in a MongoDB database.
4. **Data Display**: The data is retrieved from MongoDB and displayed on a website.

## Directory Structure

```
Firenitrix/
├── arduino/
│   ├── ESP/
│   ├── R3/
├── config/
│   ├── db.py
├── static/
│   └── index.html
├── templates/
│   ├── js/
│   └── css/
├── requirements.txt
├── main.py
├── sensorApi.py
└── README.md
```

- `main.py`: The entry point of the FastAPI application.
- `sensorApi.py`: The Api endpoint to comunicate between sensor and server.
- `requirements.txt`: A file listing the dependencies required to run the project.
- `README.md`: This file.

## Demo Dashboard
![image](https://github.com/RiwRiwara/Firenitrix/assets/61749500/102eb417-5007-427a-98ed-9f1fd051b0bc)
