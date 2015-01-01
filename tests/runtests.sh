echo "Running unit tests:"

red='\033[0;31m'
green='\033[0;32m'
nocolour='\033[0m'

for f in $(find ./tests/test_* -perm /u=x,g=x,o=x)
do
    if test -f $f
    then
        if ./$f 2>> tests/tests.log
        then
            echo -e "$f ${green}PASSED${nocolour}"
        else
            echo -e "$f ${red}FAILED${nocolour}"
            tail tests/tests.log
            exit 1
        fi
    fi
done
