if [ -z "$1" ]; then
    echo "no testcase supplied"
    exit 1
fi
if [ ! -f "$1" ]; then
    echo "testcase file does not exit"
    exit 1
fi

TESTCASE=$1

cp ${TESTCASE} testcases.txt

make clean
git add .
git commit -m 'test'
git push
yes yes | grade
