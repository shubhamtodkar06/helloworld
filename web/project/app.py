from cs50 import SQL
from flask import Flask, render_template, request, redirect, session, send_from_directory
from flask_session import Session
import os

#############################################################################################################################################
app = Flask(__name__)
#############################################################################################################################################
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
#############################################################################################################################################
db = SQL("sqlite:///loger.db")
db1 = SQL("sqlite:///books.db")
db2 = SQL("sqlite:///requests.db")

#############################################################################################################################################


@app.route("/")
def index():
    return render_template("index.html")


#############################################################################################################################################


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    else:
        # get userid as input from user to verify
        user = request.form.get("user")
        if not user:
            return redirect("/login")

        # check if input is number
        if user.isdigit():
            # get list of number form database
            number = db.execute("SELECT number FROM loger")
            numbers = []
            for i in range(len(number)):
                numb = number[i]
                numbers.append(numb["number"])

            # check if input number is in list of numbers
            if int(user) in numbers:
                # get password from database of that user
                pas = db.execute("SELECT pass FROM loger WHERE number=(?)", user)
                passs = []
                for i in range(len(pas)):
                    numb = pas[i]
                    passs.append(numb["pass"])
                # get password from user
                psd = request.form.get("passw")
                if not psd:
                    return redirect("/login")

                # check password
                if passs[0] == psd:
                    name = db.execute("SELECT name FROM loger WHERE number=(?)", user)
                    name = name[0]
                    # define session
                    session["name"] = name["name"]
                    return redirect("/success")
                else:
                    return render_template("login.html", incorrect="Incorrect Password")
            else:
                return render_template("login.html", nofound="**Number NOT Found")

        else:
            userids = db.execute("SELECT user_id FROM loger")
            userid = []
            for i in range(len(userids)):
                userd = userids[i]
                userid.append(userd["user_id"])

            if user in userid:
                pas = db.execute("SELECT pass FROM loger WHERE user_id = (?)", user)
                passs = []
                for i in range(len(pas)):
                    numb = pas[i]
                    passs.append(numb["pass"])
                psd = request.form.get("passw")
                if not psd:
                    return redirect("/login")

                if passs[0] == psd:
                    name = db.execute(
                        "SELECT name FROM loger WHERE user_id = (?)", user
                    )
                    name = name[0]
                    # define session
                    session["name"] = name["name"]
                    return redirect("/success")
                else:
                    return render_template(
                        "login.html", incorrect="**Please Check Password"
                    )
            else:
                return render_template("login.html", nofound="**UserId NOT Found")


#############################################################################################################################################


@app.route("/signup", methods=["GET", "POST"])
def signup():
    if request.method == "GET":
        return render_template("signup.html")
    else:
        signers = db.execute("SELECT user_id FROM loger")
        result = []
        for i in range(len(signers)):
            dictit = signers[i]
            result.append(dictit["user_id"])

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

        password = request.form.get("pass")
        if not password:
            return redirect("/signup")

        if userid in result:
            return render_template("signup.html", alert="UserId is NOT Avaliable!!!")
        else:
            db.execute(
                "INSERT INTO loger(user_id, name, number, email, pass, book) VALUES(?,?,?,?,?,?)",
                userid,
                name,
                int(number),
                email,
                password,
                "none",
            )
            return redirect("/login")


#############################################################################################################################################
@app.route("/confirm", methods=["POST"])
def confirm():
    if not session.get("name"):
        return redirect("/login")

    title = request.form.get("title")
    info = db1.execute("SELECT * FROM books WHERE title = (?)", title)
    info = info[0]
    author = info["author"]
    isbn = info["isbn"]
    db.execute(
        "INSERT INTO note(name, title, author, isbn, action) VALUES(?,?,?,?,?)",
        session.get("name"),
        title,
        author,
        isbn,
        "Borrow",
    )
    return render_template("confirm.html")


