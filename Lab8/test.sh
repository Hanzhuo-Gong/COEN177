

echo
echo
echo

echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput.txt | ./fifo 10 | wc -l
cat testInput.txt | ./fifo 50 | wc -l
cat testInput.txt | ./fifo 100 | wc -l
cat testInput.txt | ./fifo 250 | wc -l
cat testInput.txt | ./fifo 500 | wc -l

echo
echo
echo

echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput.txt | ./sc 10 | wc -l
cat testInput.txt | ./sc 50 | wc -l
cat testInput.txt | ./sc 100 | wc -l
cat testInput.txt | ./sc 250 | wc -l
cat testInput.txt | ./sc 500 | wc -l

echo
echo
echo

echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput.txt | ./lru 10 | wc -l
cat testInput.txt | ./lru 50 | wc -l
cat testInput.txt | ./lru 100 | wc -l
cat testInput.txt | ./lru 250 | wc -l
cat testInput.txt | ./lru 500 | wc -l


echo
echo
echo
