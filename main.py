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
    allData = client['iot']['event'].find()
    allData = list(allData)
    lastSensorMq7 = client['iot']['event'].find({"sensor_name": "MQ7"}).sort([("created_at", -1)]).limit(1)
    lastSensorMq7 = list(lastSensorMq7)[0]
    lastSensorMq9 = client['iot']['event'].find({"sensor_name": "MQ9"}).sort([("created_at", -1)]).limit(1)
    lastSensorMq9 = list(lastSensorMq9)[0]
    
    return templates.TemplateResponse("index.html", {"request": request, "data": allData, "lastSensorMq7": lastSensorMq7, "lastSensorMq9": lastSensorMq9})

# Mount the sensor API
app.mount("/sensor", sensor_app)