#############################################################################################################################################
@app.route("/Borrow", methods=["GET", "POST"])
def Borrow():
    if not session.get("name"):
        return redirect("/login")
    if request.method == "GET":
        return render_template("Borrow.html")
    else:
        if not session.get("name"):
            return redirect("/login")
        types = request.form.get("search_by")
        print(types)
        book_ = request.form.get("book_")
        if types == "title":
            book_ = "%" + book_ + "%"
            books = db1.execute("SELECT * FROM books WHERE title LIKE ?", book_)

        elif types == "author":
            book_ = "%" + book_ + "%"
            books = db1.execute("SELECT * FROM books WHERE author LIKE ?", book_)

        elif types == "series":
            book_ = "%" + book_ + "%"
            books = db1.execute("SELECT * FROM books WHERE series LIKE ?", book_)

        else:
            book_ = "%" + book_ + "%"
            books = db1.execute("SELECT * FROM books WHERE genres LIKE ?", book_)

        return render_template("list.html", books=books)


#############################################################################################################################################

#############################################################################################################################################


@app.route("/Return", methods=["GET", "POST"])
def Return():
    if not session.get("name"):
        return redirect("/login")
    if request.method == "GET":
        user = session.get("name")
        book = db.execute("SELECT book FROM loger where name = (?)", user)
        book = book[0]["book"]
        book = "%" + book + "%"
        books = db1.execute("SELECT * FROM books WHERE isbn LIKE ?", book)
        user = session.get("name")
        return render_template("Return.html", books=books, user=user)
    else:
        user = request.form.get("user")
        info = db.execute("SELECT * FROM loger WHERE name = (?)", user)
        info = info[0]
        isbn = info["book"]
        book = db1.execute("SELECT * FROM books WHERE isbn =(?)", isbn)
        book = book[0]
        title = book["title"]
        author = book["author"]
        db.execute(
            "INSERT INTO note(name, title, author, isbn, action) VALUES(?,?,?,?,?)",
            user,
            title,
            author,
            isbn,
            "Return",
        )
        return render_template("ok.html")


#############################################################################################################################################


@app.route("/requests", methods=["GET", "POST"])
def requests():
    if not session.get("name"):
        return redirect("/login")
    if request.method == "GET":
        return render_template("requests.html")
    else:
        title = request.form.get("title")
        author = request.form.get("author")
        types = request.form.get("search_by")
        text = request.form.get("textarea")
        print(title, author, types, text)
        db2.execute(
            "INSERT INTO requests(name, title, author, requests, description) VALUES (?,?,?,?,?)",
            session.get("name"),
            title,
            author,
            types,
            text,
        )
        return render_template("requested.html")


#############################################################################################################################################


@app.route("/list", methods=["GET", "POST"])
def list():
    if not session.get("name"):
        return redirect("/login")
    if request.method == "GET":
        return render_template("list.html", books=db1.execute("SELECT * FROM books"))
    else:
        if not session.get("name"):
            return redirect("/login")
        book = db.execute("SELECT book FROM loger WHERE name =(?)", session.get("name"))
        book = book[0]
        book = book["book"]
        if book == "none":
            what = request.form.get("borrow")
            books = db1.execute("SELECT * FROM books WHERE title =(?)", what)
            return render_template("descrip.html", books=books)
        else:
            return render_template("nomore.html")


#############################################################################################################################################
@app.route("/success", methods=["GET"])
def succ():
    if not session.get("name"):
        return redirect("/login")
    book = db.execute("SELECT book FROM loger WHERE name =(?)", session.get("name"))
    book = book[0]
    book = book["book"]
    if book == "none":
        return render_template(
            "successful.html", name=session.get("name").upper(), button="Borrow"
        )
    else:
        return render_template(
            "successful.html", name=session.get("name").upper(), button="Return"
        )


#############################################################################################################################################


@app.route("/logout", methods=["GET", "POST"])
def logout():
    if session.get("lib_name"):
        session["lib_name"] = None
        return redirect("/")
    session["name"] = None
    return redirect("/")


#############################################################################################################################################


#############################################################################################################################################


