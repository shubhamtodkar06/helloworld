import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user = session.get('user_id')
    portfolio = db.execute('SELECT * FROM portfolio WHERE user_id = (?)', user)
    user_info = db.execute('SELECT * FROM users WHERE id = (?)', user)
    user_name = user_info[0]['username'].upper()
    balance = user_info[0]['cash']
    ports = []
    sym = []
    for dic in portfolio:
        if dic['symbol'] not in sym:
            ports.append(dic)
            sym.append(dic['symbol'])
        else:
            temp = {}
            for port in ports:
                if dic['symbol'] == port['symbol']:
                    temp['user_id']  = port['user_id']
                    cash = dic['cash'] + port['cash']
                    temp['cash'] = cash
                    temp['symbol'] = port['symbol']
                    quantity = dic['quantity'] + port ['quantity']
                    temp['quantity'] = (quantity)
                    price = (dic['price'] + port ['price'])/2
                    temp['price'] = (price)
                    temp['action'] = (port['action'])
                    ports.remove(port)
            ports.append(temp)
    invest = 0
    p_l = 0
    value = 0



    for port in ports:
            if port['quantity'] != 0:
                info = lookup(port['symbol'])
                port['name'] = info['name']
                port['c_price'] = info['price']
                current = info['price'] * port['quantity']
                port['current'] = current
                value += current
                profit = current - port['cash']
                p_l += profit
                port['profit'] = profit
                invest += port['cash']
                port['price'] = port['cash'] / port['quantity']
                percent = (port['current']-port['cash'])/port['cash']
                percent = percent * 100
                port['percent'] = percent

    return render_template('index.html', ports = ports, users = user_name, invest = invest, p_l = p_l, value = value, balance = balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template('buy.html')
    else:
        symbol = request.form.get('symbol')
        if not symbol:
            return apology("Symbol NOT Found", 400)
        look = lookup(symbol)
        if not look:
            return apology("Company NOT found", 400)
        quantity = int(request.form.get("shares"))
        if quantity < 1:
            return apology("Incorrect Quantity", 400)

        user_id = session.get('user_id')
        sym = look['symbol']
        pri = look['price']
        cash = pri * quantity
        amount = db.execute('SELECT cash FROM users where id = ?', user_id)
        amount = amount[0]['cash']
        if cash > amount:
            return apology("No Enough Cash available", 403)
        remain = amount - cash
        db.execute('INSERT INTO portfolio(user_id, cash, symbol, quantity, price, action) VALUES (?,?,?,?,?,?)',user_id, cash, sym, quantity, pri, 'buy')
        db.execute('UPDATE users SET cash = (?) where id = (?)', remain, user_id)
        return redirect('/')


@app.route("/history")
@login_required
def history():
    user_id = session.get('user_id')
    ports = db.execute('SELECT * FROM portfolio where user_id = ?', user_id )
    return render_template('history.html', ports = ports)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template('quote.html')
    else:
        symbol = request.form.get('symbol')
        if not symbol:
            return apology("Symbol NOT Found", 400)
        look = lookup(symbol)
        if not look:
            return apology("Company NOT found", 400)

        return render_template('info.html', look = look)




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        user = request.form.get("username")
        username = db.execute("SELECT username FROM users")
        users = []
        for foo in username:
            users.append(foo['username'])
        if user in users:
            return apology("Username is already taken", 400)
        if not user:
            return apology("invalid username and/or password", 400)
        if not request.form.get("password"):
            return apology("Enter Password", 400)
        if not request.form.get("confirmation"):
            return apology("Confirm Password", 400)
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Both Passwords must be same", 400)
        password = generate_password_hash(request.form.get('password'))
        db.execute("INSERT INTO users(username, hash) VALUES(?,?)", user, password)
        list = db.execute("SELECT id FROM users WHERE username = ?",user)
        session["user_id"] = list[0]['id']

        return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == 'GET':
        return render_template('sell.html')
    else:
        user_id = session.get('user_id')
        portfolio = db.execute('SELECT * FROM portfolio WHERE user_id = (?)', user_id)
        symbol = request.form.get('symbol').upper()
        user_info = db.execute('SELECT * FROM users WHERE id = (?)', user_id)
        balance = user_info[0]['cash']
        if not symbol:
            return apology("Symbol NOT Found", 400)
        look = lookup(symbol)
        if not look:
            return apology("Company NOT found", 400)
        Quantity = int(request.form.get("number"))
        if Quantity < 1:
            return apology("Incorrect Quantity", 400)

        ports = []
        sym = []
        for dic in portfolio:
            if dic['symbol'] not in sym:
                ports.append(dic)
                sym.append(dic['symbol'])
            else:
                temp = {}
                for port in ports:
                    if dic['symbol'] == port['symbol']:
                        temp['user_id']  = port['user_id']
                        cash = dic['cash'] + port['cash']
                        temp['cash'] = cash
                        temp['symbol'] = port['symbol']
                        quantity = dic['quantity'] + port ['quantity']
                        temp['quantity'] = (quantity)
                        price = (dic['price'] + port ['price'])/2
                        temp['price'] = (price)
                        temp['action'] = (port['action'])
                        ports.remove(port)
                ports.append(temp)
        if symbol not in sym:
            return apology('You dont have this share', 400)
        for port in ports:
            if port['symbol'] == symbol:
                if Quantity > port['quantity']:
                    return apology('Please Check Quantity', 400)

        cash = Quantity * look['price']
        current_pri = look['price']
        remain = balance + cash
        db.execute('INSERT INTO portfolio(user_id, cash, symbol, quantity, price, action) VALUES (?,?,?,?,?,?)',user_id, -cash, symbol, -Quantity, -current_pri, 'sell')
        db.execute('UPDATE users SET cash = (?) where id = (?)', remain, user_id)
        return redirect('/')