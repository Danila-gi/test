from pymongo import MongoClient


class DataBaseUniversitiesController:
    def __init__(self, url_db, name_db):
        self.__client = None
        self.__db = None
        self.__url_db = url_db
        self.__name_db = name_db

    def connect_to_db(self):
        self.__client = MongoClient(self.__url_db)
        self.__db = self.__client[self.__name_db]

    def close_db(self):
        self.__client.close()

    def get_admins(self):
        admins = []
        for admin in self.__db["admins"].find():
            admin = dict(admin)
            admin['_id'] = str(admin['_id'])
            admins.append(admin)
        return admins
