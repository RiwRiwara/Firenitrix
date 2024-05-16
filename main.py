from fastapi import FastAPI
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi import Request
from sensorApi import app as sensor_app
from config.db import client


app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")

@app.get("/", response_class=HTMLResponse)
async def home(request: Request):
    db = client['iot']['event']
    
    allData = list(db.find().sort("created_at", -1))

    lastSensorMq7 = db.find_one({"sensor_name": "MQ7"}, sort=[("created_at", -1)])
    lastSensorMq9 = db.find_one({"sensor_name": "MQ9"}, sort=[("created_at", -1)])

    return templates.TemplateResponse("index.html", {
        "request": request,
        "data": allData,
        "lastSensorMq7": lastSensorMq7,
        "lastSensorMq9": lastSensorMq9
    })
# Mount the sensor API
app.mount("/sensor", sensor_app)
