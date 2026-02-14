import uvicorn
import os
from dotenv import load_dotenv
from backend.server import app

load_dotenv()

if __name__ == "__main__":
    host = os.getenv("HOST")
    port = int(os.getenv("PORT"))

    uvicorn.run(app, host=host, port=port)