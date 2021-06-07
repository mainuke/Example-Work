#!/bin/bash
cd /home/mai/Dropbox/Sent-files/School-work/2021/Spring-2021/CMSC414/hw5;
echo "CMSC414: HW5 HW-Spec task commands:";
echo "Task 1: ";
python3 program.py clientSendDeposit Alice Bob 50 Bank.enc_pk t1ctext;
python3 program.py bankRecieveDeposit Bank.enc_sk t1ctext t1Recieved;
echo "Task 2: ";
python3 program.py attack1 Bank.enc_pk t1ctext t2ctextTweaked;
python3 program.py bankRecieveDeposit Bank.enc_sk t2ctextTweaked t2Recieved;
echo "Task 3: ";
python3 program.py clientSendSignedDeposit Alice Bob 50 Bank.enc_pk t3ctext Alice.sig_sk;
python3 program.py bankRecieveDepositSigned Bank.enc_sk t3ctext t3Recieved accounts.json;
echo "Task 4: ";
python3 program.py attack2 Bank.enc_pk t3ctext t4AttackedCiphertext Eve.sig_sk;
python3 program.py bankRecieveDepositSigned Bank.enc_sk t4AttackedCiphertext t4Recieved accounts.json;
echo "Deleting generated files";
rm -f t1* t2* t3* t4*;
