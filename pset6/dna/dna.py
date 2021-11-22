import sys
import csv

#only accepting 3 argvs
if len(sys.argv) != 3:
    print("Usage: python dna.py [csv file] [txt file]")
    exit(1)

# opening csv.file
with open(sys.argv[1], 'r') as csvfile:
    content = csv.reader(csvfile)

    #declaring header
    header = next(content)

    #open textfile
    with open(sys.argv[2], 'r') as file:
        seq = file.read()

        #dict for STR count
        counter = []
        #counting occurences of STR from txt file from index 1
        for i in range(1, len(header)):
            count = 0
            #continuing on to next STR for as many different STRs as there are in header
            for j in header:
                STR = 1

                while (header[i] * STR) in seq:
                    STR += 1
                #find maximum
                if (STR - 1) > count:
                    count = STR - 1
            #putting each maximum in a dictionary
            counter.append(count)

        found = False
        #going through every row to compare STRs
        for row in content:
            for j in range(len(counter)):
                #continue if it doesnt match with current row otherwise break loop
                if int(row[j + 1]) != counter[j]:
                    break
                #print if still in loop
                elif j == (len(counter) - 1):
                    print(row[0])
                    found = True
                    break

        #print no match when loop didnt break
        if found == True:
            exit(0)
        else:
            print("No match")
            exit(0)