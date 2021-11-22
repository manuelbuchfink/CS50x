import cs50
import csv
import sys

#checking for correct usage
if len(sys.argv) != 2:
    print("usage: ./impotr.py [csv file]")
    exit(1)

#creating students table
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

#opening csv file
with open(sys.argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)

    # splitting name
    for row in reader:
        names = []
        names.append(row["name"].split(" "))
        header = names[0]

        #inserting into list
        if len(names[0]) == 2:
            db.execute("INSERT INTO students(first, last, house, birth)VALUES (?,?,?,?)",names[0][0], names[0][1], row["house"], int(row["birth"]))
        elif len(names[0]) == 3:
            db.execute("INSERT INTO students(first, middle, last,house, birth) VALUES (?,?,?,?,?)",names[0][0], names[0][1], names[0][2], row["house"],int(row["birth"]))
    exit(0)