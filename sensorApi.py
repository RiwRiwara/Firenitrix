from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from config.db import client
from pydantic import BaseModel
import json
from datetime import datetime

app = FastAPI()

origins = [
    "http://localhost",
    "http://localhost:8080",
    '*'
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class Event(BaseModel):
    sensor_name: str
    value: float
    status: str
    description: str
    created_at: datetime = datetime.now()
    updated_at: datetime = datetime.now()

@app.get("/test")
async def main():
    return {"message": "Firenitrix API"}

@app.get("/db")
async def testDB():
    data = client['iot']['event'].find()
    data = list(data)
    return {
        "message" : "Connected to MongoDB",
        "data" : json.loads(json.dumps(data, default=str))
    }


@app.post("/event")
async def create_event(event: Event):
    db = client['iot']['event']
    event_dict = {}
    event_dict['sensor_name'] = event.sensor_name
    event_dict['value'] = event.value
    event_dict['status'] = event.status
    event_dict['description'] = event.description
    event_dict['created_at'] = datetime.now()
    event_dict['updated_at'] = datetime.now()
    result = db.insert_one(event_dict)
    
    if result.inserted_id:
        return {"message": "Event created successfully"}
    else:
        raise HTTPException(status_code=500, detail="Failed to create event")
    
@app.get("/event/{sensor_name}/{status}/{value}/{description}/")
async def get_event(sensor_name: str, status: str, value: float, description: str):
    db = client['iot']['event']
    
    result = db.insert_one({
        "sensor_name": sensor_name,
        "status": status,
        "value": value,
        "description": description,
        "created_at": datetime.now(),
        "updated_at": datetime.now()
    })
    if result.inserted_id:
        return {"message": "Event created successfully"}
    else:
        raise HTTPException(status_code=500, detail="Failed to create event")