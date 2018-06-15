rm -r Output
mkdir -p Output
g++ CPP_Testing/main.cpp -o CPP_Testing/main -w -std=c++11
cd CPP_Testing
./main
cd ..
cd PythonApp
python3 Grapher.py ../Output/Deque_Random0to100000.csv