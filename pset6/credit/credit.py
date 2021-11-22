from cs50 import get_int

#get user input
num = get_int("Number: ")

d1 = 0
d2 = 0
counter = 0
odd = 0
even = 0

#counting digits, digit 1, digit 2, summing even and odd numbers
#while loop <mareksuscak>
while num > 0:
    d2 = d1
    d1 = num % 10

    if counter % 2 == 0:
        even += d1
    else:
        odd += ((d1 *2) // 10) + ((d1 * 2) % 10)

    num //= 10
    counter += 1

#bool to validate checksum
ok = (even + odd) % 10 == 0

#first two digits
d12 = (d1 * 10) + d2

#visa if ok
if d1 == 4 and counter == 13 or counter == 16 and ok:
    print("VISA")

#MC if ok
elif d12 in range(51, 56) and counter == 16 and ok:
    print("MASTERCARD")

#AMEX if ok
elif (d12 == 34 or d12 == 37) and counter == 15 and ok:
    print("AMEX")

#INVAL if not ok
else:
    print("INVALID")