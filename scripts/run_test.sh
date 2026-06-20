
#!/bin/bash
# alias で設定しておくと楽です。alias stress = 'source /path/to/this/file'
g "$1" -o gen.out
g "$2" -o sol.out
g "$3" -o naive.out

for ((i=1;;i++)); do
    ./gen.out  > input.txt
    ./sol.out < input.txt > out1.txt
    ./naive.out < input.txt > out2.txt

    if ! diff -q out1.txt out2.txt >/dev/null; then
        echo "Mismatch found on test $i"
        cat input.txt
        echo "--- sol ---"
        cat out1.txt
        echo "--- naive ---"
        cat out2.txt
        exit 1
    fi

    echo "Passed $i"
done