#!/bin/bash
PORT=8080

nc 127.0.0.1 $PORT > /tmp/received.txt &
RECEIVER=$!
sleep 0.2

MSG=$(python3 -c "print('A' * 10000)")

exec 3<>/dev/tcp/127.0.0.1/$PORT
printf "%s\n" "$MSG" >&3
sleep 0.5
exec 3>&-

sleep 0.5
kill $RECEIVER 2>/dev/null

echo "=== received ==="
cat /tmp/received.txt

echo "=== expected ==="
echo "client 1: $(python3 -c "print('A' * 10000)")"

echo "=== diff ==="
RECEIVED=$(grep "client 1:" /tmp/received.txt | sed 's/client 1: //')
EXPECTED=$(python3 -c "print('A' * 10000)")
if [ "$RECEIVED" = "$EXPECTED" ]; then
    echo "OK"
else
    echo "KO"
    echo "size received:  ${#RECEIVED}"
    echo "size expected:  ${#EXPECTED}"
fi