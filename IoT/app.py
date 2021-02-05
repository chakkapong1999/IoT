from flask import Flask, jsonify, request

import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
# ref https://firebase.google.com/docs/database/admin/save-data
# Fetch the service account key JSON file contents
cred = credentials.Certificate('iot---496-firebase-adminsdk-isvic-325c977771.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://iot---496-default-rtdb.firebaseio.com/'
})

app = Flask(__name__)


'''
structure json
{
    "topic":""
    "data":{}
    "des":"hello"
}
'''
@app.route('/data/write', methods=['POST'])
def write_data():
    json_data = request.get_json();
    print(json_data)
    ref = db.reference('/')
    ref.child(json_data['topic']).set((json_data['data']))
    return 'data writtne'

@app.route('/data/read/all', methods=['GET'])
def read_all_data():
    json_data = request.get_json(silent=True)
    ref = db.reference('/')
    return jsonify(ref.get())

#read data by query string topic
@app.route('/data/read', methods=['GET'])
def read_data():
    query_topic = request.args.get("topic", None)
    if query_topic is not None:
        ref = db.reference('/'+query_topic)
        return jsonify(ref.get())
    else:
        return jsonify({"status":"Error", "msg":"please use query string name --topic--"})

@app.route('/', methods=['GET'])
def index():
    return '<h1>Welcome to Heroku</h1>'

if __name__ == "__main__":
    # app.run(debug=True, host="0.0.0.0") #test
    app.run(threaded=True, port=5000)
    

# # As an admin, the app has access to read and write all data, regradless of Security Rules
# ref = db.reference('/')
# ref.set({
#     'theater1': {
#         'movie':'Big Bang Theory - click up',
#         'duration':'1:30hrs',
#         'status':'now showing'
#     }
# })
# print(ref.get())
# https://paas-iot.herokuapp.com/
#curl --header "Content-Type: application/json" --request POST --data '{"topic":"temp","data":{"Max":"1234", "CPE":"496"}}' http://localhost:5000/data/write