import binascii
import sys
import argparse
import string
import array

def task1(c1bin,c2bin,guessbin,offset):
    #note all three of c1bin, c2bin,guessbin have been converted into python3 bytes objects
    output = bytearray(len(c1bin))
    xor= bytearray(len(c1bin))
    space_count={}

    c2 = open("miribarr_2.txt").read()
    c3 = open("miribarr_3.txt").read()
    c4 = open("miribarr_4.txt").read()
    c5 = open("miribarr_5.txt").read()
    c6 = open("miribarr_6.txt").read()
    c7 = open("miribarr_7.txt").read()
    c8 = open("miribarr_8.txt").read()
    c9 = open("miribarr_9.txt").read()
    c10 = open("miribarr_10.txt").read()
    c11 = open("miribarr_11.txt").read()
    c12 = open("miribarr_12.txt").read()
    ciphers = [c12, c11, c10, c9, c8, c7, c6, c5, c4, c3, c2]

    for i in range(0, len(output)):
        #initialize output to asterisks
        output[i] = ord('*')
        #make dictionary to contain # of space occurrences for all 60 characters
        space_count[i]=0

    #convert all ciphertexts hex to string
    for i,c in enumerate(ciphers):
        temp= c
        ciphers[i]= binascii.unhexlify(temp)


    #loop thru all ciphertexts XORd with our first ciphertext arg to see space occurrences
    for curr, cipher in enumerate(ciphers):
        for i in range(0, len(c1bin)):
            x= c1bin[i] ^ cipher[i]
            xor[i]= x
            #if xord character meets one of these conditions, there is most likely a space in one of the plaintexts
            if chr(x).isalpha():
                space_count[i] += 1

    space_ind= []
    #makes array of most likely places with space
    for k in space_count:
        #if occurrence of letters in each position  is >= than 7/11 XORs, then high liklihood cipher1 has spaces in those places
        if space_count[k] >= 7:
            space_ind.append(k)

    for i in space_ind:
        #add a space in each corresponding position in output
        output[i]= ord(' ')

    print(output)

    c=0
    #first xor the two ciphertexts
    for i in range(0, len(output)):
        if i not in space_ind:
            xor[i]= c1bin[i] ^ c2bin[i]
##CRIB DRAG
    #print("\t\t\t\t\t\t"+str(xor))
    #apply crib to current cipher xor
    for i in range(offset, len(output)):
        if c >= len(guessbin):
            c=0

        x= xor[i] ^ guessbin[c]
        if i not in space_ind and chr(x).isalpha():
            output[i]= x
        c+=1

    print("XOR with guess: "+str(guessbin) + " | length: " + str(len(guessbin))+" \n\t" + str(output))

    return output # make sure you return the result for the auto grading

#  $$$$$$$\   $$$$$$\        $$\   $$\  $$$$$$\ $$$$$$$$\       $$\      $$\  $$$$$$\  $$$$$$$\  $$$$$$\ $$$$$$$$\ $$\     $$\
#  $$  __$$\ $$  __$$\       $$$\  $$ |$$  __$$\\__$$  __|      $$$\    $$$ |$$  __$$\ $$  __$$\ \_$$  _|$$  _____|\$$\   $$  |
#  $$ |  $$ |$$ /  $$ |      $$$$\ $$ |$$ /  $$ |  $$ |         $$$$\  $$$$ |$$ /  $$ |$$ |  $$ |  $$ |  $$ |       \$$\ $$  /
#  $$ |  $$ |$$ |  $$ |      $$ $$\$$ |$$ |  $$ |  $$ |         $$\$$\$$ $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$$$$\      \$$$$  /
#  $$ |  $$ |$$ |  $$ |      $$ \$$$$ |$$ |  $$ |  $$ |         $$ \$$$  $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$  __|      \$$  /
#  $$ |  $$ |$$ |  $$ |      $$ |\$$$ |$$ |  $$ |  $$ |         $$ |\$  /$$ |$$ |  $$ |$$ |  $$ |  $$ |  $$ |          $$ |
#  $$$$$$$  | $$$$$$  |      $$ | \$$ | $$$$$$  |  $$ |         $$ | \_/ $$ | $$$$$$  |$$$$$$$  |$$$$$$\ $$ |          $$ |
#  \_______/  \______/       \__|  \__| \______/   \__|         \__|     \__| \______/ \_______/ \______|\__|          \__|
# Helper function to carry out some type conversions
def load_and_format_run(f1,f2,guess,offset):
    ctext1 = f1.readlines()[0]
    ctext2 = f2.readlines()[0]
    c1bin = binascii.unhexlify(ctext1)
    c2bin = binascii.unhexlify(ctext2)
    assert len(c1bin) == len(c2bin)
    guessbin = guess.encode('ascii')
    output = task1(c1bin,c2bin,guessbin,offset)
    assert isinstance(output,bytearray)==True,"task1(c1bin,c2bin,guessbin,offset) must return a byte array"
    f = open('task1.out', 'w')
    f.write(str(output.hex()))
    f.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(usage="%(prog)s path/to/ciphertext1.txt path/to/ciphertext2.txt 'a multi word guess' 5")
    parser.add_argument('ciphertext1', help = 'path to file for ciphertext1')
    parser.add_argument('ciphertext2', help = 'path to file for ciphertext2')
    parser.add_argument('guess', help = 'A string. Note to pass in a multi word guess you need to put quotes around it ')
    parser.add_argument('offset', help = 'An integer where guess goes',type=int)
    args = parser.parse_args()
    with open(args.ciphertext1) as f1:
        with open(args.ciphertext2) as f2:
            load_and_format_run(f1,f2,args.guess,args.offset)
