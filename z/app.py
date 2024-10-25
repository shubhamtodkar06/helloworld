from cs50 import SQL
from flask import Flask, jsonify, render_template, request, redirect, session
from flask_session import Session
import datetime

import requests

#############################################################################################################################################
app = Flask(__name__)
#############################################################################################################################################
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
#############################################################################################################################################
db = SQL('sqlite:///loger.db')
driver = SQL('sqlite:///driver.db')
rating = SQL('sqlite:///rating.db')
rides = SQL('sqlite:///rides.db')
accept = SQL('sqlite:///accept.db')


#############################################################################################################################################

@app.route("/")
def index():
    return render_template("index.html")

#############################################################################################################################################

@app.route("/login", methods=["GET","POST"])
def login():
     if request.method == 'GET':
          return render_template("login.html")
     else:
           #get userid as input from user to verify
          user = request.form.get("user")
          if not user:
               return redirect('/login')

          #check if input is number
          if user.isdigit():
               #get list of number form database
               number = db.execute('SELECT number FROM loger')
               numbers = []
               for i in range(len(number)):
                    numb=number[i]
                    numbers.append(numb['number'])

               #check if input number is in list of numbers
               if int(user) in numbers:
                    #get password from database of that user
                    pas = db.execute('SELECT pass FROM loger WHERE number=(?)',user)
                    passs = []
                    for i in range(len(pas)):
                         numb=pas[i]
                         passs.append(numb['pass'])
                    #get password from user
                    psd= request.form.get("passw")
                    if not psd:
                         return redirect('/login')

                    #check password
                    if passs[0] == psd:
                         name = db.execute('SELECT name FROM loger WHERE number=(?)',user)
                         user_id = db.execute('SELECT user_id FROM loger WHERE number=(?)',user)
                         name = name[0]
                         user_id = user_id[0]
                         #define session
                         session["name"] = (name['name'])
                         session["user_id"] = (user_id['user_id'])
                         return redirect('/success')
                    else:
                         return render_template("login.html", incorrect="Incorrect Password")
               else:
                    return render_template("login.html", nofound="**Number NOT Found")

          else:
               userids = db.execute('SELECT user_id FROM loger')
               userid = []
               for i in range(len(userids)):
                    userd=userids[i]
                    userid.append(userd['user_id'])

               if user in userid:
                    pas = db.execute('SELECT pass FROM loger WHERE user_id = (?)',user)
                    passs = []
                    for i in range(len(pas)):
                         numb=pas[i]
                         passs.append(numb['pass'])
                    psd= request.form.get("passw")
                    if not psd:
                         return redirect('/login')

                    if passs[0] == psd:
                         name = db.execute('SELECT name FROM loger WHERE user_id = (?)',user)
                         user_id = db.execute('SELECT user_id FROM loger WHERE user_id =(?)',user)
                         name = name[0]
                         print(user_id)
                         user_id = user_id[0]
                         #define session
                         session["name"] = name['name']
                         session["user_id"] = (user_id['user_id'])
                         return redirect('/success')
                    else:
                         return render_template("login.html", incorrect="**Please Check Password")
               else:
                    return render_template("login.html", nofound="**UserId NOT Found")


#############################################################################################################################################

@app.route("/signup", methods=["GET","POST"])
def signup():
     if request.method == 'GET':
          return render_template("signup.html")
     else:
          signers = db.execute('SELECT user_id FROM loger')
          result = []
          for i in range(len(signers)):
               dictit=signers[i]
               result.append(dictit['user_id'])

          userid = request.form.get("username")
          if not userid:
               return redirect("/signup")

          name = request.form.get("fname")
          if not name:
               return redirect("/signup")

          number = request.form.get("number")
          if not number:
               return redirect("/signup")

          email = request.form.get("email")
          if not email:
               return redirect("/signup")

          password= request.form.get("pass")
          if not password:
               return redirect("/signup")

          if userid in result:
               return render_template("signup.html", alert ='UserId is NOT Avaliable!!!')
          else:
               db.execute('INSERT INTO loger(user_id, name, number, email, pass) VALUES(?,?,?,?,?)', userid, name, int(number), email, password,)
               return redirect('/login')


 #############################################################################################################################################
