echo "TEST"
./shift_client localhost 2091 ./short.txt 4 > out1.txt &

./shift_client localhost 2091 ./short.txt 7 > out2.txt &

sleep 5
diff -iw out1.txt short_4.txt
diff -iw out2.txt short_7.txt

