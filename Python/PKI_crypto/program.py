import sys
if sys.version_info[0] < 3:
    raise Exception("\n\n\nThis program must be ran with Python 3. Try running with python3\n\n\n")

from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives._serialization import NoEncryption
from collections import namedtuple
from pathlib import Path
import argparse
import array
import binascii
import json
import pickle

Deposit = namedtuple('Deposit', ['source', 'dest','amount'])
CURVE = ec.SECP384R1()
# --------------------------------- HELPERS -----------------------------------
def KeygenEnc():
    sk = ec.generate_private_key(CURVE)
    pk = sk.public_key() # PK= g^sk
    return (pk,sk)
def PKEnc(pk, m):
    #elgamal . i.e. turning a key exchange into an encryption schem
    r = ec.generate_private_key(CURVE)
    R= r.public_key()
    k = r.exchange(ec.ECDH(), pk) # the shared secret. (g^sk)^r
    key_stream = HKDF(
        algorithm=hashes.SHA256(),
        length=len(m),
        salt=None,
        info=b'fooo',
        ).derive(k)
    C = bytes([x ^ y for (x, y) in zip(m, key_stream)])
    #serialize
    Rbin=R.public_bytes(encoding=serialization.Encoding.X962,format=serialization.PublicFormat.CompressedPoint)
    ciphertext = (Rbin,C)
    ct = pickle.dumps(ciphertext)
    return ct
def PKDec(sk, ctbin):
    ct = pickle.loads(ctbin)
    Rbin,C = ct
    R= ec.EllipticCurvePublicKey.from_encoded_point(CURVE, Rbin)
    k = sk.exchange(ec.ECDH(), R)
    key_stream = derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=len(C),
        salt=None,
        info=b'fooo',
        ).derive(k)
    return  bytes([x ^ y for (x, y) in zip(C, key_stream)])

def KeygenSig():
    sk = ec.generate_private_key(CURVE)
    pk = sk.public_key() # PK= g^sk
    return (pk,sk)
def Sign(sk,m):
    return sk.sign(m,ec.ECDSA(hashes.SHA256()))
def VerifySig(pk,m,sig):
    try:
        pk.verify(sig,m,ec.ECDSA(hashes.SHA256()))
        return True
    except:
        return False
def serializePK(pk):
    return pk.public_bytes(encoding=serialization.Encoding.X962,format=serialization.PublicFormat.CompressedPoint)
def deserializePK(pkBin):
    return ec.EllipticCurvePublicKey.from_encoded_point(CURVE,pkBin)
def serializeSK(sk):
    return sk.private_bytes(encoding=serialization.Encoding.DER,format=serialization.PrivateFormat.PKCS8,encryption_algorithm=NoEncryption())
def deserializeSK(skBin):
    return serialization.load_der_private_key(skBin,password=None)

def xor(a, b):     # xor two byte arrays, LENGTH MUST BE =
    if len(a) != len(b):
        return -1
    result= bytearray(len(a))
    for i in range(len(a)):
        result[i] = a[i] ^ b[i]
    return result

def keyGenTofileEnc(filename):
    pk,sk = KeygenEnc()
    pkbin = serializePK(pk)
    skbin = serializeSK(sk)
    with open(filename+".enc_pk","wb") as f:
        pickle.dump(pkbin,f)
    with open(filename+".enc_sk","wb") as f:
        pickle.dump(skbin,f)

def keyGenTofileSig(filename):
    pk,sk = KeygenSig()
    pkbin = serializePK(pk)
    skbin = serializeSK(sk)
    with open(filename+".sig_pk","wb") as f:
        pickle.dump(pkbin,f)
    with open(filename+".sig_sk","wb") as f:
        pickle.dump(skbin,f)
# -------- YOUR CODE HERE ----  #
# Task 1
def clientSendDeposit(deposit, bankPK):
    m=pickle.dumps(deposit) # serialize deposit object
    return PKEnc((bankPK),m)

def bankRecieveDeposit(ciphertext, bankSK):
    m = PKDec(bankSK, ciphertext)
    deposit = pickle.loads(m) # deserialize decrypted object
    print("Bank Received Deposit from %s to %s for $ %s \nDecryption Successful!" %deposit)
    return deposit