@app.route("/lib_login", methods=["GET", "POST"])
def lib_login():
    if request.method == "GET":
        return render_template("lib.html")
    else:
        user = request.form.get("user")
        if not user:
            return redirect("/lib_login")

        userids = db.execute("SELECT user_id FROM lib")
        userid = []
        for i in range(len(userids)):
            userd = userids[i]
            userid.append(userd["user_id"])

        if user in userid:
            pas = db.execute("SELECT pass FROM lib WHERE user_id = (?)", user)
            passs = []
            for i in range(len(pas)):
                numb = pas[i]
                passs.append(numb["pass"])
            psd = request.form.get("passw")
            if not psd:
                return redirect("/lib_login")

            if passs[0] == psd:
                name = db.execute("SELECT name FROM lib WHERE user_id = (?)", user)
                name = name[0]
                # define session
                session["lib_name"] = name["name"]
                return redirect("/lib_success")
            else:
                return render_template("lib.html", incorrect="**Please Check Password")
        else:
            return render_template("lib.html", nofound="**UserId NOT Found")


#############################################################################################################################################


@app.route("/change_pass", methods=["GET", "POST"])
def change_pass():
    if request.method == "GET":
        return render_template("change.html")
    else:
        user = request.form.get("user")
        if not user:
            return redirect("/change_pass")

        if user.isdigit():
            # get list of number form database
            number = db.execute("SELECT number FROM loger")
            numbers = []
            for i in range(len(number)):
                numb = number[i]
                numbers.append(numb["number"])

            if user in numbers:
                email = request.form.get("email")
                emails = db.execute("SELECT email FROM loger WHERE user_id = (?)", user)
                emails = emails[0]
                emails = emails["email"]
                if emails == email:
                    psd = request.form.get("psd")
                    if not psd:
                        return redirect("/change_pass")
                    passs = request.form.get("pass")
                    if not passs:
                        return redirect("/change_pass")
                    if passs == psd:
                        db.execute(
                            "UPDATE loger SET pass = (?) where number =(?)", psd, user
                        )
                        return redirect("/login")
                    else:
                        return render_template(
                            "change.html", nopass="**Both Passwords MUST be same "
                        )
                else:
                    return render_template(
                        "change.html", noemail="**Incorrect Email Id!!!"
                    )
            else:
                return render_template("change.html", nouserid="**UserId NOT Found!!!")
        else:
            userids = db.execute("SELECT user_id FROM loger")
            userid = []
            for i in range(len(userids)):
                userd = userids[i]
                userid.append(userd["user_id"])

            if user in userid:
                email = request.form.get("email")
                emails = db.execute("SELECT email FROM loger WHERE user_id = (?)", user)
                emails = emails[0]
                emails = emails["email"]
                if emails == email:
                    psd = request.form.get("psd")
                    passs = request.form.get("pass")
                    if passs == psd:
                        db.execute(
                            "UPDATE loger SET pass = (?) where user_id =(?)", psd, user
                        )
                        return redirect("/login")
                    else:
                        return render_template(
                            "change.html", nopass="**Both Passwords MUST be same "
                        )
                else:
                    return render_template(
                        "change.html", noemail="**Incorrect Email Id!!!"
                    )
            else:
                return render_template("change.html", nouserid="**UserId NOT Found!!!")


#############################################################################################################################################
@app.route("/lib_success", methods=["GET", "POST"])
def success_lib():
    if not session.get("lib_name"):
        return redirect("/lib_login")
    if request.method == "GET":
        name = session.get("lib_name")
        return render_template("lib_success.html", name=name)


#############################################################################################################################################


@app.route("/add", methods=["GET", "POST"])
def add():
    if not session.get("lib_name"):
        return redirect("/lib_login")
    if request.method == "GET":
        return render_template("add.html")
    else:
        title = request.form.get("title")
        author = request.form.get("author")
        series = request.form.get("series")
        page = request.form.get("page")
        isbn = request.form.get("isbn")
        coverImg = request.form.get("coverImg")
        descrip = request.form.get("descrip")
        genres = request.form.get("genres")
        genres = "[" + genres + "]"
        y = "Y"
        db1.execute(
            "INSERT INTO books(title, series, author, description, isbn, genres, pages, coverImg, avail) VALUES(?,?,?,?,?,?,?,?,?)",
            title,
            series,
            author,
            descrip,
            isbn,
            genres,
            page,
            coverImg,
            y,
        )
        return render_template("added.html")