@app.route("/success", methods=["GET","POST"])
def succ():
     if not session.get("name"):
          return redirect("/login")
     user_id = rides.execute('SELECT userid FROM rides')
     users = list()
     for values in user_id:
          users.append(values['userid'])
     userid = session.get("user_id")
     print(userid, users)
     if userid in users:
          return render_template("successful.html", name = session.get("name").upper(), button = 'Check')
     else:
          return render_template("successful.html", name = session.get("name").upper(), button = 'Create')




#############################################################################################################################################

@app.route("/logout", methods=["GET","POST"])
def logout():
     if session.get('lib_name'):
          session['lib_name'] = None
          return redirect('/lib_login')
     session["name"] = None
     return redirect("/login")

##########################################################################################################################################################################################################################################################################################

@app.route("/change_pass", methods=["GET","POST"])
def change_pass():
     if request.method == 'GET':
          return render_template("change.html")
     else:
          user = request.form.get("user")
          if not user:
                    return redirect('/change_pass')

          if user.isdigit():
               #get list of number form database
               number = db.execute('SELECT number FROM loger')
               numbers = []
               for i in range(len(number)):
                    numb=number[i]
                    numbers.append(numb['number'])

               if user in numbers:
                    email = request.form.get("email")
                    emails = db.execute('SELECT email FROM loger WHERE user_id = (?)',user)
                    emails = emails[0]
                    emails = emails['email']
                    if emails == email:
                         psd = request.form.get("psd")
                         if not psd:
                              return redirect('/change_pass')
                         passs = request.form.get("pass")
                         if not passs:
                              return redirect('/change_pass')
                         if passs == psd:
                              db.execute('UPDATE loger SET pass = (?) where number =(?)', psd, user)
                              return redirect("/login")
                         else:
                              return render_template("change.html", nopass="**Both Passwords MUST be same ")
                    else:
                         return render_template("change.html", noemail="**Incorrect Email Id!!!")
               else:
                    return render_template("change.html", nouserid="**UserId NOT Found!!!")
          else:
               userids = db.execute('SELECT user_id FROM loger')
               userid = []
               for i in range(len(userids)):
                    userd=userids[i]
                    userid.append(userd['user_id'])

               if user in userid:
                    email = request.form.get("email")
                    emails = db.execute('SELECT email FROM loger WHERE user_id = (?)',user)
                    emails = emails[0]
                    emails = emails['email']
                    if emails == email:
                         psd = request.form.get("psd")
                         passs = request.form.get("pass")
                         if passs == psd:
                              db.execute('UPDATE loger SET pass = (?) where user_id =(?)', psd, user)
                              return redirect("/login")
                         else:
                              return render_template("change.html", nopass="**Both Passwords MUST be same ")
                    else:
                         return render_template("change.html", noemail="**Incorrect Email Id!!!")
               else:
                    return render_template("change.html", nouserid="**UserId NOT Found!!!")
#############################################################################################################################################



@app.route("/Create", methods=["GET", "POST"])
def create():
    if not session.get("name"):
        return redirect("/login")

    if request.method == 'GET':
         return render_template("create.html")
    else:
     act = request.form.get('search_by')
     pick = request.form.get('pickup_location')
     drop_l = request.form.get('dropoff_location')
     date = request.form.get('date')
     number = request.form.get('number')
     time1 = request.form.get('time1')
     time2 = request.form.get('time2')
     userid = session.get('user_id')
     if not pick and drop_l and date and time1 and time2 and userid and act:
          redirect('/login')
     rides.execute('INSERT INTO rides(userid, pick, drop_l, date, time1, time2, who, passengers ) VALUES (?,?,?,?,?,?,?,?)',userid, pick, drop_l, date, time1, time2, act, number)
     return redirect('/Check')



