import random
import string

sequence = ''.join(random.choices(string.ascii_letters + string.digits, k=1000000))

with open("sequence.txt", "w") as f:
    f.write(sequence)