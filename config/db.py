from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi

collection_name = 'iot'
uri = 'mongodb+srv://riw:Vha315Sfv0QM44ki@newcluster.fxldupt.mongodb.net/?retryWrites=true&w=majority'
client = MongoClient(uri, server_api=ServerApi('1'))

try:
    client.admin.command('ping')
    print("Pinged your deployment. You successfully connected to MongoDB!")
except Exception as e:
    print(e)