# Task 2
def attackDeposit(ciphertext, bankPK):
##We KNOW that the position [39-41] is BOB
    rbin,cipher=pickle.loads(ciphertext)

    attempt=bytearray(len(cipher)) #initialize an empty byte array with all 0s

    #then put Bob in the right places in attempt to get the corresponding key values from cipher
    attempt[39]=ord('B')
    attempt[40]=ord('o')
    attempt[41]=ord('b')

    #derive key stream key for the 3 indexes bob takes up by XORing Bob with the ciphertext in those places,
 #use key stream values and XOR 'Eve' with those then put those values in the tweaked ciphertext in the place of the encrypted Bob

    modified= xor(cipher, attempt)

    #Now XOR the derived key for 39-41 with Eve to input Eve as the destination in the encrypted ciphertext
    modified[39]= modified[39] ^ ord('E')
    modified[40]= modified[40] ^ ord('v')
    modified[41]= modified[41] ^ ord('e')

    attack = (rbin, modified)

    attack=pickle.dumps(attack)
    return attack

# Task 3
def clientSendSignedDeposit(deposit, clientSiginingSK, bankPK):
    m= pickle.dumps(deposit)
    ciphertext= PKEnc(bankPK, m)
    ciphertextSigned = {"Signature":Sign(clientSiginingSK, ciphertext), "Cipher": ciphertext, "Signer":"Alice"}
    return ciphertextSigned

def bankRecieveSignedDeposit(ciphertextSigned, bankSK, accounts):
    #verify validity of signature
    if VerifySig(accounts[ciphertextSigned['Signer']], ciphertextSigned['Cipher'], ciphertextSigned['Signature']):
        deposit = pickle.loads(PKDec(bankSK, ciphertextSigned['Cipher'])) # deserialize decrypted object
        print("Bank Received Deposit from %s to %s for $ %s\nSignature Verified, Decryption Sucessful!"%deposit)
        return deposit
    else: return None

# Task 4
def attackSignature(ciphertextSigned, clientSignedSK, bankPK):
    #print(ciphertextSigned)
    signature = ciphertextSigned['Signature']
    ciphertext = ciphertextSigned['Cipher']
    signer = ciphertextSigned['Signer']

    #modify UNSIGNED cipher text with Eve instead of Bob
    modified= attackDeposit(ciphertext, bankPK)

    #recreate signed cipher with Eve's secret signature key
    esig= Sign(clientSignedSK, modified)
    attempt = {"Signature":esig, "Cipher":modified, "Signer":"Eve"}

    return attempt

