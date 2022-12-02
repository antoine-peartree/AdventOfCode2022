EX_DIR=${1}

if [ ! -d "${EX_DIR}" ]
then
    echo "Directory${EX_DIR} does not exist"
    exit -1
fi
cd ${EX_DIR} && g++ -std=c++17 -o day${EX_DIR} main.cpp && ./day${EX_DIR} && cd ..