#############################################################################################################################################


@app.route("/check", methods=["GET", "POST"])
def check():
    if not session.get("lib_name"):
        return redirect("/lib_login")

    if request.method == "GET":
        requests = db2.execute("SELECT * FROM requests")
        return render_template("check.html", requests=requests)
    else:
        print("helllo")
        title = request.form.get("title")
        requests = request.form.get("requests")

        print(title)
        print(requests)

        db2.execute(
            "DELETE FROM requests WHERE title LIKE ? AND requests LIKE ?",
            title,
            requests,
        )
        return redirect("/add")


#############################################################################################################################################


@app.route("/approve", methods=["GET", "POST"])
def approve():
    if not session.get("lib_name"):
        return redirect("/lib_login")
    if request.method == "GET":
        info = db.execute("SELECT * FROM note")
        return render_template("approve.html", info=info)


#############################################################################################################################################


@app.route("/lib_Return", methods=["POST"])
def lib_Return():
    if not session.get("lib_name"):
        return redirect("/lib_login")
    isbn = request.form.get("isbn")
    db.execute("UPDATE loger SET book = (?) where book = (?)", "none", isbn)
    db1.execute("UPDATE books SET avail = (?) where isbn = (?)", "Y", isbn)
    db.execute("DELETE FROM note WHERE isbn = (?)", isbn)
    return redirect("/approve")


#############################################################################################################################################


@app.route("/lib_Borrow", methods=["POST"])
def lib_Borrow():
    if not session.get("lib_name"):
        return redirect("/lib_login")
    isbn = request.form.get("isbn")
    name = request.form.get("name")
    db.execute("UPDATE loger SET book = (?) where name = (?)", isbn, name)
    db1.execute("UPDATE books SET avail = (?) where isbn = (?)", "N", isbn)
    db.execute("DELETE FROM note WHERE isbn = (?)", isbn)
    return redirect("/approve")


#############################################################################################################################################
@app.route("/upload", methods=["GET", "POST"])
def upload():
    if not session.get("name"):
        return redirect("/login")

    if request.method == "GET":
        return render_template("pdf.html")

    # Check if a file is selected in the form
    if "file" not in request.files:
        return redirect(request.url)

    UPLOAD_FOLDER = "ebooks"
    app.config["UPLOAD_FOLDER"] = UPLOAD_FOLDER

    file = request.files["file"]

    # Check if the file is not empty
    if file.filename == "":
        return redirect(request.url)

    # Save the file to the upload folder
    file.save(os.path.join(app.config["UPLOAD_FOLDER"], file.filename))
    return render_template("uploaded.html")


#############################################################################################################################################

@app.route("/ebooks", methods=["GET", "POST"])
def ebooks():
    if not session.get("name"):
        return redirect("/login")

    EBOOK_FOLDER = 'ebooks'
    app.config['EBOOK_FOLDER'] = EBOOK_FOLDER

    search_query = request.args.get('search', '')  # Get the search query from the URL parameter

    # Get the list of files in the ebook folder
    files = os.listdir(app.config['EBOOK_FOLDER'])

    if search_query:
        # Filter the list of files based on the search query
        files = [file for file in files if search_query.lower() in file.lower()]

    return render_template('ebooks.html', files=files)


@app.route('/ebook/<path:filename>')
def serve_ebook(filename):
    if not session.get("name"):
        return redirect("/login")
    EBOOK_FOLDER = 'ebooks'
    app.config['EBOOK_FOLDER'] = EBOOK_FOLDER
    return send_from_directory(app.config['EBOOK_FOLDER'], filename)