#############################################################################################################################################

@app.route("/search", methods=["GET","POST"])
def search():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          return render_template("search.html")
     else:

          act = request.form.get('search_by')
          pick = request.form.get('pickup_location')
          pass_num = request.form.get('number')
          pick.replace(',', ' ')
          drop_l = request.form.get('dropoff_location')
          drop_l.replace(',', ' ')
          x = len((pick.split()))
          y = len((drop_l.split()))
          pick_bigger = lambda x, y: x if x > y else y
          number = pick_bigger(x,y)
          print(pick, drop_l)
          for i in range(number):
               print(i)
               pick_new = '%' + pick.split()[i] + '%'
               drop_l_new = '%' + drop_l.split()[i] + '%'
               print(pick, drop_l)
               date = request.form.get('date')
               time1 = request.form.get('time1')
               if act == 'captain':
                    info = rides.execute('SELECT * FROM rides WHERE pick LIKE ? AND drop_l LIKE ? AND who = ?', pick_new, drop_l_new , 'cruiser')
               else:
                    info = rides.execute('SELECT * FROM rides WHERE pick LIKE ? AND drop_l LIKE ? AND who = ?', pick_new, drop_l_new , 'captain')
               print(info)
               if info:
                    break

          return render_template('show.html', info = info)



#############################################################################################################################################

@app.route("/map", methods=["GET","POST"])
def map():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          return render_template("map.html")
#############################################################################################################################################

@app.route("/profile", methods=["GET","POST"])
def profile():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          return render_template("profile.html")

#############################################################################################################################################
@app.route('/search_location')
def search_location():
    if not session.get("name"):
          return redirect("/login")
    query = request.args.get('query')
    if query:
        url = 'https://nominatim.openstreetmap.org/search'
        params = {
            'q': query,
            'format': 'json',
            'limit': 5
        }
        try:
            response = requests.get(url, params=params)
            response.raise_for_status()  # Raise an exception for HTTP errors
            locations = response.json()
            print(locations)  # Print the entire response for debugging
            names = [location.get('display_name') for location in locations]  # Extract names from response
            print(names)  # Print names for debugging
            return jsonify(names)  # Return list of names as JSON response
        except Exception as e:
            print("Error occurred:", e)  # Print the exception message for debugging
            return jsonify([])  # Return empty list if an error occurs
    else:
        print("No query provided")  # Print a message if no query provided
        return jsonify([])  # Return empty list if no query provided


#############################################################################################################################################

@app.route("/Check", methods=["GET","POST"])
def Check():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          info = db.execute('SELECT * FROM loger WHERE user_id = ?', session.get('user_id'))
          ride_info = rides.execute('SELECT * FROM rides WHERE userid = ? ', session.get('user_id'))
          print(info)
          print(ride_info)
          return render_template("check.html", info = info, ride = ride_info)
#############################################################################################################################################

@app.route("/delete", methods=["GET","POST"])
def delete():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          rides.execute('DELETE FROM rides WHERE userid = ? ', session.get('user_id'))
          return redirect('/success')

#############################################################################################################################################
@app.route("/show", methods=["GET","POST"])
def show():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'POST':
          creator = request.form.get('creator')
          acceptor = session.get('user_id')
          print(creator)
          print(acceptor)
          accept.execute('INSERT INTO accept VALUES (?,?)', creator, acceptor)
          return redirect('/details')

#############################################################################################################################################
@app.route("/details", methods=["GET","POST"])
def details():
     if not session.get("name"):
          return redirect("/login")
     if request.method == 'GET':
          userid = accept.execute('SELECT creater FROM accept WHERE accepter = ?', session.get('user_id'))
          print(userid)
          return redirect('/success')
