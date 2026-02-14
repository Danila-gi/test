from fastapi import FastAPI
from db.DataBaseUniversitiesController import DataBaseUniversitiesController

app = FastAPI()
db = DataBaseUniversitiesController()

@app.on_event("startup")
async def startup_event():
    db.connect_to_db()

@app.on_event("shutdown")
async def shutdown_event():
    db.close_db()

@app.get("/")
def home():
    return {"message": "Hello World"}

@app.get("/admins")
def admins():
    return {"admins": db.get_admins()}