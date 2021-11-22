from cs50 import get_string

s = get_string("Text: ")

l = 0
for i in s:
    if(i.isalpha()):
        l+=1

w = s.count(' ') + 1

sen = s.count('.') + s.count('!') + s.count('?')

L = ((l / w ) * 100)
S = ((sen/ w ) * 100)
Grade = (0.0588 * L - 0.296 * S - 15.8)

if Grade < 1:
    print("Before Grade 1")
elif Grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(Grade)}")