# ----------------------- DO NOT MODIFY  ------------------------
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    subparsers =  parser.add_subparsers(dest='command')
    subparsers.required = True
    csd = subparsers.add_parser('clientSendDeposit', help = "run client task 1")
    csdSigned = subparsers.add_parser('clientSendSignedDeposit',help = "run client task2")
    # common arguments for client commands
    for p in [csd,csdSigned]:
        p.add_argument("src",help="deposit source")
        p.add_argument("dest",help="deposit destination")
        p.add_argument("amt",help="deposit amount",type=int)
        p.add_argument("bankPK",help="path/to/bankPK")
        p.add_argument('out', help="name of file to write ciphertext to")
    #signed csd takes an extra argument, so add it
    csdSigned.add_argument("clientSK",help=" path to client secret key for signing")
    brd = subparsers.add_parser("bankRecieveDeposit", help = 'run bank task1')
    brdSigned = subparsers.add_parser("bankRecieveDepositSigned", help = 'run bank task2')
    #common arguments for bank commands
    for p in [brd,brdSigned]:
        p.add_argument("bankSK",help="path/to/bankSK")
        p.add_argument("ciphertext",help = "path/to/ciphertext")
        p.add_argument('out', help='name of file to write output of bank to')
    #again need an extra argument
    brdSigned.add_argument("accounts",help = "path/to/accountFile.json")
    attack1=subparsers.add_parser("attack1",help="run first attack")
    attack2=subparsers.add_parser("attack2",help="run second attack")
    #common arguments for attack commands
    for p in [attack1,attack2]:
        p.add_argument('bankPK', help='path/to/bankPK')
        p.add_argument("ct",help="path/to/ciphertext to attack")
        p.add_argument('out', help="output file name")
    #attack two takes an extra arugment so add it
    attack2.add_argument('sk',help = "path/to/ Eve's secret key for signing")



    keygenSig = subparsers.add_parser("keygenSig", help = 'generate a signature public, private and key')
    keygenEnc = subparsers.add_parser("keygenEnc", help = 'generate a signature public, private and key')

    keygenSig.add_argument('filename', help='will write keys to filename.sig_pk an filename.sig_sk')
    keygenEnc.add_argument('filename', help='will write keys to filename.enc_pk an filename.enc_sk')


    args = parser.parse_args()


    if args.command == "keygenSig":
        keyGenTofileSig(args.filename)
    elif args.command == "keygenEnc":
        keyGenTofileEnc(args.filename)
    elif args.command == "clientSendDeposit":
        deposit = Deposit(args.src, args.dest, args.amt)
        with open(args.bankPK,'rb') as fPK:
            with open(args.out,'wb') as out:
                pkBin= pickle.load(fPK)
                bankPK = deserializePK(pkBin)
                ciphertext = clientSendDeposit(deposit, bankPK)
                pickle.dump(ciphertext,out)
        #FIXME DO something with this, save it somewhere. Maybe need to take a destination as an argument
    elif args.command == 'clientSendSignedDeposit':
        deposit = Deposit(args.src, args.dest, args.amt)
        with open(args.bankPK,'rb') as fPK:
            with open(args.clientSK, 'rb') as clientSK:
                with open(args.out,'wb') as out:
                    pkBin= pickle.load(fPK)
                    bankPK = deserializePK(pkBin)
                    clientSignedSKbin=pickle.load(clientSK)
                    clientSK = deserializeSK(clientSignedSKbin)
                    ciphertext = clientSendSignedDeposit(deposit, clientSK, bankPK)
                    pickle.dump(ciphertext,out)

    elif args.command == 'attack1':
        with open(args.bankPK, 'rb') as bPK:
            with open(args.ct,'rb') as ct:
                with open(args.out,'wb') as out:
                    ct=pickle.load(ct)
                    pkbin=pickle.load(bPK)
                    bPK=deserializePK(pkbin)
                    modcipher = attackDeposit(ct, bPK)
                    pickle.dump(modcipher,out)
    elif args.command == 'attack2':
        with open(args.bankPK, 'rb') as bPK:
            with open(args.sk, 'rb') as cSK:
                with open(args.ct,'rb') as ct:
                    with open(args.out,'wb') as out:
                        ct=pickle.load(ct)
                        pkbin=pickle.load(bPK)
                        bPK=deserializePK(pkbin)
                        cskbin=pickle.load(cSK)
                        cSK=deserializeSK(cskbin)
                        modcipher = attackSignature(ct, cSK, bPK)
                        pickle.dump(modcipher,out)
    elif args.command == "bankRecieveDeposit":
         with open(args.bankSK,'rb') as fSK:
            with open(args.ciphertext,'rb') as ctextf:
                with open(args.out, 'wb') as out:
                    skBin = pickle.load(fSK)
                    bankSK = deserializeSK(skBin)
                    ciphertext = pickle.load(ctextf)
                    deposit = bankRecieveDeposit(ciphertext,bankSK)
                    pickle.dump(deposit, out)
    elif args.command == 'bankRecieveDepositSigned':
        with open(args.bankSK,'rb') as fSK:
            with open(args.ciphertext,'rb') as ctextf:
                with open(args.accounts) as accounts:
                    with open(args.out, 'wb') as out:
                        names_to_pk_files = json.load(open(args.accounts))
                        accounts = {k: deserializePK(pickle.load(open(v,'rb'))) for (k,v) in names_to_pk_files.items()}
                        skBin = pickle.load(fSK)
                        bankSK = deserializeSK(skBin)
                        ciphertext = pickle.load(ctextf)
                        deposit = bankRecieveSignedDeposit(ciphertext,bankSK, accounts)
                        # TODO Maybe add a print here to indicate bank return?
                        pickle.dump(deposit, out)

    else:
        print("Command out of bounds!")
