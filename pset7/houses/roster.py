import sys
import cs50

#checking for correct usage
if len(sys.argv) != 2:
    print("usage python roster.py [house]")
    exit(1)

#selecting students from table
db = cs50.SQL("sqlite:///students.db")
result = db.execute(f"SELECT * FROM students WHERE house = '{sys.argv[1]}' ORDER BY last, first;")

# printing students
for row in result:
    print(row["first"], end= " ")

    if row["middle"] != None:
        print(row["middle"], end= " ")

    print(row["last"], end= ",")

    print(f" born",row["birth"])
exit(0)
