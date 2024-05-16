from fastapi import FastAPI, HTTPException, Request
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
    # sort by created_at
    data = client['iot']['event'].find().sort("created_at", -1)
    data = list(data)
    lastSensorMq7 = client['iot']['event'].find_one({"sensor_name": "MQ7"})
    lastSensorMq9 = client['iot']['event'].find_one({"sensor_name": "MQ9"})
    
    return {
        "message" : "Connected to MongoDB",
        "data" : json.loads(json.dumps(data, default=str)),
        "lastSensorMq7" : json.loads(json.dumps(lastSensorMq7, default=str)),
        "lastSensorMq9" : json.loads(json.dumps(lastSensorMq9, default=str))
    }



@app.post("/event")
async def create_event(request: Request):
    try:
        data = await request.json()
        data['created_at'] = datetime.now()
        data['updated_at'] = datetime.now()
        
        print(data)
        
        if data['status'] == 'Emergency':
            print("Emergency")
        else:
            result = client['iot']['event'].insert_one(data)
            if result.inserted_id:
                return {"message": "Event created successfully"}
            else:
                raise HTTPException(status_code=500, detail="Failed to create event")
                
        
    except json.JSONDecodeError:
        raise HTTPException(status_code=400, detail="Invalid JSON")



# async def get_event(data):
#     print(data)
#     # db = client['iot']['event']
    
#     # result = db.insert_one({
#     #     "sensor_name": sensor_name,
#     #     "status": status,
#     #     "value": value,
#     #     "description": description,
#     #     "created_at": datetime.now(),
#     #     "updated_at": datetime.now()
#     # })
#     if True:
#     # if result.inserted_id:
#         return {"message": "Event created successfully"}
#     else:
#         raise HTTPException(status_code=500, detail="Failed to create event")

@app.get("/deleteAll")

def deleteAll():
    client['iot']['event'].delete_many({})
    return {"message": "All data deleted"}