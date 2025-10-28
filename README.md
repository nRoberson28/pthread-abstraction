Class Thread abstracts <pthread>, creating a java-like implimentation with functions start, stop, run, done, and id. 
Main counts to 100, distributing the work evenly between 5 threads and storing numbers in a vector. 
After counting is complete, the count is outputted in order.

sample output:

Thread 0x16bf2b000 complete... Counted from 61 to 80
Thread 0x16bfb7000 complete... Counted from 81 to 100
Thread 0x16be13000 complete... Counted from 21 to 40
Thread 0x16be9f000 complete... Counted from 41 to 60
Thread 0x16bd87000 complete... Counted from 1 to 20

Final count in order...

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 
21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 
41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 
61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 
81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100
