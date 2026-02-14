from fastapi import FastAPI
import os
from dotenv import load_dotenv
from db.DataBaseUniversitiesController import DataBaseUniversitiesController

load_dotenv()

app = FastAPI()
db = DataBaseUniversitiesController(
    f"{os.getenv("DATABASE_TYPE")}://{os.getenv("DATABASE_HOST")}:{os.getenv("DATABASE_PORT")}/",
    os.getenv("DATABASE_NAME")
)

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